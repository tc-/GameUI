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

/**
@file
Headerfile for the UiRect class
*/

#ifndef UIRECT_H
#define UIRECT_H

#include <gameui.h>
#include <string>
#include <stdlib.h>

using namespace std;

namespace Ui {

class Border;

/**
Class to hold position and size data

@author Tommy Carlsson
*/
class Rect{
public:
  Rect();
  Rect( int nLeft, int nTop, int nWidth, int nHeight );
  ~Rect();

  int top;
  int left;
  int width;
  int height;

  void crop( const Rect cr );
  void merge( const Rect cr );
  void applyBorder( Border* b );

  int area() const { return width * height; }
  bool isVoid() const { return ( area() <= 0); };
  bool intersects( const Rect ir ) const;
  bool encloses( const Rect er ) const;
  bool pointInside( const int& pleft, const int& ptop ) const;
  void debug( string ds ) const;

  int operator==( const Rect& r ) const;
  int operator!=( const Rect& r ) const;
	
	static bool pointInside( const Rect& r, const int& pleft, const int& ptop );
	
};

const Rect NULL_RECT = Rect( -1, -1, -1, -1 );
}

#endif
