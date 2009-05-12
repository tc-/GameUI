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
#ifndef UIUITILEVIEW_H
#define UIUITILEVIEW_H

#include <uiwidget.h>
#include <uilist.h>
#include <uicolor.h>
#include <uiborder.h>
#include <uigui.h>
#include <math.h>

namespace Ui {

class TileSprite {
public:

  int x;
  int y;
  int image;

  TileSprite():x(0), y(0), image(-1) {}
  TileSprite( int xp, int yp ):x(xp), y(yp), image(-1) {}
  TileSprite( int xp, int yp, int im ):x(xp), y(yp), image(im) {}

};

class Tile {
public:

	Tile(): pTileImages(NULL), pObjectImages(NULL), pNumTiles(0), pNumObjects(0) {}

  int& tileImage( const unsigned int index )
  {
		assert( index < pNumTiles );
    return pTileImages[index];
  }

  void setNumTiles( const unsigned int num )
  {
    if ( (num == 0) && (pNumTiles > 0)) {
      free( pTileImages );
      pNumTiles = 0;
    } else if ( (num > 0) && ( pNumTiles == 0 )) {
      pTileImages = (int*)malloc( sizeof(int) * num );
      pNumTiles = num;
    } else {
      pTileImages = (int*)realloc( pTileImages, sizeof(int)*num );
      pNumTiles = num;
    }
  }
  int numTiles() const { return pNumTiles; }

  int& objectImage( const unsigned int index )
  {
    assert( index < pNumObjects );
    return pObjectImages[index];
  }

  void setNumObjects( const unsigned int num )
  {
    if ( (num == 0) && (pNumObjects > 0)) {
      free( pObjectImages );
      pNumObjects = 0;
    } else if ( (num > 0) && ( pNumObjects == 0 )) {
      pObjectImages = (int*)malloc( sizeof(int) * num );
      pNumObjects = num;
    } else {
      pObjectImages = (int*)realloc( pObjectImages, sizeof(int)*num );
      pNumObjects = num;
    }
  }
  int numObjects() const { return pNumObjects; }

private:
  int* pTileImages;
  int* pObjectImages;
	unsigned int pNumTiles;
	unsigned int pNumObjects;
};

/**
A tile view that can be used in tile based games.

@author Tommy Carlsson
*/
class TileView : public Widget
{
public:

  TileView( Frame* parent = NULL );
  virtual ~TileView(  );

  virtual void setTheme( Theme & t, const string prefix = "" );

  virtual ImageList& tileImages(  ) { return pTileImages; }
  virtual ImageList& objectImages(  ) { return pObjectImages; }
  virtual ImageList& spriteImages(  ) { return pSpriteImages; }

  virtual bool showGrid(  ) const { return pShowGrid; }
  virtual void showGrid( const bool enable ) { pShowGrid = enable; updated(); }
  virtual Color gridColor(  ) const { return pGridColor; }
  virtual void gridColor( const Color c ) { pGridColor = c; if ( pShowGrid ) updated(); }

  virtual List<TileSprite>& sprites(  ) { return pSprites; }

  virtual bool drawTiles(  ) const { return pDrawTiles; }
  virtual bool drawObjects(  ) const { return pDrawObjects; }
  virtual bool drawSprites(  ) const { return pDrawSprites; }
  virtual bool drawOverlays(  ) const { return pDrawOverlays; }

  virtual void setDrawTiles( const bool enable ) { pDrawTiles = enable; }
  virtual void setDrawObjects( const bool enable ) { pDrawObjects = enable; }
  virtual void setDrawSprites( const bool enable ) { pDrawSprites = enable; }
  virtual void setDrawOverlays( const bool enable ) { pDrawOverlays = enable; }

  virtual int tileWidth() const { return pTileWidth; }
  virtual int tileHeight() const { return pTileHeight; }
  virtual void setTileWidth( const int tw ) { pTileWidth = tw; }
  virtual void setTileHeight( const int th ) { pTileHeight = th; }

  virtual Tile& tiles( const unsigned int x, const unsigned int y ) { assert( (y*pNumX+x) < pNumX*pNumY ); return pTiles[y*pNumX+x]; }

  virtual void tileUpdated( const unsigned int x, const unsigned int y ) { updated(); }

  virtual unsigned int numTilesX(  ) const { return pNumX; }
  virtual unsigned int numTilesY(  ) const { return pNumY; }
  virtual void setNumTiles( const unsigned int numX, const unsigned int numY );

  virtual void render( ImageObject& img, const Rect& r );

  virtual void tileUpdated( const int x, const int y ) { updated(); }

  virtual Widget* mouseClick( int x, int y, MouseButtons mb );
  virtual Widget* mouseDblClick( int x, int y, MouseButtons mb );
  virtual Widget* mousePressed( int x, int y, MouseButtons mb );
  virtual Widget* mouseReleased( int x, int y, MouseButtons mb );

  signal2<Widget&, int> onDrawOverlay;
  signal1<Widget&> onBeforeDraw;
  signal1<Widget&> onAfterDraw;
  signal4<Widget&,int,int,MouseButtons> onTileClicked;

private:

  ImageList pTileImages;
  ImageList pObjectImages;
  ImageList pSpriteImages;

  List<TileSprite> pSprites;

  Color pGridColor;

  bool pShowGrid;
  bool pDrawTiles;
  bool pDrawObjects;
  bool pDrawSprites;
  bool pDrawOverlays;

  int pTileWidth;
  int pTileHeight;

  int pScrollX;
  int pScrollY;

  unsigned int pNumX;
  unsigned int pNumY;

  Tile* pTiles;

  void checkAlign();
  void allocateTiles();
  void freeTiles();
  int tileX( const int x ) const;
  int tileY( const int y ) const;

};

}

#endif
