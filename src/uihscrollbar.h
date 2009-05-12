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
#ifndef UIUIHSCROLLBAR_H
#define UIUIHSCROLLBAR_H

#include <gameui.h>
#include <uiwidget.h>
#include <uigui.h>
#include <uiborder.h>

namespace Ui {

/**
Horisontal scrollbar

@author Tommy Carlsson
*/
class HScrollbar : public Widget
{
public:
  int scrollBy;
  int scrollDelay;

  HScrollbar( Frame* parent );
  ~HScrollbar();

  virtual void setTheme( Theme & t, const string prefix = "" );

  virtual ImageObject* rButtonGlyph() const;
  virtual void setRButtonGlyph( ImageObject* img );

  virtual ImageObject* lButtonGlyph() const;
  virtual void setLButtonGlyph( ImageObject* img );

  virtual Border* buttonBorder() const;
  virtual void setButtonBorder( Border* b );

  virtual Border* buttonPressedBorder() const;
  virtual void setButtonPressedBorder( Border* b );

  virtual Border* scrollerBorder() const;
  virtual void setScrollerBorder( Border* b );

  virtual Border* scrollerPressedBorder() const;
  virtual void setScrollerPressedBorder( Border* b );


  virtual int scrollerPos() const;
  virtual void setScrollerPos( const int pos );

  virtual int scrollerMaxPos() const;
  virtual void setScrollerMaxPos( const int mp );

  virtual int scrollerMinWidth() const;
  virtual void setScrollerMinWidth( const int mh );

  virtual int pageSize() const;
  virtual void setPageSize( const int ps );

  virtual Widget* keyPressed(Key key);
  virtual Widget* keyReleased(Key key);
  virtual Widget* mouseClick(int x, int y, MouseButtons mb);
  virtual Widget* mouseIn(MouseButtons mb);
  virtual Widget* mouseMove(int x, int y, MouseButtons mb);
  virtual Widget* mouseOut(MouseButtons mb);
  virtual Widget* mousePressed(int x, int y, MouseButtons mb);
  virtual Widget* mouseReleased(int x, int y, MouseButtons mb);

  virtual void render( ImageObject& img, const Rect& r );

  virtual void setHeight(int h);
  virtual void setWidth(int w);

  virtual void scrollLeft();
  virtual void scrollRight();
  virtual void scroll( const int delta );

  signal2<Widget*,int> onScroll;


private:

  ImageObject* pRButtonGlyph;
  ImageObject* pLButtonGlyph;

  Border* pButtonBorder;
  Border* pButtonPressedBorder;
  Border* pScrollerBorder;
  Border* pScrollerPressedBorder;

  int pScrollerPos;
  int pScrollerMaxPos;
  int pScrollerMinWidth;
  int pPageSize;

  int pScrollWait;

  int pScrollerPressed;
  bool pButtonRightPressed;
  bool pButtonLeftPressed;

  int scrollArea() const;
  int scrollerSize() const;
  int scrollerLeft() const;
  int elementAt( const int x, const int y ) const;

  void timerTick( );

};

}

#endif
