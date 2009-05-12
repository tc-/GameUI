/***************************************************************************
 *   Copyright (C) 2005 by Tommy Carlsson   *
 *   tc@coderworld.net   *
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
#include "uiwindowframe.h"

using namespace Ui;

WindowFrame::WindowFrame()
 : Frame()
{
  pLeftMouseDown = false;
}

WindowFrame::WindowFrame( Frame* parent )
 : Frame( parent )
{
  pLeftMouseDown = false;
}

WindowFrame::~WindowFrame()
{
}

void WindowFrame::setTheme( Theme& t, const string prefix )
{
	Frame::setTheme( t, prefix );
  beginUpdate();
  setBorder( t.getBorder( prefix+"windowframe" ) );
  setFont( t.getFont( prefix+"windowframe" ) );
  setFontColor( t.getColor( prefix+"windowframe_font" ) );
  endUpdate();
}


void WindowFrame::renderBackground(const Rect& r)
{
  Frame::renderBackground(r);
}
/*
void WindowFrame::updateRegion(const Rect& r)
{
  Frame::updateRegion(r);
}*/


Widget* WindowFrame::mouseClick(int x, int y, MouseButtons mb)
{
  //return this;
	return Frame::mouseClick( x, y, mb );
}


Widget* WindowFrame::mouseDblClick(int x, int y, MouseButtons mb)
{
  //return this;
	return Frame::mouseDblClick( x, y, mb );
}


Widget* WindowFrame::mousePressed( int x, int y, MouseButtons mb )
{
  moveToTop();
  updated();

  Widget* obj = Frame::mousePressed( x, y, mb );
  if ( obj == this ) {
    if ( mb == MBT_LEFT ) {
      grabMouseInput();
      pLastMouseX = x;
      pLastMouseY = y;
      pLeftMouseDown = true;
    }
  }
  return obj;
}


Widget* WindowFrame::mouseReleased(int x, int y, MouseButtons mb)
{
  if ( pLeftMouseDown ) {
		releaseMouseInput();
		move( relativeLeft() + ( x - pLastMouseX ), relativeTop() + ( y - pLastMouseY ) );
  }

  pLeftMouseDown = false;
	return Frame::mouseReleased( x, y, mb );
}


Widget* WindowFrame::mouseMove( int x, int y, MouseButtons mb )
{
	
  if ( pLeftMouseDown ) {
		move( relativeLeft() + ( x - pLastMouseX ), relativeTop() + ( y - pLastMouseY ) );
  }
	return Frame::mouseMove( x, y, mb );
}

