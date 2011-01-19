/***************************************************************************
                          mainwindow.cpp  -  description
                             -------------------
    begin                : Sun Mar 26 2000
    copyright            : (C) 2000 by Alexander Theel, (c) 2006-2007 Amit D. Chaudhary
    email                : alex.theel@gmx.net, amitch@rajgad.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include "mainwindow.h"

//#define DEBUGGING

#include <iostream>
#include <stdlib.h>
#include <qfontdialog.h>
//Added by qt3to4:
#include <QTimerEvent>
#include <QLabel>
#include <QPixmap>
#include <QCloseEvent>
#include <Q3ValueList>
#include <Q3TextStream>
#include <QKeyEvent>
#include <Q3PopupMenu>

#include "../icons/lo16-app-tuxcards.xpm"
#include "../icons/lo32-app-tuxcards.xpm"

#ifdef DEBUGGING
  #include "../icons/debug/showText.xpm"
  #include "../icons/debug/xml.xpm"
#endif

#include "../information/converter.h"
#include "../information/CInformationCollection.h"
#include "../persister.h"
#include "../information/xmlpersister.h"
#include "../information/htmlwriter.h"
#include "../utilities/iniparser/configparser.h"

#include <qprinter.h>
#include <q3paintdevicemetrics.h>
#include <q3simplerichtext.h>
#include <qpainter.h>
#include <qfontmetrics.h>

#include <qfontdatabase.h>
#include <qapplication.h>

#include "../utilities/strings.h"
#include "BookmarkButton.h"

#include "./dialogs/CFileEncryptionPasswordDialog.h"

#include "../utilities/crypt/StringCrypter.h"

#include "../version.h"
#include "../global.h"
#include "../Greetings.h"

#include "../utilities/CIconManager.h"
#define  getIcon(x)  CIconManager::getInstance().getIcon(x)


// -------------------------------------------------------------------------------
MainWindow::MainWindow(QString arg)
 : mpCollection( NULLPTR )
 , mpMenu( NULLPTR )
 , mpOptionsDialog( NULLPTR )
 , mConfiguration( CTuxCardsConfiguration::getInstance() )
 , mpSplit( NULLPTR )
 , mpTree( NULLPTR )
 , mpSingleEntryView( NULLPTR )
 , mpEditor( NULLPTR )
 , mpQuickLoader( NULLPTR )
 , mpRecentFiles( NULLPTR )
 , mpStatusBar( NULLPTR )
 , mpLeftButton( NULLPTR )
 , mpRightButton( NULLPTR )
 , mHistory( )
 , mPasswdDialog( )          // with parent as NULLPTR
 , mpMainTools( NULLPTR )
 , mpEntryTools( NULLPTR )
 , mpEditorTools( NULLPTR )
 , miMainToolBarID( 0 )
 , miEntryToolBarID( 0 )
 , miEditorToolBarID( 0 )
// -------------------------------------------------------------------------------
{
   checkFirstTime();

   // build up mainwindow
   setCaption("TuxCards");
   setIcon(lo32_app_tuxcards_xpm);
   CIconManager::getInstance().setIconDirectory( mConfiguration.getStringValue( CTuxCardsConfiguration::S_ICON_DIR ) );

   Q3HBox* layout=new Q3HBox(this);
   setCentralWidget(layout);

   mpSplit = new QSplitter( layout );
   checkPointer( mpSplit );

   settingUpEditor( mpSplit );
   settingUpTree( mpSplit );
   mpSplit->moveToFirst( mpTree );
   mpSplit->setOpaqueResize(TRUE);

   settingUpActions();
   settingUpMenu();
   settingUpToolBar();
   settingUpStatusBar();
//  settingUpQuickLoader();

   // create optionsDialog
   mpOptionsDialog = new OptionsDialog( this, mConfiguration );
   if ( NULLPTR != mpOptionsDialog )
   {
      connect( mpOptionsDialog, SIGNAL(configurationChanged()), this, SLOT(applyConfigurationMain()) );
   }

   // create little "showing-"dialog
   showDialog   =new QDialog(this);
   Q3GroupBox* gb=new Q3GroupBox(1, Qt::Horizontal, showDialog);
   showLabel    =new QLabel("Saving ...", gb);

   applyConfiguration();

   CHANGES=FALSE;

   mHistory.setListener( this );

   // build up tree, if config-file ('.tuxcards') was found
   bool result = FALSE;
   if ( arg != "" )
   {
      result = open(arg);
   }
   else if ( mConfiguration.getStringValue( CTuxCardsConfiguration::S_DATA_FILE_NAME ) != "" )
   {
      result = open(mConfiguration.getStringValue( CTuxCardsConfiguration::S_DATA_FILE_NAME ));
   } else {
   	// For empty datafile entry in the .tuxcards config file
   	clearAll();
   }

  // show the completed window
  show();
}


// -------------------------------------------------------------------------------
MainWindow::~MainWindow()
// -------------------------------------------------------------------------------
{
   deleteCollection( mpCollection );
}


// -------------------------------------------------------------------------------
// This is an emergency exit. The application will be quited if not enough
// memory is available to create all needed objects.
// -------------------------------------------------------------------------------
void MainWindow::lowMemoryExit( void )
// -------------------------------------------------------------------------------
{
   std::cout<<"TuxCards ERROR\nNot enough memory to run application.\nTuxCards"
              " will be stopped!!!"<<std::endl;
   QMessageBox::critical( NULLPTR, "TuxCards", "Not enough memory to run "
                          "application.\nThe program will be quit.",
                          QMessageBox::Abort, QMessageBox::NoButton );
   QApplication::exit( -1 );
}

// -------------------------------------------------------------------------------
// Convenience method for 'lowMemoryExit()'.
// -------------------------------------------------------------------------------
void MainWindow::checkPointer( void* pPointer )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == pPointer )
   {
      lowMemoryExit();
   }
}


// -------------------------------------------------------------------------------
void MainWindow::historyStatusChanged( bool bHasPreviousElement,
                                       bool bHasNextElement )
// -------------------------------------------------------------------------------
{
   //std::cout<<"historyStatusChanged("<<bHasPreviousElement<<","<<bHasNextElement<<")"<<std::endl;
   if ( NULLPTR != mpLeftButton )
      mpLeftButton->setEnabled( bHasPreviousElement );

   if ( NULLPTR != mpRightButton )
      mpRightButton->setEnabled( bHasNextElement );
}


// -------------------------------------------------------------------------------
// Responses to the change of the active informationelement. Adds the new element
// to the history.
// -------------------------------------------------------------------------------
void MainWindow::activeInformationElementChanged( CInformationElement* pIE )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR != pIE )
   {
      mHistory.addElement( *pIE );
   }
}


// -------------------------------------------------------------------------------
void MainWindow::activatePreviousHistoryElement( void )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR != mpCollection )
      mpCollection->setActiveElement( mHistory.getPrevious() );
}

// -------------------------------------------------------------------------------
void MainWindow::activateNextHistoryElement( void )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR != mpCollection )
      mpCollection->setActiveElement( mHistory.getNext() );
}


// -------------------------------------------------------------------------------
void MainWindow::settingUpEditor( QWidget* pParent )
// -------------------------------------------------------------------------------
{
   mpSingleEntryView = new CSingleEntryView( pParent );
   checkPointer( mpSingleEntryView );

   if ( NULLPTR == mpSingleEntryView )
      return;

   mpEditor = mpSingleEntryView->getEditor();

   connect(mpEditor, SIGNAL(textChanged()), this, SLOT(recognizeChanges()));
   connect(mpEditor, SIGNAL(formatRecognized(InformationFormat)), this, SLOT(showRecognizedFormat(InformationFormat)));
   connect(mpEditor, SIGNAL(currentAlignmentChanged(int)), this, SLOT(textAlignmentChanged(int)) );
}


// -------------------------------------------------------------------------------
void MainWindow::settingUpTree( QWidget* pParent )
// -------------------------------------------------------------------------------
{
   mpTree  = new CTree( pParent, mConfiguration );
   checkPointer( mpTree );

   connect( mpTree, SIGNAL(showMessage(QString, int)),    this, SLOT(showMessage(QString, int)) );
   connect( mpTree, SIGNAL(makeVisible(SearchPosition*)), this, SLOT(makeVisible(SearchPosition*)) );
   connect( mpTree, SIGNAL(addEntryToBookmarksSignal()),  this, SLOT(addElementToBookmarksEvent()) );

	// On a drag start, move editor contents to InformationElement.
   connect(mpTree, SIGNAL(dragStarted()), mpEditor, SLOT(writeCurrentTextToActiveInformationElement()));
}



// -------------------------------------------------------------------------------
void MainWindow::settingUpStatusBar( void )
// -------------------------------------------------------------------------------
{
   mpStatusBar = new QStatusBar(this);
   checkPointer( mpStatusBar );

   mstatusBar_NumElements=new QLabel( " ", mpStatusBar );
   mstatusBar_NumElements->setFixedWidth(120);
   mpStatusBar->addWidget(mstatusBar_NumElements, 0, TRUE);

   statusBar_ChangeLabel=new QLabel( " ", mpStatusBar );
   statusBar_ChangeLabel->setFixedWidth(10);
   mpStatusBar->addWidget(statusBar_ChangeLabel, 0, TRUE);

   mstatusBar_EncryptedLabel = new QLabel(" ", mpStatusBar );
   mstatusBar_EncryptedLabel->setFixedWidth(30);
   mpStatusBar->addWidget(mstatusBar_EncryptedLabel, 0, TRUE);
}


// -------------------------------------------------------------------------------
void MainWindow::settingUpActions( void )
// -------------------------------------------------------------------------------
{
	// Actions for file menu
   mfileEncryptFile  = new Q3Action("Toggle file encryption", getIcon("fileunlock"),
   					"Toggle file &encryption", Qt::CTRL+Qt::Key_E, this);
	// A toggled item and off by default.
   mfileEncryptFile->setToggleAction(TRUE);
   connect( mfileEncryptFile, SIGNAL(activated()), this, SLOT(toggleFileEncryption()) );

	// Actions for edit menu
   editUndoAction = new Q3Action( "Undo", getIcon("undo"),"&Undo", Qt::CTRL+Qt::Key_Z, this);
   connect( mpEditor, SIGNAL(undoAvailable(bool)), editUndoAction, SLOT(setEnabled(bool)) );
   connect( editUndoAction, SIGNAL(activated()), mpEditor, SLOT(undo()) );

   editRedoAction = new Q3Action( "Redo", getIcon("redo"),"&Redo", Qt::CTRL+Qt::Key_Y, this);
   connect( mpEditor, SIGNAL(redoAvailable(bool)), editRedoAction, SLOT(setEnabled(bool)) );
   connect( editRedoAction, SIGNAL(activated()), mpEditor, SLOT(redo()) );

   editCopyAction = new Q3Action( "Copy", getIcon("editcopy"),"&Copy", Qt::CTRL+Qt::Key_C, this);
   connect( mpEditor, SIGNAL(copyAvailable(bool)), editCopyAction, SLOT(setEnabled(bool)) );
   connect( editCopyAction, SIGNAL(activated()), mpEditor, SLOT(copy()) );

   editSetEntryColor = new Q3Action( "Set Entry Color", getIcon("editentrycolor"),
   			"Set &Entry Color...", Qt::CTRL+Qt::Key_R, this);
   connect( editSetEntryColor, SIGNAL(activated()), mpTree, SLOT(setEntryColor()) );

   editSetEntrySubTreeColor = new Q3Action( "Set Entry Subtree Color", getIcon("editentrysubtreecolor"),
   			"Set Entry &Sub-Tree Color...", Qt::CTRL+Qt::SHIFT+Qt::Key_R, this);
   connect( editSetEntrySubTreeColor, SIGNAL(activated()), mpTree, SLOT(setEntrySubTreeColor()) );
}


// -------------------------------------------------------------------------------
void MainWindow::settingUpMenu( void )
// -------------------------------------------------------------------------------
{
   Q3PopupMenu *file = new Q3PopupMenu( this );
   file->insertItem( getIcon("filenew" ),    "&New File",     this, SLOT(newFile()), Qt::CTRL+Qt::Key_N);
   file->insertItem( getIcon("fileopen"),    "&Open File...", this, SLOT(open()), Qt::CTRL+Qt::Key_O);
   file->insertItem( getIcon("filesave"),    "&Save",         this, SLOT(save()), Qt::CTRL+Qt::Key_S);
   file->insertItem(                         "Save &As...",   this, SLOT(saveAs()) );

//    file->insertItem(                "Save Active Entry", this, SLOT(saveActiveEntry()) );
   file->insertItem( getIcon("fileprint"),   "&Print current entry...",     this, SLOT(print()), Qt::CTRL+Qt::Key_P );

   file->insertSeparator();
	// File->Encrypt current file
   mfileEncryptFile->addTo(file);

   file->insertSeparator();
   mpRecentFiles = new RecentFileList(this, file, mConfiguration.getStringValue( CTuxCardsConfiguration::S_RECENT_FILES ));
   checkPointer( mpRecentFiles );

   connect( mpRecentFiles, SIGNAL(openFile(QString)), this, SLOT(slotSaveAndLoadNewFile(QString)) );

   file->insertSeparator();
   file->insertItem(                    "Export to &HTML...", this, SLOT(exportHTML()) );
   file->insertSeparator();
   file->insertItem( getIcon("exit"),   "&Exit", this, SLOT(exit()), Qt::CTRL+Qt::Key_Q );


   Q3PopupMenu* edit = new Q3PopupMenu( this );
   editUndoAction->addTo( edit );
   editRedoAction->addTo( edit );
   edit->insertSeparator();

   if ( NULLPTR != mpEditor )
   {
      edit->insertItem( getIcon("editcut"),   "Cu&t",   mpEditor, SLOT(cut()),   Qt::CTRL+Qt::Key_X   );
      editCopyAction->addTo( edit );
      edit->insertItem( getIcon("editpaste"), "&Paste", mpEditor, SLOT(paste()), Qt::CTRL+Qt::Key_V );
      edit->insertSeparator();
      edit->insertItem(                   "Select &All", mpEditor, SLOT(selectAll()), Qt::CTRL+Qt::Key_A );

      edit->insertSeparator();
      editSetEntryColor->addTo(edit);
      editSetEntrySubTreeColor->addTo(edit);

      edit->insertSeparator();
	  edit->insertItem(                  "Insert Current &Date", this, SLOT(insertCurrentDate()), Qt::CTRL+Qt::Key_D );
	  edit->insertItem(                  "Insert Current T&ime", this, SLOT(insertCurrentTime()), Qt::CTRL+Qt::Key_T );
      edit->insertSeparator();
	  edit->insertItem(                  "&Options...", this, SLOT(editConfiguration()) );
   }

   Q3PopupMenu* toolbars = new Q3PopupMenu( this );
   Q_CHECK_PTR( toolbars );

   miMainToolBarID   = toolbars->insertItem( "Show Main Toolbar", this, SLOT(toggleMainToolbarVisability()) );
   miEntryToolBarID  = toolbars->insertItem( "Show Entry Manipulation Toolbar", this, SLOT(toggleEntryToolbarVisability()) );
   miEditorToolBarID = toolbars->insertItem( "Show Editor Toolbar", this, SLOT(toggleEditorToolbarVisability()) );

   Q3PopupMenu* view = new Q3PopupMenu( this );
   view->insertItem("Toolbars ", toolbars );
   view->insertItem(                  "&Word Count",          this, SLOT(wordCount()));

   Q3PopupMenu *about = new Q3PopupMenu( this );
   about->insertItem("&Keyboard Shortcuts", this, SLOT(showKBShortcuts()) );
   about->insertSeparator();
   about->insertItem(QPixmap(lo16_app_tuxcards_xpm),"About TuxCards", this, SLOT(showAbout()) );

   mpMenu = new QMenuBar(this);
   if ( NULLPTR != mpMenu )
   {
      mpMenu->insertItem( "&File",    file);
      mpMenu->insertItem( "&Edit",    edit);
      mpMenu->insertItem( "&View", 	view);
      mpMenu->insertItem( "&About",   about);
   }
}


// -------------------------------------------------------------------------------
void MainWindow::settingUpToolBar( void )
// -------------------------------------------------------------------------------
{
  mpMainTools = new Q3ToolBar(this);

  QToolButton* clearTool = new QToolButton( getIcon("filenew"), "Create a new file", 0,
                                            this, SLOT(newFile()), mpMainTools);
  mpMainTools->addSeparator();
  QToolButton* openTool = new QToolButton( getIcon("fileopen"), "Open a new file", 0,
                                           this, SLOT(open()), mpMainTools);

  QToolButton* saveTool=new QToolButton( getIcon("filesave"),   "Save current file (Ctrl+S)", 0,
                                         this, SLOT(save()), mpMainTools);

  QToolButton* printTool=new QToolButton( getIcon("fileprint"), "Print current entry", 0,
                                          this, SLOT(print()), mpMainTools);


  mfileEncryptFile->addTo( mpMainTools );

  // ----------- add tools for editing the text within the editor --------------
  mpMainTools->addSeparator();
  editUndoAction->addTo( mpMainTools );
  editRedoAction->addTo( mpMainTools );

  QToolButton* editCutTool = new QToolButton( getIcon("editcut"), "Cut (Ctrl+X)", 0, mpEditor, SLOT(cut()), mpMainTools);

  editCopyAction->addTo( mpMainTools );

  QToolButton* editPasteTool = new QToolButton( getIcon("editpaste"), "Paste (Ctrl+V)", 0, mpEditor, SLOT(paste()), mpMainTools);

  mpMainTools->addSeparator();

  editSetEntryColor->addTo(mpMainTools);
  editSetEntrySubTreeColor->addTo(mpMainTools);

  mpMainTools->addSeparator();

  QToolButton* findTool = new QToolButton( getIcon("find"), "Search (Ctrl+F)", 0, this, SLOT(search()), mpMainTools);
  mpMainTools->addSeparator();
  Q3WhatsThis::whatsThisButton(mpMainTools);


  Q3MimeSourceFactory::defaultFactory()->setPixmap("filenew", getIcon("filenew"));
  Q3WhatsThis::add(clearTool,"<img source=\"filenew\">"
                            "<b>Clear whole Tree</b><p>"
                            "Click this button to remove all entries from "
                            "the tree.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("fileopen", getIcon("fileopen"));
  Q3WhatsThis::add(openTool, "<img source=\"fileopen\"><b>Open a new File</b><p>"
                            "Click this button to open a new data file. "
                            "You can also select the <i>Open</i> command "
                            "from the <i>File</i> menu.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("filesave", getIcon("filesave"));
  Q3WhatsThis::add(saveTool, "<img source=\"filesave\"><b>Save Data to File</b> (Ctrl+S)<p>"
                            "Click this button to save all data to disk. "
                            "If this is a new file, you will be prompted "
                            "for a file name.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("fileprint", getIcon("fileprint"));
  Q3WhatsThis::add(printTool,  "<img source=\"fileprint\"> <b>Print current Entry</b><p>"
                            "Click this button to print the currently active "
                            "entry.<p>"
                            "<i>Please note: Only RTF-notes can be printed correctly. "
                            "When printing an plain text note white spaces are "
                            "ignored ");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("undo", getIcon("undo"));
  editUndoAction->setWhatsThis("<img source=\"undo\"><b>Undo</b> (Ctrl+Z)<p>"
                              "This button undoes changes made within the editor.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("redo", getIcon("redo"));
  editRedoAction->setWhatsThis("<img source=\"redo\"><b>Redo</b> (Ctrl+Y)<p>"
                               "This button provides redo functionality for the editor.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("editcut", getIcon("editcut"));
  Q3WhatsThis::add(editCutTool, "<img source=\"editcut\"><b>Cut</b> (Ctrl+X)<p>"
                            "Cut text within the editor.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("editcopy", getIcon("editcopy"));
  editCopyAction->setWhatsThis("<img source=\"editcopy\"><b>Copy</b> (Ctrl+C)<p>"
                               "Copy text within the editor.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("editpaste", getIcon("editpaste"));
  Q3WhatsThis::add(editPasteTool, "<img source=\"editpaste\"><b>Paste</b> (Ctrl+V)<p>"
                            "Paste text within the editor.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("find", getIcon("find"));
  Q3WhatsThis::add(findTool, "<img source=\"find\"><b>Search</b> (Ctrl+F)<p>"
                            "Use this button, if you want to search for words "
                            "within your data.");


  // ----------- add tools for moving elements within the tree --------------
  mpEntryTools = new Q3ToolBar(this);

  textFormatTool = new QToolButton( getIcon("filenew"), "Converts the Text Format", 0,
                                    this, SLOT(changeInformationFormat()), mpEntryTools);


  mpEntryTools->addSeparator();
  QToolButton* addTreeElementTool = new QToolButton( getIcon("addTreeElement"), "Add Entry (INSERT)", 0,
                                                     mpTree, SLOT(addElement()), mpEntryTools);

  QToolButton* changePropertyTool = new QToolButton( getIcon("changeProperty"), "Change Properties", 0,
                                                     mpTree, SLOT(changeActiveElementProperties()), mpEntryTools);

  QToolButton* removeKnotenTool = new QToolButton( getIcon("delete"), "Remove active Entry (DELETE)", 0,
                                                   mpTree, SLOT(askForDeletion()), mpEntryTools);

  mpEntryTools->addSeparator();
  QToolButton* ieUpTool = new QToolButton( getIcon("upArrow"), "Move Current Entry Upwards", 0,
                                           this, SLOT(moveElementUp()), mpEntryTools);

  QToolButton* ieDownTool = new QToolButton( getIcon("downArrow"), "Move Current Entry Downwards", 0,
                                             this, SLOT(moveElementDown()), mpEntryTools);

  mpEntryTools->addSeparator();
  mpLeftButton = new QToolButton( getIcon("back"), "Last Entry accessed in History (Alt+Left)", 0,
                                  this, SLOT(activatePreviousHistoryElement()), mpEntryTools );
  mpLeftButton->setEnabled(false);
  mpRightButton = new QToolButton( getIcon("forward"), "Next Entry in History (Alt+Right)", 0,
                                  this, SLOT(activateNextHistoryElement()), mpEntryTools );
  mpRightButton->setEnabled(false);


  Q3WhatsThis::add(textFormatTool, "This button shows you the text format (ASCII / RTF) "
                                  "of the currently active entry. It does also let "
                                  "you convert between the two formats.<p>"
                                  "<i>Usually, you do not need to worry about "
                                  "converting text formats.</i>");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("addTreeElement", getIcon("addTreeElement"));
  Q3WhatsThis::add(addTreeElementTool, "<img source=\"addTreeElement\"><b>Add Entry</b> (INSERT)<p>"
                                      "You can add further child-entries using this "
                                      "button. The same function is available through "
                                      "the context menu (right click on an item).<p>"
                                      "Clicking this button will open a dialog which "
                                      "prompts you for a name of the new entry.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("changeProp", getIcon("changeProperty"));
  Q3WhatsThis::add(changePropertyTool, "<img source=\"changeProp\"><b>Change Property</b><p>"
                                      "Clicking this button, a dialog will appear. There, "
                                      "you may enter a new name and select another icon "
                                      "for the currently active entry.<p>"
                                      "You can also use the context menu (right click on "
                                      "an item) to call this function.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("delete", getIcon("delete"));
  Q3WhatsThis::add(removeKnotenTool, "<img source=\"delete\"><b>Remove active Entry</b> (DELETE)<p>"
                                    "This will remove the currently active entry <i>and "
                                    "all</i> child-entries from the tree.<p>"
                                    "You can also use the context menu (right click on "
                                    "an item) for this function.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("upArrow", getIcon("upArrow"));
  Q3WhatsThis::add(ieUpTool, "<img source=\"upArrow\"><b>Move Up</b><p>"
                            "Moves the currently active entry one position upwards "
                            "within the tree.<p>"
                            "The entry is moved with all of its children.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("downArrow", getIcon("downArrow"));
  Q3WhatsThis::add(ieDownTool, "<img source=\"downArrow\"> <b>Move Down</b><p>"
                              "Moves the currently active entry "
                              "one position downwards within the tree.<p>"
                              "The entry is moved with all of its children.");

  Q3MimeSourceFactory::defaultFactory()->setPixmap("historyBack", getIcon("back"));
  Q3WhatsThis::add(mpLeftButton, "<img source=\"historyBack\"><b>History, Back</b> (Alt+Left)<p>"
                                "History function. If this button is clicked, then the "
                                "last active entry is selected.<p>"
                                "<i>This is similar to the back button within your "
                                "browser.</i>" );
  Q3MimeSourceFactory::defaultFactory()->setPixmap("historyForward", getIcon("forward"));
  Q3WhatsThis::add(mpRightButton, "<img source=\"historyForward\"><b>History, Forward</b> (Alt+Right)<p>"
                                 "History function. If this button is clicked, then the "
                                 "next entry is selected.<p>"
                                 "<i>This is similar to the forward button within your "
                                 "browser.</i>" );


  // ----------- add tools for richtext to toolbar ------------------
  //mpMainTools->addSeparator();
  mpEditorTools = new Q3ToolBar(this);

  pComboListStyle = new QComboBox( FALSE, mpEditorTools );
  pComboListStyle->insertItem( tr("Standard") );
  pComboListStyle->insertItem( tr("Bullet List (Disc)") );
  pComboListStyle->insertItem( tr("Bullet List (Circle)") );
  pComboListStyle->insertItem( tr("Bullet List (Square)") );
  pComboListStyle->insertItem( tr("Ordered List (Decimal)") );
  pComboListStyle->insertItem( tr("Ordered List (Alpha lower)") );
  pComboListStyle->insertItem( tr("Ordered List (Alpha upper)") );
  connect( pComboListStyle, SIGNAL( activated( int ) ),
           this, SLOT( textListStyle( int ) ) );

  pComboFont = new QComboBox( TRUE, mpEditorTools );
  QFontDatabase db;
  pComboFont->insertStringList( db.families() );
  connect( pComboFont, SIGNAL( activated( const QString & ) ),
           this, SLOT( textFontFamily( const QString & ) ) );
  pComboFont->lineEdit()->setText( QApplication::font().family() );

  pComboSize = new QComboBox( TRUE, mpEditorTools );
  Q3ValueList<int> sizes = db.standardSizes();
  Q3ValueList<int>::Iterator it = sizes.begin();
  for ( ; it != sizes.end(); ++it )
     pComboSize->insertItem( QString::number( *it ) );
  connect( pComboSize, SIGNAL( activated( const QString & ) ),
           this, SLOT( textFontSize( const QString & ) ) );
  pComboSize->lineEdit()->setText( QString::number( QApplication::font().pointSize() ) );


  textBoldTool = new QToolButton( getIcon("text_bold"), "Bold (Ctrl+B)", 0, this, SLOT(textBold()), mpEditorTools );
  textBoldTool->setToggleButton(TRUE);

  textItalicTool = new QToolButton( getIcon("text_italic"), "Italic (Ctrl+I)", 0, this, SLOT(textItalic()), mpEditorTools );
  textItalicTool->setToggleButton(TRUE);

  textUnderTool = new QToolButton( getIcon("text_under"), "Underline (Ctrl+U)", 0, this, SLOT(textUnder()), mpEditorTools);
  textUnderTool->setToggleButton(TRUE);

  QPixmap dummy(1,1);
  textColorTool = new QToolButton( dummy, "Color", 0, this, SLOT(textColor()), mpEditorTools );
  textColorChanged(Qt::black);

  mpEditorTools->addSeparator();
  textLeftTool = new QToolButton( getIcon("text_left"), "Align Left", 0, this, SLOT(textLeft()), mpEditorTools );
  textLeftTool->setToggleButton(TRUE);

  textCenterTool = new QToolButton( getIcon("text_center"), "Center", 0, this, SLOT(textHCenter()), mpEditorTools );
  textCenterTool->setToggleButton(TRUE);

  textRightTool = new QToolButton( getIcon("text_right"), "Align Right", 0, this, SLOT(textRight()), mpEditorTools );
  textRightTool->setToggleButton(TRUE);

  textBlockTool = new QToolButton( getIcon("text_block"), "Text Block", 0, this, SLOT(textBlock()), mpEditorTools );
  textBlockTool->setToggleButton(TRUE);

  Q3MimeSourceFactory::defaultFactory()->setPixmap("textBold", getIcon("text_bold"));
  Q3WhatsThis::add(textBoldTool, "<img source=\"textBold\"><b>Bold</b><p>"
                                "Use this button, if you want to use bold text.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("textItalic", getIcon("text_italic"));
  Q3WhatsThis::add(textItalicTool, "<img source=\"textItalic\"><b>Italic</b><p>"
                                "Use this button, if you want to use italic text.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("textUnder", getIcon("text_under"));
  Q3WhatsThis::add(textUnderTool, "<img source=\"textUnder\"><b>Underline</b><p>"
                                "Use this button, if you want to use underlined text.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("textColor", getIcon("text_color"));
  Q3WhatsThis::add(textColorTool, "<img source=\"textColor\"><b>Text Color</b><p>"
                                 "Changes the color of the selected text.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("alignLeft", getIcon("text_left"));
  Q3WhatsThis::add(textLeftTool, "<img source=\"alignLeft\"><b>Align Left</b><p>"
                                "Aligns the currently edited paragraph on the left side.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("alignCenter", getIcon("text_center"));
  Q3WhatsThis::add(textCenterTool, "<img source=\"alignCenter\"><b>Center</b><p>"
                                  "Centers the currently edited paragraph within the editor.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("alignRight", getIcon("text_left"));
  Q3WhatsThis::add(textRightTool, "<img source=\"alignRight\"><b>Align Right</b><p>"
                                 "Aligns the currently edited paragraph on the right side.");
  Q3MimeSourceFactory::defaultFactory()->setPixmap("alignBlock", getIcon("text_block"));
  Q3WhatsThis::add(textBlockTool, "<img source=\"alignBlock\"><b>Text Block</b><p>"
                                   "Aligns the currently edited paragraph on both sides "
                                   "within the editor.");



  connect( mpEditor, SIGNAL( currentFontChanged(const QFont &) ),
           this,     SLOT( textFontChanged(const QFont &) ) );
  connect( mpEditor, SIGNAL( currentColorChanged(const QColor &) ),
           this,     SLOT( textColorChanged(const QColor &) ) );


  setMainToolbarVisible(   mConfiguration.getBoolValue( CTuxCardsConfiguration::B_SHOW_MAIN_TOOLBAR )   );
  setEntryToolbarVisible(  mConfiguration.getBoolValue( CTuxCardsConfiguration::B_SHOW_ENTRY_TOOLBAR )  );
  setEditorToolbarVisible( mConfiguration.getBoolValue( CTuxCardsConfiguration::B_SHOW_EDITOR_TOOLBAR ) );


#ifdef DEBUGGING
  // --- add debug mpMainTools"
  std::cout<<"!!! still having debug turned on"<<std::endl;

  Q3ToolBar* debugTools=new Q3ToolBar(this);
  QPixmap debugShowRTFSource=QPixmap(showText_xpm);
  (void) new QToolButton(debugShowRTFSource, "Debug: Shows the RTF-TextSource", 0,
                         this, SLOT(debugShowRTFTextSource()), debugTools);

  QPixmap debugShowXMLCode=QPixmap(xml_xpm);
  (void) new QToolButton(debugShowXMLCode, "Debug: Shows the XML-Representation", 0,
                         this, SLOT(debugShowXMLCode()), debugTools);
#endif
}

// -------------------------------------------------------------------------------
void MainWindow::settingUpQuickLoader( void )
// -------------------------------------------------------------------------------
{
   mpQuickLoader = new Q3ToolBar(this);
   checkPointer( mpQuickLoader );
}


/**
 * Adds the currently active element to the bookmark list.
 */
