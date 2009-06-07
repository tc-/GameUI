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
 * @file
 * Headerfile for the UiList class
 */

#ifndef UILIST_H
#define UILIST_H

#include <gameui.h>
#include <iostream>
#include "assert.h"
#include <stdio.h>
#include <stdlib.h>


using namespace std;

namespace Ui {

/**
 * Template container Class used to store data of various kinds
 */
template<class T>
class List {
public:
  List();
  ~List();
  int allocBy() const;
  void setAllocBy( const int ab);
  int append( T item );
  void insert( T item, int pos );
  void remove( int index );
  void swap( int index1, int index2 );
  T replace( int index, T newItem );
  T get( const int index ) const;
  const int getIndex( const T item ) const;
  int count() const;
  int allocated();
  void allocate( const int numItems );
  void clear();
  void sort( bool (*sortCallback)(List<T>&,int,int) );
private:
  T *p; //!< Array used to store all items
  int pAllocBy; //!< Number of items to preallocate.
  int pCount; //!< Keeps track of how many items there are in the list.
  int pAllocated; //!< Keeps track of how many items are allocated in memory.
  void allocateMem();
  void doSort( bool (*sortCallback)(List<T>&,int,int), int beg, int end );
};


template<class T>
List<T>::List()
{
  pCount = 0;
  pAllocBy = 8;
  p = NULL;
  pAllocated = 0;
}


template<class T>
List<T>::~List()
{
  if ( p != NULL)
    free( p );
  pCount = 0;
  pAllocated = 0;
  p = 0;
}

/**
 * Returns the number of items the list preallocates.
 *
 * This is to improve the speed of the list by minimising the number of allocations beeing made.
 * @return the number of items the list preallocates
 */
 template<class T>
int List<T>::allocBy() const
{
  return pAllocBy;
}


/**
 * Sets the number of items the list preallocates.
 *
 * @note Setting allocBy to 0 will disable memory preallocation.
 * @note Any number below 0 will result in an error.
 * @param ab the number of items the list preallocates.
 * @see allocBy() allocate().
 */
template<class T>
void List<T>::setAllocBy( const int ab)
{
  assert( ab >= 0 );
  pAllocBy = ab;
}


/**
 * Add new item to the bottom of the list. This is the fastest way to add an item.
 *
 * @param item the item to add.
 * @return the index of the new item.
 * @see insert().
 */
template<class T>
int List<T>::append( T item )
{
  if ( pCount >= pAllocated )
    allocateMem();
  p[pCount] = item;
  pCount++;
  return pCount - 1;
}


/**
 * Inserts an item in the position indicated by pos.
 *
 * @note if you add an item at pos 0, the whole list will be copied one step up, this can be slow in very large lists.
 * @param item the item to add.
 * @param pos the position to add the item in.
 * @see append().
 */
template<class T>
void List<T>::insert( T item, const int pos )
{
  assert( (pos <= pCount) && (pos >= 0) );

  pCount++;
  if ( pCount >= pAllocated )
    allocateMem();

  for( int i = pCount - 1; i >= pos; i-- ) {
    p[i] = p[i-1];
  }
  p[pos] = item;
}


/**
 * Removes an item.
 *
 * @note if index is -1 the function just returns.
 * @param index the index of the item to remove.
 * @see clear().
 */
template<class T>
void List<T>::remove( const int index )
{
	if ( index == -1 ) return;
  assert( (index < pCount) && (index >= 0) );
  int i;
  for( i = index; i < pCount - 1; i++ ) {
    p[i] = p[i+1];
  }
  pCount--;
  if ( pAllocated > pCount + (pAllocBy * 2))
    allocateMem();
}


/**
 * Replaces an Item in the list with a new Item.
 *
 * @param index the index of the old item to replace.
 * @param newItem the new Item to insert.
 * @return the old Item.
 * @see delete() insert().
 */
template<class T>
T List<T>::replace( int index, T newItem )
{
  assert( (index < pCount) && (index >= 0) );
  T oldItem = p[index];
  p[index] = newItem;
  return oldItem;
}


/**
 * Lets two Items exchange placement in the list.
 *
 * @see replace().
 */
template<class T>
void List<T>::swap( int index1, int index2 )
{
  assert( (index1 < pCount) && (index1 >= 0) );
  assert( (index2 < pCount) && (index2 >= 0) );

  T tmp = p[index1];
  p[index1] = p[index2];
  p[index2] = tmp;
}


/**
 * The item indicated by index.
 *
 * @param index index of the item to return.
 * @see getIndex().
 */
template<class T>
T List<T>::get( const int index ) const
{
  assert( index < pCount );
  return p[ index ];
}



/**
 * The index of an item.
 *
 * @param item the item to find.
 * @return index to item or -1 if not found.
 * @see get().
 */
template<class T>
const int List<T>::getIndex( const T item ) const
{
  int i;
  for ( i=0; i<pCount; i++ ) {
    if ( p[i] == item ) {
      return i;
    }
  }
  return -1;
}


/**
 * The number of items in the list.
 *
 * @see allocated()
 */
template<class T>
int List<T>::count() const
{
  return pCount;
}


/**
 * Preallocates numItems Items for use in the list.
 *
 * This can be used when you know how many items you will need in the list. If you set allocBy to 0 all preallocations can be done manually.
 * @param numItems the number of items to preallocate.
 * @see allocBy().
 */
template<class T>
void List<T>::allocate( const int numItems )
{
  assert( numItems > 0 );
  if ( p == NULL ) {
    p = ( T* ) malloc( (pCount + numItems) * sizeof( T ) );
  } else {
    p = ( T* ) realloc( p, (pCount + numItems) * sizeof( T ) );
  }
  pAllocated = pCount + numItems;
}


/**
 * Internal function that allocates / reallocates memory used by list.
 *
 * @see allocated().
 */
template<class T>
void List<T>::allocateMem()
{
  if ( p == NULL ) {
    p = ( T* )malloc( (pCount + pAllocBy) * sizeof( T ) );
  } else {
    p = ( T* ) realloc( p, (pCount + pAllocBy) * sizeof( T ) );
  }
  pAllocated = pCount + pAllocBy;
}


/**
 * The number of allocated items.
 *
 * This is not allways the same number as the number of items in the list given by count(). The list preallocates items when needed to optimize memory allocations.
 * @see count() allocateMem().
 */
template<class T>
int List<T>::allocated()
{
  return pAllocated;
}


/**
 * Removes all items from the list.
 *
 * You could do this with a loop using remove(), but clear() is faster.
 * @see remove().
 */
template<class T>
void List<T>::clear()
{
  pCount = 0;
  if ( p != NULL )
    free( p );
  p = NULL;
  pAllocated = 0;
}


/**
 * Sorts the list with the help of a callback function.
 *
 * The callback function should return true if first int is below or equal to second int and false if first int is above the second int.
 * @param sortCallback pointer to the callback function that should be used.
 * @see doSort().
 */
template<class T>
void List<T>::sort( bool (*sortCallback)(List<T>&,int,int) )
{
  assert( sortCallback != NULL );
  int i, j;
  for ( i = pCount - 1; i >= 0; i-- ) {
    for ( j = 0; j < pCount - 1; j++ ) {
      if ( sortCallback(*this, j, j+1 ) )
        swap(j, j+1);
    }
  }
//  doSort( sortCallback, 0, count() - 1 );
}


/**
 * Internal function used for sorting the list.
 *
 * @see sort().
 */
template<class T>
void List<T>::doSort( bool (*sortCallback)(List<T>&,int,int), int beg, int end )
{
  if (end > beg + 1)
  {
    int piv = beg, l = beg + 1, r = end;
    while (l != r-1)
    {
      if( sortCallback(*this, l, piv) )
        l++;
      else
        swap( l, r-- );
    }
    if( sortCallback(*this, l, piv) && sortCallback(*this, r, piv) )
      l=r+1;
    else if( sortCallback(*this, l, piv) && sortCallback(*this, piv, r) )
    {l++; r--;}
    else if ( sortCallback(*this, piv, l) && sortCallback(*this, r, piv))
      swap(l++, r--);
    else
      r=l-1;

    swap( r--, beg );
    doSort( sortCallback, beg, r );
    doSort( sortCallback, l, end );
  }
}

}

#endif
