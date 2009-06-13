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
 * @file
 * Headerfile for the Position class.
 */

#ifndef UIPOSITION_H
#define UIPOSITION_H

#include <gameui.h>


namespace Ui
{

	/**
	 * Class containing a position.
	 */
	class Position
	{
		public:

			Position( ): pTop(0), pLeft(0) {}
			Position( const Position& pos ): pTop(pos.pTop), pLeft(pos.pLeft) {}
			Position( int left, int top ): pTop(top), pLeft(left) {}

			inline int top() {
				return pTop;
			}

			inline int left() {
				return pLeft;
			}

			inline void setTop( int top ) {
				pTop = top;
			}

			inline void setLeft( int left ) {
				pLeft = left;
			}

			inline void set( int left, int top ) {
				pTop = top;
				pLeft = left;
			}

			Position & operator=(const Position &rhs) {
				pTop = rhs.pTop;
				pLeft = rhs.pLeft;
				return *this;
			}

			Position & operator+=(const Position &rhs) {
				pTop += rhs.pTop;
				pLeft += rhs.pLeft;
				return *this;
			}

			Position & operator-=(const Position &rhs) {
				pTop -= rhs.pTop;
				pLeft -= rhs.pLeft;
				return *this;
			}

			const Position operator+(const Position &other) const {
				Position result = *this;
				result += other;
				return result;
			}

			const Position operator-(const Position &other) const {
				Position result = *this;
				result -= other;
				return result;
			}

			bool operator==( const Position& pos ) const {
				return (pTop == pos.pTop) && (pLeft == pos.pLeft);
			}

			bool operator!=( const Position& pos ) const {
				return (pTop != pos.pTop) || (pLeft != pos.pLeft);
			}

		private:


		protected:

			int pTop, pLeft;

	};


	/**
	 * Class containing a relative position.
	 */
	class RelPosition: public Position
	{
		public:
			RelPosition( ): Position() {}
			RelPosition( const Position& pos ): Position(pos) {}
			RelPosition( int left, int top ): Position(left,top) {}
	};

	/**
	 * Class containing a absolute position.
	 */
	class AbsPosition: public Position
	{
		public:
			AbsPosition( ): Position() {}
			AbsPosition( const Position& pos ): Position(pos) {}
			AbsPosition( int left, int top ): Position(left,top) {}
	};

}

#endif
