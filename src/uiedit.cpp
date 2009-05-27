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
Implementation of the Ui::Edit class
*/

#include <uiedit.h>
#include <uiutils.h>


namespace Ui {

Edit::Edit( Frame* parent )
{
  pReadonly = false;
  pDrawForward = true;
  pDrawIndex = 0;
  pCursorIndex = 0;
  pSelStart = 0;
  pSelEnd = 0;

  pText = L"";
  setHeight( 24 );

  setParent( parent );
}

Edit::Edit( Frame* parent, int x, int y, int width, int height )
{
  pReadonly = false;
  pDrawForward = true;
  pDrawIndex = 0;
  pCursorIndex = 0;
  pSelStart = 0;
  pSelEnd = 0;

  setBounds(x, y, width, height);

  pText = L"";

  setParent( parent );
}


Edit::~Edit()
{
}

void Edit::setTheme( Theme& t, const string prefix )
{
  beginUpdate();
	Widget::setTheme( t, prefix );
  setBorder( t.getBorder( prefix+"edit" ) );
  setFont( t.getFont( prefix+"edit" ) );
  setFontColor( t.getColor( prefix+"edit_font" ) );
	setCursor( t.getCursor( prefix+"edit" ) );
  endUpdate();
}


void Edit::setFocused( bool f )
{
  Widget::setFocused( f );
  if ( f ) {
		if ( !readOnly() ) {
			KeyCursor::cursorObject().setHeight( clientVisibleHeight() - 2 );
			KeyCursor::cursorObject().setPosition( cursorPos(), Utils::inMiddle( clientVisibleHeight(), KeyCursor::cursorObject().height() ) );
			KeyCursor::cursorObject().setEnabled( true );
		}
  }
	updated();
}

void Edit::render( ImageObject& img, const Rect& r )
{
  if ( !visible() ) return;
	if ( focused() ) {
	  if ( KeyCursor::cursorObject().getRect() == r ) {
	  	if ( !KeyCursor::cursorObject().shouldRenderBg() ) {
	  		KeyCursor::cursorObject().render( img, r );
	  	  return;
	  	}
		}
	}
  if (( pSelStart != pSelEnd ) && ( focused() )) {
    Color sc = Color( 180,220,255 );
    if ( pDrawForward ) {
      Rect r2;
      r2 = getEditArea();
//      r.applyBorder( border() );
      int start = selectionStart();
      int end = selectionEnd();
      start = indexPos( start ) + 1;
      end = indexPos( end ) + 1;

      if ( start < 0 ) start = 0;
      if ( start > r2.width ) start = r2.width;
      if ( end < 0 ) end = 0;
      if ( end > r2.width ) end = r2.width;

      r2.left += start;
      r2.width -= r2.width - end;
      r2.width -= start;

      r2.top += 1;
      r2.height -= 2;

      screen().fillRect( r2, sc );
    }
  }

  if ( font() != NULL ) {
    Rect r2 = getEditArea();
    //r2.applyBorder( border() );
    int theight = font()->textHeight();
    wstring t = renderText();
//    int twidth = font()->textWidth( t );
    r2.top += ( r2.height / 2 - theight / 2 );
      //r.left += bw;

    Color c( 0, 0, 0 );
    screen().outText( t, *font(), (int)r2.left,(int)r2.top,  c );

  }
	if ( focused() ) {
		KeyCursor::cursorObject().render( img, r );
	}

}


void Edit::renderCursor()
{
//  cout << "* Ui::Edit::renderCursor (  )" << endl;
}

wstring Edit::renderText()
{

  assert ( font() != NULL );
  if ( pText.length() == 0 )
    return L"";
  wstring rs = pText.substr( pDrawIndex, pText.length() - pDrawIndex );

  Rect r = getEditArea();
  //r.applyBorder( border() );
  int w = r.width;
//  if ( border() != NULL )
//    w -= border()->widthLeft + border()->widthRight;

  while( (font()->textWidth( rs ) > w) && (rs.length() >= 1) ) {
    rs.erase( rs.length() - 1 );//  = res.substr( 0, res.length() - 1 );
  }
 // cout << "!!! renderText len: " << res.length() << endl;


  //wstring rs = L"WWWWWWWWWWWWWWWWWWWWWWWWWWW";
  return rs;
//  return L"cvbc";
}


wstring Edit::text()
{
  return pText;
}


void Edit::setText( wstring s )
{
  pText = s;
  updated();
	changed( );
}


wstring Edit::selectedText()
{
  return pText.substr( selectionStart(), selectionSize() );
}


int Edit::selectionStart()
{
  if ( pSelStart <= pSelEnd ) {
    return pSelStart;
  } else {
    return pSelEnd;
  }
}


int Edit::selectionEnd()
{
  if ( pSelEnd >= pSelStart ) {
    return pSelEnd;
  } else {
    return pSelStart;
  }
}


int Edit::selectionSize()
{
  return selectionEnd() - selectionStart();
}

void Edit::unselect()
{
  pSelStart = 0;
  pSelEnd = 0;
}

bool Edit::readOnly(  ) const
{
  return pReadonly;
}


void Edit::setReadOnly( const bool enable )
{
  pReadonly = enable;
}


int Edit::indexAt( int x )
{

  Font* f = font();
  if ( f != NULL ) {
    Rect r = getEditArea();
    r.applyBorder( border() );
//    cout << "r: " << r.left << endl;
    int pos = r.left;
    int charw = 0;
    if ( pDrawForward ) {
//      if ( border() != NULL ) {
        //pos = r.left;
//      }
      wstring s = renderText();
      for( unsigned int i = 0; i < s.length(); i++ ){
        charw = f->charWidth( s[i] );
//        if ( x <= pos + charw / 2 - 1) {
        if ( x <= pos + f->textWidth( s.substr(0, i ) ) + charw / 2 ) {
          //cout << "!!! indexAt res: " << (pDrawIndex + i) << endl;
          return pDrawIndex + i;
        }
//        pos += charw;
      }
      //cout << "!!! indexAt res: " << (pDrawIndex + s.length()) << endl;
      return pDrawIndex + s.length();

    } else {
      assert( false );
    }
  }
  return 0;
}

int Edit::indexPos( int index )
{
  if ( pDrawForward ) {
    Font* f = font();
    if ( f != NULL ) {
      if ( pDrawIndex > index ) {
        return -1;
      }
      wstring s = pText.substr( 0, pDrawIndex );
      //int before = f->textWidth( s );
      s = pText.substr( pDrawIndex, index - pDrawIndex );
      return f->textWidth( s );
    } else {
      return 0;
    }
  } else {
    assert( false );
    return 0;
  }
}


int Edit::cursorIndex()
{
  return pCursorIndex;
}

void Edit::setCursorIndex( int pos )
{
  cout << "* Ui::Edit::setCursorIndex( " << pos << " )" << endl;
  int l = pText.length();
  if ( pos > l ) return;
  if ( pos < 0 ) return;

  pCursorIndex = pos;

  if ( focused() ) {

		KeyCursor::cursorObject().setPosition( cursorPos(), Utils::inMiddle( clientVisibleHeight(), KeyCursor::cursorObject().height() ) );
		KeyCursor::cursorObject().setVisible( true );

  }
}


int Edit::cursorPos(  )
{
  Font* f = font();
  if ( f != NULL ) {

		int borderRight = 0;
		int pos = 0;
//    int charw = 0;
    if ( pDrawForward ) {

      if ((text().length() == 0) || ( pCursorIndex < 0 )) return pos;

      wstring s = pText.substr( pDrawIndex, pText.length() - pDrawIndex );

      if ( pCursorIndex < pDrawIndex ) {
        pDrawIndex = pCursorIndex - 3;
        if ( pDrawIndex < 0 )
          pDrawIndex = 0;
        updated();
      }
			cout << "pos: " << pos << endl;
      pos += f->textWidth( s.substr(0, pCursorIndex - pDrawIndex ) );

      if ( pos >= width() - borderRight ) {
        pDrawIndex += 3;
        pos = cursorPos();
        updated();
      }

      return pos;
    } else {
      assert( false );
    }
  }
  return -1;
}

Widget* Edit::keyPressed( Key key )
{
  cout << "* Ui::Edit::keyPressed( key: " << key.unicode() << " keysym: UIK_" << key.keysymString( key.keysym() ) << endl;

  beginUpdate();

  ClipboardAction clipAction = CA_NONE;

  clipAction = gui().clipboard().getClipAction( key );
  if ( clipAction != CA_NONE ) {
    if ( ((clipAction == CA_COPY) || (clipAction == CA_CUT)) && ( selectionSize() > 0 ) ) {
      gui().clipboard().clear();
      gui().clipboard().setPlainText( selectedText() );
      if ( (clipAction == CA_CUT) && ( !pReadonly ) ) {
        if ( selectionStart() < pDrawIndex )
          setCursorIndex ( selectionStart() );
        pText.replace( selectionStart(), selectionSize(), L"" );
        setCursorIndex( selectionStart() );
        unselect();
        updated();
      }
    } else if (( clipAction == CA_PASTE ) && ( !pReadonly )) {
      if ( selectionSize() > 0 ) {
        pText.replace( selectionStart(), selectionSize(), L"" );
        setCursorIndex( selectionStart() );
      }
      pText.replace( cursorIndex(), 0, gui().clipboard().plainText() );
      int tmpPos = cursorIndex() + gui().clipboard().plainText().length();
      unselect();
      updated();
      setCursorIndex( tmpPos );
    }
  }

  if ( pReadonly ) {
    endUpdate();
    Widget::keyPressed( key );
    return this;
  }

  if ( clipAction != CA_NONE ) {
    // Do Nothing.
  } else if ( key.keysym() == KEY_BACKSPACE ) {
    if ( selectionSize() > 0 ) {
      pText.replace( selectionStart(), selectionSize(), L"" );
      int tmpPos = selectionStart();
      unselect();
      updated();
      setCursorIndex ( tmpPos );
    } else {
      if ( pText.length() > 0 ) {
        int pos = pCursorIndex;//cursorIndex();
        cout << "!!! Cursorindex1: " << pos << endl;
        if ( pos > 0 ) {
          setCursorIndex( pos - 1 );
          pText.replace( pos-1, 1, L"" );
          if ( (renderText().length() == 0) && ( pText.length() != 0 ) ) {
            pDrawIndex -= 3;
            if ( pDrawIndex == 0) pDrawIndex = 0;
          }
          updated();
        }
        cout << "!!! Cursorindex2: " << pos << endl;
      }
    }

  } else if ( key.keysym() == KEY_DELETE ) {
    if ( selectionSize() > 0 ) {
      if ( selectionStart() < pDrawIndex )
        setCursorIndex ( selectionStart() );
      pText.replace( selectionStart(), selectionSize(), L"" );
      setCursorIndex ( selectionStart() );
      cout << "!!! Cursorindex: " << cursorIndex() << endl;
      unselect();
      updated();
    } else {
      if ( pText.length() > 0 ) {
        int pos = cursorIndex();
        pText.replace( pos, 1, L"" );
        updated();
      }
    }

  } else if ( key.keysym() == KEY_RETURN ) {
  } else if ( key.keysym() == KEY_TAB ) {

  } else if ( key.keysym() == KEY_RIGHT ) {
    if ( key.isShiftPressed() ) {
      if ( selectionSize() == 0 ) {
        pSelStart = cursorIndex();
        pSelEnd = cursorIndex();
      }
			if ( pSelEnd < (int)pText.length() )
        pSelEnd++;
      updated();
      setCursorIndex ( pCursorIndex + 1 );
    } else {
      unselect();
      updated();
      setCursorIndex ( pCursorIndex + 1 );
    }

  } else if ( key.keysym() == KEY_LEFT ) {
    if ( key.isShiftPressed() ) {
      if ( selectionSize() == 0 ) {
        pSelStart = cursorIndex();
        pSelEnd = cursorIndex();
      }
      if ( pSelEnd > 0 )
        pSelEnd--;
      updated();
      setCursorIndex ( pCursorIndex - 1 );
    } else {
      unselect();
      updated();
      setCursorIndex ( pCursorIndex - 1 );
    }

  } else if ( key.keysym() == KEY_END ) {
    if ( key.isShiftPressed() ) {
      if ( selectionSize() == 0 )
        pSelStart = cursorIndex();
      pSelEnd = pText.length();
      updated();
    } else {
      unselect();
      updated();
    }
    setCursorIndex( pText.length() );

  } else if ( key.keysym() == KEY_HOME ) {
    if ( key.isShiftPressed() ) {
      if ( selectionSize() == 0 )
        pSelStart = cursorIndex();
      pSelEnd = 0;
      updated();
    } else {
      unselect();
      updated();
    }
    setCursorIndex ( 0 );

  } else {
    if ( key.unicode() != 0) {

      if ( selectionSize() > 0 ) {
        if ( selectionStart() < pDrawIndex )
          setCursorIndex ( selectionStart() );
        pText.replace( selectionStart(), selectionSize(), L"" );
        setCursorIndex( selectionStart() );
        unselect();
      }
      wchar_t c = key.unicode();
      wstring s;
      s = c;
      pText.replace( pCursorIndex, 0, s );

      updated();
      setCursorIndex ( pCursorIndex + 1 );
    }
  }
  endUpdate();
  Widget::keyPressed( key );
	changed( );
  return this;
}

Widget* Edit::keyReleased( Key key )
{
  Widget::keyReleased( key );
	changed( );
  return this;
}

void Edit::timerTick()
{

}


Widget* Edit::mouseClick(int x, int y, MouseButtons mb)
{
  Widget::mouseClick(x, y, mb);
  cout << "* Ui::Edit::mouseClick( x:" << x << " y: " << y << " )" << endl;
  Widget::mouseClick(x, y, mb);
  return this;
}


Widget* Edit::mouseDblClick(int x, int y, MouseButtons mb)
{
  Widget::mouseDblClick(x, y, mb);
  return this;
}


Widget* Edit::mouseMove( int x, int y, MouseButtons mb )
{
  //cout << "Ui::Widget::mouseMove(  )" << endl;

  beginUpdate();

  if ( mb.left ) {
    if ( x < 0 ) {
      pDrawIndex -= 1;
      if ( pDrawIndex < 0) pDrawIndex = 0;

      int i = indexAt( -1 );
      setCursorIndex( i );

      updated();
    } else if ( x > width() ) {
      pDrawIndex += 1;
			if ( pDrawIndex > (int)pText.length() ) pDrawIndex = pText.length();

      int i = indexAt( width() );
      setCursorIndex( i );

      updated();
    } else {

      int i = indexAt( x );
      if ( pSelEnd != i ) {
        pSelEnd = i;
        updated();
      }
      if ( i != cursorIndex() ) {
        setCursorIndex( i );
      }
    }
  }

  endUpdate();
  Widget::mouseMove(x, y, mb);
  return this;
}


Widget* Edit::mousePressed(int x, int y, MouseButtons mb)
{
  cout << "* Ui::Edit::mousePressed( x:" << x << " y: " << y << " )" << endl;

  beginUpdate();

  //Widget::mousePressed(x, y, mb);
  int i = indexAt( x );
//  cout << "! i:" << i << endl;
  pSelStart = i;
  pSelEnd = i;
  updated();
  if ( i != cursorIndex() ) {
    setCursorIndex( i );
  }
  grabMouseInput();

  endUpdate();
  Widget::mousePressed(x, y, mb);
  return this;
}


Widget* Edit::mouseReleased(int x, int y, MouseButtons mb)
{
  cout << "* Ui::Edit::mouseReleased( x:" << x << " y: " << y << " )" << endl;

  beginUpdate();

  releaseMouseInput();
  int i = indexAt( x );
  if ( pSelEnd != i ) {
    pSelEnd = i;
    updated();
  }
  if ( i != cursorIndex() ) {
    setCursorIndex( i );
  }

  endUpdate();
  Widget::mouseReleased(x, y, mb);
  return this;
}

Widget* Edit::changed( )
{
	onChange( this );
	return this;
}


}
