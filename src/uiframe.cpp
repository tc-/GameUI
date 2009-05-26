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
Implementation of the Ui::Frame class
*/

#include "uiframe.h"

#include <typeinfo>
#include "uiborder.h"

using namespace Ui;

Frame::Frame()
 : Widget()
{
	pCur = NULL;
}

Frame::Frame( Frame* parent )
 : Widget()
{
	pCur = NULL;

  setParent( parent );
}

Frame::~Frame()
{
  int i;
  for( i = 0; i < numChildren(); i++ ) {
    Widget* o = child( i );
    assert( o != NULL );
    o->setParent( NULL );
  }

  for( int i = 0; i < pChildList.count(); i++ ) {
    Widget* o = pChildList.get( i );
    assert( o != NULL );
    o->setParent( NULL );
  }
}

void Frame::setTheme( Theme& t, const string prefix )
{
	beginUpdate();
	Widget::setTheme( t, prefix );
	setCursor( t.getCursor( prefix+"frame" ) );
	setFont( t.getFont( prefix+"frame" ) );
	endUpdate();
}


void Frame::setGui( Gui* s )
{
  //cout << "* Ui::Frame::setScreen(  )" << endl;
  Widget::setGui( s );
  int i;
  for( i = 0; i < numChildren(); i++ ) {
    Widget* o = child( i );
    assert( o != NULL );
    o->setGui( s );
  }
 // cout << "* Ui::Frame::setScreen(  ) done" << endl;
}


void Frame::childUpdated( Widget& o )
{
	if ( &o == pCur ) return;

  arrangeChildren();
	updated();
}

bool Frame::sortWidgetsByLeft(List< Widget* > & l, int i1, int i2)
{
	if ( l.get(i1)->relativeLeft() <= l.get(i2)->relativeLeft() )
		return true;
	return false;
}


bool Frame::sortWidgetsByTop(List< Widget* > & l, int i1, int i2)
{
	if ( l.get(i1)->relativeTop() <= l.get(i2)->relativeTop() )
		return true;
	return false;
}



