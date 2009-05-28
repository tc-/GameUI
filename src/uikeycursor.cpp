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
Implementation of the Ui::KeyCursor class.
*/

#include "uikeycursor.h"
#include <uigui.h>

using namespace Ui;


KeyCursor* KeyCursor::pKeyCursorObject = NULL;


KeyCursor::KeyCursor()
{

	pEnabled = false;
  pVisible = false;

	pShow = 700;
	pHide = 400;

	pXPos = 0;
	pYPos = 0;
	pWidth = 2;
  pHeight = 16;

  pColor = Color( 0, 0, 0 );

	pDM = drawOpaque;

	pWidget = NULL;
	pTimer.onTimer.connect( this, &KeyCursor::onTimerTick );

}


KeyCursor::~KeyCursor()
{
	pTimer.setEnabled( false );
	pTimer.onTimer.disconnect( this );
	setFocusedWidget( NULL );
}

void KeyCursor::render( ImageObject& img, const Rect& r )
{
	if ( !visible() || !enabled() ) return;
	Rect r2 = Rect( pXPos, pYPos, pWidth, pHeight );
	r2.crop( r );
	if ( r2.area() > 0 ) {
		img.fillRect( r2, color() );
	}
}



void KeyCursor::setFocusedWidget( Widget* widget )
{
	setEnabled( false );
	setVisible( false );

	if ( widget != NULL ) {
		cout << " -- Ui::KeyCursor::setFocusedWidget( " << widget->name() << " )" << endl;
		pWidget = widget;
		setPosition( 0, 0 );
	} else {
		cout << " -- Ui::KeyCursor::setFocusedWidget( NULL )" << endl;
		pWidget = widget;
		setPosition( 0, 0 );
	}
}

void KeyCursor::updated()
{
	if ( ( enabled() ) && ( pWidget != NULL ) ) {
		pWidget->updated( Rect( pXPos, pYPos, pWidth, pHeight ) );
	}
}

void KeyCursor::onTimerTick( Timer& t, int& to )
{
	pVisible = !pVisible;
	if ( pVisible ) {
		to = pShow;
	} else {
		to = pHide;
	}
	updated();
}



Drawmode KeyCursor::drawmode() const
{
	return pDM;
}


void KeyCursor::setDrawmode( const Drawmode dm )
{
	pDM = dm;
}



bool KeyCursor::shouldRenderBg() const
{
	if ( pDM == drawTransparent )
		return true;
	return !visible();
}



void KeyCursor::setPosition( const int xpos, const int ypos )
{
	pXPos = xpos;
	pYPos = ypos;
	updated();
}


void KeyCursor::setSize( const int w, const int h )
{
	pWidth = w;
	pHeight = h;
	updated();
}


void KeyCursor::setRect( const Rect& r )
{
	pXPos = r.left;
	pYPos = r.top;
	pWidth = r.width;
	pHeight = r.height;
	updated();
}



Rect KeyCursor::getRect( ) const
{
	return Rect( pXPos, pYPos, pWidth, pHeight );
}



Widget* KeyCursor::focusedWidget( ) const
{
	return pWidget;
}



int KeyCursor::left() const
{
	return pXPos;
}


void KeyCursor::setLeft( const int l )
{
	pXPos = l;
	updated();
}


int KeyCursor::top() const
{
	return pYPos;
}


void KeyCursor::setTop( const int t )
{
	pYPos = t;
	updated();
}



int KeyCursor::width() const
{
	return pWidth;
}


void KeyCursor::setWidth( const int w )
{
	pWidth = w;
	updated();
}


int KeyCursor::height() const
{
	return pHeight;
}


void KeyCursor::setHeight( const int h )
{
	pHeight = h;
	updated();
}



bool KeyCursor::visible() const
{
	return pVisible;
}


void KeyCursor::setVisible( const bool vis )
{
	pVisible = vis;
	if ( pVisible ) {
		pTimer.setTimeout( pShow );
	} else {
		pTimer.setTimeout( pHide );
	}
	pTimer.reset();
	updated();
}



bool KeyCursor::enabled() const
{
	return pEnabled;
}


void KeyCursor::setEnabled( const bool en )
{
	pEnabled = en;
	pTimer.setEnabled( true );
	setVisible( true );
	updated();
}



int KeyCursor::showTime() const
{
	return pShow;
}


void KeyCursor::setShowTime( const int ms )
{
	pShow = ms;
	if ( visible() ) {
		pTimer.setTimeout( ms );
	}
}


int KeyCursor::hideTime() const
{
	return pHide;
}


void KeyCursor::setHideTime( const int ms )
{
	pHide = ms;
	if ( !visible() ) {
		pTimer.setTimeout( ms );
	}
}



Color KeyCursor::color() const
{
	return pColor;
}


void KeyCursor::setColor( const Color c )
{
	pColor = c;
	updated();
}



KeyCursor& KeyCursor::cursorObject()
{
	if ( pKeyCursorObject == NULL ) {
		static KeyCursor pDefKC;
		return pDefKC;
	} else {
		return *pKeyCursorObject;
	}
}

void KeyCursor::setCursorObject( KeyCursor* kc )
{
	pKeyCursorObject = kc;
}
