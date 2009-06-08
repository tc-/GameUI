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


#include "config.h"

#include <iostream>
#include <stdlib.h>

#include <gameui.h>
#include <uiwidget.h>
#include "uiimageobject.h"
#include "uigui.h"
#include "uisdlkeyboard.h"
#include "uilist.h"
#include "uiedit.h"
#include "uisdlfont.h"
#include "uisdlimageobject.h"
#include "uipushbutton.h"
#include "uiwindowframe.h"
#include "uiwindow.h"
#include "uivscrollbar.h"
#include "uihscrollbar.h"
#include "uiscrollframe.h"
#include "events.h"
#include "uicolor.h"
#include "uilabel.h"
#include "uicombobox.h"
#include "uipopup.h"
#include "uidropdownlist.h"
#include "uiimageborder.h"
#include "uilineborder.h"
#include "netwalkwindow.h"
#include "uitheme.h"
#include "uiutils.h"
#include "uiknob.h"
#include "uisdlcontrol.h"
#include "uitimer.h"
#include "uitabview.h"

#include "sigslot.h"

#include <stdio.h>
#include "SDL.h"
#include <stdlib.h>
#include <unistd.h>


using namespace std;
using namespace Ui;


void recursiveWidgetPlot( Widget* w, int& level )
{
	List<Widget*> wl;
	for( int p = 0; p < level; p++ ){	cout << "  "; }
	cout << "name: \"" << w->name() << "\" zIndex: " << w->zIndex() << endl;
	level++;
	w->getWidgetsInRect( wl, Rect( 0, 0, w->width(), w->height() ), false );
	if ( wl.count() > 0 )
		wl.remove( 0 );
	for ( int i = wl.count() - 1; i >= 0; i-- ) {
		recursiveWidgetPlot( wl.get( i ), level );
	}
	level--;
}


