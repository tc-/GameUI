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
Implementation of the Ui::SGui class
*/

#include "uigui.h"
#include <stdlib.h>
#include <uikey.h>
#include <uiwidget.h>

using namespace std;
using namespace Ui;


Gui::Gui( int width, int height )
{
  pWidth = width;
  pHeight = height;
  pScreen = NULL;

  pCursorObject = NULL;
  pFocusedWidget = NULL;
  pClipboard = NULL;

  pLastMouseOver = NULL;
  pMouseChannelWidget = NULL;
  pMousePressedWidget = NULL;
	pMouseDragWidget = NULL;
	pChannelPopup = NULL;

  pBgWidget = NULL;
  pFgFrame = NULL;
  pTopFrame = NULL;

  pDblClickTicks = 6;
  pLastClick = pDblClickTicks + 1;

}



Gui::~Gui()
{
  if ( pCursorObject != NULL ) {
    delete pCursorObject;
  }
  if ( pLastMouseOver != NULL )
    pLastMouseOver->onDestroy.disconnect( this );
}


Widget* Gui::bgWidget()
{
  return pBgWidget;
}


void Gui::setBgWidget( Widget* o )
{
  pBgWidget = o;
  pBgWidget->setGui( this );
  pBgWidget->setTop( 0 );
  pBgWidget->setLeft( 0 );
  pBgWidget->setWidth( pWidth );
  pBgWidget->setHeight( pHeight );
//  pBgWidget->setPreferredWidth( pWidth );
//  pBgWidget->setPreferredHeight( pHeight );
//  pBgWidget->setHSizeType( sizeFixed );
//  pBgWidget->setVSizeType( sizeFixed );

  pBgWidget->endUpdate( );

}


Frame& Gui::fgFrame()
{
  if ( pFgFrame == NULL ) {
    setFgFrame( new Frame );
  }
  return *pFgFrame;
}


void Gui::setFgFrame( Frame* f )
{
  pFgFrame = f;
  pFgFrame->setGui( this );
  pFgFrame->setTop( 0 );
  pFgFrame->setLeft( 0 );
  pFgFrame->setWidth( pWidth );
  pFgFrame->setHeight( pHeight );
//  pFgFrame->setPreferredWidth( pWidth );
//  pFgFrame->setPreferredHeight( pHeight );
//  pFgFrame->setHSizeType( sizeFixed );
//  pFgFrame->setVSizeType( sizeFixed );

  pFgFrame->setVisible( true );
}


Frame& Gui::topFrame()
{
  if ( pTopFrame == NULL ) {
    setTopFrame( new Frame );
  }
  return *pTopFrame;
}


void Gui::setTopFrame( Frame* f )
{
  pTopFrame = f;
  pFgFrame->setGui( this );
  pTopFrame->setTop( 0 );
  pTopFrame->setLeft( 0 );
  pTopFrame->setWidth( pWidth );
  pTopFrame->setHeight( pHeight );
//  pTopFrame->setPreferredWidth( pWidth );
//  pTopFrame->setPreferredHeight( pHeight );
//  pTopFrame->setHSizeType( sizeFixed );
//  pTopFrame->setVSizeType( sizeFixed );

  pFgFrame->setVisible( true );
}


void Gui::setFocusedWidget( Widget* o )
{

  if ( pFocusedWidget != o ) {

    if ( pFocusedWidget != NULL ) {
      pFocusedWidget->onDestroy.disconnect( this );
      pFocusedWidget->setFocused( false );
    }

    pFocusedWidget = o;

		KeyCursor::cursorObject().setEnabled( false );
		if ( o != NULL ) {
      o->onDestroy.connect( this, &Gui::objectDestroyed );
			KeyCursor::cursorObject().setFocusedWidget( o );
      o->setFocused( true );
    } else {
			KeyCursor::cursorObject().setFocusedWidget( NULL );
    }

  }
}


KeyCursor& Gui::keyCursorObject()
{
  if ( pCursorObject == NULL ) {
    pCursorObject = new KeyCursor;
  }
  return *pCursorObject;
}


void Gui::setKeyCursorObject( KeyCursor* cursor )
{
  pCursorObject = cursor;
}


Clipboard& Gui::clipboard()
{
  if ( pClipboard == NULL ) {
    pClipboard = new Clipboard;
  }
  return *pClipboard;
}

void Gui::setClipboard( Clipboard* c )
{
  pClipboard = c;
}


Widget* Gui::mouseChannelWidget(  ) const
{
  return pMouseChannelWidget;
}

void Gui::setMouseChannelWidget( Widget& o )
{
  cout << "* setMouseChannelWidget(  )" << endl;
  pMouseChannelWidget = &o;
  o.onDestroy.connect( this, &Gui::objectDestroyed );
}



