/****************************************************************************
** $Id: qt/examples/fileiconview/qfileiconview.h   2.3.0   edited 2001-01-26 $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#ifndef ICONSELECTOR_H
#define ICONSELECTOR_H


#include <qicon.h>
#include <qstring.h>
#include <qfileinfo.h>
#include <qdir.h>
#include <qtimer.h>
#include <q3iconview.h>
//Added by qt3to4:
#include <QPixmap>
#include <QResizeEvent>
#include <QDropEvent>
#include <Q3ValueList>
#include <QKeyEvent>

class IconSelector;
class Q3DragObject;
class QResizeEvent;

/*****************************************************************************
 *
 * Class IconSelectorDrag
 *
 *****************************************************************************/

class IconSelectorDrag : public Q3IconDrag
{
    Q_OBJECT

public:
    IconSelectorDrag( QWidget * dragSource, const char* name = 0 );

    const char* format( int i ) const;
    QByteArray encodedData( const char* mime ) const;
    static bool canDecode( QMimeSource* e );
    void append( const Q3IconDragItem &item, const QRect &pr, const QRect &tr, const QString &url );

private:
    QStringList urls;

};

/*****************************************************************************
 *
 * Class IconSelector
 *
 *****************************************************************************/
class IconSelectorItem;
class IconSelector : public Q3IconView
{
    Q_OBJECT

public:
    IconSelector( const QString &dir, QWidget *parent = 0, const char *name = 0 );

    enum ViewMode { Large, Small };

    void setViewMode( ViewMode m );
    ViewMode viewMode() const { return vm; }
    void setOpenItem( IconSelectorItem *i ) {
	openItem = i;
    }

public slots:
  void setDirectory( const QString &dir );
  void setDirectory( const QDir &dir );
  void newDirectory();
  QDir currentDir();

signals:
  void directoryChanged( const QString & );
  void startReadDir( int dirs );
  void readNextDir();
  void readDirDone();
  void enableUp();
  void disableUp();
//  void enableMkdir();
//  void disableMkdir();

protected slots:
  void itemDoubleClicked( Q3IconViewItem *i );
  void slotDropped( QDropEvent *e, const Q3ValueList<Q3IconDragItem> & );

  void viewLarge();
  void viewSmall();
  void viewBottom();
  void viewRight();
  void flowEast();
  void flowSouth();
  void itemTextTruncate();
  void itemTextWordWrap();
  void sortAscending();
  void sortDescending();
  void arrangeItemsInGrid() {
		Q3IconView::arrangeItemsInGrid( TRUE );
  }

  void slotRightPressed(Q3IconViewItem* item);
  void openFolder();

protected:
  void readDir( const QDir &dir );
  virtual Q3DragObject *dragObject();

  virtual void keyPressEvent( QKeyEvent *e );

  QDir viewDir;
  int newFolderNum;
  QSize sz;
  QPixmap pix;
  ViewMode vm;
  IconSelectorItem *openItem;
};

/*****************************************************************************
 *
 * Class IconSelectorItem
 *
 *****************************************************************************/

class IconSelectorItem : public Q3IconViewItem
{
    friend class IconSelector;

public:
    enum ItemType {
        File = 0,
        Dir,
        Link
    };

    IconSelectorItem( IconSelector *parent, QFileInfo *fi );

    virtual ~IconSelectorItem();

    ItemType type() const
    { return itemType; }
    QString filename() const { return itemFileName; }

    virtual bool acceptDrop( const QMimeSource *e ) const;

    virtual void setText( const QString &text );
    virtual QPixmap *pixmap() const;

    virtual void dragEntered();
    virtual void dragLeft();

    void viewModeChanged( IconSelector::ViewMode m );
    void paintItem( QPainter *p, const QColorGroup &cg );

protected:
    virtual void dropped( QDropEvent *e, const Q3ValueList<Q3IconDragItem> & );

    QString itemFileName;
    QFileInfo *itemFileInfo;
    ItemType itemType;
    bool checkSetText;
    QTimer timer;
    IconSelector::ViewMode vm;

};


#endif
