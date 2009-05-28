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


#include <uigraph.h>

/*
  TODO:
  Funktion för att ladda data:
    Skapa ny graf vid behov
    Deallokera data om gammalt finns allokerat
  Funktion för att ändra data
  Funktion för att skapa ny graf manuellt
  Funktion för att ändra grid etc
  Funktion för att ändra data range
  Update range in children
*/

namespace Ui {

Graph::Graph( Frame* parent )
 : Frame( parent )
{
	/*
	hGridColor.setColor  ( 140, 140, 140 );
	hColorFade1.setColor (  80,  80,  80 );
	hColorFade2.setColor ( 120, 120, 120 );
	hStyle        = GRAPH_GRID_FADE | GRAPH_GRID_SOLID;
	hGridSize     = 40;

	vGridColor.setColor  ( 160, 160, 160 );
	vStyle        = GRAPH_GRID_DOTTED;
	vGridSize     = 10;
	vGridDotSize  = 2;
	vGridDotSpace = 1;

	setBgColor ( Color( 127, 127, 127 ) );
	*/

	hGridColor.setColor  ( 140, 140, 200 );
	hStyle        = GRAPH_GRID_SOLID;
	hGridSize     = 500;
	hGridDotSize  = 1;
	hGridDotSpace = 1;

	vGridColor.setColor  ( 140, 140, 200 );
	vStyle        = GRAPH_GRID_SOLID;
	vGridSize     = 5;
	vGridDotSize  = 1;
	vGridDotSpace = 1;

	setBgColor ( Color( 30, 30, 80 ) );

//	setDrawmode( drawTransparent );


//	printf("Graph: %s\n", this->name());
	gData[0].setParent(this);
//	gData[0].setVisible(true);
	gData[0].setTop(3);
	gData[0].setLeft(0);
	gData[0].setWidth(600);
	gData[0].setHeight(400);
	gData[0].setLineColor(Color(100,200,100));

	gData[1].setParent(this);
//	gData[1].setVisible(true);
	gData[1].setTop(3);
	gData[1].setLeft(0);
	gData[1].setWidth(600);
	gData[1].setHeight(400);
	gData[1].setLineColor(Color(100,200,100));

	gCursor[0].setParent(this);
	gCursor[0].setTop(0);
	gCursor[0].setLeft(0);
	gCursor[0].setWidth(600);
	gCursor[0].setHeight(400);
//	gCursor[0].setVisible(true);


	// Default values
	rangeXMin = 0.0f;
	rangeXMax = 100.0f;
	rangeYMin = 0.0f;
	rangeYMax = 20.0f;
}


Graph::~Graph()
{
}

void  Graph::autoRange()
{
	printf("MEEP MEEP\n");
}

void Graph::setRange(float a, float b, float c, float d)
{
	rangeXMin = a;
	rangeXMax = b;
	rangeYMin = c;
	rangeYMax = d;
	updated();
}

void Graph::setXMin(float n)
{
	rangeXMin = n;
	updated();
}

void Graph::setXMax(float n)
{
	rangeXMax = n;
	updated();
}

void Graph::setYMin(float n)
{
	rangeYMin = n;
	updated();
}

void Graph::setYMax(float n)
{
	rangeYMax = n;
	updated();
}

void Graph::setTheme( Theme& t, const string prefix )
{
	Widget::setTheme( t, prefix );
//  setImage( t.getImage( prefix+"knob" ) );
}

//TODO: Jag gissar på att vi ska rendera till en ImageObject?
//TODO: Rita fina små cirklar där linjerna korsar varann
//TODO: Kikarsiktegrej :)
//TODO: A widget for the axles
//TODO: A widget for the graph
void Graph::render( ImageObject& img, const Rect& r )
{
	int i = 0;

	if ( !visible() ) return;
//	int i;
	double e, padding;

	// Calculate range
	xRange   = rangeXMax-rangeXMin;
	yRange   = rangeYMax-rangeYMin;
	xStretch = (double)width()/xRange;
	yStretch = (double)height()/yRange;

	// Draw a faded grid over the horizontal axle
	/*
	//TODO
	if ( hStyle & GRAPH_GRID_FADE ) {
		for ( i = 0; i < width(); i += 1 ) {
			img.vLine( i, 0, height(), Blend(hColorFade1, hColorFade2, (double)sqrt((i%hGridSize)/(double)hGridSize)) );
		}
	}
	*/

	// Draw a solid grid over the horizontal axle
	float unitsPerPixel = xRange/width();
	Color textCol(255, 255, 255);
	for(i = 0; i < (float)(xRange/hGridSize); i++)
	{
		img.vLine((int)(i*hGridSize/unitsPerPixel), 0, height(), hGridColor);
		wstring t = Utils::toWString(rangeXMin+(i*hGridSize));
		img.outText(t, *font(), (int)(i*hGridSize/unitsPerPixel), height()-25,  textCol);
	}

	// Draw a solid grid over the vertical axle
	unitsPerPixel = yRange/height();
	for(i = 0; i < (float)(yRange/vGridSize); i++)
	{
		img.hLine(0, height()-(int)(i*vGridSize/unitsPerPixel), width(), vGridColor);
		wstring t = Utils::toWString(rangeYMin+(i*vGridSize));
		img.outText(t, *font(), 0, height()-(int)(i*vGridSize/unitsPerPixel), textCol);
	}

/*
	if ( hStyle & GRAPH_GRID_SOLID ) {
		for ( e = hGridSize-1.0; e < (double)width(); e += hGridSize*xStretch ) {
			padding = fmod(fabs(width()-rangeXMin), hGridSize) - hGridSize + 1.0;
			img.vLine((int)(e+padding), 0, height(), hGridColor);
		}
	}
*/

	// Draw a dotted grid over the horizontal axle
	/*
	//TODO: this isn't correct anymore
	if ( hStyle & GRAPH_GRID_DOTTED ) {
		for( i = hGridSize-1; i < width(); i += hGridSize ) {
			for( int tmp = 0; tmp < height(); tmp += hGridDotSpace ) {
				for( int korv = 0; korv < hGridDotSize; korv++, tmp++ ) {
					// Because of the range we have to add padding to the grid to make it fit
					padding = (abs(rangeXMin)%hGridSize) - hGridSize + 1;
					img.putPixel(i+padding, tmp, hGridColor);
				}
			}
		}
	}
	*/


	// Draw a faded grid over the vertical axle
	/*
	//TODO
	if ( vStyle & GRAPH_GRID_FADE ) {
		for ( i = 0; i < height(); i += 1 ) {
			img.hLine( 0, i, width(), Blend(vColorFade1, vColorFade2, (double)((i%vGridSize)/(double)vGridSize)) );
		}
	}
	*/

	// Draw a solid grid over the vertical axle
	//TODO
/*
	if ( vStyle == GRAPH_GRID_SOLID ) {
		for( e = vGridSize-1.0; e < (double)height(); e += vGridSize*yStretch ) {
			//TODO: height() or not?
			padding = fmod(fabs((double)height()-rangeYMin), vGridSize) - vGridSize + 1.0;
			img.hLine(0, (int)(e+padding), width(), vGridColor);
		}

//		while(e = )
//		{
//		}
	}
*/

	// Draw a dotted grid over the vertical axle
	/*
	//TODO: this isn't correct anymore
	if ( vStyle & GRAPH_GRID_DOTTED ) {
		for( i = vGridSize-1; i < height(); i += vGridSize ) {
			for( int tmp = 0; tmp < width(); tmp += vGridDotSpace ) {
				for( int korv = 0; korv < vGridDotSize; korv++, tmp++ ) {
					// Because of the range we have to add padding to the grid to make it fit
					padding = (abs(rangeYMin)%hGridSize) - vGridSize + 1;
					img.putPixel(tmp, i+padding, vGridColor);
				}
			}
		}
	}
	*/

	//OK?
//	img.hLine( 0, (int)((double)height()-fabs(rangeYMin)*yStretch), width(), Color(255,255,255) );
//	img.vLine( (int)(fabs(rangeXMin)*xStretch),  0, height(), Color(255,255,255) );

	Frame::render( img, r );
}

Widget* Graph::mouseMove( int x, int y, MouseButtons mb )
{
  return Frame::mouseMove( x, y, mb );
}

Widget* Graph::mouseClick( int x, int y, MouseButtons mb )
{
  return Frame::mouseClick( x, y, mb );
}

Widget* Graph::mousePressed( int x, int y, MouseButtons mb )
{
  return Frame::mousePressed( x, y, mb );
}

Widget* Graph::mouseReleased( int x, int y, MouseButtons mb )
{
  releaseMouseInput();
  return this;
}

Widget* Graph::keyPressed( Key key )
{
  return Widget::keyPressed( key );
}


}