void Frame::arrangeChildren(  )
{
	// enum WidgetAlignType { walignNone, walignLeft, walignRight, walignTop, walignBottom, walignClient };
//	Rect clientArea = getClientRect();//( 0, 0, clientWidth(), clientHeight() );
	Rect clientArea(0, 0, clientWidth(), clientHeight() );
	List< Widget* > wl;

	// Widgets Aligned -TOP-
	for ( int i = 0; i < pChildList.count(); i++ ) {
		Widget* w = pChildList.get( i );
		assert( w != NULL );
		if ( w->align() == walignTop )
			wl.append( w );
	}
	wl.sort( &sortWidgetsByTop );
	for ( int i = wl.count() - 1; i >= 0; i-- ) {
		Widget* w = wl.get(i);
		w->beginUpdate();
		//pCur = w;
		int h = w->height();

		if ( w->anchorBottom() )
			h = ( clientHeight() - w->relativeTop() ) - w->anchorBottomValue();

		w->setBounds( clientArea.left, clientArea.top, clientArea.width, h );
		w->endUpdate( false );

		clientArea.top += w->height();
		clientArea.height -= w->height();
	}
	wl.clear();

	// Widgets Aligned -BOTTOM-
	for ( int i = 0; i < pChildList.count(); i++ ) {
		Widget* w = pChildList.get( i );
		if ( w->align() == walignBottom )
			wl.append( w );
	}
	wl.sort( &sortWidgetsByTop );
	for ( int i = 0; i < wl.count(); i++ ) {
		Widget* w = wl.get(i);
		w->beginUpdate();
		pCur = w;
		int h = w->height();

		if ( w->anchorTop() )
			h = ( clientHeight() - w->relativeTop() ) - w->anchorTopValue();

		w->setBounds( clientArea.left, clientArea.top + clientArea.height - h, clientArea.width, h );
		w->endUpdate( );
		clientArea.height -= w->height();
	}
	wl.clear();

	// Widgets Aligned -LEFT-
	for ( int i = 0; i < pChildList.count(); i++ ) {
		Widget* w = pChildList.get( i );
		if ( w->align() == walignLeft )
			wl.append( w );
	}
	wl.sort( &sortWidgetsByLeft );
	for ( int i = 0; i < wl.count(); i++ ) {
		Widget* wi = wl.get(i);
		wi->beginUpdate();
		pCur = wi;
		int w = wi->width();

		if ( wi->anchorRight() )
			w = clientWidth() - wi->relativeLeft() - wi->anchorRightValue();

		wi->setBounds( clientArea.left, clientArea.top, w, clientArea.height );
		wi->endUpdate( );
		clientArea.left += wi->width();
		clientArea.width -= wi->width();
	}
	wl.clear();

	// Widgets Aligned -RIGHT-
	for ( int i = 0; i < pChildList.count(); i++ ) {
		Widget* w = pChildList.get( i );
		if ( w->align() == walignRight )
			wl.append( w );
	}
	wl.sort( &sortWidgetsByLeft );
	for ( int i = wl.count() - 1; i >= 0; i-- ) {
		Widget* wi = wl.get(i);
		wi->beginUpdate();
		pCur = wi;
		int w = wi->width();

		if ( wi->anchorRight() )
			w = clientWidth() - wi->relativeLeft() - wi->anchorLeftValue();

		wi->setBounds( clientArea.left + clientArea.width - w, clientArea.top, w, clientArea.height );
		wi->endUpdate( );
		clientArea.width -= wi->width();
	}
	wl.clear();

	// Widgets Aligned -CLIENT-
	for ( int i = 0; i < pChildList.count(); i++ ) {
		Widget* w = pChildList.get( i );
		if ( w->align() == walignClient )
			wl.append( w );
	}
	wl.sort( &sortWidgetsByLeft );
	for ( int i = wl.count() - 1; i >= 0; i-- ) {
		Widget* wi = wl.get(i);
		wi->beginUpdate();
		pCur = wi;

		wi->setBounds( clientArea.left, clientArea.top, clientArea.width, clientArea.height );
		wi->endUpdate( );
	}
	wl.clear();


	// Widgets With No Align But Uses -ANCHORS-
	for ( int i = 0; i < pChildList.count(); i++ ) {
		Widget* w = pChildList.get( i );
		if ( (w->align() == walignNone) && ( (w->anchorLeft()) || (w->anchorRight()) || (w->anchorTop()) || (w->anchorBottom()) ) )
			wl.append( w );
	}
	for ( int i = 0; i < wl.count(); i++ ) {
		Widget* wi = wl.get(i);
		pCur = wi;
		int t = wi->relativeTop();
		int l = wi->relativeLeft();
		int w = wi->width();
		int h = wi->height();

		if ( ( wi->anchorLeft() ) && ( wi->anchorRight() ) ) {
			l = wi->anchorLeftValue();
			w = clientWidth() - wi->anchorLeftValue() - wi->anchorRightValue();
			if ( w > wi->maxWidth() ) {
				l = l + Utils::inMiddle( w, wi->maxWidth() );
				w = wi->maxWidth();
			}
			if ( w < wi->minWidth() ) {
				l = l - Utils::inMiddle( wi->minWidth(), w );
				w = wi->minWidth();
			}

		} else {
			if ( wi->anchorLeft() )
				l = wi->anchorLeftValue();
			else if ( wi->anchorRight() )
				l = clientWidth() - wi->width() - wi->anchorRightValue();
		}
		if ( ( wi->anchorTop() ) && ( wi->anchorBottom() ) ) {
			t = wi->anchorTopValue();
			h = clientHeight() - wi->anchorTopValue() - wi->anchorBottomValue();
			if ( h > wi->maxHeight() ) {
				t = t + Utils::inMiddle( h, wi->maxHeight() );
				h = wi->maxHeight();
			}
			if ( h < wi->minHeight() ) {
				t = t - Utils::inMiddle( wi->minHeight(), h );
				h = wi->minHeight();
			}

		} else {
			if ( wi->anchorTop() )
				t = wi->anchorTopValue();
			else if ( wi->anchorBottom() )
				t = clientHeight() - wi->height() - wi->anchorBottomValue();
		}
		wi->setBounds( l, t, w, h );
	}
	wl.clear();

	pCur = NULL;
}

