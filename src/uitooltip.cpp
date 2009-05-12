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
#include "uitooltip.h"

namespace Ui {

Tooltip::Tooltip()
 : Popup()
{
	pText = L"Tooltip";
	pFont = NULL;
	pFontColor = Color( 0, 0, 0 );
	pPressed = false;
	pAutoResize = true;
}


Tooltip::~Tooltip()
{
}


bool Tooltip::passEvents()
{
	if ( pPressed ) {
		pPressed = false;
		return false;
	}
	return true;
}

void Tooltip::mousePressed(int x, int y, MouseButtons mb)
{
  Popup::mousePressed(x, y, mb);
	close();
	pPressed = true;
}

void Tooltip::render(Rect area)
{
	if ( !active() ) return;
	if ( gui() == NULL ) return;
	gui()->screen().pushClipRect( area );
	
	if ( border() != NULL ) {
		border()->render( Rect( left(), top(), width(), height() ), gui()->screen() );
	}
	
	int x = left();
	int y = top();
	int w = width();
	int h = height();
	if ( border() != NULL ) {
		y += border()->heightTop;
		x += border()->widthLeft;
		w -= border()->widthLeft + border()->widthRight;
		h -= border()->heightTop + border()->heightBottom;
	}
	
	gui()->screen().outText( pText, *pFont, x + 1, y + 1, pFontColor ); 
	
	gui()->screen().popClipRect();

}

void Tooltip::setTheme(Theme& t, const string prefix)
{
  Popup::setTheme(t, prefix);
	Border* b = t.getBorder( prefix+"tooltip" );
	if ( b != NULL )
		setBorder( b );
	Font* f = t.getFont( prefix+"tooltip" );
	if ( f != NULL )
		setFont( f );
	setFontColor( t.getColor( prefix+"tooltip_font", Color( 0, 0, 0 ) ) );
}

void Tooltip::doAutoResize()
{
	if ( pAutoResize ) {
		int w = 10;
		int h = 10;
		if ( border() != NULL ) {
			w = border()->widthLeft + border()->widthRight + 2;
			h = border()->heightBottom + border()->heightTop + 2;
		}
		if ( font() != NULL ) {
			w += font()->textWidth( pText );
			h += font()->textHeight();
		}
		setWidth( w );
		setHeight( h );
	}
}

}
