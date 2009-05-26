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


#ifndef UIUIDROPDOWNLIST_H
#define UIUIDROPDOWNLIST_H

#include <uiborder.h>
#include <uipopup.h>
#include <uigui.h>
#include <uiutils.h>
#include <uilist.h>

namespace Ui {

class DropListItem;

/**
 * A Popup class used with a Combobox widget
 * @author Tommy Carlsson
*/
class DropdownList : public Popup
{
public:
  DropdownList();
  virtual ~DropdownList();

  virtual void setTheme( Theme & t, const string prefix = "" );

  virtual void addItem( DropListItem* item );
  virtual DropListItem* getItem( int index ) { return pChildren.get( index ); }
  virtual void removeItem( int index ) { pChildren.remove( index ); updated(); }
  virtual int getItemIndex( DropListItem* item ) const { return pChildren.getIndex( item ); }

  virtual void popup( const int x, const int y, Gui& gui );
  virtual void render( Rect area );

  virtual DropListItem* selectedItem() { return pSelected; }
  virtual void setSelectedItem( DropListItem* item );

  virtual void mouseMove(int x, int y, MouseButtons mb);
  virtual void mousePressed(int x, int y, MouseButtons mb);
  virtual void mouseReleased(int x, int y, MouseButtons mb);

  signal2<DropdownList&, DropListItem&> onItemClicked;

private:

  List<DropListItem*> pChildren;
  DropListItem* pSelected;

};

/**
 * Class used as an item inside a DropdownList
 * @author Tommy Carlsson
 */
class DropListItem {
public:

	DropListItem(  ): pText(L"Item"), pParent(NULL)
  {
    pFont = NULL;
    pFontColor = Color( 0, 0, 0 );
    pBgColor = Color( 128, 128, 128, 0 );
    pSelBgColor = Color( 180,220,255 );
    pIcon = NULL;
    pHeight = 18;
    pSelected = false;
    setTheme( Theme::defaultTheme() );
  }

	DropListItem( DropdownList* p, wstring t = L"Item", string themeprefix = "" ): pText(t), pParent(p)
  {
    pFont = NULL;
    pFontColor = Color( 0, 0, 0 );
    pBgColor = Color( 128, 128, 128, 0 );
    pSelBgColor = Color( 180,220,255 );
    pIcon = NULL;
    pHeight = 18;
    pSelected = false;
    setTheme( Theme::defaultTheme(), themeprefix );
    if ( pParent != NULL )
      pParent->addItem( this );
  }

  virtual ~DropListItem()
  {

    if ( pParent != NULL ) {
      int index = pParent->getItemIndex( this );
      if ( index >= 0 )
        pParent->removeItem( index );
    }
  }

  virtual void setTheme( Theme & t, const string prefix = "" )
  {
    setFont( t.getFont( prefix+"droplistitem" ) );
    setFontColor( t.getColor( prefix+"droplistitem_font" ) );
    setBgColor( t.getColor( prefix+"droplistitem_background" ) );
    setSelectedBgColor( t.getColor( prefix+"droplistitem_background_selected" ) );
    setIcon( t.getImage( prefix+"droplistitem_default_icon" ) );
  }

  virtual DropdownList* parent() const { return pParent; }
  virtual void setParent( DropdownList* dl ) { pParent = dl; }

  virtual wstring text() const { return pText; }
  virtual void setText( wstring s ) { pText = s; }

  virtual Font* font(  ) const { return pFont; }
  virtual void setFont( Font* f ) { pFont = f; updated(); }
  virtual Color fontColor(  ) const { return pFontColor; }
  virtual void setFontColor( Color c ) { pFontColor = c; updated(); }

  virtual Color bgColor(  ) const { return pBgColor; }
  virtual void setBgColor( Color c ) { pBgColor = c; updated(); }
  virtual Color selectedBgColor(  ) const { return pSelBgColor; }
  virtual void setSelectedBgColor( Color c ) { pSelBgColor = c; updated(); }

  virtual ImageObject* icon() const { return pIcon; }
  virtual void setIcon( ImageObject* img ) { pIcon = img; updated(); }

  virtual bool selected() const { return pSelected; }
  virtual void setSelected( const bool sel ) { pSelected = sel; }

  virtual int height() const { return pHeight; }
  virtual void setHeight( const int h ) { pHeight = h; }

  virtual void render( int x, int y, int width )
  {
    if ( pParent == NULL ) return;
    Gui* gui = pParent->gui();
    if ( gui == NULL ) return;
    if ( !pParent->active() ) return;
    if ( pSelected )
      gui->screen().fillRect( Rect( x, y, width, height() ), pSelBgColor );
    else
      gui->screen().fillRect( Rect( x, y, width, height() ), pBgColor );
    if ( pFont != NULL ) {
      int tx;
      if ( pIcon == NULL )
        tx = 2;
      else
        tx = pIcon->width() + 2;
      int ty = Utils::inMiddle( height(), pFont->textHeight() );
      gui->screen().outText( pText, *pFont, x+tx, y+ty, pFontColor );
    }
  }
  virtual void updated()
  {
    if ( pParent == NULL ) return;
    if ( pParent->active() ) pParent->updated();
  }

private:

  bool pSelected;
  wstring pText;
  DropdownList* pParent;
  Font* pFont;
  Color pFontColor;
  Color pBgColor;
  Color pSelBgColor;
  ImageObject* pIcon;
  int pHeight;

};

}

#endif
