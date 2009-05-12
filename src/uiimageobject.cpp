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
 
 /**
@file
Implementation of the Ui::ImageObject class
	*/

#include <uiimageobject.h>
#include <uilineborder.h>

using namespace Ui;


ImageObjectFactory ImageObject::pImageObjectFactory = NULL;


Rect ImageObject::sectionRect( const int& index )
{
	if ( index < 0 ) return NULL_RECT;
	if ( index >= numSections() ) return NULL_RECT;

	int xSect = 0;
	int ySect = 0;

	if ( index != 0 ) {
		int numX = (int)floor( (double)(width() / pSecWidth) );
		ySect = (int)floor( (double)(index / numX) );
		xSect = index - ( numX * ySect );
	}
	Rect r;
	r.top = ySect * pSecHeight;
	r.left = xSect * pSecWidth;
	r.width = pSecWidth;
	r.height = pSecHeight;
	return r;
}

// Xiaolin Wu's algorithm
// TODO: A buggy pixel somewhere in the code :-(
void ImageObject::line ( double x1, double y1, double x2, double y2, const Color &color )
{
	double tmp, gradient, xend, yend, xgap, ygap, xpxl1, ypxl1, xpx1l, intery, xpxl2, ypxl2;
	double deltaX = x2 - x1;
	double deltaY = y2 - y1;
	
	Rect r = Utils::getRect( (int)x1, (int)y1, (int)x2, (int)y2 );
//	r.debug( "" );
	ImageObject* img = ImageObject::createImageObject( r.width, r.height );
	
	
	
	if ( fabs(deltaY) < fabs(deltaX) ) {
//		printf("Horizontal line\n");
			
		if( x2 < x1 ) {
			// Swap x1 and x2
			tmp = x1;
			x1 = x2;
			x2 = tmp;

			// Swap y1 and y2
			tmp = y1;
			y1 = y2;
			y2 = tmp;

			deltaX = x2 - x1;
			deltaY = y2 - y1;
		}

		gradient = deltaY/deltaX;
		
		// handle first endpoint
		xend = round(x1);
		yend = y1 + gradient * (xend - x1);
		
		xgap = rfpart(x1 + 0.5);
		
		xpxl1 = xend;  // this will be used in the main loop
		ypxl1 = ipart(yend);

		img->putPixel( (int)xpx1l - r.left, (int)ypxl1 - r.top, Color( color.getR(), color.getG(), color.getB(), (unsigned char)(255.0 * fpart(yend) * xgap)) );
		img->putPixel( (int)xpxl1 - r.left, (int)(ypxl1 + 1) - r.top, Color( color.getR(), color.getG(), color.getB(), (unsigned char)(255.0 * fpart(yend) * xgap)) );
		intery = yend + gradient; // first y-intersection for the main loop

		// handle second endpoint
		xend = round(x2);
		yend = y2 + gradient * (xend - x2);
		xgap = rfpart(x2 - 0.5);
		xpxl2 = xend;  // this will be used in the main loop
		ypxl2 = ipart(yend);
		img->putPixel( (int)xpxl2 - r.left, (int)ypxl2 - r.top, Color( color.getR(), color.getG(), color.getB(), (unsigned char)(255.0 * rfpart(yend) * xgap)) );
		img->putPixel( (int)xpxl2 - r.left, (int)(ypxl2 + 1) - r.top, Color( color.getR(), color.getG(), color.getB(), (unsigned char)(255.0 * fpart(yend) * xgap)) );

		// main loop
		for ( int x = (int)xpxl1 + 1; (double)x < xpxl2 - 1; x++ ) {
			img->putPixel( x - r.left, (int)ipart(intery) - r.top, Color( color.getR(), color.getG(), color.getB(), (unsigned char)(255.0 * rfpart( intery ))) );
			img->putPixel( x - r.left, (int)(ipart(intery) + 1) - r.top, Color( color.getR(), color.getG(), color.getB(), (unsigned char)(255.0 * fpart( intery ))) );
			intery = intery + gradient;
		}
	} else {
//		printf("Vertical line\n");

		if( y2 < y1 ) {
			// Swap x1 and x2
			tmp = x1;
			x1 = x2;
			x2 = tmp;

			// Swap y1 and y2
			tmp = y1;
			y1 = y2;
			y2 = tmp;

			deltaX = x2 - x1;
			deltaY = y2 - y1;
		}

		gradient = deltaX/deltaY;
		
		// handle first endpoint
		yend = round(y1);
		xend = x1 + gradient * (yend - y1);
		ygap = rfpart(y1 + 0.5);
		xpxl1 = ipart(xend);
		ypxl1 = yend;
		img->putPixel( (int)xpxl1 - r.left, (int)ypxl1 - r.top, Color( color.getR(), color.getG(), color.getB(), (unsigned char)(255.0 * fpart(xend) * ygap)) );
		img->putPixel( (int)(xpxl1 + 1) - r.left, (int)ypxl1 - r.top, Color( color.getR(), color.getG(), color.getB(), (unsigned char)(255.0 * fpart(xend) * ygap)) );
		intery = xend + gradient; // first y-intersection for the main loop

		// handle second endpoint
		xend = x1 + gradient * (yend - y2);
		yend = round(y2);
		ygap = rfpart(y2 - 0.5);
		xpxl2 = ipart(xend);
		ypxl2 = yend;
		
		img->putPixel( (int)xpxl2 - r.left, (int)ypxl2 - r.top, Color( color.getR(), color.getG(), color.getB(), (unsigned char)(255.0 * rfpart(xend) * ygap)) );
		img->putPixel( (int)(xpxl2 + 1) - r.left, (int)ypxl2 - r.top, Color( color.getR(), color.getG(), color.getB(), (unsigned char)(255.0 * fpart(xend) * ygap)) );

		// main loop
		for ( int y = (int)ypxl1 + 1; (double)y < ypxl2 - 1; y++ ) {
			img->putPixel( (int)ipart(intery) - r.left, y - r.top, Color( color.getR(), color.getG(), color.getB(), (unsigned char)(255.0 * rfpart( intery ))) );
			img->putPixel( (int)(ipart(intery) + 1) - r.left, y - r.top, Color( color.getR(), color.getG(), color.getB(), (unsigned char)(255.0 * fpart( intery ))) );
			intery = intery + gradient;
		}
	}

	drawImage( *img, r );
	delete img;
}

