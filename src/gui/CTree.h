/***************************************************************************
                          CTree.h  -  description
                             -------------------
    begin                : Mon Mar 27 2000
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

#ifndef CTREE_H
#define CTREE_H

#include "../information/IView.h"

#include <iostream>
#include <qstring.h>
#include <q3listview.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include <QDragMoveEvent>
#include <QKeyEvent>
#include <QDragLeaveEvent>

#include "./dialogs/CPropertyDialog.h"
#include "./dialogs/searchdialog.h"
#include <q3popupmenu.h>
#include <qmessagebox.h>

#include <qpixmap.h>

#include <q3frame.h>
#include <qlineedit.h>
#include <qpushbutton.h>

#include "../information/CInformationCollection.h"
#include "../information/CTreeInformationElement.h"
#include "CTreeElement.h"
#include "../fontsettings.h"
#include "../CTuxCardsConfiguration.h"

#include <qtimer.h>

#include "../information/Path.h"

class CTree : public Q3ListView,
              public IView
{
  Q_OBJECT
private:
  CInformationCollection* mpCollection;
  Q3PopupMenu              mContextMenu;
  CPropertyDialog         mPropertyDialog;
  SearchDialog            mSearchDialog;

  //CTreeElement* draggedElement;
  QPoint                  mPressPos;
  bool                    mbMousePressed;
  QTimer                  mAutoOpenTimer;
  CTreeElement*           mpOldCurrent;
  CTreeElement*           mpDropElement;
  const int               miAutoOpenTime;

  CInformationElement*    getCurrentActive( void );
  CTreeElement*           getCurrentActiveTreeElement( void );
  CTreeElement*           getTreeElement(Path path);
  CTreeElement*           findChildWithName(const QString name);
  void                    clearTree( void );
  void                    setDefaultTreeContents( void );
  void                    settingUpContextMenu( void );

  void                    addInformationElementsToTreeItem( CTreeElement&,
                                                            CTreeInformationElement& );

protected:
//  virtual void startDrag();
  void                    contentsMousePressEvent( QMouseEvent* pE );
  void                    contentsMouseMoveEvent( QMouseEvent* pE );
  void                    contentsMouseReleaseEvent( QMouseEvent* pE );

  void                    contentsDragEnterEvent( QDragEnterEvent* pE );
  void                    contentsDragMoveEvent( QDragMoveEvent* pE );
  void                    contentsDragLeaveEvent( QDragLeaveEvent* pE );
  void                    contentsDropEvent( QDropEvent* pE );

  void                    resizeEvent( QResizeEvent* pE );

protected slots:
  void                    elementOpenedEvent( Q3ListViewItem* pItem );
  void                    elementClosedEvent( Q3ListViewItem* pItem );
  void                    rightButtonPressed( Q3ListViewItem* pItem );
  void                    timeoutEvent( void );
  void                    addEntryToBookmarks( void );

  void                    inPlaceRenaming( Q3ListViewItem* pItem , int iCol, const QString& sText );
  void                    moveElementUp();
  void                    moveElementDown();

public:
  CTree( QWidget* pParent, CTuxCardsConfiguration& refTuxConfiguration );
  ~CTree( void );
  void                    setColumnText( QString text );
  void                    createTreeFromCollection( CInformationCollection& collection );

  void                    deleteElement( CTreeElement* pElem, bool bChangeSelection = true);

  // ************** IView **********************************
   virtual void aboutToRemoveElement( CInformationElement* pIE );

public slots:
  // "contextmenu"
  void                    addElement( void );
  void 						renameElement( void );
  void                    changeActiveElementProperties( void );
  void                    askForDeletion( void );

  // "mousecalls"
  void                    selectionChanged( Q3ListViewItem* pItem );
  void                    currentChanged( Q3ListViewItem* pItem );

  virtual void            keyPressEvent( QKeyEvent* pK );

  //
  void                    removeAll( void );
  void                    search( void );

//  void makeVisible(Knoten*, int, int, int);

  void                    activeInformationElementChanged( CInformationElement* );

  void						setEntryColor();
  void 						setEntrySubTreeColor();
  
signals:
  void                    showMessage(QString, int time);
  void                    makeVisible( SearchPosition* );
  void                    addEntryToBookmarksSignal( void );
  void                    dragStarted( void );
};

#endif
