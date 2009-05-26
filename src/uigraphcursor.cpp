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


#include "uigraphcursor.h"

/*
  TODO:
    Select interpolation type
    Get frame size from parent
*/

namespace Ui {

GraphCursor::GraphCursor( Frame* parent )
 : Widget( parent )
{
	setParent(parent);

	lineColor = Color(100,100,255);

	setDrawmode(DM_TRANSPARENT);

//TODO: Not working...
//	printf("GraphData: %s\n", parent->name());
//	setWidth(parent->width());
//	setHeight(parent->height());
/*
	rangeXMin = 0.0f;
	rangeXMax = 13000.0f;
	rangeYMin = 0.0f;
	rangeYMax = 80.0f;
*/
}

GraphCursor::~GraphCursor()
{
}
/*
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
*/

void GraphCursor::setTheme( Theme& t, const string prefix )
{
	Widget::setTheme( t, prefix );
//  setImage( t.getImage( prefix+"knob" ) );
}

void GraphCursor::render( ImageObject& img, const Rect& r )
{
	img.vLine(cursorX, 0, height(), lineColor);
	img.hLine(0, cursorY, width(), lineColor);
}

Widget* GraphCursor::mouseMove( int x, int y, MouseButtons mb )
{
  cursorX = x;
  cursorY = y;
  updated();
  return this;
}

Widget* GraphCursor::mouseClick( int x, int y, MouseButtons mb )
{
printf("Click\n");
  return this;
}

Widget* GraphCursor::mousePressed( int x, int y, MouseButtons mb )
{
  return this;
}

Widget* GraphCursor::mouseReleased( int x, int y, MouseButtons mb )
{
  releaseMouseInput();
  return this;
}

Widget* GraphCursor::keyPressed( Key key )
{
  return this;
}


}
