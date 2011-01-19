/***************************************************************************
                          CTuxCardsConfiguration.h  -  description
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

#ifndef CTUXCARDS_CONFIGURATION_H
#define CTUXCARDS_CONFIGURATION_H

#include <qstring.h>
#include <qcolor.h>
#include "fontsettings.h"

#include <qmap.h>

class CTuxCardsConfiguration {
public:
  static CTuxCardsConfiguration& getInstance();

  void saveToFile();

  enum eBoolValue {
    B_AUTOSAVE,
    B_SAVE_WHEN_LEAVING,
    B_CREATE_BACKUP_FILE,

    B_SHOW_MAIN_TOOLBAR,
    B_SHOW_ENTRY_TOOLBAR,
    B_SHOW_EDITOR_TOOLBAR,

    B_LINEBREAK_MODERN,
    B_ENCRYPTION_USED
  };
  bool    getBoolValue( eBoolValue eKey ) const;
  void    setBoolValue( eBoolValue eKey, bool bValue );


  enum eStringValue {
    S_DATA_FILE_NAME,
    S_RECENT_FILES,

    S_EXECUTE_STATEMENT,

    S_ICON_DIR,
    S_LAST_ACTIVE_ELEM_PATH,
  };
  QString getStringValue( eStringValue eKey ) const;
  void    setStringValue( eStringValue eKey, const QString& sValue );


  enum eIntValue {
    I_SAVE_ALL_MINUTES,
    I_TAB_SIZE,
    I_WORD_WRAP,

    I_WINDOW_WIDTH,
    I_WINDOW_HEIGHT,
    I_TREE_WIDTH,
    I_EDITOR_WIDTH,
    I_TREE_VSCROLLBAR_VALUE
  };
  int     getIntValue( eIntValue eKey ) const;
  void    setIntValue( eIntValue eKey, int iValue );


  bool    askForUsingEncryption();

  /****** getter *************************/
//  QColor  getFontColor() const;

  FontSettings getASCIIEditorFont() const;
  FontSettings getTreeFont() const;

  /****** setter *************************/
//  void    setFontColor(QColor c);

  void    setASCIIEditorFont(FontSettings f);
  void    setTreeFont(FontSettings f);

private:
  CTuxCardsConfiguration();
  void readConfigurationFile();

//  QColor  fontColor;

  FontSettings asciiEditorFont;
  FontSettings treeFont;


  typedef QMap<int, bool> BoolMap;
  BoolMap   mBoolMap;

  typedef QMap<int, QString> StringMap;
  StringMap mStringMap;

  typedef QMap<int, int> IntMap;
  IntMap    mIntMap;
};

#endif
