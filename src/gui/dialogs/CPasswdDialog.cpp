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

#include "CPasswdDialog.h"

#include <qlineedit.h>
#include <qlabel.h>
#include <qmessagebox.h>
#include <qpushbutton.h>

#include <iostream>

// -------------------------------------------------------------------------------
CPasswdDialog::CPasswdDialog( QWidget* pParent )
 : QDialog( pParent, "CPasswdDialog", TRUE )
 , msPasswd( "" )
// -------------------------------------------------------------------------------
{
	setupUi(this);
}

// -------------------------------------------------------------------------------
void CPasswdDialog::setUp( const QString& sIEDescription )
// -------------------------------------------------------------------------------
{
   if ( (NULLPTR == mpIEDescription) || (NULLPTR == mpPasswdLineOne)
        || (NULLPTR == mpPasswdLineTwo) )
      return;

   mpIEDescription->setText("'"+sIEDescription+"'");
   mpPasswdLineOne->setText("");
   mpPasswdLineTwo->setText("");
   msPasswd = "";

   mpPasswdLineOne->setFocus();
   show();
   exec();
}



// -------------------------------------------------------------------------------
void CPasswdDialog::done()
// -------------------------------------------------------------------------------
{
   if ( (NULLPTR == mpPasswdLineOne) || (NULLPTR == mpPasswdLineTwo) )
      return;

   if ( mpPasswdLineOne->text().stripWhiteSpace().isEmpty() )
   {
      (void) QMessageBox::warning( this, "TuxCards", "Password field is empty. Please specify a valid password",
                                         "Ok" );
      //std::cout<<"no passwd"<<std::endl;
      show();
      return;
   }

   if ( 0 != mpPasswdLineOne->text().stripWhiteSpace().compare(
                        mpPasswdLineTwo->text().stripWhiteSpace())
      )
   {
      (void) QMessageBox::warning( this, "TuxCards", "Passwords did not match. Please try again",
                                         "Ok" );
      mpPasswdLineOne->setText("");
      mpPasswdLineTwo->setText("");

      mpPasswdLineOne->setFocus();
      show();
      return;
   }
   msPasswd = mpPasswdLineOne->text().stripWhiteSpace();
   close();
}



// -------------------------------------------------------------------------------
QString CPasswdDialog::getPasswd( void )
// -------------------------------------------------------------------------------
{ return msPasswd; }
