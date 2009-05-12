/***************************************************************************
 *   Copyright (C) 2005 by Tommy Carlsson                                  *
 *   tc@coderworld.net                                                     *
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
#ifndef NETWALKWINDOW_H
#define NETWALKWINDOW_H

#include <uiwindowframe.h>
#include <uitileview.h>
#include <uilineborder.h>
#include <uipushbutton.h>
#include <uicombobox.h>
#include <uidropdownlist.h>
#include <uiimageobject.h>
#include <uisdlimageobject.h>
#include <uilabel.h>
#include <uitheme.h>
#include <uiutils.h>
#include <time.h>
#include <stdlib.h>


using namespace Ui;

/**
@author Tommy Carlsson
*/
class NetwalkWindow : public WindowFrame
{
public:

  LineBorder viewBorder;
  Label titleLabel;
  Label scoreLabel;
  PushButton newButton;
  Combobox skillCombo;
  DropdownList skillDropdown;
  DropListItem skillEasyItem;
  DropListItem skillNormalItem;
  DropListItem skillHardItem;
  TileView mapView;

  NetwalkWindow( Frame* parent, Font* f);
  ~NetwalkWindow();

  void newButtonClick( Widget& o );
  void mapViewMouseClick( Widget& o );
  void mapViewMousePressed( Widget& o, MouseButtons mb );
  void mapViewMouseMove( Widget& o, int x, int y, MouseButtons mb );
  void mapViewTileClicked( Widget& o, int x, int y, MouseButtons mb );
  void skillDropdownClick( DropdownList& list, DropListItem& item );
  void onTimerTick();

  void newGame(  );
  void setSkill( const int skill );

private:

  int pSizeX;
  int pSizeY;
  int pNumCli;

  int pServX;
  int pServY;

  int pCliConn;
  int pTurns;

  int pMouseX;
  int pMouseY;
  MouseButtons pMB;

  bool newRandomMap();
  bool connectClient( const int x, const int y, int dir = -1  );
//  bool connectLine( const int x1, const int y1, const int x2, const int y2  );
//  bool disconnectLine( const int x1, const int y1, const int x2, const int y2  );
  bool clientIsConnected( const int x, const int y );
  bool isClient(  const int x, const int y  );
  bool addDir( const int x, const int y, const int dir );
  bool removeDir( const int x, const int y, const int dir );
  void rotate( const int x, const int y, const bool clock );
  void checkFlow();
  void traceFlow( const int x, const int y, const int dir, const bool enable );
  bool hasDir( const int x, const int y, const int dir );

  void debugMap( const string ds );

};

#endif
