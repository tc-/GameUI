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

#include <uiborder.h>

namespace Ui {

List<BorderLoaderItem*>& BorderLoader::pFuncs()
{
  static List<BorderLoaderItem*> pf;
  return pf;
}

void BorderLoader::addLoader( const string borderName, BorderLoadFunc loader )
{
	for( int i = 0; i < pFuncs().count(); i++ ){
		BorderLoaderItem* itm = pFuncs().get( i );
		assert( itm != NULL );
		if ( itm->name == borderName ) {
			if ( itm->func != loader )
				itm->func = loader;
			return;
		}
	}
  BorderLoaderItem* bli = new BorderLoaderItem( borderName, loader );
  pFuncs().append( bli );
}

BorderLoadFunc BorderLoader::getLoader( const string& name )
{
  for( int i = 0; i < pFuncs().count(); i++ ) {
    if ( pFuncs().get( i )->name == name ) {
      return pFuncs().get( i )->func;
    }
  }
  return NULL;
}

}
