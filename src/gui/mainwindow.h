/***************************************************************************
                          mainwindow.h  -  description
                             -------------------
    begin                : Sun Mar 26 2000
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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <q3mainwindow.h>
//Added by qt3to4:
#include <QCloseEvent>
#include <QTimerEvent>
#include <Q3ValueList>
#include <QLabel>
#include <QKeyEvent>
#include "../information/IHistoryListener.h"
#include "../information/CInformationElementHistory.h"

#include <qaction.h>
#include <qmenubar.h>
#include <q3popupmenu.h>
#include <q3filedialog.h>
#include <qmessagebox.h>
#include <qstatusbar.h>

#include "./dialogs/optionsdialog.h"

#include <q3toolbar.h>
#include <qtoolbutton.h>
#include <qpixmap.h>
#include <qmime.h>
#include <q3whatsthis.h>
#include <qcombobox.h>

#include <q3hbox.h>
//#include "qwidgetstack.h"
#include <qsplitter.h>
#include "CSingleEntryView.h"
#include "editor.h"
#include "CTree.h"

#include <qobject.h>
#include <qdir.h>
#include <qfile.h>
#include <q3textstream.h>
#include <qstring.h>

#include "../information/CInformationCollection.h"
#include "../CTuxCardsConfiguration.h"
#include "./RecentFileList.h"

#include "./dialogs/CPasswdDialog.h"

#include <iostream>

class MainWindow : public Q3MainWindow,
                   public IHistoryListener
{
  Q_OBJECT
private:
  CInformationCollection* mpCollection;
  QMenuBar*               mpMenu;
  OptionsDialog*          mpOptionsDialog;
  CTuxCardsConfiguration& mConfiguration;

  QSplitter*              mpSplit;
  Q3ValueList<int>* lst;
  CTree*                  mpTree;
  CSingleEntryView*       mpSingleEntryView;
  Editor*                 mpEditor;
  Q3ToolBar*               mpQuickLoader;
  RecentFileList*         mpRecentFiles;

  QStatusBar*             mpStatusBar;
  QLabel*     statusBar_ChangeLabel;
  QLabel*     mstatusBar_EncryptedLabel;
  QLabel*     mstatusBar_NumElements;
  QDialog*    showDialog;       // a dialog
  QLabel*     showLabel;        // the label of the 'show'-dialog, to change it
                                //     whenever we want to

  bool    CHANGES;              // states whether or not -> changes are done (for saving)

  int     TIMER_ID;

  void lowMemoryExit( void );
  void checkPointer( void* pPointer );

  void settingUpActions( void );
  void settingUpMenu( void );
  void settingUpToolBar( void );
  void settingUpStatusBar( void );
  void settingUpEditor( QWidget* pParent );
  void settingUpTree( QWidget* pParent );
  void setWindowGeometry( int,int, int,int );

  void settingUpQuickLoader( void );

  QComboBox* pComboListStyle;
  QComboBox* pComboFont;
  QComboBox* pComboSize;

  QToolButton* textFormatTool;
  QToolButton* textBoldTool;
  QToolButton* textItalicTool;
  QToolButton* textUnderTool;
  QToolButton* textColorTool;

  QToolButton* textLeftTool;
  QToolButton* textCenterTool;
  QToolButton* textRightTool;
  QToolButton* textBlockTool;

  QToolButton* mpLeftButton;
  QToolButton* mpRightButton;

  // actions
  Q3Action* mfileEncryptFile;
  Q3Action* editUndoAction;
  Q3Action* editRedoAction;
  Q3Action* editCopyAction;
  Q3Action* editSetEntryColor;
  Q3Action* editSetEntrySubTreeColor;

	int PromptBeforeNewFile();
  int askForSaving(QString question);
  bool initializingCollection(QString dataFileName);
  void deleteCollection(CInformationCollection* collection);

  void callingExecutionStatement();

  CInformationElementHistory mHistory;
  CPasswdDialog              mPasswdDialog;

  Q3ToolBar*  mpMainTools;
  Q3ToolBar*  mpEntryTools;
  Q3ToolBar*  mpEditorTools;
  int        miMainToolBarID;
  int        miEntryToolBarID;
  int        miEditorToolBarID;


  CInformationElement* getActiveIE();
  void applyConfiguration();
  void startAutosaveTimer();

private slots:
  void textListStyle(int);
  void textFontFamily( const QString &f );
  void textFontSize( const QString &p );
  void textBold();
  void textItalic();
  void textUnder();
  void textColor();
  void textLeft();
  void textHCenter();
  void textRight();
  void textBlock();

  void changeInformationFormat();
  void textFontChanged(const QFont &f);
  void textColorChanged(const QColor &c);
  void textAlignmentChanged(int);
  void showRecognizedFormat(InformationFormat format);

  void editConfiguration();
  void applyConfigurationMain();

  void wordCount();
  void insertCurrentDate();
  void insertCurrentTime();

  void activatePreviousHistoryElement( void );
  void activateNextHistoryElement( void );

  // debug slots
  void debugShowRTFTextSource();
  void debugShowXMLCode();

//  void saveActiveEntry();
  void quicklyLoad(Path*);

  void search();
  void print();

  void moveElementUp();
  void moveElementDown();

  void addElementToBookmarksEvent();

  void slotSaveAndLoadNewFile(QString newFile);

  void activeInformationElementChanged(CInformationElement*);


  void toggleMainToolbarVisability();
  void toggleEntryToolbarVisability();
  void toggleEditorToolbarVisability();

  void setMainToolbarVisible( bool bVisible );
  void setEntryToolbarVisible( bool bVisible );
  void setEditorToolbarVisible( bool bVisible );

public:
  MainWindow(QString arg);
  ~MainWindow();

  // ************* IHistoryListener ******************
  virtual void historyStatusChanged( bool bHasPreviousElement, bool bHasNextElement );

public slots:
  void showMessage(QString, int seconds);

  // menucalls
  void newFile();
  void open();
  bool open(QString fileName);
  void save();
  void save(QString);
  void saveAs();
  void toggleFileEncryption();
  void exportHTML();
  void exit();

  void showKBShortcuts();
  void showAbout();

  void selectLastActiveElement( void );
  void makeVisible( SearchPosition* pPosition );

  virtual void keyPressEvent( QKeyEvent* );

  void updateStatusbarElements(int);
protected:
  void clearAll();
  int  getDataFileFormat( QString fileName );
  bool openOldDataFile( QString fileName );
  bool openXMLDataFile( QString fileName );

  virtual void closeEvent( QCloseEvent *e );
  void timerEvent( QTimerEvent* );
  void checkFirstTime( void );

protected slots:
  void recognizeChanges( void );                  // to keep track of changes
};

#endif
