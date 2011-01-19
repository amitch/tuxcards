/***************************************************************************
                          optionsdialog.cpp  -  description
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

#include "optionsdialog.h"
#include <qradiobutton.h>
#include <qfontdialog.h>
#include <q3filedialog.h>
#include <iostream>

OptionsDialog::OptionsDialog( QWidget* parent, CTuxCardsConfiguration& config )
 : QDialog( parent, "OptionsDialog", TRUE )
 , mrefConfig( config )
{
	setupUi(this);
  connect( mpOkButton, SIGNAL(clicked()), this, SLOT(changeProperties()) );
}


int OptionsDialog::setUp( void )
{
   autosave       ->setChecked(mrefConfig.getBoolValue( CTuxCardsConfiguration::B_AUTOSAVE ));
   saveMinutes    ->setText(QString::number(mrefConfig.getIntValue( CTuxCardsConfiguration::I_SAVE_ALL_MINUTES )));
   saveWhenLeaving->setChecked(mrefConfig.getBoolValue( CTuxCardsConfiguration::B_SAVE_WHEN_LEAVING ));
   createBackup   ->setChecked(mrefConfig.getBoolValue( CTuxCardsConfiguration::B_CREATE_BACKUP_FILE ));
   pCommandLine   ->setText( mrefConfig.getStringValue( CTuxCardsConfiguration::S_EXECUTE_STATEMENT ));
   mpIconDirecory ->setText( mrefConfig.getStringValue( CTuxCardsConfiguration::S_ICON_DIR ));

   treeFontText  ->setFont(mrefConfig.getTreeFont().toFont());
   treeFontText  ->setText(mrefConfig.getTreeFont().toFont().rawName().section(':', 0,0));
   editorFontText->setFont(mrefConfig.getASCIIEditorFont().toFont());
   editorFontText->setText(mrefConfig.getASCIIEditorFont().toFont().rawName().section(':', 0,0));

   tabSize->setText(QString::number(mrefConfig.getIntValue( CTuxCardsConfiguration::I_TAB_SIZE )));

   // 'wordwrap' is a non-negative number; 0 means noWrap, 1 means widgetWrap,
   //   'wordwrap' >1 mean wrap at column 'wordwrap'
   int iWordWrap = mrefConfig.getIntValue( CTuxCardsConfiguration::I_WORD_WRAP );
   switch ( iWordWrap )
   {
   case 0:
      noWrap->setChecked( true );
      break;

   case 1:
      widgetWrap->setChecked( true );
      break;

   default:
      columnWrap->setChecked( true );
      wrapColumn->setText( QString::number(iWordWrap) );
      break;
   };

   show();
   return exec();
}

/**
 * This method is called whenever the ok-button is pressed.
 * Then all changes are set with the configuratio-object. The mainwindow
 * is also informed about the clicking of the ok-button and adjusts
 * own things.
 */
void OptionsDialog::changeProperties(){
 	mrefConfig.setBoolValue(   CTuxCardsConfiguration::B_AUTOSAVE,          getAutosave() );
 	mrefConfig.setIntValue(    CTuxCardsConfiguration::I_SAVE_ALL_MINUTES,  getMinutes());
 	mrefConfig.setBoolValue(   CTuxCardsConfiguration::B_SAVE_WHEN_LEAVING, getSaveWhenLeaving() );
 	mrefConfig.setBoolValue(   CTuxCardsConfiguration::B_CREATE_BACKUP_FILE,getCreateBackup() );
   mrefConfig.setStringValue( CTuxCardsConfiguration::S_EXECUTE_STATEMENT, pCommandLine->text() );
   mrefConfig.setStringValue( CTuxCardsConfiguration::S_ICON_DIR,          mpIconDirecory->text() );

   // editor-font
   QFont f                 = getEditorFont();
   QString FONT_FAMILY     =f.family();
   int     FONT_SIZE       =f.pointSize();
   bool    FONT_BOLD	      =f.bold();
   bool    FONT_ITALIC     =f.italic();
   bool    FONT_UNDERLINE  =f.underline();
   bool    FONT_STRIKEOUT  =f.strikeOut();
   FontSettings fontSettingsEditor( FONT_FAMILY, FONT_SIZE, FONT_BOLD, FONT_ITALIC, FONT_UNDERLINE, FONT_STRIKEOUT );
   mrefConfig.setASCIIEditorFont( fontSettingsEditor );

   // tree-font
   f              = getTreeFont();
   FONT_FAMILY    =f.family();
   FONT_SIZE      =f.pointSize();
   FONT_BOLD	   =f.bold();
   FONT_ITALIC    =f.italic();
   FONT_UNDERLINE =f.underline();
   FONT_STRIKEOUT =f.strikeOut();
   FontSettings fontSettingsTree( FONT_FAMILY, FONT_SIZE, FONT_BOLD, FONT_ITALIC, FONT_UNDERLINE, FONT_STRIKEOUT );
   mrefConfig.setTreeFont( fontSettingsTree );

   mrefConfig.setIntValue(  CTuxCardsConfiguration::I_TAB_SIZE,  getTabSize() );
   mrefConfig.setIntValue(  CTuxCardsConfiguration::I_WORD_WRAP, getWordWrap() );

   // done
   mrefConfig.saveToFile();
   emit configurationChanged();
}


bool OptionsDialog::getAutosave(){      return autosave->isChecked(); }
int  OptionsDialog::getMinutes()
{
   int minutes = saveMinutes->text().toInt();
   if ( 0 > minutes )
      return 0;

   return minutes;
}
bool OptionsDialog::getSaveWhenLeaving(){ return saveWhenLeaving->isChecked(); }
bool OptionsDialog::getCreateBackup(){    return createBackup->isChecked(); }

QFont OptionsDialog::getTreeFont(){   return treeFontText->font();   }
QFont OptionsDialog::getEditorFont(){ return editorFontText->font(); }

int OptionsDialog::getTabSize(){ return tabSize->text().toInt(); }
int OptionsDialog::getWordWrap(){
	if(noWrap->isChecked())
		return 0;
	else if(widgetWrap->isChecked())
		return 1;
	else{
		return wrapColumn->text().toInt();
	}
}

//void OptionsDialog::autosave(){
//	if (autosave->isChecked()){
//		saveMinutes->setEnabled(true);  label->setEnabled(true);
//	}else{
//		saveMinutes->setEnabled(false);  label->setEnabled(false);
//	}
//}


/**
 * calls the fontdialog and changes the option for the font of the
 * tuxcards-tree if necessary
 */
void OptionsDialog::changeTreeFont(){
 	bool ok;
	QFont f=QFontDialog::getFont(&ok, treeFontText->font(), this);

	// a valid font was selected
	if(ok){
		treeFontText->setFont(f);
		treeFontText->setText(f.rawName().section(':', 0,0));
	}
}

/**
 * calls the fontdialog and changes the option for the font of the
 * tuxcards-editor if necessary
 */

void OptionsDialog::changeEditFont(){
 	bool ok;
	QFont f=QFontDialog::getFont(&ok, editorFontText->font(), this);

	// a valid font was selected
	if(ok){
		editorFontText->setFont(f);
		editorFontText->setText(f.rawName().section(':', 0,0));
	}
}



