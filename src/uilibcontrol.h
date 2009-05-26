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


#ifndef UIUILIBCONTROL_H
#define UIUILIBCONTROL_H

#include <sigslot.h>
#include <uigui.h>
#include <uikeyboard.h>
#include <uimouse.h>
#include <uitheme.h>
#include <uiimageobject.h>

namespace Ui {

typedef int ScreenFlags;
const int SF_FULLSCREEN = 1;
const int SF_SWSURFACE = 2;
const int SF_HWSURFACE = 4;
const int SF_DOUBLEBUF = 8;
const int SF_NOFRAME = 16;
const int SF_RESIZABLE = 32;

/**
Abstract class used to implement a control interface.

@author Tommy Carlsson
*/
class LibControl : public has_slots<> {
public:
  LibControl( Gui* g = NULL ) {
    pScreen = NULL;
    pGui = g;
    pHandleKeyboard = true;
    pHandleMouse = true;
    pHandleSys = true;
    pHandleTimers = true;
  }

  virtual ~LibControl() {}

  virtual Gui* gui() { return pGui; }
  virtual void setGui( Gui* g ) {
    pGui = g;
    if ( (pGui != NULL) && (pScreen != NULL) )
      pGui->setScreen( pScreen );
  }
  virtual ImageObject* screen() { return pScreen; }
  virtual void setScreen( ImageObject* s )
  {
    pScreen = s;
    if ( pGui != NULL )
      pGui->setScreen( s );
  }

  virtual bool initializeLibrary() = 0;
  virtual bool finalizeLibrary() = 0;
	virtual ImageObject* createScreen( const int& width, const int& height, const int& bpp, const ScreenFlags& flags, const bool& assign = true ) = 0;
  virtual Keyboard& keyboard() = 0;
  virtual Mouse& mouse() = 0;

  virtual void doHandleEvents( const bool& clearEvents = true ) = 0;

  virtual void clearEvents() = 0;
  virtual void clearKeyboardEvents() = 0;
  virtual void clearMouseEvents() = 0;
  virtual void clearSysEvents() = 0;
	virtual void sleep( const unsigned int& msecs ) = 0;
  virtual void flip( const bool conditional = true ) = 0;
  virtual bool terminated() = 0;

  virtual bool handleKeyboardEvents() { return pHandleKeyboard; }
  virtual bool handleMouseEvents() { return pHandleMouse; }
  virtual bool handleSysEvents() { return pHandleSys; }
  virtual bool handleTimers() { return pHandleTimers; }
  virtual void setHandleKeyboardEvents( const bool& handle = true ) { pHandleKeyboard = handle; }
  virtual void setHandleMouseEvents( const bool& handle = true ) { pHandleMouse = handle; }
  virtual void setHandleSysEvents( const bool& handle = true ) { pHandleSys = handle; }
  virtual void setHandleTimers( const bool& handle = true ) { pHandleTimers = handle; }

  virtual ImageLoader defaultImageLoader() = 0;
  virtual FontLoader defaultFontLoader() = 0;

  signal0<> onQuit;
  signal2<int,int> onResize;
private:
  bool pHandleKeyboard;
  bool pHandleMouse;
  bool pHandleSys;
  bool pHandleTimers;
  ImageObject* pScreen;
  Gui* pGui;
};

/*

LibControl::LibControl( Gui* g )
{
  pScreen = NULL;
  pGui = g;
  pHandleKeyboard = true;
  pHandleMouse = true;
  pHandleSys = true;
  pHandleTimers = true;
}


LibControl::~LibControl()
{
}


Gui* LibControl::gui()
{
  return pGui;
}

void LibControl::setGui( Gui* g )
{
  pGui = g;
}

ImageObject* LibControl::screen()
{
  return pScreen;
}

void LibControl::setScreen( ImageObject* s )
{
  pScreen = s;
}


bool LibControl::handleKeyboardEvents()
{
  return pHandleKeyboard;
}

bool LibControl::handleMouseEvents()
{
  return pHandleMouse;
}

bool LibControl::handleSysEvents()
{
  return pHandleSys;
}

bool LibControl::handleTimers()
{
  return pHandleTimers;
}

void LibControl::setHandleKeyboardEvents( const bool& handle )
{
  pHandleKeyboard = handle;
}

void LibControl::setHandleMouseEvents( const bool& handle )
{
  pHandleMouse = handle;
}

void LibControl::setHandleSysEvents( const bool& handle )
{
  pHandleSys = handle;
}

void LibControl::setHandleTimers( const bool& handle )
{
  pHandleTimers = handle;
}

*/

}

#endif
