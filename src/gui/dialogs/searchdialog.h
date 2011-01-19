/***************************************************************************
                          search.h  -  description
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
#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <qdialog.h>
#include <q3hbox.h>
#include <q3vbox.h>
#include <qlabel.h>
#include <qradiobutton.h>
#include <q3buttongroup.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qcheckbox.h>

#include <qstring.h>
#include "searchlistitem.h"

#include "../CTreeElement.h"

class SearchDialog : public QDialog{
  Q_OBJECT
public:
  SearchDialog( QWidget* pParent );

  int          setUp( CTreeElement* rootTreeElement, CTreeElement* activeTreeElement );
  QString      getText( void );
  int          whatMode( void );

public slots:
  virtual void tell( int id );
  virtual void startSearching( void );
  virtual void selectionChange( Q3ListViewItem* x );
  virtual void close( void );

signals:
  void         makeVisible(SearchPosition*);
  //void makeVisible(TreeElement*, int, int, int);
    
private:
  QLineEdit*    edit;
  int           choice;
  CTreeElement* rootTreeElement;
  CTreeElement* activeTreeElement;
  QLabel*       status;
  QCheckBox*    caseSensitive;
  QCheckBox*    searchTitles;

  Q3ListView*   list;

};

#endif
