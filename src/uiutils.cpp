/***************************************************************************
 *   Copyright (C) 2005 by Tommy Carlsson   *
 *   tc@coderworld.net   *
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
#include "uiutils.h"

#include <stdio.h>
#include <string.h>

namespace Ui {

string Utils::pErrMsg = "";
bool Utils::pHasTask = false;
bool Utils::pTaskInt = false;
string Utils::pTaksMsg = "";

Utils::Utils()
{
}


Utils::~Utils()
{
}

void Utils::fromString( string cs, Color& out )
{
  int r=0, g=0, b=0, a=255;
  if ( cs.length() <= 0 ) { out = Color( r, g, b ); return; }
  if ( cs.find( "," ) != string::npos ) {
    std::stringstream s(cs);
      //s << cs;
    char colData[4];
    if ( s.getline( colData, 4, ',' ) ) {
      r = stringToInt( colData );
      if ( s.getline( colData, 4, ',' ) ) {
        g = stringToInt( colData );
        if ( s.getline( colData, 4, ',' ) ) {
          b = stringToInt( colData );
          if ( s.getline( colData, 4, ',' ) ) {
            a = stringToInt( colData );
          }
        }
      }
    }
    out = Color( r, g, b, a );
    return;
  }

  if ( cs == "aqua" ) { out = Color(0,255,255); return; }
  if ( cs == "black" ) { out = Color(0,0,0); return; }
  if ( cs == "blue" ) { out = Color(0,0,255); return; }
  if ( cs == "fuchsia" ) { out = Color(255,0,255); return; }
  if ( cs == "gray" ) { out = Color(128,128,128); return; }
  if ( cs == "green" ) { out = Color(0,128,0); return; }
  if ( cs == "lime" ) { out = Color(0,255,0); return; }
  if ( cs == "maroon" ) { out = Color(128,0,0); return; }
  if ( cs == "navy" ) { out = Color(0,0,128); return; }
  if ( cs == "olive" ) { out = Color(128,128,0); return; }
  if ( cs == "purple" ) { out = Color(128,0,128); return; }
  if ( cs == "red" ) { out = Color(255,0,0); return; }
  if ( cs == "silver" ) { out = Color(192,192,192); return; }
  if ( cs == "teal" ) { out = Color(0,128,128); return; }
  if ( cs == "white" ) { out = Color(255,255,255); return; }
  if ( cs == "yellow" ) { out = Color(255,255,0); return; }
  out = Color( r, g, b );
}

string Utils::toString( const Color& in )
{
  return toString( in.getR() ) + "," + toString( in.getG() ) + "," + toString( in.getB() ) + "," + toString( in.getA() );
}

wstring Utils::toWString( string in )
{
	//return toWString( in.c_str() );
	iconv_t cd = iconv_open ( "WCHAR_T//TRANSLIT", "" );
	if ( cd == (iconv_t) -1 ) {
		if ( errno == EINVAL )
			setError( "iconv_open(): This iconv implementation does not support convertion fron char to wchar_t.", false );
		else
			setError( "iconv_open(): Failed for unknown reason with errno: " + toString( errno ) + ".", false );
		iconv_close( cd );
		return L"!E!";
	}

	size_t inputBytes = in.length();
	char* input = new char[ inputBytes + 1 ];
	input = (char*) memcpy( input, in.c_str(), inputBytes + 1 );
	ICONV_CONST char* inptr = input;
	wstring output;

	wchar_t outbuf[ inputBytes + 1 ];
	wchar_t* outptr = outbuf;

	size_t outsize = (inputBytes + 1) * sizeof( wchar_t );

	size_t res = iconv( cd, &inptr, &inputBytes, (char**)&outptr, &outsize );
	outptr[0] = L'\0';

	if ( res == (size_t) -1 ) {
		setError( "iconv(): Convertion from char to wchar_t failed with errno: " + toString( errno ) + ".", false );
		output += outbuf;
	} else {
		output += outbuf;
	}

	delete input;
	iconv_close( cd );
	return output;
}


void Utils::fromWString( wstring in, string& out )
{
	iconv_t cd = iconv_open ( "//TRANSLIT", "WCHAR_T" );
	if ( cd == (iconv_t) -1 ) {
		if ( errno == EINVAL )
			setError( "iconv_open(): This iconv implementation does not support convertion fron char to wchar_t.", false );
		else
			setError( "iconv_open(): Failed for unknown reason with errno: " + toString( errno ) + ".", false );
		iconv_close( cd );
		return;
	}

	size_t inputBytes = in.length() * sizeof( wchar_t );
	wchar_t* input = new wchar_t[ inputBytes + 1 ];
	input = (wchar_t*) memcpy( input, in.c_str(), (inputBytes + 1) * sizeof( wchar_t ) );
	ICONV_CONST char* inptr = (char*)input;

	char outbuf[ inputBytes + 1 ];
	size_t outsize = (inputBytes + 1);
	char* outptr = outbuf;

	size_t res = iconv( cd, &inptr, &inputBytes, &outptr, &outsize );
	outptr[0] = '\0';

	if ( res == (size_t) -1 ) {
		setError( "iconv(): Convertion from char to wchar_t failed with errno: " + toString( errno ) + ".", false );
		out += outbuf;
	} else {
		out += outbuf;
	}

	delete input;
	iconv_close( cd );
}


void Utils::fromWStringToString( wstring in, string& out )
{
	iconv_t cd = iconv_open ( "//TRANSLIT", "WCHAR_T" );
	if ( cd == (iconv_t) -1 ) {
		if ( errno == EINVAL )
			setError( "iconv_open(): This iconv implementation does not support convertion fron char to wchar_t.", false );
		else
			setError( "iconv_open(): Failed for unknown reason with errno: " + toString( errno ) + ".", false );
		iconv_close( cd );
		return;
	}

	size_t inputBytes = in.length() * sizeof( wchar_t );
	wchar_t* input = new wchar_t[ inputBytes + 1 ];
	input = (wchar_t*) memcpy( input, in.c_str(), (inputBytes + 1) * sizeof( wchar_t ) );
	ICONV_CONST char* inptr = (char*)input;

	char outbuf[ inputBytes + 1 ];
	size_t outsize = (inputBytes + 1);
	char* outptr = outbuf;

	size_t res = iconv( cd, &inptr, &inputBytes, &outptr, &outsize );
	outptr[0] = '\0';

	if ( res == (size_t) -1 ) {
		setError( "iconv(): Convertion from char to wchar_t failed with errno: " + toString( errno ) + ".", false );
		out += outbuf;
	} else {
		out += outbuf;
	}

	delete input;
	iconv_close( cd );
}

int Utils::inMiddle( const int containerSize, const int insideSize )
{
	return (int)ceil( ((double)containerSize / 2.0) - ( (double)insideSize / 2.0 ) );
}

int Utils::align( const int containerSize, const int objectSize, HAlignType a )
{
	AlignType aa = alignCenter;
	if      ( a == halignLeft ) { aa = alignLeft; }
	else if ( a == halignCenter ) { aa = alignCenter; }
	else if ( a == halignRight ) { aa = alignRight; }
	return align( containerSize, objectSize, aa );
}

int Utils::align( const int containerSize, const int objectSize, VAlignType a )
{
	AlignType aa = alignCenter;
	if      ( a == valignTop ) { aa = alignTop; }
	else if ( a == valignCenter ) { aa = alignCenter; }
	else if ( a == valignBottom ) { aa = alignBottom; }
	return align( containerSize, objectSize, aa );
}

int Utils::align( const int containerSize, const int objectSize, AlignType a )
{
	if ( ( a == alignTop ) || ( a == alignLeft ) ) {
		return 0;
	} else if ( ( a == alignBottom ) || ( a == alignRight ) ) {
		return containerSize - objectSize;
	} else { // alignCenter
		return Utils::inMiddle( containerSize, objectSize );
	}
}


int Utils::stringToInt( const string& in )
{
  int b;
  std::stringstream ss(in);
  ss >> b;
  return b;
}

bool Utils::onLine( int x1, int y1, int x2, int y2, int px, int py )
{
	if ( !(( px >= Utils::min( x1, x2 ) - 1 ) && ( px <= Utils::max( x1, x2 ) + 1 )) ) return false;
	if ( !(( py >= Utils::min( y1, y2 ) - 1 ) && ( py <= Utils::max( y1, y2 ) + 1 )) ) return false;

	int dx = (x1 - x2);
	if ( dx == 0 ) return ( ( px >= x1 - 1 ) && ( px <= x1 + 1 ) );
	double k = ((double)y1 - (double)y2) / (double)dx;
	if ( k == 0.0 ) return ( ( py >= y1 - 1 ) && ( py <= y1 + 1 ) );
	double m = (double)y1 - k * (double)x1;
	double yt = k * (double)px + m;
	double xt = ((double)py - m) / k;

	bool yret = ( ( yt >= (double)py - 1.5 ) && ( yt <= (double)py + 1.5 ) );
	bool xret = ( ( xt >= (double)px - 1.5 ) && ( xt <= (double)px + 1.5 ) );
	return ( yret || xret );
}

int Utils::max( const int& i1, const int& i2 )
{
  if ( i1 > i2 )
    return i1;
  else
    return i2;
}

int Utils::min( const int& i1, const int& i2 )
{
  if ( i1 < i2 )
    return i1;
  else
    return i2;
}


Rect Utils::getRect( int x1, int y1, int x2, int y2 )
{
	//cout << "getRect x1:" << x1 << " x2:" << x2 << " y1:" << y1 << " y2:" << y2 << endl;
	Rect res;
	res.left = min( x1, x2 );
	res.top = min( y1, y2 );
	res.width = max( x1, x2 ) - res.left + 1;
	res.height = max( y1, y2 ) - res.top + 1;
	return res;
}


void Utils::setError( const string& msg, const bool& stopTask )
{
  if ( (pHasTask) && (stopTask) ) {
    endTask( false );
  } else if ( (pHasTask) && (!stopTask) ) {
    if ( !pTaskInt ) cout << endl;
    pTaskInt = true;
  }
  pErrMsg = msg;
  cerr << " EE " << msg << endl;
	cerr.flush();
}

void Utils::setWarning( const string& msg )
{
  if ( (pHasTask) && (!pTaskInt) ) cout << endl;
  cout << " !! " << msg << endl;
	cout.flush();
	pTaskInt = true;
}

void Utils::setNotice( const string& msg )
{
  if ( (pHasTask) && (!pTaskInt) ) cout << endl;
  cout << " -- " << msg << endl;
	cout.flush();
	pTaskInt = true;
}

string Utils::getError( )
{
  return pErrMsg;
}

void Utils::startTask( const string& msg )
{
  if ( pHasTask ) endTask( true );
  cout << " ** " << msg << "... ";
	cout.flush();
	pHasTask = true;
  pTaskInt = false;
}

void Utils::endTask( const bool& result )
{
  if ( !pHasTask ) return;

  if ( pTaskInt )
    cout << " ** " << pTaksMsg << "... ";
  if ( result ) {
    cout << "Ok" << endl;
  } else {
    cout << "Error!" << endl;
  }
	cout.flush();
  pHasTask = false;
}

void Utils::startSection( const string& name )
{
  if ( pHasTask ) {
    endTask( true );
  }
  cout << endl;
  cout << "  //////////////////////////////////////////////////////////////////" << endl;
  cout << " //  " << name << endl;
  cout << "//////////////////////////////////////////////////////////////////" << endl;
  cout << endl;
	cout.flush();
}


}