void Gui::unsetMouseChannelWidget( Widget& o )
{
  cout << "* unsetMouseChannelWidget(  )" << endl;
  if ( &o == pMouseChannelWidget ) {
    o.onDestroy.disconnect( this );
    pMouseChannelWidget = NULL;
  }
}



ImageObject& Gui::screen(  )
{
  return *pScreen;
}



void Gui::setScreen( ImageObject* iobj )
{
  pScreen = iobj;
}

bool Gui::objectsListSortCallback( List<UpdateWidget*>& l, int i1, int i2 )
{
  if ( l.get( i1 )->o == NULL ) return false;
  if ( l.get( i2 )->o == NULL ) return true;

  if ( l.get( i1 )->o->zIndex() <= l.get( i2 )->o->zIndex() )
    return true;
  else
    return false;
}

bool objectListSortCallback( List<Widget*>& l, int i1, int i2 )
{
  if ( l.get( i1 )->zIndex() <= l.get( i2 )->zIndex() )
    return true;
  else
    return false;
}

void Gui::render(  )
{
  List<UpdateWidget*>& l = Widget::updatedWidgets();
  if ( l.count() <= 0 ) return;
  int i = l.count() - 1;
  Widget* o = NULL;
  List<Widget*> tmpL;
  l.sort( &objectsListSortCallback );
  while( i >= 0 ){

    o = l.get( i )->o;
    Rect r = l.get( i )->r;

    if ( pFgFrame != NULL )
      fgFrame().getWidgetsInRect( tmpL, r );
    if ( pTopFrame != NULL )
      topFrame().getWidgetsInRect( tmpL, r );

    tmpL.sort( &objectListSortCallback );

    int i2 = 0;
    bool skip = false;
//    int before = tmpL.count();

    while ( (i2 < tmpL.count()) && ( o != NULL ) ) {

      Widget* o2 = tmpL.get( i2 );
			Rect r2( o2->absoluteXPos(), o2->absoluteYPos(), o2->width(), o2->height() );
      if ( o2->border() != NULL ) {
        if ( o2->border()->drawmode() != DM_OPAQUE )
          r2.applyBorder( o2->border() );
      }
			if ( (r2.encloses( r )) && ( o2->drawmode() == DM_OPAQUE ) && ( o2->visible() ) ) {
        if ( o2->zIndex() > o->zIndex() ) {

          skip = true;
          break;
        } else {
          while ( i2+1 < tmpL.count() ) {

            tmpL.remove( i2+1 );
          }
          break;
        }
      }
      i2++;
    }


    if ( !skip ) {

      for( int i2 = tmpL.count() - 1; i2 >= 0; i2-- ){

        Rect r2 = Rect( tmpL.get( i2 )->absoluteXPos(),
                        tmpL.get( i2 )->absoluteYPos(),
                        tmpL.get( i2 )->width(), tmpL.get( i2 )->height() );
        r2.crop( r );

        screen().pushClipRect( r2 );
        screen().pushClipRect( tmpL.get( i2 )->getClipRect() );
        screen().setRelativePoint( tmpL.get( i2 )->absoluteXPos(), tmpL.get( i2 )->absoluteYPos() );

        tmpL.get( i2 )->renderBorder( screen() );

        screen().setRelativePoint( tmpL.get( i2 )->absoluteXPos() + tmpL.get( i2 )->borderLeft(),
                                  tmpL.get( i2 )->absoluteYPos() + tmpL.get( i2 )->borderTop() );
        Rect r3( r2.left - tmpL.get( i2 )->absoluteXPos() - tmpL.get( i2 )->borderLeft(), r2.top - tmpL.get( i2 )->absoluteYPos() - tmpL.get( i2 )->borderTop(), r2.width, r2.height );
        tmpL.get( i2 )->render( screen(), r3 );

        screen().popClipRect();
        screen().popClipRect();
        screen().setRelativePoint( 0, 0 );

      }

      for( int i = 0; i < pPopups.count(); i++ ) {
        Popup* p = pPopups.get( i );
        r.crop( p->getRect() );
        if ( r.area() > 0 ) {
          Rect r = p->getRect();
          r.crop( r );
          p->render( r );
        }
      }
    } else {

    }
    tmpL.clear();
    i--;
  }

  Widget::clearUpdatedWidgets();

}

/*
void Gui::updateRegion( const Rect& r, Widget* o )
{
  cout << "* Ui::Gui::updateRegion()" << endl;

}*/


