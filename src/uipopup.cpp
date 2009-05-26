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


#include "uipopup.h"

#include "uigui.h"

namespace Ui {

Popup::Popup()
{
  pTop = 0;
  pLeft = 0;
  pWidth = 100;
  pHeight = 100;
  pBorder = NULL;
  pDrawmode = DM_OPAQUE;
  pActive = false;
  pGui = NULL;
}


Popup::~Popup()
{
  onDestroy( *this );
}

void Popup::setTheme( Theme & t, const string prefix )
{
  setBorder( t.getBorder( prefix+"popup" ) );
}


void Popup::setPosition( int l, int t )
{
	int oldLeft = pLeft;
	int oldTop = pTop;
	pLeft = l;
	pTop = t;
	Rect r( oldLeft, oldTop, width(), height() );
	r.merge( Rect( pLeft, pTop, width(), height() ) );
	updated( r );
}


void Popup::popup( const int x, const int y, Gui& gui )
{
  if ( pActive ) {
    close();
  }
  pTop = y;
  pLeft = x;
  if ( pTop < 0 )
    pTop = 0;
  if ( pTop + pHeight > gui.screen().height() )
    pTop = gui.screen().height() - pHeight;

  if ( pLeft < 0 )
    pLeft = 0;
  if ( pLeft + pWidth > gui.screen().width() )
    pLeft = gui.screen().width() - pWidth;
  pGui = &gui;
  pGui->addPopup( this );
  pActive = true;
  updated();
}

void Popup::close()
{
  if ( pActive ) {
    onClose( *this );
    if ( pGui != NULL )
      pGui->removePopup( this );
  }
  pActive = false;
}


void Popup::updated()
{
  if ( (pActive) && ( pDoUpdate == 0 ) ) {
    if ( pGui != NULL )
      Widget::updatedWidget( NULL, getRect() );
  }
}

void Popup::updated( Rect r )
{
	if ( (pActive) && ( pDoUpdate == 0 ) ) {
		if ( pGui != NULL )
			Widget::updatedWidget( NULL, r );
	}
}

void Popup::beginUpdate()
{
  pDoUpdate++;
}

void Popup::endUpdate( const bool doRender )
{
  if ( pDoUpdate > 0 )
    pDoUpdate--;
  if ( (pDoUpdate == 0) && (doRender) )
    updated();
}

void Popup::render( Rect area )
{
  Rect cr = area;
  cr.crop( getRect() );
  if ( cr.area() <= 0 ) return;
  if ( pGui == NULL ) return;

  pGui->screen().pushClipRect( cr );

  if ( border() != NULL ) {
    border()->render( getRect(), pGui->screen() );
  }

  pGui->screen().popClipRect();

}


}
