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


#include "uitheme.h"

#include <uiborder.h>
#include <uiinifile.h>
#include <uilibcontrol.h>
#include <uimouse.h>

namespace Ui {

Theme::Theme()
{
  pName = "Default";
  pDesc = "The Default Theme.";

  pDefaultFont = NULL;

  pDCDefault = Color( 0,0,0 );
  pDCFont = Color( 0,0,0 );
  pDCButton = Color( 0,0,0 );
  pDCSelect = Color( 0,0,0 );
  pDCBorderLine = Color( 0,0,0 );

	pUpdated = false;
	pDontUpdate = 0;
}


Theme::~Theme()
{
  clearAllResources();
}


Border* Theme::getBorder( const string name, const defBorder db )
{
  for( int i = 0; i < pBorders.count(); i++ ) {
    if ( pBorders.get(i)->name == name )
      return pBorders.get(i)->border;
  }
  return NULL;
}

void Theme::setBorder( const string name, Border* border, const bool clone )
{
  for( int i = 0; i < pBorders.count(); i++ ) {
    if ( pBorders.get(i)->name == name ) {
      pBorders.get(i)->border = border;
			updated();
			return;
    }
  }
  BorderName* bn = new BorderName( name, border, clone );
  pBorders.append( bn );
	updated();
}


ImageObject* Theme::getImage( const string name )
{
  for( int i = 0; i < pImages.count(); i++ ) {
    if ( pImages.get(i)->name == name )
      return pImages.get(i)->image;
  }
  return NULL;
}

void Theme::setImage( const string name, ImageObject* img, const bool clone )
{
  for( int i = 0; i < pImages.count(); i++ ) {
    if ( pImages.get(i)->name == name ) {
      pImages.get(i)->image = img;
			updated();
			return;
    }
  }
  ImageName* in = new ImageName( name, img, clone );
  pImages.append( in );
	updated();
}

Color Theme::getColor( const string name, Color dc ) const
{
  for( int i = 0; i < pColors.count(); i++ ) {
    if ( pColors.get(i)->name == name )
      return pColors.get(i)->color;
  }
  return dc;
}


Color Theme::getColor( const string& name, const defColor& dc ) const
{
  Color c;
  if ( dc == dcDefault ) {
    c = pDCDefault;
  } else if ( dc == dcFont ) {
    c = pDCFont;
  } else if ( dc == dcButton ) {
    c = pDCButton;
  } else if ( dc == dcSelect ) {
    c = pDCSelect;
  } else if ( dc == dcBorderLine ) {
    c = pDCBorderLine;
  } else {
    assert( true );
  }
  return getColor( name, c );
}

void Theme::setColor( const string name, const Color c, const bool clone )
{
  if ( name == "default" ) {
    setDefaultColor( c, dcDefault );
  } else if ( name == "default.font" ) {
    setDefaultColor( c, dcFont );
  } else if ( name == "default.button" ) {
    setDefaultColor( c, dcButton );
  } else if ( name == "default.select" ) {
    setDefaultColor( c, dcSelect );
  } else if ( name == "default.borderline" ) {
    setDefaultColor( c, dcBorderLine );
    Utils::setNotice( "Default BorderLine color set to: " + Utils::toString( c ) );
  }
  for( int i = 0; i < pColors.count(); i++ ) {
    if ( pColors.get(i)->name == name ) {
      pColors.get(i)->color = c;
			updated();
			return;
    }
  }
  ColorName* cn = new ColorName( name, c );
  pColors.append( cn );
	updated();
}

void Theme::setDefaultColor( Color c, const defColor& dc )
{
  if ( dc == dcDefault ) {
    pDCDefault = c;
  } else if ( dc == dcFont ) {
    pDCFont = c;
  } else if ( dc == dcButton ) {
    pDCButton = c;
  } else if ( dc == dcSelect ) {
    pDCSelect = c;
  } else if ( dc == dcBorderLine ) {
    pDCBorderLine = c;
  } else {
    assert( true );
  }
	updated();
}


Font* Theme::getFont( const string name )
{
  for( int i = 0; i < pFonts.count(); i++ ) {
    if ( pFonts.get(i)->name == name )
      return pFonts.get(i)->font;
  }
  return pDefaultFont;
}
Font* Theme::getFont( const string name, Font* defFont )
{
	for( int i = 0; i < pFonts.count(); i++ ) {
		if ( pFonts.get(i)->name == name )
			return pFonts.get(i)->font;
	}
	return defFont;
}


void Theme::setFont( const string name, Font* f, const bool clone )
{
  for( int i = 0; i < pFonts.count(); i++ ) {
    if ( pFonts.get(i)->name == name ) {
      pFonts.get(i)->font = f;
			updated();
			return;
    }
  }
  FontName* fn = new FontName( name, f, clone );
  pFonts.append( fn );
	updated();
}

MouseCursor* Theme::getCursor( const string& name )
{
	for( int i = 0; i < pCursors.count(); i++ ) {
		if ( pCursors.get(i)->name == name )
			return pCursors.get(i)->cursor;
	}
	return pDefaultCursor;
}

void Theme::setCursor( const string& name, MouseCursor* c, const bool clone )
{
	assert( c != NULL );
	for( int i = 0; i < pCursors.count(); i++ ) {
		if ( pCursors.get(i)->name == name ) {
			pCursors.get(i)->cursor = c;
			updated();
			return;
		}
	}
	CursorName* cn = new CursorName( name, c, clone );
	pCursors.append( cn );
	updated();
}


bool Theme::loadTheme( const string fname, const string rootDir, LibControl& lc )
{
  return loadTheme( fname, rootDir, rootDir, rootDir, lc.defaultImageLoader(), lc.defaultFontLoader() );
}

bool Theme::loadTheme( const string fname, const string borderRoot, const string fontRoot, const string imageRoot, LibControl& lc )
{
  return loadTheme( fname, borderRoot, fontRoot, imageRoot, lc.defaultImageLoader(), lc.defaultFontLoader() );
}

bool Theme::loadTheme( const string fname, const string rootDir, ImageLoader il, FontLoader fl )
{
  return loadTheme( fname, rootDir, rootDir, rootDir, il, fl );
}


bool Theme::loadTheme( const string fname, const string borderRoot, const string fontRoot, const string imageRoot, ImageLoader il, FontLoader fl )
{
  return loadTheme( fname, ThemeLoadOptions( il, fl, borderRoot, fontRoot, imageRoot, this ) );
}


Border* loadBorder( InifileSection& is, const ThemeLoadOptions& op )
{
  string borderType = is.keyStringValue( "type", "LineBorder" );
  BorderLoadFunc bf = BorderLoader::getLoader( borderType );
  if ( bf != NULL ) {
    return bf( &is, op );
  } else {
    return NULL;
  }
}


bool Theme::loadTheme( const string fname, const ThemeLoadOptions& op )
{
  Inifile ini;
  Utils::startTask( "Reading theme from file: " + fname );
  if ( ini.load( fname ) ) {
		beginUpdate();
    Utils::endTask( true );
    ini.setSection( "Theme" );
    pName = ini.readString( "name", "Default" );
    pDesc = ini.readString( "description", "The Default Theme." );
    Utils::setNotice( "Themename is \"" + pName + "\"" );

    for ( int i = 0; i < ini.sections.count(); i++ ) {
      InifileSection* inis = ini.sections.get( i );
      assert( inis != NULL );
      string sname = inis->name();
      if ( sname.substr(0,7) == "border." ) {
        string bname = sname.substr( 7, sname.length() - 7 );
        Utils::startTask( "Loading border \"" + bname + "\"" );
        Border* b = loadBorder( *inis, op );
        if ( b != NULL ) {
          setBorder( bname, b );
        }
        Utils::endTask( (b != NULL) );

      } else if ( sname.substr(0,6) == "color." ) {
        string bname = sname.substr( 6, sname.length() - 6 );
        Color c;
        Utils::fromString( inis->keyStringValue( "color", "0,0,0" ), c );
        c.setColor( c.getR(), c.getG(), c.getB(), inis->keyIntValue( "alpha", 255 ) );
        setColor( bname, c );
      } else if ( sname.substr(0,5) == "font." ) {
        string bname = sname.substr( 5, sname.length() - 5 );
        Utils::startTask( "Loading font \"" + bname + "\"" );
        Font* f = op.fontLoader( inis, op );
        if ( f != NULL ) {
          setFont( bname, f );
          if ( bname == "default" ) {
            setDefaultFont( f );
            Utils::setNotice( "Font \"" + bname + "\" set as default font." );
          }
        }
        Utils::endTask( ( f != NULL ) );
      } else if ( sname.substr(0,6) == "image." ) {
        string iname = sname.substr( 6, sname.length() - 6 );
        string ifile = inis->keyStringValue( "file", "" );
        Utils::startTask( "Loading image \"" + iname + "\" from file \"" + ifile + "\"");
        ImageObject* img = op.imageLoader( op.imageRoot+"/"+ifile, inis, op );
        if ( img != NULL )
          setImage( iname, img );
        Utils::endTask( ( img != NULL ) );
			} else if ( sname.substr(0,7) == "cursor." ) {
				string iname = sname.substr( 7, sname.length() - 7 );
				string ifile = inis->keyStringValue( "file", "" );
				Utils::startTask( "Loading cursor \"" + iname + "\" from file \"" + ifile + "\"");
				ImageObject* img = op.imageLoader( op.imageRoot+"/"+ifile, inis, op );
				if ( img != NULL ) {
					Color tc, ic;
					Utils::fromString( inis->keyStringValue( "transparentcolor", "0,0,255" ), tc );
					Utils::fromString( inis->keyStringValue( "invertcolor", "255,0,0" ), ic );
					int hotx, hoty;
					hotx = inis->keyIntValue( "hotspotx", 0 );
					hoty = inis->keyIntValue( "hotspoty", 0 );
					MouseCursor* mc = MouseCursor::createMouseCursor();

					if ( mc != NULL ) {

						mc->load( *img, hotx, hoty, tc, ic );
						if ( mc->isLoaded() ) {

							setCursor( iname, mc, false );
							if ( iname == "default" )
								setDefaultCursor( mc );

						} else {
							Utils::setError( "Could not load cursor into cursor object", true );
						}
					} else {
						Utils::setError( "Could not create cursor object", true );
					}
				} else {
					Utils::setError( "Could not load image", true );
				}
//				setImage( iname, img );
				Utils::endTask( true );
			}
    }

    InifileSection* s = ini.section( "Entries", true );
    for ( int i = 0; i < s->keys.count(); i++ ) {
      InifileKey* k = s->keys.get( i );
      string kname = k->name();
      if ( kname.substr(0,7) == "border." ) {
        kname = kname.substr( 7, kname.length() - 7 );
        string kvalue = k->valueString();
        if ( kvalue.length() > 0 ) {
          if ( kvalue[0] == '$' ) kvalue.erase(0,1);
          setBorder( kname, getBorder( kvalue ), true );
        }
      } else if ( kname.substr(0,6) == "color." ) {
        kname = kname.substr( 6, kname.length() - 6 );
        string col = k->valueString();
        if ( col.length() > 0 ) {
          Color c;
          if ( col[0] == '$' ) {
            col.erase(0,1);
            c = getColor( col );
          } else {
            Utils::fromString( col, c );
          }
          setColor( kname, c );
        }
      } else if ( kname.substr(0,5) == "font." ) {
        kname = kname.substr( 5, kname.length() - 5 );
        string kvalue = k->valueString();
        if ( kvalue.length() > 0 ) {
          if ( kvalue[0] == '$' ) kvalue.erase(0,1);
          Font* f = getFont( kvalue );
          if ( f != NULL ) {
            setFont( kname, f, true );
            if ( kname == "default" ) {
              setDefaultFont( f );
              Utils::setNotice( "Font \"" + kvalue + "\" set as default font." );
            }
          }
        }
			} else if ( kname.substr(0,7) == "cursor." ) {
				kname = kname.substr( 7, kname.length() - 7 );
				string kvalue = k->valueString();
				if ( kvalue.length() > 0 ) {
					if ( kvalue[0] == '$' ) kvalue.erase(0,1);
					MouseCursor* mc = getCursor( kvalue );
					if ( mc != NULL ) {
						setCursor( kname, mc, true );
						if ( kname == "default" ) {
							setDefaultCursor( mc );
							Utils::setNotice( "Cursor \"" + kvalue + "\" set as default cursor." );
						}
					}
				}
			} else if ( kname.substr(0,6) == "image." ) {
        kname = kname.substr( 6, kname.length() - 6 );
        string kvalue = k->valueString();
        if ( kvalue.length() > 0 ) {
          if ( kvalue[0] == '$' ) {
            kvalue.erase(0,1);
            ImageObject* img = getImage( kvalue );
            if ( img != NULL ) {
              setImage( kname, img, true );
            } else {
              Utils::setError( "There is no image called \"" + kvalue + "\" loaded.", false );
            }
          } else {
            InifileSection tmpIni;
            Utils::startTask( "Loading image \"" + kname + "\" from file \"" + k->valueString() + "\"" );
            ImageObject* img = op.imageLoader( op.imageRoot+"/"+k->valueString(), &tmpIni, op );
            if ( img != NULL ) {
              setImage( kname, img );
            }
            Utils::endTask( ( img != NULL ) );
          }
        }
      }

    }
		endUpdate();
  } else {
    Utils::endTask( false );
    return false;
  }
  return true;
}

void Theme::freeAllResources()
{
	beginUpdate();
  freeFonts();
  freeBorders();
  freeImages();
  freeColors();
	freeCursors();
	endUpdate();
}

void Theme::freeFonts()
{
  for( int i = 0; i < pFonts.count(); i++ ) {
    FontName* fn = pFonts.get( i );
    if ( !fn->clone )
      delete fn->font;
    delete fn;
  }
  pFonts.clear();
	updated();

}

void Theme::freeBorders()
{
  for( int i = 0; i < pBorders.count(); i++ ) {
    BorderName* bn = pBorders.get( i );
    if ( !bn->clone )
      delete bn->border;
    delete bn;
  }
  pBorders.clear();
	updated();

}

void Theme::freeImages()
{
  for( int i = 0; i < pImages.count(); i++ ) {
    ImageName* in = pImages.get( i );
    if ( !in->clone )
      delete in->image;
    delete in;
  }
  pImages.clear();
	updated();
}

void Theme::freeColors()
{
  clearColors();
}

void Theme::freeCursors()
{
  for( int i = 0; i < pCursors.count(); i++ ) {
		CursorName* cn = pCursors.get( i );
		if ( !cn->clone )
			delete cn->cursor;
		delete cn;
	}
	pCursors.clear();
	updated();
}

void Theme::clearAllResources()
{
	beginUpdate();
	clearFonts();
  clearBorders();
  clearImages();
  clearColors();
	clearCursors();
	endUpdate();
}

void Theme::clearFonts()
{
  for( int i = 0; i < pFonts.count(); i++ ) {
    delete pFonts.get( i );
  }
  pFonts.clear();
	updated();
}

void Theme::clearBorders()
{
  for( int i = 0; i < pBorders.count(); i++ ) {
    delete pBorders.get( i );
  }
  pBorders.clear();
	updated();
}

void Theme::clearImages()
{
  for( int i = 0; i < pImages.count(); i++ ) {
    delete pImages.get( i );
  }
  pImages.clear();
	updated();
}

void Theme::clearColors()
{
  for( int i = 0; i < pColors.count(); i++ ) {
    delete pColors.get( i );
  }
  pColors.clear();
	updated();
}

void Theme::clearCursors()
{
	for( int i = 0; i < pCursors.count(); i++ ) {
		delete pCursors.get( i );
	}
	pCursors.clear();
	updated();
}

void Theme::updated()
{
	pUpdated = true;
	if ( isUpdated() ) {
		onUpdated( *this );
	}
}

bool Theme::isUpdated()
{
	return ( (pUpdated) && (pDontUpdate == 0) );
}

void Theme::beginUpdate()
{
	pDontUpdate++;
}

void Theme::endUpdate()
{
	assert( pDontUpdate != 0 );
	pDontUpdate--;
	if ( (pDontUpdate == 0) ) {
		updated();
	}
}

}
