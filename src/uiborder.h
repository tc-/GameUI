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
Headerfile for the Ui::Border class
*/

#ifndef UIBORDER_H
#define UIBORDER_H

#include <gameui.h>
#include "uilist.h"
#include "uiimageobject.h"
#include "uiwidget.h"
#include "uirect.h"
#include "uiinifile.h"

#include <string>

using std::string;

namespace Ui
{

	typedef Border* ( *BorderLoadFunc )( InifileSection*, const ThemeLoadOptions& );

	/**
	 * Used internally to link a border load function to a specific border type.
	 */
	struct BorderLoaderItem {
		BorderLoaderItem( string n, BorderLoadFunc f ): name( n ), func( f ) {}
		string name;
		BorderLoadFunc func;
	};


	/**
	 * Used internally to keep track of all border load functions.
	 *
	 * @see Border BorderLoaderItem BorderLoadFunc
	 */
	class BorderLoader
	{
		public:
			BorderLoader( const string borderName, BorderLoadFunc loader ) {
				addLoader( borderName, loader );
			}

			static void addLoader( const string borderName, BorderLoadFunc loader );
			static BorderLoadFunc getLoader( const string& name );
		private:
			static List<BorderLoaderItem*>& pFuncs();
	};

	/**
	 * Describing a Widget border.
	 *
	 * @note The border also renders the background.
	 * @see Widget::border().
	 */
	class Border
	{
		public:

			Border(): widthLeft( 0 ), widthRight( 0 ), heightTop( 0 ), heightBottom( 0 ) {
				pDrawmode = drawOpaque;
			}
			virtual ~Border(  ) {};

			int widthLeft;		//!< Left padding.
			int widthRight;		//!< Right padding.
			int heightTop;		//!< Top padding.
			int heightBottom;	//!< Bottom padding.

			/**
			 * Drawmode of this Border.
			 *
			 * @note If a Border with drawmode drawTransparent is assigned to a Widget with drawmode drawOpaque the Widget drawmode will return drawTransparent.
			 * @see Widget::drawmode().
			 */
			virtual Drawmode drawmode() {
				return pDrawmode;
			}

			/**
			 * Setter for the drawmode property.
			 *
			 * @see drawmode().
			 */
			virtual void setDrawmode( const Drawmode& dm ) {
				pDrawmode = dm;
			}

			/**
			 * Render the border.
			 *
			 * Override this method in your derived classes.
			 */
			virtual void render( const Rect r, ImageObject& iobj ) = 0;

		private:
			Drawmode pDrawmode;

	};

}

#endif
