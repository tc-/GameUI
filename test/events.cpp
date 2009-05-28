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


#include "events.h"

Events::Events()
{
}


Events::~Events()
{
}

void Events::b1Pressed( PushButton& btn )
{
  if ( btn.text() == L"Blipp" ) {
    btn.setText( L"Blopp" );
  } else {
    btn.setText( L"Blipp" );
  }
}

void Events::b1mPressed( Widget& w, MouseButtons mb )
{
	PushButton& btn = (PushButton&)w;
	if ( btn.text() == L"Blipp" ) {
		btn.setText( L"Blopp" );
	} else {
		btn.setText( L"Blipp" );
	}
}

void Events::transbuttonPressed( PushButton& btn )
{
	btn.parent()->setVisible( false );
}

void Events::b1DblClick( Widget& btn )
{
  PushButton* b = (PushButton*) &btn;
  b->setText( L"Bubble!" );
}

void Events::tTimer( Timer& timer, int& timeout )
{
	if ( timeout == 5000 ) timeout = 0;
	timeout += 100;
	if ( timeout <= 1000 ) {
		cout << " -- Timer Ticked... next tick in: " << timeout << " ms drift: " << timer.drift() << " ms." << endl;
	} else {
		cout << " -- Timer Ticked... that's enuff i'm done here." << endl;
		timer.destroyDelayed();
	}
}

void Events::sc1Scroll( Widget * s, int by )
{
	if ( s == NULL) return;
	HScrollbar* sc = (HScrollbar*)s;
	PushButton* b = (PushButton*)s->tag();
	if ( b == NULL ) return;
	b->setBounds( Utils::inMiddle( 204, sc->scrollerPos() + 24 ) + 2, Utils::inMiddle( 100, (int)((sc->scrollerPos() + 160) * 0.1) ) + 198, sc->scrollerPos() + 64, (int)((sc->scrollerPos() + 160) * 0.12) );
	if ( b->font() == NULL ) return;
	b->font()->setSize( (int)(sc->scrollerPos() * 0.15) + 14 );
}

void Events::dfbDrag(Widget* w, int x, int y, DragObject** d )
{
	static DragObject dd;
	dd.setImage( Theme::defaultTheme().getImage( "trans_coder" ) );
	dd.setDenyImage( Theme::defaultTheme().getImage( "dont_drop" ) );
	dd.setDrawmode( drawTransparent );
	*d = &dd;
}

void Events::dtbDrop( Widget* w, int x, int y, DragObject* d, bool& a )
{
	a = true;
	int* i = (int*)w->tag();
	*i = *i + 1;
	PushButton* pb = (PushButton*)w;
	if ( *i == 1 )
		pb->setImage( Theme::defaultTheme().getImage( "coder" ) );
	pb->setText( L"x" + Utils::toWString( *i ) );
}

void Events::dtbDragOver( Widget* w, int x, int y, DragObject* d, bool& a, ImageObject** i )
{
	a = true;
}

void Events::btbPressed( PushButton& btn )
{
	int* i = (int*)btn.tag();
	if ( *i > 1 ) {
		*i = *i - 1;
		btn.setText( L"x" + Utils::toWString( *i ) );
	} else if ( *i == 1 ) {
		*i = 0;
		btn.setText( L"Drop here" );
		btn.setImage( NULL );
	}
}




