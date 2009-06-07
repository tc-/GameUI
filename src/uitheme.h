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


#ifndef UITHEME_H
#define UITHEME_H

#include <gameui.h>
#include <uicolor.h>
#include <uifont.h>
#include <uiinifile.h>
#include <uiimageobject.h>
#include <string>
#include <sigslot.h>

using std::string;
using namespace sigslot;

namespace Ui
{

	class Border;
	class LibControl;
	class MouseCursor;

	enum defBorder {
		dbNone,
		dbButton,
		dbButtonPressed,
		dbEdit,
		dbDropdown,
		dbPopup,
		dbSelect
	};

	enum defColor {
		dcDefault,
		dcFont,
		dcButton,
		dcSelect,
		dcBorderLine
	};

	/**
	 * Class used internally to link a name string to a border object.
	 */
	class BorderName
	{
		public:
			string name;
			Border* border;
			bool clone;
			BorderName( const string n, Border* b, const bool& cl ): name( n ),border( b ),clone( cl ) {}
	};


	/**
	 * Class used internally to link a name string to a color object.
	 */
	class ColorName
	{
		public:
			string name;
			Color color;
			ColorName( const string n, const Color c ): name( n ),color( c ) {}
	};


	/**
	 * Class used internally to link a name string to a image object.
	 */
	class ImageName
	{
		public:
			string name;
			ImageObject* image;
			bool clone;
			ImageName( const string n, ImageObject* img, const bool cl ): name( n ),image( img ),clone( cl ) {}
	};


	/**
	 * Class used internally to link a name string to a font object.
	 */
	class FontName
	{
		public:
			string name;
			Font* font;
			bool clone;
			FontName( const string n, Font* f, const bool cl ): name( n ),font( f ),clone( cl ) {}
	};


	/**
	 * Class used internally to link a name string to a cursor object.
	 */
	class CursorName
	{
		public:
			string name;
			MouseCursor* cursor;
			bool clone;
			CursorName( const string n, MouseCursor* c, const bool cl ): name( n ),cursor( c ),clone( cl ) {}
	};


	class ThemeLoadOptions;
	class Theme;

	typedef ImageObject* ( *ImageLoader )( const string, InifileSection*, const ThemeLoadOptions& );
	typedef Font* ( *FontLoader )( InifileSection*, const ThemeLoadOptions& );


	/**
	 * Class optionally used when loading a theme. Also used internally for the same purpose.
	 */
	class ThemeLoadOptions
	{
		public:
			ThemeLoadOptions():
					theme( NULL ), imageLoader( NULL ), fontLoader( NULL ), borderRoot( "." ), fontRoot( "." ), imageRoot( "." ) {  }
			ThemeLoadOptions( ImageLoader il, FontLoader fl, string br, string fr, string ir, Theme* th ):
					theme( th ), imageLoader( il ), fontLoader( fl ), borderRoot( br ), fontRoot( fr ), imageRoot( ir ) {  }

			Theme* theme;
			ImageLoader imageLoader;
			FontLoader fontLoader;
			string borderRoot;
			string fontRoot;
			string imageRoot;
	};

	/**
	 * Class containing colors, images and borders that can be applied to the controls.
	 */
	class Theme
	{
		public:

			Theme();
			~Theme();

			/**
			 * The default Theme class.
			 *
			 * @see Widget::setTheme().
			 */
			static Theme& defaultTheme() {
				static Theme pDefaultTheme;
				return pDefaultTheme;
			}

			/**
			 * The name of the Theme.
			 *
			 * @see setName(), description()
			 */
			string name() {
				return pName;
			}

			/**
			 * Set the name of the Theme.
			 *
			 * @param s The new name of the Theme.
			 * @see name().
			 */
			void setName( const string& s ) {
				pName = s;
			}

			/**
			 * The Theme description.
			 *
			 * @return The Theme description.
			 * @see setDescription() name().
			 */
			string description() {
				return pDesc;
			}

