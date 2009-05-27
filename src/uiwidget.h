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
Headerfile for the Ui::Widget class
*/

#ifndef UIWIDGET_H
#define UIWIDGET_H

#include <gameui.h>
#include <uikey.h>
#include <uifont.h>
#include <uirect.h>
#include <uicolor.h>
#include <uitheme.h>
#include <uiimageobject.h>
#include <sigslot.h>

#include <string>

using std::string;

using namespace sigslot;

namespace Ui
{

	class MouseCursor;

	class DragObject;

	class Tooltip;

	class Timer;

	enum WidgetAlignType { walignNone, walignLeft, walignRight, walignTop, walignBottom, walignClient };

	struct MouseButtons {
		MouseButtons() {
			left = false;
			right = false;
			middle = false;
			wheelUp = false;
			wheelDown = false;
		}
		bool left;
		bool right;
		bool middle;
		bool wheelUp;
		bool wheelDown;

		string toString() {
			string ret = "(";
			if ( left ) ret += "l";
			if ( right ) ret += "r";
			if ( middle ) ret += "m";
			if ( wheelUp ) ret += "u";
			if ( wheelDown ) ret += "d";
			ret += ")";
			return ret;
		}
	};
	//enum MouseButtons { MBT_NONE = 0, MBT_LEFT = 1, MBT_MIDDLE = 2, MBT_RIGHT = 4, MBT_WHEELUP = 8, MBT_WHEELDOWN = 16 };

//	typedef int MouseButtons;
//
//	const int MBT_NONE = 0;
//
//	const int MBT_LEFT = 1;
//	const int MBT_MIDDLE = 2;
//	const int MBT_RIGHT = 4;
//
//	const int MBT_WHEELUP = 8;
//	const int MBT_WHEELDOWN = 16;


	enum Drawmode {
		DM_OPAQUE,
		DM_TRANSPARENT
	};

	class Frame;

	class Gui;

	class Border;

	class Widget;

	/**
	 * Internal class used to keep track of Objects to be updated.
	 */
	class UpdateWidget
	{

		public:
			Widget* o;
			Rect r;
			UpdateWidget( Widget* obj, const Rect rec ): o( obj ),r( rec ) {}
	};

	/**
	 * Base class for all visual widgets.
	 *
	 * Base you class on this class if you want to create a completely new type of widget.
	 */
	class Widget : public has_slots<>
	{

		public:

			Widget( Frame* parent = NULL );
			Widget( Frame* parent, int x, int y, int width, int height );
			virtual ~Widget(  );

			/**
			 * Returns name of widget.
			 * @note this property is not used by GameUI, it's only avaiable to simplify debugging.
			 * @see Widget::setName()
			 * @return name of widget.
			 */
			virtual string name() {
				return pName;
			}

			/**
			 * Setter for the name property.
			 * @see Widget::name()
			 * @param s new value for name.
			 */
			virtual void setName( const string& s ) {
				pName = s;
			}

			/**
			 * Assign a Theme to this widget.
			 * @param t the Theme to use.
			 * @param prefix prefix to add to theme property names, default ''
			 * @see Theme
			 */
			virtual void setTheme( Theme & t, const string prefix = "" );
			virtual void themeUpdated( Theme & t );

			virtual MouseCursor* cursor() const;
			virtual void setCursor( MouseCursor* mc );
			virtual MouseCursor* getCursor( const int& x, const int& y ) {
				return pCursor;
			}

			virtual WidgetAlignType align() const {
				return pAlign;
			}

			virtual void setAlign( const WidgetAlignType& al ) {
				pAlign = al;

				if ( isManaged() ) sizeChanged( Rect( 0 - borderLeft(), 0 - borderTop(), width(), height() ) );
			}

			virtual bool anchorLeft() const {
				return pAnchorL;
			}

			virtual bool anchorRight() const {
				return pAnchorR;
			}

			virtual bool anchorTop() const {
				return pAnchorT;
			}

			virtual bool anchorBottom() const {
				return pAnchorB;
			}

			virtual void setAnchorLeft( const bool& a = true );
			virtual void setAnchorRight( const bool& a = true );
			virtual void setAnchorTop( const bool& a = true );
			virtual void setAnchorBottom( const bool& a = true );

			virtual int anchorLeftValue() const {
				return pAnchorLV;
			}

