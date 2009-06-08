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
Implementation of the Ui::SDLImageObject class
*/

#include <uisdlimageobject.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace Ui;

SDLImageObject::SDLImageObject( const int& width, const int& height )
 : ImageObject()
{
	s = NULL;
	if ( ( width != 0 ) && ( height != 0 ) ) {
		SDL_Surface* ts;
		if ( SDL_BYTEORDER == SDL_BIG_ENDIAN ) {
			ts = SDL_CreateRGBSurface( SDL_SWSURFACE, width, height, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff );
		} else {
			ts = SDL_CreateRGBSurface( SDL_SWSURFACE, width, height, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000 );
		}
		if ( ts ) {
			SDL_Surface* ts2 = SDL_DisplayFormatAlpha( ts );
			if ( ts2 ) {
				assignSurface( ts2 );
				SDL_FreeSurface( ts );
			} else {
				assignSurface( ts );
			}
		}
	}
  updated = true;
  pRelX = 0;
  pRelY = 0;
}


SDLImageObject::~SDLImageObject()
{
  if ( isLoaded() ) {
    freeImage();
  }
}

ImageObject* SDLImageObject::themeSDLImageObjectLoader( const string fname, InifileSection* iniSec, const ThemeLoadOptions& op )
{
  SDLImageObject* im = new SDLImageObject;
  im->loadImage( fname );
  if ( im->isLoaded() ) {
    int sw = iniSec->keyIntValue( "sectionwidth", 0 );
    int sh = iniSec->keyIntValue( "sectionheight", 0 );
		int a = iniSec->keyIntValue( "alpha", 255 );
    if ( (sw != 0) && (sh != 0) ) {
      im->setSectionWidht( sw );
      im->setSectionHeight( sh );
    }
		if ( iniSec->keyIndex( "colorkey" ) >= 0 ) {
			Color c;
			Utils::fromString( iniSec->keyStringValue( "colorkey", "" ), c );
			SDL_SetColorKey( im->getSurface(), SDL_SRCCOLORKEY, SDL_MapRGB( im->getSurface()->format, c.getR(), c.getG(), c.getB() ) );
			if ( (c.getA() != 255) && ( a == 255 ) )
				a = c.getA();
			else
				im->setAlpha( 255 );
		}
		if ( a != 255 )
			im->setAlpha( a );

    return (ImageObject*)im;
  } else {
    delete im;
    return NULL;
  }
}

ImageObject* SDLImageObject::sdlImageObjectFactory( const int& width, const int& height )
{
	return new SDLImageObject( width, height );
}


int SDLImageObject::height()
{
  if ( isLoaded() ) {
    return s->h;
  } else {
    return -1;
  }
}

int SDLImageObject::width()
{
  if ( isLoaded() ) {
    return s->w;
  } else {
    return -1;
  }
}

bool SDLImageObject::loadImage( string fname )
{
  if (isLoaded()) {
    freeImage();
  }
  s = IMG_Load( fname.c_str() );
  if ( s ) {
    SDL_Surface* s2 = SDL_DisplayFormatAlpha( s );
    if ( s2 != NULL) {
      SDL_FreeSurface( s );
      s = s2;
    }
  } else {
    Utils::setError( "Failed loading Image from file: " + fname, false );
    Utils::setError( " - Error message: " + string(IMG_GetError()), false );
    s = NULL;
  }
	if ( isLoaded() ) {
		unsetClipRect();
		return true;
	} else {
		return false;
	}
}

SDL_Surface* SDLImageObject::getSurface()
{
  return s;
}

void SDLImageObject::freeImage()
{
  if ( s != NULL )
    SDL_FreeSurface( s );
  s = NULL;
}

bool SDLImageObject::isLoaded()
{
  return (s != NULL);
}


