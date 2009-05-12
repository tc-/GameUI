/***************************************************************************
 *   Copyright (C) 2005 by Tommy Carlsson                                      *
 *   tc@coderworld.net                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
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
