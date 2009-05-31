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
Headerfile for the Ui::SDLImageObject class
*/

#ifndef UISDLIMAGEOBJECT_H
#define UISDLIMAGEOBJECT_H

#include <gameui.h>
#include <uiimageobject.h>
#include <uisdlfont.h>
#include <uirect.h>
#include <uiinifile.h>

#include <string>
#include <cmath>
#include "SDL_image.h"
#include "SDL.h"

namespace Ui {

/**
Container for an SDL Image.
@see Ui::ImageObject http://libsdl.org/
@author Tommy Carlsson
*/
class SDLImageObject : public ImageObject
{
public:

  SDLImageObject( const int& width = 0, const int& height = 0 );
  ~SDLImageObject();

  void drawImage ( ImageObject &image, const Rect &dr, const Rect &sr = NULL_RECT );
  void drawImageTiled ( ImageObject &image, const Rect &dr, const Rect &sr = NULL_RECT );
  void drawImageStreched ( ImageObject &image, const Rect &dr, const Rect &sr = NULL_RECT );
  void drawImage( SDL_Surface& image, const Rect r, const Rect &sr = NULL_RECT );
  void fillRect ( const Rect &r, const Color &color );
  void outText ( const wstring &text, Font &font, int left, int top, const Color &color );

	void putPixel ( int left, int top, const Color &color );
	Uint32 getPixel( SDL_Surface *s, const int& x, const int& y );
	Color getPixel( const int& x, const int& y );

  void hLine ( int left, int top, int width, const Color &color );
  void vLine ( int left, int top, int height, const Color &color );

  void pushClipRect ( const Rect &r );
  Rect popClipRect (  );
  Rect clipRect() { return pClipRect; };
  void setRelativePoint( const int left = 0, const int top = 0 );
  void relativePoint( int& left, int& top );
  void freeImage(  );
  bool isLoaded(  );
  bool loadImage( string fname );

  int height(  );
  int width(  );

  SDL_Surface *getSurface();
  Uint32 getColor( Uint8 r, Uint8 g, Uint8 b );
	Uint32 getColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
	void assignSurface( SDL_Surface *surface );
  void flip( bool conditional = true );
  void setAlpha(unsigned short int a );
  void visDebug( const Rect& r );

  static ImageObject* themeSDLImageObjectLoader( const string fname, InifileSection* iniSec, const ThemeLoadOptions& op );
	static ImageObject* sdlImageObjectFactory( const int& width = 0, const int& height = 0 );
private:

  SDL_Surface *s;

  List<Rect> pClipRects;
  Rect pClipRect;
  bool updated;

  int pRelX;
  int pRelY;

  void setClipRect( const Rect& r );
  void unsetClipRect(  );

};

}

#endif
