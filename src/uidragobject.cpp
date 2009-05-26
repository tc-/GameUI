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


#include "uidragobject.h"
#include <uipopup.h>
#include <uigui.h>

namespace Ui {

DragObject::DragObject()
 : Popup()
{
	pMoving = false;
	pImage = NULL;
	pDImage = NULL;
	pTmpDImage = NULL;
	pAccepts = false;
}


DragObject::~DragObject()
{
}


void DragObject::render( Rect area )
{
	if ( !active() ) return;
	if ( gui() == NULL ) return;
	gui()->screen().pushClipRect( area );

	if ( border() != NULL ) {
		border()->render( Rect( left(), top(), width(), height() ), gui()->screen() );
	}

	int x = left();
	int y = top();
	int w = width();
	int h = height();
	if ( border() != NULL ) {
		y += border()->heightTop;
		x += border()->widthLeft;
		w -= border()->widthLeft + border()->widthRight;
		h -= border()->heightTop + border()->heightBottom;
	}

	if ( pImage != NULL )
		gui()->screen().drawImage( *pImage, Rect( x, y, w, h ) );

	if ( !pAccepts ) {
		if ( pTmpDImage != NULL )
			gui()->screen().drawImage( *pTmpDImage, Rect( x + Utils::align( w, pTmpDImage->width(), alignCenter ), y, w, h ) );
		else if ( pDImage != NULL )
			gui()->screen().drawImage( *pDImage, Rect( x + Utils::align( w, pDImage->width(), alignCenter ), y + Utils::align( h, pDImage->height(), alignCenter ), w, h ) );
	}

	gui()->screen().popClipRect();

}

void DragObject::popup( const int x, const int y, Gui& gui )
{
	Popup::popup( x, y, gui);
	gui.setMouseChannelPopup( this );
}

void DragObject::close()
{
	Popup::close( );
	if ( gui() != NULL )
		gui()->setMouseChannelPopup( NULL );
}


void DragObject::setImage( ImageObject* img, bool adjustSize )
{
	pImage = img;
	if ( ( pImage != NULL ) && ( adjustSize ) ) {
		setWidth( pImage->width() );
		setHeight( pImage->height() );
	} else {
		updated();
	}
}



void DragObject::mouseMove( int x, int y, MouseButtons mb )
{
	if ( pMoving ) {
		setPosition( x - (width() / 2), y - (height() / 2) );
		Widget* w = gui()->fgFrame().getWidgetAt( x, y, true );
		if ( w != NULL ) {
			bool accept = false;
			ImageObject* tmpDenyImage = NULL;
			w->onDragOver( w, x - w->absoluteXPos(), y - w->absoluteYPos(), this, accept, &tmpDenyImage );
			pAccepts = accept;
			pTmpDImage = tmpDenyImage;
		}
	}
}


void DragObject::mousePressed( int x, int y, MouseButtons mb )
{
	pMoving = true;
	Widget* w = gui()->fgFrame().getWidgetAt( x, y, true );
	if ( w != NULL ) {
		bool accept = false;
		ImageObject* tmpDenyImage = NULL;
		w->onDragOver( w, x - w->absoluteXPos(), y - w->absoluteYPos(), this, accept, &tmpDenyImage );
		pAccepts = accept;
		pTmpDImage = tmpDenyImage;
	}

}


void DragObject::mouseReleased( int x, int y, MouseButtons mb )
{
	if ( pMoving ) {
		pMoving = false;
		Widget* w = gui()->fgFrame().getWidgetAt( x, y, true );
		if ( w != NULL ) {
			bool accept = false;
			w->onDrop( w, x - w->absoluteXPos(), y - w->absoluteYPos(), this, accept );
			close();
		}
	}
}


}
