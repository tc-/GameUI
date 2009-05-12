/***************************************************************************
 *   Copyright (C) 2005 by Tommy Carlsson                                      *
 *   tc@coderworld.net                                                               *
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
#ifndef UIUISDLCONTROL_H
#define UIUISDLCONTROL_H

#include <uilibcontrol.h>
#include <uisdlkeyboard.h>
#include <uisdlimageobject.h>
#include <uisdlfont.h>
#include <uigui.h>
#include <uisdlmouse.h>
#include <uitheme.h>

#include "SDL.h"

namespace Ui {

/**
Class interfacing with the SDL library

@author Tommy Carlsson
*/
class SDLControl : public LibControl {
public:
  SDLControl( Gui* g = NULL );
  virtual ~SDLControl();

  virtual void setGui( Gui* g );

  virtual bool initializeLibrary();
  virtual bool finalizeLibrary();
	virtual ImageObject* createScreen( const int& width, const int& height, const int& bpp, const ScreenFlags& flags, const bool& assign = true );
  virtual Keyboard& keyboard();
  virtual Mouse& mouse();

  virtual void doHandleEvents( const bool& clearEvs = true );

  virtual void clearEvents();
  virtual void clearKeyboardEvents();
  virtual void clearMouseEvents();
  virtual void clearSysEvents();
	virtual void sleep( const unsigned int& msecs );
  virtual void flip( const bool conditional = true );
  virtual bool terminated();

  ImageLoader defaultImageLoader() { return &SDLImageObject::themeSDLImageObjectLoader; }
  FontLoader defaultFontLoader() { return &SDLFont::themeSDLFontLoader; }

private:

  SDLKeyboard pKeyboard;
  SDLMouse pMouse;
  bool pTerminated;
};

}

#endif
