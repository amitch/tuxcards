/***************************************************************************
                          CTree.cpp  -  description
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

#include "CTree.h"

#include "../icons/delete.xpm"
#include "../icons/changeProperty.xpm"
#include "../icons/addTreeElement.xpm"
#include "../icons/upArrow.xpm"
#include "../icons/downArrow.xpm"
//#include "../icons/bookmark_add.xpm"

#include <qcursor.h>
#include <q3header.h>
#include <qapplication.h>
#include <qcolor.h>
#include <qcolordialog.h>
//Added by qt3to4:
#include <QDragLeaveEvent>
#include <QKeyEvent>
#include <QPixmap>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QEvent>

#include "../information/xmlpersister.h"

#include "../utilities/CIconManager.h"
#define  getIcon(x)  CIconManager::getInstance().getIcon(x)


/**
 * Constructor
 * 'Editor* editor' is the component to which the text to show will be presented
 *
 * setting up the gui and connections
 */
CTree::CTree( QWidget* pParent, CTuxCardsConfiguration& refTuxConfiguration )
  : Q3ListView( pParent )
  , mpCollection( NULLPTR )
  , mContextMenu( pParent )
  , mPropertyDialog( pParent, refTuxConfiguration )
  , mSearchDialog( pParent )
  , mPressPos()
  , mbMousePressed( false )
  , mAutoOpenTimer( pParent )
  , mpOldCurrent( NULLPTR )
  , mpDropElement( NULLPTR )
  , miAutoOpenTime( 750 )
{

  // this
  addColumn("");
  setSorting(-1);
  setRootIsDecorated(true);

  setAcceptDrops(true);
  viewport()->setAcceptDrops(true);

  connect( &mAutoOpenTimer, SIGNAL(timeout()), this, SLOT(timeoutEvent()) );

  setVScrollBarMode(AlwaysOn);
  // Communication
  connect( this, SIGNAL(selectionChanged(Q3ListViewItem*)),
           this, SLOT(selectionChanged(Q3ListViewItem*)) );
  connect( this, SIGNAL(rightButtonPressed(Q3ListViewItem*,const QPoint&, int)),
           this, SLOT(rightButtonPressed(Q3ListViewItem*)) );
  connect( this, SIGNAL(expanded(Q3ListViewItem*)),
           this, SLOT(elementOpenedEvent(Q3ListViewItem*)) );
  connect( this, SIGNAL(collapsed(Q3ListViewItem*)),
           this, SLOT(elementClosedEvent(Q3ListViewItem*)) );
  connect( this, SIGNAL(itemRenamed(Q3ListViewItem*, int, const QString&)),
           this, SLOT(inPlaceRenaming(Q3ListViewItem*, int, const QString&)) );


  // searchdialog
  //searchDialog=new SearchDialog(this);
  connect( &mSearchDialog, SIGNAL(makeVisible(SearchPosition*)),
           this,           SIGNAL(makeVisible(SearchPosition*)) );
//  QObject::connect(searchWindow, SIGNAL(makeVisible(CTreeElement*, int, int, int)),
//									 this, 				 SLOT  (makeVisible(CTreeElement*, int, int, int)) );
//  connect(this, SIGNAL(TreeElementDeleted()), searchWindow, SLOT(close()));


  settingUpContextMenu();
}


CTree::~CTree( void )
{
   mpCollection = NULLPTR;
   mpOldCurrent = NULLPTR;
   mpDropElement= NULLPTR;
}

void CTree::timeoutEvent( void )
{
   mAutoOpenTimer.stop();
   if ( NULLPTR == mpDropElement )
      return;


   if ( !mpDropElement->isOpen() )
   {
      mpDropElement->setOpen( TRUE );
      //mpDropElement->repaint();
   }
}


// -------------------------------------------------------------------------------
void CTree::aboutToRemoveElement( CInformationElement* pIE )
// -------------------------------------------------------------------------------
{
   if ( (NULLPTR != mpOldCurrent) && (mpOldCurrent->getInformationElement() == pIE) )
      mpOldCurrent = NULLPTR;                    // set to nullptr only

   if ( (NULLPTR != mpDropElement) && (mpDropElement->getInformationElement() == pIE) )
      mpDropElement = NULLPTR;                   // set to nullptr only
}



void CTree::setColumnText(QString text){
  Q3ListView::setColumnText(0, text);
}

