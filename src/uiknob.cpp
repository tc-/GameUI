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
#include "uiknob.h"

#include <cmath>

namespace Ui {

Knob::Knob( Frame* parent )
 : Widget( parent )
{
  pValue = 0;
  pImages = NULL;
  pImage = NULL;
  pPPS = 0;
  pDrag = false;
  setDrawmode( DM_TRANSPARENT );
}


Knob::~Knob()
{
}

void Knob::setTheme( Theme& t, const string prefix )
{
	Widget::setTheme( t, prefix );
  setImage( t.getImage( prefix+"knob" ) );
}

void Knob::render( ImageObject& img, const Rect& r )
{
  if ( !visible() ) return;
  if ( pImage != NULL ) {
    img.drawImage( *pImage, Rect( 0, 0, pImage->sectionWidth(), pImage->sectionHeight() ), pImage->sectionRect( pValue ) );
  } else if ( pImages != NULL ) {
    ImageObject* tmp = pImages->get( pValue );
    if ( tmp != NULL ) {
      img.drawImage( *tmp, Rect( 0, 0, tmp->width(), tmp->height()), pImage->sectionRect( pValue ) );
    }
  } else {
    Widget::render( img, r );
  }
}


ImageList* Knob::imageList()
{
  return pImages;
}


void Knob::setImageList( ImageList* imgl )
{
  pImages = imgl;
  updated();
}

ImageObject* Knob::image()
{
  return pImage;
}

void Knob::setImage( ImageObject* img )
{
  pImage = img;
}


int Knob::value()
{
  return pValue;
}

void Knob::setValue( const int& val )
{
  int v = val;
  int startval = pValue;
  if ( v < 0 ) v = 0;
  if ( pImage != NULL ) {
    if ( v >= pImage->numSections() )
      v = pImage->numSections() - 1;
  } else if ( pImages != NULL ) {
    if ( v >= pImages->count() )
      v = pImages->count() - 1;
  }
  if ( v < 0 ) v = 0;
  pValue = v;
  if ( startval != pValue ) {
    onChange( *this, v );
    updated( );
  }
}

int Knob::numValues()
{
  if ( pImage != NULL ) {
    return pImage->numSections();
  } else if ( pImages != NULL ) {
    return pImages->count();
  } else {
    return 0;
  }
}

int Knob::pixelsPerStep()
{
  if ( pPPS == 0 ) {
    return 30 / ( numValues() / 2 );
  } else {
    return pPPS;
  }
}


void Knob::setPixelsPerStep( const int& pps )
{
  pPPS = pps;
}


Widget* Knob::mouseMove( int x, int y, MouseButtons mb )
{
  if ( pDrag ) {
		int dv = (int)floor( (double)(( y - pStartY ) / pixelsPerStep()) );
    if ( dv != 0 ) pHasDrag = true;
    setValue( pStartVal - dv );
  }
  return this;
}

Widget* Knob::mouseClick( int x, int y, MouseButtons mb )
{
  if ( pDrag ) {
    pDrag = false;
//    int dv = (int)floor( ( y - pStartY ) / pixelsPerStep() );
    if ( pHasDrag )
      return this;
  }
  if ( mb == MBT_LEFT ) {
    setValue( pValue + 1 );
  } else if ( mb == MBT_RIGHT ) {
    setValue( pValue - 1 );
  } else if ( mb == MBT_WHEELUP ) { 
    setValue( pValue + 1 );
  } else if ( mb == MBT_WHEELDOWN ) { 
    setValue( pValue - 1 );
  }
  return this;
}

Widget* Knob::mousePressed( int x, int y, MouseButtons mb )
{
  pHasDrag = false;
  if ( mb == MBT_LEFT ) {
    grabMouseInput();
    pStartY = y;
    pStartVal = pValue;
    pDrag = true;
    
  }
  return this;
}

Widget* Knob::mouseReleased( int x, int y, MouseButtons mb )
{
  releaseMouseInput();
  return this;
}

Widget* Knob::keyPressed( Key key )
{
  return this;
}


}
