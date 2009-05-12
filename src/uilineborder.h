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
#ifndef UIUILINEBORDER_H
#define UIUILINEBORDER_H

#include <uiborder.h>
#include <uicolor.h>
#include <uiutils.h>
#include <uiimageobject.h>

namespace Ui {

enum borderType { btLine };

/**
Border only using fillRect functions

@author Tommy Carlsson
*/
class LineBorder : public Border
{
public:
  LineBorder();
  ~LineBorder();

  virtual borderType type() const { return pType; }
  virtual void setType( const borderType bt );

  virtual Color lineColor() const { return pLineColor; }
  virtual void setLineColor( const Color c ) { pLineColor = c; }
  virtual Color bgColor() const { return pBgColor; }
  virtual void setBgColor( const Color c ) { pBgColor = c; }

  virtual void render(const Rect r, ImageObject& iobj);
  
	static void useWithLoader();
  static Border* themeLineBorderLoader( InifileSection* is, const ThemeLoadOptions& op );
  
private:

  borderType pType;
  Color pLineColor;
  Color pBgColor;

  //static BorderLoader lineBorderLoader;

};

}

#endif
