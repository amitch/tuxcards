/***************************************************************************
                          CTreeElement.h  -  description
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
#ifndef CTREE_ELEMENT_H
#define CTREE_ELEMENT_H

#include <q3listview.h>
#include <qobject.h>
#include <qpainter.h>
#include "../information/CTreeInformationElement.h"
#include "../information/Path.h"


class CTreeElement : public QObject, public Q3ListViewItem{
   Q_OBJECT
public:
  CTreeElement( Q3ListView* pParent, CTreeInformationElement& element );
  CTreeElement( CTreeElement* pParent, CTreeInformationElement& element );
  virtual ~CTreeElement( void );

  void         init( CTreeInformationElement& element );

  CTreeElement* getChildAtPosition( int pos );

  CTreeInformationElement* getInformationElement( void );

  bool         isChildOrSelfSelected( void );

  void         search( QString pattern, bool recursive, bool caseSensitive,
                       bool SearchOnlyTitles, Q3ListView& list );

  CTreeElement* findChildWithName( QString name );

  virtual void paintCell( QPainter *p, const QColorGroup &cg,
			    int column, int width, int alignment );

public slots:
  // slot which is called from a "mediator"
  void         propertyChangeEvent( void );
  void         childAddEvent( CInformationElement* pChild );
  void         childMovedEvent( int oldPos, int newPos );

protected:
  CTreeElement* getLastChild( void );

private:
  CTreeInformationElement* mpInformationElement;

  void         copyPropertiesFromInformationElement( void );
};

#endif