			/**
			 * Set the Theme Description.
			 *
			 * @param s The Theme Description.
			 * @see description().
			 */
			void setDescription( const string& s ) {
				pDesc = s;
			}

			/**
			 * Get a Border loaded into the theme.
			 *
			 * @param name Name of the Border to get.
			 * @param db What to return if the Border is not found.
			 * @return A Border loaded into the theme.
			 * @see setBorder() freeBorders().
			 */
			Border* getBorder( const string name, const defBorder db = dbNone );

			/**
			 * Add a Border to the Theme.
			 *
			 * @todo Remove clone parameter and fix it automatically.
			 * @param name Name of the Border.
			 * @param border The Border object itself.
			 * @param clone True if the Border object is a copy of another Border allready added to the Theme.
			 * @see getBorder().
			 */
			void setBorder( const string name, Border* border, const bool clone = false );

			/**
			 * Get an Image loaded into the Theme.
			 *
			 * @param name Name of the Image.
			 * @return The ImageObject requested or NULL if not found.
			 * @see setImage() freeImages().
			 */
			ImageObject* getImage( const string name );

			/**
			 * Add a Image into the Theme.
			 *
			 * @param name Name of the Image.
			 * @param img The ImageObject object itself.
			 * @param clone
			 * @see getImage().
			 */
			void setImage( const string name, ImageObject* img, const bool clone = false );

			/**
			 * Get a Color loaded into the Theme or a default Color.
			 *
			 * @param name Name of the Color.
			 * @param dc what color to return if the Color is not found.
			 * @return The Color requested or a default Color.
			 * @see setColor() clearColors().
			 */
			Color getColor( const string& name, const defColor& dc = dcDefault ) const;

			/**
			 * Get a Color loaded into Theme or return the Color provided,
			 *
			 * @param name Name of the Color.
			 * @param dc The default Color to return.
			 * @return The color requested or the default color provided.
			 * @see setColor() clearColors().
			 */
			Color getColor( const string name, Color dc ) const;

			/**
			 * Get a default Color.
			 *
			 * @param dc The default Color to get.
			 * @return The default Color.
			 * @see setDefaultColor() getColor().
			 */
			Color getDefaultColor( const defColor& dc = dcDefault ) const;

			/**
			 * Add a Color to the Theme.
			 *
			 * @param name Name of the Color.
			 * @param c The Color itself.
			 * @param clone
			 * @see getColor().
			 */
			void setColor( const string name, const Color c, const bool clone = false );

			/**
			 * Set a default Color.
			 *
			 * @param c The new Color.
			 * @param dc The default Color to set.
			 * @see getDefaultColor() getColor().
			 */
			void setDefaultColor( Color c, const defColor& dc = dcDefault );

			/**
			 * Get a Font added to the Theme.
			 *
			 * @param name Name of the Font.
			 * @return The font Requested or default Font if not found.
			 * @see setFont().
			 */
			Font* getFont( const string name );

			/**
			 * Get a Font added to the Theme or return provided Font if not found.
			 *
			 * @param name Name of Font.
			 * @param defFont Default font to return if not found.
			 * @return The requested Font or provided Font if not found.
			 */
			Font* getFont( const string name, Font* defFont );

			/**
			 * Add a Font to the Theme.
			 *
			 * @param name Name of the Font.
			 * @param f The Font object itself.
			 * @param clone
			 * @see getFont() freeFonts().
			 */
			void setFont( const string name, Font* f, const bool clone = false );

			/**
			 * Set the default Font.
			 *
			 * @param f The Font object itself.
			 * @see setFont() getFont() freeFonts().
			 */
			void setDefaultFont( Font* f ) {
				pDefaultFont = f;
			}

			/**
			 * Get a Cursor added into the Theme or default Cursor if not found.
			 *
			 * @param name Name of the Cursor to get.
			 * @return The requested Cursor or default Cursor if not found.
			 * @see setCursor().
			 */
			MouseCursor* getCursor( const string& name );

