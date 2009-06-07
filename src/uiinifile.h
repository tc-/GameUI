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


#ifndef INIFILE_H
#define INIFILE_H

#include <string.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include "uilist.h"

using namespace std;

namespace Ui
{

	/**
	 * Class representing an Ini-file key.
	 */
	class InifileKey
	{
		public:

			InifileKey() :pName( "default" ), pValue( "" ) {}
			InifileKey( const InifileKey& ik ) : pName( ik.name() ) {
				const string s = ik.pValue;
				pValue = s;
			}
			const InifileKey& operator= ( const InifileKey& right );
			InifileKey( const string n, const string value ): pName( n ) {
				setValueString( value );
			}
			InifileKey( const string n, const int value ): pName( n ) {
				setValueInt( value );
			}
			InifileKey( const string n, const double value ): pName( n ) {
				setValueFloat( value );
			}

			string name() const {
				return pName;
			}
			void setName( const string newName ) {
				pName = newName;
			}

			string valueString( ) {
				return pValue;
			}
			int valueInt( ) {
				stringstream io;
				io << pValue;
				int i;
				io >> i;
				return i;
			}
			double valueFloat( ) {
				stringstream io;
				io << pValue;
				double d;
				io >> d;
				return d;
			}

			void setValueString( const string value ) {
				pValue = value;
			}
			void setValueInt( const int value ) {
				stringstream io;
				io << value;
				pValue = io.str();
			}
			void setValueFloat( const double value ) {
				stringstream io;
				io << value;
				pValue = io.str();
			}

			string& comment() {
				return pComment;
			}

		private:

			string pName;
			string pValue;
			string pComment;

	};


	/**
	 * Class representing an Ini-file section.
	 */
	class InifileSection
	{
		public:

			InifileSection( ): pName( "default" ) {}
			InifileSection( const InifileSection& is ) : keys( is.keys ), pName( is.name() ) {}
			InifileSection( const string n ): pName( n ) {}
			~InifileSection();

			string name() const {
				return pName;
			}
			void setName( const string newName ) {
				pName = newName;
			}

			string keyComment( const string keyName );

			string keyStringValue( const string keyName, const string def = "" );
			int keyIntValue( const string keyName, const int def = 0 );
			double keyFloatValue( const string keyName, const double def = 0.0 );

			void setKeyStringValue( const string keyName, const string value = "" );
			void setKeyIntValue( const string keyName, const int value = 0 );
			void setKeyFloatValue( const string keyName, const double value = 0.0 );

			int keyIndex( const string keyName );

			string& comment() {
				return pComment;
			}

			List<InifileKey*> keys;

		private:

			string pName;
			string pComment;

	};


	/**
	 * Class used to read and write Ini-files.
	 *
	*/
	class Inifile
	{
		public:
			Inifile( const string fname = "" );
			~Inifile();

			InifileSection* section( const string sectionName, const bool create = true );
			void setSection( const string sectionName );

			string keyComment( const string keyName );
			string& sectionComment( const string sectionName );

			string readString( const string keyName, const string def = "" );
			int readInt( const string keyName, const int def = 0 );
			double readFloat( const string keyName, const double def = 0.0 );

			void writeString( const string keyName, const string data );
			void writeInt( const string keyName, const int data );
			void writeFloat( const string keyName, const double data );

			void deleteKey( const string keyName );
			void deleteSection( const string sectionName );

			bool load( const string fname );
			bool save( const string fname = "" );

			void clear(  );

			List<InifileSection*> sections;

		private:

			string pFName;
			InifileSection* pCurSec;
			bool parseIniFile( const string fname );

	};

}

#endif