			virtual int anchorRightValue() const {
				return pAnchorRV;
			}

			virtual int anchorTopValue() const {
				return pAnchorTV;
			}

			virtual int anchorBottomValue() const {
				return pAnchorBV;
			}

			virtual void setAnchors( const bool& l, const bool& r, const bool& t, const bool& b );

			virtual int minWidth(  ) const {
				return pMinWidth;
			}

			virtual void setMinWidth( int mw );

			virtual int minHeight(  ) const {
				return pMinHeight;
			}

			virtual void setMinHeight( int mh );

			virtual int maxWidth(  ) const {
				return pMaxWidth;
			}

			virtual void setMaxWidth( int mw );

			virtual int maxHeight(  ) const {
				return pMaxHeight;
			}

			virtual void setMaxHeight( int mh );

			/**
			 * Returns the position in the y axis of the widget relative to parent frame.
			 * @return the position in the y axis of the widget relative to parent frame.
			 * @see Widget::setTop() Widget::parent() Widget::absoluteYPos() Widget::left() Widget::height()
			 */
			virtual int top(  ) const;
			virtual int relativeTop(  ) const;

			/**
			 * Set the position in the y axis of the widget relative to parent frame.
			 * @param t the position in the y axis of the widget relative to parent frame.
			 * @see Widget::top()
			 */
			virtual void setTop( int t );

			/**
			 * Returns the position in the x axis of the widget relative to parent frame.
			 * @return the position in the x axis of the widget relative to parent frame.
			 * @see Widget::setLeft() Widget::parent() Widget::absoluteYPos() Widget::top() Widget;;width()
			 */
			virtual int left(  ) const;
			virtual int relativeLeft(  ) const;

			virtual void setLeft( int l );

			/**
			 * Returns the width of the widget.
			 * @return  the width of the widget.
			 * @see Widget::setWidth() Widget::height() Widget::left()
			 */
			virtual int width(  ) const {
				return pWidth;
			}

			/**
			 * Set the width of the widget.
			 * @param w the width of the widget.
			 * @see Widget::width()
			 */
			virtual void setWidth( int w );

			/**
			 * Returns the height of the widget.
			 * @return the height of the widget.
			 * @see Widget::setHeight() Widget::width() Widget::top()
			 */
			virtual int height(  ) const {
				return pHeight;
			}

			/**
			 * Set the height of the widget.
			 * @param h the height of the widget.
			 * @see Widget::height()
			 */
			virtual void setHeight( int h );

			/**
			 * Return Drawmode of the widget.
			 * Drawmode changes the way the widget is drawn. DM_TRANSPARENT can always be used but is slightly slower than DM_OPAQUE. In DM_OPAQUE mode the bgColor is also drawn behind the widget if no border is assigned while in DM_TRANSPARENT mode it's not.
			 * @return Drawmode of the widget.
			 * @see Ui::Drawmode Widget::setDrawmode() Widget::border() Widget::bgColor()
			 */
			virtual Drawmode drawmode(  ) const;

			/**
			 * Set Drawmode of the widget.
			 * @param dm Drawmode of the widget.
			 * @see Widget::drawmode()
			 */
			virtual void setDrawmode( Drawmode dm );

			/**
			 * Returns the position of the widget in the x axis relative to the whole screen.
			 * @return the position of the widget in the x axis relative to the whole screen.
			 * @see Widget::absoluteYPos() Widget::top() Widget::left() Widget;;width() Widget::height()
			 */
			virtual int absoluteXPos( ) const;

			/**
			 * Returns the position of the widget in the y axis relative to the whole screen.
			 * @return the position of the widget in the y axis relative to the whole screen.
			 * @see Widget::absoluteXPos() Widget::top() Widget::left() Widget;;width() Widget::height()
			 */
			virtual int absoluteYPos( ) const;

			/**
			 * - TO BE REMOVED - Returns a Ui::Rect object containing the visible area on the object.
			 * @return Ui::Rect object containing the visible area on the object.
			 * @see Ui::Rect
			 */
			virtual Rect getClipRect(  ) const;

			virtual int borderTop( ) const;
			virtual int borderLeft( ) const;
			virtual int borderBottom( ) const;
			virtual int borderRight( ) const;
			virtual int clientWidth( );
			virtual int clientHeight( );
			virtual int clientVisibleWidth( );
			virtual int clientVisibleHeight( );

