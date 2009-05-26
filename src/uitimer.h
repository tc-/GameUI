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


#ifndef UIUITIMER_H
#define UIUITIMER_H

#include <sigslot.h>
#include <uiwidget.h>
//#include <sys/time.h>

using namespace std;

namespace Ui {

class Timer;
class TimerControl;

typedef TimerControl* (*TimerControlFactory)(  );
typedef void (*TimerControlDestroyer)( TimerControl* );

/**
 * Abstract class that is used by the Timer class to interface with various timer interfaces.
 * @see Timer
 * @author Tommy Carlsson
 */
class TimerControl {
public:
	TimerControl( ) { }
	virtual ~TimerControl() { }

	/**
	 * Returns the number of milliseconds left until the timer should "tick".
	 * This function should normally not be used. Insted use the Timer::timeLeft() function.
	 * @note the timer pointed to by the parameter t has to be passed through TimerControl::assignTimer() prior to this call.
	 * @param t pointer to a timer to check time left on.
	 * @return the number of milliseconds left until the timer should "tick".
	 * @see Timer::timeLeft()
	 */
	virtual long int getTimeLeft( Timer* t ) = 0;
	/**
	 * Tells the TimerControl that the timer has "ticked" and should be resetted.
	 * @note the timer pointed to by the parameter t has to be passed through TimerControl::assignTimer() prior to this call.
	 * @param t pointer to timer to be resetted.
	 */
	virtual void timerTicked( Timer* t ) = 0;

	/**
	 * Assign timer to be controled by this TimerControl.
	 * @param t timer to be assigned.
	 * @see TimerControl::removeTimer() Timer::createTimerControl()
	 */
	virtual void assignTimer( Timer* t ) = 0;
	/**
	 * Deassign timer from TimerControl.
	 * @param t timer to deassign.
	 * @see TimerControl::assignTimer() Timer::destroyTimerControl()
	 */
	virtual void removeTimer( Timer* t ) = 0;

	/**
	 * Wrapper that creates a TimerControl class.
	 * @return a pointer to a TimerControl class created.
	 * @see TimerControl::setCreateTimerControl() TimerControlFactory
	 */
	static TimerControl* createTimerControl();
	/**
	 * Set a TimerControlFactory function to use when creating TimerControls.
	 * @param tcc TimerControlFactory function to use when creating TimerControls.
	 * @see TimerControl::createTimerControl()
	 */
	static void setCreateTimerControl( TimerControlFactory tcc );
	/**
	 * Wrapper that destroys TimerControls.
	 * @param tc pointer to a TimerControl to be destroyed.
	 * @see TimerControl::setDestroyTimerControl() TimerControlDestroyer
	 */
	static void destroyTimerControl( TimerControl* tc );
	/**
	 * Set a TimerControlDestroyer function to use when destroying TimerControls.
	 * @param tcd TimerControlDestroyer function to use.
	 */
	static void setDestroyTimerControl( TimerControlDestroyer tcd );

private:

	static void defaultDestroyer( TimerControl* tc );

	static TimerControlDestroyer pTCD;
	static TimerControlFactory pTCC;

};

/**
 * A timer class that emits a signal when it times out.
 * @see Timer::timeout() Timer::tick() Timer::onTimer Timer::enabled() TimerControl
 * @author Tommy Carlsson
 */
class Timer : public has_slots<>
{
public:

  Timer( TimerControl* tc = NULL );

	virtual ~Timer();

	/**
	 * Can be used to destroy the timer from within an eventhandler.
	 * The Timer itself will then be destroyed at a later time.
	 * @see Timer::isDestroying()
	 */
	virtual void destroyDelayed() { pDestroy = true; setTimeout( 0 ); setEnabled( true ); }
	/**
	 * Indicates if the timer is set to be destroyed later.
	 * @return true if timer is set to be destroyed later.
	 * @see Timer::destroyDelayed()
	 */
	virtual bool isDestroying() { return pDestroy; }

