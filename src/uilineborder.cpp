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


#include "uilineborder.h"

namespace Ui {

//BorderLoader LineBorder::lineBorderLoader( "LineBorder", &themeLineBorderLoader );

LineBorder::LineBorder(): Border()
{
  setType( btLine );
  pLineColor = Color( 90,90,90 );
  pBgColor = Color( 255,255,255 );
}


LineBorder::~LineBorder()
{
}


void LineBorder::useWithLoader()
{
	BorderLoader::addLoader( "LineBorder", &themeLineBorderLoader );
}


Border* LineBorder::themeLineBorderLoader( InifileSection* is, const ThemeLoadOptions& op )
{
  if ( is == NULL ) return NULL;
  string subType = is->keyStringValue( "subtype", "line" );
  if ( subType == "line" ) {
    string lColor = is->keyStringValue( "linecolor", "$black" );
    string bColor = is->keyStringValue( "bgcolor", "$silver" );
    LineBorder* lb = new LineBorder();
    lb->setType( btLine );
    Color c;
    Utils::fromString( lColor, c );
    lb->setLineColor( c );
    Utils::fromString( bColor, c );
    lb->setBgColor( c );
    return (Border*)lb;
  }
  return NULL;
}

void LineBorder::setType( const borderType bt )
{
  pType = bt;
  if ( pType == btLine ) {
    widthLeft = 1;
    widthRight = 1;
    heightTop = 1;
    heightBottom = 1;
  }
}

void LineBorder::render(const Rect r, ImageObject& iobj)
{
  if ( pType == btLine ) {
    iobj.fillRect( Rect( r.left, r.top, r.width - 1, 1 ), pLineColor );
    iobj.fillRect( Rect( r.left + r.width - 1, r.top, 1, r.height ), pLineColor );
    iobj.fillRect( Rect( r.left, r.top + 1, 1, r.height - 1 ), pLineColor );
    iobj.fillRect( Rect( r.left, r.top + r.height - 1, r.width - 1, 1 ), pLineColor );
    iobj.fillRect( Rect( r.left + 1, r.top + 1, r.width - 2, r.height - 2 ), pBgColor );
  }
}

}
