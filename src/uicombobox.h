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


#ifndef UICOMBOBOX_H
#define UICOMBOBOX_H

#include <gameui.h>
#include <sigslot.h>
#include <uigui.h>
#include <uiedit.h>
#include <uiborder.h>
#include <uipopup.h>
#include <uidropdownlist.h>
#include <uiimageobject.h>

namespace Ui
{

	/**
	 * A Combobox Widget
	 */
	class Combobox : public Edit
	{
		public:
			Combobox( Frame* p = NULL );
			virtual ~Combobox();

			virtual void setTheme( Theme & t, const string prefix = "" );

			virtual MouseCursor* getCursor( const int & x, const int& y ) {
				if ( getEditArea().pointInside( x, y ) ) return cursor();
				else return pButtonCursor;
			}
			virtual MouseCursor* buttonCursor() {
				return pButtonCursor;
			}
			virtual void setButtonCursor( MouseCursor* mc ) {
				pButtonCursor = mc;
			}

			virtual ImageObject* buttonGlyph() const {
				return pButtonGlyph;
			}
			virtual void setButtonGlyph( ImageObject* img ) {
				pButtonGlyph = img;
				updated();
			}

			virtual Border* buttonBorder() const {
				return pButtonBorder;
			}
			virtual void setButtonBorder( Border* b ) {
				pButtonBorder = b;
				updated();
			}

			virtual Border* buttonPressedBorder() const {
				return pButtonPressedBorder;
			}
			virtual void setButtonPressedBorder( Border* b ) {
				pButtonPressedBorder = b;
				updated();
			}

			virtual DropdownList* dropdownLis() {
				return pDropDown;
			}
			virtual void setDropdownList( DropdownList* dd );

			virtual void setFocused( bool f );

			virtual void render( ImageObject& img, const Rect& r );
			virtual Rect getEditArea() {
				return Rect( 0, 0, clientVisibleWidth() - height(), clientVisibleHeight() );
			}

			virtual Widget* mouseClick( int x, int y, MouseButtons mb );
			virtual Widget* mouseDblClick( int x, int y, MouseButtons mb );
			virtual Widget* mousePressed( int x, int y, MouseButtons mb );
			virtual Widget* mouseReleased( int x, int y, MouseButtons mb );

			signal3<Combobox&, DropdownList&, DropListItem&> onItemSelected;

		private:

			ImageObject* pButtonGlyph;
			Border* pButtonBorder;
			Border* pButtonPressedBorder;

			MouseCursor* pButtonCursor;

			bool pButtonPressed;

			DropdownList* pDropDown;

			virtual void onDropdownDestroy( Popup& dd );
			virtual void onDropdownClose( Popup& dd );
			virtual void onItemClicked( DropdownList& l, DropListItem& item );

	};

}

#endif
