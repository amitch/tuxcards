/***************************************************************************
                          RecentFileList.h  -  description
                             -------------------
    begin                : Sun Feb 09 2003
    copyright            : (C) 2003 by Alexander Theel
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

#ifndef RECENTFILELIST_H
#define RECENTFILELIST_H

#include <q3popupmenu.h>
#include <qaction.h>
//Added by qt3to4:
#include <Q3ActionGroup>

class RecentFileList : public QObject {
  Q_OBJECT
public:
  RecentFileList(QWidget* parent, Q3PopupMenu* menu, QString files="");
  
  void setOnTop(QString absPath);

  QString toString();

private:
  QWidget* parent;
  Q3PopupMenu* menu;
  QStringList fileList;
  Q3ActionGroup * recentFileGroup;
  Q3PopupMenu* recentlyFilesMenu;

  static /*const*/ QString separator;
  static /*const*/ uint MAX_ELEMENT_COUNT;

  void setList(QString files);
  void checkSize();
  void update();
  void updateMenu();
  
  void remove(QString absPath);

private slots:
  void slotRecenlyOpenedFilesActivated( int id );
  
signals:
  void openFile(QString fileName);
};

#endif
