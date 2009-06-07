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


#ifndef UIUILABEL_H
#define UIUILABEL_H

#include <uiwidget.h>
#include <uiborder.h>
#include <uiframe.h>
#include <uilist.h>

namespace Ui
{

	/**
	 * Simple text output control
	 */
	class Label : public Widget
	{
		public:
			Label();
			Label( Frame* parent );
			~Label();

			virtual void setTheme( Theme & t, const string prefix = "" );

			virtual HAlignType textHAlign() const {
				return pHAl;
			}
			virtual void setTextHAlign( const HAlignType al ) {
				pHAl = al;
				updated();
			}
			virtual VAlignType textVAlign() const {
				return pVAl;
			}
			virtual void setTextVAlign( const VAlignType al ) {
				pVAl = al;
				updated();
			}

			virtual wstring text();
			virtual void setText( wstring s );

			virtual bool multiline() const;
			virtual void setMultiline( const bool enable );

			virtual void render( ImageObject& img, const Rect& rr );

		private:

			HAlignType pHAl;
			VAlignType pVAl;

			wstring pText;
			bool pMultiline;

	};

}

#endif