void CTree::settingUpContextMenu( void )
{
  QPixmap addIcon(addTreeElement_xpm);
  QPixmap changePropertyIcon(changeProperty_xpm);
  QPixmap removeTreeElementIcon(delete_xpm);
  QPixmap upIcon(upArrow_xpm);
  QPixmap downIcon(downArrow_xpm);
  //QPixmap bookmarkAddIcon(bookmark_add_xpm);

  //context = new QPopupMenu(this);
  mContextMenu.insertItem( getIcon("addTreeElement"), "&Add Entry...",        this, SLOT(addElement()) );
  mContextMenu.insertItem("&Rename Entry", this, SLOT(renameElement()));
  mContextMenu.insertItem( getIcon("changeProperty"), "Change Properties...",this, SLOT(changeActiveElementProperties()) );
  mContextMenu.insertItem( getIcon("delete"),         "Delete Entry",        this, SLOT(askForDeletion()) );
  mContextMenu.insertSeparator();
  mContextMenu.insertItem( getIcon("editentrycolor"), "Set &Entry Color...",  this, SLOT(setEntryColor()) );
  mContextMenu.insertItem( getIcon("editentrysubtreecolor"), "Set &Entry Sub-Tree Color...", this, SLOT(setEntrySubTreeColor()));
  mContextMenu.insertSeparator();
  mContextMenu.insertItem( getIcon("upArrow"),        "Move Entry Upwards",  this, SLOT(moveElementUp()) );
  mContextMenu.insertItem( getIcon("downArrow"),      "Move Entry Downwards",this, SLOT(moveElementDown()) );
  //mContextMenu.insertSeparator();
  //mContextMenu.insertItem(bookmarkAddIcon,  "add Entry to Bookmarks",this, SLOT(addEntryToBookmarks()) );
}

// selection has changed either via mouse-click or via keyboard
void CTree::selectionChanged( Q3ListViewItem* pItem )
{
  //cout<<"selection Changed"<<endl;

   if ( (NULLPTR == mpCollection) || (NULLPTR == pItem) )
      return;

   CTreeElement* pTreeElem = dynamic_cast<CTreeElement*>(pItem);
   if ( !pTreeElem )
      return;

   mpCollection->setActiveElement(pTreeElem->getInformationElement());

//  // saving currentText to the QListViewItem
//  getCurrentActive()->setText(editor->getText());
//  getCurrentActive()=(CTreeElement*)x;
//
//  editor->setText(getCurrentActive()->getText());
}


void CTree::currentChanged( Q3ListViewItem* pItem )
{
   if ( NULLPTR == pItem )
      return;

   this->setSelected(pItem, TRUE);
}

void CTree::rightButtonPressed( Q3ListViewItem* pItem )
{
   if ( NULLPTR == pItem )
      return;

   mContextMenu.popup( QCursor::pos() );
}

void CTree::elementOpenedEvent( Q3ListViewItem* pItem )
{
   if (NULLPTR == pItem)
      return;

   CTreeElement* pTreeElem = dynamic_cast<CTreeElement*>(pItem);
   if ( !pTreeElem )
      return;

   pTreeElem->getInformationElement()->setOpen(true);
}

void CTree::elementClosedEvent( Q3ListViewItem* pItem )
{
   if (NULLPTR == pItem)
      return;

   CTreeElement* pTreeElem = dynamic_cast<CTreeElement*>(pItem);
   if ( !pTreeElem )
      return;

   pTreeElem->getInformationElement()->setOpen(false);
}


/******************************************************************************/

void CTree::contentsMousePressEvent( QMouseEvent* pE )
{
   //cout<<"contentsMousePressEvent()"<<endl;
   if ( NULLPTR == pE )
      return;

   Q3ListView::contentsMousePressEvent(pE);
   if (Qt::RightButton == pE->button())
      return;

   QPoint p( contentsToViewport( pE->pos() ) );
   CTreeElement* pItem = dynamic_cast<CTreeElement*>(itemAt(p));
   if ( NULLPTR == pItem )
      return;

   // if the user clicked into the root decoration of the item, don't try to start a drag!
   if ( p.x() > header()->cellPos( header()->mapToActual(0) ) +
        treeStepSize() * ( pItem->depth() + ( rootIsDecorated() ? 1 : 0) ) + itemMargin() ||
        p.x() < header()->cellPos( header()->mapToActual(0) ) )
   {
      mPressPos = pE->pos();
      mbMousePressed = true;
   }
}



