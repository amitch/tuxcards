/***************************************************************************
                          informationformat.cpp  -  mDescription
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

#include "informationformat.h"

#include "format_none.xpm"
#include "format_ascii.xpm"
#include "format_rtf.xpm"
//Added by qt3to4:
#include <QPixmap>

/*const*/ InformationFormat InformationFormat::NONE("NONE", QImage(format_none_xpm));
/*const*/ InformationFormat InformationFormat::ASCII("ASCII", QImage(format_ascii_xpm));
/*const*/ InformationFormat InformationFormat::RTF("RTF", QImage(format_rtf_xpm));


// -------------------------------------------------------------------------------
InformationFormat::InformationFormat(QString description, QImage image)
 : mDescription( description )
 , mImage( image )
// -------------------------------------------------------------------------------
{
}


/**
 * Two InformationFormats are equal if the mDescription is equal.
 */
// -------------------------------------------------------------------------------
bool InformationFormat::equals( InformationFormat anotherFormat )
// -------------------------------------------------------------------------------
{
   return ( toString()==anotherFormat.toString() );
}


// -------------------------------------------------------------------------------
InformationFormat* InformationFormat::canbeConvertedTo( void )
// -------------------------------------------------------------------------------
{
   // needs to be implemented
   return this;
}


// -------------------------------------------------------------------------------
QPixmap InformationFormat::getPixmap( void )
// -------------------------------------------------------------------------------
{
   QPixmap pixmap;
   pixmap.convertFromImage( mImage, Qt::AutoColor );
   return pixmap;
}


// -------------------------------------------------------------------------------
QString InformationFormat::toString( void )
// -------------------------------------------------------------------------------
{
   return mDescription;
}



/**
 * Returns a format that was parsed from the string 'format'; if
 * no informationFormat was recognized -> 'NONE' is returned.
 */
// -------------------------------------------------------------------------------
InformationFormat* InformationFormat::getByString( QString format )
// -------------------------------------------------------------------------------
{
  if (format == "RTF")
    return &RTF;
  else if (format == "ASCII")
    return &ASCII;
  else
    return &NONE;
}
