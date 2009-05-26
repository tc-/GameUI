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


/**
@file
Headerfile for the UiImageObject class
*/

#ifndef UIIMAGEOBJECT_H
#define UIIMAGEOBJECT_H

#include <gameui.h>
#include <uilist.h>
#include <uirect.h>
#include <uicolor.h>
#include <uifont.h>
#include <cmath>

namespace Ui {

class ImageObject;

typedef List<ImageObject*> ImageList;

typedef ImageObject* (*ImageObjectFactory)( const int&, const int& );

/**
Abstract class used to represent an image

@author Tommy Carlsson
*/
class ImageObject{
public:
  ImageObject(  ) {}
  virtual ~ImageObject(  ) {}

  virtual void drawImage ( ImageObject &image, const Rect &dr, const Rect &sr = NULL_RECT ) = 0;
  virtual void drawImageTiled ( ImageObject &image, const Rect &dr, const Rect &sr = NULL_RECT ) = 0;
  virtual void drawImageStreched ( ImageObject &image, const Rect &dr, const Rect &sr = NULL_RECT ) = 0;

  virtual void fillRect ( const Rect &r, const Color &color ) = 0;

  virtual void outText ( const wstring &text, Font &font, int left, int top, const Color &color ) = 0;

  virtual void putPixel ( int left, int top, const Color &color ) = 0;
	virtual Color getPixel( const int& x, const int& y ) = 0;
  virtual void hLine ( int left, int top, int width, const Color &color ) = 0;
  virtual void vLine ( int left, int top, int height, const Color &color ) = 0;

	//TODO: remove/move?
	// Return integer part of val
	// Chille OK
	double ipart(double val)
	{
		int tmp = (int)val;
		return (double)tmp;
	}

	// Return fractional part of val
	// Is this one correct?
	double fpart(double val)
	{
		int tmp = (int)val;
		return (val-(double)tmp);
	}

	// Round - round to nearest integer
	// Chille OK
	double round(double val)
	{
		return ipart(val + 0.5);
	}

	// Wtf is this?
	double rfpart(double val)
	{
		return (1.0 - fpart(val));
	}

	virtual void line ( double x1, double y1, double x2, double y2, const Color &color );

  virtual void pushClipRect ( const Rect &r ) = 0;
  virtual Rect popClipRect (  ) = 0;
  virtual Rect clipRect (  ) = 0;

  virtual void setRelativePoint( const int left = 0, const int top = 0 ) = 0;
  virtual void getRelativePoint( int& left, int& top ) = 0;

  virtual void freeImage() = 0;
  virtual bool isLoaded() = 0;
  virtual bool loadImage( string fname ) = 0;

  virtual int width(  ) = 0;
  virtual int height(  ) = 0;

  virtual int sectionWidth(  ) { return pSecWidth; }
  virtual void setSectionWidht( const int& w ) { pSecWidth = w; }
  virtual int sectionHeight(  ) { return pSecHeight; }
  virtual void setSectionHeight( const int& h ) { pSecHeight = h; }

	virtual Rect sectionRect( const int& index );

  virtual int numSections(  )
  {
    if ( ( pSecWidth <= 0 ) || ( pSecHeight <= 0 ) ) return 0;
		return (int)floor( (double)(width() / pSecWidth) ) * (int)floor( (double)(height() / pSecHeight) );
  }

	static ImageObject* createImageObject( const int& width = 0, const int& height = 0 )
	{
		if ( pImageObjectFactory != NULL ) {
			return pImageObjectFactory( width, height );
		} else {
			return NULL;
		}
	}

	static ImageObjectFactory objectFactory()
	{
		return pImageObjectFactory;
	}

	static void setObjectFactory( ImageObjectFactory imgf )
	{
		pImageObjectFactory = imgf;
	}

private:

  int pSecWidth;
  int pSecHeight;
	static ImageObjectFactory pImageObjectFactory;

};

}

#endif