void CTree::contentsMouseMoveEvent( QMouseEvent* pE )
{
   if ( (NULLPTR == mpCollection) || (NULLPTR == pE) )
      return;

   if ( mbMousePressed &&
        (mPressPos - pE->pos()).manhattanLength() > QApplication::startDragDistance() )
   {
      //cout<<"contentsMouseMoveEvent()"<<endl;
      mbMousePressed = false;
      Q3ListViewItem* pItem = itemAt(contentsToViewport(mPressPos));
      if ( NULLPTR != pItem )
      {
      	 emit dragStarted();

         QDrag* pDrag = new QDrag(this);
         QMimeData *mimeData = new QMimeData;

         mimeData->setText(mpCollection->toXML(getCurrentActive()));
         pDrag->setMimeData(mimeData);

         Qt::DropAction dropAction = pDrag->exec();

         pE->accept();
      }
   }
}



void CTree::contentsMouseReleaseEvent( QMouseEvent* )
{
   mbMousePressed = false;
}

/******************************************************************************/

void CTree::contentsDragEnterEvent( QDragEnterEvent* pE )
{
   //cout<<"contentsDragEnterEvent()"<<endl;
   if ( NULLPTR == pE )
      return;

   if (!pE->mimeData()->hasText())
   {
      pE->ignore();
      return;
   }

   mpOldCurrent = dynamic_cast<CTreeElement*>( currentItem() );

   CTreeElement* pElement = dynamic_cast<CTreeElement*>(itemAt(contentsToViewport(pE->pos())));
   if ( NULLPTR != pElement )
   {
      mpDropElement = pElement;
      mAutoOpenTimer.start(miAutoOpenTime);
   }

   pE->acceptProposedAction();
}

void CTree::contentsDragMoveEvent( QDragMoveEvent* pE )
{
   //cout<<"contentsDragMoveEvent()"<<endl;
   if ( NULLPTR == pE )
      return;

   if (!pE->mimeData()->hasText())
   {
      pE->ignore();
      return;
   }

   QPoint vp = contentsToViewport( pE->pos() );
   CTreeElement* pElement = dynamic_cast<CTreeElement*>( itemAt(vp) );
   if ( NULLPTR != pElement ){
      setSelected(pElement, TRUE);
      pE->setAccepted(true);
      if ( pElement != mpDropElement ){
         mAutoOpenTimer.stop();
         mpDropElement = pElement;
         mAutoOpenTimer.start(miAutoOpenTime);
      }
      switch ( pE->dropAction() )
      {
      case Qt::CopyAction:
         break;
      case Qt::MoveAction:
         pE->acceptProposedAction();
         emit showMessage("Move to '"+ (pElement->text(0))+"'", 1);
         break;
      case Qt::LinkAction:
         pE->acceptProposedAction();
         break;
      default:
         ;
      }
   }else{
      pE->ignore();
      mAutoOpenTimer.stop();
      mpDropElement = NULLPTR;
      emit showMessage("", 1);
   }
}


void CTree::contentsDragLeaveEvent( QDragLeaveEvent* )
{
  //cout<<"contentsDragLeaveEvent()"<<endl;
  mAutoOpenTimer.stop();
  mpDropElement = NULLPTR;

  setCurrentItem( mpOldCurrent );
  setSelected( mpOldCurrent, TRUE );
}


