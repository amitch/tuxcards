/****************************************************************************
** $Id: qt/examples/fileiconview/mainwindow.h   2.3.0   edited 2001-01-26 $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#ifndef ICONSELECTORDIALOG_H
#define ICONSELECTORDIALOG_H

#include <qdialog.h>
#include <q3iconview.h>
//Added by qt3to4:
#include <QLabel>

class IconSelector;
//class DirectoryView;
class Q3ProgressBar;
class QLabel;
class QComboBox;
class Button;

class IconSelectorDialog : public QDialog{
	Q_OBJECT

public:
  IconSelectorDialog();

	IconSelector *fileView() { return fileview; }
//	DirectoryView *dirList() { return dirlist; }

	void    show();
	bool    getResult();
	QString getIconFileName();
	
protected:
  void setup();
  void setPathCombo();

  IconSelector *fileview;
  QLabel* location;
//    QPushButton* ok;
//    QPushButton
//    DirectoryView *dirlist;
  Q3ProgressBar *progress;
  QLabel *label;
  QComboBox *pathCombo;
  QPushButton *upButton, *mkdirButton;

  bool result;				// states whether the user pressed 'ok' or 'cancel'

protected slots:
  void directoryChanged( const QString & );
  void slotStartReadDir( int dirs );
  void slotReadNextDir();
  void slotReadDirDone();
  void cdUp();
//  void newFolder();
  void changePath( const QString &path );
  void enableUp();
  void disableUp();
//  void enableMkdir();
//  void disableMkdir();

	void slotOkPressed();
	void slotCancelPressed();
	void slotFileSelected(Q3IconViewItem* item);
private:
	QString mstrIconDir;
};

#endif
