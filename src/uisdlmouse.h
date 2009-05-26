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


#ifndef UIUISDLMOUSE_H
#define UIUISDLMOUSE_H

#include <SDL.h>
#include <uimouse.h>
#include <uicolor.h>


namespace Ui {



/**
 * MouseCursor object used with the SDL lib
 * @author Tommy Carlsson
 */
class SDLMouseCursor {
public:

	SDLMouseCursor() { pCursor = NULL; pImage = NULL; }
	virtual ~SDLMouseCursor() { if ( isSystem() ) SDL_FreeCursor( pCursor ); }

	/**
	 *  Loads a cursor from an image.
	 * @note If image only contains the colors black, white, transparentColor and invertColor it will be loaded as a system cursor, and will then enjoy hardware accelleration.
	 * @see MouseCursor::load(), Ui::Mouse, Ui::ImageObject, and Ui::SDLMouse
	 */
	virtual void load( ImageObject& img, const int& hotspotX, const int& hotspotY, const Color& transparentColor, const Color& invertColor );
	/**
	 *  Checks if image contains a system cursor or an image cursor.
	 * @param img the Image to check.
	 * @return true if Image contains a system cursor.
	 * @see MouseCursor::load(), and Ui::ImageObject
	 */
	virtual bool imageIsSystemCursor( ImageObject* img );
	virtual bool isSystem() { return ( pCursor != NULL ); }
	virtual bool isLoaded();

	virtual ImageObject* getImageObject() { return pImage; }
	virtual SDL_Cursor* getSDLCursorObject() { return pCursor; }

	/**
	 *  Creates a SDLMouseCursor object.
	 * @return pointer to a SDLMouseCursor object.
	 * @see MouseCursor::createMouseCursor(), and MouseCursor::setMouseCursorFactory()
	 */
	static MouseCursor* createSDLMouseCursor();

private:

	SDL_Cursor* pCursor;
	ImageObject* pImage;

};





/**
Mouse object for use with the SDL lib

@author Tommy Carlsson
*/
class SDLMouse : public Mouse
{
public:
  SDLMouse( Gui* g = NULL );
  ~SDLMouse();

  virtual MouseButtons mouseButtons();
  virtual void mousePos(int& x, int& y);
  virtual void update();

  virtual MouseButtons translateMouseButtons( const Uint8& sdlButton );

	virtual MouseCursor* cursor();
	virtual void setCursor( MouseCursor* mc );

private:

	SDLMouseCursor* pCursor;
	Widget* pLastMouseOver;
};

}

#endif