void SDLImageObject::drawImage( ImageObject &image, const Rect& dr, const Rect &sr )
{
  Rect dr2 = dr;
  dr2.left += pRelX;
  dr2.top += pRelY;
  visDebug( dr2 );
  updated = true;
  SDLImageObject *i = (SDLImageObject*)&image;

//  cout << "* Ui::SDLDrawInterface::drawImage(  )" << endl;
  pushClipRect( dr2 );
  if ( clipRect().area() <= 0 ) {
    popClipRect();
    return;
  }

  SDL_Rect *sdldr = new SDL_Rect;

  sdldr->x = dr2.left;
  sdldr->y = dr2.top;
  if ( dr2.width == 0 ) {
    sdldr->w = image.width();
  } else {
    sdldr->w = dr2.width;
  }
  if ( dr2.height == 0 ) {
    sdldr->h = image.height();
  } else {
    sdldr->h = dr2.height;
  }

  SDL_Rect *sdlsr = NULL;
  if ( sr != NULL_RECT ) {
    sdlsr = new SDL_Rect;
    sdlsr->x = sr.left;
    sdlsr->y = sr.top;
    sdlsr->w = sr.width;
    sdlsr->h = sr.height;
  }

  SDL_BlitSurface( i->getSurface(), sdlsr, s, sdldr );

  popClipRect();
  delete sdldr;

}


void SDLImageObject::drawImageTiled( ImageObject &image, const Rect& dr, const Rect &sr )
{
  Rect dr2 = dr;
  dr2.left += pRelX;
  dr2.top += pRelY;
  visDebug( dr2 );
  updated = true;
  SDLImageObject *i = (SDLImageObject*)&image;

//  cout << "* Ui::SDLDrawInterface::drawImageTiled(  )" << endl;
  pushClipRect( dr2 );
  if ( clipRect().area() <= 0 ) {
    popClipRect();
    return;
  }

  SDL_Rect *sdldr = new SDL_Rect;

  //clipRect().debug( "drawImage" );

  double fnumx, fnumy;
  int numx, numy;

  fnumx = (double)dr2.width / (double)i->width();
  fnumy = (double)dr2.height / (double)i->height();

  numx = (int)ceil( fnumx );
  numy = (int)ceil( fnumy );

  sdldr->w = i->width();
  sdldr->h = i->height();

  SDL_Rect *sdlsr = NULL;
  if ( sr != NULL_RECT ) {
    sdlsr = new SDL_Rect;
    sdlsr->x = sr.left;
    sdlsr->y = sr.top;
    sdlsr->w = sr.width;
    sdlsr->h = sr.height;
  }

  int x, y;
  for( y = 0; y < numy; y++ ) {
    for( x = 0; x < numx; x++ ) {
      sdldr->x = dr2.left + x * i->width();
      sdldr->y = dr2.top + y * i->height();

      SDL_BlitSurface( i->getSurface(), sdlsr, s, sdldr );
    }
  }

  popClipRect();
  delete sdldr;

}


void SDLImageObject::drawImageStreched( ImageObject &image, const Rect& dr, const Rect &sr )
{
  Rect dr2 = dr;
  dr2.left += pRelX;
  dr2.top += pRelY;
  visDebug( dr2 );
  updated = true;
  SDLImageObject *i = (SDLImageObject*)&image;

//  cout << "* Ui::SDLDrawInterface::drawImageTiled(  )" << endl;
  pushClipRect( dr2 );
  if ( clipRect().area() <= 0 ) {
    popClipRect();
    return;
  }

  SDL_Rect *sdldr = new SDL_Rect;

  //clipRect().debug( "drawImage" );

  double fnumx, fnumy;
  int numx, numy;

  fnumx = (double)dr.width / (double)i->width();
  fnumy = (double)dr.height / (double)i->height();

  numx = (int)ceil( fnumx );
  numy = (int)ceil( fnumy );

  sdldr->w = i->width();
  sdldr->h = i->height();

  SDL_Rect *sdlsr = NULL;
  if ( sr != NULL_RECT ) {
    sdlsr = new SDL_Rect;
    sdlsr->x = sr.left;
    sdlsr->y = sr.top;
    sdlsr->w = sr.width;
    sdlsr->h = sr.height;
  }

  int x, y;
  for( y = 0; y < numy; y++ ) {
    for( x = 0; x < numx; x++ ) {
      sdldr->x = dr2.left + x * i->width();
      sdldr->y = dr2.top + y * i->height();

      SDL_BlitSurface( i->getSurface(), sdlsr, s, sdldr );
    }
  }

  popClipRect();
  delete sdldr;

}


