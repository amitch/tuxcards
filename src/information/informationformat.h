/***************************************************************************
                          informationformat.h  -  description
                             -------------------
    begin                : Sat Jul 13 2002
    copyright            : (C) 2002 by Alexander Theel
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
#ifndef INFORMATION_FORMAT_H
#define INFORMATION_FORMAT_H

#include <iostream>
#include <qstring.h>
#include <qpixmap.h>
#include <qimage.h>

class InformationFormat{
public:
   static /*const*/ InformationFormat NONE;
   static /*const*/ InformationFormat ASCII;
   static /*const*/ InformationFormat RTF;


   InformationFormat( QString, QImage );
   //~InformationFormat();

   bool equals( InformationFormat );

   InformationFormat* canbeConvertedTo( void );

   QPixmap getPixmap( void );
   QString toString( void );

   static InformationFormat* getByString( QString format );

private:
   QString mDescription;
   QImage  mImage;
};

#endif

