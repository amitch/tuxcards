/***************************************************************************
                          CPasswdDialog.cpp  -  description
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

#include "CFileEncryptionPasswordDialog.h"

#include <qlineedit.h>
#include <qmessagebox.h>
#include <qpushbutton.h>
#include <qlabel.h>

#include <iostream>

// -------------------------------------------------------------------------------
CFileEncryptionPasswordDialog::CFileEncryptionPasswordDialog( QWidget* pParent )
 : QDialog( pParent, "CFileEncryptionPasswordDialog", TRUE )
 , msPasswd( "" )
{
	setupUi(this);
	connect( buttonOk, SIGNAL(clicked()), this, SLOT(accept()) );

}

// -------------------------------------------------------------------------------
void CFileEncryptionPasswordDialog::setUp(QString strFileName)
{
	if (NULLPTR == leFilePassword)
    	return;

	tlFileName->setText(strFileName);
	leFilePassword->setText("");
	msPasswd = "";

	leFilePassword->setFocus();
	show();
	exec();
}



// -------------------------------------------------------------------------------
void CFileEncryptionPasswordDialog::accept()
{
   if ( NULLPTR == leFilePassword)
      return;

   if ( leFilePassword->text().stripWhiteSpace().isEmpty() )
   {
      (void) QMessageBox::warning( this, "TuxCards", "Password field is empty. Please specify a valid password");
      show();
      return;
   }

   msPasswd = leFilePassword->text().stripWhiteSpace();
   close();
}


// -------------------------------------------------------------------------------
QString CFileEncryptionPasswordDialog::getPasswd( void )
{
	return msPasswd;
}