			virtual void getWidgetsInRect( List<Widget*>& l, const Rect r, bool recursive = true );

			/**
			 * Returns the Widget located at the point (x;y).
			 * @note Ui::Widget allways returns this but Ui::Frame can return Widgets inside itself.
			 * @param x the x position relative from Widget.
			 * @param y the x position relative from Widget.
			 * @return the Widget located at the point (x;y).
			 */
			virtual Widget* getWidgetAt( int x, int y, bool recursive = false ) {
				return this;
			}

			/**
			 * Parent that owns and contains this Ui::Widget.
			 * @see Ui::Widget::hasParent() Ui::Widget::isManaged() Ui::Widget::setParent().
			 */
			virtual Frame* parent(  ) const {
				return pParent;
			}

			/**
			 * Setter for the parent property.
			 * @see Ui::Widget::parent().
			 */
			virtual void setParent( Frame* p );

			/**
			 * Returns true if this Ui::Widget is owned by a parent Ui::Frame.
			 * @see Ui::Widget::parent().
			 */
			inline bool hasParent(  ) const {
				return ( pParent != NULL );
			};

			/**
			 * Gives access to associated Ui::Gui object.
			 * @note If you only want to access the Ui::DrawInterface object, call the interface() function instead.
			 * @warning This function can return NULL.
			 * @return Ui::Gui associated with current object.
			 * @see Ui::Widget::interface() Ui::Gui
			 */
			virtual Gui& gui(  ) const;

			/**
			 * Setter for the gui property.
			 * @see Ui::Widget:gui().
			 */
			virtual void setGui( Gui* s );

			/**
			 * Indicates if this Ui::Widget is visible on screen or not.
			 * @see Ui::Widget::setVisible().
			 */
			virtual bool visible(  ) const;

			/**
			 * Setter for the visible property.
			 * @see Ui::Widget::visible().
			 */
			virtual void setVisible( bool v );

			/**
			 * Indicates if this Ui::Widget can receive events.
			 * @see Ui::Widget::setEnabled().
			 */
			virtual bool enabled(  ) const {
				return pEnabled;
			}

			/**
			 * Setter for the enabled property.
			 * @see Ui::Widget::enabled().
			 */
			virtual void setEnabled( bool e );

			/**
			 * This property can be used by application writer and is not used by GameUI.
			 * @see Ui::Widget::setTag().
			 */
			virtual void* tag(  ) const {
				return pTag;
			}

			/**
			 * Setter for the tag property.
			 * @see Ui::Widget::tag().
			 */
			virtual void setTag( void* t ) {
				pTag = t;
			};

			/**
			 * The font that will be used when rendering text on this Ui::Widget.
			 * @todo Is this just a waste of a pointer? Some widgets will not use this at all.
			 * @see Ui::Widget::setFont().
			 */
			virtual Font* font(  ) const {
				return pFont;
			}

			/**
			 * Setter for the font property.
			 * @see Ui::Widget::font().
			 */
			virtual void setFont( Font* f );

			/**
			 * The color to be used on text rendered on this widget.
			 * @todo Should this be removed for the same argument as Ui::Widget::font().
			 * @see Ui::Widget::setFontColor().
			 */
			virtual Color fontColor(  ) const {
				return pFontColor;
			}

			/**
			 * Setter for the fontColor property.
			 * @see Ui::Widget::fontColor().
			 */
			virtual void setFontColor( Color c ) {
				pFontColor = c;
				updated();
			}

			/**
			 * The color used to draw the background of this Ui::Widget if visible.
			 * @see Ui::Widget::setBgColor().
			 */
			virtual Color bgColor(  ) const {
				return pBgColor;
			}

			/**
			 * Setter for the bgColor property.
			 * @see Ui::Widget::bgColor().
			 */
			virtual void setBgColor( Color c ) {
				pBgColor = c;
				updated();
			}

			/**
			 * The Ui::Border object to use as border for this Ui::Widget.
			 * @see Ui::Widget::setBorder() Ui::Border.
			 */
			virtual Border* border() const {
				return pBorder;
			};

			/**
			 * Setter for the border property.
			 * @see Ui::Widget::border().
			 */
			virtual void setBorder( Border* bs );

