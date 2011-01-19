/***************************************************************************
                          CTuxCardsConfiguration.cpp  -  description
                             -------------------
    begin                : Sam Aug 17 2002
    copyright            : (C) 2002 by Alexander Theel
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

#include "CTuxCardsConfiguration.h"

#include "version.h"
#include "global.h"
#include "./utilities/iniparser/configparser.h"
#include <qdir.h>

#include <qmessagebox.h>


// -------------------------------------------------------------------------------
CTuxCardsConfiguration::CTuxCardsConfiguration()
// -------------------------------------------------------------------------------
 : mBoolMap()
 , mStringMap()
 , mIntMap()
{
   readConfigurationFile();
}

// -------------------------------------------------------------------------------
CTuxCardsConfiguration& CTuxCardsConfiguration::getInstance()
// -------------------------------------------------------------------------------
{
   static CTuxCardsConfiguration static_Instance;
   return static_Instance;
}

// -------------------------------------------------------------------------------
void CTuxCardsConfiguration::readConfigurationFile()
// -------------------------------------------------------------------------------
{
   // set default options just to be sure; if the config-file
   // might not be there or version 0.4 was used before
   ConfigParser parser( QDir::homeDirPath() + TUX_CONFIG_FILE, false );

   parser.setGroup("General");
   QString version   = parser.readEntry("Version",   QString("TuxCards_") + TUX_VERSION);

   mStringMap[S_DATA_FILE_NAME]     = parser.readEntry("Data_File", QDir::homeDirPath()+"/tuxcards_greeting");
   mBoolMap  [B_AUTOSAVE]           = parser.readNumEntry("Autosave",            0);
   mIntMap   [I_SAVE_ALL_MINUTES]   = parser.readNumEntry("Save_All_Minutes",   15);
   mBoolMap  [B_SAVE_WHEN_LEAVING]  = parser.readNumEntry("Save_when_Leaving",   0);
   mBoolMap  [B_CREATE_BACKUP_FILE] = parser.readNumEntry("Create_Backupfile",   0);
   mStringMap[S_EXECUTE_STATEMENT]  = parser.readEntry("Execution_Statement",   "");
   mStringMap[S_RECENT_FILES]       = parser.readEntry("Recent_Files",          "");
   mBoolMap  [B_ENCRYPTION_USED]    = parser.readNumEntry("Encryption_Used",     0);

//   colorR                           = parser.readNumEntry("Color_Font_R"      ,255);
//   colorG                           = parser.readNumEntry("Color_Font_G"      ,255);
//   colorB                           = parser.readNumEntry("Color_Font_B"      ,255);
//   fontColor                        = QColor(colorR, colorG, colorB);

   mStringMap[S_ICON_DIR]           = parser.readEntry("Icon_Dir", "/usr/local/tuxcards/icons");

   QString FONT_family              = parser.readEntry("Font_Family",  "Helvetica");
   int  FONT_size                   = parser.readNumEntry("Font_Size",          11);
   bool FONT_bold                   = parser.readNumEntry("Font_Bold",           0);
   bool FONT_italic                 = parser.readNumEntry("Font_Italic",         0);
   bool FONT_underline              = parser.readNumEntry("Font_Underline",      0);
   bool FONT_strikeout              = parser.readNumEntry("Font_Strikeout",      0);
   asciiEditorFont                  = FontSettings( FONT_family, FONT_size, FONT_bold,
                                                    FONT_italic, FONT_underline,
                                                    FONT_strikeout );

   FONT_family                      = parser.readEntry("Tree_Font_Family", "Helvetica");
   FONT_size                        = parser.readNumEntry("Tree_Font_Size",         11);
   FONT_bold                        = parser.readNumEntry("Tree_Font_Bold",          0);
   FONT_italic	                     = parser.readNumEntry("Tree_Font_Italic",        0);
   FONT_underline                   = parser.readNumEntry("Tree_Font_Underline",     0);
   FONT_strikeout                   = parser.readNumEntry("Tree_Font_Strikeout",     0);
   treeFont                         = FontSettings( FONT_family, FONT_size, FONT_bold,
                                                    FONT_italic, FONT_underline,
                                                    FONT_strikeout );

   mIntMap   [I_TAB_SIZE]           = parser.readNumEntry("TabSize",             4);
   mIntMap   [I_WORD_WRAP]          = parser.readNumEntry("WordWrap",            1);

   mStringMap[S_LAST_ACTIVE_ELEM_PATH] = parser.readEntry("Last_Active_Element","");

   mBoolMap  [B_SHOW_MAIN_TOOLBAR]  = parser.readNumEntry("Show_Main_Toolbar",   1);
   mBoolMap  [B_SHOW_ENTRY_TOOLBAR] = parser.readNumEntry("Show_Entry_Toolbar",  1);
   mBoolMap  [B_SHOW_EDITOR_TOOLBAR]= parser.readNumEntry("Show_Editor_Toolbar", 1);

   parser.setGroup("WindowGeometry");
   mIntMap   [I_WINDOW_WIDTH]       = parser.readNumEntry("WindowWidth",       750);
   mIntMap   [I_WINDOW_HEIGHT]      = parser.readNumEntry("WindowHeight",      550);
   mIntMap   [I_TREE_WIDTH]         = parser.readNumEntry("TreeWidth",         240);
   mIntMap   [I_EDITOR_WIDTH]       = parser.readNumEntry("EditorWidth",       500);
   mIntMap   [I_TREE_VSCROLLBAR_VALUE] = parser.readNumEntry("Tree_VScrollBar",  0);
}


// -------------------------------------------------------------------------------
void CTuxCardsConfiguration::saveToFile()
// -------------------------------------------------------------------------------
{
  // -- write to config-file ".tuxcards" ---------------------------
  // "Version" is the version of this program (not the version of a datafile)
  ConfigParser p(QDir::homeDirPath()+"/.tuxcards", false);

  p.setGroup("General");
  p.changeEntry("Version",             "TuxCardsV2.0");
  p.changeEntry("Data_File",                mStringMap[S_DATA_FILE_NAME]    );
  p.changeEntry("Autosave",            (int)mBoolMap  [B_AUTOSAVE]          );
  p.changeEntry("Save_All_Minutes",         mIntMap   [I_SAVE_ALL_MINUTES]  );
  p.changeEntry("Save_when_Leaving",   (int)mBoolMap  [B_SAVE_WHEN_LEAVING] );
  p.changeEntry("Create_Backupfile",   (int)mBoolMap  [B_CREATE_BACKUP_FILE]);
  p.changeEntry("Execution_Statement",      mStringMap[S_EXECUTE_STATEMENT] );
  p.changeEntry("Recent_Files",             mStringMap[S_RECENT_FILES]      );
  p.changeEntry("Encryption_Used",     (int)mBoolMap  [B_ENCRYPTION_USED]   );
//  p.changeEntry("Color_Font_R",             fontColor.red());
//  p.changeEntry("Color_Font_G",             fontColor.green());
//  p.changeEntry("Color_Font_B",             fontColor.blue());
  p.changeEntry("Icon_Dir",                 mStringMap[S_ICON_DIR]          );

  p.changeEntry("Font_Family",              asciiEditorFont.getFamily());
  p.changeEntry("Font_Size",                asciiEditorFont.getSize());
  p.changeEntry("Font_Bold",                asciiEditorFont.isBold());
  p.changeEntry("Font_Italic",              asciiEditorFont.isItalic());
  p.changeEntry("Font_Underline",           asciiEditorFont.isUnderlined());
  p.changeEntry("Font_Strikeout",           asciiEditorFont.isStrikeout());
  p.changeEntry("Tree_Font_Family",         treeFont.getFamily());
  p.changeEntry("Tree_Font_Size",           treeFont.getSize());
  p.changeEntry("Tree_Font_Bold",           treeFont.isBold());
  p.changeEntry("Tree_Font_Italic",         treeFont.isItalic());
  p.changeEntry("Tree_Font_Underline",      treeFont.isUnderlined());
  p.changeEntry("Tree_Font_Strikeout",      treeFont.isStrikeout());

  p.changeEntry("TabSize",                  mIntMap[I_TAB_SIZE]             );
  p.changeEntry("WordWrap",                 mIntMap[I_WORD_WRAP]            );

  p.changeEntry("Last_Active_Element",      mStringMap[S_LAST_ACTIVE_ELEM_PATH]);

  p.changeEntry("Show_Main_Toolbar",        mBoolMap[B_SHOW_MAIN_TOOLBAR]   );
  p.changeEntry("Show_Entry_Toolbar",       mBoolMap[B_SHOW_ENTRY_TOOLBAR]  );
  p.changeEntry("Show_Editor_Toolbar",      mBoolMap[B_SHOW_EDITOR_TOOLBAR] );

  p.setGroup("WindowGeometry");
  p.changeEntry("WindowWidth",              mIntMap[I_WINDOW_WIDTH]         );
  p.changeEntry("WindowHeight",             mIntMap[I_WINDOW_HEIGHT]        );
  p.changeEntry("TreeWidth",                mIntMap[I_TREE_WIDTH]           );
  p.changeEntry("EditorWidth",              mIntMap[I_EDITOR_WIDTH]         );
  p.changeEntry("Tree_VScrollBar",          mIntMap[I_TREE_VSCROLLBAR_VALUE]);

  p.writeChanges();
}




/****** getter *************************/
//QColor CTuxCardsConfiguration::getFontColor() const { return fontColor; }

