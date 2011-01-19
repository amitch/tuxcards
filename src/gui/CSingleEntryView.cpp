/***************************************************************************
                          CSingleEntryView.cpp  -  description
                             -------------------
    begin                : Fri Jan 09 2004
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


#include "CSingleEntryView.h"
#include <iostream>

// -------------------------------------------------------------------------------
CSingleEntryView::CSingleEntryView( QWidget* pParent )
  : Q3WidgetStack( pParent )
  , mpActiveElement( NULLPTR )
  , mpEditor( NULLPTR )
// -------------------------------------------------------------------------------
{
   mpEditor = new Editor( this );

   if ( (NULLPTR == mpEditor) )
   {
      std::cout<<"Constructor 'CSingleEntryView': ERROR not enough memory "
               <<" to create objects!!!"<<std::endl;
      return;
   }

   (void)addWidget( mpEditor, EDITOR );
}


// -------------------------------------------------------------------------------
CSingleEntryView::~CSingleEntryView( void )
// -------------------------------------------------------------------------------
{
   mpActiveElement = NULLPTR;
}

// ************** IView *********************************************************
// -------------------------------------------------------------------------------
void CSingleEntryView::aboutToRemoveElement( CInformationElement* pIE )
// -------------------------------------------------------------------------------
{
   if ( mpActiveElement == pIE )
   {
      mpActiveElement = NULLPTR;
   }
   mpEditor->aboutToRemoveElement( pIE );
}
// ************** IView - End ****************************************************


// -------------------------------------------------------------------------------
Editor* CSingleEntryView::getEditor( void )
// -------------------------------------------------------------------------------
{
   return mpEditor;
}


/**
 * This slot is called as soon as the encrypted entry is decrypted.
 */
// -------------------------------------------------------------------------------
void CSingleEntryView::entryDecrypted( void )
// -------------------------------------------------------------------------------
{
   activeInformationElementChanged( mpActiveElement );
}


// -------------------------------------------------------------------------------
QString CSingleEntryView::getText( void )
// -------------------------------------------------------------------------------
{
   return (NULLPTR != mpEditor) ? mpEditor->getText() : QString("");
}

// -------------------------------------------------------------------------------
void CSingleEntryView::setText( QString text )
// -------------------------------------------------------------------------------
{
   if (NULLPTR != mpEditor)
      mpEditor->setText( text );
}


// -------------------------------------------------------------------------------
void CSingleEntryView::writeCurrentTextToActiveInformationElement( void )
// -------------------------------------------------------------------------------
{
   if (NULLPTR != mpEditor)
      mpEditor->writeCurrentTextToActiveInformationElement();
}

// -------------------------------------------------------------------------------
int CSingleEntryView::countBRs( void )
// -------------------------------------------------------------------------------
{
   return (NULLPTR != mpEditor) ? mpEditor->countBRs() : 0;
}

// -------------------------------------------------------------------------------
void CSingleEntryView::activeInformationElementChanged( CInformationElement* pIE )
// -------------------------------------------------------------------------------
{
   if ( (NULLPTR == pIE) || (NULLPTR == mpEditor) )
      return;

   mpActiveElement = pIE;

   mpEditor->activeInformationElementChanged( mpActiveElement );
   raiseWidget( EDITOR );
//   signalEntryDecrypted();
}
