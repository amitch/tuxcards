/***************************************************************************
                          searchpos.cpp  -  description
                             -------------------
    begin                : Sun Mar 26 2000
    copyright            : (C) 2000 by Alexander Theel
    email                : alex.theel@gmx.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include "searchposition.h"

/* 'CTreeElement' should be used instead of 'QListViewItem' in future
 * 'x' is actually a 'CTreeElement', the 'CTreeElement' where we have found s.th.
 * 'line': the textline
 * 'pos':  the position in 'line'
 * 'len':  length of searchString; needed to draw this item (especially for
 *         regular expressions)
 */
SearchPosition::SearchPosition(Path/*CTreeElement*//*QListViewItem*/* path, int location,
                               int line, int pos, int len,
                               QString s)
{
  //referenceElement = x;
  this->path     = path;
  this->searchLocation = location;
  this->line     = line;
  this->pos      = pos;
  this->len      = len;
  this->s        = s;
}


CTreeElement* SearchPosition::getReferenceElement()
{
  return referenceElement;
}

Path* SearchPosition::getPath()
{
  return path;
}

int SearchPosition::getLine(){ return line; }
int SearchPosition::getPos(){ return pos; }
int SearchPosition::getLen(){ return len; }

// really dirty, calling x->text(0), althought we are using 'Knoten'
// -> da kreuzweise verschachtelung der Headerfiles 'knoten.h' & 'searchpos.h'
QString SearchPosition::getName(){ return referenceElement->text(0); }
QString SearchPosition::getString(){ return s; }


/*SP_LOCATION SearchPosition::getLocation()*/
int SearchPosition::getLocation()
{
  return searchLocation;
}