// -------------------------------------------------------------------------------
void MainWindow::addElementToBookmarksEvent( void )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpCollection )
      return;

   CInformationElement* pElement = mpCollection->getActiveElement();
   if ( NULLPTR == pElement )
      return;

   BookmarkButton* b = new BookmarkButton( QPixmap( pElement->getIconFileName() ),
                                           pElement->getDescription(), mpQuickLoader,
                                           Path( pElement ) );
   connect( b, SIGNAL(activatedSignal(Path*)), this, SLOT(quicklyLoad(Path*)) );
}


// -------------------------------------------------------------------------------
void MainWindow::quicklyLoad(Path* path)
// -------------------------------------------------------------------------------
{
   std::cout<<"load quickly "<<path->toString().toStdString() <<std::endl;
//  save();
//  open();
}


// -------------------------------------------------------------------------------
void MainWindow::changeInformationFormat()
// -------------------------------------------------------------------------------
{
   if ( (NULLPTR == mpCollection) || (NULLPTR == mpEditor) )
      return;

   CInformationElement* pActiveElement = mpCollection->getActiveElement();
   if ( NULLPTR == pActiveElement )
   {
      QMessageBox::information( 0, "Converter", "There is no active entry.",
                                QMessageBox::Abort );
      return;
   }

   if ( pActiveElement->getInformationFormat() == &InformationFormat::RTF)
   {
      QMessageBox::information( 0, "Converter", "Sorry, but converting RTF to ASCII "
                                "is not implemented yet.",
                                QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
      return;
   }

   if (QMessageBox::Cancel == QMessageBox::warning(this, "Converting Information Format",
                                                   "Are you sure to change the information "
                                                   "format.\nSome of the text layout will be lost.",
                                                   QMessageBox::Yes,
                                                   QMessageBox::Cancel,
                                                   QMessageBox::NoButton))
   {
      return;
   }


   // converting
   mpEditor->writeCurrentTextToActiveInformationElement();
   Converter::convert( *pActiveElement );

   mpEditor->setTextFormat( Qt::RichText );
   mpEditor->setText( pActiveElement->getInformation() );

   mpCollection->setActiveElement( pActiveElement );
}



// -------------------------------------------------------------------------------
void MainWindow::showRecognizedFormat(InformationFormat format)
// -------------------------------------------------------------------------------
{
  textFormatTool->setPixmap(format.getPixmap());

  // enabeling rtf-formatting stuff for rtf-information-items only
  bool b = format.equals(InformationFormat::RTF);
  textBoldTool->setEnabled(b);
  textItalicTool->setEnabled(b);
  textUnderTool->setEnabled(b);
  textColorTool->setEnabled(b);

  textLeftTool->setEnabled(b);
  textCenterTool->setEnabled(b);
  textRightTool->setEnabled(b);
  textBlockTool->setEnabled(b);
}



// -------------------------------------------------------------------------------
void MainWindow::textListStyle( int i )
// -------------------------------------------------------------------------------
{
   if ( !mpEditor )
      return;

   if ( i == 0 )
      mpEditor->setParagType( Q3StyleSheetItem::DisplayBlock, Q3StyleSheetItem::ListDisc );
   else if ( i == 1 )
      mpEditor->setParagType( Q3StyleSheetItem::DisplayListItem, Q3StyleSheetItem::ListDisc );
   else if ( i == 2 )
      mpEditor->setParagType( Q3StyleSheetItem::DisplayListItem, Q3StyleSheetItem::ListCircle );
   else if ( i == 3 )
      mpEditor->setParagType( Q3StyleSheetItem::DisplayListItem, Q3StyleSheetItem::ListSquare );
   else if ( i == 4 )
      mpEditor->setParagType( Q3StyleSheetItem::DisplayListItem, Q3StyleSheetItem::ListDecimal );
   else if ( i == 5 )
      mpEditor->setParagType( Q3StyleSheetItem::DisplayListItem, Q3StyleSheetItem::ListLowerAlpha );
   else if ( i == 6 )
      mpEditor->setParagType( Q3StyleSheetItem::DisplayListItem, Q3StyleSheetItem::ListUpperAlpha );

   mpEditor->viewport()->setFocus();
}


// -------------------------------------------------------------------------------
void MainWindow::textFontFamily( const QString &f )
// -------------------------------------------------------------------------------
{
   if ( !mpEditor )
      return;

   mpEditor->setFamily( f );
   mpEditor->viewport()->setFocus();
}

// -------------------------------------------------------------------------------
void MainWindow::textFontSize( const QString &p )
// -------------------------------------------------------------------------------
{
   if ( !mpEditor )
      return;
   mpEditor->setPointSize( p.toInt() );
   mpEditor->viewport()->setFocus();
}


/**
 * whenever the font of the currently edited text within the editor
 * is changed -> the toolbuttons are adjusted
 */
// -------------------------------------------------------------------------------
void MainWindow::textFontChanged(const QFont &f)
// -------------------------------------------------------------------------------
{
  pComboFont->lineEdit()->setText( f.family() );
  pComboSize->lineEdit()->setText( QString::number( f.pointSize() ) );
  textBoldTool->setOn( f.bold() );
  textItalicTool->setOn( f.italic() );
  textUnderTool->setOn( f.underline() );
}

// -------------------------------------------------------------------------------
void MainWindow::textColorChanged(const QColor &c)
// -------------------------------------------------------------------------------
{
  QPixmap pix( getIcon("text_color") );

  QPainter p;
  p.begin(&pix);
  p.fillRect(1,13, 16,4, QColor(c));
  p.end();
  textColorTool->setIconSet(pix);
}

// -------------------------------------------------------------------------------
void MainWindow::textAlignmentChanged(int a)
// -------------------------------------------------------------------------------
{
  //std::cout<<"alignment changed to "<<a<<std::endl;
  textLeftTool->setOn(FALSE);
  textCenterTool->setOn(FALSE);
  textRightTool->setOn(FALSE);
  textBlockTool->setOn(FALSE);

  switch (a){
  case Qt::AlignHCenter:
    textCenterTool->setOn(TRUE);
    //std::cout<<"center"<<std::endl;
    break;
  case Qt::AlignRight:
    textRightTool->setOn(TRUE);
    //std::cout<<"right"<<std::endl;
    break;
  case Qt::AlignJustify:
    textBlockTool->setOn(TRUE);
    //std::cout<<"just"<<std::endl;
    break;
  case Qt::AlignLeft:
  default:
    textLeftTool->setOn(TRUE);
    //std::cout<<"left"<<std::endl;
    break;
  }
}

// -------------------------------------------------------------------------------
void MainWindow::textBold()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpEditor )
      return;

   mpEditor->setBold(textBoldTool->isOn());
}


