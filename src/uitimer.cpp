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


#include "uitimer.h"

namespace Ui {


TimerControlDestroyer TimerControl::pTCD = &TimerControl::defaultDestroyer;
TimerControlFactory TimerControl::pTCC = NULL;


TimerControl* TimerControl::createTimerControl()
{
	assert( pTCC != NULL /*A TimerControl Class Factory Has Not Been Set.*/ );
//	if ( pTCC != NULL ) {
		return pTCC();
//	} else {
//		return NULL;
//	}
}


void TimerControl::setCreateTimerControl( TimerControlFactory tcc )
{
	pTCC = tcc;
}


void TimerControl::destroyTimerControl( TimerControl* tc )
{
	if ( pTCD != NULL ) {
		if ( tc != NULL )
  	  pTCD( tc );
	}
}


void TimerControl::setDestroyTimerControl( TimerControlDestroyer tcd )
{
	pTCD = tcd;
}


void TimerControl::defaultDestroyer( TimerControl* tc )
{
	if ( tc != NULL )
		delete tc;
}




Timer::Timer( TimerControl* tc )
{
	pDestroy = false;
	pTag = NULL;
	pTCTag = NULL;
	pTC = NULL;

	pTimeout = 1000;
	pDrift = 0;

	if ( tc != NULL ) {
		pTC = tc;
		pTC->assignTimer( this );
	} else {
		pTC = TimerControl::createTimerControl();
		if ( pTC != NULL )
			pTC->assignTimer( this );
	}
	setEnabled( false );
}


Timer::~Timer()
{
	if ( pTC != NULL ) {
		pTC->removeTimer( this );
	  TimerControl::destroyTimerControl( pTC );
	}
}


void Timer::setTimerControl( TimerControl* tc )
{
	if ( ( pTC != NULL ) && ( pTC != tc ) )
		pTC->removeTimer( this );
	if ( pTC != tc )
		pTC->assignTimer( this );
	pTC = tc;
}


int Timer::timeLeft()
{
	if ( pTC != NULL )
		return pTC->getTimeLeft( this );
	else
		return pTimeout;
}

void Timer::tick()
{
	int to = pTimeout;
	onTimer( *this, to );
	if ( to != pTimeout )	setTimeout( to );
	if ( pTC != NULL ) pTC->timerTicked( this );
}

}
