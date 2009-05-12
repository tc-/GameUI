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
Implementation of the Ui::SDLFont class
*/

#include "uisdlfont.h"
#include "uiinifile.h"
#include "SDL_ttf.h"
#include "assert.h"
#include <string>

using std::string;

namespace Ui {

SDLFont::SDLFont()
 : Font()
{
  f = NULL;
}

SDLFont::SDLFont( string fname, int size, int index )
{
  f = NULL;
  loadFont( fname, size, index );
}

SDLFont::~SDLFont()
{
  freeFont();
}

Font* SDLFont::themeSDLFontLoader( InifileSection* iniSec, const ThemeLoadOptions& op )
{
  SDLFont* f = new SDLFont();
  if ( iniSec != NULL ) {
    string fname = op.fontRoot+"/"+iniSec->keyStringValue( "file", "" );
    int size = iniSec->keyIntValue( "size", 12 );
    int index = iniSec->keyIntValue( "index", 0 );
    if ( fname != "" )
      f->loadFont( fname, size ,index );
  }
  if ( f->isLoaded() ) {
    return f;
  } else {
    delete f;
    return NULL;
  }
}


int SDLFont::size()
{
  if ( !isLoaded() ) return 0;
  return psize;
}

int SDLFont::textHeight(  )
{
  if ( !isLoaded() ) return 0;
  return TTF_FontHeight( f );
}

int SDLFont::textWidth( wstring s )
{
  if ( !isLoaded() ) return 0;
/*  int trash, advance;
  int l = 0;

  for( int i = 0; i < s.length(); i++ ) {
    TTF_GlyphMetrics( f, s[i], &trash, &trash, &trash, &trash, &advance );
    l += advance;
  }
  return l;
*/

  Uint16* d = (Uint16*)malloc( s.length()*2 + 2 );
  for ( unsigned int i = 0; i <= s.length(); i++ ){
    d[i] = (Uint16)s[i];
//      cout << "," << (Uint16)s[i];
  }

  int x, y;
  TTF_SizeUNICODE( f, d, &x, &y );

  free( d );

  return x;

}

int SDLFont::charWidth( wchar_t c )
{
  if ( !isLoaded() ) return 0;
  int trash, advance;
  TTF_GlyphMetrics( f, c, &trash, &trash, &trash, &trash, &advance );
  return advance;
}


void SDLFont::setSize( int newSize )
{
  loadFont( pfname, newSize, pindex );
  psize = newSize;
}

void SDLFont::loadFont( string fname, int size, int index )
{
	if ( f != NULL ) TTF_CloseFont( f );
  f = TTF_OpenFontIndex( fname.c_str(), size, index );
  pfname = fname;
  pindex = index;
  psize = size;
}

/*
void SDLFont::setStyle( int style )
{
  assert( f != NULL );
  TTF_SetFontStyle( f, style );
}*/

FontStyle SDLFont::style()
{
	assert( f != NULL );
	int style = TTF_GetFontStyle( f );
	if( style == TTF_STYLE_NORMAL )
		return FontStyle();
	else {
		bool b = false;
		bool i = false;
		bool u = false;
		if ( style & TTF_STYLE_BOLD )
			b = true;
		if ( style&TTF_STYLE_ITALIC )
			i = true;
		if ( style & TTF_STYLE_UNDERLINE )
			u = true;
		return FontStyle( b, i, u );
	}
}

void SDLFont::setStyle( const FontStyle& fs )
{
	assert( f != NULL );
	int style = 0;
	if ( fs.isNormal() ) {
		style = TTF_STYLE_NORMAL;
	} else {
		if ( fs.bold ) style = style | TTF_STYLE_BOLD;
		if ( fs.italic ) style = style | TTF_STYLE_ITALIC;
		if ( fs.underline ) style = style | TTF_STYLE_UNDERLINE;
	}
	cout << "S: " << style << endl;
	TTF_SetFontStyle( f, style );
}


void SDLFont::freeFont()
{
  if ( isLoaded() ) {
    TTF_CloseFont( f );
    f = NULL;
  }
}


bool SDLFont::isLoaded()
{
  return ( f != NULL );
}

TTF_Font* SDLFont::getFont()
{
  return f;
}

}
