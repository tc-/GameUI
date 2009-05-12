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
#ifndef UIUISDLTIMERCONTROL_H
#define UIUISDLTIMERCONTROL_H

#include <uitimer.h>
#include <uilist.h>

namespace Ui {

/**
TimerControl class using the SDL library.

@author Tommy Carlsson
*/
class SDLTimerControl : public TimerControl
{
public:
  SDLTimerControl();

  ~SDLTimerControl();

	virtual long int getTimeLeft( Timer* t );
	virtual void timerTicked( Timer* t );

	virtual void assignTimer( Timer* t );
	virtual void removeTimer( Timer* t );
	
	static TimerControl* createTimerControl();
  static void destroyTimerControl(TimerControl* tc);

	static SDLTimerControl* defaultSDlTimerControl();
	
	static void handleSDLTimers();
	
private:
	
	static List<Timer*> pTimers;
	
};

}

#endif
