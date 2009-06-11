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
 * @file
 * Header and implementationfile of the Key class.
 */

#ifndef KEYEY_H
#define KEYEY_H

#include <gameui.h>
#include <string>
#include <iostream>

using namespace std;

namespace Ui
{


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
	 * Class that contians a single keystroke.
	 */
	class Key
	{
		public:

			Key():
				pKeysym(KEY_NONE), pUnicode(0), pLShift(false), pRShift(false), pLCtrl(false), pRCtrl(false),
				pLAlt(false), pRAlt(false), pLMeta(false), pRMeta(false), pNumlock(false), pCapslock(false), pMode(false)
			{ }

			/**
			 * Two Key objects are equal if they hold the same Keysym and the same mods.
			 *
			 * @param k the key to compare with.
			 */
			inline bool operator== ( const Key& k ) const {
				return ( (k.pKeysym == pKeysym) && (k.pUnicode == pUnicode) && (k.pLShift == pLShift) && (k.pRShift == pRShift) &&
					(k.pLCtrl == pLCtrl) && (k.pRCtrl == pRCtrl) && (k.pLAlt == pLAlt) && (k.pRAlt == pRAlt) &&
					(k.pLMeta == pLMeta) && (k.pRMeta == pRMeta) && (k.pNumlock == pNumlock) && (k.pCapslock == pCapslock) &&
					(k.pMode == pMode)
				);
			}

			/**
			 * The keysym associated with the key.
			 *
			 * @note do not hardcode any keysyms since these can vary from one caracterset to another. If you have to hardcode some, only use the once available on all keyboards.
			 * @note If unset the function returns Ui::Keysym::KEY_NONE
			 * @see setKeysym() unicode().
			 */
			inline Keysym keysym() {
				return pKeysym;
			};

			/**
			 * Returns unicode value of the key.
			 *
			 * @note will return 0 if key does not have an associated unicode value.
			 * @return Unicode value of the key.
			 * @see setUnicode() keysym().
			 */
			inline wchar_t unicode() {
				return pUnicode;
			};


			/**
			 * Sets the keysym for the Key Object.
			 *
			 * @note If not set the keysym() will return Keysym::KEY_NONE.
			 * @param ks the new keysym.
			 * @see keysym() setUnicode().
			 */
			inline void setKeysym( const Keysym& ks ) {
				pKeysym = ks;
			};

			/**
			 * Assigns a unicode value to the key.
			 *
			 * @note If no unicode value is assigned unicode() will return 0.
			 * @param uc the unicode value to assign.
			 * @see unicode() setKeysym().
			 */
			inline void setUnicode( wchar_t uc ) {
				pUnicode = uc;
			};

			inline bool isLShiftPressed() {
				return pLShift;
			}
			inline bool isRShiftPressed() {
				return pRShift;
			}
			inline bool isLCtrlPressed() {
				return pLCtrl;
			}
			inline bool isRCtrlPressed() {
				return pRCtrl;
			}
			inline bool isLAltPressed() {
				return pLAlt;
			}
			inline bool isRAltPressed() {
				return pRAlt;
			}
			inline bool isLMetaPressed() {
				return pLMeta;
			}
			inline bool isRMetaPressed() {
				return pRMeta;
			}
			inline bool isNumlockPressed() {
				return pNumlock;
			}
			inline bool isCapslockPressed() {
				return pCapslock;
			}
			inline bool isModePressed() {
				return pMode;
			}

			inline void setLShiftPressed( bool p ) {
				pLShift = p;
			}
			inline void setRShiftPressed( bool p ) {
				pRShift = p;
			}
			inline void setLCtrlPressed( bool p ) {
				pLCtrl = p;
			}
			inline void setRCtrlPressed( bool p ) {
				pRCtrl = p;
			}
			inline void setLAltPressed( bool p ) {
				pLAlt = p;
			}
			inline void setRAltPressed( bool p ) {
				pRAlt = p;
			}
			inline void setLMetaPressed( bool p ) {
				pLMeta = p;
			}
			inline void setRMetaPressed( bool p ) {
				pRMeta = p;
			}
			inline void setNumlockPressed( bool p ) {
				pNumlock = p;
			}
			inline void setCapslockPressed( bool p ) {
				pCapslock = p;
			}
			inline void setModePressed( bool p ) {
				pMode = p;
			}

			inline bool isCtrlPressed() {
				return ( pLCtrl || pRCtrl );
			}
			inline bool isShiftPressed() {
				return ( pLShift || pRShift );
			}
			inline bool isAltPressed() {
				return ( pLAlt || pRAlt );
			}
			inline bool isMetaPressed() {
				return ( pLMeta || pRMeta );
			}
			inline bool isAnyModsPressed() {
				return ( pLShift || pRShift || pLCtrl || pRCtrl || pLAlt || pRAlt || pLMeta || pRMeta || pNumlock || pCapslock || pMode );
			}

			/**
			 * Generates a wstring with the name on the Keysym provided as parameter.
			 *
			 * @see keysymString().
			 */
			wstring keysymWString( const Keysym& k );

			/**
			 * Generates a string with the name on the Keysym provided as parameter.
			 *
			 * @see keysymString().
			 */
			string keysymString( const Keysym& k );

			/**
			 * Output debug info about this Key object.
			 */
			void debugString( );

		private:

			Keysym pKeysym;
			wchar_t pUnicode;

			//! @todo Should make a Keymod class to contain the key mods.
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
