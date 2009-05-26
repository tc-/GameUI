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


#include "uidropdownlist.h"

namespace Ui {

DropdownList::DropdownList()
{
  pSelected = NULL;
}


DropdownList::~DropdownList()
{
  for ( int i = 0; i < pChildren.count(); i++) {
    pChildren.get( i )->setParent( NULL );
  }
}

void DropdownList::setTheme( Theme & t, const string prefix )
{
  setBorder( t.getBorder( prefix+"dropdownlist" ) );
}


void DropdownList::addItem( DropListItem* item )
{
  if ( item == NULL ) return;
  pChildren.append( item );
  item->setParent( this );
  updated();
}

void DropdownList::setSelectedItem( DropListItem* item )
{
  beginUpdate();
  if ( pSelected != NULL ) {
    pSelected->setSelected( false );
  }
  pSelected = item;
  if ( pSelected != NULL ) {
    pSelected->setSelected( true );
  }
	updated();
  endUpdate();
}


void DropdownList::mouseMove(int x, int y, MouseButtons mb)
{
	x -= left();
	y -= top();
  int h = 0;
  if ( border() != NULL ) {
    h += border()->heightTop;
  }
  for( int i = 0; i < pChildren.count(); i++ ) {
    DropListItem* c = pChildren.get( i );
    if ( (y > h) && ( y < h+c->height() ) ) {
      setSelectedItem( c );
//			updated();
      break;
    }
    h += c->height();
  }
}

void DropdownList::mousePressed(int x, int y, MouseButtons mb)
{
  return;
}

void DropdownList::mouseReleased(int x, int y, MouseButtons mb)
{
  if ( pSelected != NULL )
    onItemClicked( *this, *pSelected );
  close();
}

void DropdownList::popup( const int x, const int y, Gui& gui )
{
  beginUpdate();
  setHeight( 4 );
  if ( border() != NULL )
    setHeight( border()->heightTop + border()->heightBottom );
  for( int i = 0; i < pChildren.count(); i++ ) {
    setHeight( height() + pChildren.get( i )->height() );
  }
  endUpdate( false );
  Popup::popup( x, y, gui );
}


void DropdownList::render(Rect area)
{
  if ( gui() == NULL ) return;
  if ( !active() ) return;
  gui()->screen().pushClipRect( area );
  if ( border() != NULL ) {
		border()->render( Rect( left(), top(), width(), height() ), gui()->screen() );
  }
	int x = left();
	int y = top();
  int w = width();
  if ( border() != NULL ) {
    y += border()->heightTop;
    x += border()->widthLeft;
    w -= border()->widthLeft + border()->widthRight;
  }
  for( int i = 0; i < pChildren.count(); i++ ) {
    DropListItem* dl = pChildren.get( i );

    gui()->screen().pushClipRect( Rect( x, y, w, dl->height()) );
    dl->render( x, y, w );
    gui()->screen().popClipRect();

    y += dl->height();
  }
  gui()->screen().popClipRect();
}

}
