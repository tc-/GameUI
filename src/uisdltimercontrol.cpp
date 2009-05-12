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
#include "uisdltimercontrol.h"
#include "SDL.h"

namespace Ui {

List<Timer*> SDLTimerControl::pTimers;

SDLTimerControl::SDLTimerControl()
 : TimerControl()
{
}


SDLTimerControl::~SDLTimerControl()
{
}


TimerControl* SDLTimerControl::createTimerControl()
{
	return defaultSDlTimerControl();
}

long int SDLTimerControl::getTimeLeft( Timer* t )
{
	if ( t == NULL ) return -1;
	if ( t->tcTag() == NULL ) {
		Uint32* tmp = new Uint32;
		t->setTCTag( (void*)tmp );
		*tmp = SDL_GetTicks();
		return t->timeout();
	} else {
		Uint32* tmp = (Uint32*)t->tcTag();
		return t->timeout() - ( SDL_GetTicks() - *tmp );
	}
}

void SDLTimerControl::timerTicked( Timer* t )
{
	if ( t == NULL ) return;
	if ( t->tcTag() == NULL ) {
		Uint32* tmp = new Uint32;
		t->setTCTag( (void*)tmp );
		*tmp = SDL_GetTicks();
	} else {
		Uint32* tmp = (Uint32*)t->tcTag();
		*tmp = SDL_GetTicks();
	}
}

void SDLTimerControl::assignTimer( Timer* t )
{
	pTimers.append( t );
}
 
void SDLTimerControl::removeTimer( Timer* t )
{
/*	list<Timer*>::iterator i;
	for( i = pTimers.begin(); i != pTimers.end(); ++i ) {
		if ( *i == t ) {
		  pTimers.erase( i );
			break;
		}
	}*/
	pTimers.remove( pTimers.getIndex( t ) );
	if ( t != NULL ) {
		if ( t->tcTag() != NULL ) delete (Uint32*)t->tcTag();
		t->setTCTag( NULL );
	}
}

void SDLTimerControl::destroyTimerControl(TimerControl* tc)
{
	
}

SDLTimerControl* SDLTimerControl::defaultSDlTimerControl()
{
	static SDLTimerControl sdltc;
	return &sdltc;
}

void SDLTimerControl::handleSDLTimers()
{
	for( int i = pTimers.count() - 1; i >= 0; i-- ) {
		Timer* t = pTimers.get( i );
		assert( t != NULL );
		if ( !t->isDestroying() ) {
			if ( t->enabled() ) {
				int tl = t->timeLeft();
				if ( tl <= 0 ) {
					t->setDrift( 0 - tl );
					t->tick();
				}
			}
		} else {
			pTimers.remove( i );
			delete t;
		}
	}
}


}