FontSettings CTuxCardsConfiguration::getASCIIEditorFont() const { return asciiEditorFont; }
FontSettings CTuxCardsConfiguration::getTreeFont() const { return treeFont; }

/****** setter *************************/
//void CTuxCardsConfiguration::setFontColor(QColor c){ this->fontColor=c; }

void CTuxCardsConfiguration::setASCIIEditorFont(FontSettings f){ this->asciiEditorFont=f; }
void CTuxCardsConfiguration::setTreeFont(FontSettings f){ this->treeFont=f; }




// -------------------------------------------------------------------------------
bool CTuxCardsConfiguration::getBoolValue( eBoolValue eKey ) const
// -------------------------------------------------------------------------------
{
   return mBoolMap[eKey];
}

// -------------------------------------------------------------------------------
void CTuxCardsConfiguration::setBoolValue( eBoolValue eKey, bool bValue )
// -------------------------------------------------------------------------------
{
   mBoolMap[eKey] = bValue;
}





// -------------------------------------------------------------------------------
QString CTuxCardsConfiguration::getStringValue( eStringValue eKey ) const
// -------------------------------------------------------------------------------
{
   return mStringMap[eKey];
}

// -------------------------------------------------------------------------------
void CTuxCardsConfiguration::setStringValue( eStringValue eKey, const QString& sValue )
// -------------------------------------------------------------------------------
{
   mStringMap[eKey] = sValue;
}





