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
Headerfile for the UiRect class
*/

#ifndef UIRECT_H
#define UIRECT_H

#include <gameui.h>
#include <string>
#include <stdlib.h>

using namespace std;

namespace Ui
{

	class Border;

	/**
	 * Class to hold position and size data.
	 */
	class Rect
	{
		public:
			Rect();
			Rect( int nLeft, int nTop, int nWidth, int nHeight );
			~Rect();

			int top;		//!< Vertical position.
			int left;		//!< Horizontal position.
			int width;
			int height;

			/**
			 * Sets this Rect to be the intersection between cr and this Rect.
			 *
			 * @see merge().
			 */
			void crop( const Rect cr );

			/**
			 * Sets this Rect to be the Union of cr and this Rect.
			 *
			 * This takes the lowest values of top and left and calculates the width and height to include both Rect objects.
			 * @see crop().
			 */
			void merge( const Rect cr );

			/**
			 * Shrink this Rect with the marigins of a Border.
			 *
			 * @see crop() Border.
			 */
			void applyBorder( Border* b );

			/**
			 * The area of this Rect.
			 *
			 * @see isVoid().
			 */
			inline int area() const {
				return width * height;
			}

			/**
			 * Is this Rect empty.
			 *
			 * @see area().
			 */
			inline bool isVoid() const {
				return ( area() <= 0 );
			};

			/**
			 * Does this Rect intersect with ir.
			 *
			 * @return true if the Rect objects have a common area.
			 * @see encloses() pointInside().
			 */
			bool intersects( const Rect ir ) const;

			/**
			 * Does this Rect enclose er.
			 *
			 * @return true if er is completely enclosed inside this Rect.
			 * @see intersects() pointInside().
			 */
			bool encloses( const Rect er ) const;

			/**
			 * Is specified point inside this Rect.
			 *
			 * @see intersects() encloses().
			 */
			bool pointInside( const int& pleft, const int& ptop ) const;

			/**
			 * Output string repressenting this Rect.
			 *
			 * @todo Change to a "toString" method instead.
			 */
			void debug( string ds ) const;

			/**
			 * Rect objects are equal if left, top, width, and height are equal.
			 */
			int operator==( const Rect& r ) const;

			/**
			 * Rect objects are not equal if any of left, top, width, and height are not equal.
			 */
			int operator!=( const Rect& r ) const;

			/**
			 * Is specified point inside r Rect.
			 *
			 * @todo Does this method really provide any extra functionality that pointInside() does not have?
			 * @see pointInside().
			 */
			static bool pointInside( const Rect& r, const int& pleft, const int& ptop );

	};

	const Rect NULL_RECT = Rect( -1, -1, -1, -1 ); //!< Rect to use in the same way as null.
}

#endif