void CTree::contentsDropEvent( QDropEvent* pE )
{
  //std::cout<<"contentsDropEvent()"<<" format="<<e->format()<<std::endl;
  mAutoOpenTimer.stop();

  if ( (NULLPTR == pE) || (NULLPTR == mpOldCurrent) )
   return;

  if (!pE->mimeData()->hasText())
  {
     pE->ignore();
     return;
  }

  if (pE->source()==this && mpOldCurrent->isChildOrSelfSelected()){ // if 'dragging->selected()==true' -> elter is moved to son
    QMessageBox::information( this, "Dragging", "An Entry cannot be moved onto itself or a child.", "Ok" );
    emit showMessage("Move not possible.", 5);
    pE->ignore();
    return;
  }

   CTreeElement* pItem = dynamic_cast<CTreeElement*>( itemAt(contentsToViewport(pE->pos())) );
   if ( NULLPTR == pItem )
   {
      pE->ignore();
      return;
   }

   switch ( pE->dropAction() )
   {
   case Qt::CopyAction:
      break;
   case Qt::MoveAction:
      pE->acceptProposedAction();
      break;
   case Qt::LinkAction:
      pE->acceptProposedAction();
      break;
   default:
      ;
   }
   pE->setAccepted(true);


   QString collectionString = pE->mimeData()->text();
//   Q3TextDrag::decode(pE, collectionString);

// %%AC: Is this needed for copy\paste or text drag?
/*
    //std::cout<<"CTree::contentsDropEvent; format="<<e->format()<<std::endl;
    QString format(pE->format());
    if ( format.startsWith("text/plain") )
    {
      QString data(pE->encodedData("text/plain"));
      pItem->getInformationElement()->appendInformation(data);
      return;
    }
*/
    // add the dropped tree
    CInformationCollection* pCollection = XMLPersister::createInformationCollection(collectionString);
    if ( NULLPTR != pCollection )
    {
      CInformationElement* pRoot = pCollection->getRootElement();
      if ( NULLPTR != pRoot )
      {
         pItem->getInformationElement()->addChild(
                                          dynamic_cast<CTreeInformationElement*>(pRoot) );
      }
    }

    // remove
    this->deleteElement(mpOldCurrent, false);
}

/******************************************************************************/



CInformationElement* CTree::getCurrentActive( void )
{
   if ( NULLPTR == mpCollection )
      return NULLPTR;

   return mpCollection->getActiveElement();
}


/**
 * wrapper for 'clearTree()'
 */
void CTree::removeAll( void )
{
  clearTree();
  setColumnText("");
}
/**
 * removes all children from rootItem
 */
void CTree::clearTree( void )
{
   if ( NULL == childCount() )
      return;

   CTreeElement* pRoot = dynamic_cast<CTreeElement*>( firstChild() );
   //selectionChanged(root);

   if ( NULLPTR == pRoot )
      return;

   CTreeElement* pX    = dynamic_cast<CTreeElement*>(pRoot->firstChild());
   CTreeElement* pNext = NULLPTR;

   for ( int i=1; i <= pRoot->childCount(); i++ )
   {
      pNext = dynamic_cast<CTreeElement*>( pX->nextSibling() );
      DELETE( pX );
      pX = pNext;
   }

   DELETE( pRoot );
}

void CTree::setDefaultTreeContents( void )
{
  (void) new Q3ListViewItem(this, "root");
}


void CTree::createTreeFromCollection( CInformationCollection& collection )
{
   //cout<<"CTree:: creating tree from collection"<<endl;

   removeAll();

   CTreeInformationElement* pCollectionRootElement = dynamic_cast<CTreeInformationElement*>(collection.getRootElement());
   if ( NULLPTR == pCollectionRootElement )
   {
      std::cout<<"CTree::createTreeFromCollection(): NULLPTR == pCollectionRootElement !"<<std::endl;
      return;
   }
   CTreeElement* pTreeElement = new CTreeElement(this, *pCollectionRootElement);
   Q3PtrListIterator<CInformationElement> it(*pCollectionRootElement->getChildren());
   CTreeInformationElement* pX = NULLPTR;
   while( (pX = dynamic_cast<CTreeInformationElement*>(it.current())) != NULLPTR )
   {
      ++it;
      addInformationElementsToTreeItem( *pTreeElement, *pX );
   }

   // add this tree as listener
   // TODO: disconnect from previous collection
   // TODO: delete old collection
   mpCollection = &collection;
   connect( mpCollection, SIGNAL(activeInformationElementChanged(CInformationElement*)),
            this, SLOT(activeInformationElementChanged(CInformationElement*)) );
}

/**
 * transforms the informationelement 'element' in a qlistitem and adds
 * it to 'parent'; same function as above but recursively
 */
void CTree::addInformationElementsToTreeItem( CTreeElement& parent, CTreeInformationElement& element){
  CTreeElement* pTreeElement = new CTreeElement(&parent, element);

  Q3PtrListIterator<CInformationElement> it( *(element.getChildren()) );
  CTreeInformationElement* pX = NULLPTR;
  while( (pX = dynamic_cast<CTreeInformationElement*>(it.current())) != NULLPTR )
  {
    ++it;
    addInformationElementsToTreeItem( *pTreeElement, *pX );
  }
}


/**
 * through this slot, the tree will be notified, if the active element
 * within the structure has changed.
 */
