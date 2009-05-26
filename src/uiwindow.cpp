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


#include "uiwindow.h"

namespace Ui {

Window::Window()
 : WindowFrame()
{
	pResizeRL = NULL;
	pResizeTB = NULL;
	pResizeTLBR = NULL;
	pResizeTRBL = NULL;
	pActiveBorder = NULL;
	pInactiveBorder = NULL;

	pCapFont = NULL;

	pCapColor = Color( 255, 255, 255 );

	pTitleHeight = 22;
	pDoResize = 0;
	pResizeable = true;
	pResizeX = 0;
	pResizeY = 0;

	pCapAlign = halignCenter;

	pCaption = L"";

}

Window::Window( Frame* parent )
 : WindowFrame( parent )
{
	pResizeRL = NULL;
	pResizeTB = NULL;
	pResizeTLBR = NULL;
	pResizeTRBL = NULL;
	pActiveBorder = NULL;
	pInactiveBorder = NULL;

	pCapFont = NULL;

	pCapColor = Color( 255, 255, 255 );

	pTitleHeight = 22;
	pDoResize = 0;
	pResizeable = true;
	pResizeX = 0;
	pResizeY = 0;

	pCapAlign = halignCenter;

	pCaption = L"";
}


Window::~Window()
{
}

void Window::setTheme( Theme& t, const string prefix )
{
  beginUpdate();

  setBorder( t.getBorder( prefix+"window" ) );
	setTitleBorderActive( t.getBorder( prefix+"window_title_active" ) );
	setTitleBorderInactive( t.getBorder( prefix+"window_title_inactive" ) );

  setFont( t.getFont( prefix+"window" ) );
	setCaptionFont( t.getFont( prefix+"window_caption" ) );

	setFontColor( t.getColor( prefix+"window_font" ) );
	setCaptionColor( t.getColor( prefix+"window_caption_font" ) );

	setCursor( t.getCursor( prefix+"window" ) );
	setResizeCursorRL( t.getCursor( prefix+"window_rl" ) );
	setResizeCursorTB( t.getCursor( prefix+"window_tb" ) );
	setResizeCursorTRBL( t.getCursor( prefix+"window_trbl" ) );
	setResizeCursorTLBR( t.getCursor( prefix+"window_tlbr" ) );

	endUpdate();
}

Widget* Window::mouseClick(int x, int y, MouseButtons mb)
{
    return WindowFrame::mouseClick(x, y, mb);
}

Widget* Window::mouseDblClick(int x, int y, MouseButtons mb)
{
    return WindowFrame::mouseDblClick(x, y, mb);
}

Widget* Window::mouseMove(int x, int y, MouseButtons mb)
{
	if ( isResizing() ) {
		if ( pDoResize == 1 ) {
			setBounds( relativeLeft() + ( x - pResizeX ), relativeTop() + ( y - pResizeY ), width() - ( x - pResizeX ), height() - ( y - pResizeY ) );
		} else if ( pDoResize == 2 ) {
			setBounds( relativeLeft(), relativeTop() + ( y - pResizeY ), width(), height() - ( y - pResizeY ) );
		} else if ( pDoResize == 3 ) {
			//cout << "x: " << ( x - pResizeX - width() ) << endl;
			setBounds( relativeLeft(), relativeTop() + ( y - pResizeY ), width() + ( x - pResizeX - clientVisibleWidth() ), height() - ( y - pResizeY ) );
		} else if ( pDoResize == 4 ) {
			setWidth( width() + ( x - width() ) );
			updated();
		} else if ( pDoResize == 5 ) {
			resize( width() + ( x - width() ), height() + ( y - height() ) );
		} else if ( pDoResize == 6 ) {
			setHeight( height() + ( y - height() ) );
		} else if ( pDoResize == 7 ) {
			setBounds( relativeLeft() + x, relativeTop(), width() - x, height() + ( y - height() ) );
		} else if ( pDoResize == 8 ) {
			setBounds( relativeLeft() + x, relativeTop(), width() - x, height() );
		}

		return this;
	} else {
		int area = resizeArea( x, y );
		if ( area != 0 ) {
			return this;
		}
	}
  return WindowFrame::mouseMove(x, y, mb);
}

Widget* Window::mousePressed(int x, int y, MouseButtons mb)
{
	if ( pDoResize != 0 ) return this;
	int area = resizeArea( x, y );
	if ( area != 0 ) {
		pDoResize = area;
		pResizeX = x;
		pResizeX = y;
		grabMouseInput();
		moveToTop();
		return this;
	}
  return WindowFrame::mousePressed(x, y, mb);
}

Widget* Window::mouseReleased(int x, int y, MouseButtons mb)
{
	if ( pDoResize != 0 ) {
	  releaseMouseInput();
		pDoResize = 0;
		return this;
	}
  return WindowFrame::mouseReleased(x, y, mb);
}


void Window::sizeChanged( const Rect& news )
{
	arrangeChildren();
	Widget::sizeChanged( news );
}

int Window::resizeArea( const int& x, const int& y )
{
	if ( Rect::pointInside( Rect( 0, 0, width(), height() ), x, y ) ) {
		if ( !Rect::pointInside( Rect( borderLeft(), WindowFrame::borderTop(), clientVisibleWidth(), clientVisibleHeight() + pTitleHeight - WindowFrame::borderTop() ), x, y ) ) {
			if ( x < 16 ) {
				if ( y < 16 )
					return 1;
				else if ( y > height() - 16 )
					return 7;
				else
					return 8;
			} else if ( x > width() - 16 ) {
				if ( y < 16 )
					return 3;
				else if ( y > height() - 16 )
					return 5;
				else
					return 4;
			} else {
				if ( y < 16 )
					return 2;
				else if ( y > height() - 16 )
					return 6;
			}
		}
	}
	return 0;
}

MouseCursor* Window::getCursorFromArea( const int& a )
{
	if ( a == 1 )
		return pResizeTRBL;
	else if ( a == 2 )
		return pResizeTB;
	else if ( a == 3 )
		return pResizeTLBR;
	else if ( a == 4 )
		return pResizeRL;
	else if ( a == 5 )
		return pResizeTRBL;
	else if ( a == 6 )
		return pResizeTB;
	else if ( a == 7 )
		return pResizeTLBR;
	else if ( a == 8 )
		return pResizeRL;
	return cursor();
}

Border* Window::titleBorder() const
{
	if ( pActiveBorder != NULL )
		return pActiveBorder;
	else
		return border();
}

void Window::render( ImageObject& img, const Rect& r )
{
	if ( !visible() ) return;
	if ( pTitleHeight > 0 ) {
		Border* b = titleBorder();
		if ( b != NULL )
			b->render( Rect( 0-borderLeft(), 0-borderTop(), width(), pTitleHeight ), img );
	}
	Font* f = captionFont();
	if ( (pCaption != L"") && (f != NULL) ) {
		img.outText( pCaption, *f, Utils::align( width() - borderLeft() - borderRight(), f->textWidth( pCaption ), pCapAlign ), 0-borderTop()+Utils::align( pTitleHeight, f->textHeight(), alignCenter ), pCapColor );

	}
	WindowFrame::render( img, r );
}
/*
Rect Window::getClientRect()
{
	Rect r ( borderLeft(), borderTop(), clientWidth(), clientHeight() );
	return r;
}
*/
/*Rect Window::getClientVisibleRect()
{
	Rect r ( borderLeft(), borderTop(), clientVisibleWidth(), clientVisibleHeight() );
	return r;
}*/

int Window::clientVisibleWidth( )
{
	return width() - borderLeft() - borderRight();
}

int Window::clientVisibleHeight( )
{
	return height() - borderTop() - borderBottom();
}

}
