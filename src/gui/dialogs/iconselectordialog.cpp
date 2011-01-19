/****************************************************************************
** $Id: qt/examples/fileiconview/mainwindow.cpp   2.3.0   edited 2001-01-26 $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#include "iconselector.h"
#include "iconselectordialog.h"
//#include "../dirview/dirview.h"

#include <qsplitter.h>
#include <q3progressbar.h>
#include <qlabel.h>
#include <qstatusbar.h>
#include <q3toolbar.h>
#include <qcombobox.h>
#include <qpixmap.h>
#include <qtoolbutton.h>
#include <qdir.h>
#include <qfileinfo.h>

#include <q3vbox.h>
#include <qpushbutton.h>
//Added by qt3to4:
#include <Q3Frame>
#include <iostream>

static const char* cdtoparent_xpm[]={
    "15 13 3 1",
    ". c None",
    "* c #000000",
    "a c #ffff99",
    "..*****........",
    ".*aaaaa*.......",
    "***************",
    "*aaaaaaaaaaaaa*",
    "*aaaa*aaaaaaaa*",
    "*aaa***aaaaaaa*",
    "*aa*****aaaaaa*",
    "*aaaa*aaaaaaaa*",
    "*aaaa*aaaaaaaa*",
    "*aaaa******aaa*",
    "*aaaaaaaaaaaaa*",
    "*aaaaaaaaaaaaa*",
    "***************"};

IconSelectorDialog::IconSelectorDialog()
 :QDialog(0, "name", true){

	setup();
}

void IconSelectorDialog::show(){
	QDialog::show();
}

void IconSelectorDialog::setup()
{
//  QSplitter *splitter = new QSplitter( this );
//
//  dirlist = new DirectoryView( splitter, "dirlist", TRUE );
//  dirlist->addColumn( "Name" );
//  dirlist->addColumn( "Type" );
//  Directory *root = new Directory( dirlist, "/" );
//  root->setOpen( TRUE );
//  splitter->setResizeMode( dirlist, QSplitter::KeepSize );

	Q3VBox* layout=new Q3VBox(this);
	layout->setMinimumSize(400,400);	
	
	// upper-section
	Q3HBox* upperLayout=new Q3HBox(layout);
  QLabel* pathLabel=new QLabel( tr( " Path: " ), upperLayout);
  pathLabel->setMaximumWidth(35);


  pathCombo=new QComboBox(TRUE, upperLayout);
  pathCombo->setAutoCompletion(TRUE);
//  toolbar->setStretchableWidget( pathCombo );
  connect(pathCombo, SIGNAL( activated( const QString & ) ),
     this, SLOT ( changePath( const QString & ) ) );
//  toolbar->addSeparator();
  QPixmap pix;
  pix = QPixmap( cdtoparent_xpm );
  upButton = new QPushButton( pix, "",upperLayout);
  upButton->setMaximumWidth(26);
  connect(upButton, SIGNAL(pressed()), this, SLOT(cdUp()));
	
	// middle-section
	fileview = new IconSelector("/", layout);
  fileview->setSelectionMode(Q3IconView::Extended);
  fileview->setDirectory(QDir::current());

  location=new QLabel("", layout);
	location->setFrameStyle(Q3Frame::Box | Q3Frame::Raised);
	
	// lower-section
	Q3HBox* lowerLayout=new Q3HBox(layout);
	QPushButton* ok    =new QPushButton("Ok",     lowerLayout);
	connect(ok, SIGNAL(released()), this, SLOT(slotOkPressed()));	
	QPushButton* cancel=new QPushButton("Cancel", lowerLayout);
	connect(cancel, SIGNAL(released()), this, SLOT(slotCancelPressed()));

//  QToolBar *toolbar = new QToolBar( this, "toolbar" );
//  setRightJustification( TRUE );


//  pix = QPixmap( newfolder_xpm );
//  mkdirButton = new QToolButton( pix, "New Folder", QString::null,
//			   this, SLOT( newFolder() ), toolbar, "new folder" );

//  connect( dirlist, SIGNAL( folderSelected( const QString & ) ),
//     fileview, SLOT ( setDirectory( const QString & ) ) );
  connect( fileview, SIGNAL( directoryChanged( const QString & ) ),
    this, SLOT( directoryChanged( const QString & ) ) );
  connect( fileview, SIGNAL( startReadDir( int ) ),
    this, SLOT( slotStartReadDir( int ) ) );
  connect( fileview, SIGNAL( readNextDir() ),
    this, SLOT( slotReadNextDir() ) );
  connect( fileview, SIGNAL( readDirDone() ),
    this, SLOT( slotReadDirDone() ) );
  connect(fileview, SIGNAL(pressed(Q3IconViewItem*)),
  	this, SLOT(slotFileSelected(Q3IconViewItem*)));

//  setDockEnabled( Left, FALSE );
//  setDockEnabled( Right, FALSE );

//  label = new QLabel( statusBar() );
//  statusBar()->addWidget( label, 2, TRUE );
  progress = new Q3ProgressBar(layout);
//  statusBar()->addWidget( progress, 1, TRUE );

  connect( fileview, SIGNAL( enableUp() ),
     this, SLOT( enableUp() ) );
  connect( fileview, SIGNAL( disableUp() ),
     this, SLOT( disableUp() ) );
//  connect( fileview, SIGNAL( enableMkdir() ),
//     this, SLOT( enableMkdir() ) );
//  connect( fileview, SIGNAL( disableMkdir() ),
//     this, SLOT( disableMkdir() ) );

	directoryChanged(QDir::current().absPath());
	
	
}

void IconSelectorDialog::slotOkPressed(){
	accept();
}

void IconSelectorDialog::slotCancelPressed(){
	reject();
}

QString IconSelectorDialog::getIconFileName(){
	if(location->text()=="")						// i.e. no file was selected
		return "";
	else
		return pathCombo->currentText() +"/"+ location->text();
}

void IconSelectorDialog::slotFileSelected(Q3IconViewItem* item){
	if(item==0) return;								// i.e. the user did not press on an item
	location->setText(item->text());
}

void IconSelectorDialog::setPathCombo(){
  QString dir=caption();
  int i=0;
  bool found=FALSE;
  for(i=0; i<pathCombo->count(); i++){
    if(pathCombo->text(i) == dir){
      found = TRUE;
      break;
    }
  }

  if(found)
	  pathCombo->setCurrentItem(i);
  else{
  	pathCombo->insertItem(dir);
  	pathCombo->setCurrentItem(pathCombo->count() - 1);
  }
}

void IconSelectorDialog::directoryChanged(const QString &dir){
	setCaption(dir);
	setPathCombo();
}

void IconSelectorDialog::slotStartReadDir( int dirs )
{
//    label->setText( tr( " Reading Directory..." ) );
    progress->reset();
    progress->setTotalSteps( dirs );
}

void IconSelectorDialog::slotReadNextDir()
{
    int p = progress->progress();
    progress->setProgress( ++p );
}

void IconSelectorDialog::slotReadDirDone()
{
//    label->setText( tr( " Reading Directory Done." ) );
    progress->setProgress( progress->totalSteps() );
}

void IconSelectorDialog::cdUp(){	
	QDir dir=fileview->currentDir();
	dir.cd("..");
	fileview->setDirectory(dir);
}

//void IconSelectorDialog::newFolder()
//{
//    fileview->newDirectory();
//}

void IconSelectorDialog::changePath(const QString &path){
	if(QFileInfo(path).exists())
		fileview->setDirectory(path);
  else
		setPathCombo();
}

void IconSelectorDialog::enableUp(){
	upButton->setEnabled(TRUE);
}

void IconSelectorDialog::disableUp(){
	upButton->setEnabled(FALSE);
}

//void IconSelectorDialog::enableMkdir(){
//	mkdirButton->setEnabled(TRUE);
//}
//
//void IconSelectorDialog::disableMkdir(){
//	mkdirButton->setEnabled(FALSE);
//}
