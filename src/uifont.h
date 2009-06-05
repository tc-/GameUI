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
 * @file
 * Headerfile for the UiFont class.
*/

#ifndef UIFONT_H
#define UIFONT_H

#include <gameui.h>
#include <assert.h>
#include <string>

using std::wstring;
using std::string;


namespace Ui
{

	class Font;

	typedef Font* ( *FontFactory )();


	/**
	 * Class used to store a Font's style.
	 */
	class FontStyle
	{
		public:
			FontStyle( const bool b = false, const bool i = false, const bool u = false ) {
				bold = b;
				italic = i;
				underline = u;
			}

			bool bold;			//!< Font is bold.
			bool italic;		//!< Font is italic.
			bool underline;	//!< Font is underlined.

			/**
			 * Are any styles set for this font.
			 */
			bool isNormal() const {
				return ( ( !bold ) && ( !italic ) && ( !underline ) );
			}

			bool operator== ( const FontStyle& fs ) const {
				return ( ( bold == fs.bold ) && ( italic == fs.italic ) && ( underline == fs.underline ) );
			}
			bool operator!= ( const FontStyle& fs ) const {
				return ( ( bold != fs.bold ) || ( italic != fs.italic ) || ( underline != fs.underline ) );
			}
	};


	/**
	 * Abstract class used to contain a font.
	 */
	class Font
	{
		public:
			Font() {}
			virtual ~Font() {}

			/**
			 * The font size in px.
			 *
			 * @see setSize().
			 */
			virtual int size() = 0;

			/**
			 * Setter for the size property.
			 *
			 * @see size()
			 */
			virtual void setSize( int newSize ) = 0;

			/**
			 * The width of a string.
			 *
			 * @param s the string to get the width of.
			 * @see textHeight() charWidth().
			 */
			virtual int textWidth( wstring s ) = 0;

			/**
			 * The height of the characters in the font.
			 *
			 * @see textWidth() charWidth().
			 */
			virtual int textHeight(  ) = 0;

			/**
			 * The width of a specific char.
			 *
			 * @param c the char to get width of.
			 * @see textWidth() textHeight().
			 */
			virtual int charWidth( wchar_t c ) = 0;

			/**
			 * Load Font from file.
			 *
			 * @see isLoaded().
			 */
			virtual void loadFont( string fname, int size, int index ) = 0;

			/**
			 * Is the font is loaded.
			 *
			 * @see loadFont().
			 */
			virtual bool isLoaded() = 0;

			/**
			 * The style of this font.
			 *
			 * @see setStyle() FontStyle.
			 */
			virtual FontStyle style() = 0;

			/**
			 * Setter for the style property.
			 *
			 * @see style().
			 */
			virtual void setStyle( const FontStyle& fs ) = 0;

			/**
			 * Factory method for creating Font class objects.
			 *
			 * @see setFontFactory().
			 */
			static Font* createFont() {
				assert( pFF != NULL );
				return pFF();
			}

			/**
			 * Set the FontFacroty method to use when creating new Font objects.
			 *
			 * @see createFont() FontFactory.
			 */
			static void setFontFactory( FontFactory ff ) {
				pFF = ff;
			}

		private:

			static FontFactory pFF;

	};

}

#endif