			/**
			 * Indicates if this Ui::Widget currently is the focused widget to receive key events.
			 * @see Ui::Widget::setFocused().
			 */
			virtual bool focused(  ) const {
				return pFocused;
			}

			/**
			 * Setter for the focused property.
			 * @see Ui::Widget::focused().
			 */
			virtual void setFocused( bool f );

			/**
			 * The string to show in tooltip.
			 * @see Ui::Widget::setTooltip() Ui::Tooltip.
			 */
			virtual wstring tooltip(  ) const {
				return pToolTip;
			}

			/**
			 * Setter for the tooltip property.
			 * @see Ui::Widget::tooltip().
			 */
			virtual void setTooltip( wstring t ) {
				pToolTip = t;
			}

			/**
			 * The main render method, this method should be overridden in derived classes to give the widget its own look.
			 * @see Ui::Widget::renderBorder().
			 */
			virtual void render( ImageObject& img, const Rect& r );

			/**
			 * This method renders the border and background of this Ui::Widget, override if you want the background to be drawn differently.
			 * @see Ui::Widget::.
			 */
			virtual void renderBorder( ImageObject& img );

			/**
			 * Tells object is updated and needs to call render() to reflect changes.
			 * @note Doesn't do anything if beginUpdate() is called.
			 * @see Ui::Widget::beginUpdate() Ui::Widget::render()
			 */
			virtual void updated(  );
			virtual void updated( const Rect& r );

			virtual void sizeChanged( const Rect& news );

			/**
			 * Halts automatic calls to render() for example when many update operations will be performed in a row. Call endUpdate() when you want the automatic render calls to be performed again.
			 *
			 * This function stacks, if you call beginUpdate() 5 times you have to call endUpdate() 5 times for the automatic render() calls to start again.
			 * @see Ui::Widget::endUpdate()
			 */
			virtual void beginUpdate(  );

			/**
			 * Resumes automatic render() calls.
			 *
			 * Calls render() when beginUpdate() and endUpdate() has been called the same number of times.
			 * @note Make sure you call beginUpdate() and endUpdate() the same number of times, otherwise automatic render() will stop working completly.
			 * @see Ui::Widget::beginUpdate()
			 */
			virtual void endUpdate( bool dontupdate = false );

			/**
			 * Set the limits in which the object's size can vary.
			 * @param minw minimum width.
			 * @param minh minimum height.
			 * @param maxw maximum width.
			 * @param maxh maximum height.
			 */
			virtual void setSizeLimit( int minw, int minh, int maxw, int maxh );
			virtual void setBounds( int left, int top, int width, int height );
			virtual void move( const int newleft, const int newtop );

			/**
			 * Returns true if the object's constraints is managed by a parent.
			 * @return true if the object's constraints is managed by a parent.
			 */
			virtual bool isManaged(  ) const;

			virtual Widget* mouseMove( int x, int y, MouseButtons mb );
			virtual Widget* mouseClick( int x, int y, MouseButtons mb );
			virtual Widget* mouseDblClick( int x, int y, MouseButtons mb );
			virtual Widget* mousePressed( int x, int y, MouseButtons mb );
			virtual Widget* mouseReleased( int x, int y, MouseButtons mb );
			virtual Widget* mouseIn( MouseButtons mb );
			virtual Widget* mouseOut( MouseButtons mb );
			virtual Widget* keyPressed( Key key );
			virtual Widget* keyReleased( Key key );

			/**
			 * Sets new size of object.
			 * @param newwidth the new width.
			 * @param newheight the new height.
			 * @see Ui::Widget::setBounds() Ui::Widget::setSizeLimit() Ui::Widget::width() Ui::Widget::height()
			 */
			virtual void resize( int newwidth, int newheight );
			virtual void timerTick();

			/**
			 * Returns the Z-index of this Ui::Widget, this is the order in which the Ui::Widget will be drawn on it's parent Ui::Frame.
			 * @see Ui::Widget::setZIndex()
			 */
			virtual int zIndex( );

			/**
			 * Sets the Z-index of this Ui::Widget, this is the order in which the Ui::Widget will be drawn on it's parent Ui::Frame.
			 * @see Ui::Widget::setZIndex() Ui::Frame::setZIndex()
			 */
			virtual int setZIndex( const int z );

