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


#ifndef UIUIKNOB_H
#define UIUIKNOB_H

#include <uiwidget.h>
#include <uiimageobject.h>

namespace Ui
{

	/**
	 * A Knob Widget.
	 */
	class Knob : public Widget
	{
		public:
			Knob( Frame* parent = NULL );
			~Knob();

			virtual void setTheme( Theme& t, const string prefix="" );
			virtual void render( ImageObject& img, const Rect& r );

			ImageList* imageList();
			void setImageList( ImageList* imgl );

			ImageObject* image();
			void setImage( ImageObject* img );

			int value();
			void setValue( const int& val );
			int numValues();

			int pixelsPerStep();
			void setPixelsPerStep( const int& pps );

			virtual Widget* mouseMove( int x, int y, MouseButtons mb );
			virtual Widget* mouseClick( int x, int y, MouseButtons mb );
			virtual Widget* mousePressed( int x, int y, MouseButtons mb );
			virtual Widget* mouseReleased( int x, int y, MouseButtons mb );
			virtual Widget* keyPressed( Key key );

			signal2<Widget&,int> onChange;

		private:
			int pValue;
			ImageList* pImages;
			ImageObject* pImage;
			int pStartY;
			int pStartVal;
			int pPPS;
			bool pDrag;
			bool pHasDrag;
	};

}

#endif
