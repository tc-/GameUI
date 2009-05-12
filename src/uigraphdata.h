/***************************************************************************
 *   Copyright (C) 2007 by Christian Antila                                *
 *   chille@chille.se                                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef UIUIGRAPHDATA_H
#define UIUIGRAPHDATA_H

#include <uiwidget.h>
#include <uiframe.h>


namespace Ui {

#define GRAPH_INTERPOLATION_NONE	0x01
#define GRAPH_INTERPOLATION_LINEAR	0x02
#define GRAPH_INTERPOLATION_CUBIC	0x03
#define GRAPH_INTERPOLATION_SPLINE	0x04

/**
A Graph Widget

@author Christian Antila <chille@chille.se>
*/
class GraphData : public Widget
{
public:
  GraphData( Frame* parent = NULL );
  ~GraphData();

  virtual void setTheme( Theme& t, const string prefix="" );
  virtual void render( ImageObject& img, const Rect& r );

  virtual void recalculate();

  virtual void autoRange();
  virtual void setRange(float a, float b, float c, float d);
  virtual void setXMin(float n);
  virtual void setXMax(float n);
  virtual void setYMin(float n);
  virtual void setYMax(float n);

  virtual int interpolation() { return pInterpolation; }
  virtual void setInterpolationType(int type);

  void loadData(float* newdata, int size);

  void setLineColor(Color col) { lineColor = col; updated(); }

  virtual Widget* mouseMove( int x, int y, MouseButtons mb );
  virtual Widget* mouseClick( int x, int y, MouseButtons mb );
  virtual Widget* mousePressed( int x, int y, MouseButtons mb );
  virtual Widget* mouseReleased( int x, int y, MouseButtons mb );
  virtual Widget* keyPressed( Key key );

  signal2<Widget&,int> onChange;

private:
	//chille
	Color bgColor;
	Color lineColor;

	// Range
	double rangeXMin, rangeXMax;
	double rangeYMin, rangeYMax;
	double xRange;
	double yRange;

	int pInterpolation;

	int background;
	int border;

	// Data
	int values;
	int data_pixels[128][2];
	float data[128][2];
	float getValue(int i, int e);

	// Interpolation
	float linearInterpolation(float, float, float);
	float splineInterpolation(float pos, float p0, float p1, float p2, float p3, float p4, float p5);
};

}

#endif
