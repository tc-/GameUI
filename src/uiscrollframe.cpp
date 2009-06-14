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


#include "uiscrollframe.h"

namespace Ui {

ScrollFrame::ScrollFrame( Frame* parent )
 : Frame( parent )
{
  pScrollX = 0;
  pScrollY = 0;
  pVScroll = NULL;
  pHScroll = NULL;

	pClientCasheValid = false;
	pClientWidthCashe = 0;
	pClientHeightCashe = 0;

}


ScrollFrame::~ScrollFrame()
{
  if ( pVScroll != NULL )
    pVScroll->onScroll.disconnect( this );
	if ( pHScroll != NULL )
		pHScroll->onScroll.disconnect( this );
}

void ScrollFrame::setTheme( Theme& t, const string prefix )
{
	Widget::setTheme( t, prefix );
	setFont( t.getFont( prefix+"scrollframe" ) );
	setFontColor( t.getColor( prefix+"scrollframe" ) );
	setBorder( t.getBorder( prefix+"scrollframe" ) );
	setBgColor( t.getColor( prefix+"scrollframe" ) );
}

VScrollbar* ScrollFrame::vScroll() const
{
  return pVScroll;
}

void ScrollFrame::setVScroll( VScrollbar* sb )
{
	if ( pVScroll != NULL ) {
    pVScroll->onScroll.disconnect( this );
		pVScroll->onDestroy.disconnect( this );
	}
	pVScroll = sb;
  if ( sb != NULL ) {
    sb->setGui( &gui() );
		if  ( sb->parent() != this )
			sb->setParent( this );
		updateScrollbars();
		sb->setVisible( true );
    sb->onScroll.connect( this, &ScrollFrame::onScrolled );
		sb->onDestroy.connect( this, &ScrollFrame::scrollDestroyed );
	}
	updateScrollbars();
}

HScrollbar* ScrollFrame::hScroll() const
{
  return pHScroll;
}

void ScrollFrame::setHScroll( HScrollbar* sb )
{
	if ( pHScroll != NULL ) {
		pHScroll->onScroll.disconnect( this );
		pHScroll->onDestroy.disconnect( this );
	}
	pHScroll = sb;
	if ( sb != NULL ) {
		sb->setGui( &gui() );
		if  ( sb->parent() != this )
			sb->setParent( this );
		updateScrollbars();
		sb->setVisible( true );
		sb->onScroll.connect( this, &ScrollFrame::onScrolled );
		sb->onDestroy.connect( this, &ScrollFrame::scrollDestroyed );
	}
	updateScrollbars();
}

/*Rect ScrollFrame::getClientVisibleRect()
{
	return Rect ( borderLeft(), borderTop(), width() - borderLeft() - borderRight(), height() - borderTop() - borderBottom() );
}*/

Rect ScrollFrame::getClientRect()
{
	if ( pClientCasheValid ) {
		return Rect( 0, 0, pClientWidthCashe, pClientHeightCashe );
	}
	int mw = 0;
	int mh = 0;
	for( int i = 0; i < numChildren(); i++ ) {
		Widget* w = child( i );
		if ( ( w != NULL ) && ( w != pVScroll ) && ( w != pHScroll ) ) {
			if ( mw < w->relativeLeft() + w->width() )
				mw = w->relativeLeft() + w->width();
			if ( mh < w->relativeTop() + w->height() )
				mh = w->relativeTop() + w->height();
		}
	}
	mw += scrollX();
	mh += scrollY();
//	cout << " -- MW: " << mw << " MH: " << mh << endl;

	pClientHeightCashe = mh;
	pClientWidthCashe = mw;
	pClientCasheValid = true;

  return Rect( 0, 0, mw, mh );
 // return getClientVisibleRect();
}

int ScrollFrame::clientWidth()
{
	if ( pClientCasheValid ) {
		return pClientWidthCashe;
	}
	return getClientRect().width;
}

int ScrollFrame::clientHeight()
{
	if ( pClientCasheValid ) {
		return pClientHeightCashe;
	}
	return getClientRect().height;
}


void ScrollFrame::render( ImageObject& img, const Rect& r )
{
  if ( visible() != true ) return;
	Frame::render( img, r );
}


void ScrollFrame::resize( int newwidth, int newheight )
{
	Frame::resize( newwidth, newheight );
	updateScrollbars();
}

void ScrollFrame::setPosition( const Position& pos )
{
	Frame::setPosition( pos );
	updateScrollbars();
}


void ScrollFrame::scroll( const int dx, const int dy )
{
}


void ScrollFrame::scrollTo( const int top, const int left )
{
}


void ScrollFrame::onScrolled( Widget* obj, int old )
{
  if ( obj == pVScroll ) {
		if ( pScrollY != pVScroll->scrollerPos() ) {
			setScrollY( pVScroll->scrollerPos() );
			updateScrollbars( true );
    	updated();
		}
  }
	if ( obj == pHScroll ) {
		if ( pScrollX != pHScroll->scrollerPos() ) {
			setScrollX( pHScroll->scrollerPos() );
			updateScrollbars( true );
			updated();
		}
	}
}


void ScrollFrame::scrollDestroyed( Widget& obj )
{
	if ( &obj == pVScroll ) {
		pVScroll = NULL;
		updated();
	}
	if ( &obj == pHScroll ) {
		pHScroll = NULL;
		updated();
	}
}


Widget* ScrollFrame::mouseMove( int x, int y, MouseButtons mb )
{
  return Frame::mouseMove( x, y, mb );
}


Widget* ScrollFrame::mousePressed( int x, int y, MouseButtons mb )
{
  return Frame::mousePressed( x, y, mb );
}


Widget* ScrollFrame::mouseReleased( int x, int y, MouseButtons mb )
{
  return Frame::mouseReleased( x, y, mb );
}


void ScrollFrame::childUpdated( Widget& o )
{
	Frame::childUpdated( o );
	if (( &o != pHScroll ) && ( &o != pVScroll )) {
		pClientCasheValid = false;
	}
}

void ScrollFrame::childAdded( Widget* o )
{
	Frame::childAdded( o );
	if (( o != pHScroll ) && ( o != pVScroll )) {
		pClientCasheValid = false;
	}
}

void ScrollFrame::childRemoved( Widget* o )
{
	Frame::childRemoved( o );
	if (( o != pHScroll ) && ( o != pVScroll )) {
		pClientCasheValid = false;
	}
}


void ScrollFrame::updateScrollbars( bool onlyBounds )
{
	//Rect cr = getClientRect();
	if ( !onlyBounds ) {
		if ( pVScroll != NULL ) {
			pVScroll->beginUpdate();
			if ( pHScroll != NULL )
				pVScroll->setScrollerMaxPos( Utils::max( 0, clientHeight() + pHScroll->height() ) );
			else
				pVScroll->setScrollerMaxPos( Utils::max( 0, clientHeight() ) );
			pVScroll->setScrollerPos( pScrollY );
			pVScroll->setPageSize( clientVisibleHeight() );
			pVScroll->endUpdate( true );
		}
		if ( pHScroll != NULL ) {
			pHScroll->beginUpdate();
			if ( pVScroll != NULL )
				pHScroll->setScrollerMaxPos( Utils::max( 0, clientWidth() + pVScroll->width() ) );
			else
				pHScroll->setScrollerMaxPos( Utils::max( 0, clientWidth() ) );
			pHScroll->setScrollerPos( pScrollX );
			pHScroll->setPageSize( clientVisibleWidth() );
			pHScroll->endUpdate( true );
		}
	}
	if ( ( pVScroll != NULL ) && ( pHScroll != NULL ) ) {
		pVScroll->beginUpdate();
		pVScroll->setBounds( scrollX() + clientVisibleWidth() - pVScroll->width(), scrollY(), pVScroll->width(), clientVisibleHeight() - pHScroll->height() );
		pVScroll->moveToTop();
		pVScroll->endUpdate( true );
		pHScroll->beginUpdate();
		pHScroll->setBounds( scrollX(), scrollY() + clientVisibleHeight() - pHScroll->height(), clientVisibleWidth() - pVScroll->width(), pHScroll->height() );
		pHScroll->moveToTop();
		pHScroll->endUpdate( true );
	} else if ( pVScroll != NULL ) {
		pVScroll->beginUpdate();
		pVScroll->setBounds( scrollX() + clientVisibleWidth() - pVScroll->width(), scrollY(), pVScroll->width(), clientVisibleHeight() );
		pVScroll->moveToTop();
		pVScroll->endUpdate( true );
	} else if ( pHScroll != NULL ) {
		pHScroll->beginUpdate();
		pHScroll->setBounds( scrollX(), scrollY() + clientVisibleHeight() - pHScroll->height(), clientVisibleWidth() - pVScroll->width(), pHScroll->height() );
		pHScroll->moveToTop();
		pHScroll->endUpdate( true );
	}
}

}