void SDLImageObject::drawImage( SDL_Surface& image, const Rect r, const Rect &sr )
{
  updated = true;
//  cout << "* Ui::SDLDrawInterface::drawImage( SDL_Surface& )" << endl;
  SDL_Rect *dr = new SDL_Rect;

  dr->x = r.left + pRelX;
  dr->y = r.top + pRelY;
  if ( r.width == 0 ) {
    dr->w = image.w;
  } else {
    dr->w = r.width;
  }
  if ( r.height == 0 ) {
    dr->h = image.h;
  } else {
    dr->h = r.height;
  }

  SDL_BlitSurface( &image, NULL, s, dr );

  delete dr;

}


void SDLImageObject::fillRect( const Rect& r, const Color& color )
{
  if ( color.getA() == 0 ) return;
  visDebug( r );
  updated = true;

	SDL_Rect dr;
  dr.x = r.left + pRelX;
  dr.y = r.top + pRelY;
  dr.w = r.width;
  dr.h = r.height;

  Color c = color;

	if ( c.getA() == 255 )
	  SDL_FillRect( s, &dr, getColor( c.getR(), c.getG(), c.getB() ) );
	else {
		SDL_Surface* s2 = SDL_CreateRGBSurface( SDL_SWSURFACE, dr.w, dr.h, s->format->BitsPerPixel, s->format->Rmask, s->format->Gmask, s->format->Bmask, s->format->Amask);
		SDL_Rect sr;
		sr.x = 0;
		sr.y = 0;
		sr.w = dr.w;
		sr.h = dr.h;
		SDL_FillRect( s2, &sr, getColor( c.getR(), c.getG(), c.getB() ) );
		SDL_SetAlpha( s2, SDL_SRCALPHA, c.getA() );
		SDL_BlitSurface( s2, &sr, s, &dr );
		SDL_FreeSurface( s2 );
	}
}


void SDLImageObject::outText( const wstring &text, Font &font, int left, int top, const Color& color )
{

  updated = true;
  if ( !font.isLoaded() ) return;
  SDL_Color c;
  c.r = color.getR();
  c.g = color.getG();
  c.b = color.getB();

  SDLFont *f = (SDLFont*)&font;

  SDL_Surface *text_surface;

  if ( sizeof( wchar_t ) == 4 ) {

    Uint16* d = (Uint16*)malloc( text.length()*2 + 2 );
    for ( unsigned int i = 0; i <= text.length(); i++ ){
      d[i] = (Uint16)text[i];
    }

    text_surface = TTF_RenderUNICODE_Blended( f->getFont(), d, c );

    free( d );

  } else {
    text_surface = TTF_RenderUNICODE_Blended( f->getFont(), (Uint16*)text.c_str(), c );
  }

  if ( text_surface != NULL ) {
    drawImage( *text_surface, Rect( left, top, text_surface->w, text_surface->h ) );

    SDL_FreeSurface( text_surface );
  }

}

void SDLImageObject::putPixel( int left, int top, const Color &color )
{
//TODO: replace fillRect with http://www.libsdl.org/pipermail/sdl/2001-January/032832.html
  fillRect ( Rect( left, top, 1, 1 ), color );
}

Uint32 SDLImageObject::getPixel( SDL_Surface *sur, const int& x, const int& y )
{
	assert( sur != NULL );
	int bpp = sur->format->BytesPerPixel;
	Uint8 *pix = (Uint8 *)sur->pixels + y * sur->pitch + x * bpp;

	switch ( bpp ) {
		case 1:
			return *pix;
		case 2:
			return *(Uint16*) pix;
		case 3:
			if ( SDL_BYTEORDER != SDL_BIG_ENDIAN ) {
				return pix[0] | pix[1] << 8 | pix[2] << 16;
			} else {
				return pix[0] << 16 | pix[1] << 8 | pix[2];
			}
		case 4:
			return *(Uint32*) pix;
	}
	return 0;
}

Color SDLImageObject::getPixel( const int& x, const int& y )
{
	Uint32 c = getPixel( getSurface(), x, y );
	Uint8 r, g, b, a;
	SDL_GetRGBA( c, getSurface()->format, &r, &g, &b, &a);
	return Color( r, g, b, a );
}


void SDLImageObject::hLine( int left, int top, int width, const Color &color )
{
  fillRect ( Rect( left, top, width, 1), color);
}

