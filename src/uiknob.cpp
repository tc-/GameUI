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
  if ( mb.left ) {
    setValue( pValue + 1 );
  } else if ( mb.right ) {
    setValue( pValue - 1 );
  } else if ( mb.wheelUp ) {
    setValue( pValue + 1 );
  } else if ( mb.wheelDown ) {
    setValue( pValue - 1 );
  }
  return this;
}

Widget* Knob::mousePressed( int x, int y, MouseButtons mb )
{
  pHasDrag = false;
  if ( mb.left ) {
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
