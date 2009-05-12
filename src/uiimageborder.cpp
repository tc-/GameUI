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
#include "uiimageborder.h"
#include "uilist.h"


namespace Ui {

//BorderLoader ImageBorder::imageBorderLoader( "ImageBorder", &themeImageBorderLoader );

ImageBorder::~ImageBorder()
{
}

Border* ImageBorder::themeImageBorderLoader( InifileSection* is, const ThemeLoadOptions& op )
{
  if ( is == NULL ) return NULL;
  int alpha = is->keyIntValue( "alpha", 255 );
  string aprefix = is->keyStringValue( "autoprefix", "*?*" );
  string ext = is->keyStringValue( "fileextension", ".png" );
  ImageBorder* ib = new ImageBorder();
  ib->setImageList( new ImageList() );

  InifileSection ini;
  ini.setKeyIntValue( "alpha", alpha );

  string iname = is->keyStringValue( "imagebackground", "" );
  if ( iname != "" ) {
    ImageObject* img = op.imageLoader( op.imageRoot + "/" + iname, &ini, op );
    if ( img != NULL ) { ib->imageList()->append( img ); ib->imageBackground = ib->imageList()->count() - 1; }
  }
  iname = is->keyStringValue( "imageleft", "" );
  if ( iname != "" ) {
    ImageObject* img = op.imageLoader( op.imageRoot + "/" + iname, &ini, op );
    if ( img != NULL ) { ib->imageList()->append( img ); ib->imageLeft = ib->imageList()->count() - 1; ib->widthLeft = img->width(); }
  }
  iname = is->keyStringValue( "imageright", "" );
  if ( iname != "" ) {
    ImageObject* img = op.imageLoader( op.imageRoot + "/" + iname, &ini, op );
    if ( img != NULL ) { ib->imageList()->append( img ); ib->imageRight = ib->imageList()->count() - 1; ib->widthRight = img->width(); }
  }
  iname = is->keyStringValue( "imagetop", "" );
  if ( iname != "" ) {
    ImageObject* img = op.imageLoader( op.imageRoot + "/" + iname, &ini, op );
    if ( img != NULL ) { ib->imageList()->append( img ); ib->imageTop = ib->imageList()->count() - 1; ib->heightTop = img->height(); }
  }
  iname = is->keyStringValue( "imagebottom", "" );
  if ( iname != "" ) {
    ImageObject* img = op.imageLoader( op.imageRoot + "/" + iname, &ini, op );
    if ( img != NULL ) { ib->imageList()->append( img ); ib->imageBottom = ib->imageList()->count() - 1; ib->heightBottom = img->height(); }
  }
  iname = is->keyStringValue( "imagetopleft", "" );
  if ( iname != "" ) {
    ImageObject* img = op.imageLoader( op.imageRoot + "/" + iname, &ini, op );
    if ( img != NULL ) { ib->imageList()->append( img ); ib->imageTopLeft = ib->imageList()->count() - 1; }
  }
  iname = is->keyStringValue( "imagetopright", "" );
  if ( iname != "" ) {
    ImageObject* img = op.imageLoader( op.imageRoot + "/" + iname, &ini, op );
    if ( img != NULL ) { ib->imageList()->append( img ); ib->imageTopRight = ib->imageList()->count() - 1; }
  }
  iname = is->keyStringValue( "imagebottomleft", "" );
  if ( iname != "" ) {
    ImageObject* img = op.imageLoader( op.imageRoot + "/" + iname, &ini, op );
    if ( img != NULL ) { ib->imageList()->append( img ); ib->imageBottomLeft = ib->imageList()->count() - 1; }
  }
  iname = is->keyStringValue( "imagebottomright", "" );
  if ( iname != "" ) {
    ImageObject* img = op.imageLoader( op.imageRoot + "/" + iname, &ini, op );
    if ( img != NULL ) { ib->imageList()->append( img ); ib->imageBottomRight = ib->imageList()->count() - 1; }
  }

  if ( aprefix != "*?*" ) {
    if ( ib->imageBackground == -1 ) {
      ImageObject* img = op.imageLoader( op.imageRoot + "/" + aprefix + "_bg" + ext, &ini, op );
      if ( img != NULL ) { ib->imageList()->append( img ); ib->imageBackground = ib->imageList()->count() - 1; }
    }
    if ( ib->imageLeft == -1 ) {
      ImageObject* img = op.imageLoader( op.imageRoot + "/" + aprefix + "_l" + ext, &ini, op );
      if ( img != NULL ) { ib->imageList()->append( img ); ib->imageLeft = ib->imageList()->count() - 1; ib->widthLeft = img->width(); }
    }
    if ( ib->imageRight == -1 ) {
      ImageObject* img = op.imageLoader( op.imageRoot + "/" + aprefix + "_r" + ext, &ini, op );
      if ( img != NULL ) { ib->imageList()->append( img ); ib->imageRight = ib->imageList()->count() - 1; ib->widthRight = img->width(); }
    }
    if ( ib->imageTop == -1 ) {
      ImageObject* img = op.imageLoader( op.imageRoot + "/" + aprefix + "_t" + ext, &ini, op );
      if ( img != NULL ) { ib->imageList()->append( img ); ib->imageTop = ib->imageList()->count() - 1; ib->heightTop = img->height(); }
    }
    if ( ib->imageBottom == -1 ) {
      ImageObject* img = op.imageLoader( op.imageRoot + "/" + aprefix + "_b" + ext, &ini, op );
      if ( img != NULL ) { ib->imageList()->append( img ); ib->imageBottom = ib->imageList()->count() - 1; ib->heightBottom = img->height(); }
    }
    if ( ib->imageTopLeft == -1 ) {
      ImageObject* img = op.imageLoader( op.imageRoot + "/" + aprefix + "_tl" + ext, &ini, op );
      if ( img != NULL ) { ib->imageList()->append( img ); ib->imageTopLeft = ib->imageList()->count() - 1; }
    }
    if ( ib->imageTopRight == -1 ) {
      ImageObject* img = op.imageLoader( op.imageRoot + "/" + aprefix + "_tr" + ext, &ini, op );
      if ( img != NULL ) { ib->imageList()->append( img ); ib->imageTopRight = ib->imageList()->count() - 1; }
    }
    if ( ib->imageBottomLeft == -1 ) {
      ImageObject* img = op.imageLoader( op.imageRoot + "/" + aprefix + "_bl" + ext, &ini, op );
      if ( img != NULL ) { ib->imageList()->append( img ); ib->imageBottomLeft = ib->imageList()->count() - 1; }
    }
    if ( ib->imageBottomRight == -1 ) {
      ImageObject* img = op.imageLoader( op.imageRoot + "/" + aprefix + "_br" + ext, &ini, op );
      if ( img != NULL ) { ib->imageList()->append( img ); ib->imageBottomRight = ib->imageList()->count() - 1; }
    }
  }

  if ( ib->isLoaded() ) {
    return ib;
  } else {
    for( int i = 0; i < ib->imageList()->count(); i++ ) {
      delete ib->imageList()->get(i);
    }
    delete ib->imageList();
    delete ib;
    return NULL;
  }
}

void ImageBorder::useWithLoader()
{
	BorderLoader::addLoader( "ImageBorder", &themeImageBorderLoader );
}

void ImageBorder::render( const Rect r, ImageObject& iobj )
{
    //cout << "Rect: top: " << r.top << " left: " << r.left << " width: " << r.width << " height: " << r.height << endl;
    int xpos = r.left;
    int ypos = r.top;
    Rect imgr;

//    iobj.pushClipRect( r );

    if ( imageBackground >= 0 ) {
      //cout << "* Boarder Render BG" << endl;
      imgr.top = ypos + heightTop;
      imgr.left = xpos + widthLeft;
      imgr.width =  r.width - widthLeft - widthRight;
      imgr.height = r.height - heightTop - heightBottom;
 //cout << "ImgRect: top: " << imgr.top << " left: " << imgr.left << " width: " << imgr.width << " height: " << imgr.height << endl;

      iobj.drawImageTiled( *imageList()->get( imageBackground ), imgr );
    }

    if ( this->imageTopLeft >= 0 ) {
      imgr.top = ypos;
      imgr.left = xpos;
      imgr.width = widthLeft;
      imgr.height = heightTop;
     // cout << "ImgTLRect: top: " << imgr.top << " left: " << imgr.left << " width: " << imgr.width << " height: " << imgr.height << endl;

      iobj.drawImage( *imageList()->get( imageTopLeft ), imgr );
    }

    if ( imageTopRight >= 0 ) {
      imgr.top = ypos;
      imgr.left = xpos + r.width - widthRight;
      imgr.width = widthRight;
      imgr.height = heightTop;

      iobj.drawImage( *imageList()->get( imageTopRight ), imgr );
    }

    if ( imageBottomLeft >= 0 ) {
      imgr.top = ypos + r.height - heightBottom;
      imgr.left = xpos;
      imgr.width = widthLeft;
      imgr.height = heightBottom;

      iobj.drawImage( *imageList()->get( imageBottomLeft ), imgr );
    }

    if ( imageBottomRight >= 0 ) {
      imgr.top = ypos + r.height - heightBottom;
      imgr.left = xpos + r.width - widthRight;
      imgr.width = widthRight;
      imgr.height = heightBottom;

      iobj.drawImage( *imageList()->get( imageBottomRight ), imgr );
    }

    if ( imageTop >= 0 ) {
      imgr.top = ypos;
      imgr.left = xpos + widthLeft;
      imgr.width = r.width - widthLeft - widthRight;
      imgr.height = heightTop;

      iobj.drawImageTiled( *imageList()->get( imageTop ), imgr );
    }

    if ( this->imageBottom >= 0 ) {
      imgr.top = ypos + r.height - heightBottom;
      imgr.left = xpos + widthLeft;
      imgr.width = r.width - widthLeft - widthRight;
      imgr.height = heightBottom;

      iobj.drawImageTiled( *imageList()->get( imageBottom ), imgr );
    }

    if ( this->imageLeft >= 0 ) {
      imgr.top = ypos + heightTop;
      imgr.left = xpos;
      imgr.width =  widthLeft;
      imgr.height = r.height - heightTop - heightBottom;

      iobj.drawImageTiled( *imageList()->get( imageLeft ), imgr );
    }

    if ( imageRight >= 0 ) {
      imgr.top = ypos + heightTop;
      imgr.left = xpos + r.width - widthRight;
      imgr.width =  widthRight;
      imgr.height = r.height - heightTop - heightBottom;

      iobj.drawImageTiled( *imageList()->get( imageRight ), imgr );
    }

  //  iobj.popClipRect();

}


bool ImageBorder::isLoaded()
{
  return ( imageLeft != -1 );
}

}