// -------------------------------------------------------------------------------
int CTuxCardsConfiguration::getIntValue( eIntValue eKey ) const
// -------------------------------------------------------------------------------
{
   return mIntMap[eKey];
}

// -------------------------------------------------------------------------------
void CTuxCardsConfiguration::setIntValue( eIntValue eKey, int iValue )
// -------------------------------------------------------------------------------
{
   mIntMap[eKey] = iValue;
}





// -------------------------------------------------------------------------------
bool CTuxCardsConfiguration::askForUsingEncryption()
// -------------------------------------------------------------------------------
{
   if ( getBoolValue(B_ENCRYPTION_USED) )
   {
      return true;
   }

   int iUseEncryption = QMessageBox::warning( 0, "TuxCards",
                           "You are about to use encryption "
                           "for the first time.<p>"
                           "It is recommended that you use encryption on a "
                           "uncritical file for a few days.<p>"
                           "The encryption algorithm was written "
                           "with the best intents nevertheless "
                           "err is human.<p>"
                           "Therefore, you are solely responsible for "
                           "using this feature. This includes possible "
                           "errors within the algorithm, loss "
                           "of data, hacked data or forgotten passwords, etc.<p>"
                           "Are you sure that you want to use the "
                           "encryption feature?",
                           QMessageBox::Yes, QMessageBox::No );

   if ( QMessageBox::Yes == iUseEncryption )
   {
      setBoolValue( B_ENCRYPTION_USED, true );
      saveToFile();
      return true;
   }

   return false;
}