// -------------------------------------------------------------------------------
void MainWindow::textItalic()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpEditor )
      return;

   mpEditor->setItalic(textItalicTool->isOn());
}


// -------------------------------------------------------------------------------
void MainWindow::textUnder()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpEditor )
      return;

   mpEditor->setUnderline(textUnderTool->isOn());
}


// -------------------------------------------------------------------------------
void MainWindow::textColor()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpEditor )
      return;

   QColor c = QColorDialog::getColor(mpEditor->color(), this);
   if ( !c.isValid() )
      return;
   mpEditor->setColor( c );
   textColorChanged( c );
}


// -------------------------------------------------------------------------------
void MainWindow::textLeft()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpEditor )
      return;

   mpEditor->setAlignment(Qt::AlignLeft);
}
// -------------------------------------------------------------------------------
void MainWindow::textHCenter()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpEditor )
      return;
   mpEditor->setAlignment(Qt::AlignHCenter);
}
// -------------------------------------------------------------------------------
void MainWindow::textRight()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpEditor )
      return;

   mpEditor->setAlignment(Qt::AlignRight);
}
// -------------------------------------------------------------------------------
void MainWindow::textBlock()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpEditor )
      return;

   mpEditor->setAlignment(Qt::AlignJustify);
}



/**
 * checks whether tuxcards runs for the first time with this version
 * if yes -> write new features in file
 */
 // -------------------------------------------------------------------------------
