/***************************************************************************
                          CPropertyDialog.h  -  description
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

#ifndef C_PROPERTY_DIALOG_H
#define C_PROPERTY_DIALOG_H

#include "ui_IPropertyDialog.h"

#include "iconselectordialog.h"
//Added by qt3to4:
#include <QPixmap>
class CInformationElement;
class CTuxCardsConfiguration;

#include <q3datetimeedit.h>


class CPropertyDialog : public QDialog, public Ui_IPropertyDialog {
   Q_OBJECT
public:
   CPropertyDialog( QWidget* pParent, CTuxCardsConfiguration& refTuxConfiguration );
   ~CPropertyDialog( void );

   void    setUp( CInformationElement* pElement, int iMode );

   QString getName( void );
   QString getIconFileName( void );

   enum {
      MODE_NONE,
      MODE_CHANGE_PROPERTIES,
      MODE_CREATE_NEW_ELEMENT
   };

private slots:
   void chooseIcon( void );
   void changeProperties( void );

private:
   QPixmap             mBlankIcon;
   IconSelectorDialog  mIconSelector;

   //#define DEFAULT_DURATION 1

   void   setAttributes( QString, QString);
   int    miMode;
   int    miChoice;

   CInformationElement* mpEditingElement;


   CTuxCardsConfiguration& mrefTuxConfiguration;
};

#endif
