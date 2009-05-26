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


/**
@file
Headerfile for the Ui::Edit class
*/

#ifndef UIEDIT_H
#define UIEDIT_H

#include <gameui.h>
#include <uiwidget.h>
#include <uigui.h>
#include <uiborder.h>
#include <uiclipboard.h>
#include <math.h>

using std::wstring;
using namespace std;

namespace Ui {

/**
Control used for simple text input.

@author Tommy Carlsson
*/
class Edit : public Widget
{
public:

  Edit( Frame* parent = NULL );
  Edit( Frame* parent, int x, int y, int width, int height);

  virtual ~Edit(  );

  virtual void setTheme( Theme& t, const string prefix = "" );

  virtual void render( ImageObject& img, const Rect& r );
  virtual void setFocused( bool f );

  virtual Widget* mouseClick(int x, int y, MouseButtons mb);
  virtual Widget* mouseDblClick(int x, int y, MouseButtons mb);
  virtual Widget* mousePressed(int x, int y, MouseButtons mb);
  virtual Widget* mouseReleased(int x, int y, MouseButtons mb);
  virtual Widget* mouseMove( int x, int y, MouseButtons mb );
  virtual Widget* keyPressed( Key key );
  virtual Widget* keyReleased( Key key );

  virtual void timerTick();

  virtual wstring text(  );
  virtual void setText( wstring s );

  virtual wstring selectedText(  );
  virtual int selectionStart(  );
  virtual int selectionEnd(  );
  virtual int selectionSize(  );
  virtual void unselect();

  virtual bool readOnly(  ) const;
  virtual void setReadOnly( const bool enable = true );
  virtual int indexAt( int x );
  virtual int indexPos( int index );
  virtual int cursorIndex();
  virtual void setCursorIndex( int pos );
  virtual int cursorPos(  );

	virtual Rect getEditArea() { return Rect( 0, 0, clientVisibleWidth(), clientVisibleHeight() ); }

	virtual Widget* changed( );

	signal1<Widget*> onChange;


private:

  wstring pText;

  bool pReadonly;
  bool pDrawForward;
  int pDrawIndex;
  int pCursorIndex;
  int pSelStart;
  int pSelEnd;

  wstring renderText();
  void renderCursor();

};

}

#endif
