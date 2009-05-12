/***************************************************************************
 *   Copyright (C) 2005 by Tommy Carlsson   *
 *   tc@coderworld.net   *
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

/**
@file
Headerfile for the Ui::PushButton class
*/

#ifndef UIPUSHBUTTON_H
#define UIPUSHBUTTON_H

#include <gameui.h>
#include <sigslot.h>
#include <uiwidget.h>
#include <uiborder.h>
#include <uiimageobject.h>

namespace Ui {

/**
Basic button class

@author Tommy Carlsson
*/
class PushButton : public Widget
{
public:
  PushButton();
  PushButton( Frame* parent );
	/*
	setReleasedBorder( t.getBorder( prefix+"pushbutton_released" ) );
	setPressedBorder( t.getBorder( prefix+"pushbutton_pressed" ) );
	setFont( t.getFont( prefix+"pushbutton" ) );
	setFontColor( t.getColor( prefix+"pushbutton_font" ) );
	setImage( t.getImage( prefix+"pushbutton" ) );
	*/
  /**
   * Assigns a theme to the button.
	 * border.pushbutton_released: Border to use when button is released.@n
	 * border.pushbutton_pressed: Border to use when button is pressed.@n
	 * font.pushbutton: the font to use.@n
	 * color.pushbutton_font: The font color to use.@n
	 * image.pushbutton: Image to use as glyph.
	 * @see Widget::setTheme()
   */
  virtual void setTheme( Theme& t, const string prefix = "" );

  virtual bool pressed();
  virtual wstring text();
  virtual void setText( wstring s );

  virtual ImageObject* image(  ) { return pImage; }
  virtual void setImage( ImageObject* img ) { pImage = img; updated(); }

  virtual Border* pressedBorder();
  virtual void setPressedBorder( Border* bs );
  virtual Border* releasedBorder();
  virtual void setReleasedBorder( Border* bs );

  virtual void buttonPressed();
  virtual Widget* keyPressed( Key key );
  virtual Widget* mouseClick(int x, int y, MouseButtons mb);
  virtual Widget* mouseIn(MouseButtons mb);
  virtual Widget* mouseOut(MouseButtons mb);
  virtual Widget* mousePressed(int x, int y, MouseButtons mb);
  virtual Widget* mouseReleased(int x, int y, MouseButtons mb);


  virtual void render( ImageObject& img, const Rect& r );

  signal1<PushButton&> onButtonPressed;

private:

  wstring pText;
  bool pPressed;
  Border* pPressedBorder;
  Border* pReleasedBorder;
  ImageObject* pImage;

};

}

#endif
