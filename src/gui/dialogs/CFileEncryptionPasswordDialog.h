/***************************************************************************
                          CFileEncryptionPasswordDialog.h  -  description
                             -------------------
    begin                : Thu May 25 2006
    copyright            : (C) 2006 by Amit D. Chaudhary
    email                : amitch@rajgad.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef CFILEENCRYPTIONPASSWORDDIALOG_H
#define CFILEENCRYPTIONPASSWORDDIALOG_H

#include "../../global.h"
#include "ui_IFileEncryptionPasswordDialog.h"
#include <qstring.h>


class CFileEncryptionPasswordDialog :  public QDialog, public Ui_IFileEncryptionPasswordDialog {
  Q_OBJECT
public:
  CFileEncryptionPasswordDialog( QWidget* pParent = NULLPTR );

  void    setUp(QString strFileName);
  QString getPasswd( void );

protected slots:
   virtual void   accept( );

private:
   QString msPasswd;
};

#endif // CFILEENCRYPTIONPASSWORDDIALOG_H
