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

/**
@file
Implementation of the Ui::Widget class
*/

#include "uiwidget.h"
#include "uiframe.h"
#include "uigui.h"
#include "uiborder.h"
#include "uimouse.h"
#include <uidragobject.h>
#include <uitooltip.h>
#include <uitimer.h>
#include <uilineborder.h>


#include "limits.h"
#include <stdlib.h>

using namespace std;
//using namespace Ui;

namespace Ui {


Widget::Widget( Frame* parent )
{
  //cout << "* Widget::Widget( Frame* )" << endl;

  pGui = NULL;
  setParent( parent );

  pTag = NULL;
  pFont = NULL;
  pBorder = NULL;
	pCursor = NULL;

	pToolTipTimer = NULL;
	pToolTipObject = NULL;

	pTheme = NULL;
	pThemePrefix = "";

//  pHSizeType = sizePreferred;
//  pVSizeType = sizePreferred;

//  pPreferredWidth = 100;
//  pPreferredHeight = 80;

	pAlign = walignNone;
	pAnchorL = false;
	pAnchorR = false;
	pAnchorT = false;
	pAnchorB = false;

  pMinWidth = 0;
  pMinHeight = 0;
  pMaxWidth = INT_MAX;
  pMaxHeight = INT_MAX;
  pTop = 0;
  pLeft = 0;
  pWidth = 100;
  pHeight = 100;
  pZIndex = 0;

  pVisible = true;
  pEnabled = true;
  pFocused = false;

  pDrawmode = DM_OPAQUE;

  pToolTip = L"";

  pDontRender = 0;
  pIsUpdated = false;
	pToldParentUpdate = false;

  pBgColor = Color( 128, 128, 128 );
  pFontColor = Color( 0, 0, 0 );
}

Widget::Widget( Frame* parent, int x, int y, int width, int height )
{
  //cout << "* Widget::Widget( Frame* )" << endl;

  pGui = NULL;
  setParent( parent );

  pTag = NULL;
  pFont = NULL;
  pBorder = NULL;
	pCursor = NULL;

	pToolTipTimer = NULL;
	pToolTipObject = NULL;

	pTheme = NULL;
	pThemePrefix = "";

//  pHSizeType = sizePreferred;
//  pVSizeType = sizePreferred;

//  pPreferredWidth = 100;
//  pPreferredHeight = 80;

	pAlign = walignNone;
	pAnchorL = false;
	pAnchorR = false;
	pAnchorT = false;
	pAnchorB = false;

  pMinWidth = 0;
  pMinHeight = 0;
  pMaxWidth = INT_MAX;
  pMaxHeight = INT_MAX;
  pTop = y;
  pLeft = x;
  pWidth = width;
  pHeight = height;
  pZIndex = 0;

  pVisible = true;
  pEnabled = true;
  pFocused = false;

  pDrawmode = DM_OPAQUE;

  pToolTip = L"";

  pDontRender = 0;
  pIsUpdated = false;
	pToldParentUpdate = false;

  pBgColor = Color( 128, 128, 128 );
  pFontColor = Color( 0, 0, 0 );
}

Widget::~Widget(  )
{
  //cout << "* ~Ui::Widget" << endl;

  if ( pParent != NULL )
    pParent->removeChild( this );

  onDestroy( *this );

//  if ( screen() != NULL )
//    screen()->objectDestroyed( *this );
}


void Widget::setTheme( Theme& t, const string prefix )
{
	if ( pTheme != &t ) {
		if ( pTheme != NULL )
			pTheme->onUpdated.disconnect( this );
		t.onUpdated.connect( this, &Widget::themeUpdated );
	}

	pTheme = &t;
	pThemePrefix = prefix;

  setBorder( t.getBorder( "default" ) );
  setFont( t.getFont( "default" ) );
	setCursor( t.getCursor( "default" ) );
}

void Widget::themeUpdated( Theme & t )
{
	if ( &t == pTheme ) {
		setTheme( *pTheme, pThemePrefix );
	}
}

void Widget::setAnchorLeft( const bool& a )
{
	pAnchorL = a;
	if ( isManaged() )
		pAnchorLV = relativeLeft();
	else
		pAnchorLV = 0;
}

void Widget::setAnchorRight( const bool& a )
{
	pAnchorR = a;
	if ( isManaged() )
		pAnchorRV = parent()->clientWidth() - relativeLeft() - width();
	else
		pAnchorRV = 0;
}

void Widget::setAnchorTop( const bool& a )
{
	pAnchorT = a;
	if ( isManaged() )
		pAnchorTV = relativeTop();
	else
		pAnchorTV = 0;
}

void Widget::setAnchorBottom( const bool& a )
{
	pAnchorB = a;
	if ( isManaged() )
		pAnchorBV = parent()->clientHeight() - relativeTop() - height();
	else
		pAnchorBV = 0;
}


void Widget::setAnchors( const bool& l, const bool& r, const bool& t, const bool& b )
{
	setAnchorLeft( l );
	setAnchorRight( r );
	setAnchorTop( t );
	setAnchorBottom( b );
}


MouseCursor* Widget::cursor() const
{
	return pCursor;
}

void Widget::setCursor( MouseCursor* mc )
{
	pCursor = mc;
}


void Widget::setParent( Frame* p )
{
  //cout << "* Ui::Widget::setParent(  )" << endl;
  pParent = p;
  if ( pParent != NULL ) {
    pParent->addChild( *this );
  }
//  cout << "* Ui::Widget::setParent(  ) done" << endl;
}


void Widget::sizeChanged( const Rect& news )
{
	if ( pDontRender > 0 )
		return;
	if ( isManaged() ) {
		if ( pToldParentUpdate ) return;
		pToldParentUpdate = true;
		parent()->childUpdated( *this );
		pToldParentUpdate = false;
	}
	else
		updated( news );
}


void Widget::updated(  )
{
//  cout << "* Ui::Widget::updated(  )" << endl;
  if ( pDontRender > 0 ) {
    pIsUpdated = true;
    return;
  }

//  if ( isManaged() ) {
//    pParent->childUpdated( *this );
//  }
  Widget::updatedWidget( this );
}

void Widget::updated( const Rect& r )
{
  if ( pDontRender > 0 ) {
    pIsUpdated = true;
    return;
  }

//  if ( isManaged() ) {
//    pParent->childUpdated( *this );
//  }
  Widget::updatedWidget( this, r );
}



void Widget::beginUpdate(  )
{
  pDontRender++;
}



void Widget::endUpdate( bool dontupdate )
{
  assert( pDontRender != 0 );
  pDontRender--;
  if (( pDontRender == 0 ) && ( pIsUpdated )) {
    pIsUpdated = false;
    if ( !dontupdate )
      updated();
  }
}




ImageObject& Widget::screen(  )
{
  return gui().screen();
}


void Widget::setMinWidth( int mw )
{
  pMinWidth = mw;
  updated();
}

void Widget::setMinHeight( int mh )
{
  pMinHeight = mh;
  updated();
}

void Widget::setMaxWidth( int mw )
{
  pMaxWidth = mw;
  updated();
}

void Widget::setMaxHeight( int mh )
{
  pMaxHeight = mh;
  updated();
}


int Widget::top( ) const
{
//	cout << " -- top()"<< endl;
	return pTop;
}


int Widget::left( ) const
{
//	cout << " -- left()"<< endl;
	return pLeft;
}


int Widget::relativeTop(  ) const
{
	if ( hasParent() ) {
		return pTop - parent()->scrollY();
	} else {
		return pTop;
	}
}

int Widget::relativeLeft(  ) const
{
	if ( hasParent() ) {
		return pLeft - parent()->scrollX();
	} else {
		return pLeft;
	}
}


void Widget::setTop( int t )
{
	move( left(), t );
//  pTop = t;
//  updated();
}

void Widget::setLeft( int l )
{
	move( l, top() );
//  pLeft = l;
//  updated();
}

void Widget::setWidth( int w )
{
  resize( w, height() );
//  updated();
}

void Widget::setHeight( int h )
{
  resize( width(), h );
  //updated();
}

Drawmode Widget::drawmode(  ) const
{
  return pDrawmode;
}

void Widget::setDrawmode( Drawmode dm )
{
  pDrawmode = dm;
  updated();
}

int Widget::absoluteXPos( ) const
{
  if ( hasParent() ) {
		return ( parent()->absoluteXPos() + parent()->borderLeft() + relativeLeft() );
  } else {
		return relativeLeft();
  }
}



int Widget::absoluteYPos( ) const
{
  if ( hasParent() ) {
		return ( parent()->absoluteYPos() + parent()->borderTop() + relativeTop() );
  } else {
		return relativeTop();
  }
}


/*Rect Widget::getWidgetRect(  ) const
{
	return Rect( absoluteXPos(), absoluteYPos(), width(), height() );
}
*/


Rect Widget::getClipRect(  ) const
{
  Rect r;
  if ( hasParent() ) {
    Rect pr = parent()->getClientClipRect( );

    r.top = absoluteYPos();
    r.left = absoluteXPos();
    r.width = width();
    r.height = height();

    r.crop( pr );

   return r;

  } else {

    r.top = absoluteYPos();
    r.left = absoluteXPos();
    r.width = pWidth;
    r.height = pHeight;

    return r;

  }
}


int Widget::borderTop( ) const
{
  if ( border() != NULL ) {
    return border()->heightTop;
  }
  return 0;
}


int Widget::borderLeft( ) const
{
  if ( border() != NULL ) {
    return border()->widthLeft;
  }
  return 0;
}

int Widget::borderBottom( ) const
{
  if ( border() != NULL ) {
    return border()->heightBottom;
  }
  return 0;
}

int Widget::borderRight( ) const
{
  if ( border() != NULL ) {
    return border()->widthRight;
  }
  return 0;
}


int Widget::clientWidth()
{
	return width() - borderLeft() - borderRight();
}

int Widget::clientHeight()
{
	return height() - borderTop() - borderBottom();
}

int Widget::clientVisibleWidth( )
{
	return width() - borderLeft() - borderRight();
}

int Widget::clientVisibleHeight( )
{
	return height() - borderTop() - borderBottom();
}

Gui& Widget::gui(  ) const
{
  if ( (pGui == NULL) && ( hasParent() ) ) {
    return parent()->gui();
  }
  assert( pGui != NULL );
  return *pGui;
}

void Widget::setGui( Gui* s )
{
  pGui = s;
  updated();
}


bool Widget::visible(  ) const
{
  if ( pVisible ) {
    if ( hasParent() )
      return parent()->visible();
    else
      return true;
  } else {
    return false;
  }
}


void Widget::setVisible( bool v )
{
  pVisible = v;
	if ( hasParent() )
		parent()->childUpdated( *this );
	updatedWidget( NULL, Rect( relativeLeft() - borderLeft(), relativeTop() - borderTop(), width() + borderLeft(), height() + borderTop() ) );
}

void Widget::setEnabled( bool e )
{
  pEnabled = e;
  updated();
}


void Widget::setFont( Font* f )
{
  pFont = f;
  updated();
}

void Widget::setBorder( Border* bs )
{
  pBorder = bs;
  updated();
}

void Widget::setFocused( bool f )
{
  if (( pFocused != f ) && ( f ) ) {
    gui().setFocusedWidget( this );
  }
  pFocused = f;
  updated();
}



void Widget::render( ImageObject& img, const Rect& r )
{
}


void Widget::renderBorder( ImageObject& img )
{
	if ( !visible() ) return;
  if ( border() != NULL ) {
    border()->render( Rect( 0, 0, width(), height() ), img );
  } else {
    if ( drawmode() == DM_OPAQUE )
      img.fillRect( Rect( 0, 0, width(), height() ), bgColor() );
  }
}


void Widget::move( const int newleft, const int newtop )
{
  if ( visible() ) {
    Rect updateRect( absoluteXPos(), absoluteYPos(), width(), height() );

    Rect tmpRect = updateRect;

    tmpRect.top = newtop;
    tmpRect.left = newleft;

		pTop = newtop;
		pLeft = newleft;


    updateRect.merge( tmpRect );

    updateRect.top -= absoluteYPos() + borderTop();
    updateRect.left -= absoluteXPos() + borderLeft();

    updated( updateRect );

	} else {
		pTop = newtop;
		pLeft = newleft;
	}
}


void Widget::setSizeLimit( int minw, int minh, int maxw, int maxh )
{
  pMinWidth = minw;
  pMinHeight = minh;
  pMaxWidth = maxw;
  pMaxHeight = maxh;
  updated();
}



void Widget::setBounds( int left, int top, int width, int height )
{
	move( left, top );
  resize( width, height );
}


bool Widget::isManaged(  ) const
{
  if ( hasParent() ) {
		return ( (pAlign != walignNone) || (pAnchorL) || (pAnchorR) || (pAnchorT) || (pAnchorB) );
  } else {
    return false;
  }
}

void Widget::tooltipTimerCallback( Timer& t, int& to )
{
	// Tooltip Should Now Be Shown.
	t.setEnabled( false );
	static Tooltip stobj;
	Tooltip* tobj = &stobj;
	tobj->setTheme( Theme::defaultTheme() );
	tobj->setText( pToolTip );

	if ( tobj->border() == NULL ) {
		static LineBorder lb;
		tobj->setBorder( &lb );
	}

	onTooltip( this, pLastX, pLastY, &tobj );

	if ( tobj != NULL ) {
		pToolTipObject = tobj;
		tobj->popup( pLastX + this->absoluteXPos() + 1, pLastY + this->absoluteYPos() + 20, gui() );
	}
}

Widget* Widget::mouseMove( int x, int y, MouseButtons mb )
{
	onMouseMove( *this, x, y, mb );
	if ( pToolTip != L"" ) {
		if ( pToolTipTimer == NULL ) {
			pToolTipTimer = new Timer;
			pToolTipTimer->onTimer.connect( this, &Widget::tooltipTimerCallback );
			pToolTipTimer->setTimeout( 1000 );
			pToolTipTimer->setEnabled( true );
		} else {
			pToolTipTimer->reset();
		}
	}
	pLastX = x;
	pLastY = y;
  return this;
}


Widget* Widget::mouseClick( int x, int y, MouseButtons mb )
{
	Utils::setNotice( "onMouseClick( " + Utils::toString(x) +  ", " + Utils::toString(y) + ", " + Utils::toString(mb) + " ) by '" + name() + "'" );
	onMouseClick( *this );
  return this;
}


Widget* Widget::mouseDblClick( int x, int y, MouseButtons mb )
{
	Utils::setNotice( "onMouseDblClick( " + Utils::toString(x) +  ", " + Utils::toString(y) + ", " + Utils::toString(mb) + " ) by '" + name() + "'" );
	onMouseDblClick( *this );
  return this;
}


Widget* Widget::mousePressed( int x, int y, MouseButtons mb )
{
	Utils::setNotice( "onMousePressed( " + Utils::toString(x) +  ", " + Utils::toString(y) + ", " + Utils::toString(mb) + " ) by '" + name() + "'" );
  onMousePressed( *this, mb );
	if ( pToolTipTimer != NULL ) {
		delete pToolTipTimer;
		pToolTipTimer = NULL;
	}
	if ( pToolTipObject != NULL ) {
		pToolTipObject->close();
	}
  return this;
}


Widget* Widget::mouseReleased( int x, int y, MouseButtons mb )
{
	Utils::setNotice( "onMouseReleased( " + Utils::toString(x) +  ", " + Utils::toString(y) + ", " + Utils::toString(mb) + " ) by '" + name() + "'" );
	onMouseReleased( *this, mb );
	if ( pToolTipTimer != NULL ) {
		delete pToolTipTimer;
		pToolTipTimer = NULL;
	}
	if ( pToolTipObject != NULL ) {
		pToolTipObject->close();
	}
  return this;
}


Widget* Widget::mouseIn( MouseButtons mb )
{
	Utils::setNotice( "onMouseIn( " + Utils::toString(mb) + " ) by '" + name() + "'" );
  onMouseIn( *this );
  return this;
}


Widget* Widget::mouseOut( MouseButtons mb )
{
	Utils::setNotice( "onMouseOut( " + Utils::toString(mb) + " ) by '" + name() + "'" );
	onMouseOut( *this );
	if ( pToolTipTimer != NULL ) {
		delete pToolTipTimer;
		pToolTipTimer = NULL;
	}
	if ( pToolTipObject != NULL ) {
		pToolTipObject->close();
	}
  return this;
}


Widget* Widget::keyPressed( Key key )
{
  onKeyPressed( *this, key );
  return this;
}

Widget* Widget::keyReleased( Key key )
{
  onKeyReleased( *this, key );
  return this;
}


void Widget::timerTick()
{
}


void Widget::resize( int newwidth, int newheight )
{
  int oldw = pWidth;
  int oldh = pHeight;
	newwidth = min( max( newwidth, minWidth() ), maxWidth() );
	newheight = min( max( newheight, minHeight() ), maxHeight() );
	pWidth = newwidth;
  pHeight = newheight;
  if ( ( oldw > pWidth ) || ( oldh > pHeight ) ) {
		sizeChanged( Rect( 0 - borderLeft(), 0 - borderTop(), oldw, oldh ) );
  } else {
		sizeChanged( Rect( 0 - borderLeft(), 0 - borderTop(), width(), height()) );
  }
}


int Widget::zIndex()
{
  return pZIndex;
}


int Widget::setZIndex( const int z )
{
  if ( pZIndex == z ) return 1;
  pZIndex = z;
  return 1;
}

void Widget::getWidgetsInRect( List<Widget*>& l, const Rect r, bool recursive )
{
  l.append( this );
}

void Widget::moveToTop()
{
  if ( parent() != NULL ) {
    parent()->moveWidgetToTop( this );
  }
}


void Widget::moveToBottom()
{
  if ( parent() != NULL ) {
    parent()->moveWidgetToBottom( this );
  }
}



void Widget::grabMouseInput()
{
  gui().setMouseChannelWidget( *this );
}



void Widget::releaseMouseInput()
{
  gui().unsetMouseChannelWidget( *this );
}
/*
void Widget::updatedWidget( Widget* o )
{
  if ( o == NULL ) return;
	Rect r = Rect( 0 - o->borderLeft(), 0 - o->borderTop(), o->width(), o->height() );
	updatedWidget( o, r );
}
*/

void Widget::updatedWidget( Widget* o, const Rect r )
{
	Rect r2 = r;
	if ( r2 == NULL_RECT ) {
		if ( o != NULL )
			r2 = o->getClipRect();
		if ( r2.area() == 0 ) return;
	} else {
  	if ( r2.area() == 0 ) return;
  	if ( o != NULL ) {
			if ( !o->visible() ) return;
			r2.top += o->absoluteYPos() + o->borderTop();
			r2.left += o->absoluteXPos() + o->borderLeft();
  	}
	}
  for( int i = 0; i < updatedWidgets().count(); i++ ) {
    if ( updatedWidgets().get( i )->o == o ) {
      updatedWidgets().get( i )->r.merge( r2 );
      return;
    }
  }
  UpdateWidget* ud = new UpdateWidget( o, r2 );
  updatedWidgets().append( ud );
}

void Widget::clearUpdatedWidgets()
{
  for( int i = 0; i < updatedWidgets().count(); i++ ) {
    delete updatedWidgets().get(i);
  }
  updatedWidgets().clear();
}

}
