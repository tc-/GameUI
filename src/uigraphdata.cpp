/******************************************************************************
 * Copyright (C) 2005-2009 by Tommy Carlsson
 *
 * This file is part of GameUI.
 *
 * GameUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * GameUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with GameUI.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/


#include <uigraphdata.h>

/*
  TODO:
    Select interpolation type
    Get frame size from parent
*/

namespace Ui {

GraphData::GraphData( Frame* parent )
 : Widget( parent )
{
	setParent(parent);

//TODO: Not working...
//	printf("GraphData: %s\n", parent->name());
//	setWidth(parent->width());
//	setHeight(parent->height());

	setDrawmode(DM_TRANSPARENT);

	rangeXMin = 0.0f;
	rangeXMax = 13000.0f;
	rangeYMin = 0.0f;
	rangeYMax = 80.0f;

	xRange   = rangeXMax-rangeXMin;
	yRange   = rangeYMax-rangeYMin;

	lineColor = Color(100,255,100);

	pInterpolation = GRAPH_INTERPOLATION_LINEAR;

	values = 0;
}

GraphData::~GraphData()
{
}

void  GraphData::autoRange()
{
	float xmin = data[0][0], xmax = data[0][0];
	float ymin = data[0][1], ymax = data[0][1];

	for(int i = 1; i < values; i++)
	{
		printf("Val: %f\n", data[i][0]);
		if(data[i][0] < xmin)
		{
			xmin = data[i][0];
		}
		else if(data[i][0] > xmax)
		{
			xmax = data[i][0];
		}

		if(data[i][1] < ymin)
		{
			ymin = data[i][1];
		}
		else if(data[i][1] > ymax)
		{
			ymax = data[i][1];
		}
	}

	setRange(xmin, xmax, ymin, ymax);
}

void GraphData::setRange(float a, float b, float c, float d)
{
	rangeXMin = a;
	rangeXMax = b;
	rangeYMin = c;
	rangeYMax = d;

	recalculate();
}

void GraphData::setXMin(float n)
{
	rangeXMin = n;
	updated();
}

void GraphData::setXMax(float n)
{
	rangeXMax = n;
	updated();
}

void GraphData::setYMin(float n)
{
	rangeYMin = n;
	updated();
}

void GraphData::setYMax(float n)
{
	rangeYMax = n;
	updated();
}

void GraphData::setInterpolationType(int type)
{
	pInterpolation = type;
	updated();
}

void GraphData::setTheme( Theme& t, const string prefix )
{
	Widget::setTheme( t, prefix );
//  setImage( t.getImage( prefix+"knob" ) );
}

void GraphData::render( ImageObject& img, const Rect& r )
{
	int pixel = 0;
	int old_pixel = 0;

	for(int i = 0; i < values-1; i++)
	{
		if(pInterpolation == GRAPH_INTERPOLATION_NONE)
		{
			img.putPixel(data_pixels[i][0], (int)getValue(i, 1), lineColor);
		}
		else
		{
			int spacing = (data_pixels[i+1][0]-data_pixels[i][0]);
			for(int i2 = 0; i2 < spacing; i2++)
			{
				float pos = ((float)i2/(float)(data_pixels[i+1][0]-data_pixels[i][0]));

				//TODO: Select interpolation type
				if(pInterpolation == GRAPH_INTERPOLATION_SPLINE)
				{
					pixel = (int)splineInterpolation(pos, getValue(i-2,1), getValue(i-1, 1), getValue(i, 1), getValue(i+1, 1), getValue(i+2, 1), getValue(i+3, 1));
				}
				else if(pInterpolation == GRAPH_INTERPOLATION_CUBIC)
				{
					pixel = (int)linearInterpolation(pos, getValue(i, 1), getValue(i+1, 1)) + 10;
				}
				else
				{
					pixel = (int)linearInterpolation(pos, getValue(i, 1), getValue(i+1, 1));
				}

				// Going up
				if(pixel > old_pixel)
				{
					for(int apa = abs(pixel-old_pixel); apa >= 0; apa--)
					{
						img.putPixel(data_pixels[i][0]+i2, pixel-apa, lineColor);
					}
				}
				// Going down
				else if(old_pixel > pixel)
				{
					for(int apa = abs(pixel-old_pixel); apa >= 0; apa--)
					{
						img.putPixel(data_pixels[i][0]+i2, pixel+apa-1, lineColor);
					}
				}
				// Same value as previous sample
				else
				{
					img.putPixel(data_pixels[i][0]+i2, pixel, lineColor);
					img.putPixel(data_pixels[i][0]+i2, pixel-1, lineColor);
				}
				old_pixel = pixel;
			}
		}
	}
}

void GraphData::loadData(float* newdata, int size)
{
	int i;
	values = size;

	for(i = 0; i < size; i++)
	{
		data[i][0] = newdata[i*2];
		data[i][1] = newdata[i*2+1];
	}

//	memcpy(&data, newdata, sizeof(float)*2*size);

	recalculate();
}

void GraphData::recalculate()
{
	xRange   = rangeXMax-rangeXMin;
	yRange   = rangeYMax-rangeYMin;

	for(int i = 0; i < values; i++)
	{
		data_pixels[i][0] = (int)((data[i][0]-rangeXMin)/xRange*(float)width());
		data_pixels[i][1] = height()-(int)((data[i][1]-rangeYMin)/yRange*(float)height());
		printf("Kebab\n");
	}
	printf("Range X: %f-%f, Y: %f-%f\n", rangeXMin, rangeXMax, rangeYMin, rangeYMax);

	updated();
}

float GraphData::getValue(int i, int e)
{
	if(i <= 0)
	{
		return data_pixels[0][e];
	}
	else if(i >= 15)
	{
//TODO
		return data_pixels[15][e];
	}
	else
	{
		return data_pixels[i][e];
	}
}

float GraphData::linearInterpolation(float pos, float old, float new2)
{
	return (old+((new2-old)*pos));
}

float GraphData::splineInterpolation(float pos, float p0, float p1, float p2, float p3, float p4, float p5)
{
	return (p2 + 0.04166666666f*pos*((p3-p1)*16.0f+(p0-p4)*2.0f
	+ pos *((p3+p1)*16.0f-p0-p2*30.0f- p4
	+ pos *(p3*66.0f-p2*70.0f-p4*33.0f+p1*39.0f+ p5*7.0f- p0*9.0f
	+ pos *(p2*126.0f-p3*124.0f+p4*61.0f-p1*64.0f- p5*12.0f+p0*13.0f
	+ pos *((p3-p2)*50.0f+(p1-p4)*25.0f+(p5-p0)*5.0f))))));
}

Widget* GraphData::mouseMove( int x, int y, MouseButtons mb )
{
  return this;
}

Widget* GraphData::mouseClick( int x, int y, MouseButtons mb )
{
  return this;
}

Widget* GraphData::mousePressed( int x, int y, MouseButtons mb )
{
  return this;
}

Widget* GraphData::mouseReleased( int x, int y, MouseButtons mb )
{
  releaseMouseInput();
  return this;
}

Widget* GraphData::keyPressed( Key key )
{
  return this;
}


}
