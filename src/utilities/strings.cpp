/***************************************************************************
                          strings.cpp  -  description
                             -------------------
    begin                : Fri Jul 19 2002
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

#include "strings.h"
#include <iostream>

#include <qregexp.h>

/**
 * returns a string that has length 'n' and is filled with spaces
 */
// -------------------------------------------------------------------------------
QString Strings::spaces(int n)
// -------------------------------------------------------------------------------
{
  QString result="";
  for (int i=0; i<n; i++)
    result+=" ";

  return result;
}


/**
 * Counts the number of words within the given string and
 * returns it.
 */
// -------------------------------------------------------------------------------
int Strings::wordCount(QString text)
// -------------------------------------------------------------------------------
{
  text = text.simplifyWhiteSpace();

  int words = 0;
  int currentPos = 1;

  while ( (currentPos = text.find(" ", currentPos) +1) > 0 )
  {
    words++;
  }
  words++;
  
  return words;
}


/**
 * Removes the first line from the given string and returns that line.
 * Notice, the given string *is* changed.
 */
// -------------------------------------------------------------------------------
QString Strings::removeAndReturnFirstLine(QString& s)
// -------------------------------------------------------------------------------
{
  int i = s.find("\n");
  if (i < 0 )
    return 0;

  QString retVal = s.left(i);
  s = s.mid(i+1);
  return retVal;
}


/**
 * Removes all html tags within the given string.
 * Any '<br />' will be replaced by a ' ' (Space).
 */
// -------------------------------------------------------------------------------
QString Strings::removeHTMLTags(const QString text)
// -------------------------------------------------------------------------------
{
  QString retVal = text;
  
  retVal.replace(QRegExp("<br />"), " ");

  int tagStart = retVal.find("<");
  int tagEnd = 0;
  while ( tagStart >= 0 )
  {
    tagEnd = retVal.find(">", tagStart);
    retVal = retVal.remove(tagStart, tagEnd-tagStart+1);

    // prepare next turn
    tagStart = retVal.find("<");
  }
  retVal = retVal.mid(1);           // kill first '\n' which
                                    // does not belong to the
                                    // real information text
  // replace existing encoded tags
  retVal.replace(QRegExp("&lt;"), "<");
  retVal.replace(QRegExp("&gt;"), ">");

  //std::cout<<"___"<<retVal<<"___"<<std::endl;
  return retVal;
}
