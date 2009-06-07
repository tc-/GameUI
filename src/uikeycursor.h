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
 * Headerfile for the Ui::KeyCursor class.
 */

#ifndef UIKEYCURSOR_H
#define UIKEYCURSOR_H

#include <gameui.h>
#include <uicolor.h>
#include <uiwidget.h>
#include <uitimer.h>

namespace Ui
{

	/**
	 * Blinking cursor used to indicate current position in text where it's beeing edited.
	 */
	class KeyCursor : public has_slots<>
	{
		public:

			KeyCursor();
			~KeyCursor();

			virtual void render( ImageObject& img, const Rect& r );
			virtual void setFocusedWidget( Widget* widget );
			virtual void updated();

			virtual Widget* focusedWidget( ) const;

			virtual Drawmode drawmode() const;
			virtual void setDrawmode( Drawmode dm );

			virtual bool shouldRenderBg() const;

			virtual void setPosition( const int xpos, const int ypos );
			virtual void setSize( const int w, const int h );
			virtual void setRect( const Rect& r );

			virtual Rect getRect( ) const;

			virtual int left() const;
			virtual void setLeft( const int l );
			virtual int top() const;
			virtual void setTop( const int t );

			virtual int width() const;
			virtual void setWidth( const int w );
			virtual int height() const;
			virtual void setHeight( const int h );

			virtual bool visible() const;
			virtual void setVisible( const bool vis );
			virtual bool enabled() const;
			virtual void setEnabled( const bool en );

			virtual int showTime() const;
			virtual void setShowTime( const int ms );
			virtual int hideTime() const;
			virtual void setHideTime( const int ms );

			virtual Color color() const;
			virtual void setColor( Color c );

			static KeyCursor& cursorObject();
			static void setCursorObject( KeyCursor* kc );

		private:

			static KeyCursor* pKeyCursorObject;
			int pShow;
			int pHide;

			bool pVisible;
			bool pEnabled;

			int pXPos;
			int pYPos;
			int pWidth;
			int pHeight;

			Drawmode pDM;

			Color pColor;

			Widget* pWidget;

			Timer pTimer;

			void onTimerTick( Timer& t, int& to );

	};

}

#endif
