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

	/**
	 * Widget alignment policy on parent Frame.
	 *
	 * @see Widget::align() Frame::arrangeChildren().
	 */
	enum WidgetAlign {
		walignNone,			//!< Do not try to align this Widget.
		walignLeft,			//!< Align Widget to the left.
		walignRight,		//!< Align Widget to the right.
		walignTop,			//!< Align Widget to the top.
		walignBottom,		//!< Align Widget to the bottom.
		walignClient		//!< Let Widget fill the remaining area after all other Widgets has been aligned.
	};

	/**
	 * Struct repressenting Pressed mousebuttons.
	 */
	struct MouseButtons {
		//! Left mouse button was pressed.
		bool left;
		//! Right mouse button was pressed.
		bool right;
		//! Middle mouse button was pressed.
		bool middle;
		//! Wheel was scrolled up.
		bool wheelUp;
		//! Wheel was scrolled down.
		bool wheelDown;

		//! Set default values.
		MouseButtons() {
			left = right = middle = wheelUp = wheelDown = false;
		}

		//! Make string repressentation.
		string toString() {
			string ret = "[";
			if ( left ) ret += "l";
			if ( right ) ret += "r";
			if ( middle ) ret += "m";
			if ( wheelUp ) ret += "u";
			if ( wheelDown ) ret += "d";
			ret += "]";
			return ret;
		}
	};

	/**
	 * Opaque or transparent.
	 *
	 * As soon as any part of the Widget is transparent or alpha blended Widget::drawmode() should be set to
	 * drawTransparent. Only use drawOpaque if the Widget has no areas that show areas of the parent Frame.
	 * @see Widget::drawmode().
	 */
	enum Drawmode {
		drawOpaque, //!< Whole Widget has solid color.
		drawTransparent //!< Widget has transparent areas.
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
			Widget( Frame* parent, Theme& theme);
			Widget( Frame* parent, int x, int y, int width, int height );
			Widget( Frame* parent, Theme& theme, int x, int y, int width, int height );
			virtual ~Widget(  );

			/**
			 * Set default values, run by the constructor.
			 *
			 * @note When virtual methods are run from constructor they behave like non-vrtual methods.
			 */
			virtual void Init();

			/**
			 * Name of widget, available for use by the application writer for easier debugging.
			 *
			 * @note this property is not used by GameUI, it's only avaiable to simplify debugging.
			 * @return name of widget.
			 * @see setName().
			 */
			virtual string name() {
				return pName;
			}

			/**
			 * Setter for the name property.
			 *
			 * @param s new value for name.
			 * @see name().
			 */
			virtual void setName( const string& s ) {
				pName = s;
			}

			/**
			 * Assign a Theme to this widget.
			 *
			 * @note Override this method if you want to add theme support to your custom widget.
			 * @param t the Theme to use.
			 * @param prefix prefix to add to theme property names, default ""
			 * @see Ui::Theme.
			 */
			virtual void setTheme( Theme & t, const string prefix = "" );

			/**
			 * Reloads the theme, call if theme has been updated.
			 *
			 * @see setTheme().
			 */
			virtual void themeUpdated( Theme & t );

			/**
			 * The Ui::MouseCursor to be shown over this Widget.
			 *
			 * @see setCursor() Ui::MouseCursor::setCursor().
			 */
			virtual MouseCursor* cursor() const;

			/**
			 * Setter for the property
			 *
			 * @param mc the new Ui::MouseCursor.
			 * @see cursor().
			 */
			virtual void setCursor( MouseCursor* mc );

			/**
			 * The Ui::MouseCursor to be shown over a certain area of this Widget.
			 *
			 * @todo When is this used instead of cursor()? Are both needed?
			 * @param x the horizontal position relative to this Widget.
			 * @param y the vertical position relative to this Widget.
			 * @see cursor().
			 */
			virtual MouseCursor* getCursor( const int& x, const int& y ) {
				return pCursor;
			}

			/**
			 * Widget alignment on parent Frame.
			 *
			 * @see setAlign() WidgetAlign Frame.
			 */
			virtual WidgetAlign align() const {
				return pAlign;
			}

			/**
			 * Setter for the align property.
			 *
			 * @see align.
			 */
			virtual void setAlign( const WidgetAlign& al ) {
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
			 * The position in the y axis of the widget relative to parent frame.
			 *
			 * @return the position in the y axis of the widget relative to parent frame.
			 * @see setTop() parent() absoluteYPos() left() height()
			 */
			virtual int top(  ) const;

			/**
			 * The vertical position of this Widget relative to parent frame scroll.
			 *
			 * @note Same as top() but this also takes into account the parent's scroll values.
			 * @see top() Ui::Frame::scrollY().
			 */
			virtual int relativeTop(  ) const;

			/**
			 * Setter for the top property.
			 *
			 * @param t the new top value.
			 * @see top().
			 */
			virtual void setTop( int t );

			/**
			 * The horizontal position of this Widget relative to parent frame.
			 *
			 * @return the position in the x axis of the widget relative to parent frame.
			 * @see setLeft() parent() absoluteYPos() top() width() relativeLeft().
			 */
			virtual int left(  ) const;

			/**
			 * The horizontal position of this Widget relative to parent frame scroll.
			 *
			 * @note Same as left() but this also takes into account the parent's scroll values.
			 * @see left() Ui::Frame::scrollX().
			 */
			virtual int relativeLeft(  ) const;

			/**
			 * Setter for the left property.
			 *
			 * @param l the new left value.
			 * @see left().
			 */
			virtual void setLeft( int l );

			/**
			 * The width of this Widget.
			 *
			 * @see setWidth() height() left().
			 */
			virtual int width(  ) const {
				return pWidth;
			}

			/**
			 * Setter for the width property.
			 *
			 * @param w the new width of this Widget.
			 * @see width().
			 */
			virtual void setWidth( int w );

			/**
			 * Returns the height of the widget.
			 *
			 * @return the height of the widget.
			 * @see setHeight() width() top().
			 */
			virtual int height(  ) const {
				return pHeight;
			}

			/**
			 * Set the height of the widget.
			 *
			 * @param h the height of the widget.
			 * @see height()
			 */
			virtual void setHeight( int h );

			/**
			 * Drawmode of this Widget.
			 *
			 * Drawmode changes the way the widget is drawn. drawTransparent can always be used but is slightly slower than drawOpaque. In drawOpaque mode the bgColor is also drawn behind the widget if no border is assigned while in drawTransparent mode it's not.
			 * @return Drawmode of the widget.
			 * @see Drawmode setDrawmode() border() bgColor().
			 */
			virtual Drawmode drawmode(  ) const;

			/**
			 * Set Drawmode of the widget.
			 *
			 * @param dm Drawmode of the widget.
			 * @see drawmode().
			 */
			virtual void setDrawmode( Drawmode dm );

			/**
			 * The position of the widget in the x axis relative to the whole screen.
			 *
			 * @note This method is recursive and is not very effective, only use it if you have to.
			 * @see absoluteYPos() top() left() width() height().
			 */
			virtual int absoluteXPos( ) const;

			/**
			 * The position of the widget in the y axis relative to the whole screen.
			 *
			 * @note This method is recursive and is not very effective, only use it if you have to.
			 * @see absoluteXPos() top() left() Widget;;width() height()
			 */
			virtual int absoluteYPos( ) const;

			/**
			 * - TO BE REMOVED - Returns a Ui::Rect object containing the visible area on the object.
			 *
			 * @return Ui::Rect object containing the visible area on the object.
			 * @see Ui::Rect.
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
			 * Get the Widget located at the point (x;y).
			 *
			 * @note Widget allways returns this but Ui::Frame can return Widgets inside itself.
			 * @param x the x position relative from Widget.
			 * @param y the x position relative from Widget.
			 * @param recursive determines if the search should be done recursively.
			 * @return the Widget located at the point (x;y).
			 */
			virtual Widget* getWidgetAt( int x, int y, bool recursive = false ) {
				return this;
			}

			/**
			 * Parent that owns and contains this Widget.
			 *
			 * @see hasParent() isManaged() setParent().
			 */
			virtual Frame* parent(  ) const {
				return pParent;
			}

			/**
			 * Setter for the parent property.
			 *
			 * @see parent().
			 */
			virtual void setParent( Frame* p );

			/**
			 * Returns true if this Widget is owned by a parent Ui::Frame.
			 *
			 * @see parent().
			 */
			inline bool hasParent(  ) const {
				return ( pParent != NULL );
			};

			/**
			 * Gives access to associated Ui::Gui object.
			 *
			 * @note If you only want to access the Ui::DrawInterface object, call the interface() function instead.
			 * @todo It should not be possible to create a Widget without an Ui::Gui object attached.
			 * @warning This property should never be NULL.
			 * @return Ui::Gui associated with current object.
			 * @see interface() Ui::Gui
			 */
			virtual Gui& gui(  ) const;

			/**
			 * Setter for the gui property.
			 *
			 * @see gui().
			 */
			virtual void setGui( Gui* s );

			/**
			 * Indicates if this Widget is visible on screen or not.
			 *
			 * @see setVisible().
			 */
			virtual bool visible(  ) const;

			/**
			 * Setter for the visible property.
			 *
			 * @see visible().
			 */
			virtual void setVisible( bool v );

			/**
			 * Indicates if this Widget can receive events.
			 *
			 * @see setEnabled().
			 */
			virtual bool enabled(  ) const {
				return pEnabled;
			}

			/**
			 * Setter for the enabled property.
			 *
			 * @see enabled().
			 */
			virtual void setEnabled( bool e );

			/**
			 * This property can be used by application writer and is not used by GameUI.
			 *
			 * @see setTag().
			 */
			virtual void* tag(  ) const {
				return pTag;
			}

			/**
			 * Setter for the tag property.
			 *
			 * @see tag().
			 */
			virtual void setTag( void* t ) {
				pTag = t;
			};

			/**
			 * The font that will be used when rendering text on this Widget.
			 *
			 * @todo Is this just a waste of a pointer? Some widgets will not use this at all.
			 * @see setFont().
			 */
			virtual Font* font(  ) const {
				return pFont;
			}

			/**
			 * Setter for the font property.
			 *
			 * @see font().
			 */
			virtual void setFont( Font* f );

			/**
			 * The color to be used on text rendered on this widget.
			 *
			 * @todo Should this be removed for the same argument as font().
			 * @see setFontColor().
			 */
			virtual Color fontColor(  ) const {
				return pFontColor;
			}

			/**
			 * Setter for the fontColor property.
			 *
			 * @see fontColor().
			 */
			virtual void setFontColor( Color c ) {
				pFontColor = c;
				updated();
			}

			/**
			 * The color used to draw the background of this Widget if visible.
			 *
			 * @see setBgColor().
			 */
			virtual Color bgColor(  ) const {
				return pBgColor;
			}

			/**
			 * Setter for the bgColor property.
			 *
			 * @see bgColor().
			 */
			virtual void setBgColor( Color c ) {
				pBgColor = c;
				updated();
			}

			/**
			 * The Ui::Border object to use as border for this Widget.
			 *
			 * @see setBorder() Ui::Border.
			 */
			virtual Border* border() const {
				return pBorder;
			};

			/**
			 * Setter for the border property.
			 *
			 * @see border().
			 */
			virtual void setBorder( Border* bs );

			/**
			 * Indicates if this Widget currently is the focused widget to receive key events.
			 *
			 * @see setFocused().
			 */
			virtual bool focused(  ) const {
				return pFocused;
			}

			/**
			 * Setter for the focused property.
			 *
			 * @see focused().
			 */
			virtual void setFocused( bool f );

			/**
			 * The string to show in tooltip.
			 *
			 * @see setTooltip() Ui::Tooltip.
			 */
			virtual wstring tooltip(  ) const {
				return pToolTip;
			}

			/**
			 * Setter for the tooltip property.
			 *
			 * @see tooltip().
			 */
			virtual void setTooltip( wstring t ) {
				pToolTip = t;
			}

			/**
			 * The main render method, this method should be overridden in derived classes to give the widget its own look.
			 *
			 * @see renderBorder().
			 */
			virtual void render( ImageObject& img, const Rect& r );

			/**
			 * This method renders the border and background of this Widget, override if you want the background to be drawn differently.
			 *
			 * @see render() Ui::Border.
			 */
			virtual void renderBorder( ImageObject& img );

			/**
			 * Tells object is updated and needs to call render() to reflect changes.
			 *
			 * @note Doesn't do anything if beginUpdate() is called.
			 * @see beginUpdate() render()
			 */
			virtual void updated(  );
			virtual void updated( const Rect& r );

			virtual void sizeChanged( const Rect& news );

			/**
			 * Halts automatic calls to render() for example when many update operations will be performed in a row. Call endUpdate() when you want the automatic render calls to be performed again.
			 *
			 * This function stacks, if you call beginUpdate() 5 times you have to call endUpdate() 5 times for the automatic render() calls to start again.
			 * @see endUpdate()
			 */
			virtual void beginUpdate(  );

			/**
			 * Resumes automatic render() calls.
			 *
			 * Calls render() when beginUpdate() and endUpdate() has been called the same number of times.
			 * @note Make sure you call beginUpdate() and endUpdate() the same number of times, otherwise automatic render() will stop working completly.
			 * @see beginUpdate()
			 */
			virtual void endUpdate( bool dontupdate = false );

			/**
			 * Set the limits in which the object's size can vary.
			 *
			 * @param minw minimum width.
			 * @param minh minimum height.
			 * @param maxw maximum width.
			 * @param maxh maximum height.
			 */
			virtual void setSizeLimit( int minw, int minh, int maxw, int maxh );
			virtual void setBounds( int left, int top, int width, int height );
			virtual void move( const int newleft, const int newtop );

			/**
			 * Is this Widget managed by a Ui::Frame parent?
			 *
			 * @return true if this Widget's constraints is managed by a parent.
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
			 *
			 * @param newwidth the new width.
			 * @param newheight the new height.
			 * @see setBounds() setSizeLimit() width() height() move()
			 */
			virtual void resize( int newwidth, int newheight );
			virtual void timerTick();

			/**
			 * Returns the Z-index of this Widget, this is the order in which the Widget will be drawn on it's parent Ui::Frame.
			 *
			 * @see setZIndex()
			 */
			virtual int zIndex( );

			/**
			 * Sets the Z-index of this Widget, this is the order in which the Widget will be drawn on it's parent Ui::Frame.
			 *
			 * @see setZIndex() Ui::Frame::setZIndex()
			 */
			virtual int setZIndex( const int z );

			/**
			 * Assign the highest possible Z-index to this Widget.
			 *
			 * @see moveToBottom()
			 */
			virtual void moveToTop();

			/**
			 * Assign the lowest possible Z-index to this Widget.
			 *
			 * @see moveToTop()
			 */
			virtual void moveToBottom();

			/**
			 * Gives access to the Ui::DrawInterface object associated with current Ui::Gui object in use.
			 *
			 * @warning this function can return NULL.
			 * @return Ui::DrawInterface object associated with current Ui::Screen object in use.
			 * @see screen() Ui::DrawInterface Ui::Gui
			 */
			virtual ImageObject& screen(  );


			/** @name Static methods */
			//@{

			/**
			 * Adds a Widget to the update queue.
			 */
			static void updatedWidget( Widget* o, const Rect r = NULL_RECT );

			/**
			 * Clears the widget update queue.
			 */
			static void clearUpdatedWidgets();

			/**
			 * Returns the widget update queue, containing all widgets that have been updated since last call to clearUpdateWidgets().
			 *
			 * @see clearUpdatedWidgets()
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

			WidgetAlign pAlign;

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
			 *
			 * @see releaseMouseInput()
			 */
			void grabMouseInput();

			/**
			 * Makes the Ui::Screen object stop channeling all mouse events to this object.
			 *
			 * @see grabMouseInput()
			 */
			void releaseMouseInput();

	};

}

#endif
