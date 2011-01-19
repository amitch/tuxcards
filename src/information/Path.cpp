/***************************************************************************
                          Path.cpp  -  description
                             -------------------
    begin                : Fri Jan 09 2002
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

#include "../global.h"
#include "Path.h"
#include <iostream>

QString Path::separator = "//";

// -------------------------------------------------------------------------------
Path::Path( IParent* pElement )
 : mPathList()
// -------------------------------------------------------------------------------
{
   while ( (NULLPTR != pElement)
           && ( INFORMATION_COLLECTION_DESC != pElement->getDescription()) )
   {
      mPathList.prepend( pElement->getDescription() );
      pElement = pElement->getParent();
   }

   //std::cout<<"Path::Path() - "<<toString()<<std::endl;
}



// -------------------------------------------------------------------------------
Path::Path( QString pathString )
// -------------------------------------------------------------------------------
{
   mPathList = QStringList::split(separator, pathString);
}



/**
 * does check for listsize.
 */
// -------------------------------------------------------------------------------
bool Path::isEmpty( void )
// -------------------------------------------------------------------------------
{
   if ( mPathList.size() == 0 )
      return true;

   return false;
}


// -------------------------------------------------------------------------------
QStringList Path::getPathList( void )
// -------------------------------------------------------------------------------
{
   return mPathList;
}


// -------------------------------------------------------------------------------
QString Path::toString( void )
// -------------------------------------------------------------------------------
{
   return mPathList.join(separator);
}
