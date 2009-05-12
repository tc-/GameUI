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
#ifndef UIUIPOPUP_H
#define UIUIPOPUP_H

#include "uirect.h"
#include "uiwidget.h"
#include "uiborder.h"
#include "uitheme.h"

namespace Ui {

class Gui;

/**
The base Popup class

@author Tommy Carlsson
*/
class Popup : public has_slots<>
{
public:

  Popup();
  virtual ~Popup();

  virtual void setTheme( Theme & t, const string prefix = "" );

  virtual int top(  ) const { return pTop; }
  virtual void setTop( int t ) { pTop = t; updated(); }

  virtual int left(  ) const { return pLeft; }
  virtual void setLeft( int l ) { pLeft = l; updated(); }
	
	virtual void setPosition( int l, int t );

  virtual int width() const { return pWidth; }
  virtual void setWidth( const int w ) { pWidth = w; updated(); }
  virtual int height() const { return pHeight; }
  virtual void setHeight( const int h ) { pHeight = h; updated(); }
  virtual Rect getRect() const { return Rect( left(), top(), width(), height() ); }

  virtual Drawmode drawmode() const { return pDrawmode; }
  virtual void setDrawmode( const Drawmode dm ) { pDrawmode = dm; updated(); }
  virtual bool active() const { return pActive; }
  virtual void setActive( const bool a ) { pActive = a; updated(); }

  virtual Border* border() const { return pBorder; }
  virtual void setBorder( Border* bs ) { pBorder = bs; updated(); }

  virtual void popup( const int x, const int y, Gui& gui );
  virtual void close();

  virtual void updated();
	virtual void updated( Rect r );
	virtual void beginUpdate();
  virtual void endUpdate( const bool doRender = true );

  virtual void render( Rect area );

  virtual Gui* gui() { return pGui; }

	virtual bool passEvents() { return false; }
	
  virtual void mouseMove( int x, int y, MouseButtons mb ) {}
  virtual void mousePressed( int x, int y, MouseButtons mb ){ close(); }
  virtual void mouseReleased( int x, int y, MouseButtons mb ){}

  signal1<Popup&> onClose;
  signal1<Popup&> onDestroy;
  signal2<Popup&, MouseButtons> onMousePressed;
  signal2<Popup&, MouseButtons> onMouseReleased;
  signal4<Popup&, int, int, MouseButtons> onMouseMove;

private:

  int pTop;
  int pLeft;
  int pWidth;
  int pHeight;
  Border* pBorder;
  Drawmode pDrawmode;
  Gui* pGui;
  bool pActive;
  int pDoUpdate;

};

}

#endif
