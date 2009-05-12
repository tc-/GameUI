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

/**
@file
Implementation of the Ui::Rect class
*/

#include "uirect.h"
#include <uiborder.h>

using namespace Ui;

Rect::Rect()
{
  top = 0;
  left = 0;
  width = 0;
  height = 0;
}



Rect::Rect( int nLeft, int nTop, int nWidth, int nHeight )
{
  top = nTop;
  left = nLeft;
  width = nWidth;
  height = nHeight;
}



Rect::~Rect()
{
}



void Rect::crop( const Rect cr )
{

  if ( left < cr.left ) {
    width -= (cr.left - left);
    left = cr.left;
  }
  int dist = left - cr.left;
  if ( cr.width < width + dist ) {
    width = cr.width - dist;
  }
  if ( width < 0 ) {
    width = 0;
  }

  if ( top < cr.top ) {
    height -= (cr.top - top);
    top = cr.top;
  }
  dist = top - cr.top;
  if ( cr.height < height + dist ) {
    height = cr.height - dist;
  }
  if ( height < 0 ) {
    height = 0;
  }

}

void Rect::merge( const Rect cr )
{
/*  if ( cr.top < top) {
    cout << "!!! dfg: " << top << " " << cr.top << " " << (top - cr.top) << endl;

    height += 1*(top - cr.top);
    top = cr.top;
  } else {
    height += cr.top - top;
  }
  if ( cr.left < left) {
    width += left - cr.left;
    left = cr.left;
  } else {
    width += cr.left - left;
  }*/
  if ( top < cr.top ) {
		int th = cr.top - top + Utils::max( height, cr.height );//cr.height;
    if ( height < th ) {
      height = th;
    }
  } else {
		int th = top - cr.top + Utils::max( height, cr.height );
    top = cr.top;
    if ( height < th ) {
      height = th;
    }
  }
  if ( left < cr.left ) {
		int tw = cr.left - left + Utils::max( width, cr.width );//cr.width;
    if ( width < tw ) {
      width = tw;
    }
  } else {
		int tw = left - cr.left + Utils::max( width, cr.width );//width;
    left = cr.left;
    if ( width < tw ) {
      width = tw;
    }
  }
}


void Rect::applyBorder( Border* b )
{
  if ( b != NULL ) {
    top += b->heightTop;
    left += b->widthLeft;
    width -= b->widthLeft + b->widthRight;
    height -= b->heightTop + b->heightBottom;
  }
}

bool Rect::intersects( const Rect ir ) const
{
  Rect r2 = *this;
  r2.crop( ir );
  return ( r2.area() > 0 );
/*  if (( pointInside( ir.top, ir.left) ) || ( pointInside( ir.top, ir.left+ir.width) ) ||
      ( pointInside( ir.top+ir.height, ir.left) ) || ( pointInside( ir.top+ir.height, ir.left+ir.width) )) {
    return true;
  } else if (( ir.pointInside( top, left) ) || ( ir.pointInside( top, left+width) ) ||
      ( ir.pointInside( top+height, left) ) || ( ir.pointInside( top+height, left+width) )) {
    return true;
  } else {
    return false;
}*/
}

bool Rect::encloses( const Rect er ) const
{
  if (( pointInside( er.left, er.top ) ) && ( pointInside( er.left+er.width, er.top ) ) &&
        ( pointInside( er.left, er.top+er.height ) ) && ( pointInside( er.left+er.width, er.top+er.height ) )) {
    return true;
  } else {
    return false;
  }
}


bool Rect::pointInside( const int& pleft, const int& ptop ) const
{
  if ( (ptop >= top) && (pleft >= left) && (ptop <= top+height) && (pleft <= left+width))
    return true;
  else
    return false;

  if (( ptop >= top ) && ( pleft >= left )) {
    if (( ptop <= top+height ) && ( pleft <= left+width ))
      return true;
  }

  return false;
}

bool Rect::pointInside( const Rect& r, const int& pleft, const int& ptop )
{
	if ( (ptop >= r.top) && (pleft >= r.left) && (ptop <= r.top+r.height) && (pleft <= r.left+r.width))
		return true;
	else
		return false;

	if (( ptop >= r.top ) && ( pleft >= r.left )) {
		if (( ptop <= r.top+r.height ) && ( pleft <= r.left+r.width ))
			return true;
	}

	return false;
}	

void Rect::debug( string ds ) const
{
  cout << "!!! " << ds << " Rect::" << "top: " << top << " left: " << left << " width: " << width << " height: " << height << endl;
}

int Rect::operator==( const Rect& r ) const
{
  return ( ( left == r.left ) && ( top == r.top ) && ( width == r.width ) && ( height == r.height ) );
}


int Rect::operator!=( const Rect& r ) const
{
  return (( left != r.left ) || ( top != r.top ) || ( width != r.width ) || ( height != r.height ) );
}
