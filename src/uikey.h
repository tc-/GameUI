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
Header and implementationfile of the Ui::Key class
*/

#ifndef KEYEY_H
#define KEYEY_H

#include <gameui.h>
#include <string>
#include <iostream>

using namespace std;

namespace Ui {


typedef int Keysym;

const int KEY_NONE = 0;
const int KEY_BACKSPACE = 1;
const int KEY_TAB = 2;
const int KEY_CLEAR = 3;
const int KEY_RETURN = 4;
const int KEY_PAUSE = 5;
const int KEY_ESCAPE = 6;
const int KEY_SPACE = 7;
const int KEY_EXCLAIM = 8;
const int KEY_QUOTEDBL = 9;
const int KEY_HASH = 10;
const int KEY_DOLLAR = 11;
const int KEY_AMPERSAND = 12;
const int KEY_QUOTE = 13;
const int KEY_LEFTPAREN = 14;
const int KEY_RIGHTPAREN = 15;
const int KEY_ASTERISK = 16;
const int KEY_PLUS = 17;
const int KEY_COMMA = 18;
const int KEY_MINUS = 19;
const int KEY_PERIOD = 20;
const int KEY_SLASH = 21;
const int KEY_0 = 22;
const int KEY_1 = 23;
const int KEY_2 = 24;
const int KEY_3 = 25;
const int KEY_4 = 26;
const int KEY_5 = 27;
const int KEY_6 = 28;
const int KEY_7 = 29;
const int KEY_8 = 30;
const int KEY_9 =  31;
const int KEY_COLON = 32;
const int KEY_SEMICOLON = 33;
const int KEY_LESS = 34;
const int KEY_EQUALS = 35;
const int KEY_GREATER = 36;
const int KEY_QUESTION = 37;
const int KEY_AT = 38;
const int KEY_LEFTBRACKET = 39;
const int KEY_BACKSLASH = 40;
const int KEY_RIGHTBRACKET = 41;
const int KEY_CARET = 42;
const int KEY_UNDERSCORE = 43;
const int KEY_BACKQUOTE = 44;
const int KEY_a = 45;
const int KEY_b = 46;
const int KEY_c = 47;
const int KEY_d = 48;
const int KEY_e = 49;
const int KEY_f = 50;
const int KEY_g = 51;
const int KEY_h = 52;
const int KEY_i = 53;
const int KEY_j = 54;
const int KEY_k = 55;
const int KEY_l = 56;
const int KEY_m = 57;
const int KEY_n = 58;
const int KEY_o = 59;
const int KEY_p = 60;
const int KEY_q = 61;
const int KEY_r = 62;
const int KEY_s = 63;
const int KEY_t = 64;
const int KEY_u = 65;
const int KEY_v = 66;
const int KEY_w = 67;
const int KEY_x = 68;
const int KEY_y = 69;
const int KEY_z = 70;
const int KEY_DELETE = 71;
const int KEY_KP0 = 72;
const int KEY_KP1 = 73;
const int KEY_KP2 = 74;
const int KEY_KP3 = 75;
const int KEY_KP4 = 76;
const int KEY_KP5 = 77;
const int KEY_KP6 = 78;
const int KEY_KP7 = 79;
const int KEY_KP8 = 80;
const int KEY_KP9 = 81;
const int KEY_KP_PERIOD = 82;
const int KEY_KP_DIVIDE = 83;
const int KEY_KP_MULTIPLY = 84;
const int KEY_KP_MINUS = 85;
const int KEY_KP_PLUS = 86;
const int KEY_KP_ENTER = 87;
const int KEY_KP_EQUALS = 88;
const int KEY_UP = 89;
const int KEY_DOWN = 90;
const int KEY_RIGHT = 91;
const int KEY_LEFT = 92;
const int KEY_INSERT = 93;
const int KEY_HOME = 94;
const int KEY_END = 95;
const int KEY_PAGEUP = 96;
const int KEY_PAGEDOWN = 97;
const int KEY_F1 = 98;
const int KEY_F2 = 99;
const int KEY_F3 = 100;
const int KEY_F4 = 101;
const int KEY_F5 = 102;
const int KEY_F6 = 103;
const int KEY_F7 = 104;
const int KEY_F8 = 105;
const int KEY_F9 = 106;
const int KEY_F10 = 107;
const int KEY_F11 = 108;
const int KEY_F12 = 109;
const int KEY_F13 = 110;
const int KEY_F14 = 111;
const int KEY_F15 = 112;
const int KEY_NUMLOCK = 113;
const int KEY_CAPSLOCK = 114;
const int KEY_SCROLLOCK = 115;
const int KEY_RSHIFT = 116;
const int KEY_LSHIFT = 117;
const int KEY_RCTRL = 118;
const int KEY_LCTRL = 119;
const int KEY_RALT = 120;
const int KEY_LALT = 121;
const int KEY_RMETA = 122;
const int KEY_LMETA = 123;
const int KEY_LSUPER = 124;
const int KEY_RSUPER = 125;
const int KEY_MODE = 126;
const int KEY_COMPOSE = 127;
const int KEY_HELP = 128;
const int KEY_PRINT = 129;
const int KEY_SYSREQ = 130;
const int KEY_BREAK = 131;
const int KEY_MENU = 132;
const int KEY_POWER = 133;
const int KEY_EURO = 134;
const int KEY_UNDO = 135;

/**
Class that contians a single key.

@author Tommy Carlsson
*/
class Key{
public:

