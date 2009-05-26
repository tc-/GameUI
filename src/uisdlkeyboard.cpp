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
Implementation of the Ui::SDLKeyboard class.
*/

#include <iostream>
#include "uisdlkeyboard.h"

using namespace Ui;

SDLKeyboard::SDLKeyboard( Gui* g )
 : Keyboard( g )
{
}


SDLKeyboard::~SDLKeyboard()
{
}

void SDLKeyboard::update()
{

  SDL_Event event;
  while ( SDL_PeepEvents(&event, 1, SDL_GETEVENT, ( SDL_EVENTMASK(SDL_KEYDOWN) | SDL_EVENTMASK(SDL_KEYUP)) ) > 0 )
  {
    Key key;
    if ( event.type == SDL_KEYDOWN ) {
			cout << " -- Key Pressed" << endl;

      if ( event.key.keysym.mod != KMOD_NONE ) {
//        cout << "!!! Mod Pressed." << endl;

        if ( (event.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT ) {
          key.setLShiftPressed( true );
        } if ( (event.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT ) {
          key.setRShiftPressed( true );
        } if ( (event.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL ) {
          key.setLCtrlPressed( true );
        } if ( (event.key.keysym.mod & KMOD_RCTRL) == KMOD_RCTRL ) {
          key.setRCtrlPressed( true );
        } if ( (event.key.keysym.mod & KMOD_LALT) == KMOD_LALT ) {
          key.setLAltPressed( true );
        } if ( (event.key.keysym.mod & KMOD_RALT) == KMOD_RALT ) {
          key.setRAltPressed( true );
        } if ( (event.key.keysym.mod & KMOD_LMETA) == KMOD_LMETA ) {
          key.setLMetaPressed( true );
        } if ( (event.key.keysym.mod & KMOD_RMETA) == KMOD_RMETA ) {
          key.setRMetaPressed( true );
        } if ( (event.key.keysym.mod & KMOD_NUM) == KMOD_NUM ) {
          key.setNumlockPressed( true );
        } if ( (event.key.keysym.mod & KMOD_CAPS) == KMOD_CAPS ) {
          key.setCapslockPressed( true );
        } if ( (event.key.keysym.mod & KMOD_MODE) == KMOD_MODE ) {
          key.setModePressed( true );
        }
      }

      key.setKeysym( translateSDLKeysym( event.key.keysym.sym ) );
      key.setUnicode( event.key.keysym.unicode );

			keyPressed( key );

    } else if ( event.type == SDL_KEYUP ) {
			cout << " -- Key Released" << endl;

      key.setKeysym( translateSDLKeysym( event.key.keysym.sym ) );
      key.setUnicode( event.key.keysym.unicode );
      if ( event.key.keysym.mod != KMOD_NONE ) {
        if ( event.key.keysym.mod == KMOD_LSHIFT ) {
          key.setLShiftPressed( false );
        } if ( event.key.keysym.mod & KMOD_RSHIFT == KMOD_RSHIFT ) {
          key.setRShiftPressed( false );
        } if ( event.key.keysym.mod == KMOD_LCTRL ) {
          key.setLCtrlPressed( false );
        } if ( event.key.keysym.mod == KMOD_RCTRL ) {
          key.setRCtrlPressed( false );
        } if ( event.key.keysym.mod == KMOD_LALT ) {
          key.setLAltPressed( false );
        } if ( event.key.keysym.mod == KMOD_RALT ) {
          key.setRAltPressed( false );
        } if ( event.key.keysym.mod == KMOD_LMETA ) {
          key.setLMetaPressed( false );
        } if ( event.key.keysym.mod == KMOD_RMETA ) {
          key.setRMetaPressed( false );
        } if ( event.key.keysym.mod == KMOD_NUM ) {
          key.setNumlockPressed( false );
        } if ( event.key.keysym.mod == KMOD_CAPS ) {
          key.setCapslockPressed( false );
        } if ( event.key.keysym.mod == KMOD_MODE ) {
          key.setModePressed( false );
        }
      }
      keyReleased( key );


    }
  }
}

void SDLKeyboard::setRepeat( int delay, int interval )
{
  if ( delay != -1 ) {
    SDL_EnableKeyRepeat( delay, interval );
  } else {
    SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL );
  }
}


Keysym SDLKeyboard::translateSDLKeysym( const SDLKey ks )
{
  switch ( ks ) {
    case SDLK_BACKSPACE:
    return KEY_BACKSPACE;
    case SDLK_TAB:
    return KEY_TAB;
    case SDLK_CLEAR:
    return KEY_CLEAR;
    case SDLK_RETURN:
    return KEY_RETURN;
    case SDLK_PAUSE:
    return KEY_PAUSE;
    case SDLK_ESCAPE:
    return KEY_ESCAPE;
    case SDLK_SPACE:
    return KEY_SPACE;
    case SDLK_EXCLAIM:
    return KEY_EXCLAIM;
    case SDLK_QUOTEDBL:
    return KEY_QUOTEDBL;
    case SDLK_HASH:
    return KEY_HASH;
    case SDLK_DOLLAR:
    return KEY_DOLLAR;
    case SDLK_AMPERSAND:
    return KEY_AMPERSAND;
    case SDLK_QUOTE:
    return KEY_QUOTE;
    case SDLK_LEFTPAREN:
    return KEY_LEFTPAREN;
    case SDLK_RIGHTPAREN:
    return KEY_RIGHTPAREN;
    case SDLK_ASTERISK:
    return KEY_ASTERISK;
    case SDLK_PLUS:
    return KEY_PLUS;
    case SDLK_COMMA:
    return KEY_COMMA;
    case SDLK_MINUS:
    return KEY_MINUS;
    case SDLK_PERIOD:
    return KEY_PERIOD;
    case SDLK_SLASH:
    return KEY_SLASH;
    case SDLK_0:
    return KEY_0;
    case SDLK_1:
    return KEY_1;
    case SDLK_2:
    return KEY_2;
    case SDLK_3:
    return KEY_3;
    case SDLK_4:
    return KEY_4;
    case SDLK_5:
    return KEY_5;
    case SDLK_6:
    return KEY_6;
    case SDLK_7:
    return KEY_7;
    case SDLK_8:
    return KEY_8;
    case SDLK_9:
    return KEY_9;
    case SDLK_COLON:
    return KEY_COLON;
    case SDLK_SEMICOLON:
    return KEY_SEMICOLON;
    case SDLK_LESS:
    return KEY_LESS;
    case SDLK_EQUALS:
    return KEY_EQUALS;
    case SDLK_GREATER:
    return KEY_GREATER;
    case SDLK_QUESTION:
    return KEY_QUESTION;
    case SDLK_AT:
    return KEY_AT;
    case SDLK_LEFTBRACKET:
    return KEY_LEFTBRACKET;
    case SDLK_BACKSLASH:
    return KEY_BACKSLASH;
    case SDLK_RIGHTBRACKET:
    return KEY_RIGHTBRACKET;
    case SDLK_CARET:
    return KEY_CARET;
    case SDLK_UNDERSCORE:
    return KEY_UNDERSCORE;
    case SDLK_BACKQUOTE:
    return KEY_BACKQUOTE;
    case SDLK_a:
    return KEY_a;
    case SDLK_b:
    return KEY_b;
    case SDLK_c:
    return KEY_c;
    case SDLK_d:
    return KEY_d;
    case SDLK_e:
    return KEY_e;
    case SDLK_f:
    return KEY_f;
    case SDLK_g:
    return KEY_g;
    case SDLK_h:
    return KEY_h;
    case SDLK_i:
    return KEY_i;
    case SDLK_j:
    return KEY_j;
    case SDLK_k:
    return KEY_k;
    case SDLK_l:
    return KEY_l;
    case SDLK_m:
    return KEY_m;
    case SDLK_n:
    return KEY_n;
    case SDLK_o:
    return KEY_o;
    case SDLK_p:
    return KEY_p;
    case SDLK_q:
    return KEY_q;
    case SDLK_r:
    return KEY_r;
    case SDLK_s:
    return KEY_s;
    case SDLK_t:
    return KEY_t;
    case SDLK_u:
    return KEY_u;
    case SDLK_v:
    return KEY_v;
    case SDLK_w:
    return KEY_w;
    case SDLK_x:
    return KEY_x;
    case SDLK_y:
    return KEY_y;
    case SDLK_z:
    return KEY_z;
    case SDLK_DELETE:
    return KEY_DELETE;
    case SDLK_KP0:
    return KEY_KP0;
    case SDLK_KP1:
    return KEY_KP1;
    case SDLK_KP2:
    return KEY_KP2;
    case SDLK_KP3:
    return KEY_KP3;
    case SDLK_KP4:
    return KEY_KP4;
    case SDLK_KP5:
    return KEY_KP5;
    case SDLK_KP6:
    return KEY_KP6;
    case SDLK_KP7:
    return KEY_KP7;
    case SDLK_KP8:
    return KEY_KP8;
    case SDLK_KP9:
    return KEY_KP9;
    case SDLK_KP_PERIOD:
    return KEY_KP_PERIOD;
    case SDLK_KP_DIVIDE:
    return KEY_KP_DIVIDE;
    case SDLK_KP_MULTIPLY:
    return KEY_KP_MULTIPLY;
    case SDLK_KP_MINUS:
    return KEY_KP_MINUS;
    case SDLK_KP_PLUS:
    return KEY_KP_PLUS;
    case SDLK_KP_ENTER:
    return KEY_KP_ENTER;
    case SDLK_KP_EQUALS:
    return KEY_KP_EQUALS;
    case SDLK_UP:
    return KEY_UP;
    case SDLK_DOWN:
    return KEY_DOWN;
    case SDLK_RIGHT:
    return KEY_RIGHT;
    case SDLK_LEFT:
    return KEY_LEFT;
    case SDLK_INSERT:
    return KEY_INSERT;
    case SDLK_HOME:
    return KEY_HOME;
    case SDLK_END:
    return KEY_END;
    case SDLK_PAGEUP:
    return KEY_PAGEUP;
    case SDLK_PAGEDOWN:
    return KEY_PAGEDOWN;
    case SDLK_F1:
    return KEY_F1;
    case SDLK_F2:
    return KEY_F2;
    case SDLK_F3:
    return KEY_F3;
    case SDLK_F4:
    return KEY_F4;
    case SDLK_F5:
    return KEY_F5;
    case SDLK_F6:
    return KEY_F6;
    case SDLK_F7:
    return KEY_F7;
    case SDLK_F8:
    return KEY_F8;
    case SDLK_F9:
    return KEY_F9;
    case SDLK_F10:
    return KEY_F10;
    case SDLK_F11:
    return KEY_F11;
    case SDLK_F12:
    return KEY_F12;
    case SDLK_F13:
    return KEY_F13;
    case SDLK_F14:
    return KEY_F14;
    case SDLK_F15:
    return KEY_F15;
    case SDLK_NUMLOCK:
    return KEY_NUMLOCK;
    case SDLK_CAPSLOCK:
    return KEY_CAPSLOCK;
    case SDLK_SCROLLOCK:
    return KEY_SCROLLOCK;
    case SDLK_RSHIFT:
    return KEY_RSHIFT;
    case SDLK_LSHIFT:
    return KEY_LSHIFT;
    case SDLK_RCTRL:
    return KEY_RCTRL;
    case SDLK_LCTRL:
    return KEY_LCTRL;
    case SDLK_RALT:
    return KEY_RALT;
    case SDLK_LALT:
    return KEY_LALT;
    case SDLK_RMETA:
    return KEY_RMETA;
    case SDLK_LMETA:
    return KEY_LMETA;
    case SDLK_LSUPER:
    return KEY_LSUPER;
    case SDLK_RSUPER:
    return KEY_RSUPER;
    case SDLK_MODE:
    return KEY_MODE;
    case SDLK_COMPOSE:
    return KEY_COMPOSE;
    case SDLK_HELP:
    return KEY_HELP;
    case SDLK_PRINT:
    return KEY_PRINT;
    case SDLK_SYSREQ:
    return KEY_SYSREQ;
    case SDLK_BREAK:
    return KEY_BREAK;
    case SDLK_MENU:
    return KEY_MENU;
    case SDLK_POWER:
    return KEY_POWER;
    case SDLK_EURO:
    return KEY_EURO;
    case SDLK_UNDO:
    return KEY_UNDO;
    default: return KEY_NONE;
  }
}
