/***************************************************************************
 *   Copyright (C) 2005 by Tommy Carlsson                                  *
 *   tc@coderworld.net                                                     *
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
#ifndef EVENTS_H
#define EVENTS_H

#include <sigslot.h>
#include <uipushbutton.h>
#include <uihscrollbar.h>
#include <uitimer.h>

using namespace sigslot;
using namespace Ui;

/**
@author Tommy Carlsson
*/
class Events : public has_slots<>
{
public:
  Events();

  ~Events();

  void b1Pressed( PushButton& btn );
	void b1mPressed( Widget& w, MouseButtons mb );
	void transbuttonPressed( PushButton& btn );
	void b1DblClick( Widget& btn );
	void tTimer( Timer& timer, int& timeout );
	void sc1Scroll( Widget * s, int by );
	void dfbDrag( Widget* w, int x, int y, DragObject** d );
	void dtbDrop( Widget* w, int x, int y, DragObject* d, bool& a );
	void dtbDragOver( Widget* w, int x, int y, DragObject* d, bool& a, ImageObject** i );
	void btbPressed( PushButton& btn );
			
};

#endif
