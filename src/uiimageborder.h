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
#ifndef UIUIIMAGEBORDER_H
#define UIUIIMAGEBORDER_H

#include <uiborder.h>
#include <uitheme.h>
#include <uiinifile.h>

namespace Ui {

/**
Class describing a border.

imageTopLeft, imageTopRight, imageBottomLeft, imageBottomRight, imageLeft, imageRight, imageTop, imageBottom, imageBackground
are indexes used reference an image inside the Ui::ImageList object indicated by imageList(). The images will be rendered like the following image 

@image html border_indexes.png

The variables widthLeft, widthRight, heightTop, heightBottom all indicates the size of the border.

@see Ui::Object::border()
@author Tommy Carlsson
*/
class ImageBorder: public Border 
{
public:

	ImageBorder(): imageTopLeft( -1 ), imageTopRight( -1 ), imageBottomLeft( -1 ), imageBottomRight( -1 ), imageLeft( -1 ), imageRight( -1 ), imageTop( -1 ), imageBottom( -1 ), imageBackground( -1 ), il( NULL ) {};

  virtual ~ImageBorder(  );

  int imageTopLeft;
  int imageTopRight;
  int imageBottomLeft;
  int imageBottomRight;
  int imageLeft;
  int imageRight;
  int imageTop;
  int imageBottom;
  int imageBackground;

  virtual ImageList* imageList() { return il; };
  virtual void setImageList( ImageList* iList ) { il = iList; };

  virtual void render( const Rect r, ImageObject& iobj );
  virtual bool isLoaded();
	
	static void useWithLoader();
  static Border* themeImageBorderLoader( InifileSection* is, const ThemeLoadOptions& op );

private:

  ImageList* il;

  //static BorderLoader imageBorderLoader;

};

}

#endif
