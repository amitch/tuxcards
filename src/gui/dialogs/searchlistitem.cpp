/***************************************************************************
                          searlistitem.cpp  -  description
                             -------------------
    begin                : Fri Mar 31 2000
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

#include "searchlistitem.h"
#include <qpainter.h>
#include <iostream>

/**
 * 'parent' is a pointer to the QViewList where we want to insert this item
 */
SearchListItem::SearchListItem(Q3ListView *parent, Path* path, int location,
                               int line, int pos, int len, QString s)
	:Q3ListViewItem(parent, parent->lastItem(), path->getPathList().last(), (location == SearchPosition::SP_NAME ? QString("") : s))
{

  searchPosition = new SearchPosition(path, location, line, pos, len, s);
}


SearchPosition* SearchListItem::getSearchPosition()
{
  return searchPosition;
}

void SearchListItem::paintCell(QPainter *p, const QColorGroup &cg,
                               int column, int width, int alignment )
{
  //if (column==1){
  if (searchPosition->getLocation() == column)
  {
    // cache often needed variables
    int pos = searchPosition->getPos();
    int len = searchPosition->getLen();

    p->fillRect (0,0, width,30, Qt::white );

    // draw first part
    QFont f=p->font(); f.setBold(false); QFontMetrics fm(f); p->setFont(f);
    if (pos > 0)
      p->drawText(0,15, text(column).mid(0, pos));
    int x = fm.width(text(column).mid(0, pos));

    // draw 2nd part = "searchPart"
    f.setBold(true);	p->setFont(f);
    p->drawText(x,15, text(column).mid(pos, len));
    x+=fm.width(text(column).mid(pos, len))+1;       // '+1' -> so that it looks nicer

    // draw last part
    f.setBold(false);	p->setFont(f);
    p->drawText(x,15, text(column).mid(pos+len));
  }
  else
  {
    Q3ListViewItem::paintCell( p, cg, column, width, alignment );
  }
}

QString SearchListItem::toString(){
  return text(0)
        +": line="+QString::number(searchPosition->getLine())
        +" pos="+QString::number(searchPosition->getPos());
}