void MainWindow::checkFirstTime()
// -------------------------------------------------------------------------------
{
  QString configurationFileName = QDir::homeDirPath() + "/.tuxcards";

  ConfigParser parser( configurationFileName, FALSE );
  parser.setGroup("General");
  QString version   = parser.readEntry("Version",   "previousVersion");
  // TODO: Check whether this version is correct and does work
  if( version != "TuxCardsV2.0" )
  {
    // write datafile
    QFile file( QDir::homeDirPath() + "/tuxcards_greeting" );
    Q3TextStream* pLog = NULLPTR;

    if( !file.open(QIODevice::WriteOnly) )
    {
      std::cerr<<"TuxCards - cannot write to "<<configurationFileName.toStdString()<<"\n";
    }
    else
    {
      pLog = new Q3TextStream(&file);
      pLog->setEncoding(Q3TextStream::UnicodeUTF8);
    }

    *pLog<<sGreetingsText;

    file.close();
    DELETE( pLog );
  }
}



// -------------------------------------------------------------------------------
void MainWindow::timerEvent(QTimerEvent*)
// -------------------------------------------------------------------------------
{
  //if (AUTOSAVE)
  save();
}



/**
 * show messages via the statusbar
 */
 // -------------------------------------------------------------------------------
void MainWindow::showMessage(QString s, int seconds)
// -------------------------------------------------------------------------------
{
   if ( NULLPTR != mpStatusBar )
      mpStatusBar->message(s, seconds*1000);
}



