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
@file
Header and implementationfile for the Ui::Keyboard class.
*/

#ifndef UIKEYBOARD_H
#define UIKEYBOARD_H

#include <gameui.h>
#include <uigui.h>
#include <uikey.h>
#include <sigslot.h>

namespace Ui {

/**
Abstract class used to implement a keyboard control.

@author Tommy Carlsson
*/
class Keyboard : public has_slots<>
{
public:
  Keyboard( Gui* g = NULL ) { pGui = g; };
  virtual ~Keyboard() {  };

  virtual void update() = 0;

  /**
   * Sets the repeat values for the keyboard.
   * If not called keyboard repeat will be disabled.
   * @note If you set delay to 0, repeat will be disabled.
   * @note If you set delay to -1, default values will be assigned.
   * @param delay the delay in ms.
   * @param interval the interval in ms.
   */
  virtual void setRepeat( int delay = 0, int interval = 0 ) = 0;

  virtual Gui* gui() {  return pGui; }
  virtual void setGui( Gui* s ) {  pGui = s; }

  virtual void keyPressed( Key k ) {
    if ( gui() != NULL ) {
      gui()->keyPressed( k );
    }
    onKeyPressed( k );
  }

  virtual void keyReleased( Key k ) {
    if ( gui() != NULL ) {
      gui()->keyReleased( k );
    }
    onKeyReleased( k );
  }

  signal1< Key > onKeyPressed;
  signal1< Key > onKeyReleased;

private:
  Gui* pGui;

};

}

#endif
