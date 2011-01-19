/***************************************************************************
                          RecentFileList.cpp  -  description
                             -------------------
    begin                : Sun Feb 09 2003
    copyright            : (C) 2003 by Alexander Theel
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

#include "RecentFileList.h"
#include <iostream>
#include <qstringlist.h>
#include <qfile.h>
#include <qmessagebox.h>

#include <qobject.h>
#include <q3ptrlist.h>
//Added by qt3to4:
#include <Q3PopupMenu>

QString RecentFileList::separator = ",";
uint RecentFileList::MAX_ELEMENT_COUNT = 5;

/**
 * Constructor
 */
// -------------------------------------------------------------------------------
RecentFileList::RecentFileList(QWidget* parent, Q3PopupMenu* parentMenu, QString files)
 : QObject()
// -------------------------------------------------------------------------------
{
  this->parent = parent;
  this->menu   = parentMenu;
  recentFileGroup = 0;
  recentlyFilesMenu = new Q3PopupMenu( parent );
  parentMenu->insertItem( "Recently Used Files", recentlyFilesMenu );

  connect( recentlyFilesMenu, SIGNAL( activated( int ) ),
           this, SLOT( slotRecenlyOpenedFilesActivated( int ) ) );

  setList(files);
  update();
}



/**
 * Sets the given string on top of the list. If the string
 * is already within the list, it is moved to the first position.S
 */
// -------------------------------------------------------------------------------
void RecentFileList::setOnTop(QString absPath)
// -------------------------------------------------------------------------------
{
  remove(absPath);
  fileList.prepend(absPath);

  update();
}




/**
 * Updates the corresponding recent file list.
 *
 */
// -------------------------------------------------------------------------------
void RecentFileList::setList(QString files)
// -------------------------------------------------------------------------------
{
  if ( files.isEmpty() )
  {
  //  files = "test 1,test 2,ende";
  }

  fileList = QStringList::split(separator, files);
}



// -------------------------------------------------------------------------------
void RecentFileList::update()
// -------------------------------------------------------------------------------
{
  //checkSize();
  updateMenu();
}



/**
 * Makes sure that the file list is limited to MAX_ELEMENT_COUNT.
 * Any additional elements will be removed from the list.
 *
 */
// -------------------------------------------------------------------------------
void RecentFileList::checkSize()
// -------------------------------------------------------------------------------
{
  QString tmp;
  while (fileList.count() > MAX_ELEMENT_COUNT)
  {
    tmp = fileList.last();
    fileList.remove( tmp );
  }
}





/**
 * Updates the corresponding recent menu.
 *
 */
// -------------------------------------------------------------------------------
void RecentFileList::updateMenu()
// -------------------------------------------------------------------------------
{
   recentlyFilesMenu->clear();

   int id = 0;
   for (uint i=0; i < fileList.count(); i++)
   {
     recentlyFilesMenu->insertItem( fileList[i], id );
     id++;
   }
}


// -------------------------------------------------------------------------------
void RecentFileList::slotRecenlyOpenedFilesActivated( int id )
// -------------------------------------------------------------------------------
{
   if ( id == -1 )
      return;

   QString fileName = fileList[id];

   if ( QFile::exists(fileName) )
   {
      emit openFile(fileName);
      // File will be set on top when the file is actually opened.
   }
   else
   {
      if (QMessageBox::Yes == QMessageBox::warning(parent, "File not found",
                      "The file '"+fileName+"' does not exist.\n"
                      "Do you want to remove it from the recent file menu?",
                      QMessageBox::Yes, QMessageBox::No))
      {
         remove(fileName);
         update();
      }
   }
}


/**
 * Removes the specified file from the list and updates the
 * recent file menu.
 */
// -------------------------------------------------------------------------------
void RecentFileList::remove(QString absPath)
// -------------------------------------------------------------------------------
{
  if ( fileList.contains( absPath ) )
  {
    fileList.remove(absPath);
    //std::cout<<" file removed; new list = "<<toString()<<std::endl;
  }
}




// -------------------------------------------------------------------------------
QString RecentFileList::toString()
// -------------------------------------------------------------------------------
{
  return fileList.join(separator);
}