			/**
			 * Add a Cursor to the Theme.
			 *
			 * @param name Name of the Cursor.
			 * @param c The Cursor object itself.
			 * @param clone
			 * @see getCursor() freeCursors().
			 */
			void setCursor( const string& name, MouseCursor* c, const bool clone = false );

			/**
			 * Set the default Cursor.
			 *
			 * @param mc The Cursor object.
			 * @see setCursor() getCursor() freeCursors().
			 */
			void setDefaultCursor( MouseCursor* mc ) {
				pDefaultCursor = mc;
			}

			bool loadTheme( const string fname, const string rootDir, LibControl& lc );
			bool loadTheme( const string fname, const string borderRoot, const string fontRoot, const string imageRoot, LibControl& lc );

			bool loadTheme( const string fname, const string rootDir, ImageLoader il, FontLoader fl );
			bool loadTheme( const string fname, const string borderRoot, const string fontRoot, const string imageRoot, ImageLoader il, FontLoader fl );

			/**
			 * Load Theme from file.
			 * @param fname Filename.
			 * @param op Load options.
			 * @return True if Theme loaded successfully.
			 */
			bool loadTheme( const string fname, const ThemeLoadOptions& op );

			/**
			 * Free all reasources allocated within the Theme.
			 * @see freeBorders() freeColors() reeCursors() freeFonts() freeImages() clearAllResources().
			 */
			void freeAllResources();

			/**
			 * Free all Fonts.
			 * @see freeAllResources() clearFonts().
			 */
			void freeFonts();

			/**
			 * Free all Borders.
			 * @see freeAllResources() clearBorders().
			 */
			void freeBorders();

			/**
			 * Free all Images.
			 * @see freeAllResources() clearImages().
			 */
			void freeImages();

			/**
			 * Free all Colors.
			 * @see freeAllResources() clearColors().
			 */
			void freeColors();

			/**
			 * Free all Cursors.
			 * @see freeAllResources() clearCursors().
			 */
			void freeCursors();

			/**
			 * Empty Lists to all resources.
			 * @see clearBorders() clearColors() clearCursors() clearFonts() clearImages() freeAllResources().
			 */
			void clearAllResources();

			/**
			 * Empty the Font List.
			 * @see clearAllResources() clearFonts().
			 */
			void clearFonts();

			/**
			 * Empty the Border List.
			 * @see clearAllResources() clearBorders().
			 */
			void clearBorders();

			/**
			 * Empty the Image List
			 * @see clearAllResources() clearImages()
			 */
			void clearImages();

			/**
			 * Empty the Color List.
			 * @see clearAllResources() clearColors()
			 */
			void clearColors();

			/**
			 * Empty the Cursor List.
			 * @see clearAllResources() clearCursors().
			 */
			void clearCursors();

			/**
			 * Set Theme as Updated.
			 * @see isUpdated() beginUpdate().
			 */
			void updated();

			/**
			 * Is Theme updated.
			 * @return True if Theme has been Updated.
			 * @see updated().
			 */
			bool isUpdated();

			/**
			 * Halts any updated actions to be taken until endUpdate() is called.
			 * @see updated() Theme::endUpdate().
			 */
			void beginUpdate();

			/**
			 * Resumes all updated actions.
			 * @see beginUpdate().
			 */
			void endUpdate();

			/**
			 * Event emitted when Theme is uppdated.
			 */
			signal1<Theme&> onUpdated;

		private:

			string pName;
			string pDesc;

			Font* pDefaultFont;
			MouseCursor* pDefaultCursor;

			Color pDCDefault;
			Color pDCFont;
			Color pDCButton;
			Color pDCSelect;
			Color pDCBorderLine;

			List<BorderName*> pBorders;
			List<ImageName*> pImages;
			List<ColorName*> pColors;
			List<FontName*> pFonts;
			List<CursorName*> pCursors;

			bool pUpdated;
			int pDontUpdate;
	};



}

#endif
