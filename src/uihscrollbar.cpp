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


#include "uihscrollbar.h"

namespace Ui {


HScrollbar::HScrollbar( Frame* parent )
 : Widget( parent )
{
  setWidth( 100 );
  setHeight( 17 );
  pRButtonGlyph = NULL;
  pLButtonGlyph = NULL;

  pButtonBorder = NULL;
  pButtonPressedBorder = NULL;
  pScrollerBorder = NULL;
  pScrollerPressedBorder = NULL;

  pScrollerPos = 0;
  pScrollerMaxPos = 100;
  pScrollerMinWidth = 10;
  pPageSize = 20;

  pScrollerPressed = -1;
  pButtonRightPressed = false;
  pButtonLeftPressed = false;

  scrollBy = 5;
  scrollDelay = 8;
  pScrollWait = 0;
}


HScrollbar::~HScrollbar()
{
}

void HScrollbar::setTheme( Theme & t, const string prefix )
{
	Widget::setTheme( t, prefix );
  setBorder( t.getBorder( prefix+"hscrollbar" ) );
  setButtonBorder( t.getBorder( prefix+"hscrollbar_button" ) );
  setButtonPressedBorder( t.getBorder( prefix+"hscrollbar_button_pressed" ) );
  setScrollerBorder( t.getBorder( prefix+"hscrollbar_scroller" ) );
  setLButtonGlyph( t.getImage( prefix+"hscrollbar_glyph_left" ) );
  setRButtonGlyph( t.getImage( prefix+"hscrollbar_glyph_right" ) );
	setCursor( t.getCursor( prefix+"hscrollbar" ) );
}

ImageObject* HScrollbar::rButtonGlyph() const
{
  return pRButtonGlyph;
}

void HScrollbar::setRButtonGlyph( ImageObject* img )
{
  pRButtonGlyph = img;
}


ImageObject* HScrollbar::lButtonGlyph() const
{
  return pLButtonGlyph;
}

void HScrollbar::setLButtonGlyph( ImageObject* img )
{
  pLButtonGlyph = img;
}


Border* HScrollbar::buttonBorder() const
{
  return pButtonBorder;
}

void HScrollbar::setButtonBorder( Border* b )
{
  pButtonBorder = b;
}


Border* HScrollbar::buttonPressedBorder() const
{
  return pButtonPressedBorder;
}

void HScrollbar::setButtonPressedBorder( Border* b )
{
  pButtonPressedBorder = b;
}


Border* HScrollbar::scrollerBorder() const
{
  return pScrollerBorder;
}

void HScrollbar::setScrollerBorder( Border* b )
{
  pScrollerBorder = b;
}


Border* HScrollbar::scrollerPressedBorder() const
{
  return pScrollerPressedBorder;
}

void HScrollbar::setScrollerPressedBorder( Border* b )
{
  pScrollerPressedBorder = b;
}



int HScrollbar::scrollerPos() const
{
  return pScrollerPos;
}

void HScrollbar::setScrollerPos( const int pos )
{
  int old = pScrollerPos;
  if ( pos < 0 )
    pScrollerPos = 0;
	else if ( pos > Utils::max( 0, scrollerMaxPos() - pageSize() ))
		pScrollerPos = Utils::max( 0, scrollerMaxPos() - pageSize() );
  else
    pScrollerPos = pos;
  if ( pScrollerPos != old ) {
		onScroll( this, old );
  }
}


int HScrollbar::scrollerMaxPos() const
{
  return pScrollerMaxPos;
}

void HScrollbar::setScrollerMaxPos( const int mp )
{
  pScrollerMaxPos = mp;
}


int HScrollbar::scrollerMinWidth() const
{
  return pScrollerMinWidth;
}

void HScrollbar::setScrollerMinWidth( const int mh )
{
  pScrollerMinWidth = mh;
}


int HScrollbar::pageSize() const
{
  if ( pPageSize != 0 ) {
    return pPageSize;
  } else {
    return 1;
  }
}

void HScrollbar::setPageSize( const int ps )
{
  pPageSize = ps;
}


Widget* HScrollbar::keyPressed(Key key)
{
    return Widget::keyPressed(key);
}

Widget* HScrollbar::keyReleased(Key key)
{
    return Widget::keyReleased(key);
}

Widget* HScrollbar::mouseClick(int x, int y, MouseButtons mb)
{
    return Widget::mouseClick(x, y, mb);
}

Widget* HScrollbar::mouseIn(MouseButtons mb)
{
    return Widget::mouseIn(mb);
}

Widget* HScrollbar::mouseMove(int x, int y, MouseButtons mb)
{
  if ( pScrollerPressed >= 0 ) {
    x = x - pScrollerPressed - height();
		double tmp = ( (double)x / (double)(scrollArea() - scrollerSize()) ) * (double)(scrollerMaxPos() - pageSize());
    //cout << "!!! y: " << y << " tmp: " << tmp << " sp: " << pScrollerPressed << endl;
    setScrollerPos( (int)tmp );
    updated();
  }
  return Widget::mouseMove(x, y, mb);
}

Widget* HScrollbar::mouseOut(MouseButtons mb)
{
    return Widget::mouseOut(mb);
}

Widget* HScrollbar::mousePressed(int x, int y, MouseButtons mb)
{
  int el = elementAt( x, y );
  //cout << "* Element Pressed: " << el << endl;
  if ( el != 0 ) {
    if ( el == 1 ) { // Scroller
      pScrollerPressed = x - scrollerLeft() - height();
    } else if ( el == 2 ) { // RightButton
      scrollRight();
      pButtonRightPressed = true;
      pScrollWait = 0;
      gui().onTimerTick.connect( this, &HScrollbar::timerTick );
    } else if ( el == 3 ) { // LeftButton
      scrollLeft();
      pButtonLeftPressed = true;
      pScrollWait = 0;
      gui().onTimerTick.connect( this, &HScrollbar::timerTick );
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

Widget* HScrollbar::mouseReleased(int x, int y, MouseButtons mb)
{
//  int el = elementAt( x, y );
  /*if ( (pScrollerPressed > 0) && (el == 1) ) {
  } else if ( (pButtonUpPressed) && (el == 2) ) {
  } else if ( (pButtonDownPressed) && (el == 2) ) {
  }*/
  gui().onTimerTick.disconnect( this );
  pScrollerPressed = -1;
  pButtonRightPressed = false;
  pButtonLeftPressed = false;
  releaseMouseInput();
  updated();
  return Widget::mouseReleased(x, y, mb);
}
void HScrollbar::render( ImageObject& img, const Rect& r )
{
  if ( !visible() ) return;

  Border* b;

  int ud = 1;
  if ( pButtonLeftPressed ) {
    b = buttonPressedBorder();
  } else {
    b = buttonBorder();
    ud = 0;
  }

  if ( b != NULL )
		b->render( Rect( 0 - borderLeft(), 0 - borderTop(), height(), height() ), img );

  int dd = 1;
  if ( pButtonRightPressed ) {
    b = buttonPressedBorder();
  } else {
    b = buttonBorder();
    dd = 0;
  }

  if ( b != NULL )
    b->render( Rect( width() - height() - borderRight(), 0 - borderTop(), height(), height() ), img );

  if ( rButtonGlyph() != NULL ) {
		img.drawImage( *rButtonGlyph(), Rect( Utils::inMiddle( clientVisibleHeight(), rButtonGlyph()->width() ) + width() - height() + dd, Utils::inMiddle( clientVisibleHeight(), rButtonGlyph()->height() ) + dd, rButtonGlyph()->width(), rButtonGlyph()->height() ) );
	}
  if ( lButtonGlyph() != NULL ) {
		img.drawImage( *lButtonGlyph(), Rect( Utils::inMiddle( clientVisibleHeight(), rButtonGlyph()->width() ) + ud, Utils::inMiddle( clientVisibleHeight(), rButtonGlyph()->height() ) + ud, lButtonGlyph()->width(), lButtonGlyph()->height() ) );
	}

	if ( ( scrollerBorder() != NULL ) && ( scrollerSize() < scrollArea() ) ) {
		scrollerBorder()->render( Rect( height() + scrollerLeft() - borderLeft(), 0 - borderTop(), scrollerSize(), height() ), img );
  }

}


void HScrollbar::setHeight(int h)
{
    Widget::setHeight(h);
}

void HScrollbar::setWidth(int w)
{
    Widget::setWidth(w);
}

int HScrollbar::scrollArea() const
{
  return (width() - (height() * 2));
}

int HScrollbar::scrollerSize() const
{
  /*int s = (int)((double)scrollArea() / ( ((double)scrollerMaxPos() + 1) / (double)pageSize() ));
  if ( s >= scrollerMinWidth() )
    return s;
  else
		return scrollerMinWidth();*/
	if ( pScrollerMaxPos != 0 ) {
		return Utils::max( pScrollerMinWidth, Utils::min( scrollArea(), (int)round ( ( (double)pPageSize / (double)pScrollerMaxPos ) * (double)scrollArea() ) ) );
	} else {
		return scrollArea();
	}
}

int HScrollbar::scrollerLeft() const
{
	double tmp = (double)scrollerPos() * ( ( (double)scrollArea() - (double)scrollerSize() ) / (double)(scrollerMaxPos() - pageSize()) );
  //cout << "!!! scrollerTop() = " << tmp << endl;
  return (int)tmp;
}

int HScrollbar::elementAt( const int x, const int y ) const
{
  // Outside
  if ( (x < 0) || (y < 0) || (x > width()) || (y > height() ))
    return 0;

  //cout << "* X: " << x << " Y: " << y << endl;

  // On Scroller
  if ( (y >= 0) && ( x >= height() + scrollerLeft()) && ( y <= height()) && ( x <= height() + scrollerLeft() + scrollerSize() ) )
    return 1;
  // On Up Button
  if ( (y >= 0) && ( x >= 0) && ( y <= height()) && ( x <= height() ) )
    return 3;
  // On Down Button
  if ( (y >= 0) && ( x >= width()-height()) && ( y <= height()) && ( x <= width() ) )
    return 2;
  // On ScrollArea
  if ( x < height() + scrollerLeft() )
    return 10; // Above Scroller
  else
    return 11; // Below Scroller
}

void HScrollbar::scrollLeft()
{
  scroll( 0-scrollBy );
}

void HScrollbar::scrollRight()
{
  scroll( scrollBy );
}

void HScrollbar::scroll( const int delta )
{
  setScrollerPos( scrollerPos() + delta );
}

void HScrollbar::timerTick( )
{
  if ( pScrollWait <= scrollDelay ) {
    pScrollWait++;
    return;
  }
  if ( pButtonRightPressed ) {
    scrollRight();
    updated();
  } else if ( pButtonLeftPressed ) {
    scrollLeft();
    updated();
  }
}


}
