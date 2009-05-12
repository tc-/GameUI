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
#include "uisdlcontrol.h"
#include "uitimer.h"
#include "uisdltimercontrol.h"

namespace Ui {


SDLControl::SDLControl( Gui* g )
{
  setGui( g );
  pTerminated = false;
  pKeyboard.setRepeat( -1 );
	
}


SDLControl::~SDLControl()
{
}


void SDLControl::setGui( Gui* g )
{
  LibControl::setGui( g );
  pKeyboard.setGui( g );
  pMouse.setGui( g );
}

bool SDLControl::initializeLibrary()
{
  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "Error: %s\n", SDL_GetError() );
    return false;
  }
	
  if( TTF_Init() == -1 ) {
    printf( "Error: %s\n", TTF_GetError() );
    return false;
  }
  SDL_EnableUNICODE( 1 );

	ImageObject::setObjectFactory( &SDLImageObject::sdlImageObjectFactory );
	
	TimerControl::setCreateTimerControl( &SDLTimerControl::createTimerControl );
	TimerControl::setDestroyTimerControl( &SDLTimerControl::destroyTimerControl );
	
	MouseCursor::setMouseCursorFactory( &SDLMouseCursor::createSDLMouseCursor );
	
	Font::setFontFactory( &SDLFont::sdlFontFactory );
	
  return true;
}


bool SDLControl::finalizeLibrary()
{
	if ( ImageObject::objectFactory() == &SDLImageObject::sdlImageObjectFactory ) {
		ImageObject::setObjectFactory( NULL );
	}
  SDL_Quit();
  return true;
}


ImageObject* SDLControl::createScreen( const int& width, const int& height, const int& bpp, const ScreenFlags& flags, const bool& assign )
{
  SDL_Surface *newScreen;
  Uint32 f = 0;

  if ( (flags & SF_FULLSCREEN) == SF_FULLSCREEN )
    f = (flags | SDL_FULLSCREEN);
  if ( (flags & SF_SWSURFACE) == SF_SWSURFACE )
    f = (flags | SDL_SWSURFACE);
  if ( (flags & SF_HWSURFACE) == SF_HWSURFACE )
    f = (flags | SDL_HWSURFACE);
  if ( (flags & SF_DOUBLEBUF) == SF_DOUBLEBUF )
    f = (flags | SDL_DOUBLEBUF);
  if ( (flags & SF_NOFRAME) == SF_NOFRAME )
    f = (flags | SDL_NOFRAME);
  if ( (flags & SF_RESIZABLE) == SF_RESIZABLE )
    f = (flags | SDL_RESIZABLE);
//  if ( (flags & SF_) == SF_ )
//    f = (flags | SDL_);

  newScreen = SDL_SetVideoMode( width, height, bpp, f );
  if ( newScreen == NULL )
  {
    printf("Error: %s\n", SDL_GetError());
    exit(3);
  }
  SDLImageObject* imScreen = new SDLImageObject();
  imScreen->assignSurface( newScreen );
  if ( assign )
    setScreen( (ImageObject*) imScreen );
  return (ImageObject*) imScreen;
}


Keyboard& SDLControl::keyboard()
{
  return pKeyboard;
}


Mouse& SDLControl::mouse()
{
  return pMouse;
}


void SDLControl::doHandleEvents( const bool& clearEvs )
{
  SDL_PumpEvents();
//  Uint32 f = 0;
  if ( handleKeyboardEvents() ) {
//    f = ( f | ( SDL_EVENTMASK(SDL_KEYDOWN) | SDL_EVENTMASK(SDL_KEYUP) ) );
    keyboard().update();
  }

  if ( handleMouseEvents() ) {
//    f = ( f | ( SDL_EVENTMASK(SDL_MOUSEBUTTONDOWN) | SDL_EVENTMASK(SDL_MOUSEBUTTONUP) | SDL_EVENTMASK(SDL_MOUSEMOTION) ) );
    mouse().update();
  }

  if ( handleSysEvents() ) {
//    f = ( f | ( SDL_EVENTMASK(SDL_QUIT) | SDL_EVENTMASK(SDL_ACTIVEEVENT ) | SDL_EVENTMASK(SDL_SYSWMEVENT) | 
//        SDL_EVENTMASK(SDL_VIDEORESIZE) | SDL_EVENTMASK(SDL_VIDEOEXPOSE) ) );

    SDL_Event event;
    while ( SDL_PeepEvents(&event, 1, SDL_GETEVENT, ( SDL_EVENTMASK(SDL_QUIT) | SDL_EVENTMASK(SDL_ACTIVEEVENT ) | SDL_EVENTMASK(SDL_SYSWMEVENT) | 
            SDL_EVENTMASK(SDL_VIDEORESIZE) | SDL_EVENTMASK(SDL_VIDEOEXPOSE) ) ) > 0 ) {
      if ( event.type == SDL_QUIT ) {
        pTerminated = true;
        onQuit();
      } else if ( event.type == SDL_VIDEORESIZE ) {
        onResize( event.resize.w, event.resize.h );
      }
    }
  }

	if ( handleTimers() ) {
		SDLTimerControl::handleSDLTimers();
	}
	
  if ( clearEvs )
    SDLControl::clearEvents();
}


void SDLControl::clearEvents(  )
{
  SDL_Event event;
  while ( SDL_PollEvent(&event) ) {
		cout << ".";
	}
}


void SDLControl::clearKeyboardEvents()
{
  SDL_Event event;
  while ( SDL_PeepEvents(&event, 1, SDL_GETEVENT, ( SDL_EVENTMASK(SDL_KEYDOWN) | SDL_EVENTMASK(SDL_KEYUP) ) ) > 0 ) { }
}


void SDLControl::clearMouseEvents()
{
  SDL_Event event;
  while ( SDL_PeepEvents(&event, 1, SDL_GETEVENT, ( SDL_EVENTMASK(SDL_MOUSEBUTTONDOWN) | SDL_EVENTMASK(SDL_MOUSEBUTTONUP) | SDL_EVENTMASK(SDL_MOUSEMOTION) ) ) > 0 ) { }
}


void SDLControl::clearSysEvents()
{
  SDL_Event event;
  while ( SDL_PeepEvents(&event, 1, SDL_GETEVENT, ( SDL_EVENTMASK(SDL_QUIT) | SDL_EVENTMASK(SDL_ACTIVEEVENT ) | SDL_EVENTMASK(SDL_SYSWMEVENT) |  SDL_EVENTMASK(SDL_VIDEORESIZE) | SDL_EVENTMASK(SDL_VIDEOEXPOSE) ) ) > 0 ) { }
}


void SDLControl::sleep( const unsigned int& msecs )
{
	//SDL_Delay( msecs );
	Uint32 first = SDL_GetTicks();
	while( SDL_GetTicks() - first < msecs ) {
		SDLTimerControl::handleSDLTimers();
		SDL_Delay( 1 );
	}
//	Uint32 sd = ( (SDL_GetTicks() - first) - msecs );
//	if ( sd > 5 )
//		cout << " -- Sleep Drift: " << sd << endl;
}

void SDLControl::flip( const bool conditional )
{
  SDLImageObject* is = (SDLImageObject*)screen();
  if ( is != NULL )
    is->flip( conditional );
}

bool SDLControl::terminated()
{
  return pTerminated;
}


}
