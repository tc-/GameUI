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


#ifndef UICLIPBOARD_H
#define UICLIPBOARD_H

#include <uikey.h>
#include <string>

using namespace std;

namespace Ui {

enum ClipboardAction {
  CA_NONE,
  CA_COPY,
  CA_CUT,
  CA_PASTE
};

/**
Class able to store and restore text for use as clipboard. Can be reimplemented to use other systems internal clipboards.

@author Tommy Carlsson
*/
class Clipboard {
public:

  Clipboard() { clear(); }
  virtual ~Clipboard() {}

  /**
   * Returns corresponding action to the Ui::Key object passed.
   * The keys ctrl+c(copy) ctrl+x(cut) ctrl+v(paste) are hardcoded.
   * @param k key to check.
   * @return UICA_NONE if key is not a key to cutnpaste otherwise returns UICA_COPY, UICA_CUT or UICA_PASTE.
   */
  virtual ClipboardAction getClipAction( Key& k ) {
    if ( (k.keysym() == KEY_c) && (k.isCtrlPressed()) ) {
      return CA_COPY;
    } else if ( (k.keysym() == KEY_x) && (k.isCtrlPressed()) ) {
      return CA_CUT;
    } else if ( (k.keysym() == KEY_v) && (k.isCtrlPressed()) ) {
      return CA_PASTE;
    } else {
      return CA_NONE;
    }
  }

  /**
   * Clears the clipboard from any data.
   * @note This function should be called before any new data is pasted into the clipboard.
   * @see Ui::Clipboard::clear()
   */
  virtual void clear() { pPlainText = L""; }
  /**
   * Returns true if clipboard is empty.
   * @see Ui::Clipboard::clear()
   * @return true if the clipboard is empty.
   */
  virtual bool isEmpty() { return (pPlainText.length() == 0); }

  /**
   * Pastes a plaintext text into clipboard.
   * @note Before pasting new data into the clipboard clear() should be called to erace all data previously in clipboard.
   * @see Ui::Clipboard::plainText() Ui::Clipboard::clear()
   * @param text The text to paste into clipboard.
   */
  virtual void setPlainText( wstring text ) { pPlainText = text; };
  /**
   * Returns the plaintext element in the clipboard.
   * @see Ui::Clipboard::setPlainText()
   * @return plaintext element of the clipboard.
   */
  virtual wstring plainText() { return pPlainText; }
  /**
   * Returns true if the clipboard has been assigned a plaintext element.
   * @see Ui::Clipboard::plainText()
   * @return true if the clipboard has been assigned a plaintext element.
   */
  virtual bool hasPlainText() { return (pPlainText.length() == 0); }

private:

  wstring pPlainText;

};

}

#endif
