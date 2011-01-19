/***************************************************************************
                          searchpos.h  -  description
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
#ifndef SEARCHPOSITION_H
#define SEARCHPOSITION_H

#include <qstring.h>
#include <q3listview.h>
#include "../CTreeElement.h"

class SearchPosition {
public:
  SearchPosition(Path* path, int location,
                 int line, int pos, int len, QString s);

  CTreeElement* getReferenceElement();
  Path* getPath();
  int getLine();
  int getPos();
  int getLen();
  QString getName();
  QString getString();

  // states where the string that was searched is found
  enum SP_LOCATION
  {
    SP_NONE = -1,
    SP_NAME,
    SP_INFORMATION
  };

  /*SP_LOCATION*/int getLocation();


private:
  CTreeElement/*QListViewItem*/* referenceElement;     // actually a 'CTreeElement' -> kreuzweise Einbindung d. Headerdateien
  Path* path;
  int searchLocation;                                 // states where the string that was searched is found

  int line;
  int pos;
  int len;
  QString s;

};

#endif






