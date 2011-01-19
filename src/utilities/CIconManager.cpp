/***************************************************************************
                          CIconManager.cpp  -  description
                             -------------------
    begin                : Tue May 01 2004
    copyright            : (C) 2004 by Alexander Theel
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

#include "CIconManager.h"
#include "../global.h"
#include <qfile.h>
//Added by qt3to4:
#include <QPixmap>
#include <iostream>

#include "../icons/fileopen.xpm"
#include "../icons/filenew.xpm"
#include "../icons/filesave.xpm"
#include "../icons/fileprint.xpm"
#include "../icons/exit.xpm"
#include "../icons/addTreeElement.xpm"
#include "../icons/changeProperty.xpm"
#include "../icons/delete.xpm"
#include "../icons/lock.xpm"
#include "../icons/unlock.xpm"
#include "../icons/find.xpm"

#include "../icons/redo.xpm"
#include "../icons/undo.xpm"
#include "../icons/editcut.xpm"
#include "../icons/editcopy.xpm"
#include "../icons/editpaste.xpm"
#include "../icons/editentrycolor.xpm"
#include "../icons/editentrysubtreecolor.xpm"

#include "../icons/text_bold.xpm"
#include "../icons/text_italic.xpm"
#include "../icons/text_under.xpm"
#include "../icons/text_color.xpm"
#include "../icons/text_left.xpm"
#include "../icons/text_center.xpm"
#include "../icons/text_right.xpm"
#include "../icons/text_block.xpm"

#include "../icons/upArrow.xpm"
#include "../icons/downArrow.xpm"
#include "../icons/back.xpm"            // leftArrow
#include "../icons/forward.xpm"         // rightArrow

#include "../icons/locksm.xpm"
#include "../icons/unlocksm.xpm"
#include "../icons/filelock.xpm"
#include "../icons/fileunlock.xpm"

// -------------------------------------------------------------------------------
CIconManager::CIconManager()
// -------------------------------------------------------------------------------
  : mDefaultIconMap()
  , mAlternativeIconMap()
  , msIconDirectory()
  , mFileEndingList()
{
   buildupDefaultIconMap();
   buildupListWithPossibleFileEndings();
}


// -------------------------------------------------------------------------------
CIconManager& CIconManager::getInstance()
// -------------------------------------------------------------------------------
{
   static CIconManager instance;
   return instance;
}


// -------------------------------------------------------------------------------
void CIconManager::buildupDefaultIconMap()
// -------------------------------------------------------------------------------
{
   mDefaultIconMap["fileopen"]       = QPixmap(fileopen_xpm);
   mDefaultIconMap["filenew"]        = QPixmap(filenew_xpm);
   mDefaultIconMap["filesave"]       = QPixmap(filesave_xpm);
   mDefaultIconMap["fileprint"]      = QPixmap(fileprint_xpm);
   mDefaultIconMap["exit"]           = QPixmap(exit_xpm);
   mDefaultIconMap["addTreeElement"] = QPixmap(addTreeElement_xpm);
   mDefaultIconMap["changeProperty"] = QPixmap(changeProperty_xpm);
   mDefaultIconMap["delete"]         = QPixmap(delete_xpm);
   mDefaultIconMap["lock"]           = QPixmap(lock_xpm);
   mDefaultIconMap["unlock"]         = QPixmap(unlock_xpm);
   mDefaultIconMap["find"]           = QPixmap(find_xpm);

   mDefaultIconMap["redo"]           = QPixmap(redo_xpm);
   mDefaultIconMap["undo"]           = QPixmap(undo_xpm);
   mDefaultIconMap["editcut"]        = QPixmap(editcut_xpm);
   mDefaultIconMap["editcopy"]       = QPixmap(editcopy_xpm);
   mDefaultIconMap["editpaste"]      = QPixmap(editpaste_xpm);
   mDefaultIconMap["editentrycolor"]       = QPixmap(editentrycolor_xpm);
   mDefaultIconMap["editentrysubtreecolor"]      = QPixmap(editentrysubtreecolor_xpm);

   mDefaultIconMap["text_bold"]      = QPixmap(text_bold_xpm);
   mDefaultIconMap["text_italic"]    = QPixmap(text_italic_xpm);
   mDefaultIconMap["text_under"]     = QPixmap(text_under_xpm);
   mDefaultIconMap["text_color"]     = QPixmap(text_color_xpm);
   mDefaultIconMap["text_left"]      = QPixmap(text_left_xpm);
   mDefaultIconMap["text_center"]    = QPixmap(text_center_xpm);
   mDefaultIconMap["text_right"]     = QPixmap(text_right_xpm);
   mDefaultIconMap["text_block"]     = QPixmap(text_block_xpm);

   mDefaultIconMap["upArrow"]        = QPixmap(upArrow_xpm);
   mDefaultIconMap["downArrow"]      = QPixmap(downArrow_xpm);
   mDefaultIconMap["back"]           = QPixmap(back_xpm);
   mDefaultIconMap["forward"]        = QPixmap(forward_xpm);

   mDefaultIconMap["locksm"]           = QPixmap(locksm_xpm);
   mDefaultIconMap["unlocksm"]         = QPixmap(unlocksm_xpm);
   mDefaultIconMap["filelock"]           = QPixmap(filelock_xpm);
   mDefaultIconMap["fileunlock"]         = QPixmap(fileunlock_xpm);
}


// -------------------------------------------------------------------------------
void CIconManager::buildupListWithPossibleFileEndings()
// -------------------------------------------------------------------------------
{
   mFileEndingList.append(".xpm");
   mFileEndingList.append(".png");
   mFileEndingList.append(".gif");
   mFileEndingList.append(".jpg");
   mFileEndingList.append(".bmp");
   mFileEndingList.append(".xbm");
   mFileEndingList.append(".pnm");
   mFileEndingList.append(".mng");
   mFileEndingList.append(".jpeg");
}


// -------------------------------------------------------------------------------
// Sets the directory where to get the icons from.
// -------------------------------------------------------------------------------
void CIconManager::setIconDirectory( const QString& sDir )
// -------------------------------------------------------------------------------
{
   msIconDirectory = sDir;
}


// -------------------------------------------------------------------------------
QString CIconManager::testExistenceOfFile( const QString& sFileName ) const
// -------------------------------------------------------------------------------
{
   for ( uint i = 0; i < mFileEndingList.size(); i++ )
   {
      if( QFile(sFileName + mFileEndingList[i]).exists() )
      {
         return sFileName + mFileEndingList[i];
      }
   }

   return "";
}

// -------------------------------------------------------------------------------
const QPixmap& CIconManager::getIcon( const QString& sFileName )
// -------------------------------------------------------------------------------
{
   // If an icon is already loaded, return that one.
   if ( !mAlternativeIconMap[sFileName].isNull() )
   {
      return mAlternativeIconMap[sFileName];
   }

   // Otherwise, look whether a valid file for the icons does exist.
   QString sResult = testExistenceOfFile( msIconDirectory + "/" + sFileName );
   if ( !sResult.isEmpty() )
   {
      mAlternativeIconMap[sFileName] = QPixmap(sResult);
      return mAlternativeIconMap[sFileName];
   }

   // return default icon
   return mDefaultIconMap[sFileName];
}
