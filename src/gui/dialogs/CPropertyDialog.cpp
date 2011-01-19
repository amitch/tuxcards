/***************************************************************************
                          CPropertyDialog.cpp  -  description
                             -------------------
    begin                : Tue Mar 28 2000
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
#include "../../icons/blank.xpm"


#include "CPropertyDialog.h"
#include "../../global.h"

#include "../../information/CTreeInformationElement.h"
#include "../../CTuxCardsConfiguration.h"

#include <qmessagebox.h>
#include <qradiobutton.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
//Added by qt3to4:
#include <QPixmap>


// -------------------------------------------------------------------------------
CPropertyDialog::CPropertyDialog( QWidget* pParent,
                                  CTuxCardsConfiguration& refTuxConfiguration )
 : QDialog( pParent, "CPropertyDialog", TRUE )
 , mBlankIcon( blank_xpm )
 , mIconSelector()
 , miMode( MODE_NONE )
 , miChoice( 0 )
 , mpEditingElement( NULLPTR )
 , mrefTuxConfiguration( refTuxConfiguration )
// -------------------------------------------------------------------------------
{
	setupUi(this);

   connect( mpIconButton, SIGNAL(clicked()), this, SLOT(chooseIcon()) );
   connect( mpButtonApply, SIGNAL(clicked()), this, SLOT(changeProperties()) );
}


// -------------------------------------------------------------------------------
CPropertyDialog::~CPropertyDialog( void )
// -------------------------------------------------------------------------------
{
   mpEditingElement = NULLPTR;                 // do not kill this pointer
}


// -------------------------------------------------------------------------------
void CPropertyDialog::setUp( CInformationElement* pElement, int iMode )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == pElement )
      return;

   if ( iMode == MODE_CHANGE_PROPERTIES )
   {
      setCaption("Change Properties of existing Entry");
      setAttributes( pElement->getDescription(), pElement->getIconFileName());
      mpTextFormatChoser->setEnabled( FALSE );
   }
   else if ( iMode == MODE_CREATE_NEW_ELEMENT )
   {
      setCaption( "Add new Entry" );
      setAttributes( "", "none" );
      mpTextFormatChoser->setEnabled( TRUE );
   }
   else
   {
      return;
   }


   miMode = iMode;
   mpEditingElement = pElement;
   show();

   exec();
}


// -------------------------------------------------------------------------------
void CPropertyDialog::setAttributes( QString sDescription, QString sIconFilename)
// -------------------------------------------------------------------------------
{
   if ( sIconFilename == "none" )
   {
      // entry without icon
      mpNoIconRB->setChecked(true); mpUseIconRB->setChecked(false);
      mpIconButton->setPixmap( mBlankIcon );
   }
   else
   {
      mpIconButton->setPixmap( sIconFilename );
      mpNoIconRB->setChecked(false); mpUseIconRB->setChecked(true);
   }
   mpLocationLabel->setText( sIconFilename );

   mpNameLine->setText(sDescription);
}



/**
 * open a filedialog to let user select his icon
 */
// -------------------------------------------------------------------------------
void CPropertyDialog::chooseIcon( void )
// -------------------------------------------------------------------------------
{
   // getting iconfileName
   if( ! mIconSelector.exec() ) return;
   QString h = mIconSelector.getIconFileName();

   if( h == "" ) return;
   // if 'h' is a valid fileName, test whether it is a valid Pixmap
   QPixmap pix(h);
   if ( ! pix.isNull() )
   {
      mpIconButton->setPixmap(h); mpLocationLabel->setText(h);
   }
}


// -------------------------------------------------------------------------------
QString CPropertyDialog::getName( void )
// -------------------------------------------------------------------------------
{ return mpNameLine->text(); }


// -------------------------------------------------------------------------------
QString CPropertyDialog::getIconFileName( void )
// -------------------------------------------------------------------------------
{
   if ( mpUseIconRB->isChecked() )
      return mpLocationLabel->text();
   else
      return "none";
}


/**
 *  This slot is called when the apply-Button is pressed.
 *  The set attributes are applied to the currently edited informationElement.
 */
// -------------------------------------------------------------------------------
void CPropertyDialog::changeProperties( void )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpEditingElement )
      return;

//   if ( (NULLPTR == mpPasswdLineOne) || (NULLPTR == mpPasswdLineTwo) )
//      return;

   if ( getName().stripWhiteSpace().isEmpty() )
   {
      int iAnswer = QMessageBox::warning( this, "TuxCards", "The name of your note is empty.\n"
                                          "Do you want to change this?",
                                          QMessageBox::Yes, QMessageBox::No );
      if ( QMessageBox::Yes == iAnswer )
      {
         show();
         return;
      }
   }



   if ( miMode == MODE_CHANGE_PROPERTIES )
   {
      // change properties: name & icon
      mpEditingElement->setBatched( TRUE );
      mpEditingElement->setDescription( getName() );
      mpEditingElement->setIconFileName( getIconFileName() );
      mpEditingElement->setBatched( FALSE );
   }
   else if ( miMode == MODE_CREATE_NEW_ELEMENT )
   {
      InformationFormat* pInfoFormat
             = InformationFormat::getByString( mpTextFormatChoser->currentText() );

      CTreeInformationElement* pNewElement = new CTreeInformationElement( mpEditingElement,
                                                             getName(),
                                                             "",
                                                             pInfoFormat,
                                                             getIconFileName());

      mpEditingElement->addChild( pNewElement );
      ((CTreeInformationElement*)mpEditingElement)->setOpen(true);
   }

   close();
}
