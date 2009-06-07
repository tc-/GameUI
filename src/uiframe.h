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
 * Headerfile for the Frame class.
 */

#ifndef UIFRAME_H
#define UIFRAME_H

#include <gameui.h>
#include <uiwidget.h>
#include <uilist.h>


namespace Ui
{

	enum LineUpType { lineHorizontal, lineVertical, lineFill, lineNone };

	/**
	 * Class used for framed objects able to manage child objects.
	 */
	class Frame : public Widget
	{
		public:

			Frame(  );
			Frame( Frame* parent );
			virtual ~Frame(  );

			virtual void setTheme( Theme& t, const string prefix = "" );

			virtual void setGui( Gui* s );

			virtual void childUpdated( Widget& o );

			virtual void arrangeChildren(  );

			virtual Rect getClientClipRect();

			virtual Widget* getWidgetAt( int x, int y, bool recursive = false );

			virtual void updated(  );
			virtual void renderBackground( const Rect& r );

			virtual void resize( int newwidth, int newheight );

			virtual int scrollX( ) const {
				return 0;
			}
			virtual int scrollY( ) const {
				return 0;
			}

			virtual int zIndex( );
			virtual int setZIndex( const int z );

			virtual void getWidgetsInRect( List<Widget*>& l, const Rect r, bool recursive = true );

			virtual Widget* mouseMove( int x, int y, MouseButtons mb );
			virtual Widget* mouseClick( int x, int y, MouseButtons mb );
			virtual Widget* mouseDblClick( int x, int y, MouseButtons mb );
			virtual Widget* mousePressed( int x, int y, MouseButtons mb );
			virtual Widget* mouseReleased( int x, int y, MouseButtons mb );
			virtual Widget* mouseIn( MouseButtons mb );
			virtual Widget* mouseOut( MouseButtons mb );
			virtual Widget* keyPressed( Key key );
			virtual Widget* keyReleased( Key key );

			virtual void moveWidgetToTop( Widget* obj ) {
				int pos = pChildList.getIndex( obj );
				if ( pos != -1 ) {
					pChildList.remove( pos );
					pChildList.insert( obj, 0 );
					setZIndex( zIndex() );
				}
			}

			virtual void moveWidgetToBottom( Widget* obj ) {
				int pos = pChildList.getIndex( obj );
				if ( pos != -1 ) {
					pChildList.remove( pos );
					pChildList.insert( obj, pChildList.count() - 1 );
					setZIndex( zIndex() );
				}
			}

			virtual Widget* child( int index ) const {
				return pChildList.get( index );
			}

			virtual void addChild( Widget& o ) {
				//cout << "* UiFrame::addChild(  )" << endl;
				if ( pChildList.getIndex( &o ) == -1 ) {
					Widget* p = &o;
					pChildList.append( p );
					setZIndex( zIndex() );
					childAdded( &o );
				}
				//cout << "* UiFrame::addChild(  ) done" << endl;
			}

			virtual void removeChild( Widget* o ) {
				pChildList.remove( pChildList.getIndex( o ) );
				setZIndex( zIndex() );
				onChildRemoved( o );
			}

			virtual void removeChild( int index ) {
				Widget* o = pChildList.get( index );
				pChildList.remove( index );
				setZIndex( zIndex() );
				onChildRemoved( o );
			}

			virtual bool hasChildren() const {
				return ( numChildren() > 0 );
			}

			virtual int numChildren() const {
				return pChildList.count();
			}

			signal1<Widget*> onChildAdded;
			signal1<Widget*> onChildRemoved;

		private:

			Widget* pCur;

			static bool sortWidgetsByLeft( List< Widget* > & l, int i1, int i2 );
			static bool sortWidgetsByTop( List< Widget* > & l, int i1, int i2 );

		protected:

			List<Widget*> pChildList;

			virtual void childAdded( Widget* o );
			virtual void childRemoved( Widget* o );

	};

}

#endif