  /**
   * Returns the number of milliseconds until the next "tick".
	 * If the timer is disabled it will allways return timeout() instead.
	 * @return the number of milliseconds until the next "tick".
	 * @see Timer::tick() Timer::timeout() TimerControl::getTimeLeft()
   */
  virtual int timeLeft();
	/**
	 * The number of milliseconds to wait before the timer should "tick".
	 * @return number of milliseconds to wait before the timer should "tick".
	 * @see Timer::setTimeout() Timer::timeLeft()
	 */
	virtual int timeout() { return pTimeout; }
	/**
	 * Set time in milliseconds that the timer waits before it should "tick".
	 * @param t time in milliseconds that the timer waits before it should "tick".
	 * @see Timer::timeout()
	 */
	virtual void setTimeout( const int& t) { pTimeout = t; }
	/**
	 * Reset the timer.
	 * timeleft() will be the same as timeout() again. enabled() is not affected.
	 * @see Timer::timeLeft() Timer::timeout() Timer::enabled()
	 */
	virtual void reset() { if ( pTC != NULL ) pTC->timerTicked( this ); }

	/**
	 * Return true if the timer is enabled and false if the timer is disabled.
	 * @return true if the timer is enabled and false if the timer is disabled.
	 * @see Timer::setEnabled()
	 */
	virtual bool enabled() { return pEnabled; }
	/**
	 * Sets enabled() state.
	 * @param enable set to true if timer should be enabled and false if timer should be disabled.
	 * @see Timer::enabled()
	 */
	virtual void setEnabled( const bool enable = true ) { if ( pEnabled != enable ) { pEnabled = enable; onEnabled( *this, pEnabled ); } }

	/**
	 * Returns a pointer to the TimerControl responsible for handeling this timer.
	 * @return a pointer to the TimerControl responsible for handeling this timer or NULL if none assigned.
	 * @see TimerControl Timer::setTimerControl()
	 */
	virtual TimerControl* timerControl() { return pTC; }
	/**
	 * Set the TimerControl that should be responsible for handeling this timer.
	 * @param tc the TimerControl that should be responsible for handeling this timer.
	 * @see Timer::timerControl()
	 */
	virtual void setTimerControl( TimerControl* tc );

	/**
	 * Returns a user definable pointer.
	 * If you want to associate something with this timer, use this property to do that. The Timer::tcTag() property is ONLY for use by the TimerControl classes.
	 * @return user definable pointer.
	 * @see Timer::setTag() Timer::setTCTag()
	 */
	virtual void* tag(  ) { return pTag; }
	/**
	 * Set a user definable pointer.
	 * @param p a user definable pointer.
	 * @see Timer::tag()
	 */
	virtual void setTag( void* p ) { pTag = p; }

	/**
	 * Returns a pointer used by the TimerControl returned by Timer::timerControl().
	 * @note This property should ONLY be used by the TimerControl returned by Timer::timerControl(), the data stored in this pointer can vary from one TimerControl class to another.
	 * @return a pointer used by the TimerControl returned by Timer::timerControl().
	 * @see Timer::setTCTag() TimerControl
	 */
	virtual void* tcTag(  ) { return pTCTag; }
	/**
	 * Set a pointer used by the TimerControl returned by Timer::timerControl().
	 * @note This property should ONLY be used by the TimerControl returned by Timer::timerControl(), the data stored in this pointer can vary from one TimerControl class to another.
	 * @param p a pointer used by the TimerControl returned by Timer::timerControl().
	 * @see Timer::tcTag() TimerControl
	 */
	virtual void setTCTag( void* p ) { pTCTag = p; }

	/**
	 * Force timer to "tick".
	 * If timer is enabled it will be reset.
	 * @see Timer::timeout() Timer::timeLeft() Timer::reset()
	 */
	virtual void tick();

	virtual int drift() { return pDrift; }
	virtual void setDrift( int d ) { pDrift = d; }

	/**
	 * onTimer Event - Run every time the timer "ticks".
	 *
	 * @param 1 Reference to Timer that started the event.
	 * @param 2 Reference to the current timeout, this can be changed by the event handler.
	 * @see Timer::tick() Timer::timeLeft() Timer::timeout()
	 */
	signal2<Timer&,int&> onTimer;
	/**
	 * onEnabled Event - Run when timer is enabled or disabled.
	 *
	 * @param 1 Reference to Timer that started the event.
	 * @param 2 Indicates if the timer has been enabled( true ) or disabled( false ).
	 * @see Timer::enabled(), Timer::setEnabled()
	 */
	signal2<Timer&,bool> onEnabled;

private:

	bool pDestroy;

	int pDrift;
  int pTimeout;
	bool pEnabled;
	TimerControl* pTC;

	void* pTag;
	void* pTCTag;

};

}

#endif
