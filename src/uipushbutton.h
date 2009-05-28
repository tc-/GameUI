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
 * Headerfile for the Ui::PushButton class.
 */

#ifndef UIPUSHBUTTON_H
#define UIPUSHBUTTON_H

#include <gameui.h>
#include <sigslot.h>
#include <uiwidget.h>
#include <uiborder.h>
#include <uiimageobject.h>

#include <string.h>

using std::wstring;

namespace Ui
{

	/**
	 * Basic button class
	 */
	class PushButton : public Widget
	{
		public:
			PushButton();
			PushButton( Frame* parent );
			PushButton( Frame* parent, wstring text );
			PushButton( Frame* parent, wstring text, Theme& theme );
			PushButton( Frame* parent, int left, int top, int width );
			PushButton( Frame* parent, int left, int top, int width, int height );
			PushButton( Frame* parent, wstring text, int left, int top, int width );
			PushButton( Frame* parent, wstring text, int left, int top, int width, int height );
			PushButton( Frame* parent, wstring text, Theme& theme, int left, int top, int width );
			PushButton( Frame* parent, wstring text, Theme& theme, int left, int top, int width, int height );

			/**
			 * Reset values to defaults.
			 */
			void Init();

			/**
			 * Assigns a theme to the button.
			 *
			 * border.pushbutton_released: Border to use when button is released.@n
			 * border.pushbutton_pressed: Border to use when button is pressed.@n
			 * font.pushbutton: the font to use.@n
			 * color.pushbutton_font: The font color to use.@n
			 * image.pushbutton: Image to use as glyph.
			 * @see Widget::setTheme()
			 */
			virtual void setTheme( Theme& t, const string prefix = "" );

			/**
			 * Is PushButton pressed.
			 */
			virtual bool pressed();

			/**
			 * Text drawn on the PuchButton.
			 *
			 * @see setText().
			 */
			virtual wstring text();

			/**
			 * Setter for the text property.
			 *
			 * @see text().
			 */
			virtual void setText( wstring s );

			/**
			 * Image to draw on the PushButton.
			 *
			 * @see setImage().
			 */
			virtual ImageObject* image(  ) {
				return pImage;
			}

			/**
			 * Setter for the image property.
			 *
			 * @see image() ImageObject.
			 */
			virtual void setImage( ImageObject* img ) {
				pImage = img;
				updated();
			}

			/**
			 * Border to display when PushButton is pressed.
			 *
			 * @see releasedBorder() Border.
			 */
			virtual Border* pressedBorder();

			/**
			 * Setter for the pressedBorder property.
			 *
			 * @see pressedBorder().
			 */
			virtual void setPressedBorder( Border* bs );

			/**
			 * Border to display when PushButton is released, this is the default.
			 *
			 * @see pressedBorder() Border.
			 */
			virtual Border* releasedBorder();

			/**
			 * Setter for the releasedBorder property.
			 *
			 * @see releasedBorder().
			 */
			virtual void setReleasedBorder( Border* bs );

			virtual void buttonPressed();
			virtual Widget* keyPressed( Key key );
			virtual Widget* mouseClick( int x, int y, MouseButtons mb );
			virtual Widget* mouseIn( MouseButtons mb );
			virtual Widget* mouseOut( MouseButtons mb );
			virtual Widget* mousePressed( int x, int y, MouseButtons mb );
			virtual Widget* mouseReleased( int x, int y, MouseButtons mb );


			virtual void render( ImageObject& img, const Rect& r );

			//! Called when PushButton has been pressed and released.
			signal1<PushButton&> onButtonPressed;

		private:

			wstring pText;
			bool pPressed;
			Border* pPressedBorder;
			Border* pReleasedBorder;
			ImageObject* pImage;


	};

}

#endif
