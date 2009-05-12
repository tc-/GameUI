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
#include "uiinifile.h"

namespace Ui {

// InifileSection ///////////////////////////////////////////////////////////

InifileSection::~InifileSection()
{
  for( int i = 0; i < keys.count(); i++ ) {
    delete keys.get( i );
  }
  keys.clear();
}

string InifileSection::keyComment( const string keyName )
{
  int key = keyIndex( keyName );
  if ( key != -1 ) {
    return keys.get(key)->comment();
  }
	return "";
}


string InifileSection::keyStringValue( const string keyName, const string def )
{
  int key = keyIndex( keyName );
  if ( key != -1 ) {
    return keys.get(key)->valueString();
  } else {
    return def;
  }
}

int InifileSection::keyIntValue( const string keyName, const int def )
{
  int key = keyIndex( keyName );
  if ( key != -1 ) {
    return keys.get(key)->valueInt();
  } else {
    return def;
  }
}

double InifileSection::keyFloatValue( const string keyName, const double def )
{
  int key = keyIndex( keyName );
  if ( key != -1 ) {
    return keys.get(key)->valueFloat();
  } else {
    return def;
  }
}


void InifileSection::setKeyStringValue( const string keyName, const string value )
{
  int key = keyIndex( keyName );
  if ( key != -1 ) {
     keys.get(key)->setValueString( value );
  } else {
    InifileKey* k = new InifileKey( keyName, value );
    keys.append( k );
  }
}

void InifileSection::setKeyIntValue( const string keyName, const int value )
{
  int key = keyIndex( keyName );
  if ( key != -1 ) {
    keys.get(key)->setValueInt( value );
  } else {
    InifileKey* k = new InifileKey( keyName, value );
    keys.append( k );
  }
}

void InifileSection::setKeyFloatValue( const string keyName, const double value )
{
  int key = keyIndex( keyName );
  if ( key != -1 ) {
    keys.get(key)->setValueFloat( value );
  } else {
    InifileKey* k = new InifileKey( keyName, value );
    keys.append( k );
  }
}


int InifileSection::keyIndex( const string keyName )
{
  for( int i = 0; i < keys.count(); i++ ) {
    InifileKey* k = keys.get( i );
    if ( k->name() == keyName )
      return i;
  }
  return -1;
}



// Inifile  //////////////////////////////////////////////////////////////////////

Inifile::Inifile( const string fname )
{
  pCurSec = NULL;
  if ( fname != "" )
    parseIniFile( fname );
}


Inifile::~Inifile()
{
  clear();
}

bool Inifile::load( const string fname )
{
  return parseIniFile( fname );
}

void Inifile::clear(  )
{
  for( int i = 0; i < sections.count(); i++ ) {
    delete sections.get( i );
  }
  sections.clear();
}

InifileSection* Inifile::section( const string sectionName, const bool create )
{
  for( int i = 0; i < sections.count(); i++ ) {
  InifileSection* s = sections.get( i );
  if ( s->name() == sectionName )
    return s;
  }
  if ( create ) {
    InifileSection* s = new InifileSection( sectionName );
    sections.append( s );
    return s;
  } else {
    return NULL;
  }
}


void Inifile::setSection( const string sectionName )
{
  pCurSec = section( sectionName );
}

string Inifile::keyComment( const string keyName )
{
  if ( pCurSec == NULL ) setSection( "default" );
  return pCurSec->keyComment( keyName );
}

string& Inifile::sectionComment( const string sectionName )
{
  return section( sectionName )->comment();
}


string Inifile::readString( const string keyName, const string def )
{
  if ( pCurSec == NULL ) setSection( "default" );
  return pCurSec->keyStringValue( keyName, def );
}

int Inifile::readInt( const string keyName, const int def )
{
  if ( pCurSec == NULL ) setSection( "default" );
  return pCurSec->keyIntValue( keyName, def );
}

double Inifile::readFloat( const string keyName, const double def )
{
  if ( pCurSec == NULL ) setSection( "default" );
  return pCurSec->keyFloatValue( keyName, def );
}


void Inifile::writeString( const string keyName, const string data )
{
  if ( pCurSec == NULL ) setSection( "default" );
  return pCurSec->setKeyStringValue( keyName, data );
}

void Inifile::writeInt( const string keyName, const int data )
{
  if ( pCurSec == NULL ) setSection( "default" );
  return pCurSec->setKeyIntValue( keyName, data );
}

void Inifile::writeFloat( const string keyName, const double data )
{
  if ( pCurSec == NULL ) setSection( "default" );
  return pCurSec->setKeyFloatValue( keyName, data );
}


void Inifile::deleteKey( const string keyName )
{
  if ( pCurSec == NULL ) setSection( "default" );
  int index = pCurSec->keyIndex( keyName );
  if ( index > -1 ) {
    delete pCurSec->keys.get( index );
    pCurSec->keys.remove( index );
  }
}

void Inifile::deleteSection( const string sectionName )
{
  InifileSection* s = section( sectionName, false );
  if ( s != NULL ) {
    sections.remove( sections.getIndex( s ) );
    delete s;
  }
}


bool Inifile::save( const string fname )
{
  string filename = fname;
  if ( filename == "" )
    filename = pFName;
  if ( filename == "" )
    return false;

  ofstream f;
  f.open( filename.c_str(), fstream::out | fstream::trunc );
  if (!f.is_open ( )) return false;
  for( int is = 0; is < sections.count(); is++ ) {
    InifileSection* sec = sections.get( is );

    f << sec->comment();
    f << "[" << sec->name() << "]" << "\n";

    for( int ik = 0; ik < sec->keys.count(); ik++ ) {
      InifileKey* key = sec->keys.get( ik );

      f << key->comment();
      f << key->name() << " = \"" << key->valueString() << "\"\n";
    }
  }
  f.close();
  return true;
}

void rTrim( string& s )
{
  while( s.length() > 0 ) {
    if ( s[s.length()-1] == ' ' )
      s.erase( s.length()-1, 1 );
    else
      break;
  }
}


void lTrim( string& s )
{
  while( s.length() > 0 ) {
    if ( s[0] == ' ' )
      s.erase( 0, 1 );
    else
      break;
  }
}


void trim( string& s )
{
  rTrim(s);
  lTrim(s);
}

bool Inifile::parseIniFile( const string fname )
{
  const int buffSize = 1024;
  char buff[buffSize];

  string comment = "";
  ifstream f;
  f.open( fname.c_str() );
  if (!f.is_open ( )) return false;

  pFName = fname;

  while( !f.eof() ) {
    f.getline( buff, buffSize );
    string s = buff;
    if ( s.length() > 0 ) {
      if ( s[0] == '[' ) {
        // New Section
        string section = s.substr( 1, s.find( "]" ) - 1 );
        setSection( section );
        pCurSec->comment() += comment;
        comment = "";
      } else if ((s[0] == '#') || (s[0] == ';')) {
        comment += s + "\n";
      } else if ( s.find( "=" ) != string::npos ) {
        int i = s.find( "=" );
        string key = s.substr( 0, i );
        trim(key);
        string value = s.substr( i + 1, s.length() - 1 );
        trim(value);
        if ( value.length() > 0 ) {
          if ( value[0] == '"' ) {
            value.erase( 0, 1 );
            value.erase( value.length() - 1, 1 );
          }
        }
        writeString( key, value );
        i = pCurSec->keyIndex( key );
        pCurSec->keys.get( i )->comment() += comment;
        comment = "";
      }
    } else {
      comment += "\n";
    }
  }
  f.close();
  return true;
}

}
