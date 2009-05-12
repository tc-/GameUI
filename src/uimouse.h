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
#ifndef UIUIMOUSE_H
#define UIUIMOUSE_H

#include <gameui.h>
#include <sigslot.h>
#include <uiwidget.h>
#include <uigui.h>

namespace Ui {

class MouseCursor;

typedef MouseCursor* (*MouseCursorFactory)();

/**
 * Abstract class used to implement a mouse cursor.
 * @author Tommy Carlsson
 */ 
class MouseCursor {
public:
	MouseCursor() {}
	virtual ~MouseCursor() {}
	virtual void load( ImageObject& img, const int& hotspotX, const int& hotspotY, const Color& transparentColor, const Color& invertColor ) = 0;
	virtual bool isLoaded() = 0;
	virtual bool isSystem() = 0;
	static MouseCursor* createMouseCursor();
	static void setMouseCursorFactory( MouseCursorFactory f );
	
private:
	static MouseCursorFactory pFactory;
};

/**
 * Abstract class used to implement a mouse control.
 * @author Tommy Carlsson
 */
class Mouse : public has_slots<>
{
public:

  Mouse( Gui* g = NULL ) { pGui = g; }
  virtual ~Mouse() {}

  virtual Gui* gui() {  return pGui; }
  virtual void setGui( Gui* s ) {  pGui = s; }

  virtual void update() = 0;
  virtual void mousePos( int& x, int& y ) = 0;
  
	virtual MouseButtons mouseButtons( ) = 0;
	
	virtual MouseCursor* cursor() = 0;
	virtual void setCursor( MouseCursor* mc ) = 0;
	
  signal3< int,int,MouseButtons > onMousePressed;
  signal3< int,int,MouseButtons > onMouseReleased;
  signal3< int,int,MouseButtons > onMouseMove;

private:

  Gui* pGui;

};

}

#endif