/**
 * to keep track of changes, put a marker in the statusbar,
 * and update the global variable 'CHANGES' to prevent unnecessary savings
 */
// -------------------------------------------------------------------------------
void MainWindow::recognizeChanges()
// -------------------------------------------------------------------------------
{
  CHANGES=TRUE;
  statusBar_ChangeLabel->setText("*");
}


// respond to menu-calls ----------------------------------------------

// -------------------------------------------------------------------------------
void MainWindow::newFile()
{
	if (PromptBeforeNewFile() != QMessageBox::Yes)
    	return;

	// New files are unencrypted by default.
	mfileEncryptFile->setOn(false);

	clearAll();
}

// -------------------------------------------------------------------------------
void MainWindow::clearAll()
{
	if (mpCollection)
		deleteCollection( mpCollection );
	mpCollection = CInformationCollection::createDefaultCollection();
	initializingCollection("");
}


// -------------------------------------------------------------------------------
int MainWindow::PromptBeforeNewFile()
// -------------------------------------------------------------------------------
{
  int result = QMessageBox::No;

  if ( CHANGES ) {
 		result = askForSaving("Would you like to save the current file?");
  } else {
    result = QMessageBox::warning( this, "New File", "Create New File, closing current one?",
                                   QMessageBox::Yes | QMessageBox::Default,
                                   QMessageBox::No | QMessageBox::Escape);
  }

  return result;
}

// -------------------------------------------------------------------------------
int MainWindow::askForSaving(QString question)
// -------------------------------------------------------------------------------
{
  int result = QMessageBox::Yes;
  if ( CHANGES ){
    result = QMessageBox::warning( this, "Save", question,
                                   QMessageBox::Yes | QMessageBox::Default, QMessageBox::No,
                                   QMessageBox::Cancel | QMessageBox::Escape);
    if (result==QMessageBox::Yes)
      save();
    else  // Over-write no as we did not save
        if (result==QMessageBox::No)
            result = QMessageBox::Yes;
  }

  return result;
}



/**
 * Before calling this method the informationCollection 'mpCollection'
 * must be valid !!!
 */
// -------------------------------------------------------------------------------
bool MainWindow::initializingCollection( QString collectionName )
// -------------------------------------------------------------------------------
{
   if ( (NULLPTR == mpCollection) || (NULLPTR == mpSingleEntryView) ) {
   		std::cout<<"MainWindow::initializingCollection returning due to null"<<std::endl;
      return false;
   }

   checkPointer( mpTree );

	if (mpCollection->isEncrypted()) {
		bool bCorrectPasswd = false;
        int wrongPassCount=0;
        const int WRONG_PASS_MAX_COUNT=3;

		mfileEncryptFile->setOn(true);
		// Continue to ask for valid password, on cancel, open an empty collection
		do {
			// Ask for password here.
		   CFileEncryptionPasswordDialog fileEncryptionPasswordDialog( this );
		   fileEncryptionPasswordDialog.setUp(collectionName);

	   		// If cancel are pressed, do not use this collection.
	   		if (fileEncryptionPasswordDialog.getPasswd().isEmpty()) {
	   			// mpTree will be deleted when the empty collection is loaded.
	   			return false;
	   		}

		   bCorrectPasswd = mpCollection->decryptTree(fileEncryptionPasswordDialog.getPasswd());
           if (!bCorrectPasswd) {
               wrongPassCount++;
               if (wrongPassCount >= WRONG_PASS_MAX_COUNT) {
                   QMessageBox::warning(this, "TuxCards", "Too many password attempts",
                         QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
                   return false;
               }

           }

		} while (!bCorrectPasswd);

		mstatusBar_EncryptedLabel->setPixmap(getIcon("unlocksm"));

	} else {
		mfileEncryptFile->setOn(false);
		mstatusBar_EncryptedLabel->clear();
	}

   mpTree->createTreeFromCollection( *mpCollection );

   connect( mpCollection,      SIGNAL(activeInformationElementChanged(CInformationElement*)),
            mpSingleEntryView, SLOT(activeInformationElementChanged(CInformationElement*)) );
   connect( mpCollection,      SIGNAL(activeInformationElementChanged(CInformationElement*)),
            this,              SLOT(activeInformationElementChanged(CInformationElement*)) );
   connect( mpCollection,      SIGNAL(modelHasChanged()), this, SLOT(recognizeChanges()) );
   connect( mpCollection,      SIGNAL(numElementsChanged(int)), this, SLOT(updateStatusbarElements(int)) );

   if ( NULLPTR != mpEditor )
      mpEditor->clear();

   // collection successfully created and system set up with it
   // !!! if using a windows-system: this might not work since '/' not in path
   int i=collectionName.findRev('/');
   if (i>-1)
      mpTree->setColumnText(collectionName.mid(i+1));
   else
      mpTree->setColumnText(collectionName);

	updateStatusbarElements(mpCollection->numElements());

   selectLastActiveElement();

   mpCollection->addView( &mHistory );
   mpCollection->addView( mpTree );
   mpCollection->addView( mpSingleEntryView );

   setCaption("TuxCards (" + collectionName + ")");

   mConfiguration.setStringValue( CTuxCardsConfiguration::S_DATA_FILE_NAME, collectionName );
   mConfiguration.saveToFile();                    // because the dataFileName has changed

   statusBar_ChangeLabel->setText(" ");
   CHANGES=FALSE;
   return true;
}

// -------------------------------------------------------------------------------
void MainWindow::deleteCollection(CInformationCollection* collection)
{
	if (!collection)
		return;

	disconnect( collection, SIGNAL(numElementsChanged(int)), this, SLOT(updateStatusbarElements(int)) );
	DELETE( collection );
}


// -------------------------------------------------------------------------------
CInformationElement* MainWindow::getActiveIE()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpCollection )
      return NULLPTR;

   return mpCollection->getActiveElement();
}