int main(int argc, char *argv[])
{

  const int screenWidth = 640;
  const int screenHeight = 480;
  const int screenBPP = 32;

	ImageBorder::useWithLoader();
	LineBorder::useWithLoader();

  string datadir;
//	datadir = getenv( "PWD" );
	char* buf = new char [2048];
	char* resbuf = getcwd( buf, 2048 );
	if ( resbuf != NULL )
		datadir = resbuf;
	delete buf;

  string fontsdatadir = datadir + "/Fonts";
  string imagedatadir = datadir + "/Images";

	wstring ver = L"v " + Utils::toWString( VERSION );


  Utils::startSection( "Initializing GameUITest" );


	Utils::startTask( "Creating Gui Object" );
	Gui* g = new Gui( screenWidth, screenHeight );

	Utils::startTask( "Initializing SDL Library" );
	SDLControl* sdlc = new SDLControl( g );

  if ( sdlc->initializeLibrary() ) {
    Utils::endTask( true );
  } else {
    Utils::endTask( false );
    exit(1);
  }

	SDL_WM_SetCaption( "GameUITest", NULL );

  Utils::startTask( "Setting Videomode: " + Utils::toString(screenWidth) + "x" + Utils::toString(screenHeight) + " " + Utils::toString(screenBPP) + " bpp" );
  sdlc->createScreen( screenWidth, screenHeight, screenBPP, 0 );
  Utils::endTask( true );


  Utils::startSection( "Loading Data" );
  Utils::setNotice( "Dataroot directory is: " + datadir );

  Theme::defaultTheme().loadTheme( imagedatadir + "/theme.ini", datadir, *sdlc );



  Utils::startSection( "Initializing Objects" );


  Utils::startTask( "Creating Events object" );
	Events* e = new Events();

	Utils::startTask( "Creating TabView1 object" );
	TabView* tv1 = new TabView( &g->fgFrame() );
	tv1->setTheme( Theme::defaultTheme() );
	tv1->setName( "TabView1" );
	tv1->setBounds( 0, 0, 250, 200 );
	tv1->setVisible( true );

	Utils::startTask( "Creating VersionLabel object" );
	Label* vl = new Label( &g->fgFrame() );
	vl->setTheme( Theme::defaultTheme() );
	vl->setFontColor( Color( 20,60,220 ) );
	vl->setBounds( screenWidth-60, screenHeight-18, 60, 18 );
	vl->setText( ver );
	vl->setName( "VersionLabel" );
	vl->setVisible( true );



	// A nice button :)
  Utils::startTask( "Creating Button1 object" );
  PushButton* b1 = new PushButton( &g->fgFrame() );
  b1->setTheme( Theme::defaultTheme(), "test_" );
	b1->setBounds( Utils::inMiddle( 224, 44 + 24 ) + 2, Utils::inMiddle( 224, 44 + 24 ) + 230, 44 + 24, 44 + 24 );
	b1->setText( L"Click Me!" );
	b1->setTooltip( L"Click or dubble click this button." );
  b1->setVisible( true );
  b1->onMousePressed.connect( e, &Events::b1mPressed );
  b1->onMouseDblClick.connect( e, &Events::b1DblClick );
  b1->setName( "Button1" );


	Utils::startTask( "Creating Scrollframe3 object" );
	ScrollFrame* f3 = new ScrollFrame( tv1 );
	f3->setTheme( Theme::defaultTheme() );
	f3->setLeft( 0 );
	f3->setTop( 0 );
	f3->setWidth( 246 );
	f3->setHeight( 196 );
	f3->setVisible( true );
	f3->setName( "Labels" );


	// scrollframe2 - A ScrollFrame, contains 4 Knobs and a HScrollbar
  Utils::startTask( "Creating Scrollframe2 object" );
	ScrollFrame* f2 = new ScrollFrame( tv1 );
  f2->setTheme( Theme::defaultTheme() );
	f2->setVisible( true );
	f2->setName( "Misc" );

	Utils::startTask( "Creating VScrollbar1 object" );
	VScrollbar* sb1 = new VScrollbar( NULL );
  sb1->setTheme( Theme::defaultTheme() );
  sb1->setName( "Scrollframe2Vscrollbar" );
	f2->setVScroll( sb1 );

	Utils::startTask( "Creating HScrollbar1 object" );
	HScrollbar* hsb1 = new HScrollbar( NULL );
	hsb1->setTheme( Theme::defaultTheme() );
	hsb1->setName( "Scrollframe2Hscrollbar" );
	f2->setHScroll( hsb1 );

  Utils::startTask( "Creating Knob1 object" );
  Knob* k1 = new Knob( f2 );
  k1->setTheme( Theme::defaultTheme() );
	k1->setTop( 105 );
	k1->setLeft( 10 );
	k1->setWidth( 35 );
	k1->setHeight( 35 );
	k1->setVisible( true );
	k1->setName( "Knob1" );

	Utils::startTask( "Creating Knob2 object" );
  Knob* k2 = new Knob( f2 );
	k2->setTheme( Theme::defaultTheme() );
	k2->setTop( 105 );
	k2->setLeft( 55 );
	k2->setWidth( 35 );
	k2->setHeight( 35 );
	k2->setVisible( true );
	k2->setName( "Knob2" );

	Utils::startTask( "Creating Knob3 object" );
  Knob* k3 = new Knob( f2 );
	k3->setTheme( Theme::defaultTheme() );
	k3->setTop( 105 );
	k3->setLeft( 100 );
	k3->setWidth( 35 );
	k3->setHeight( 35 );
	k3->setVisible( true );
	k3->setName( "Knob3" );

	Utils::startTask( "Creating Knob4 object" );
  Knob* k4 = new Knob( f2 );
	k4->setTheme( Theme::defaultTheme() );
	k4->setTop( 105 );
	k4->setLeft( 145 );
	k4->setWidth( 35 );
	k4->setHeight( 35 );
	k4->setVisible( true );
	k4->setName( "Knob4" );

	Utils::startTask( "Creating Label3 object" );
	Label* l4 = new Label( f2 );
	l4->setTheme( Theme::defaultTheme() );
	l4->setBounds( 200, 250, 90, 20 );
	l4->setMultiline( true );
	l4->setText( L"Hello World!" );
	l4->setTextHAlign( halignCenter );
	l4->setTextVAlign( valignTop );
	l4->setVisible( true );
	l4->setName( "HelloLabel" );

	Utils::startTask( "Creating HScrollbar1 object" );
	HScrollbar* sc1 = new HScrollbar( &g->fgFrame() );
	sc1->setTheme( Theme::defaultTheme() );
	sc1->setTop( 208 );
	sc1->setLeft( 2 );
	sc1->setWidth( 244 );
	sc1->setVisible( true );
	sc1->setScrollerMaxPos( 180+80 );
	sc1->setPageSize( 80 );
	sc1->setScrollerPos( 44 );
	sc1->setName( "TestHScroll" );
	sc1->setTooltip( L"Scroll this to resize the button below." );
	sc1->setTag( (void*)b1 );
	sc1->onScroll.connect( e, &Events::sc1Scroll );
	sc1->onScroll( sc1, 0 );
	// End of scrollframe2

	Utils::startTask( "Creating Label3 object" );
	Label* l3 = new Label( f3 );
	l3->setTheme( Theme::defaultTheme() );
	l3->setBounds( 30, 10, 188, 20 );
	l3->setMultiline( true );
	l3->setText( L"Hello World!" );
	l3->setTextHAlign( halignCenter );
	l3->setTextVAlign( valignTop );
	l3->setVisible( true );
	l3->setName( "HelloLabel" );



	// Edit boxes
  Utils::startTask( "Creating Edit1 object" );
  Edit* e1 = new Edit( &g->fgFrame() );
  e1->setTheme( Theme::defaultTheme() );
	e1->setTop( 2 );
	e1->setWidth( 200 );
	e1->setLeft( 270 );
	e1->setText( L"Test1" );
	e1->setVisible( true );
	e1->setName( "Edit1" );

  Utils::startTask( "Creating Edit2 object" );
  Edit* e2 = new Edit( &g->fgFrame() );
	e2->setTheme( Theme::defaultTheme() );
	e2->setTop( 28 );
	e2->setWidth( 300 );
	e2->setLeft( 270 );
	e2->setText( L"Bla Bla Blaaa" );
	e2->setVisible( true );
	e2->setName( "Edit2" );
	// End of Edit boxes



	// Window1 - Contains a multi line label and a button
  Utils::startTask( "Creating Window1 object" );
  Window* wf1 = new Window( &g->fgFrame() );
  wf1->setTheme( Theme::defaultTheme() );
	wf1->setLeft( 210 );
	wf1->setTop( 210 );
	wf1->setWidth( 200 );
	wf1->setHeight( 184 );
	wf1->setCaption( L"Test Caption" );
	wf1->setDrawmode( drawTransparent );
	wf1->moveToTop();
	wf1->setVisible( true );
	wf1->setName( "TransWindow" );

  Utils::startTask( "Creating Label1 object" );
  Label* l1 = new Label( wf1 );
  l1->setTheme( Theme::defaultTheme(), "white_" );
	l1->setHeight( 116 );
	l1->setAlign( walignTop );
	l1->setAnchorBottom( true );
	l1->setMultiline( true );
	//l1->setDrawmode( drawOpaque );
	l1->setText( L"This is a\nMultiline\nLabel.\nThis line is way too long and should be wordwrapped a lot of times." );
	l1->setTooltip( L"The first three lines are linebreaked with linebreak chars and the fourth is wordwrapped." );
	l1->setTextHAlign( halignCenter );
	l1->setTextVAlign( valignCenter );
	l1->setVisible( true );
	l1->setName( "TransLabel" );

  Utils::startTask( "Creating Button5 object" );
  PushButton* b5 = new PushButton( wf1 );
  b5->setTheme( Theme::defaultTheme(), "trans_" );
	b5->setLeft( 36 );
	b5->setTop( 124 );
	b5->setWidth( 120 );
	b5->setMaxWidth( 140 );
	b5->setMinWidth( 80 );
	b5->setAnchors( true, true, false, true );
//	b5->setAlign( walignTop );
	b5->setText( L"Okay" );
	b5->setDrawmode( drawTransparent );
	b5->setVisible( true );
	b5->setName( "TransButton" );
	b5->onButtonPressed.connect( e, &Events::transbuttonPressed );
	// End of Window1

	Window wf3( &g->fgFrame() );
	wf3.setBounds( 100, 100, 210, 210 );
	wf3.moveToTop();
	wf3.setTitleHeight( 0 );
	wf3.setDrawmode( drawTransparent );
	wf3.setTheme( Theme::defaultTheme() );

	PushButton bw1( &wf3 );
	bw1.setHeight( 40 );
	bw1.setAlign( walignTop );
	bw1.setText( L"Top" );
	bw1.setTooltip( L"Drag the edges of this window" );
	bw1.setTheme( Theme::defaultTheme() );
	bw1.setVisible( true );
	bw1.onButtonPressed.connect( e, &Events::transbuttonPressed );


	PushButton bw2( &wf3 );
	bw2.setHeight( 40 );
	bw2.setAlign( walignBottom );
	bw2.setTheme( Theme::defaultTheme() );
	bw2.setText( L"Bottom" );
	bw2.setVisible( true );
	bw2.onButtonPressed.connect( e, &Events::transbuttonPressed );

	PushButton bw3( &wf3 );
	bw3.setTheme( Theme::defaultTheme() );
	bw3.setWidth( 40 );
	bw3.setAlign( walignLeft );
	bw3.setText( L"Left" );
	bw3.setVisible( true );
	bw3.onButtonPressed.connect( e, &Events::transbuttonPressed );

	PushButton bw4( &wf3 );
	bw4.setWidth( 40 );
	bw4.setAlign( walignRight );
	bw4.setTheme( Theme::defaultTheme() );
	bw4.setText( L"Right" );
	bw4.setVisible( true );
	bw4.onButtonPressed.connect( e, &Events::transbuttonPressed );

	PushButton bw5( &wf3 );
	bw5.setBounds( 40, 40, 40, 40 );
	bw5.setAnchors( true, false, true, false );
	bw5.setTheme( Theme::defaultTheme() );
	bw5.setText( L"l,t" );
	bw5.setVisible( true );
	bw5.onButtonPressed.connect( e, &Events::transbuttonPressed );

	PushButton bw6( &wf3, L"l,r,t", Theme::defaultTheme(), 80, 40, 40, 40 );
	bw6.setAnchors( true, true, true, false );
	bw6.setVisible( true );
	bw6.onButtonPressed.connect( e, &Events::transbuttonPressed );

	PushButton bw7( &wf3, L"r,t", Theme::defaultTheme(), 120, 40, 40, 40 );
	bw7.setAnchors( false, true, true, false );
	bw7.setVisible( true );
	bw7.onButtonPressed.connect( e, &Events::transbuttonPressed );

	PushButton bw8( &wf3 );
	bw8.setBounds( 40, 80, 40, 40 );
	bw8.setAnchors( true, false, true, true );
	bw8.setTheme( Theme::defaultTheme() );
	bw8.setText( L"l,t,b" );
	bw8.setVisible( true );
	bw8.onButtonPressed.connect( e, &Events::transbuttonPressed );

	PushButton bw9( &wf3 ); // Middle!
	bw9.setBounds( 80, 80, 40, 40 );
	bw9.setAnchors( true, true, true, true );
	bw9.setTheme( Theme::defaultTheme() );
	bw9.setImage( Theme::defaultTheme().getImage( "coder" ) );
	bw9.setText( L"" );
	bw9.setVisible( true );
	bw9.onButtonPressed.connect( e, &Events::transbuttonPressed );

	PushButton bw10( &wf3 );
	bw10.setBounds( 120, 80, 40, 40 );
	bw10.setAnchors( false, true, true, true );
	bw10.setTheme( Theme::defaultTheme() );
	bw10.setText( L"r,t,b" );
	bw10.setVisible( true );
	bw10.onButtonPressed.connect( e, &Events::transbuttonPressed );

	PushButton bw11( &wf3 );
	bw11.setBounds( 40, 120, 40, 40 );
	bw11.setAnchors( true, false, false, true );
	bw11.setTheme( Theme::defaultTheme() );
	bw11.setText( L"l,b" );
	bw11.setVisible( true );
	bw11.onButtonPressed.connect( e, &Events::transbuttonPressed );

	PushButton bw12( &wf3 );
	bw12.setBounds( 80, 120, 40, 40 );
	bw12.setAnchors( true, true, false, true );
	bw12.setTheme( Theme::defaultTheme() );
	bw12.setText( L"l,r,b" );
	bw12.setVisible( true );
	bw12.onButtonPressed.connect( e, &Events::transbuttonPressed );

	PushButton bw13( &wf3 );
	bw13.setBounds( 120, 120, 40, 40 );
	bw13.setAnchors( false, true, false, true );
	bw13.setTheme( Theme::defaultTheme() );
	bw13.setText( L"r,b" );
	bw13.setVisible( true );
	bw13.onButtonPressed.connect( e, &Events::transbuttonPressed );

	wf3.setWidth( 50 );
	wf3.setHeight( 50 );
	wf3.setVisible( true );

	// WindowFrame2 - A WindowFrame, contains a drop down menu and a label
	Utils::startTask( "Creating WindowFrame2 object" );
  WindowFrame* wf2 = new WindowFrame( &g->fgFrame() );
  wf2->setTheme( Theme::defaultTheme() );
	wf2->setLeft( 270 );
	wf2->setTop( 75 );
	wf2->setWidth( 150 );
	wf2->setVisible( true );
	wf2->setName( "ResWindowFrame" );

  Utils::startTask( "Creating Label1 object" );
  Label* l2 = new Label( wf2 );
	l2->setTheme( Theme::defaultTheme() );
	l2->setBounds( 4, 0, 188, 20 );
	l2->setMultiline( true );
	l2->setText( L"Select resolution" );
	l2->setTextHAlign( halignLeft );
	l2->setTextVAlign( valignTop );
	l2->setVisible( true );
	l2->setName( "ResLabel" );

  Utils::startTask( "Creating DropDownList1 object" );
  DropdownList* dl1 = new DropdownList;
  dl1->setTheme( Theme::defaultTheme() );
  DropListItem* dli1 = new DropListItem( dl1, L"640x480" );
	DropListItem* dli2 = new DropListItem( dl1, L"800x600" );
	DropListItem* dli3 = new DropListItem( dl1, L"1024x768" );
	DropListItem* dli4 = new DropListItem( dl1, L"1280x1024" );
	DropListItem* dli5 = new DropListItem( dl1, L"1600x1200" );

  Utils::startTask( "Creating Combobox1 object" );
  Combobox* cb1 = new Combobox( wf2 );
  cb1->setTheme( Theme::defaultTheme() );
	cb1->setDropdownList( dl1 );
	cb1->setTop( 20 );
	cb1->setWidth( 120 );
	cb1->setLeft( 4 );
  //cb1.setReadOnly();
	cb1->setText( L"- select one -" );
	cb1->setVisible( true );
	cb1->setName( "ResCombobox" );
	// End of WindowFrame2



	// This is actually a whole game :)
  Utils::startTask( "Creating NetwalkWindow object" );
  NetwalkWindow* nw = new NetwalkWindow( &g->fgFrame(), NULL );
  nw->setTheme( Theme::defaultTheme() );
	nw->setTop( 100 );
	nw->setLeft( 450 );
	nw->setSkill( 0 );
	nw->newGame();
	nw->moveToTop();
	nw->setVisible( true );
	nw->setName( "NetwalkWindow" );



	Utils::startTask( "Creating DragFrom Button object" );
	PushButton* dfb = new PushButton( &g->fgFrame() );
	dfb->setName( "DragFrom" );
	dfb->setBounds( 2, 280, 64, 64 );
	dfb->setTheme( Theme::defaultTheme() );
	dfb->setText( L"" );
	dfb->setTooltip( L"You can drag a coder from here" );
	dfb->setImage( Theme::defaultTheme().getImage( "coder" ) );
	dfb->setVisible( true );
	dfb->onDrag.connect( e, &Events::dfbDrag );

	Utils::startTask( "Creating DragTo Button object" );
	PushButton* dtb = new PushButton( &g->fgFrame() );
	dtb->setName( "DragTo" );
	dtb->setBounds( 68, 280, 86, 64 );
	dtb->setTheme( Theme::defaultTheme() );
	dtb->setText( L"Drop here" );
	dtb->setTooltip( L"You can drop a coder here" );
	int* dti = new int;
	*dti = 0;
	dtb->setTag( dti );
	dtb->setVisible( true );
	dtb->onDrop.connect( e, &Events::dtbDrop );
	dtb->onDragOver.connect( e, &Events::dtbDragOver );
	dtb->onButtonPressed.connect( e, &Events::btbPressed );
	nw->moveToTop(); // TODO Fix The Bug

	Utils::endTask( true );

	g->fgFrame().setName( "BGFrame" );
	g->fgFrame().setTheme( Theme::defaultTheme() );
  g->fgFrame().setBgColor( Color( 200, 216, 245 ) );



  Utils::startSection( "GameUITest Up And Running" );

	Timer* t = new Timer();
	t->setTimeout( 5000 );
	t->onTimer.connect( e, &Events::tTimer );
	t->setEnabled( true );


  sdlc->keyboard().setRepeat( - 1 );

	Utils::setNotice( "Entering main loop" );

	/*
	List<Widget*> wl;
	g->fgFrame().getWidgetsInRect( wl, Rect( 0, 0, g->fgFrame().width(), g->fgFrame().height() ) );
	for ( int i = 0; i < wl.count(); i++ ) {
		Widget* w = wl.get( i );
		cout << " - " << w->name() << " z: " << w->zIndex() << endl;
	}*/
	int l = 0;
	recursiveWidgetPlot( (Widget*)&g->fgFrame(), l );

  while( !sdlc->terminated() )
  {
    sdlc->doHandleEvents();
		sdlc->clearEvents(); // Should not Be Needed

    g->render();
    sdlc->flip();
    sdlc->sleep( 32 );
    g->timerTick();
  }

  b1->onButtonPressed.disconnect( e );
  b1->onMouseDblClick.disconnect( e );

  Theme::defaultTheme().freeAllResources();
  sdlc->finalizeLibrary();


	Utils::startSection( "Destroying Objects" );

	Utils::startTask( "Destroying DragTo Button Object" );
	delete dtb;
	Utils::startTask( "Destroying DragFrom Button Object" );
	delete dfb;
	Utils::startTask( "Destroying NetwalkWindow Object" );
	delete nw;
	Utils::startTask( "Destroying DropListItems Object" );
	delete dli5;
	delete dli4;
	delete dli3;
	delete dli2;
	delete dli1;
	Utils::startTask( "Destroying DropdownList1 Object" );
	delete dl1;
	Utils::startTask( "Destroying Combobox1 Object" );
	delete cb1;
	Utils::startTask( "Destroying Lable2 Object" );
	delete l2;
	Utils::startTask( "Destroying WindowFrame2 Object" );
	delete wf2;
	Utils::startTask( "Destroying Button5 Object" );
	delete b5;
	Utils::startTask( "Destroying Lable1 Object" );
	delete l1;
	Utils::startTask( "Destroying Edit2 Object" );
	delete e2;
	Utils::startTask( "Destroying Edit1 Object" );
	delete e1;
	Utils::startTask( "Destroying Label3 Object" );
	delete l3;
	Utils::startTask( "Destroying HScrollbar1 Object" );
	delete sc1;
	Utils::startTask( "Destroying Knob4 Object" );
	delete k4;
	Utils::startTask( "Destroying Knob3 Object" );
	delete k3;
	Utils::startTask( "Destroying Knob2 Object" );
	delete k2;
	Utils::startTask( "Destroying Knob1 Object" );
	delete k1;
	Utils::startTask( "Destroying VScrollBar1 Object" );
	delete sb1;
	Utils::startTask( "Destroying ScrollFrame2 Object" );
	delete f2;
	Utils::startTask( "Destroying Button1 Object" );
	delete b1;
	Utils::startTask( "Destroying VersionLabel Object" );
	delete vl;
	Utils::startTask( "Destroying Events Object" );
	delete e;
	Utils::startTask( "Destroying SDLControl Object" );
	delete sdlc;
	Utils::startTask( "Destroying Gui Object" );
	delete g;
	Utils::endTask( true );
	Utils::setNotice( "Cee Yah! :)" );
	string test;
	Utils::fromWString( L"Test", test );
	Utils::setNotice( test );
}