Rect Frame::getClientClipRect()
{

  Rect r;
	Rect cr( borderLeft(), borderTop(), width() - borderLeft() - borderRight(), height() - borderTop() - borderBottom() );

  if ( hasParent() ) {

    Rect pr = parent()->getClientClipRect( );

    r.top = absoluteYPos() + cr.top;
    r.left = absoluteXPos() + cr.left;
    r.width = cr.width;
    r.height = cr.height;

    r.crop( pr );

    return r;

  } else {

    r.top = absoluteYPos() + cr.top;
    r.left = absoluteXPos() + cr.left;
    r.width = cr.width;
    r.height = cr.height;

    return r;
  }
}



/*Rect Frame::getClientVisibleRect()
{
  Rect r;
//  if ( border() != NULL ) {
    r.top = borderTop();
    r.left = borderLeft();
    r.width = width() - r.left - borderRight();
    r.height = height() - r.top - borderBottom();
/*  } else {
    r.top = 0;
    r.left = 0;
    r.width = width();
    r.height = height();
}*/
 // return r;
//}

/*Rect Frame::getClientRect()
{
	return Rect( borderLeft(), borderTop(), width() - borderLeft() - borderRight(), height() - borderTop() - borderBottom() );
}*/

Widget* Frame::getWidgetAt( int x, int y, bool recursive )
{
	//Utils::setNotice( "getWidgetAt( " + Utils::toString(x) + ", " + Utils::toString(y) + " ) by " + name() );
	Rect r( borderLeft(), borderTop(), width() - borderLeft() - borderRight(), height() - borderTop() - borderBottom() );
	x -= r.left;
	y -= r.top;
	Widget* o;
  int i;

  for( i = 0; i < numChildren(); i++ ) {
    o = child( i );
    assert( o != NULL );

		if (( o->relativeTop() <= y ) && ( o->relativeLeft() <= x ) &&
						( o->relativeLeft()+o->width() >= x ) && ( o->relativeTop() + o->height() >= y ) )
    {
			if ( o->visible() ) {
				if ( recursive )
					return o->getWidgetAt( x - o->relativeLeft(), y - o->relativeTop() );
				else
        	return o;
			}
    }
  }
  return this;
}

int Frame::zIndex( )
{
  return Widget::zIndex();
}


int Frame::setZIndex( const int z )
{
	int index = z + 1;
	if ( z != zIndex() )
    Widget::setZIndex( z );
  for( int i = pChildList.count() - 1; i >= 0; i-- ) {
		Widget* o = pChildList.get( i );
    index += o->setZIndex( index );
  }
  return index - z;
}


void Frame::getWidgetsInRect( List<Widget*>& l, const Rect r, bool recursive )
{
  l.append( this );
  for( int i = 0; i < numChildren(); i++ ) {
    Widget* o = child( i );
		if ( recursive ) {
			if ( r.intersects( Rect( o->absoluteXPos(), o->absoluteYPos(), o->width(), o->height() ) ) ) {
        o->getWidgetsInRect( l, r );
      }
		} else {
			l.append( o );
		}
	}
}


void Frame::renderBackground( const Rect& r )
{
  if ( !visible() ) return;

  screen().pushClipRect( Rect( r.left + absoluteXPos(), r.top + absoluteYPos(), r.width, r.height ) );

  if ( drawmode() == DM_TRANSPARENT ) {
    if ( hasParent() ) {
      parent()->renderBackground( r );
    }
  }

  if ( border() != NULL ) {
		border()->render( Rect( absoluteXPos(), absoluteYPos(), width(), height() ), screen() );
  } else {
    screen().fillRect( Rect ( absoluteXPos(), absoluteYPos(), width(), height() ), Color( 200,200,200 ) );
  }
  screen().popClipRect();
}