void CTree::activeInformationElementChanged( CInformationElement* pElement )
{
   if ( NULLPTR == pElement )
      return;

   Path path(pElement);
   CTreeElement* pX = getTreeElement(path);

   // do nothing if path not valid
   if ( NULLPTR == pX )
      return;

   // do nothing if already active
   if ( getCurrentActiveTreeElement() == pX )
      return;

	// If both previous and current items have same text, do not reselect.
	// This allows child with same name to be selected.
	if (pX->text(0) == getCurrentActiveTreeElement()->text(0))
		return;

   setSelected( pX, true );
   ensureItemVisible( pX );
  //Path p2(x->getInformationElement());
  //std::cout<<"found "<<x<<"; path="<<p2.toString()<<std::endl;
}

CTreeElement* CTree::getTreeElement( Path path )
{
   QStringList list = path.getPathList();

   CTreeElement* pX = findChildWithName(list[0]);
   if ( NULLPTR == pX )
      return NULLPTR;

   for ( uint i=1; i < list.size(); i++ )
   {
      pX = pX->findChildWithName(list[i]);
      if ( NULLPTR == pX )
         return NULLPTR;
   }

   return pX;
}

/**
 * Returns the first (Top-)CTreeElement whose "name"/text(0) equals
 * 'name'. If it does not exist return 0. (searches within siblings only)
 */
CTreeElement* CTree::findChildWithName( const QString name )
{
  Q3ListViewItem* pX = firstChild();
  while ( NULLPTR != pX )
  {
    //std::cout<<"search through "<<x->text(0)<<std::endl;
    if ( pX->text(0) == name )
      return dynamic_cast<CTreeElement*>(pX);

    pX = pX->nextSibling();
  }

  return NULLPTR;
}


// responde to "context-menu" -------------------------------------------
void CTree::addElement( void )
{
  mPropertyDialog.setUp( getCurrentActive(),
                         CPropertyDialog::MODE_CREATE_NEW_ELEMENT );
}


void CTree::changeActiveElementProperties( void )
{
  mPropertyDialog.setUp( getCurrentActive(),
                         CPropertyDialog::MODE_CHANGE_PROPERTIES);
}

/**
 * This slot is called if an element should be deleted.
 * The corresponding datamodel is called to delete this element.
 */
void CTree::askForDeletion( void )
{
  if ( (NULLPTR == selectedItem()) || (NULLPTR == getCurrentActive()) )
  {
    emit showMessage("Nothing selected.", 5);
    return;
  }

  if (selectedItem() == firstChild())
  {
    QMessageBox::information( this, "Delete the active Entry",
                              "The root entry cannot be deleted.",
                              "Ok" );
    return;
  }

  if (QMessageBox::warning( this, "Delete the active Entry",
                            "Do you really want to delete '"
                            +getCurrentActive()->getDescription()+"'?",
                            "Yes", "No"))
  {
    return;
  }

  deleteElement( dynamic_cast<CTreeElement*>(selectedItem()) );
}

/**
 * This slot is called if an element should be deleted.
 * The corresponding datamodel is called to delete this element.
 */
void CTree::deleteElement( CTreeElement* pElem, bool bChangeSelection /*= true*/)
{
   if ( NULLPTR == pElem )
      return;

   if ( pElem == firstChild() )
      return;

   // this does only work as long as only one view is present at one time
   if (bChangeSelection)
	   setSelected( pElem->itemAbove(), true );

   CInformationElement* pIE = pElem->getInformationElement();
   if ( NULLPTR != pIE )
      pIE->deleteSelf();
   else
      std::cout<<"CTree::deleteElement(): pIE == NULLPTR"<<std::endl;

   DELETE( pElem );
}


CTreeElement* CTree::getCurrentActiveTreeElement( void )
{
  CTreeElement* retVal = dynamic_cast<CTreeElement*>( currentItem() );
  Q_CHECK_PTR(retVal);
  return retVal;
}

/**
 *
 */
void CTree::search( void )
{
   if (mSearchDialog.setUp( dynamic_cast<CTreeElement*>(firstChild()),
                            getCurrentActiveTreeElement()) == QDialog::Rejected )
   {
      return;
   }
}

