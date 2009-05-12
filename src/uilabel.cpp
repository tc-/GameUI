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
#include "uilabel.h"

namespace Ui {

Label::Label()
 : Widget()
{
  pText = L"Label";
  pMultiline = false;
  pHAl = halignLeft;
  pVAl = valignTop;
  setWidth( 100 );
  setHeight( 24 );
  setDrawmode ( DM_TRANSPARENT );
}

Label::Label( Frame* parent )
  : Widget( parent )
{
  pText = L"Label";
  pMultiline = false;
  pHAl = halignCenter;
  pVAl = valignCenter;
  setWidth( 100 );
  setHeight( 18 );
  setDrawmode ( DM_TRANSPARENT );
}


Label::~Label()
{
}

void Label::setTheme( Theme & t, const string prefix )
{
	Widget::setTheme( t, prefix );
  beginUpdate();
  setBorder( t.getBorder( prefix+"label" ) );
  setFont( t.getFont( prefix+"label" ) );
  setFontColor( t.getColor( prefix+"label_font" ) );
  endUpdate();
}


wstring Label::text()
{
  return pText;
}

void Label::setText( wstring s )
{
  pText = s;
  updated();
}

bool Label::multiline() const
{
  return pMultiline;
}

void Label::setMultiline( const bool enable )
{
  pMultiline = enable;
}

void Label::render( ImageObject& img, const Rect& rr )
{
  if ( !visible() ) return;

  if ( font() != NULL ) {
    if (!pMultiline ) {
      Rect r = Rect( 0, 0, clientVisibleWidth(), clientVisibleHeight() );
      int theight = font()->textHeight();
      int twidth = font()->textWidth( pText );

      if ( pVAl == valignCenter ) {
        r.top += ( r.height / 2 - theight / 2 );
      } else if ( pVAl == valignBottom ) {
        r.top += ( r.height - theight );
      }

      if ( pHAl == halignCenter ) {
        r.left += ( r.width / 2 - twidth / 2 );
      } else if ( pHAl == halignRight ) {
        r.left += ( r.width - twidth );
      }

      screen().outText( pText, *font(), (int)r.left, (int)r.top, fontColor() );

    } else {

      List<wstring*> sl;
      wstring tmps = pText;
      int pos = tmps.find( L"\n", 0 );
      while( pos > 0 ) {
       // cout << "pos: " << pos << endl;
        wstring* s = new wstring;
        *s = tmps.substr( 0, pos );
        tmps.erase(0, pos + 1);
        sl.append( s );
        pos = tmps.find( L"\n", 0 );
      }
      if ( tmps != L"" ) {
        wstring* s = new wstring;
        *s = tmps;
        sl.append( s );
      }

      Rect r = Rect( 0, 0, clientVisibleWidth(), clientVisibleHeight() );
      pos = 0;

      while( pos < sl.count() ) {
        wstring* s = sl.get( pos );
        if ( font()->textWidth( *s ) > r.width ) {
          int space = s->find( L" ", 0 );
          wstring* news = new wstring;
          while( space > 0 ) {
  //          cout << "space:" << space << endl;
            if ( font()->textWidth( *news + s->substr(0, space) ) > r.width ) {
//              cout << "Added at pos: " << pos << " len: " << news->length() << endl;
              sl.insert( s, pos );
              sl.replace( pos, news );
              pos++;
              news = new wstring;
            }
            *news += s->substr(0, space) + L" ";
            s->erase(0, space + 1);
            space = s->find( L" ", 0 );
            if ( (space == 0) && (s->length() > 0) )
              space = s->length()-1;
          }
          if ( !news->empty() )
            s->replace(0, 0, *news);
          delete news;
        }
        pos++;
      }



      int theight = font()->textHeight();

      for( int i = 0; i < sl.count(); i++ ){
        r = Rect( 0, 0, clientVisibleWidth(), clientVisibleHeight() );
        int twidth = font()->textWidth( *sl.get( i ) );
        if ( pVAl == valignCenter ) {
          r.top += ( (r.height / 2) - ((theight * sl.count()) / 2) ) + (theight * i);
        } else if ( pVAl == valignBottom ) {
          r.top += ( r.height - (theight * i ) );
        } else  if ( pVAl == valignTop ) {
          r.top += (theight * i);
        }

        if ( pHAl == halignCenter ) {
          r.left += ( r.width / 2 - twidth / 2 );
        } else if ( pHAl == halignRight ) {
          r.left += ( r.width - twidth );
        }

        screen().outText( *sl.get( i ), *font(), (int)r.left, (int)r.top, fontColor() );
        delete sl.get( i );
      }

    }

  }

}



}
