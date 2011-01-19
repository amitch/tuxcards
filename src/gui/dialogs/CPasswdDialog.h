/***************************************************************************
                          CPasswdDialog.h  -  description
                             -------------------
    begin                : Wed Jan 14 2004
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
#ifndef CPASSWDDIALOG_H
#define CPASSWDDIALOG_H

#include "../../global.h"
#include "ui_IPasswdDialog.h"
#include <qstring.h>


class CPasswdDialog : public QDialog, public Ui_IPasswdDialog {
  Q_OBJECT
public:
  CPasswdDialog( QWidget* pParent = NULLPTR );

  void    setUp( const QString& sIEDescription );
  QString getPasswd( void );

protected slots:
   virtual void   done( );

private:
   QString msPasswd;
};

#endif
