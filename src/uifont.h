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
Headerfile for the UiFont class
*/

#ifndef UIFONT_H
#define UIFONT_H

#include <gameui.h>
#include <assert.h>
#include <string>

using std::wstring;
using std::string;


namespace Ui {

class Font;

typedef Font* (*FontFactory)();


	/**
	 * Class used to store a font style
	 * @author Tommy Carlsson
	 */
class FontStyle {
public:
	FontStyle( const bool b = false, const bool i = false, const bool u = false ) { bold = b; italic = i; underline = u; }

	bool bold;
	bool italic;
	bool underline;

	bool isNormal() const { return ( (!bold) && (!italic) && (!underline) ); }

	bool operator== ( const FontStyle& fs ) const { return ( ( bold == fs.bold ) && ( italic == fs.italic ) && ( underline == fs.underline ) ); }
	bool operator!= ( const FontStyle& fs ) const { return ( ( bold != fs.bold ) || ( italic != fs.italic ) || ( underline != fs.underline ) ); }
};


/**
Abstract class used to contain a font

@author Tommy Carlsson
*/
class Font{
public:
  Font() {}
  virtual ~Font() {}

  /**
   * Returns the font size.
   * @return the font size.
   */
  virtual int size() = 0;
	/**
	 * Sets a new font size.
	 * @param newSize new font size.
	 * @see Font::size()
	 */
	virtual void setSize( int newSize ) = 0;
  /**
   * Returns the width of a string.
   * @param s the string to get the width of.
   * @return the width of the string.
   */
  virtual int textWidth( wstring s ) = 0;

  /**
   * Returns the height of the characters in the font.
   * @return the height of the characters in the font.
   */
  virtual int textHeight(  ) = 0;

  /**
   * Returns the width of a single char.
   * @param c the char to get width of.
   * @return the width of the char.
   */
  virtual int charWidth( wchar_t c ) = 0;
	virtual void loadFont( string fname, int size, int index ) = 0;

  /**
   * Returns true if the font is loaded.
   * @return true if the font is loaded.
   */
  virtual bool isLoaded() = 0;

	virtual FontStyle style() = 0;
	virtual void setStyle( const FontStyle& fs ) = 0;

	static Font* createFont() {	assert( pFF != NULL ); return pFF(); }
	static void setFontFactory( FontFactory ff ) { pFF = ff; }

private:

	static FontFactory pFF;

};

}

#endif
