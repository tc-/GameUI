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
Implementation of the Ui::Key class
 */

#include <uikey.h>

namespace Ui {

Key::Key() {
	pKeysym = KEY_NONE;
	pUnicode = 0;
	pLShift = false;
	pRShift = false;
	pLCtrl = false;
	pRCtrl = false;
	pLAlt = false;
	pRAlt = false;
	pLMeta = false;
	pRMeta = false;
	pNumlock = false;
	pCapslock = false;
	pMode = false;
}

Key::~Key() {
}

bool Key::operator== ( const Key& k ) const {
	return (
		(k.pKeysym == pKeysym) &&
		(k.pUnicode == pUnicode) &&
		(k.pLShift == pLShift) && (k.pRShift == pRShift) &&
		(k.pLCtrl == pLCtrl) && (k.pRCtrl == pRCtrl) &&
		(k.pLAlt == pLAlt) && (k.pRAlt == pRAlt) &&
		(k.pLMeta == pLMeta) && (k.pRMeta == pRMeta) &&
		(k.pNumlock == pNumlock) && (k.pCapslock == pCapslock) &&
		(k.pMode == pMode)
	);
}

wstring Key::keysymWString( Keysym k ) {
	switch ( k ) {
		case KEY_NONE: return L"NONE";
		case KEY_BACKSPACE : return L"BACKSPACE";
		case KEY_TAB : return L"TAB";
		case KEY_CLEAR : return L"CLEAR";
		case KEY_RETURN : return L"RETURN";
		case KEY_PAUSE : return L"PAUSE";
		case KEY_ESCAPE : return L"ESCAPE";
		case KEY_SPACE : return L"SPACE";
		case KEY_EXCLAIM : return L"EXCLAIM";
		case KEY_QUOTEDBL : return L"QUOTEDB";
		case KEY_HASH : return L"HASH";
		case KEY_DOLLAR : return L"DOLLAR";
		case KEY_AMPERSAND : return L"AMPERSAND";
		case KEY_QUOTE : return L"QUOTE";
		case KEY_LEFTPAREN : return L"LEFTPAREN";
		case KEY_RIGHTPAREN : return L"RIGHTPAREN";
		case KEY_ASTERISK : return L"ASTERISK";
		case KEY_PLUS : return L"PLUS";
		case KEY_COMMA : return L"COMMA";
		case KEY_MINUS : return L"MINUS";
		case KEY_PERIOD : return L"PERIOD";
		case KEY_SLASH : return L"SLASH";
		case KEY_0 : return L"0";
		case KEY_1 : return L"1";
		case KEY_2 : return L"2";
		case KEY_3 : return L"3";
		case KEY_4 : return L"4";
		case KEY_5 : return L"5";
		case KEY_6 : return L"6";
		case KEY_7 : return L"7";
		case KEY_8 : return L"8";
		case KEY_9 : return L"9";
		case KEY_COLON : return L"COLON";
		case KEY_SEMICOLON : return L"SEMICOLON";
		case KEY_LESS : return L"LESS";
		case KEY_EQUALS : return L"EQUALS";
		case KEY_GREATER : return L"GREATER";
		case KEY_QUESTION : return L"QUESTION";
		case KEY_AT : return L"AT";
		case KEY_LEFTBRACKET : return L"LEFTBRACKET";
		case KEY_BACKSLASH : return L"BACKSLASH";
		case KEY_RIGHTBRACKET : return L"RIGHTBRACKET";
		case KEY_CARET : return L"CARET";
		case KEY_UNDERSCORE : return L"UNDERSCORE";
		case KEY_BACKQUOTE : return L"BACKQUOTE";
		case KEY_a : return L"a";
		case KEY_b : return L"b";
		case KEY_c : return L"c";
		case KEY_d : return L"d";
		case KEY_e : return L"e";
		case KEY_f : return L"f";
		case KEY_g : return L"g";
		case KEY_h : return L"h";
		case KEY_i : return L"i";
		case KEY_j : return L"j";
		case KEY_k : return L"k";
		case KEY_l : return L"l";
		case KEY_m : return L"m";
		case KEY_n : return L"n";
		case KEY_o : return L"o";
		case KEY_p : return L"p";
		case KEY_q : return L"q";
		case KEY_r : return L"r";
		case KEY_s : return L"s";
		case KEY_t : return L"t";
		case KEY_u : return L"u";
		case KEY_v : return L"v";
		case KEY_w : return L"w";
		case KEY_x : return L"x";
		case KEY_y : return L"y";
		case KEY_z : return L"z";
		case KEY_DELETE : return L"DELETE";
		case KEY_KP0 : return L"KP0";
		case KEY_KP1 : return L"KP1";
		case KEY_KP2 : return L"KP2";
		case KEY_KP3 : return L"KP3";
		case KEY_KP4 : return L"KP4";
		case KEY_KP5 : return L"KP5";
		case KEY_KP6 : return L"KP6";
		case KEY_KP7 : return L"KP7";
		case KEY_KP8 : return L"KP8";
		case KEY_KP9 : return L"KP9";
		case KEY_KP_PERIOD : return L"KP_PERIOD";
		case KEY_KP_DIVIDE : return L"KP_DIVIDE";
		case KEY_KP_MULTIPLY : return L"KP_MULTIPLY";
		case KEY_KP_MINUS : return L"KP_MINUS";
		case KEY_KP_PLUS : return L"KP_PLUS";
		case KEY_KP_ENTER : return L"KP_ENTER";
		case KEY_KP_EQUALS : return L"KP_EQUALS";
		case KEY_UP : return L"UP";
		case KEY_DOWN : return L"DOWN";
		case KEY_RIGHT : return L"RIGHT";
		case KEY_LEFT : return L"LEFT";
		case KEY_INSERT : return L"INSERT";
		case KEY_HOME : return L"HOME";
		case KEY_END : return L"END";
		case KEY_PAGEUP : return L"PAGEUP";
		case KEY_PAGEDOWN : return L"PAGEDOWN";
		case KEY_F1 : return L"F1";
		case KEY_F2 : return L"F2";
		case KEY_F3 : return L"F3";
		case KEY_F4 : return L"F4";
		case KEY_F5 : return L"F5";
		case KEY_F6 : return L"F6";
		case KEY_F7 : return L"F7";
		case KEY_F8 : return L"F8";
		case KEY_F9 : return L"F9";
		case KEY_F10 : return L"F10";
		case KEY_F11 : return L"F11";
		case KEY_F12 : return L"F12";
		case KEY_F13 : return L"F13";
		case KEY_F14 : return L"F14";
		case KEY_F15 : return L"F15";
		case KEY_NUMLOCK : return L"NUMLOCK";
		case KEY_CAPSLOCK : return L"CAPSLOCK";
		case KEY_SCROLLOCK : return L"SCROLLOCK";
		case KEY_RSHIFT : return L"RSHIFT";
		case KEY_LSHIFT : return L"LSHIFT";
		case KEY_RCTRL : return L"RCTR";
		case KEY_LCTRL : return L"LCTR";
		case KEY_RALT : return L"RALT";
		case KEY_LALT : return L"LALT";
		case KEY_RMETA : return L"RMETA";
		case KEY_LMETA : return L"LMETA";
		case KEY_LSUPER : return L"LSUPER";
		case KEY_RSUPER : return L"RSUPER";
		case KEY_MODE : return L"MODE";
		case KEY_COMPOSE : return L"COMPOSE";
		case KEY_HELP : return L"HELP";
		case KEY_PRINT : return L"PRINT";
		case KEY_SYSREQ : return L"SYSREQ";
		case KEY_BREAK : return L"BREAK";
		case KEY_MENU : return L"MENU";
		case KEY_POWER : return L"POWER";
		case KEY_EURO : return L"EURO";
		case KEY_UNDO : return L"UNDO";
		default: return L"KEY_UNKNOWN";
	}
}


string Key::keysymString( const Keysym k ) {
	switch ( k ) {
		case KEY_NONE: return "NONE";
		case KEY_BACKSPACE : return "BACKSPACE";
		case KEY_TAB : return "TAB";
		case KEY_CLEAR : return "CLEAR";
		case KEY_RETURN : return "RETURN";
		case KEY_PAUSE : return "PAUSE";
		case KEY_ESCAPE : return "ESCAPE";
		case KEY_SPACE : return "SPACE";
		case KEY_EXCLAIM : return "EXCLAIM";
		case KEY_QUOTEDBL : return "QUOTEDB";
		case KEY_HASH : return "HASH";
		case KEY_DOLLAR : return "DOLLAR";
		case KEY_AMPERSAND : return "AMPERSAND";
		case KEY_QUOTE : return "QUOTE";
		case KEY_LEFTPAREN : return "LEFTPAREN";
		case KEY_RIGHTPAREN : return "RIGHTPAREN";
		case KEY_ASTERISK : return "ASTERISK";
		case KEY_PLUS : return "PLUS";
		case KEY_COMMA : return "COMMA";
		case KEY_MINUS : return "MINUS";
		case KEY_PERIOD : return "PERIOD";
		case KEY_SLASH : return "SLASH";
		case KEY_0 : return "0";
		case KEY_1 : return "1";
		case KEY_2 : return "2";
		case KEY_3 : return "3";
		case KEY_4 : return "4";
		case KEY_5 : return "5";
		case KEY_6 : return "6";
		case KEY_7 : return "7";
		case KEY_8 : return "8";
		case KEY_9 : return "9";
		case KEY_COLON : return "COLON";
		case KEY_SEMICOLON : return "SEMICOLON";
		case KEY_LESS : return "LESS";
		case KEY_EQUALS : return "EQUALS";
		case KEY_GREATER : return "GREATER";
		case KEY_QUESTION : return "QUESTION";
		case KEY_AT : return "AT";
		case KEY_LEFTBRACKET : return "LEFTBRACKET";
		case KEY_BACKSLASH : return "BACKSLASH";
		case KEY_RIGHTBRACKET : return "RIGHTBRACKET";
		case KEY_CARET : return "CARET";
		case KEY_UNDERSCORE : return "UNDERSCORE";
		case KEY_BACKQUOTE : return "BACKQUOTE";
		case KEY_a : return "a";
		case KEY_b : return "b";
		case KEY_c : return "c";
		case KEY_d : return "d";
		case KEY_e : return "e";
		case KEY_f : return "f";
		case KEY_g : return "g";
		case KEY_h : return "h";
		case KEY_i : return "i";
		case KEY_j : return "j";
		case KEY_k : return "k";
		case KEY_l : return "l";
		case KEY_m : return "m";
		case KEY_n : return "n";
		case KEY_o : return "o";
		case KEY_p : return "p";
		case KEY_q : return "q";
		case KEY_r : return "r";
		case KEY_s : return "s";
		case KEY_t : return "t";
		case KEY_u : return "u";
		case KEY_v : return "v";
		case KEY_w : return "w";
		case KEY_x : return "x";
		case KEY_y : return "y";
		case KEY_z : return "z";
		case KEY_DELETE : return "DELETE";
		case KEY_KP0 : return "KP0";
		case KEY_KP1 : return "KP1";
		case KEY_KP2 : return "KP2";
		case KEY_KP3 : return "KP3";
		case KEY_KP4 : return "KP4";
		case KEY_KP5 : return "KP5";
		case KEY_KP6 : return "KP6";
		case KEY_KP7 : return "KP7";
		case KEY_KP8 : return "KP8";
		case KEY_KP9 : return "KP9";
		case KEY_KP_PERIOD : return "KP_PERIOD";
		case KEY_KP_DIVIDE : return "KP_DIVIDE";
		case KEY_KP_MULTIPLY : return "KP_MULTIPLY";
		case KEY_KP_MINUS : return "KP_MINUS";
		case KEY_KP_PLUS : return "KP_PLUS";
		case KEY_KP_ENTER : return "KP_ENTER";
		case KEY_KP_EQUALS : return "KP_EQUALS";
		case KEY_UP : return "UP";
		case KEY_DOWN : return "DOWN";
		case KEY_RIGHT : return "RIGHT";
		case KEY_LEFT : return "LEFT";
		case KEY_INSERT : return "INSERT";
		case KEY_HOME : return "HOME";
		case KEY_END : return "END";
		case KEY_PAGEUP : return "PAGEUP";
		case KEY_PAGEDOWN : return "PAGEDOWN";
		case KEY_F1 : return "F1";
		case KEY_F2 : return "F2";
		case KEY_F3 : return "F3";
		case KEY_F4 : return "F4";
		case KEY_F5 : return "F5";
		case KEY_F6 : return "F6";
		case KEY_F7 : return "F7";
		case KEY_F8 : return "F8";
		case KEY_F9 : return "F9";
		case KEY_F10 : return "F10";
		case KEY_F11 : return "F11";
		case KEY_F12 : return "F12";
		case KEY_F13 : return "F13";
		case KEY_F14 : return "F14";
		case KEY_F15 : return "F15";
		case KEY_NUMLOCK : return "NUMLOCK";
		case KEY_CAPSLOCK : return "CAPSLOCK";
		case KEY_SCROLLOCK : return "SCROLLOCK";
		case KEY_RSHIFT : return "RSHIFT";
		case KEY_LSHIFT : return "LSHIFT";
		case KEY_RCTRL : return "RCTR";
		case KEY_LCTRL : return "LCTR";
		case KEY_RALT : return "RALT";
		case KEY_LALT : return "LALT";
		case KEY_RMETA : return "RMETA";
		case KEY_LMETA : return "LMETA";
		case KEY_LSUPER : return "LSUPER";
		case KEY_RSUPER : return "RSUPER";
		case KEY_MODE : return "MODE";
		case KEY_COMPOSE : return "COMPOSE";
		case KEY_HELP : return "HELP";
		case KEY_PRINT : return "PRINT";
		case KEY_SYSREQ : return "SYSREQ";
		case KEY_BREAK : return "BREAK";
		case KEY_MENU : return "MENU";
		case KEY_POWER : return "POWER";
		case KEY_EURO : return "EURO";
		case KEY_UNDO : return "UNDO";
		default: return "KEY_UNKNOWN";
	}
}

void Key::debugString( ) {
	cout << "*** KeyInfo ***" << endl <<
			"Keysym: KEY_" << keysymString( keysym() ) << endl <<
			"Unicode: " << unicode() << endl <<
			"Mods: ";
}


}
