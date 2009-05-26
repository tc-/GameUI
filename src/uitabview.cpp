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


#include "uitabview.h"

namespace Ui {

TabView::TabView(Frame* parent): Frame(parent)
{
	pTabHeight = 28;
	pActiveTab = NULL;
	pTabButton = NULL;
	pTabButtonActive = NULL;
	pMouseInside = false;
}


TabView::~TabView()
{
}

void TabView::setTheme(Theme& t, const string prefix)
{
	Frame::setTheme(t, prefix);
	beginUpdate();
	setCursor( t.getCursor( prefix+"tabview" ) );
	setBorder( t.getBorder( prefix+"tabview" ) );
	setFont( t.getFont( prefix+"tabview" ) );
	setTabButtonBorder( t.getBorder( prefix+"tabview_button" ) );
	setTabButtonActiveBorder( t.getBorder( prefix+"tabview_button_active" ) );
	endUpdate();
}

/*Rect TabView::getClientVisibleRect()
{
  Rect r = Frame::getClientVisibleRect();
	r.top += pTabHeight;
	r.height -= pTabHeight;
	return r;
}*/

int TabView::clientVisibleHeight()
{
	return Frame::clientHeight() - pTabHeight;
}


int TabView::borderTop() const
{
	return pTabHeight;//Frame::borderTop();// + pTabHeight;
}

Widget* TabView::mouseClick(int x, int y, MouseButtons mb)
{
    return Frame::mouseClick(x, y, mb);
}

void TabView::setActiveTab( Widget* w )
{
	pActiveTab = w;
	if ( pActiveTab == NULL ) return;
	w->setAlign( walignClient );
//	w->moveToTop();
	for( int i = 0; i < numChildren(); i++ ) {
		Widget* w2 = child( i );
		if ( w2 == NULL ) continue;
		if ( w2 != pActiveTab ) {
			cout << w2->name() << "false" << endl;
			w2->setVisible( false );
		} else {
			cout << w2->name() << "true" << endl;
			w2->setVisible( true );
		}
	}
	w->setVisible( true );
	updated();
}

void TabView::childAdded( Widget* o )
{
	if ( o == NULL ) return;
	if ( pActiveTab == NULL ) {
		setActiveTab( o );
	} else {
		setActiveTab( pActiveTab );
	}
	Frame::childAdded( o );
}

void TabView::render( ImageObject& img, const Rect& r )
{
	if ( !visible() ) return;

	int posx = 0;

	for( int i = 0; i < numChildren(); i++ ) {
		Widget* w = child( i );
		if ( w == NULL ) continue;

		int theight = 0;
		int twidth = 0;
		if ( (font() != NULL) && ( w->name() != "" ) ) {
			theight = font()->textHeight();
			twidth = font()->textWidth( Utils::toWString( w->name() ) );
		}

		Border* b = NULL;
		if ( ( w == activeTab() ) || ( (w == pButtonPressed) && (pMouseInside) ) )
			b = tabButtonActiveBorder();
		else
			b = tabButtonBorder();

		if ( b != NULL ) {
			b->render( Rect( posx, 0-tabHeight(), twidth + b->widthLeft + b->widthRight + 8, tabHeight() ), img );
		}

		if ( font() != NULL ) {
			int t = 0; int l = 0;
			if ( b != NULL )
				l =	posx + Utils::inMiddle( twidth + b->widthLeft + b->widthRight + 8, twidth );
			else
				l = posx + 4;
			t = Utils::inMiddle( tabHeight(), theight )-tabHeight();

			img.outText( Utils::toWString( w->name() ), *font(), l, t, fontColor() );
		}

		if ( b != NULL )
			posx += twidth + b->widthLeft + b->widthRight + 8;
		else
			posx += twidth + 8;

	}

}

Widget* TabView::getTabButtonAt( const int x )
{
	int posx = 0;
	for( int i = 0; i < numChildren(); i++ ) {
		Widget* w = child( i );
		if ( w == NULL ) continue;

		int twidth = 0;
		if ( (font() != NULL) && ( w->name() != "" ) )
			twidth = font()->textWidth( Utils::toWString( w->name() ) );

		Border* b = NULL;
		if ( w == activeTab() )
			b = tabButtonActiveBorder();
		else
			b = tabButtonBorder();

		if ( b != NULL )
			posx += twidth + b->widthLeft + b->widthRight + 8;
		else
			posx += twidth + 8;

		if ( x <= posx )
			return w;
	}
	return NULL;
}

Widget* TabView::mouseMove( int x, int y, MouseButtons mb )
{
	Widget* w = Frame::mouseMove( x, y, mb );
	if ( ( w == this ) && ( pButtonPressed != NULL ) ) {
		if ( y <= tabHeight() ) {
			Widget* w2 = getTabButtonAt( x );
			if ( w2 == pButtonPressed ) {
				pMouseInside = true;
				tabsUpdated();
				return w;
			}
		}
	}
	pMouseInside = false;
	return w;
}

Widget* TabView::mousePressed( int x, int y, MouseButtons mb )
{
	Widget* w = Frame::mousePressed( x, y, mb );
	if ( w == this ) {
    if ( y <= tabHeight() ) {
			Widget* w2 = getTabButtonAt( x );
			if ( w2 != NULL ) {
				grabMouseInput();
				pButtonPressed = w2;
				pMouseInside = true;
				tabsUpdated();
				return w;
			}
		}
	}
	pButtonPressed = NULL;
	pMouseInside = false;
	return w;
}

Widget* TabView::mouseReleased( int x, int y, MouseButtons mb )
{
	releaseMouseInput();
	Widget* w = Frame::mouseReleased( x, y, mb );
	if ( ( w == this ) && ( pButtonPressed != NULL ) ) {
		if ( y <= tabHeight() ) {
			Widget* w2 = getTabButtonAt( x );
			if ( w2 == pButtonPressed ) {
				setActiveTab( w2 );
				pButtonPressed = NULL;
				pMouseInside = false;
				tabsUpdated();
				return w;
			}
		}
	}
	pButtonPressed = NULL;
	pMouseInside = false;
	return w;
}

Widget* TabView::mouseIn( MouseButtons mb )
{
	return Frame::mouseIn( mb );
}

Widget* TabView::mouseOut( MouseButtons mb )
{
	pMouseInside = false;
	return Frame::mouseOut( mb );
}



}
