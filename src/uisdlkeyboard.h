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

/**
@file
Headerfile for the Ui::SDLKeyboard class.
*/

#ifndef UISDLKEYBOARD_H
#define UISDLKEYBOARD_H

#include <uikeyboard.h>
#include "SDL.h"

namespace Ui {

/**
Ui::Keyboard class using SDL for input.

@author Tommy Carlsson
*/
class SDLKeyboard : public Keyboard
{
public:
  SDLKeyboard( Gui* g = NULL );
  ~SDLKeyboard();

  void update();
  void setRepeat( int delay = 0, int interval = 0 );

  Keysym translateSDLKeysym( const SDLKey ks );

};

}

#endif