/**
 * adapter for 'open(QString h)'
 */
// -------------------------------------------------------------------------------
void MainWindow::open()
// -------------------------------------------------------------------------------
{
  // give a chance to save the file before opening another one
  if (askForSaving("Do you want to save the current file before opening another?") == QMessageBox::Cancel)
    return;

  // getting dataFileName
  QString fileName( Q3FileDialog::getOpenFileName() );
  if ( fileName.isNull() || fileName=="" )
    showMessage("No Filename specified.", 5);
  else
    open(fileName);
}



/**
 * Returns TRUE, if file was opened successfully; otherwise FALSE.
 */
// -------------------------------------------------------------------------------
bool MainWindow::open( QString fileName )
// -------------------------------------------------------------------------------
{
   bool retVal = FALSE;

   int format = getDataFileFormat(fileName);

   if ( format == 2 )
      retVal = openXMLDataFile(fileName);
   else if ( format == 1 )
      retVal = openOldDataFile(fileName);
   else
   {
      QMessageBox::critical(	this, "Opening a data file",
            "Could not open file '"+fileName+"'<br> or did not "
            "recognize the dataformat.",
            "Ok");
   }

   if (retVal)
   {
      if ( NULLPTR != mpRecentFiles )
         mpRecentFiles->setOnTop(fileName);
   } else {
		// Can fail for encrypted files (incorrect password.) or bad xml data.
		// Open an empty new file in that case.
		clearAll();
   }

   return retVal;
}



/**
 * Opens a file and detects the fileformat.
 *     i.e. '2' == XML-File (the new TuxCards format)
 *          '1' == Old-File (the old TuxCards format, that was used since version 0.5)
 *          '0' == unknown format
 */
// -------------------------------------------------------------------------------
int MainWindow::getDataFileFormat(QString fileName)
// -------------------------------------------------------------------------------
{
  QFile file(fileName);
  if ( !file.open(QIODevice::ReadOnly) ) {
    //showMessage("ERROR could not open '"+fileName+"' for reading.", 5);
    return 0;
  }


  Q3TextStream t( &file );
  QString line=t.readLine();
  //cout<<"readLine="<<line<<endl;
  file.close();

  if (line.startsWith("TuxCardsV0.5"))
    return 1;
  else if (line.startsWith("<?xml"))
    return 2;

  return 0;
}



/**
 * Opens a file given by a valid name ('fileName'), creates an
 * informationcollection from it & sets latter one to be presented
 * within tuxcards.
 *
 * Returns TRUE, if file was opend successfully; otherwise FALSE.
 */
// -------------------------------------------------------------------------------
bool MainWindow::openOldDataFile(QString fileName)
// -------------------------------------------------------------------------------
{
  QFile file(fileName);
  bool retval;

  if (! file.open(QIODevice::ReadOnly) ) {
    showMessage("ERROR could not open '"+fileName+"' for reading.", 5);
    return FALSE;
  }

  // create absolute file name, in case a relative one is given
  fileName = QFileInfo(fileName).absFilePath();


  QString s="";
  Q3TextStream t( &file );               // use a text stream
  while ( !t.eof() ) {
    s += QChar((char)10) + t.readLine();// the first chr(10) is wrong, but doesn't matter
  }
  file.close();
  s=s.mid(1);                           // remove wrong chr(10) from beginning

  deleteCollection( mpCollection);
  mpCollection = Persister::createInformationCollection( s );
  retval = initializingCollection( fileName );
  // On failure, mpCollection will be deleted when the empty collection is loaded.

  return retval;
}



/**
 * Opens a file given by a valid name ('fileName'), creates an
 * informationcollection from it & sets latter one to be presented
 * within tuxcards.
 *
 * Returns TRUE, if file was opend successfully; otherwise FALSE.
 */
// -------------------------------------------------------------------------------
bool MainWindow::openXMLDataFile(QString fileName)
// -------------------------------------------------------------------------------
{
  bool retval;

  // create absolute file name, in case a relative one is given
  fileName = QFileInfo(fileName).absFilePath();

  deleteCollection( mpCollection );

  QFile file(fileName);
  mpCollection = XMLPersister::createInformationCollection( file );

  if ( !mpCollection )
  {
    QMessageBox::warning(this, "TuxCards - XML I/O",
                         "ERROR could not open '"+fileName+"' for reading or parse error.",
                         QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
    return FALSE;
  }

  retval = initializingCollection( fileName );
  // On failure, mpCollection will be deleted when the empty collection is loaded.

  return retval;
}

// When opening a new file, if current file is dirty, ask for it to be saved.
// -------------------------------------------------------------------------------
void MainWindow::slotSaveAndLoadNewFile(QString newFile)
{
	if (askForSaving("Would you like to save the current file?") == QMessageBox::Cancel)
    	return;

	open(newFile);

}


/**
 * Reads the last active element from the configuration file and selects it.
 * Also, the position of the vertical scrollbar within the tree is restored.
 */
// -------------------------------------------------------------------------------
void MainWindow::selectLastActiveElement()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpCollection )
      return;


   //Path path(mConfiguration.getStringValue( CTuxCardsConfiguration::S_LAST_ACTIVE_ELEM_PATH ));
   Path path( XMLPersister::getPathOfLastActiveElement() );
   //std::cout<<"Path = "<<path.toString()<<std::endl;

   if ( mpCollection->isPathValid(path) )
   {
      //std::cout<<"Path is valid"<<std::endl;
      mpCollection->setActiveElement( path );
   } else {
      //std::cout<<"Path is invalid"<<std::endl;
      mpCollection->setActiveElement( mpCollection->getRootElement() );
   }

   mpTree->verticalScrollBar()->setValue(
      mConfiguration.getIntValue( CTuxCardsConfiguration::I_TREE_VSCROLLBAR_VALUE ) );
}


// -------------------------------------------------------------------------------
void MainWindow::save()
// -------------------------------------------------------------------------------
{
  if (mConfiguration.getStringValue( CTuxCardsConfiguration::S_DATA_FILE_NAME ) == "")
  {
    saveAs();
  }
  else
  {
    save(mConfiguration.getStringValue( CTuxCardsConfiguration::S_DATA_FILE_NAME ));
  }
}


// -------------------------------------------------------------------------------
void MainWindow::saveAs()
// -------------------------------------------------------------------------------
{
   QString newFileName( Q3FileDialog::getSaveFileName() );
   if ( newFileName.isNull() || newFileName=="" )
   {
      showMessage("No Filename specified.", 5);
      return;
   }

   save(newFileName);

   if ( NULLPTR != mpRecentFiles )
   {
      mpRecentFiles->setOnTop(newFileName);
   }

   mConfiguration.setStringValue( CTuxCardsConfiguration::S_DATA_FILE_NAME, newFileName );
   mConfiguration.saveToFile();
}


// -------------------------------------------------------------------------------
void MainWindow::save(QString fileName)
// -------------------------------------------------------------------------------
{
   if ( (NULLPTR == mpCollection) || (NULLPTR == mpEditor) )
      return;

   if ( (QDir::homeDirPath() + TUX_CONFIG_FILE) == fileName )
   {
      QMessageBox::warning( this, "Saving", "File not saved.\n"
                            "Please do not use \"" + fileName +"\""
                            " as file name.",
                            QMessageBox::Abort, NULL );
      return;
   }

   // before saving -> move current file i.e. "myfile.data" to "myfile.data~"
   if ( mConfiguration.getBoolValue( CTuxCardsConfiguration::B_CREATE_BACKUP_FILE ) )
   {
      QDir tmp;
      QString sFileName = mConfiguration.getStringValue( CTuxCardsConfiguration::S_DATA_FILE_NAME );
      tmp.rename( sFileName, sFileName + "~" );
   }

   // saving eventual changes
   mpEditor->writeCurrentTextToActiveInformationElement();
   XMLPersister::save( *mpCollection, fileName );


   int i=fileName.findRev('/');
   if (i>-1)
      mpTree->setColumnText(fileName.mid(i+1));
   else
      mpTree->setColumnText(fileName);

   setCaption("TuxCards (" + fileName + ")");

   mConfiguration.setStringValue( CTuxCardsConfiguration::S_DATA_FILE_NAME, fileName );
   mConfiguration.saveToFile();

   statusBar_ChangeLabel->setText(" ");
   CHANGES=FALSE;
   showMessage("Saved to '" + fileName + "'.", 5);

   callingExecutionStatement();
}


// -------------------------------------------------------------------------------
void MainWindow::callingExecutionStatement()
// -------------------------------------------------------------------------------
{
	QString execStatement = mConfiguration.getStringValue( CTuxCardsConfiguration::S_EXECUTE_STATEMENT );
	if (execStatement.size() > 0)
		system( execStatement.ascii() );
}