///**
// * 'x' the CTreeElement to make visible
// * 'line', 'pos', 'len' describe the exact place of the String found
// *  (i.o. to highlight it)
// */
//void CTree::makeVisible(CTreeElement* x, int paragraph, int pos, int len){
//
//	// open all parents
//	CTreeElement* y=x;
//	while(y!=firstChild()){
//		y=(CTreeElement*)(y->parent());
//		setOpen(y, true);
//	}
//	setOpen(firstChild(), true);
//
//	// make it visible
//	setSelected(x, true);
//	ensureItemVisible(x);
//
////  editor->setSelection(paragraph,pos, paragraph,pos+len, 0);
////	editor->setCursorPosition(paragraph, pos+len);
////  editor->ensureCursorVisible();
//}


/**
 * links splitter with tree and resizes the listwidth automatically
 */
void CTree::resizeEvent( QResizeEvent* pE )
{
   if ( NULLPTR == pE )
      return;

   setColumnWidth(0, pE->size().width()-22);   // evtl. make vScrollBar auto-on
   triggerUpdate();
}


void CTree::addEntryToBookmarks( void )
{
  emit addEntryToBookmarksSignal();
}


// -------------------------------------------------------------------------------
void CTree::keyPressEvent( QKeyEvent* pK )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == pK )
      return;

   // If
   //   ALT + left  cursor (history one back / previous entry) or
   //   ALT + right cursor (history one forward / next entry)
   // is called, then ignore it.
   if( ( (pK->state() == Qt::AltButton)  &&  (pK->key() == Qt::Key_Left) ) ||
       ( (pK->state() == Qt::AltButton)  &&  (pK->key() == Qt::Key_Right) ) )
   {
      //std::cout<<" -> ignore"<<std::endl;
      pK->ignore();
      return;
   }

   switch( pK->key() )
   {
   case Qt::Key_Delete:
      //std::cout<<"Within CTree: pressing 'Delete"<<std::endl;
      askForDeletion();
      break;
   case Qt::Key_Menu:
      mContextMenu.popup( mapToGlobal( QPoint(5,5) ) );
      break;
   case Qt::Key_F2:
   	qDebug (" CTree::keyPressEventQt::Key_F2 %d ascii %d\n", pK->ascii(), Qt::Key_F2);

   default:
      Q3ListView::keyPressEvent(pK);
  }
}

// -------------------------------------------------------------------------------
void CTree::inPlaceRenaming( Q3ListViewItem* pItem, int /*iCol*/, const QString& sText )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == pItem )
      return;

   CTreeElement* pTreeElement = dynamic_cast<CTreeElement*>(pItem);
   if ( NULLPTR == pTreeElement )
      return;

   CTreeInformationElement* pIE = pTreeElement->getInformationElement();
   if ( NULLPTR == pIE )
      return;

   pIE->setDescription( sText );
}

// -------------------------------------------------------------------------------
void CTree::moveElementUp()
// -------------------------------------------------------------------------------
{
   CInformationElement* pIE = getCurrentActive();
   CTreeInformationElement* pTreeIE = dynamic_cast<CTreeInformationElement*>(pIE);

   if (pTreeIE)
      pTreeIE->moveOneUp();
}

// -------------------------------------------------------------------------------
void CTree::moveElementDown()
// -------------------------------------------------------------------------------
{
   CInformationElement* pIE = getCurrentActive();
   CTreeInformationElement* pTreeIE = dynamic_cast<CTreeInformationElement*>(pIE);

   if (pTreeIE)
      pTreeIE->moveOneDown();
}

// -------------------------------------------------------------------------------
void CTree::renameElement()
// -------------------------------------------------------------------------------
{
	// Fake a F2 key down. It is ok to specify 0 as ascii though it is 4145
	QKeyEvent editElementKey(QEvent::KeyPress, Qt::Key_F2, 0, Qt::NoButton);

	Q3ListView::keyPressEvent(&editElementKey);
}


// -------------------------------------------------------------------------------
void CTree::setEntryColor()
{
   CInformationElement* pElement = getCurrentActive();
   if ( NULLPTR == pElement )
      return;

	QColor c = QColorDialog::getColor(pElement->getTextColor());

	if(!c.isValid()) return;

	pElement->setTextColor(c);

//	std::cout << "MainWindow::setEntryColor: set text color as " << c.red() << ":" << c.green() << ":"
//   		<< c.blue() << std::endl;
}

// -------------------------------------------------------------------------------
void CTree::setEntrySubTreeColor()
{
   CInformationElement* pElement = getCurrentActive();
   if ( NULLPTR == pElement )
      return;

	QColor c = QColorDialog::getColor(pElement->getTextColor());

	if(!c.isValid()) return;

	pElement->setSubTreeTextColor(c);
}
