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


#ifndef UIWINDOWFRAME_H
#define UIWINDOWFRAME_H

#include <uiframe.h>
#include <uigui.h>

namespace Ui {

/**
Frame control behaving like a window.

@author Tommy Carlsson
*/
class WindowFrame : public Frame
{
public:
  WindowFrame();
  WindowFrame( Frame* parent );

  virtual ~WindowFrame();

  virtual void setTheme( Theme& t, const string prefix = "" );


  virtual void renderBackground(const Rect& r);
 // virtual void updateRegion(const Rect& r);

  virtual Widget* mouseClick(int x, int y, MouseButtons mb);
  virtual Widget* mouseDblClick(int x, int y, MouseButtons mb);
  virtual Widget* mousePressed(int x, int y, MouseButtons mb);
  virtual Widget* mouseReleased(int x, int y, MouseButtons mb);
  virtual Widget* mouseMove( int x, int y, MouseButtons mb );

private:

  int pLastMouseX;
  int pLastMouseY;
  bool pLeftMouseDown;

};

}

#endif
