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


#include "uitileview.h"

namespace Ui {

TileView::TileView(Frame* parent): Widget(parent)
{

  pShowGrid = false;
  pDrawTiles = true;
  pDrawObjects = false;
  pDrawSprites = false;
  pDrawOverlays = false;

  pTileWidth = 32;
  pTileHeight = 32;

  pNumX = 0;
  pNumY = 0;

  pScrollX = 0;
  pScrollY = 0;

  pTiles = NULL;
}


TileView::~TileView()
{
  freeTiles();
}

void TileView::render( ImageObject& img, const Rect& r )
{
  int startX = (int)( (r.left + pScrollX) / pTileWidth );
	int startY = (int)floor( (double)((r.top + pScrollY) / pTileHeight) );
	int stopX = (int)ceil( (double)((r.left + pScrollX + r.width) / pTileWidth) ) + 1;
	int stopY = (int)ceil( (double)((r.top + pScrollY + r.height) / pTileHeight) ) + 1;

  if ( startX < 0 ) startX = 0;
  if ( startY < 0 ) startY = 0;
  if ( stopY < 0 ) stopY = 0;
  if ( stopY < 0 ) stopY = 0;

	if ( startX >= (int)pNumX ) startX = pNumX;
	if ( startY >= (int)pNumY ) startY = pNumY;
	if ( stopX >= (int)pNumX ) stopX = pNumX;
	if ( stopY >= (int)pNumY ) stopY = pNumY;

//  cout << "startX: " << startX << " startY: " << startY << " stopX: " << stopX << " stopY: " << stopY << endl;

  int x = pScrollX + (startX * pTileWidth);
  int y = pScrollY + (startY * pTileHeight);

//  cout << "absX: " << absoluteXPos() << " absY: " << absoluteYPos() << endl;
//  cout << "x: " << x << " y: " << y << endl;

  for ( int iy = startY; iy < stopY; iy++ ) {
    for ( int ix = startX; ix < stopX; ix++ ) {
      for( int i = 0; i < tiles(ix, iy).numTiles(); i++ ){
        if ( tiles(ix, iy).tileImage( i ) >= 0 ) {
          gui().screen().drawImage( *tileImages().get( tiles(ix, iy).tileImage( i ) ), Rect( x, y, pTileWidth, pTileHeight ) );
        }
      }
      for( int i = 0; i < tiles(ix, iy).numObjects(); i++ ){
        if ( tiles(ix, iy).objectImage( i ) >= 0 ) {
          gui().screen().drawImage( *objectImages().get( tiles(ix, iy).objectImage( i ) ), Rect( x, y, pTileWidth, pTileHeight ) );
        }
      }
      x += pTileWidth;
    }
    x = pScrollX + (startX * pTileWidth);
    y += pTileHeight;
  }

}


void TileView::setTheme( Theme & t, const string prefix )
{
	Widget::setTheme( t, prefix );
  setBorder( t.getBorder( prefix+"tileview" ) );
	setCursor( t.getCursor( prefix+"tileview" ) );
}


void TileView::setNumTiles( const unsigned int numX, const unsigned int numY )
{
  pNumX = numX;
  pNumY = numY;
  allocateTiles();
  checkAlign();
}

void TileView::freeTiles()
{
  if ( pTiles != NULL ) {
    delete[] pTiles;
    pTiles = NULL;
  }
}

void TileView::allocateTiles()
{
  freeTiles();
  pTiles = new Tile[pNumX * pNumY];
}

int TileView::tileX( const int x ) const
{
  int bx = 0;
  if ( border() != NULL )
    bx = border()->widthLeft;

  int res = (int)( (x + pScrollX - bx) / pTileWidth );
  if ( res < 0 ) res = -1;
	if ( res >= (int)pNumX ) res = -1;
  return res;
}

int TileView::tileY( const int y ) const
{
  int by = 0;
  if ( border() != NULL )
    by = border()->heightTop;

  int res = (int)( (y + pScrollY - by) / pTileHeight );
  if ( res < 0 ) res = -1;
	if ( res >= (int)pNumY ) res = -1;
  return res;
}

void TileView::checkAlign()
{
/*  Rect r = getWidgetRect();
  r.applyBorder( border() );
  int tmpSX = pScrollX;
  int tmpSY = pScrollY;
  pScrollX = 0;
  pScrollY = 0;

  int w = tileX( pNumX - 1 )+pTileWidth;
  if ( w < r.width ) {
    pScrollX = 0 - Gui::inMiddle( r.width, w );
  } else
    pScrollX = tmpSX;

  int h = tileY( pNumY - 1 )+pTileHeight;
  if ( h < r.height ) {
    pScrollY = 0 - Gui::inMiddle( r.height, h );
  } else
    pScrollY = tmpSY;
*/
}


Widget* TileView::mouseClick( int x, int y, MouseButtons mb )
{
  return Widget::mouseClick( x, y, mb );
}

Widget* TileView::mouseDblClick( int x, int y, MouseButtons mb )
{
  return Widget::mouseDblClick( x, y, mb );
}

Widget* TileView::mousePressed( int x, int y, MouseButtons mb )
{
  x -= borderLeft();
  y -= borderTop();
  x = tileX( x );
  y = tileY( y );
  if ( ( x != -1 ) && ( y != -1) )
    onTileClicked.emit( *this, x, y, mb );
 return Widget::mousePressed( x, y, mb );
}

Widget* TileView::mouseReleased( int x, int y, MouseButtons mb )
{
  return Widget::mouseReleased( x, y, mb );
}


}
