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


#ifndef UIUITABVIEW_H
#define UIUITABVIEW_H

#include <uiframe.h>
#include <uiutils.h>
#include <uiborder.h>

namespace Ui {

/**
A tab view Widget.

	@author Tommy Carlsson <tc@coderworld.net>
*/
class TabView : public Frame
{
  public:

    TabView(Frame* parent = NULL );
    virtual ~TabView();

//    virtual Rect getClientVisibleRect();
		virtual int clientVisibleHeight();

    virtual Widget* mouseClick(int x, int y, MouseButtons mb);

    virtual void setTheme(Theme& t, const string prefix = "");

		virtual void render( ImageObject& img, const Rect& r );

		virtual void tabsUpdated() { updated(); }

		virtual int tabHeight() { return pTabHeight; }
		virtual void tabHeight( int th ) { pTabHeight = th; updated(); }

		virtual void setTabButtonBorder( Border* b ) { pTabButton = b; tabsUpdated(); }
		virtual Border* tabButtonBorder() { if ( pTabButton != NULL ) return pTabButton; else return pTabButtonActive; }
		virtual void setTabButtonActiveBorder( Border* b )  { pTabButtonActive = b; tabsUpdated(); }
		virtual Border* tabButtonActiveBorder() { if ( pTabButtonActive != NULL ) return pTabButtonActive; else return pTabButton; }

		virtual Widget* activeTab() { return pActiveTab; }
		virtual void setActiveTab( Widget* w );


		virtual int borderTop () const;

		virtual Widget* mouseMove( int x, int y, MouseButtons mb );
		virtual Widget* mousePressed( int x, int y, MouseButtons mb );
		virtual Widget* mouseReleased( int x, int y, MouseButtons mb );
		virtual Widget* mouseIn( MouseButtons mb );
		virtual Widget* mouseOut( MouseButtons mb );

  private:

		Widget* pActiveTab;
		Border* pTabButton;
		Border* pTabButtonActive;
		int pTabHeight;
		Widget* pButtonPressed;
		bool pMouseInside;

	protected:

		virtual Widget* getTabButtonAt( const int x );
		virtual void childAdded( Widget* o );

};

}

#endif
