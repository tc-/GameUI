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


#ifndef UIUIGRAPH_H
#define UIUIGRAPH_H

//#include <uiimageobject.h>
#include <cmath>
#include <uiframe.h>
#include <uigraphcursor.h>
#include <uigraphdata.h>


//TODO: move this?
#define GRAPH_GRID_NONE			0x01
#define GRAPH_GRID_SOLID		0x02
#define GRAPH_GRID_DOTTED		0x04
#define GRAPH_GRID_FADE			0x08
#define GRAPH_GRID_CIRCLES	0x10
#define GRAPH_GRID_SQUARES	0x20
#define GRAPH_GRID_XXXXX		0x40
#define GRAPH_GRID_XXXX			0x80


#define Blend(col1, col2, alpha) Color( \
	(unsigned char)( ((double)col1.getR()*alpha + (double)col2.getR()*(1.0-alpha)) ), \
	(unsigned char)( ((double)col1.getG()*alpha + (double)col2.getG()*(1.0-alpha)) ), \
	(unsigned char)( ((double)col1.getB()*alpha + (double)col2.getB()*(1.0-alpha)) ))


namespace Ui {

/**
A Graph Widget

@author Tommy Carlsson <tc@coderworld.net>
*/
class Graph : public Frame
{
public:
  Graph( Frame* parent = NULL );
  ~Graph();

  virtual void setTheme( Theme& t, const string prefix="" );
  virtual void render( ImageObject& img, const Rect& r );

  virtual void autoRange();
  virtual void setRange(float a, float b, float c, float d);
  virtual void setXMin(float n);
  virtual void setXMax(float n);
  virtual void setYMin(float n);
  virtual void setYMax(float n);

  virtual Widget* mouseMove( int x, int y, MouseButtons mb );
  virtual Widget* mouseClick( int x, int y, MouseButtons mb );
  virtual Widget* mousePressed( int x, int y, MouseButtons mb );
  virtual Widget* mouseReleased( int x, int y, MouseButtons mb );
  virtual Widget* keyPressed( Key key );

  signal2<Widget&,int> onChange;

	GraphData gData[4];
	GraphCursor gCursor[1];

private:
	//chille
	Color bgColor;

	// Range
	double rangeXMin, rangeXMax;
	double rangeYMin, rangeYMax;

	// Grid
	Color hGridColor, vGridColor;
	Color hColorFade1, vColorFade1;
	Color hColorFade2, vColorFade2;
	int hStyle, vStyle;
	int hGridType, vGridType;
	int hGridDotSize, vGridDotSize;
	int hGridDotSpace, vGridDotSpace;
	double hGridSize, vGridSize;

	int background;
	int border;

	float orgioX;
	float origoY;


	double xRange;
	double yRange;
	double xStretch;
	double yStretch;

};

}

#endif