void Gui::objectDestroyed( Widget& o )
{
  cout << "Ui::Gui::objectDestroyed(  )" << endl;
  if ( pMouseChannelWidget == &o ) {
    pMouseChannelWidget = NULL;
  }
  if ( pLastMouseOver == &o ) {
    pLastMouseOver = NULL;
  }
  if ( pMousePressedWidget == &o ) {
    pMousePressedWidget = NULL;
  }
  if ( pFocusedWidget == &o ) {
    pFocusedWidget = NULL;
  }
	if ( pMouseDragWidget == &o ) {
		pMouseDragWidget = NULL;
	}
}


void Gui::addPopup( Popup* p )
{
  assert( p != NULL );
  pPopups.append( p );
  Widget::updatedWidget( NULL, Rect( p->left(), p->top(), p->width(), p->height() ) );
}

void Gui::removePopup( Popup* p )
{
  int index = pPopups.getIndex( p );
  if ( index >= 0 ) {
    pPopups.remove( index );
		Widget::updatedWidget( NULL, Rect( p->left(), p->top(), p->width(), p->height() ) );
  }
}



void Gui::mouseMove( int x, int y, MouseButtons mb )
{
//  cout << "Ui::Gui::mouseMove(  )"  << endl;

	if ( pChannelPopup != NULL ) {
		pChannelPopup->mouseMove( x, y, mb );
		if ( pChannelPopup != NULL ) {
			if ( !pChannelPopup->passEvents() )
				return;
		}
	}

  if ( pMouseChannelWidget != NULL ) {

		Widget* o =  pMouseChannelWidget->mouseMove( x - pMouseChannelWidget->absoluteXPos(), y - pMouseChannelWidget->absoluteYPos(), mb );

    if ( pLastMouseOver != o ) {

      if ( (pLastMouseOver == pMouseChannelWidget) || (o == pMouseChannelWidget) ) {
        if ( o == pMouseChannelWidget ) {
          pMouseChannelWidget->mouseIn( mb );
        } else {
          pMouseChannelWidget->mouseOut( mb );
          pMouseChannelWidget->onDestroy.disconnect( this );
        }
      } else {
        pLastMouseOver->onDestroy.disconnect( this );
      }
      pLastMouseOver = o;
      pLastMouseOver->onDestroy.connect( this, &Gui::objectDestroyed );

    }

  } else {

    for( int i = 0; i < pPopups.count(); i++ ) {
      Popup* p = pPopups.get( i );
      Rect r = p->getRect();
      if ( r.pointInside( x, y ) ) {
        p->mouseMove( x, y, mb );
				if ( !p->passEvents() )
					return;
      }
    }

    Widget* o = fgFrame().mouseMove( x, y, mb );

    if ( o != NULL ) {
      if ( o != pLastMouseOver ) {

        if ( pLastMouseOver != NULL ) {
          pLastMouseOver->onDestroy.disconnect( this );
          pLastMouseOver->mouseOut( mb );
          pLastMouseOver = NULL;
        }

//        if ( o != &frame )
        o->mouseIn( mb );

        pLastMouseOver = o;
        pLastMouseOver->onDestroy.connect( this, &Gui::objectDestroyed );

      }
      //o->mouseMove( x, y, mb );

    } else {
      pLastMouseOver->onDestroy.disconnect( this );
      pLastMouseOver = NULL;
    }

  }
	if ( pMouseDragWidget != NULL ) {
		if ( ( Utils::max(x, pPressedX) - Utils::min(x, pPressedX) > 5 ) || ( Utils::max(y, pPressedY) - Utils::min(y, pPressedY) > 5 ) ) {
			DragObject* d = NULL;
			pMouseDragWidget->onDrag( pMouseDragWidget, x - pMouseDragWidget->absoluteXPos(), y - pMouseDragWidget->absoluteYPos(), &d );
			if ( d != NULL ) {
				pMouseDragWidget->mouseReleased( x - pMouseDragWidget->absoluteXPos(), y - pMouseDragWidget->absoluteYPos(), mb );
				d->popup( x - (d->width() / 2), y - (d->height() / 2), *this );
				if ( mouseChannelWidget() != NULL )
					unsetMouseChannelWidget( *mouseChannelWidget() );

				d->mousePressed( x, y, mb );
			}
			pMouseDragWidget->onDestroy.disconnect( this );
			pMouseDragWidget = NULL;
		}
	}
}



