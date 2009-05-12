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
#ifndef UIUIWINDOW_H
#define UIUIWINDOW_H

#include <uiwindowframe.h>
#include <uiborder.h>
#include <string>

using namespace std;

namespace Ui {

enum HAlignment {
  AL_RIGHT,
  AL_LEFT,
  AL_CENTER
};

enum VAlignment {
  AL_TOP,
  AL_BOTTOM,
  AL_MIDDLE
};

/**
Window class

@author Tommy Carlsson
*/
class Window : public WindowFrame
{
public:
  Window();
  Window( Frame* parent );

  ~Window();

  virtual void setTheme( Theme& t, const string prefix = "" );

  virtual Widget* mouseClick(int x, int y, MouseButtons mb);
  virtual Widget* mouseDblClick(int x, int y, MouseButtons mb);
  virtual Widget* mouseMove(int x, int y, MouseButtons mb);
  virtual Widget* mousePressed(int x, int y, MouseButtons mb);
  virtual Widget* mouseReleased(int x, int y, MouseButtons mb);

	virtual MouseCursor* getCursor( const int& x, const int& y )
	{ 
		return getCursorFromArea( resizeArea( x, y ) ); 
	}
	
	virtual void sizeChanged( const Rect& news );
			
	virtual bool resizable() { return pResizeable; }
	virtual void setResizeable( const bool& r = true ) { pResizeable = r; }
	
	virtual bool isResizing() { return ( pDoResize != 0 ); }
	
	virtual MouseCursor* resizeCursorRL() { return pResizeRL; }
	virtual void setResizeCursorRL( MouseCursor* mc ) { pResizeRL = mc; }
	virtual MouseCursor* resizeCursorTB() { return pResizeTB; }
	virtual void setResizeCursorTB( MouseCursor* mc ) { pResizeTB = mc; }
	virtual MouseCursor* resizeCursorTRBL() { return pResizeTRBL; }
	virtual void setResizeCursorTRBL( MouseCursor* mc ) { pResizeTRBL = mc; }
	virtual MouseCursor* resizeCursorTLBR() { return pResizeTLBR; }
	virtual void setResizeCursorTLBR( MouseCursor* mc ) { pResizeTLBR = mc; }

  //virtual void updateRegion(const Rect& r);

	//TODO Should know when the window is active.
	virtual Border* titleBorder() const;
	virtual Border* titleBorderActive() const { return pActiveBorder; }
	virtual Border* titleBorderInactive() const { return pInactiveBorder; }
	virtual void setTitleBorderActive( Border* b ) { pActiveBorder = b; updated(); }
	virtual void setTitleBorderInactive( Border* b ) { pActiveBorder = b; updated(); }

	virtual int titleHeight( ) const { return pTitleHeight; };
	virtual void setTitleHeight( const int th ) { pTitleHeight = th; updated(); }
	
	virtual wstring caption() const { return pCaption; }
	virtual void setCaption( wstring c ) { pCaption = c; }

	virtual Font* captionFont() const { if ( pCapFont != NULL ) return pCapFont; else return font(); }
	virtual void setCaptionFont( Font* f ) { pCapFont = f; updated(); }

	virtual Color captionColor() const { return pCapColor; }
	virtual void setCaptionColor( const Color c ) { pCapColor = c; updated(); }
	
	virtual HAlignType captionAlignment() const { return pCapAlign; }
	virtual void setCaptionAlignment( HAlignType al ) { pCapAlign = al; updated();}

	virtual int borderTop( ) const { if ( pTitleHeight > WindowFrame::borderTop() ) return pTitleHeight; else return WindowFrame::borderTop(); }
//	virtual int clientHeight( ) { return WindowFrame::clientHeight() - pTitleHeight + WindowFrame::borderTop(); }
	
	virtual int clientVisibleWidth( );
	virtual int clientVisibleHeight( );
	
//	virtual Rect getClientRect();
//	virtual Rect getClientVisibleRect();
	
	virtual void render( ImageObject& img, const Rect& r );
	
//  virtual Rect getClientRect();

private:

	int resizeArea( const int& x, const int& y );
	MouseCursor* getCursorFromArea( const int& a );
	
	MouseCursor* pResizeRL;
	MouseCursor* pResizeTB;
	MouseCursor* pResizeTLBR;
	MouseCursor* pResizeTRBL;
	
	Font* pCapFont;
	
	Border* pActiveBorder;
	Border* pInactiveBorder;
	
	Color pCapColor;
	
	bool pResizeable;
	
	int pDoResize;
	int pResizeX;
	int pResizeY;
	int pTitleHeight;
	
	HAlignType pCapAlign;
	
	wstring pCaption;
	
};

}

#endif
