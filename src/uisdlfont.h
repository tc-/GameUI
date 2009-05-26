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
Headerfile for the Ui::SDLFont class
*/

#ifndef UISDLFONT_H
#define UISDLFONT_H

#include <gameui.h>
#include <uifont.h>
#include <uitheme.h>
#include <uiinifile.h>
#include <string>
#include "SDL_ttf.h"

using std::string;

namespace Ui {

/**
Class containing a SDL TTF font

@author Tommy Carlsson
*/
class SDLFont : public Font
{
public:
  SDLFont(  );
  SDLFont( string fname, int size, int index );
  ~SDLFont(  );

  int size();
  int textWidth( wstring s );
  int charWidth( wchar_t c );
  int textHeight(  );

  void setSize( int newSize );
  void loadFont( string fname, int size, int index );
//  void setStyle( int style );
	FontStyle style();
	void setStyle( const FontStyle& fs );

  void freeFont(  );
  bool isLoaded(  );

  TTF_Font* getFont(  );

  static Font* themeSDLFontLoader( InifileSection* iniSec, const ThemeLoadOptions& op );

	static Font* sdlFontFactory()
	{
		return new SDLFont();
	}

private:
  TTF_Font *f;
  string pfname;
  int pindex;
  int psize;

};

}

#endif
