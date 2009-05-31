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


#include "uicombobox.h"

namespace Ui {

Combobox::Combobox( Frame* p )
{
  pButtonGlyph = NULL;
  pButtonBorder = NULL;
  pButtonPressedBorder = NULL;

	pButtonCursor = NULL;

  pButtonPressed = false;

  pDropDown = NULL;

  setParent( p );
  setHeight( 22 );
}


Combobox::~Combobox()
{
  if ( pDropDown != NULL ) {
    if ( pDropDown->active() ) {
      pDropDown->close();
    }
    pDropDown->onClose.disconnect( this );
    pDropDown->onItemClicked.disconnect( this );
  }
 // setDropdownList( NULL );
}

void Combobox::setTheme( Theme & t, const string prefix )
{
	Widget::setTheme( t, prefix );
  setBorder( t.getBorder( prefix+"combobox" ) );
  setButtonBorder( t.getBorder( prefix+"combobox_button" ) );
  setButtonPressedBorder( t.getBorder( prefix+"combobox_button_pressed" ) );
  setButtonGlyph( t.getImage( prefix+"combobox_button" ) );
  setFont( t.getFont( prefix+"combobox" ) );
  setFontColor( t.getColor( prefix+"combobox_font" ) );
  if ( pDropDown != NULL ) {
    Border* b = t.getBorder( prefix+"combobox_dropdown" );
    if ( b == NULL )
			pDropDown->setTheme( t, prefix );
		else
    	pDropDown->setBorder( b );
  }
	setCursor( t.getCursor( prefix+"combobox" ) );
	setButtonCursor( t.getCursor( prefix+"combobox_button" ) );
}


void Combobox::setDropdownList( DropdownList* dd )
{
  if ( pDropDown != NULL ) {
    pDropDown->onClose.disconnect( this );
    pDropDown->onItemClicked.disconnect( this );
		pDropDown->onDestroy.disconnect( this );
  }

  pDropDown = dd;
  if ( pDropDown != NULL ) {
    pDropDown->onClose.connect( this, &Combobox::onDropdownClose );
    pDropDown->onItemClicked.connect( this, &Combobox::onItemClicked );
		pDropDown->onDestroy.connect( this, &Combobox::onDropdownDestroy );
  }

  updated();
}

void Combobox::setFocused( bool f )
{
  Edit::setFocused( f );
  if ( !f ) {
    if ( pDropDown != NULL ) {
      if ( pDropDown->active() )
        pDropDown->close();
    }
    pButtonPressed = false;
    updated();
  }
}

void Combobox::render( ImageObject& img, const Rect& r )
{
  if ( !visible() ) return;
  //img.setRelativePoint( absoluteXPos() + clientLeft(), absoluteYPos() + clientTop() );
  int x;
  int y;
  img.relativePoint( x, y );
  //cout << "Combo RelX: " << x << " RelY: " << y << endl;
  Edit::render( img, r );

  Border* b;
  int dd = 1;
  if ( pButtonPressed ) {
    b = buttonPressedBorder();
  } else {
    b = buttonBorder();
    dd = 0;
  }

  if ( b != NULL )
		b->render( Rect( clientVisibleWidth() - clientVisibleHeight(), 0, clientVisibleHeight(), clientVisibleHeight() ), img );

  if ( buttonGlyph() != NULL ) {
		img.drawImage( *buttonGlyph(), Rect( 0 + clientVisibleWidth() - clientVisibleHeight() + ( clientVisibleHeight() / 2 - buttonGlyph()->width() / 2 ) + dd, 0 + ( clientVisibleHeight() / 2 - buttonGlyph()->height() / 2 ) + dd, 10, 10 ) );
  }
}


Widget* Combobox::mouseClick(int x, int y, MouseButtons mb)
{
  return Edit::mouseClick(x, y, mb);
}

Widget* Combobox::mouseDblClick(int x, int y, MouseButtons mb)
{
    return Edit::mouseDblClick(x, y, mb);
}

Widget* Combobox::mousePressed(int x, int y, MouseButtons mb)
{
  Widget* res = Edit::mousePressed(x, y, mb);
  //x -= absoluteXPos();
  if ( ( x > width() - height() ) && ( x < width() ) ) {
    if ( !pButtonPressed ) {
      pButtonPressed = true;
      if ( pDropDown != NULL ) {
        pDropDown->setWidth( width() );
        pDropDown->popup( absoluteXPos(), absoluteYPos() + height(), gui() );
				releaseMouseInput();
      }
    } else {
      pButtonPressed = false;
      if ( pDropDown != NULL )
        pDropDown->close();
      updated();
    }
    updated();
  } else {
    pButtonPressed = false;
    if ( pDropDown != NULL )
      pDropDown->close();
    updated();
  }
  return res;
}

Widget* Combobox::mouseReleased(int x, int y, MouseButtons mb)
{
  return Edit::mouseReleased(x, y, mb);
}

void Combobox::onDropdownClose( Popup& dd )
{
  pButtonPressed = false;
  setCursorIndex( 0 );

  updated();
}

void Combobox::onItemClicked( DropdownList& l, DropListItem& item )
{
  setText( item.text() );
  setCursorIndex( 0 );
  onItemSelected( *this, l, item );
  updated();
}

void Combobox::onDropdownDestroy( Popup& dd )
{
	pDropDown = NULL;
}


}