void SDLImageObject::vLine( int left, int top, int height, const Color &color )
{
  fillRect ( Rect( left, top, 1, height), color);
}


void SDLImageObject::pushClipRect( const Rect& r )
{
//  cout << "* pushClipRect(  )" << endl;
//  r.debug( "pushClipRect" );
  Rect r2 = r;
//  r2.top += pRelY;
//  r2.left += pRelX;
  pClipRects.append( r2 );
  r2.crop( clipRect() );
  setClipRect( r2 );
}



Rect SDLImageObject::popClipRect(  )
{
//  cout << "* popClipRect(  )" << endl;
  assert( pClipRects.count() > 0 );
  pClipRects.remove( pClipRects.count() - 1 );
  if ( pClipRects.count() > 0 ) {
    int i;
    Rect r = pClipRects.get( 0 );
    Rect r2;
    for ( i = 1; i < pClipRects.count(); i++ ) {
      r2 = pClipRects.get( i );
      r2.crop( r );
      r = r2;
    }
    setClipRect( r );
  } else {
    unsetClipRect();
  }

  return clipRect();
}

void SDLImageObject::setRelativePoint( const int left, const int top )
{
  pRelX = left;
  pRelY = top;
}

void SDLImageObject::relativePoint( int& left, int& top )
{
  left = pRelX;
  top = pRelY;
}


void SDLImageObject::setClipRect( const Rect& r )
{
  assert( s != NULL );

//  cout << "setClipRect(1): top: " << r.top << " left: " << r.left << " width: " << r.width << " height: " << r.height << endl;

  pClipRect = r;

  SDL_Rect dr;
  dr.x = r.left;
  dr.y = r.top;
  dr.w = r.width;
  dr.h = r.height;

  SDL_SetClipRect( s, &dr );

}

void SDLImageObject::unsetClipRect(  )
{
  assert( s != NULL );
  pClipRect.top = 0;
  pClipRect.left = 0;
  pClipRect.width = s->w;
  pClipRect.height = s->h;
  setClipRect( pClipRect );
}

void SDLImageObject::assignSurface( SDL_Surface *surface )
{
  if ( isLoaded() ) {
    freeImage();
  }
  updated = true;
  s = surface;
	if ( s != NULL ) {
		unsetClipRect();
	}
}


Uint32 SDLImageObject::getColor( Uint8 r, Uint8 g, Uint8 b)
{
  assert( s != NULL );
  return SDL_MapRGB( s->format, r, g, b );
}

Uint32 SDLImageObject::getColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
	assert( s != NULL );
	return SDL_MapRGBA( s->format, r, g, b, a );
}

void SDLImageObject::flip( bool conditional )
{
  if ( (conditional && updated) || (!conditional) ) {
    assert( s != NULL );
    SDL_Flip( s );
    updated = false;
  }
}

void SDLImageObject::setAlpha(unsigned short int a )
{
  //cout << "* SDLImageObject::setAlpha(  )" << endl;
	SDL_SetAlpha( s, SDL_SRCALPHA, a );
	SDL_Surface* s2 = SDL_DisplayFormat( s );
  if ( s2 != NULL) {
    delete s;
    s = s2;
  }
}

void SDLImageObject::visDebug( const Rect& r )
{
  return;
  SDL_Surface* tmps = SDL_CreateRGBSurface( SDL_SWSURFACE, r.width, r.height, s->format->BitsPerPixel,
                                  s->format->Rmask, s->format->Gmask, s->format->Bmask, s->format->Amask );
  SDL_Rect* sr = new SDL_Rect;
  SDL_Rect* dr = new SDL_Rect;

  dr->x = dr->y = 0;
  dr->w = r.width;
  dr->h = r.height;

  sr->y = r.top;
  sr->x = r.left;
  sr->h = r.height;
  sr->w = r.width;

  SDL_BlitSurface( s, sr, tmps, dr );

  SDL_FillRect( s, sr, SDL_MapRGB( s->format, 255, 0, 0 ) );

  SDL_Flip( s );
  SDL_Delay( 20 );

  SDL_BlitSurface( tmps, dr, s, sr );
  SDL_Flip( s );

  delete sr;
  delete dr;
}