void Gui::mousePressed( int x, int y, MouseButtons mb )
{
	cout << "Ui::Gui::mousePressed( " << x << ", " << y << " )"  << endl;

	if ( pChannelPopup != NULL ) {
		pChannelPopup->mousePressed( x, y, mb );
		if ( pChannelPopup != NULL ) {
			if ( !pChannelPopup->passEvents() )
				return;
		}
	}

  if ( pMouseChannelWidget != NULL ) {

    if ( pMousePressedWidget != NULL ) {
      pMousePressedWidget->onDestroy.disconnect( this );
    }

    pMousePressedWidget = pMouseChannelWidget;
    pMousePressedWidget->onDestroy.connect( this, &Gui::objectDestroyed );
		pMouseChannelWidget->mousePressed( x - pMouseChannelWidget->absoluteXPos(), y - pMouseChannelWidget->absoluteYPos(), mb );

  } else {

    for ( int i = 0; i < pPopups.count(); i++ ) {
      Popup* p = pPopups.get( i );
      Rect r = p->getRect();
      if ( r.pointInside( x, y ) ) {
        p->mousePressed( x, y, mb );
				if ( !p->passEvents() )
					return;
      }
    }
		Widget* o = fgFrame().mousePressed( x, y, mb);

    setFocusedWidget( o );

    if ( ( o != NULL ) ) {

      if ( pMousePressedWidget != NULL ) {
        pMousePressedWidget->onDestroy.disconnect( this );
      }

			if ( pMouseDragWidget != NULL ) {
				pMouseDragWidget->onDestroy.disconnect( this );
			}

      pMousePressedWidget = o;
      pMousePressedWidget->onDestroy.connect( this, &Gui::objectDestroyed );
			pMouseDragWidget = o;
			pMouseDragWidget->onDestroy.connect( this, &Gui::objectDestroyed );

		} else {
			if ( pMouseDragWidget != NULL ) {
				pMouseDragWidget->onDestroy.disconnect( this );
				pMouseDragWidget = NULL;
			}
		}
  }
	pPressedX = x;
	pPressedY = y;
}



void Gui::mouseReleased( int x, int y, MouseButtons mb )
{
  cout << "Ui::Gui::mouseReleased( " << x << ", " << y << " )"  << endl;

	if ( pChannelPopup != NULL ) {
		pChannelPopup->mouseReleased( x, y, mb );
		if ( pChannelPopup != NULL ) {
			if ( !pChannelPopup->passEvents() )
				return;
		}
	}

	if ( pMouseDragWidget != NULL ) {
		pMouseDragWidget->onDestroy.disconnect( this );
		pMouseDragWidget = NULL;
	}

  if ( pMouseChannelWidget != NULL ) {


    if ( pMousePressedWidget == pMouseChannelWidget ) {
      if ( pLastClick <= pDblClickTicks ) {
        pMouseChannelWidget->mouseDblClick( x - pMouseChannelWidget->absoluteXPos(), y - pMouseChannelWidget->absoluteYPos(), mb );
				pMouseChannelWidget->mouseClick( x - pMouseChannelWidget->absoluteXPos(), y - pMouseChannelWidget->absoluteYPos(), mb );
				pLastClick = pDblClickTicks + 1;
      } else {
        pMouseChannelWidget->mouseClick( x - pMouseChannelWidget->absoluteXPos(), y - pMouseChannelWidget->absoluteYPos(), mb );
        pLastClick = 0;
      }
      pMousePressedWidget->onDestroy.disconnect( this );
      pMousePressedWidget = NULL;
    }
    pMouseChannelWidget->mouseReleased( x - pMouseChannelWidget->absoluteXPos(), y - pMouseChannelWidget->absoluteYPos(), mb );

  } else {

    for( int i = 0; i < pPopups.count(); i++ ) {
      Popup* p = pPopups.get( i );
      Rect r = p->getRect();
      if ( r.pointInside( x, y ) ) {
        p->mouseReleased( x, y, mb );
				if ( !p->passEvents() )
        	return;
      }
    }

    Widget* o = fgFrame().mouseReleased( x, y, mb );
    if ( o != NULL ) {
      if ( pMousePressedWidget == o ) {
        pMousePressedWidget->onDestroy.disconnect( this );
        pMousePressedWidget = NULL;
        o->mouseClick( x, y, mb );
      }
      //o->mouseReleased( x, y, mb );
    }
  }
}


void Gui::keyPressed( Key k )
{
  cout << "* Ui::Gui::keyPressed()" << endl;
  if ( pFocusedWidget != NULL ) {
    pFocusedWidget->keyPressed( k );
  }
}

void Gui::keyReleased( Key k )
{
  cout << "* Ui::Gui::keyReleased()" << endl;
  if ( pFocusedWidget != NULL ) {
    pFocusedWidget->keyReleased( k );
  }
}


void Gui::timerTick(  )
{
  onTimerTick();

  pLastClick++;
	/*
  if ( pCursorObject != NULL ) {
    pCursorObject->timerTick();
	}*/
}
