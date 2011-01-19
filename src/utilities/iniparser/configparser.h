/***************************************************************************
                          configparser.h  -  description
                             -------------------
    begin                : Fri Apr 28 2000
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

#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <qstring.h>
#include <q3ptrlist.h>
#include "configgroup.h"
#include <qfile.h>
#include <q3textstream.h>

class ConfigParser {
public: 
   ConfigParser(QString fileName, bool writeAtOnce);
   ~ConfigParser();

   bool correct();
   void setGroup(QString);
   QString getCurrentGroup();
   QString readEntry(QString, QString);
   int readNumEntry(QString, int);
   void changeEntry(QString, QString);
   void changeEntry(QString, int);
   void writeChanges();

   QString toString();

protected:
   Q3PtrList<ConfigGroup>* list;
   bool ready;
   ConfigGroup* currentGroup;

   QString fileName;
   bool writeAtOnce;                           // if it is =true, all changes are written to the file,
                                               //    immediatly -> if =false -> 'writeChanges()' must
                                               // be called, otherwise the changes are not saved
};

#endif