void Frame::updated()
{
  Widget::updated();
}


void Frame::resize( int newwidth, int newheight )
{
	Widget::resize( newwidth, newheight );
	arrangeChildren();
}


void Frame::childAdded( Widget* o )
{
	onChildAdded( o );

  //cout << "* Ui::Frame::childAdded(  )" << endl;
/*  if ( o == NULL ) return;
  o->setGui( &gui() );
  if ( o->parent() != this )
    o->setParent( this );
	if ( o->isManaged() )
		arrangeChildren();*/
}

void Frame::childRemoved( Widget* o )
{
  //cout << "* Ui::Frame::childRemoved(  )" << endl;
  if ( o == NULL ) return;
	if ( o->isManaged() )
  	arrangeChildren();
}


Widget* Frame::mouseMove( int x, int y, MouseButtons mb )
{
  Widget* obj = getWidgetAt( x, y );
  if (( obj == this ) || ( obj == NULL )) {
    return Widget::mouseMove( x, y, mb );
  } else {
		Rect r( borderLeft(), borderTop(), width() - borderLeft() - borderRight(), height() - borderTop() - borderBottom() );
		return obj->mouseMove( x - obj->relativeLeft() - r.left, y - obj->relativeTop() - r.top, mb );
  }
}


Widget* Frame::mouseClick( int x, int y, MouseButtons mb )
{
  Widget* obj = getWidgetAt( x, y );
  if (( obj == this ) || ( obj == NULL )) {
    return Widget::mouseClick( x, y, mb );
  } else {
		Rect r( borderLeft(), borderTop(), width() - borderLeft() - borderRight(), height() - borderTop() - borderBottom() );
		return obj->mouseClick( x - obj->relativeLeft() - r.left, y - obj->relativeTop() - r.top, mb );
  }
}


Widget* Frame::mouseDblClick( int x, int y, MouseButtons mb )
{
  Widget* obj = getWidgetAt( x, y );
  if (( obj == this ) || ( obj == NULL )) {
    return Widget::mouseDblClick( x, y, mb );
  } else {
		Rect r( borderLeft(), borderTop(), width() - borderLeft() - borderRight(), height() - borderTop() - borderBottom() );
		return obj->mouseDblClick( x - obj->relativeLeft() - r.left, y - obj->relativeTop() - r.top, mb );
  }
}


Widget* Frame::mousePressed( int x, int y, MouseButtons mb )
{
	Widget* obj = getWidgetAt( x, y );
  if (( obj == this ) || ( obj == NULL )) {
    return Widget::mousePressed( x, y, mb );
  } else {
		Rect r( borderLeft(), borderTop(), width() - borderLeft() - borderRight(), height() - borderTop() - borderBottom() );
		return obj->mousePressed( x - obj->relativeLeft() - r.left, y - obj->relativeTop() - r.top, mb );
  }
}


Widget* Frame::mouseReleased( int x, int y, MouseButtons mb )
{
	Widget* obj = getWidgetAt( x, y );
  if (( obj == this ) || ( obj == NULL )) {
    return Widget::mouseReleased( x, y, mb );
  } else {
		Rect r( borderLeft(), borderTop(), width() - borderLeft() - borderRight(), height() - borderTop() - borderBottom() );
		return obj->mouseReleased( x - obj->relativeLeft() - r.left, y - obj->relativeTop() - r.top, mb );
  }
}


Widget* Frame::mouseIn( MouseButtons mb )
{
  return Widget::mouseIn( mb );
}


Widget* Frame::mouseOut( MouseButtons mb )
{
  return Widget::mouseOut( mb );
}


Widget* Frame::keyPressed( Key key )
{
  return Widget::keyPressed( key );
}


Widget* Frame::keyReleased( Key key )
{
  return Widget::keyReleased( key );
}


