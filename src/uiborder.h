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
Headerfile for the Ui::Border class
*/

#ifndef UIBORDER_H
#define UIBORDER_H

#include <gameui.h>
#include "uilist.h"
#include "uiimageobject.h"
#include "uiwidget.h"
#include "uirect.h"
#include "uiinifile.h"

#include <string>

using std::string;

namespace Ui {

  typedef Border* (*BorderLoadFunc)( InifileSection*, const ThemeLoadOptions& );

/**
	Class used internally to link a border load function to a specific border type.

	@author Tommy Carlsson
*/
class BorderLoaderItem {
public:
  BorderLoaderItem( string n, BorderLoadFunc f ): name(n), func(f) {}
  string name;
  BorderLoadFunc func;
};


/**
Class used internally to keep track of all border load functions.

@author Tommy Carlsson
 */
class BorderLoader {
public:
  BorderLoader( const string borderName, BorderLoadFunc loader ) { addLoader( borderName, loader ); }

  static void addLoader( const string borderName, BorderLoadFunc loader );
  static BorderLoadFunc getLoader( const string& name );
private:
  static List<BorderLoaderItem*>& pFuncs();
};

/**
Class describing a border.

imageTopLeft, imageTopRight, imageBottomLeft, imageBottomRight, imageLeft, imageRight, imageTop, imageBottom, imageBackground
are indexes used reference an image inside the Ui::ImageList object indicated by imageList(). The images will be rendered like the following image

@image html border_indexes.png

The variables widthLeft, widthRight, heightTop, heightBottom all indicates the size of the border.

@see Ui::Object::border()
@author Tommy Carlsson
*/
class Border {
public:

	Border(): widthLeft(0), widthRight(0), heightTop(0), heightBottom(0) { pDrawmode = DM_OPAQUE; }
  virtual ~Border(  ) {};

  int widthLeft;
  int widthRight;
  int heightTop;
  int heightBottom;

  virtual Drawmode drawmode() {
    return pDrawmode;
  }
  virtual void setDrawmode( const Drawmode& dm ) {
    pDrawmode = dm;
  }

  virtual void render( const Rect r, ImageObject& iobj ) = 0;
	//virtual void useWithLoader() = 0;

private:
  Drawmode pDrawmode;

};

}

#endif
