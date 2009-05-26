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
