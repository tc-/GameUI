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


#include "config.h"

#include "netwalkwindow.h"
#include "SDL.h"
#include "stdlib.h"
#include "uiutils.h"

#ifndef UIDATADIR
#define UIDATADIR "."
#endif


NetwalkWindow::NetwalkWindow(Frame* parent, Font* f)
 : WindowFrame( parent )
{
  pSizeX = 6;
  pSizeY = 6;
  pNumCli = 8;

  beginUpdate();
  titleLabel.setParent( this );
  titleLabel.setTheme( Theme::defaultTheme() );

  scoreLabel.setParent( this );
  newButton.setParent( this );
  skillCombo.setParent( this );
  skillEasyItem.setText( L"Easy" );
  skillNormalItem.setText( L"Normal" );
  skillHardItem.setText( L"Hard" );
  skillDropdown.addItem( &skillEasyItem );
  skillDropdown.addItem( &skillNormalItem );
  skillDropdown.addItem( &skillHardItem );

  skillCombo.setDropdownList( &skillDropdown );

  skillDropdown.setTheme( Theme::defaultTheme() );

  skillCombo.setTheme( Theme::defaultTheme(), "readonly_" );
  skillCombo.setHeight( 20 );
  skillCombo.setName( "nw.skillCombo" );
  mapView.setParent( this );
  mapView.setTheme( Theme::defaultTheme() );
  mapView.setName( "nw.mapView" );

  titleLabel.setTop( 0 );
  titleLabel.setLeft( 0 );
  titleLabel.setWidth( 80 );
  titleLabel.setHeight( 20 );
//  titleLabel.setFont( f );
  titleLabel.setText( L"Netwalk" );
  titleLabel.setName( "nw.titleLabel" );

  scoreLabel.setTop( 20 );
  scoreLabel.setLeft( 0 );
  scoreLabel.setWidth( 40 );
  scoreLabel.setHeight( 20 );
  scoreLabel.setTheme( Theme::defaultTheme(), "score_" );
  scoreLabel.setText( L"0" );
  scoreLabel.setName( "nw.scoreLabel" );

  newButton.setTheme( Theme::defaultTheme() );
  newButton.setTop( 20 );
  newButton.setLeft( 42 );
  newButton.setWidth( 40 );
  newButton.setHeight( 20 );
  newButton.setText( L"New" );
  newButton.setName( "nw.newButton" );

  skillCombo.setTop( 20 );
  skillCombo.setLeft( 84 );
  skillCombo.setWidth( 78 );
  skillCombo.setText( L"Easy" );
  skillCombo.setReadOnly( true );

  mapView.setTop( 40 );
  mapView.setLeft( 0 );
  mapView.setTheme( Theme::defaultTheme() );

  string datadir;
  datadir = UIDATADIR;
  datadir += "/Images";

  Utils::setNotice( "Datadir is: " + datadir );

  SDLImageObject* imbg = new SDLImageObject();
  assert( imbg->loadImage( datadir+string("/net_bg.png") ) );
  mapView.tileImages().append( (ImageObject*&)imbg );

  SDLImageObject* imbg1 = new SDLImageObject();
  assert( imbg1->loadImage( datadir+"/net_flare1.png" ) );
  mapView.tileImages().append( (ImageObject*&)imbg1 );

  SDLImageObject* imbg2 = new SDLImageObject();
  assert( imbg2->loadImage( datadir+"/net_flare2.png" ) );
  mapView.tileImages().append( (ImageObject*&)imbg2 );

  SDLImageObject* imbg3 = new SDLImageObject();
  assert( imbg3->loadImage( datadir+"/net_flare3.png" ) );
  mapView.tileImages().append( (ImageObject*&)imbg3 );

  SDLImageObject* imo1 = new SDLImageObject();
  assert( imo1->loadImage( datadir+"/net_1u.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo1 );

  SDLImageObject* imo2 = new SDLImageObject();
  assert( imo2->loadImage( datadir+"/net_1r.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo2 );

  SDLImageObject* imo3 = new SDLImageObject();
  assert( imo3->loadImage( datadir+"/net_1d.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo3 );

  SDLImageObject* imo4 = new SDLImageObject();
  assert( imo4->loadImage( datadir+"/net_1l.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo4 );

  SDLImageObject* imo5 = new SDLImageObject();
  assert( imo5->loadImage( datadir+"/net_ph.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo5 );

  SDLImageObject* imo6 = new SDLImageObject();
  assert( imo6->loadImage( datadir+"/net_pv.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo6 );

  SDLImageObject* imo7 = new SDLImageObject();
  assert( imo7->loadImage( datadir+"/net_tur.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo7 );

  SDLImageObject* imo8 = new SDLImageObject();
  assert( imo8->loadImage( datadir+"/net_tul.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo8 );

  SDLImageObject* imo9 = new SDLImageObject();
  assert( imo9->loadImage( datadir+"/net_tdr.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo9 );

  SDLImageObject* imo10 = new SDLImageObject();
  assert( imo10->loadImage( datadir+"/net_tdl.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo10 );

  SDLImageObject* imo11 = new SDLImageObject();
  assert( imo11->loadImage( datadir+"/net_3u.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo11 );

  SDLImageObject* imo12 = new SDLImageObject();
  assert( imo12->loadImage( datadir+"/net_3r.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo12 );

  SDLImageObject* imo13 = new SDLImageObject();
  assert( imo13->loadImage( datadir+"/net_3d.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo13 );

  SDLImageObject* imo14 = new SDLImageObject();
  assert( imo14->loadImage( datadir+"/net_3l.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo14 );


  SDLImageObject* imo15 = new SDLImageObject();
  assert( imo15->loadImage( datadir+"/net_1u2.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo15 );

  SDLImageObject* imo16 = new SDLImageObject();
  assert( imo16->loadImage( datadir+"/net_1r2.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo16 );

  SDLImageObject* imo17 = new SDLImageObject();
  assert( imo17->loadImage( datadir+"/net_1d2.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo17 );

  SDLImageObject* imo18 = new SDLImageObject();
  assert( imo18->loadImage( datadir+"/net_1l2.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo18 );

  SDLImageObject* imo19 = new SDLImageObject();
  assert( imo19->loadImage( datadir+"/net_ph2.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo19 );

  SDLImageObject* imo20 = new SDLImageObject();
  assert( imo20->loadImage( datadir+"/net_pv2.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo20 );

  SDLImageObject* imo21 = new SDLImageObject();
  assert( imo21->loadImage( datadir+"/net_tur2.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo21 );

  SDLImageObject* imo22 = new SDLImageObject();
  assert( imo22->loadImage( datadir+"/net_tul2.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo22 );

  SDLImageObject* imo23 = new SDLImageObject();
  assert( imo23->loadImage( datadir+"/net_tdr2.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo23 );

  SDLImageObject* imo24 = new SDLImageObject();
  assert( imo24->loadImage( datadir+"/net_tdl2.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo24 );

  SDLImageObject* imo25 = new SDLImageObject();
  assert( imo25->loadImage( datadir+"/net_3u2.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo25 );

  SDLImageObject* imo26 = new SDLImageObject();
  assert( imo26->loadImage( datadir+"/net_3r2.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo26 );

  SDLImageObject* imo27 = new SDLImageObject();
  assert( imo27->loadImage( datadir+"/net_3d2.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo27 );

  SDLImageObject* imo28 = new SDLImageObject();
  assert( imo28->loadImage( datadir+"/net_3l2.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo28 );


  SDLImageObject* imo29 = new SDLImageObject();
  assert( imo29->loadImage( datadir+"/net_serv.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo29 );

  SDLImageObject* imo30 = new SDLImageObject();
  assert( imo30->loadImage( datadir+"/net_cli.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo30 );

  SDLImageObject* imo31 = new SDLImageObject();
  assert( imo31->loadImage( datadir+"/net_cli2.png" ) );
  mapView.objectImages().append( (ImageObject*&)imo31 );


  skillDropdown.onItemClicked.connect( this, &NetwalkWindow::skillDropdownClick );
  newButton.onMouseClick.connect( this, &NetwalkWindow::newButtonClick );
  mapView.onMouseMove.connect( this, &NetwalkWindow::mapViewMouseMove );
  mapView.onMousePressed.connect( this, &NetwalkWindow::mapViewMousePressed );
  mapView.onMouseClick.connect( this, &NetwalkWindow::mapViewMouseClick );
  mapView.onTileClicked.connect( this, &NetwalkWindow::mapViewTileClicked );

  titleLabel.setVisible( true );
  scoreLabel.setVisible( true );
  newButton.setVisible( true );
  skillCombo.setVisible( true );
  mapView.setVisible( true );

  endUpdate();
}


NetwalkWindow::~NetwalkWindow()
{
}

void NetwalkWindow::newGame(  )
{

  mapView.setNumTiles( pSizeX, pSizeY );
  do {

  for( int y = 0; y < pSizeY; y++ ){
    for( int x = 0; x < pSizeX; x++ ){
      mapView.tiles( x, y ).setNumTiles( 2 );
      mapView.tiles( x, y ).tileImage( 0 ) = 0;
      mapView.tiles( x, y ).tileImage( 1 ) = -1;
      mapView.tiles( x, y ).setNumObjects( 1 );
      mapView.tiles( x, y ).objectImage( 0 ) = -1;
    }
  }

  } while (!newRandomMap()) ;
  pTurns = 0;
  mapView.updated();
  scoreLabel.setText( Utils::toWString(pTurns) );
}

bool NetwalkWindow::newRandomMap()
{
  int sdf = time(NULL);
//  cout << "rand: " << sdf << endl;
  srand ( sdf );
  bool found = false;
  int x;
  int y;
  for( int i = 0; i < pNumCli; i++ ) {
    while( !found ){
      x = rand() % pSizeX;
      y = rand() % pSizeY;
      if ( mapView.tiles(x, y).numObjects() == 1 ) {
        found = true;
        mapView.tiles(x, y).setNumObjects( 2 );
        mapView.tiles(x, y).objectImage( 0 ) = -1;
        mapView.tiles(x, y).objectImage( 1 ) = 30;
      //  cout << "Cli" << i << ": (" << x << ";" << y << ")" << endl;
      }
    }
    found = false;
  }

  while( !found ){
    pServX = rand() % pSizeX;
    pServY = rand() % pSizeY;
    if ( mapView.tiles(pServX, pServY).numObjects() == 1 ) {
      found = true;
      mapView.tiles(pServX, pServY).setNumObjects( 2 );
      mapView.tiles(pServX, pServY).objectImage( 0 ) = -1;
      mapView.tiles(pServX, pServY).objectImage( 1 ) = 28;
 //     cout << "Server: (" << pServX << ";" << pServY << ")" << endl;
    }
  }
  bool complete;
  do {
    complete = true;
    for( y = 0; y < pSizeY; y++ ){
      for( x = 0; x < pSizeY; x++ ){
        if ( isClient(x, y) ) {
          if ( !clientIsConnected( x, y ) ) {
  //          cout << "Conn Cli: (" << x << ";" << y << ")" << endl;
            if (!connectClient( x, y ) ) {
  //            cout << "!!! Conn Cli: (" << x << ";" << y << ")" << endl;
              return false;
/*              debugMap("Failed");
              mapView.tiles(x, y).setNumObjects( 1 );
              mapView.tiles(x, y).objectImage( 0 ) = -1;
              removeDir(x+1,y,3);
              removeDir(x-1,y,1);
              removeDir(x,y+1,0);
              removeDir(x,y-1,2);
              complete = false;
              for( int y2 = 0; y2 < pSizeX; y2++ ){
                for( int x2 = 0; x2 < pSizeX; x2++ ){
                  if ( ( mapView.tiles(x2, y2).objectImage( 0 ) > -1 ) && ( mapView.tiles(x2, y2).objectImage( 0 ) < 14 ))
                    mapView.tiles(x2, y2).objectImage( 0 ) = -1;
                }
              }*/
            } else {
              for( int y2 = 0; y2 < pSizeX; y2++ ){
                for( int x2 = 0; x2 < pSizeX; x2++ ){
                  if ( ( mapView.tiles(x2, y2).objectImage( 0 ) > -1 ) && ( mapView.tiles(x2, y2).objectImage( 0 ) < 14 ))
                    mapView.tiles(x2, y2).objectImage( 0 ) += 14;
                }
              }
            }
          }
        }
      }
    }
    if ( ! complete ) {
      found = false;
      while( !found ){
        x = rand() % pSizeX;
        y = rand() % pSizeY;
        if ( mapView.tiles(x, y).numObjects() == 1 ) {
          found = true;
          mapView.tiles(x, y).setNumObjects( 2 );
          mapView.tiles(x, y).objectImage( 0 ) = -1;
          mapView.tiles(x, y).objectImage( 1 ) = 30;
        }
      }
    }
  } while ( !complete );
  for ( int i = 0 ; i < (pSizeX*pSizeY)/2; i++ ){
    x = rand() % pSizeX;
    y = rand() % pSizeY;
    rotate(x,y,true);
    x = rand() % pSizeX;
    y = rand() % pSizeY;
    rotate(x,y,false);
  }
  checkFlow();
  return true;
}

bool NetwalkWindow::addDir( const int x, const int y, const int dir )
{
  if ( (x < 0) || ( x >= pSizeX) ) return false;
  if ( (y < 0) || ( y >= pSizeY) ) return false;

  int t = mapView.tiles( x, y ).objectImage( 0 );
  int a = 0;
  if ( (t > 13) ) {
    a = 14;
    t -= 14;
  }
  if ( (x == pServX) && (y == pServY) ) a = 14;

  if ( dir == 0 ) {
    if ( t == -1 ) t = dir;
    else if ( t == 0 ) return true;
    else if ( t == 1 ) t = 6;
    else if ( t == 2 ) t = 5;
    else if ( t == 3 ) t = 7;
    else if ( t == 4 ) t = 10;
    else if ( t == 5 ) return true;
    else if ( t == 6 ) return true;
    else if ( t == 7 ) return true;
    else if ( t == 8 ) t = 11;
    else if ( t == 9 ) t = 13;
    else if ( t == 10 ) return true;
    else if ( t == 11 ) return true;
    else if ( t == 12 ) return false;
    else if ( t == 13 ) return true;

  } else if ( dir == 1 ) {
    if ( t == -1 ) t = dir;
    else if ( t == 0 ) t = 6;
    else if ( t == 1 ) return true;
    else if ( t == 2 ) t = 8;
    else if ( t == 3 ) t = 4;
    else if ( t == 4 ) return true;
    else if ( t == 5 ) t = 11;
    else if ( t == 6 ) return true;
    else if ( t == 7 ) t = 10;
    else if ( t == 8 ) return true;
    else if ( t == 9 ) t = 12;
    else if ( t == 10 ) return true;
    else if ( t == 11 ) return true;
    else if ( t == 12 ) return true;
    else if ( t == 13 ) return false;

  } else if ( dir == 2 ) {
    if ( t == -1 ) t = dir;
    else if ( t == 0 ) t = 5;
    else if ( t == 1 ) t = 8;
    else if ( t == 2 ) return true;
    else if ( t == 3 ) t = 9;
    else if ( t == 4 ) t = 12;
    else if ( t == 5 ) return true;
    else if ( t == 6 ) t = 11;
    else if ( t == 7 ) t = 13;
    else if ( t == 8 ) return true;
    else if ( t == 9 ) return true;
    else if ( t == 10 ) return false;
    else if ( t == 11 ) return true;
    else if ( t == 12 ) return true;
    else if ( t == 13 ) return true;

  } else if ( dir == 3 ) {
    if ( t == -1 ) t = dir;
    else if ( t == 0 ) t = 7;
    else if ( t == 1 ) t = 4;
    else if ( t == 2 ) t = 9;
    else if ( t == 3 ) return true;
    else if ( t == 4 ) return true;
    else if ( t == 5 ) t = 13;
    else if ( t == 6 ) t = 10;
    else if ( t == 7 ) return true;
    else if ( t == 8 ) t = 12;
    else if ( t == 9 ) return true;
    else if ( t == 10 ) return true;
    else if ( t == 11 ) return false;
    else if ( t == 12 ) return true;
    else if ( t == 13 ) return true;

  }
  t += a;
  mapView.tiles( x, y ).objectImage( 0 ) = t;
  return true;
}

bool NetwalkWindow::removeDir( const int x, const int y, const int dir )
{
  if ( (x < 0) || ( x >= pSizeX) ) return false;
  if ( (y < 0) || ( y >= pSizeY) ) return false;

  int t = mapView.tiles( x, y ).objectImage( 0 );
  int a = 0;
  if ( t > 13 ) {
    a = 14;
    t -= 14;
  }

  if ( dir == 0 ) {
    if ( t == -1 ) return true;
    else if ( t == 0 ) t = -1;
    else if ( t == 1 ) return true;
    else if ( t == 2 ) return true;
    else if ( t == 3 ) return true;
    else if ( t == 4 ) return true;
    else if ( t == 5 ) t = 2;
    else if ( t == 6 ) t = 1;
    else if ( t == 7 ) t = 3;
    else if ( t == 8 ) return true;
    else if ( t == 9 ) return true;
    else if ( t == 10 ) t = 4;
    else if ( t == 11 ) t = 8;
    else if ( t == 12 ) return true;
    else if ( t == 13 ) t = 9;

  } else if ( dir == 1 ) {
    if ( t == -1 ) return true;
    else if ( t == 0 ) return true;
    else if ( t == 1 ) t = -1;
    else if ( t == 2 ) return true;
    else if ( t == 3 ) return true;
    else if ( t == 4 ) t = 3;
    else if ( t == 5 ) return true;
    else if ( t == 6 ) t = 0;
    else if ( t == 7 ) return true;
    else if ( t == 8 ) t = 2;
    else if ( t == 9 ) return true;
    else if ( t == 10 ) t = 7;
    else if ( t == 11 ) t = 5;
    else if ( t == 12 ) t = 9;
    else if ( t == 13 ) return true;

  } else if ( dir == 2 ) {
    if ( t == -1 ) return true;
    else if ( t == 0 ) return true;
    else if ( t == 1 ) return true;
    else if ( t == 2 ) t = -1;
    else if ( t == 3 ) return true;
    else if ( t == 4 ) return true;
    else if ( t == 5 ) t = 0;
    else if ( t == 6 ) return true;
    else if ( t == 7 ) return true;
    else if ( t == 8 ) t = 1;
    else if ( t == 9 ) t = 3;
    else if ( t == 10 ) return true;
    else if ( t == 11 ) t = 6;
    else if ( t == 12 ) t = 4;
    else if ( t == 13 ) t = 7;

  } else if ( dir == 3 ) {
    if ( t == -1 ) return true;
    else if ( t == 0 ) return true;
    else if ( t == 1 ) return true;
    else if ( t == 2 ) return true;
    else if ( t == 3 ) t = -1;
    else if ( t == 4 ) t = 1;
    else if ( t == 5 ) return true;
    else if ( t == 6 ) return true;
    else if ( t == 7 ) t = 0;
    else if ( t == 8 ) return true;
    else if ( t == 9 ) t = 2;
    else if ( t == 10 ) t = 6;
    else if ( t == 11 ) return true;
    else if ( t == 12 ) t = 8;
    else if ( t == 13 ) t = 5;

  }

  if ( t != -1 )
    t += a;
  mapView.tiles( x, y ).objectImage( 0 ) = t;
  return true;
}


void NetwalkWindow::rotate( const int x, const int y, const bool clock )
{
  if ( (x < 0) || ( x >= pSizeX) ) return;
  if ( (y < 0) || ( y >= pSizeY) ) return;
  int t = mapView.tiles( x, y ).objectImage( 0 );

  int a = 0;
  if ( (t > 13) ) {
    a = 14;
    t -= 14;
  }

  if ( t == -1 ) return;
  if ( clock ) {
    if ( t == 0 ) t = 1;
    else if ( t == 1 ) t = 2;
    else if ( t == 2 ) t = 3;
    else if ( t == 3 ) t = 0;
    else if ( t == 4 ) t = 5;
    else if ( t == 5 ) t = 4;
    else if ( t == 6 ) t = 8;
    else if ( t == 7 ) t = 6;
    else if ( t == 8 ) t = 9;
    else if ( t == 9 ) t = 7;
    else if ( t == 10 ) t = 11;
    else if ( t == 11 ) t = 12;
    else if ( t == 12 ) t = 13;
    else if ( t == 13 ) t = 10;
  } else {
    if ( t == 0 ) t = 3;
    else if ( t == 1 ) t = 0;
    else if ( t == 2 ) t = 1;
    else if ( t == 3 ) t = 2;
    else if ( t == 4 ) t = 5;
    else if ( t == 5 ) t = 4;
    else if ( t == 6 ) t = 7;
    else if ( t == 7 ) t = 9;
    else if ( t == 8 ) t = 6;
    else if ( t == 9 ) t = 8;
    else if ( t == 10 ) t = 13;
    else if ( t == 11 ) t = 10;
    else if ( t == 12 ) t = 11;
    else if ( t == 13 ) t = 12;
  }
  t += a;
  mapView.tiles( x, y ).objectImage( 0 ) = t;
}

void NetwalkWindow::checkFlow()
{
  for( int y = 0; y < pSizeY; y++ ){
    for( int x = 0; x < pSizeX; x++ ){
      int t = mapView.tiles(x,y).objectImage(0);
      if ( isClient(x,y) )
        mapView.tiles(x,y).objectImage(1) = 29;
      if ( t > 13 ) {
        mapView.tiles(x,y).objectImage(0) = t - 14;
      }
    }
  }
  traceFlow( pServX, pServY, -1, true );
}

bool NetwalkWindow::hasDir( const int x, const int y, const int dir )
{
  if ( (x < 0) || ( x >= pSizeX) ) return false;
  if ( (y < 0) || ( y >= pSizeY) ) return false;

  int t = mapView.tiles(x,y).objectImage(0);
  if ( t == -1 ) return false;
  if ( (t > 13) ) t -= 14;

  if ( dir == 0 ) {
    if ( t == 0 ) return true;
    if ( t == 1 ) return false;
    if ( t == 2 ) return false;
    if ( t == 3 ) return false;
    if ( t == 4 ) return false;
    if ( t == 5 ) return true;
    if ( t == 6 ) return true;
    if ( t == 7 ) return true;
    if ( t == 8 ) return false;
    if ( t == 9 ) return false;
    if ( t == 10 ) return true;
    if ( t == 11 ) return true;
    if ( t == 12 ) return false;
    if ( t == 13 ) return true;

  } else if ( dir == 1 ) {
    if ( t == 0 ) return false;
    if ( t == 1 ) return true;
    if ( t == 2 ) return false;
    if ( t == 3 ) return false;
    if ( t == 4 ) return true;
    if ( t == 5 ) return false;
    if ( t == 6 ) return true;
    if ( t == 7 ) return false;
    if ( t == 8 ) return true;
    if ( t == 9 ) return false;
    if ( t == 10 ) return true;
    if ( t == 11 ) return true;
    if ( t == 12 ) return true;
    if ( t == 13 ) return false;
  } else if ( dir == 2 ) {
    if ( t == 0 ) return false;
    if ( t == 1 ) return false;
    if ( t == 2 ) return true;
    if ( t == 3 ) return false;
    if ( t == 4 ) return false;
    if ( t == 5 ) return true;
    if ( t == 6 ) return false;
    if ( t == 7 ) return false;
    if ( t == 8 ) return true;
    if ( t == 9 ) return true;
    if ( t == 10 ) return false;
    if ( t == 11 ) return true;
    if ( t == 12 ) return true;
    if ( t == 13 ) return true;
  } else if ( dir == 3 ) {
    if ( t == 0 ) return false;
    if ( t == 1 ) return false;
    if ( t == 2 ) return false;
    if ( t == 3 ) return true;
    if ( t == 4 ) return true;
    if ( t == 5 ) return false;
    if ( t == 6 ) return false;
    if ( t == 7 ) return true;
    if ( t == 8 ) return false;
    if ( t == 9 ) return true;
    if ( t == 10 ) return true;
    if ( t == 11 ) return false;
    if ( t == 12 ) return true;
    if ( t == 13 ) return true;
  }
  return false;
}


void NetwalkWindow::traceFlow( const int x, const int y, const int dir, const bool enable )
{
  if ( (x < 0) || ( x >= pSizeX) ) return;
  if ( (y < 0) || ( y >= pSizeY) ) return;

  if ( dir != -1 )
    if ( !hasDir( x, y, (dir + 2) % 4) ) return;

  int t = mapView.tiles(x,y).objectImage(0);
  if ( (enable) && ( t != -1 ) && ( t < 14) ) {
    mapView.tiles(x,y).objectImage(0) = t + 14;
    if ( isClient(x,y) ) {
      mapView.tiles(x,y).objectImage(1) = 30;
      pCliConn++;
    }
  } else if ( (enable) && ( t > 14 ) ) {
    return;
  } else if ( (!enable) && ( t > 14 ) ) {
    mapView.tiles(x,y).objectImage(0) = t - 14;
  } else if ( (!enable) && ( t != -1 ) && ( t < 14) ) {
    return;
  }


  if ( (dir != 2 ) && (hasDir(x,y,0)) ) { // Try Up
    traceFlow( x, y-1, 0, enable );
  }
  if ( (dir != 3) && (hasDir(x,y,1)) ) { // Try Right
    traceFlow( x+1, y, 1, enable );
  }
  if ( (dir != 0) && (hasDir(x,y,2)) ) { // Try Down
    traceFlow( x, y+1, 2, enable );
  }
  if ( (dir != 1) && (hasDir(x,y,3)) ) { // Try Left
    traceFlow( x-1, y, 3, enable );
  }

}


bool NetwalkWindow::connectClient( const int x, const int y, int dir )
{
  if ( (x < 0) || ( x >= pSizeX) ) return false;
  if ( (y < 0) || ( y >= pSizeY) ) return false;

  bool triedUp = false;
  bool triedDown = false;
  bool triedRight = false;
  bool triedLeft = false;

  if ( dir == 0 )
    triedDown = true;
  else if ( dir == 1 )
    triedLeft = true;
  else if ( dir == 2 )
    triedUp = true;
  else if ( dir == 3 )
    triedRight = true;

  int r;
  while ( (!triedUp) || (!triedDown) || (!triedLeft) || (!triedRight) ) {
    r = rand() % 4;
    if ( (r == 0) && (!triedUp) ) {
      if ( (!isClient( x, y-1 )) && ( y-1 >= 0) ) {
        if ( ( mapView.tiles(x, y-1).objectImage( 0 ) == -1 ) || ( mapView.tiles(x, y-1).objectImage( 0 ) > 13 ) ) {
          if ( ( addDir(x, y, r) ) && ( addDir(x, y-1, (r + 2) % 4) ) ) {
            if ( mapView.tiles(x, y-1).objectImage( 0 ) > 13 ) {
              //mapView.tiles(x, y).objectImage( 0 ) += 14;
              return true;
            } else {
              if ( connectClient( x, y-1, r) ) {
                //mapView.tiles(x, y).objectImage( 0 ) += 14;
                return true;
              }
            }
          }
          removeDir(x, y, r);
          removeDir(x, y-1, (r + 2) % 4);
        }
      }
      triedUp = true;

    } else if ( (r == 1) && (!triedRight) ) {
      if ( (!isClient( x+1, y )) && ( x+1 < pSizeX) ) {
        if ( ( mapView.tiles(x+1, y).objectImage( 0 ) == -1 ) || ( mapView.tiles(x+1, y).objectImage( 0 ) > 13 ) ) {
          if ( ( addDir(x, y, r) ) && ( addDir(x+1, y, (r + 2) % 4) ) ) {
            if ( mapView.tiles(x+1, y).objectImage( 0 ) > 13 ) {
             // mapView.tiles(x, y).objectImage( 0 ) += 14;
              return true;
            } else {
              if ( connectClient(x+1, y, r) ) {
               // mapView.tiles(x, y).objectImage( 0 ) += 14;
                return true;
              }
            }
          }
          removeDir(x, y, r);
          removeDir(x+1, y, (r + 2) % 4);
        }
      }
      triedRight = true;

    } else if ( (r == 2) && (!triedDown) ) {
      if ( (!isClient( x, y+1 )) && ( y+1 < pSizeY) ) {
        if ( ( mapView.tiles(x, y+1).objectImage( 0 ) == -1 ) || ( mapView.tiles(x, y+1).objectImage( 0 ) > 13 ) ) {
          if ( ( addDir(x, y, r) ) && ( addDir(x, y+1, (r + 2) % 4) ) ) {
            if ( mapView.tiles(x, y+1).objectImage( 0 ) > 13 ) {
           //   mapView.tiles(x, y).objectImage( 0 ) += 14;
              return true;
            } else {
              if ( connectClient(x, y+1, r) ) {
             //   mapView.tiles(x, y).objectImage( 0 ) += 14;
                return true;
              }
            }
          }
          removeDir(x, y, r);
          removeDir(x, y+1, (r + 2) % 4);
        }
      }
      triedDown = true;

    } else if ( (r == 3) && (!triedLeft) ) {
      if ( (!isClient( x-1, y )) && ( x-1 >= 0) ) {
        if ( ( mapView.tiles(x-1, y).objectImage( 0 ) == -1 ) || ( mapView.tiles(x-1, y).objectImage( 0 ) > 13 ) ) {
          if ( ( addDir(x, y, r) ) && ( addDir(x-1, y, (r + 2) % 4) ) ) {
            if ( mapView.tiles(x-1, y).objectImage( 0 ) > 13 ) {
         //     mapView.tiles(x, y).objectImage( 0 ) += 14;
              return true;
            } else {
              if ( connectClient(x-1, y, r) ) {
           //     mapView.tiles(x, y).objectImage( 0 ) += 14;
                return true;
              }
            }
          }
          removeDir(x, y, r);
          removeDir(x-1, y, (r + 2) % 4);
        }
      }
      triedLeft = true;

    }
  }

  return false;
}


bool NetwalkWindow::isClient(  const int x, const int y  )
{
  if ( (x < 0) || ( x >= pSizeX) ) return false;
  if ( (y < 0) || ( y >= pSizeY) ) return false;
  if ( mapView.tiles( x, y ).numObjects() > 1 ) {
    if ( mapView.tiles( x, y ).objectImage( 1 ) != 28 ) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

void NetwalkWindow::debugMap( const string ds )
{
  cout << ds << endl << "  ";
  for( int y = 0; y < pSizeY; y++ ){
    for( int x = 0; x < pSizeY; x++ ){
      cout << mapView.tiles( x, y ).objectImage( 0 );
      if (mapView.tiles( x, y ).numObjects() > 1 ) {
        if ( mapView.tiles( x, y ).objectImage( 1 ) == 28 )
          cout << "s ";
        else if ( mapView.tiles( x, y ).objectImage( 1 ) == 29 )
          cout << "c ";
        else if ( mapView.tiles( x, y ).objectImage( 1 ) == 30 )
          cout << "C ";
        else
          cout << "? ";
      } else {
        cout << "  ";
      }
    }
    cout << endl << "  ";
  }
  cout << endl;
}

bool NetwalkWindow::clientIsConnected( const int x, const int y )
{
  if ( (x < pSizeX) && ( x >= 0) ) return false;
  if ( (y < pSizeY) && ( y >= 0) ) return false;

  if ( mapView.tiles( x, y ).numObjects() > 1 ) {
    if (mapView.tiles( x, y ).objectImage( 1 ) == 28 )
      return true;
    else if ( mapView.tiles( x, y ).objectImage( 0 ) > 13 )
      return true;
    else
      return false;
  } else {
    return false;
  }
}

void NetwalkWindow::setSkill( const int skill )
{
  int bw = 0;
  int bh = 0;
  if ( border() != NULL ) {
    bw = border()->widthLeft + border()->widthRight;
    bh = border()->heightBottom + border()->heightTop;
  }
  //beginUpdate();
  if ( skill == 0 ) {
    pSizeX = 5;
    pSizeY = 5;
    pNumCli = 6;
    setWidth( (5 * 32) + 2 + bw );
    setHeight( (5 * 32) + 2 + bh + 40 );
    mapView.setWidth( (5 * 32) + 2 );
    mapView.setHeight( mapView.width() );
    return;
  } else if ( skill == 1 ) {
    pSizeX = 8;
    pSizeY = 8;
    pNumCli = 16;
  } else if ( skill == 2 ) {
    pSizeX = 10;
    pSizeY = 10;
    pNumCli = 22;
  }

  setWidth( (pSizeX * 32) + 2 + bw );
  setHeight( (pSizeY * 32) + 2 + bh + 40 );
  mapView.setWidth( (pSizeX * 32) + 2 );
  mapView.setHeight( mapView.width() );
  updated();
  //endUpdate();
  newGame();
}


void NetwalkWindow::newButtonClick( Widget& o )
{
  newGame();
}

void NetwalkWindow::mapViewMouseClick( Widget& o )
{

}

void NetwalkWindow::mapViewMousePressed( Widget& o, MouseButtons mb )
{
  pMB = mb;
}

void NetwalkWindow::mapViewMouseMove( Widget& o, int x, int y, MouseButtons mb )
{
  pMouseX = x;
  pMouseY = y;
  pMB = mb;
}

void NetwalkWindow::mapViewTileClicked( Widget& o, int x, int y, MouseButtons mb )
{
  if ( mb.left ) {
    rotate( x, y, true );
    pCliConn = 0;
    checkFlow();
    scoreLabel.setText( Utils::toWString(++pTurns) );
    o.updated();
  } else if ( mb.right ) {
    rotate( x, y, false );
    pCliConn = 0;
    checkFlow();
    scoreLabel.setText( Utils::toWString(++pTurns) );
    o.updated();
  }
}


void NetwalkWindow::skillDropdownClick( DropdownList& list, DropListItem& item )
{
  if ( item.text() == L"Easy" ) {
    setSkill( 0 );
  } else if ( item.text() == L"Normal" ) {
    setSkill( 1 );
  } else if ( item.text() == L"Hard" ) {
    setSkill( 2 );
  }
  newGame();
  //newRandomMap();
}

void NetwalkWindow::onTimerTick()
{
}