// Toggles encrption for current file
// -------------------------------------------------------------------------------
void MainWindow::toggleFileEncryption()
{
	QString strPassword("");

	if ( NULLPTR == mpCollection )
		return;

	// Check current state of encryption before changing it
	if (mpCollection->isEncrypted()) {

		// Confirm decryption
		if (QMessageBox::Cancel == QMessageBox::warning(this, "Tuxcards File Encryption",
													"About to remove encryption for current"
                                                   " file.\n Would you like to continue?",
                                                   QMessageBox::Ok,
                                                   QMessageBox::Cancel,
                                                   QMessageBox::NoButton))
	   {
            // Reset toggle to on.
			mfileEncryptFile->setOn(true);
    	  	return;
	   }

		mfileEncryptFile->setOn(false);
		mstatusBar_EncryptedLabel->clear();
	}
	else {
		// Confirm with user before going ahead
	   int iUseEncryption = mConfiguration.askForUsingEncryption();
		// User decided not to go ahead
		if(!iUseEncryption) {
	    	mfileEncryptFile->setOn(false);
			return;
		}

		// Request user for password to use for encryption
		mPasswdDialog.setUp( "Current file");
		strPassword = mPasswdDialog.getPasswd();
	    if (strPassword.isEmpty() ) {
	    	mfileEncryptFile->setOn(false);
	    	return;
	    }

		mstatusBar_EncryptedLabel->setPixmap(getIcon("unlocksm"));
	}

	mpCollection->toggleEncryption(strPassword);
	recognizeChanges();

}

/**
 * opens the current file from disk and exports it to
 */
// -------------------------------------------------------------------------------
void MainWindow::exportHTML()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpCollection )
      return;

   QString dirPath = Q3FileDialog::getExistingDirectory(
                               QDir::homeDirPath(),
                               this,
                               "get existing directory",
                               "Choose a directory",
                               TRUE );

   if ( dirPath.isEmpty() )
      return;

   bool bSuccess = HTMLWriter::writeCollectionToHTMLFile( *mpCollection, dirPath );

   // done
   if ( FALSE != bSuccess )
   {
      QMessageBox::information( this, "HTML-Export", "HTML<em>Export</em> "
                                "<font size=-1>(" + QString(TUX_VERSION) + ")</font>"
                                " finished, successfully.\n\n"
                                "The data are stored in\n"+dirPath, 1);
   }
   else
   {
      QMessageBox::warning( this, "HTML-Export", "HTML<em>Export</em> "
                            "<font size=-1>(" + QString(TUX_VERSION) + ")</font>"
                            " not successfully.\n\n"
                            "Please check write permission and disk space\n"
                            "(" + dirPath + ")", "Abort");
   }
}


// -------------------------------------------------------------------------------
void MainWindow::keyPressEvent(QKeyEvent* k)
// -------------------------------------------------------------------------------
{
   if ( !k || !mpTree || !mpSingleEntryView )
      return;

   switch( k->state() )
   {
   case Qt::ControlButton:
      //cout<<"CTL + "<<k->ascii()<<"\ttext="<<k->text()<<"\tkey="<<k->key()<<endl;
      if (k->key() == Qt::Key_S)
         save();
      else if ( (Qt::ControlButton == k->state())  &&  (Qt::Key_F == k->key()) )
         search();
      break;

   case Qt::AltButton:
      if ( k->key() == Qt::Key_Left )
         activatePreviousHistoryElement();
      else if ( k->key() == Qt::Key_Right )
         activateNextHistoryElement();
      break;

   default:
      if ( Qt::Key_F5 == k->key() )
      {
         if ( mpEditor->hasFocus() )
            mpTree->setFocus();
         else
            mpEditor->setFocus();
      }
      else
         k->ignore();
      break;
  }
}


// -------------------------------------------------------------------------------
void MainWindow::exit()
// -------------------------------------------------------------------------------
{
  close();                      // calls 'closeEvent(..)' indirectly
}


// -------------------------------------------------------------------------------
void MainWindow::wordCount( void )
// -------------------------------------------------------------------------------
{
   if ( (NULLPTR == mpCollection) || (NULLPTR == mpEditor) )
      return;

   mpEditor->writeCurrentTextToActiveInformationElement();
   CInformationElement* pActiveElement = mpCollection->getActiveElement();
   if ( NULLPTR == pActiveElement )
   {
      QMessageBox::information( 0, "WordCount", "There is no active entry.",
                                QMessageBox::Abort );
      return;
   }

   QString text = pActiveElement->getInformationText();
   //std::cout<<text<<std::endl;
   int numchar  = text.length();
   int words  = Strings::wordCount( text );
   int lines  = mpEditor->lines();
   int parags = mpEditor->paragraphs();

   QMessageBox::information( this, "TuxCards",
                    "<center>Current Entry contains<br><br>"
                    +QString::number(numchar) + (numchar > 1 ? " characters<br>" : " character<br>")
                    +QString::number(words)
                    +(words > 1 ? " words<br>" : " word<br>")
                    +QString::number(lines)  + (lines  > 1 ? " lines<br>" : " line<br>" )
                    +QString::number(parags) + (parags > 1 ? " paragraphs" : " paragraph" )
                    +".</center>");
}

// -------------------------------------------------------------------------------
void MainWindow::insertCurrentDate( void )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR != mpEditor )
      mpEditor->insert( QDate::currentDate().toString() );
}

// -------------------------------------------------------------------------------
void MainWindow::insertCurrentTime()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR != mpEditor )
      mpEditor->insert( QTime::currentTime().toString() );
}

// -------------------------------------------------------------------------------
void MainWindow::showKBShortcuts()
// -------------------------------------------------------------------------------
{
   QMessageBox::about(  this, "TuxCards",
                    "TuxCards Keyboard shortcuts\n\n"

					"Common shortcuts:\n"
					"Qt::CTRL+N: New File\n"
					"Qt::CTRL+O: Open File\n"
					"Qt::CTRL+S: Save current file\n"
					"Qt::CTRL+E: Encrypt current file\n"
					"Qt::CTRL+F: Search\n"
					"F5: Switch between tree(left pane) and editor window(right pane)\n"
					"Alt+Left or Right arrow: Navigate items accessed earlier(history)\n"
					"MENU (Left of right Qt::CTRL key): Show current context menu\n"
					"Qt::CTRL+W:Word count, Qt::CTRL+D: Date insertion, Qt::CTRL+T: Time insertion\n\n"

					"Tree (Left pane) shortcuts:\n"
					"F2: Edit current entry title\n"
					"INS: Add a new entry\n"
					"DEL: Delete current entry\n\n"

					"Editor (Right pane) shortcuts:\n"
					"Qt::CTRL+X: Cut, Qt::CTRL+C: Copy, Qt::CTRL+V: Paste\n"
					"Qt::CTRL+Z: Undo, Qt::CTRL+Y: Redo\n"
					"Qt::CTRL+K: Delete till end of current line\n"
					"Qt::CTRL+B: Bold, Qt::CTRL+I: Italic, Qt::CTRL+U: Underline, Qt::CTRL+A: Select all\n"
                    );
}

// -------------------------------------------------------------------------------
void MainWindow::showAbout()
// -------------------------------------------------------------------------------
{
   QMessageBox::about(  this, "TuxCards",
                    "TuxCards - The Notebook for Linux\n"
                    +QString(TUX_VERSION)+"\n\n"
                    "Copyright (c) 2006-2009 Amit Chaudhary\n"
                    "amitch@rajgad.com\n"
                    "Copyright (c) 2007 Yahoo! Inc.\n"
                    "Copyright (c) 2000-2004 Alexander Theel\n"
                    "alex.theel@gmx.net\n");
}

/**
 * saves the data automatically by closing/quitting the program
 */
// -------------------------------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent *e)
// -------------------------------------------------------------------------------
{
   // accept signal
   e->accept();                  // default implementation of this method


   // we always save the options; the splitter-size may have changed
   if ( NULLPTR != mpCollection )
   {
      Path path( mpCollection->getActiveElement() );
      mConfiguration.setStringValue( CTuxCardsConfiguration::S_LAST_ACTIVE_ELEM_PATH, path.toString() );
   }
   mConfiguration.setIntValue( CTuxCardsConfiguration::I_TREE_VSCROLLBAR_VALUE, mpTree->verticalScrollBar()->value());

   mConfiguration.setIntValue( CTuxCardsConfiguration::I_WINDOW_WIDTH, width() );
   mConfiguration.setIntValue( CTuxCardsConfiguration::I_WINDOW_HEIGHT, height() );
   mConfiguration.setIntValue( CTuxCardsConfiguration::I_TREE_WIDTH,  mpSplit->sizes().first() );
   mConfiguration.setIntValue( CTuxCardsConfiguration::I_EDITOR_WIDTH, mpSplit->sizes().last() );

   if ( NULLPTR != mpRecentFiles )
   {
      mConfiguration.setStringValue( CTuxCardsConfiguration::S_RECENT_FILES, mpRecentFiles->toString() );
   }
   mConfiguration.saveToFile();


   if (!CHANGES)
      return;

   if ( mConfiguration.getBoolValue( CTuxCardsConfiguration::B_SAVE_WHEN_LEAVING )
       || (QMessageBox::warning(  this, "Save before exiting.",
                                  "Do you want to save before leaving TuxCards?",
                                  "Yes", "No") == 0) )
   {
      showDialog->show();
      save();
      showDialog->hide();
   }
}


// -------------------------------------------------------------------------------
void MainWindow::toggleMainToolbarVisability()
// -------------------------------------------------------------------------------
{
   bool bValue = mConfiguration.getBoolValue( CTuxCardsConfiguration::B_SHOW_MAIN_TOOLBAR );
   bValue = !bValue;

   setMainToolbarVisible( bValue );
   mConfiguration.saveToFile();
}
// -------------------------------------------------------------------------------
void MainWindow::setMainToolbarVisible( bool bVisible )
// -------------------------------------------------------------------------------
{
   mConfiguration.setBoolValue( CTuxCardsConfiguration::B_SHOW_MAIN_TOOLBAR, bVisible );

   if ( mpMainTools )
   {
      if (bVisible) mpMainTools->show();
      else mpMainTools->hide();
   }
   if ( mpMenu ) mpMenu->setItemChecked( miMainToolBarID, bVisible );
}


