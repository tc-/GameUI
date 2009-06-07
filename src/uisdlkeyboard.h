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
 * @file
 * Headerfile for the Ui::SDLKeyboard class.
*/

#ifndef UISDLKEYBOARD_H
#define UISDLKEYBOARD_H

#include <uikeyboard.h>
#include "SDL.h"

namespace Ui
{

	/**
	 * Keyboard class using SDL for input.
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
