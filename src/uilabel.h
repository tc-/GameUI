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
#ifndef UIUILABEL_H
#define UIUILABEL_H

#include <uiwidget.h>
#include <uiborder.h>
#include <uiframe.h>
#include <uilist.h>

namespace Ui {

/**
Simple text output control

@author Tommy Carlsson
*/
class Label : public Widget
{
public:
  Label();
  Label( Frame* parent );
  ~Label();

  virtual void setTheme( Theme & t, const string prefix = "" );

  virtual HAlignType textHAlign() const { return pHAl; }
  virtual void setTextHAlign( const HAlignType al ) { pHAl = al; updated(); }
  virtual VAlignType textVAlign() const { return pVAl; }
  virtual void setTextVAlign( const VAlignType al ) { pVAl = al; updated(); }

  virtual wstring text();
  virtual void setText( wstring s );

  virtual bool multiline() const;
  virtual void setMultiline( const bool enable );

  virtual void render( ImageObject& img, const Rect& rr );

private:

  HAlignType pHAl;
  VAlignType pVAl;

  wstring pText;
  bool pMultiline;

};

}

#endif
