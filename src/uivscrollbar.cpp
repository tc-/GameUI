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
#include "uivscrollbar.h"
#include "uiwidget.h"
#include "uiframe.h"
#include "uigui.h"
#include "uiutils.h"
#include "sigslot.h"

namespace Ui {

VScrollbar::VScrollbar( Frame* parent )
 : Widget( parent )
{
  setWidth( 17 );
  setHeight( 100 );
  pTButtonGlyph = NULL;
  pBButtonGlyph = NULL;

  pButtonBorder = NULL;
  pButtonPressedBorder = NULL;
  pScrollerBorder = NULL;
  pScrollerPressedBorder = NULL;

  pScrollerPos = 0;
  pScrollerMaxPos = 100;
  pScrollerMinHeight = 10;
  pPageSize = 20;

  pScrollerPressed = -1;
  pButtonUpPressed = false;
  pButtonDownPressed = false;

  scrollBy = 5;
  scrollDelay = 8;
  pScrollWait = 0;
}


VScrollbar::~VScrollbar()
{
}

void VScrollbar::setTheme( Theme & t, const string prefix )
{
	Widget::setTheme( t, prefix );
  setBorder( t.getBorder( prefix+"vscrollbar" ) );
  setButtonBorder( t.getBorder( prefix+"vscrollbar_button" ) );
  setButtonPressedBorder( t.getBorder( prefix+"vscrollbar_button_pressed" ) );
  setScrollerBorder( t.getBorder( prefix+"vscrollbar_scroller" ) );
  setTButtonGlyph( t.getImage( prefix+"vscrollbar_glyph_up" ) );
  setBButtonGlyph( t.getImage( prefix+"vscrollbar_glyph_down" ) );
}

ImageObject* VScrollbar::tButtonGlyph() const
{
  return pTButtonGlyph;
}

void VScrollbar::setTButtonGlyph( ImageObject* img )
{
  pTButtonGlyph = img;
}


ImageObject* VScrollbar::bButtonGlyph() const
{
  return pBButtonGlyph;
}

void VScrollbar::setBButtonGlyph( ImageObject* img )
{
  pBButtonGlyph = img;
}


Border* VScrollbar::buttonBorder() const
{
  return pButtonBorder;
}

void VScrollbar::setButtonBorder( Border* b )
{
  pButtonBorder = b;
}


Border* VScrollbar::buttonPressedBorder() const
{
  return pButtonPressedBorder;
}

void VScrollbar::setButtonPressedBorder( Border* b )
{
  pButtonPressedBorder = b;
}


Border* VScrollbar::scrollerBorder() const
{
  return pScrollerBorder;
}

void VScrollbar::setScrollerBorder( Border* b )
{
  pScrollerBorder = b;
}


Border* VScrollbar::scrollerPressedBorder() const
{
  return pScrollerPressedBorder;
}

void VScrollbar::setScrollerPressedBorder( Border* b )
{
  pScrollerPressedBorder = b;
}



int VScrollbar::scrollerPos() const
{
  return pScrollerPos;
}

void VScrollbar::setScrollerPos( const int pos )
{
  int old = pScrollerPos;
  if ( pos < 0 ) 
    pScrollerPos = 0;
	else if ( pos > Utils::max( 0, scrollerMaxPos() - pageSize() ) )
		pScrollerPos = Utils::max( 0, scrollerMaxPos() - pageSize() );
  else
    pScrollerPos = pos;
  if ( pScrollerPos != old ) {
    onScroll( this, old );
  }
}


int VScrollbar::scrollerMaxPos() const
{
  return pScrollerMaxPos;
}

void VScrollbar::setScrollerMaxPos( const int mp )
{
  pScrollerMaxPos = mp;
	setScrollerPos( scrollerPos() );
}


int VScrollbar::scrollerMinHeight() const
{
  return pScrollerMinHeight;
}

void VScrollbar::setScrollerMinHeight( const int mh )
{
  pScrollerMinHeight = mh;
}


int VScrollbar::pageSize() const
{
  if ( pPageSize != 0 ) {
    return pPageSize;
  } else {
    return 1;
  }
}

void VScrollbar::setPageSize( const int ps )
{
  pPageSize = ps;
}


Widget* VScrollbar::keyPressed(Key key)
{
    return Widget::keyPressed(key);
}

Widget* VScrollbar::keyReleased(Key key)
{
    return Widget::keyReleased(key);
}

Widget* VScrollbar::mouseClick(int x, int y, MouseButtons mb)
{
    return Widget::mouseClick(x, y, mb);
}

Widget* VScrollbar::mouseIn(MouseButtons mb)
{
    return Widget::mouseIn(mb);
}

Widget* VScrollbar::mouseMove(int x, int y, MouseButtons mb)
{
  if ( pScrollerPressed >= 0 ) {
    y = y - pScrollerPressed - width();
		double tmp = ( (double)y / (double)(scrollArea() - scrollerSize()) ) * (double)(scrollerMaxPos() - pageSize());
    //cout << "!!! y: " << y << " tmp: " << tmp << " sp: " << pScrollerPressed << endl;
    setScrollerPos( (int)tmp );
    updated();
  }
  return Widget::mouseMove(x, y, mb);
}

Widget* VScrollbar::mouseOut(MouseButtons mb)
{
    return Widget::mouseOut(mb);
}

Widget* VScrollbar::mousePressed(int x, int y, MouseButtons mb)
{
  int el = elementAt( x, y );
  //cout << "* Element Pressed: " << el << endl;
  if ( el != 0 ) {
    if ( el == 1 ) { // Scroller
      pScrollerPressed = y - scrollerTop() - width();
    } else if ( el == 2 ) { // UpButton
      scrollUp();
      pButtonUpPressed = true;
      pScrollWait = 0;
      gui().onTimerTick.connect( this, &VScrollbar::timerTick );
    } else if ( el == 3 ) { // DownButton
      scrollDown();
      pButtonDownPressed = true;
      pScrollWait = 0;
      gui().onTimerTick.connect( this, &VScrollbar::timerTick );
    } else if ( el == 10 ) { // Above Scroller
      scroll( 0-pageSize() );
    } else if ( el == 11 ) { // Below Scroller
      scroll( pageSize() );
    }
    grabMouseInput();
  }
  updated();
  return Widget::mousePressed(x, y, mb);  // On Up Button

}

Widget* VScrollbar::mouseReleased(int x, int y, MouseButtons mb)
{
  int el = elementAt( x, y );
  if ( (pScrollerPressed > 0) && (el == 1) ) {
  } else if ( (pButtonUpPressed) && (el == 2) ) {
  } else if ( (pButtonDownPressed) && (el == 2) ) {
  }
  gui().onTimerTick.disconnect( this );
  pScrollerPressed = -1;
  pButtonUpPressed = false;
  pButtonDownPressed = false;
  releaseMouseInput();
  updated();
  return Widget::mouseReleased(x, y, mb);
}


void VScrollbar::render( ImageObject& img, const Rect& r )
{
  if ( !visible() ) return;

  Border* b;

  int ud = 0;
  if ( pButtonUpPressed ) {
    b = buttonPressedBorder(); 
  } else {
    b = buttonBorder();
    ud = -1;
  }

  if ( b != NULL )
    b->render( Rect(0 - borderLeft(), 0 - borderTop(), width(), width() ), img );

  int dd = 0;
  if ( pButtonDownPressed ) {
    b = buttonPressedBorder();
  } else {
    b = buttonBorder();
    dd = -1;
  }

  if ( b != NULL )
		b->render( Rect( 0 - borderLeft(), height() - width() - borderBottom(), width(), width() ), img );

  if ( bButtonGlyph() != NULL ) {
		img.drawImage( *bButtonGlyph(), Rect( Utils::inMiddle( width(), bButtonGlyph()->width() ) + dd, Utils::inMiddle( width(), bButtonGlyph()->height() ) + height() - width() + dd, 10, 10 ) );
  }
  if ( tButtonGlyph() != NULL ) {
    img.drawImage( *tButtonGlyph(), Rect( ( width() / 2 - tButtonGlyph()->width() / 2 ) + ud, ( width() / 2 - tButtonGlyph()->height() / 2 ) + ud, 10, 10 ) );
  }

	if ( ( scrollerBorder() != NULL ) && ( scrollerSize() < scrollArea() ) ) {
		scrollerBorder()->render( Rect( 0 - borderLeft(), width() + scrollerTop() - borderTop(), width(), scrollerSize() ), img );
  }
	
}


void VScrollbar::setHeight(int h)
{
    Widget::setHeight(h);
}

void VScrollbar::setWidth(int w)
{
    Widget::setWidth(w);
}

int VScrollbar::scrollArea() const
{
  return (height() - (width() * 2));
}

int VScrollbar::scrollerSize() const
{
/*  int s = (int)((double)scrollArea() / ( ((double)scrollerMaxPos() + 1) / (double)pageSize() ));
  if ( s >= scrollerMinHeight() )
    return s;
  else
	return scrollerMinHeight();*/
	if ( pScrollerMaxPos != 0 ) {
		return Utils::max( pScrollerMinHeight, Utils::min( scrollArea(), (int)round ( ( (double)pPageSize / (double)pScrollerMaxPos ) * (double)scrollArea() ) ) );
	} else {
		return scrollArea();
	}
	//int pScrollerMinHeight;
}

int VScrollbar::scrollerTop() const
{
	double tmp = (double)scrollerPos() * ( ( (double)scrollArea() - (double)scrollerSize() ) / (double)(scrollerMaxPos() - pageSize()) );
  //cout << "!!! scrollerTop() = " << tmp << endl;
  return (int)tmp;
}

int VScrollbar::elementAt( const int x, const int y ) const
{
  // Outside
  if ( (x < 0) || (y < 0) || (x > width()) || (y > height() ))
    return 0;

  //cout << "* X: " << x << " Y: " << y << endl;

  // On Scroller
  if ( (x >= 0) && ( y >= width() + scrollerTop()) && ( x <= width()) && ( y <= width() + scrollerTop() + scrollerSize() ) )
    return 1;
  // On Up Button
  if ( (x >= 0) && ( y >= 0) && ( x <= width()) && ( y <= width() ) )
    return 2;
  // On Down Button
  if ( (x >= 0) && ( y >= height()-width()) && ( x <= width()) && ( y <= height() ) )
    return 3;
  // On ScrollArea
  if ( y < width() + scrollerTop() ) 
    return 10; // Above Scroller
  else
    return 11; // Below Scroller
}

void VScrollbar::scrollUp()
{
  scroll( 0-scrollBy );
}

void VScrollbar::scrollDown()
{
  scroll( scrollBy );
}

void VScrollbar::scroll( const int delta )
{
  setScrollerPos( scrollerPos() + delta );
}

void VScrollbar::timerTick( )
{
  if ( pScrollWait <= scrollDelay ) {
    pScrollWait++;
    return;
  }
  if ( pButtonUpPressed ) {
    scrollUp();
    updated();
  } else if ( pButtonDownPressed ) {
    scrollDown();
    updated();
  }
}


}
