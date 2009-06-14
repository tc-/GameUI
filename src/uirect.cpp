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


/**
@file
Implementation of the Ui::Rect class
*/

#include "uirect.h"
#include <uiborder.h>

using namespace Ui;


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


void Rect::applyBorder( const Border& b )
{
	top += b.heightTop;
	left += b.widthLeft;
	width -= b.widthLeft + b.widthRight;
	height -= b.heightTop + b.heightBottom;
}


bool Rect::encloses( const Rect& er ) const
{
  if (( pointInside( er.left, er.top ) ) && ( pointInside( er.left+er.width, er.top ) ) &&
        ( pointInside( er.left, er.top+er.height ) ) && ( pointInside( er.left+er.width, er.top+er.height ) )) {
    return true;
  } else {
    return false;
  }
}


void Rect::debug( const string& ds ) const
{
  cout << "!!! " << ds << " Rect::" << "top: " << top << " left: " << left << " width: " << width << " height: " << height << endl;
}