// -------------------------------------------------------------------------------
void MainWindow::toggleEntryToolbarVisability()
// -------------------------------------------------------------------------------
{
   bool bValue = mConfiguration.getBoolValue( CTuxCardsConfiguration::B_SHOW_ENTRY_TOOLBAR );
   bValue = !bValue;

   setEntryToolbarVisible( bValue );
   mConfiguration.saveToFile();
}
// -------------------------------------------------------------------------------
void MainWindow::setEntryToolbarVisible( bool bVisible )
// -------------------------------------------------------------------------------
{
   mConfiguration.setBoolValue( CTuxCardsConfiguration::B_SHOW_ENTRY_TOOLBAR, bVisible );

   if ( mpEntryTools )
   {
      if (bVisible) mpEntryTools->show();
      else mpEntryTools->hide();
   }
   if ( mpMenu ) mpMenu->setItemChecked( miEntryToolBarID, bVisible );
}

// -------------------------------------------------------------------------------
void MainWindow::toggleEditorToolbarVisability()
// -------------------------------------------------------------------------------
{
   bool bValue = mConfiguration.getBoolValue( CTuxCardsConfiguration::B_SHOW_EDITOR_TOOLBAR );
   bValue = !bValue;

   setEditorToolbarVisible( bValue );
   mConfiguration.saveToFile();
}
// -------------------------------------------------------------------------------
void MainWindow::setEditorToolbarVisible( bool bVisible )
// -------------------------------------------------------------------------------
{
   mConfiguration.setBoolValue( CTuxCardsConfiguration::B_SHOW_EDITOR_TOOLBAR, bVisible );

   if ( mpEditorTools )
   {
      if (bVisible) mpEditorTools->show();
      else mpEditorTools->hide();
   }
   if ( mpMenu ) mpMenu->setItemChecked( miEditorToolBarID, bVisible );
}

// -------------------------------------------------------------------------------
void MainWindow::editConfiguration( void )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpOptionsDialog )
      return;

   mpOptionsDialog->setUp();
}


// -------------------------------------------------------------------------------
void MainWindow::applyConfigurationMain()
// -------------------------------------------------------------------------------
{
	applyConfiguration();
	startAutosaveTimer();
}

// -------------------------------------------------------------------------------
void MainWindow::applyConfiguration()
// -------------------------------------------------------------------------------
{
   // editor
   if ( NULLPTR != mpEditor )
   {
      QFont font = mConfiguration.getASCIIEditorFont().toFont();
      mpEditor->setFont(font);
      mpEditor->setTabStopWidth( mConfiguration.getIntValue( CTuxCardsConfiguration::I_TAB_SIZE ) * QFontMetrics(font).width('X') );
      mpEditor->setWordWrap( mConfiguration.getIntValue( CTuxCardsConfiguration::I_WORD_WRAP ) );
   }

   // tree
   mpTree->setFont( mConfiguration.getTreeFont().toFont() );

   // windowsize & splitter
   setWindowGeometry( mConfiguration.getIntValue( CTuxCardsConfiguration::I_WINDOW_WIDTH ),
                      mConfiguration.getIntValue( CTuxCardsConfiguration::I_WINDOW_HEIGHT ),
                      mConfiguration.getIntValue( CTuxCardsConfiguration::I_TREE_WIDTH ),
                      mConfiguration.getIntValue( CTuxCardsConfiguration::I_EDITOR_WIDTH )
                    );
}

// -------------------------------------------------------------------------------
void MainWindow::startAutosaveTimer()
// -------------------------------------------------------------------------------
{
	 // autosave
   killTimer(TIMER_ID);
   if ( mConfiguration.getBoolValue( CTuxCardsConfiguration::B_AUTOSAVE ) )
      TIMER_ID=startTimer( 60000 * mConfiguration.getIntValue( CTuxCardsConfiguration::I_SAVE_ALL_MINUTES ) );
}


// -------------------------------------------------------------------------------
void MainWindow::setWindowGeometry( int windowWidth, int windowHeight,
                                    int treeSize,    int editorSize )
// -------------------------------------------------------------------------------
{
  resize(windowWidth, windowHeight);

  lst = new Q3ValueList<int>();
  lst->append(treeSize);
  lst->append(editorSize);
  mpSplit->setSizes( *lst );
}


// -------------------------------------------------------------------------------
void MainWindow::search()
// -------------------------------------------------------------------------------
{
   if ( (NULLPTR == mpEditor) || (NULLPTR == mpTree) )
      return;

   mpEditor->writeCurrentTextToActiveInformationElement();
   mpTree->search();
}

// -------------------------------------------------------------------------------
void MainWindow::print()
// -------------------------------------------------------------------------------
{
   if ( (NULLPTR == mpCollection) || (NULLPTR == mpCollection->getActiveElement()) )
      return;

   if ( mpCollection->getActiveElement()->getInformationFormat() == &InformationFormat::ASCII )
   {
      QMessageBox::information( this, "Printing", "Please consider converting this note to "
                               "rtf before printing.", "Ok" );
   }

   if ( NULLPTR == mpEditor )
      return;


  mpEditor->writeCurrentTextToActiveInformationElement();
#ifndef QT_NO_PRINTER
  QPrinter printer;
  printer.setFullPage(TRUE);
  if ( printer.setup( this ) ) {
    QPainter p( &printer );
    // Check that there is a valid device to print to.
    if ( !p.device() ) return;
    Q3PaintDeviceMetrics metrics( p.device() );
    int dpix = metrics.logicalDpiX();
    int dpiy = metrics.logicalDpiY();
    const int margin = 72; // pt
    QRect body( margin * dpix / 72, margin * dpiy / 72,
                metrics.width()  - margin * dpix / 72 * 2,
                metrics.height() - margin * dpiy / 72 * 2 );
    QFont font( mConfiguration.getASCIIEditorFont().toFont() );
    font.setPointSize( 10 ); // we define 10pt to be a nice base size for printing
    Q3SimpleRichText richText( mpCollection->getActiveElement()->getInformation(), font,
                              mpEditor->context(),
                              mpEditor->styleSheet(),
                              mpEditor->mimeSourceFactory(),
                              body.height() );
    richText.setWidth( &p, body.width() );
    QRect view( body );
    int page = 1;
    do{
      richText.draw( &p, body.left(), body.top(), view, colorGroup() );
      view.moveBy( 0, body.height() );
      p.translate( 0 , -body.height() );
      p.setFont( font );
      p.drawText( view.right() - p.fontMetrics().width( QString::number( page ) ),
      view.bottom() + p.fontMetrics().ascent() + 5, QString::number( page ) );
      if ( view.top()  >= body.top() + richText.height() )
        break;
      printer.newPage();
      page++;
    }while (TRUE);
  }
#endif
}

// -------------------------------------------------------------------------------
void MainWindow::makeVisible( SearchPosition* pPosition )
// -------------------------------------------------------------------------------
{
   if ( (NULLPTR == mpCollection) || (NULLPTR == pPosition) || (NULLPTR == mpEditor) )
      return;

   mpCollection->setActiveElement( *(pPosition->getPath()) );

   int paragraph = pPosition->getLine();
   int pos = pPosition->getPos();
   int len = pPosition->getLen();

   this->setActiveWindow();
   mpEditor->setSelection(paragraph,pos, paragraph,pos+len, 0);
//    qDebug ("MainWindows.makeVisible: para %d pos %d len %d\n",
//		paragraph, pos, len);
   
   mpEditor->setFocus();
   mpEditor->setCursorPosition(paragraph, pos+len);
   mpEditor->ensureCursorVisible();
}

// -------------------------------------------------------------------------------
void MainWindow::moveElementUp()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpCollection )
      return;

   if ( NULLPTR == mpCollection->getActiveElement() )
      return;


   ((CTreeInformationElement*) mpCollection->getActiveElement())->moveOneUp();
}

// -------------------------------------------------------------------------------
void MainWindow::moveElementDown()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpCollection )
      return;

   if ( NULLPTR == mpCollection->getActiveElement() )
      return;


   ((CTreeInformationElement*) mpCollection->getActiveElement())->moveOneDown();
}



/*********************** debug methods **********************************/
// -------------------------------------------------------------------------------
void MainWindow::debugShowRTFTextSource()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpEditor )
      return;

   Q3TextEdit* outputWindow=new Q3TextEdit();
   outputWindow->resize(400,400);
   outputWindow->setTextFormat(Qt::PlainText);
   outputWindow->setText(mpEditor->getText());
   outputWindow->show();
}


// -------------------------------------------------------------------------------
void MainWindow::debugShowXMLCode()
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpCollection )
      return;

   Q3TextEdit* outputWindow=new Q3TextEdit();
   outputWindow->resize(400,400);
   outputWindow->setTextFormat(Qt::PlainText);
   outputWindow->setText(mpCollection->toXML());
   outputWindow->show();
}

// -------------------------------------------------------------------------------
void MainWindow::updateStatusbarElements(int numElements)
{
	QString strNumElements = QString("Notes: %1").arg(numElements);
	mstatusBar_NumElements->setText(strNumElements);
}
