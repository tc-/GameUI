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
