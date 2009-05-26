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


#ifndef UIUITOOLTIP_H
#define UIUITOOLTIP_H

#include <uipopup.h>
#include <uigui.h>

namespace Ui {

/**
Popup used with Tooltips.

	@author Tommy Carlsson <tc@coderworld.net>
*/
class Tooltip : public Popup
{
public:

  Tooltip();
  ~Tooltip();

	virtual wstring text() const { return pText; }
	virtual void setText( wstring t ) { pText = t; doAutoResize(); updated(); }

	virtual bool autoResize(  ) const { return pAutoResize; }
	virtual void setAutoResize( const bool ar ) { pAutoResize = ar; }

	virtual Font* font(  ) const { return pFont; }
	virtual void setFont( Font* f ) { pFont = f; doAutoResize(); updated(); }

	virtual Color fontColor(  ) const { return pFontColor; }
	virtual void setFontColor( Color c ) { pFontColor = c; updated(); }
	//virtual void setText( wstring s, const bool autoresize = false );

  virtual bool passEvents();
  virtual void mousePressed(int x, int y, MouseButtons mb);
  virtual void render(Rect area);
  virtual void setTheme(Theme& t, const string prefix = "" );

	virtual void doAutoResize();

private:

	wstring pText;
	Font* pFont;
	Color pFontColor;
	bool pPressed;
	bool pAutoResize;

};

}

#endif