	Key();
	virtual ~Key();

  /**
   * Returns true if k has same key and mods as the Ui::Key object.
   * @param k the key to compare with.
   * @return true if k has same key and mods as the Ui::Key object.
   */
	virtual bool operator== ( const Key& k ) const;

  /**
   * Returns the keysym associated with the key.
   * @note do not hardcode any keysyms since these can vary from one caracterset to another. If you have to hardcode some, only use the once available on all keyboards.
   * @note If unset the function returns Ui::Keysym::KEY_NONE
   * @see Ui::Key::setKeysym() Ui::Key::unicode()
   * @return the keysym associated with the key.
   */
  virtual Keysym keysym() {  return pKeysym; };

  /**
   * Returns unicode value of the key.
   * @note will return 0 if key does not have an associated unicode value.
   * @see Ui::Key::setUnicode() Ui::Key::keysym()
   * @return Unicode value of the key.
   */
  virtual wchar_t unicode() {  return pUnicode; };


  /**
   * Sets the keysym for the Ui::Key Object.
   * @note If not set the Ui::Key::keysym() will return Ui::Keysym::KEY_NONE
   * @see Ui::Key::keysym() Ui::Key::setUnicode()
   * @param ks the new keysym
   */
  virtual void setKeysym( Keysym ks ) {  pKeysym = ks; };

  /**
   * Assigns a unicode value to the key.
   * @note If no unicode value is assigned Ui::Key::unicode() will return 0
   * @see Ui::Key::unicode() Ui::Key::setKeysym()
   * @param uc the unicode value to assign.
   */
  virtual void setUnicode( wchar_t uc ) { pUnicode = uc; };

  virtual bool isLShiftPressed() {  return pLShift; }
  virtual bool isRShiftPressed() {  return pRShift; }
  virtual bool isLCtrlPressed() {  return pLCtrl; }
  virtual bool isRCtrlPressed() {  return pRCtrl; }
  virtual bool isLAltPressed() {  return pLAlt; }
  virtual bool isRAltPressed() {  return pRAlt; }
  virtual bool isLMetaPressed() {  return pLMeta; }
  virtual bool isRMetaPressed() {  return pRMeta; }
  virtual bool isNumlockPressed() {  return pNumlock; }
  virtual bool isCapslockPressed() {  return pCapslock; }
  virtual bool isModePressed() {  return pMode; }

  virtual void setLShiftPressed( bool p ) { pLShift = p; }
  virtual void setRShiftPressed( bool p ) { pRShift = p; }
  virtual void setLCtrlPressed( bool p ) { pLCtrl = p; }
  virtual void setRCtrlPressed( bool p ) { pRCtrl = p; }
  virtual void setLAltPressed( bool p ) { pLAlt = p; }
  virtual void setRAltPressed( bool p ) { pRAlt = p; }
  virtual void setLMetaPressed( bool p ) { pLMeta = p; }
  virtual void setRMetaPressed( bool p ) { pRMeta = p; }
  virtual void setNumlockPressed( bool p ) { pNumlock = p; }
  virtual void setCapslockPressed( bool p ) { pCapslock = p; }
  virtual void setModePressed( bool p ) { pMode = p; }

  virtual bool isCtrlPressed() {  return ( pLCtrl || pRCtrl ); }
  virtual bool isShiftPressed() {  return ( pLShift || pRShift ); }
  virtual bool isAltPressed() {  return ( pLAlt || pRAlt ); }
  virtual bool isMetaPressed() {  return ( pLMeta || pRMeta ); }
  virtual bool isAnyModsPressed() {  return (pLShift || pRShift || pLCtrl || pRCtrl || pLAlt || pRAlt || pLMeta || pRMeta || pNumlock || pCapslock || pMode); }

	virtual wstring keysymWString( Keysym k );
	virtual string keysymString( const Keysym k );

	virtual void debugString( );

private:

  Keysym pKeysym;
  wchar_t pUnicode;

  bool pLShift;
  bool pRShift;
  bool pLCtrl;
  bool pRCtrl;
  bool pLAlt;
  bool pRAlt;
  bool pLMeta;
  bool pRMeta;
  bool pNumlock;
  bool pCapslock;
  bool pMode;

};

}

#endif
