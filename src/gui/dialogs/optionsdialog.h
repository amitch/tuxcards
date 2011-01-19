/***************************************************************************
                          optionsdialog.h  -  description
                             -------------------
    begin                : Thu Mar 30 2000
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

#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include "ui_IOptionsDialog.h"
#include <qtabbar.h>

#include <q3hbox.h>
#include <q3vbox.h>
#include <q3grid.h>
#include <qcheckbox.h>

#include <qlabel.h>
#include <qlineedit.h>
#include <qvalidator.h>

#include <qpushbutton.h>
#include <qcolordialog.h>
#include <qstring.h>
#include <qfont.h>

#include "../../CTuxCardsConfiguration.h"

#include <iostream>
class OptionsDialog : public QDialog, public Ui_IOptionsDialog {
   Q_OBJECT
public:
   OptionsDialog(QWidget* parent, CTuxCardsConfiguration& config);
   int setUp( void );

   bool getAutosave();
   int  getMinutes();
   bool getSaveWhenLeaving();
   bool getCreateBackup();

   QFont   getTreeFont();
   QFont   getEditorFont();
   int     getTabSize();
   int     getWordWrap();

protected slots:
   virtual void changeTreeFont();
   virtual void changeEditFont();

   virtual void changeProperties();

signals:
  void configurationChanged();

private:
  CTuxCardsConfiguration& mrefConfig;
};

#endif

