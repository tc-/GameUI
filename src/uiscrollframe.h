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


#ifndef UIUISCROLLFRAME_H
#define UIUISCROLLFRAME_H

#include <uiwidget.h>
#include <uiframe.h>
#include <uirect.h>
#include <uivscrollbar.h>
#include <uihscrollbar.h>

namespace Ui
{

	/**
	 * Frame class able to scroll its contents.
	 */
	class ScrollFrame: public Frame
	{
		public:
			ScrollFrame( Frame* parent );

			~ScrollFrame();

			virtual void setTheme( Theme & t, const string prefix = "" );

			virtual Rect getClientRect();

			virtual int clientWidth( );
			virtual int clientHeight( );

			virtual void render( ImageObject& img, const Rect& r );

			virtual void resize( int newwidth, int newheight );
			virtual void setPosition( const Position& pos );
			inline void setPosition( const int left, const int top ) {
				setPosition( Position(left, top) );
			}

			virtual void scroll( const int dx, const int dy );
			virtual void scrollTo( const int top, const int left );

			virtual VScrollbar* vScroll() const;
			virtual void setVScroll( VScrollbar* sb );
			virtual HScrollbar* hScroll() const;
			virtual void setHScroll( HScrollbar* sb );

			virtual int scrollX() const {
				return pScrollX;
			}
			virtual int scrollY() const {
				return pScrollY;
			}

			virtual void setScrollX( const int x ) {
				pScrollX = x;
				updateScrollbars();
			}
			virtual void setScrollY( const int y ) {
				pScrollY = y;
				updateScrollbars();
			}
			virtual void setScroll( const int x, const int y ) {
				pScrollX = x;
				pScrollY = y;
				updateScrollbars();
			}

			virtual void childUpdated( Widget& o );

			virtual Widget* mouseMove( int x, int y, MouseButtons mb );
			virtual Widget* mousePressed( int x, int y, MouseButtons mb );
			virtual Widget* mouseReleased( int x, int y, MouseButtons mb );

		private:

			VScrollbar* pVScroll;
			HScrollbar* pHScroll;

			int pScrollX;
			int pScrollY;

			bool pClientCasheValid;
			int pClientWidthCashe;
			int pClientHeightCashe;

			virtual void onScrolled( Widget* obj, int old );
			virtual void scrollDestroyed( Widget& obj );

			virtual void updateScrollbars( bool onlyBounds = false );

		protected:

			virtual void childAdded( Widget* o );
			virtual void childRemoved( Widget* o );

	};

}

#endif