			/**
			 * Assign the highest possible Z-index to this Ui::Widget.
			 * @see Ui::Widget::moveToBottom()
			 */
			virtual void moveToTop();

			/**
			 * Assign the lowest possible Z-index to this Ui::Widget.
			 * @see Ui::Widget::moveToTop()
			 */
			virtual void moveToBottom();

			/**
			 * Gives access to the Ui::DrawInterface object associated with current Ui::Gui object in use.
			 *
			 * @warning this function can return NULL.
			 * @return Ui::DrawInterface object associated with current Ui::Screen object in use.
			 * @see Ui::Widget::screen() Ui::DrawInterface Ui::Gui
			 */
			virtual ImageObject& screen(  );


			/** @name Static methods */
			//@{

			/**
			 * Adds a Ui::Widget to the update queue.
			 */
			static void updatedWidget( Widget* o, const Rect r = NULL_RECT );

			/**
			 * Clears the widget update queue.
			 */
			static void clearUpdatedWidgets();

			/**
			 * Returns the widget update queue, containing all widgets that have been updated since last call to clearUpdateWidgets().
			 * @see Ui::Widget::clearUpdatedWidgets()
			 */
			static List<UpdateWidget*>& updatedWidgets(  ) {
				static List<UpdateWidget*> pUpdatedWidgets;
				return pUpdatedWidgets;
			}

			//@}


			/** @name Events */
			//@{

			//! Called just before the Widget is destroyed.
			signal1<Widget&> onDestroy;

			//! Called when mouse has been pressed and released on the same widget.
			signal1<Widget&> onMouseClick;

			//! Called when widget receives a double click from the mouse.
			signal1<Widget&> onMouseDblClick;

			//! Called when a mouse button is pressed over the widget.
			signal2<Widget&, MouseButtons> onMousePressed;

			//! Called when a mouse button is released over the widget.
			signal2<Widget&, MouseButtons> onMouseReleased;

			//! Called when mouse is moving over the widget.
			signal4<Widget&, int, int, MouseButtons> onMouseMove;

			//! Called when the mouse cursor enters the widget's area.
			signal1<Widget&> onMouseIn;

			//! Called when the mouse cursor leaves the widget's area.
			signal1<Widget&> onMouseOut;

			//! Called when a key is pressed while widget is in focus.
			signal2<Widget&, Key> onKeyPressed;

			//! Called when a key is released while widget is in focus.
			signal2<Widget&, Key> onKeyReleased;

			signal4<Widget*, int, int, DragObject**> onDrag;

			signal5<Widget*, int, int, DragObject*, bool&> onDrop;

			signal6<Widget*, int, int, DragObject*, bool&, ImageObject**> onDragOver;

			signal4<Widget*, int, int, Tooltip**> onTooltip;

			//@}

		private:

			string pName;

			WidgetAlignType pAlign;

			bool pAnchorL;
			bool pAnchorR;
			bool pAnchorT;
			bool pAnchorB;
			int pAnchorLV;
			int pAnchorRV;
			int pAnchorTV;
			int pAnchorBV;

			int pMinWidth;
			int pMinHeight;
			int pMaxWidth;
			int pMaxHeight;
			int pTop;
			int pLeft;
			int pWidth;
			int pHeight;
			int pZIndex;

			Drawmode pDrawmode;

			Frame* pParent;
			Gui* pGui;
			MouseCursor* pCursor;

			Theme* pTheme;
			string pThemePrefix;

			bool pVisible;
			bool pEnabled;
			bool pFocused;

			int pDontRender;
			bool pIsUpdated;
			bool pToldParentUpdate;

			void* pTag;

			wstring pToolTip;
			Timer* pToolTipTimer;
			Tooltip* pToolTipObject;

			int pLastX;
			int pLastY;

			Font* pFont;
			Color pFontColor;
			Color pBgColor;
			Border* pBorder;

			void tooltipTimerCallback( Timer& t, int& to );

		protected:

			/**
			 * Makes the Ui::Screen object channel all mouse events to this object. No other objects will get any mouse events.
			 * @see Ui::Widget::releaseMouseInput()
			 */
			void grabMouseInput();

			/**
			 * Makes the Ui::Screen object stop channeling all mouse events to this object.
			 * @see Ui::Widget::grabMouseInput()
			 */
			void releaseMouseInput();

	};

}

#endif
