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


#ifndef UIUIDRAGOBJECT_H
#define UIUIDRAGOBJECT_H

#include <uipopup.h>

namespace Ui {

/**
Drag and Drop object.

	@author Tommy Carlsson <tc@coderworld.net>
*/
class DragObject : public Popup
{
public:
  DragObject();
  ~DragObject();

	virtual void render( Rect area );

	/**
	 *  Image to draw in the DragObject.
	 * @return the image.
	 * @see DragObject::denyImage() DragObject::setImage()
	 */
	virtual ImageObject* image() const { return pImage; }
	/**
	 *  Set image()
	 * @param img The image to set.
	 * @param adjustSize True if the size of the DragObject should be adjusted to fit the image.
	 * @see DragObject::image()
	 */
	virtual void setImage( ImageObject* img, bool adjustSize = true );

	/**
	 *  Image to be displayed on top of image() when hovering Widget does not accept the drop.
	 * @return the deny image.
	 * @see DragObject::image() DragObject::setDenyImage()
	 */
	virtual ImageObject* denyImage() const { return pDImage; }
	/**
	 *  Set the deny image to use.
	 * @param dimg the deny image.
	 * @see DragObject::denyImage()
	 */
	virtual void setDenyImage( ImageObject* dimg ) { pDImage = dimg; updated(); }

	/**
	 * @see Popup::popup()
	 */
	virtual void popup( const int x, const int y, Gui& gui );
	/**
	 * @see Popup::close()
	 */
	virtual void close();

	virtual void mouseMove( int x, int y, MouseButtons mb );
	virtual void mousePressed( int x, int y, MouseButtons mb );
	virtual void mouseReleased( int x, int y, MouseButtons mb );

private:

	bool pMoving;
	bool pAccepts;
	ImageObject* pImage;
	ImageObject* pDImage;
	ImageObject* pTmpDImage;

};

}

#endif
