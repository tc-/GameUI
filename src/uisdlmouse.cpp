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


#include "uisdlmouse.h"

namespace Ui {

void SDLMouseCursor::load( ImageObject& img, const int& hotspotX, const int& hotspotY, const Color& transparentColor, const Color& invertColor )
{
	if ( imageIsSystemCursor( &img ) ) {

		Uint8* data = new Uint8[ (int)ceil( (double)(img.width() * img.height()) / 8 ) ];
		Uint8* mask = new Uint8[ (int)ceil( (double)(img.width() * img.height()) / 8 ) ];

		int bit = 1;
		int i = -1;

		Color black( 0, 0, 0 );
		Color white( 255, 255, 255 );
		//cout << "Cursor:" << endl;
		for( int y = 0; y < img.height(); y++ ) {
			for( int x = 0; x < img.width(); x++ ) {
				Color c = img.getPixel( x, y );

				if ( bit == 128 ) {
					bit = 64;
				}
				else if ( bit == 64 )
					bit = 32;
				else if ( bit == 32 )
					bit = 16;
				else if ( bit == 16 )
					bit = 8;
				else if ( bit == 8 )
					bit = 4;
				else if ( bit == 4 )
					bit = 2;
				else if ( bit == 2 )
					bit = 1;
				else if ( bit == 1 ) {
					bit = 128;
					i++;
					data[i] = 0;
					mask[i] = 0;
				}

				if ( c == white ) {
					//cout << ".";
					mask[i] |= bit;
				} else if ( c == black ) {
					//cout << "X";
					data[i] |= bit;
					mask[i] |= bit;
				} else if ( c == invertColor ) {
					//cout << "0";
					data[i] |= bit;
				} else {
					//cout << " ";
				}
			}
			//cout << endl;
		}
		pCursor = SDL_CreateCursor( data, mask, img.width(), img.height(), hotspotX, hotspotY );

		delete[] mask;
		delete[] data;

	} else {
	}
}

bool SDLMouseCursor::isLoaded()
{
	return ( ( pCursor != NULL ) || ( pImage != NULL ) );
}

bool SDLMouseCursor::imageIsSystemCursor( ImageObject* img )
{
	return true;
}


MouseCursor* SDLMouseCursor::createSDLMouseCursor()
{
	return (MouseCursor*)new SDLMouseCursor();
}


SDLMouse::SDLMouse( Gui* g ): Mouse( g )
{
	pCursor = NULL;
	pLastMouseOver = NULL;
}


SDLMouse::~SDLMouse()
{
}


MouseButtons SDLMouse::mouseButtons()
{
  SDL_PumpEvents();
  int x, y;
  return translateMouseButtons( SDL_GetRelativeMouseState( &x, &y ) );
}

void SDLMouse::mousePos(int& x, int& y)
{
  SDL_PumpEvents();
	SDL_GetMouseState( &x, &y);

//  SDL_GetRelativeMouseState( &x, &y );
}


void SDLMouse::update()
{
  SDL_Event event;

	SDL_PumpEvents();

  while ( SDL_PeepEvents(&event, 1, SDL_GETEVENT, ( SDL_EVENTMASK(SDL_MOUSEBUTTONDOWN) | SDL_EVENTMASK(SDL_MOUSEBUTTONUP) | SDL_EVENTMASK(SDL_MOUSEMOTION) ) ) > 0  )
  {
    if ( event.type == SDL_MOUSEBUTTONDOWN ) {
			cout << endl << " [EE] Mouse Pressed";
			if ( gui() != NULL ) {
				cout << " gui";
        gui()->mousePressed( event.button.x, event.button.y, translateMouseButtons( event.button.button ) );
			}
			cout << endl;
      onMousePressed( event.button.x, event.button.y, translateMouseButtons( event.button.button ) );

    } else if ( event.type == SDL_MOUSEBUTTONUP ) {
			cout << " [EE] Mouse Released" << endl << endl;
			if ( gui() != NULL ) {
				cout << " gui";
				gui()->mouseReleased( event.button.x, event.button.y, translateMouseButtons( event.button.button ) );
			}
			cout << endl;
			onMouseReleased( event.button.x, event.button.y, translateMouseButtons( event.button.button ) );

    } else if ( event.type == SDL_MOUSEMOTION ) {
      if ( gui() != NULL )
        gui()->mouseMove( event.button.x, event.button.y, translateMouseButtons( event.button.button ) );
      onMouseMove( event.button.x, event.button.y, translateMouseButtons( event.button.button ) );

    }

  }
	if ( gui() != NULL ) {
		Widget* w = gui()->lastMouseOverWidget();
		if ( w != NULL ) {
			int x, y;
			mousePos( x, y );
			MouseCursor* mc = w->getCursor( x - w->absoluteXPos(), y - w->absoluteYPos() );
			if ( mc != (MouseCursor*)pCursor ) {
				setCursor( mc );
			}
		}
/*		if ( gui()->lastMouseOverWidget() != pLastMouseOver ) {
			pLastMouseOver = gui()->lastMouseOverWidget();
			if ( pLastMouseOver != NULL ) {
				if ( (MouseCursor*)pCursor != pLastMouseOver->cursor() )
					setCursor( pLastMouseOver->cursor() );
			}
	}*/
	}

}

MouseButtons SDLMouse::translateMouseButtons( const Uint8& sdlButton )
{
  MouseButtons mb = MBT_NONE;
  switch ( sdlButton ) {
    case SDL_BUTTON_LEFT :
      mb = ( mb | MBT_LEFT );
      break;
    case SDL_BUTTON_MIDDLE :
      mb = ( mb | MBT_MIDDLE );
      break;
    case SDL_BUTTON_RIGHT:
      mb = ( mb | MBT_RIGHT );
      break;
    case SDL_BUTTON_WHEELUP:
      mb = ( mb | MBT_WHEELUP );
      break;
    case SDL_BUTTON_WHEELDOWN:
      mb = ( mb | MBT_WHEELDOWN );
      break;
  }
  return mb;
}

MouseCursor* SDLMouse::cursor()
{
	return (MouseCursor*)pCursor;
}

void SDLMouse::setCursor( MouseCursor* mc )
{
	pCursor = (SDLMouseCursor*)mc;

	if ( pCursor != NULL ) {
		if ( pCursor->isSystem() ) {
			SDL_SetCursor( pCursor->getSDLCursorObject() );
		} else {
		}
	}

}



}
