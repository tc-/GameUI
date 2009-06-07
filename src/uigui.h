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
 * Headerfile for the UiScreen class
 */

#ifndef UIGUI_H
#define UIGUI_H

#include <gameui.h>
#include <uiframe.h>
#include <uikeycursor.h>
#include <uikey.h>
#include <uilist.h>
#include <uipopup.h>
#include <uiimageobject.h>
#include <sigslot.h>
#include <uiclipboard.h>
#include <uidragobject.h>

#include <sstream>
#include <iostream>
#include <cstdio>

using namespace std;

namespace Ui
{

	/**
	 * Root frame object.
	 */
	class Gui : public has_slots<>
	{
		public:

			Gui( int width, int height );
			~Gui();

// Properties

			virtual Widget* bgWidget(  );
			virtual void setBgWidget( Widget* o );
			virtual Frame& fgFrame(  );
			virtual void setFgFrame( Frame* f );
			virtual Frame& topFrame(  );
			virtual void setTopFrame( Frame* f );

			virtual Widget* mouseChannelWidget(  ) const;
			virtual void setMouseChannelWidget( Widget& o );
			virtual void unsetMouseChannelWidget( Widget& o );

			virtual Popup* mouseChannelPopup(  ) const {
				return pChannelPopup;
			}
			virtual void setMouseChannelPopup( Popup* p ) {
				pChannelPopup = p;
			}

			virtual Widget* lastMouseOverWidget() {
				return pLastMouseOver;
			}

			virtual ImageObject& screen(  );
			virtual void setScreen( ImageObject* iobj );

			virtual KeyCursor& keyCursorObject(  );
			virtual void setKeyCursorObject( KeyCursor* cursor );

			virtual Clipboard& clipboard(  );
			virtual void setClipboard( Clipboard* c );

// Functions

			virtual void render(  );
			virtual void setFocusedWidget( Widget* o );
			virtual void objectDestroyed( Widget& o );

// Popups

			virtual Popup* popup( int index ) {
				return pPopups.get( index );
			}
			virtual int numPopups() {
				return pPopups.count();
			}
			virtual void addPopup( Popup* p );
			virtual void removePopup( Popup* p );

// Events

			virtual void mouseMove( int x, int y, MouseButtons mb );
			virtual void mousePressed( int x, int y, MouseButtons mb );
			virtual void mouseReleased( int x, int y, MouseButtons mb );
			virtual void keyPressed( Key k );
			virtual void keyReleased( Key k );
			virtual void timerTick(  );

			static bool objectsListSortCallback( List<UpdateWidget*>& l, int i1, int i2 );

			signal0<> onTimerTick;

		private:

			List<Popup*> pPopups;

			Widget* pBgWidget;
			Frame* pFgFrame;
			Frame* pTopFrame;

			KeyCursor* pCursorObject;
			Widget* pFocusedWidget;
			Clipboard* pClipboard;

			Widget* pLastMouseOver;
			Widget* pMousePressedWidget;
			Widget* pMouseDragWidget;
			Widget* pMouseChannelWidget;
			Popup* pChannelPopup;

			ImageObject* pScreen;

			int pLastClick;
			int pDblClickTicks;

			int pPressedX;
			int pPressedY;

			int pWidth;
			int pHeight;
	};

}

#endif
