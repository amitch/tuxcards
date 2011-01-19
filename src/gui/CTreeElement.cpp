/***************************************************************************
                          treeelement.cpp  -  description
                             -------------------
    begin                : Fri Jul 19 2002
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
#include <iostream>

#include "CTreeElement.h"
#include "./dialogs/searchlistitem.h"

#include "../global.h"
//Added by qt3to4:
#include <QPixmap>
#include <Q3PtrList>

/**
 * creates a treeElement from the treeInformatoinElement and
 * adds it to 'parent'
 */
// -------------------------------------------------------------------------------
CTreeElement::CTreeElement( Q3ListView* pParent, CTreeInformationElement& element )
  : Q3ListViewItem( pParent, element.getDescription() )
  , mpInformationElement( NULLPTR )
// -------------------------------------------------------------------------------
{
   init(element);
}

/**
 * creates a treeElement from the treeInformatoinElement and
 * adds it to 'parent'
 */
// -------------------------------------------------------------------------------
CTreeElement::CTreeElement( CTreeElement* pParent, CTreeInformationElement& element )
  : Q3ListViewItem(pParent, pParent->getLastChild(), element.getDescription())
  , mpInformationElement( NULLPTR )
// -------------------------------------------------------------------------------
{
   init(element);
}

// -------------------------------------------------------------------------------
CTreeElement::~CTreeElement( void )
// -------------------------------------------------------------------------------
{
   mpInformationElement = NULLPTR;
}

// -------------------------------------------------------------------------------
void CTreeElement::init( CTreeInformationElement& element )
// -------------------------------------------------------------------------------
{
  mpInformationElement = &element;
  copyPropertiesFromInformationElement();
  connect( &element, SIGNAL(propertyChanged()), this, SLOT(propertyChangeEvent()) );
  connect( &element, SIGNAL(childAdded(CInformationElement*)), this, SLOT(childAddEvent(CInformationElement*)) );
  connect( &element, SIGNAL(childMoved(int, int)), this, SLOT(childMovedEvent(int, int)) );

  setRenameEnabled(0, TRUE);
}

/**
 * Returns the last child of this element. Utility-method needed to
 * place the elements in correct order.
 */
// -------------------------------------------------------------------------------
CTreeElement* CTreeElement::getLastChild( void )
// -------------------------------------------------------------------------------
{
   CTreeElement* pResult = (CTreeElement*)firstChild();
   if ( NULLPTR == pResult )
      return NULLPTR;

   while ( NULLPTR != pResult->nextSibling() )
      pResult = (CTreeElement*) pResult->nextSibling();

   return pResult;
}

// -------------------------------------------------------------------------------
CTreeInformationElement* CTreeElement::getInformationElement( void )
// -------------------------------------------------------------------------------
{
   return mpInformationElement;
}

/**
 * This slot is called if an attribut of the informationelement
 * belonging to this object was changed.
 */
// -------------------------------------------------------------------------------
void CTreeElement::propertyChangeEvent( void )
// -------------------------------------------------------------------------------
{
   //cout<<"CTreeElement::propertyChangeEvent()"<<endl;
   copyPropertiesFromInformationElement();
}

/**
 * Copies all necessary attributes from the informationelement (data)
 * to this object (view).
 */
// -------------------------------------------------------------------------------
void CTreeElement::copyPropertiesFromInformationElement( void )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpInformationElement )
      return;

   setText(  0, mpInformationElement->getDescription() );
   setPixmap(0, QPixmap(mpInformationElement->getIconFileName()) );
   setOpen( mpInformationElement->isOpen() );
}


/**
 * This method is called whenever a child is added within the "data-model"
 * to the equivalent of this treeElement.
 */
// -------------------------------------------------------------------------------
void CTreeElement::childAddEvent( CInformationElement* pChild )
// -------------------------------------------------------------------------------
{
   //cout<<"CTreeElement::childAddEvent()"<<endl;
   if ( NULLPTR == pChild )
      return;

   CTreeElement* pNewElement = new CTreeElement(this, *((CTreeInformationElement*)pChild));


   // recursive (i.e. if a whole subtree was added during drag&drop)
   Q3PtrList<CInformationElement>* pList = pChild->getChildren();
   for ( CInformationElement* pX = pList->first(); NULLPTR != pX; pX = pList->next() )
   {
      pNewElement->childAddEvent(pX);
   }

   pNewElement->listView()->setSelected(pNewElement, true);
}


/**
 * This slot is called, whenever one of the element's children
 * has been moved upwards or downwards.
 */
// -------------------------------------------------------------------------------
void CTreeElement::childMovedEvent( int oldPos, int newPos )
// -------------------------------------------------------------------------------
{
  if ( oldPos == newPos )
    return;

  CTreeElement* pElementToMove = getChildAtPosition(oldPos);
  if ( NULLPTR == pElementToMove )
    return;

  Q3ListViewItem* pTmp = getChildAtPosition(newPos);
  if ( NULLPTR == pTmp )
    return;

  if ( newPos < oldPos )
  {
    // moving upwards
    if ( (newPos - 1) >= 0  )
    {
      pTmp = getChildAtPosition(newPos-1);
      pElementToMove->moveItem(pTmp);
    }
    else
    {
      // insert temporary dummy element
      Q3ListViewItem* pDummy = new Q3ListViewItem(this);
      pDummy->setText(0, "pDummy");
      pTmp = pDummy;
      pElementToMove->moveItem(pTmp);
      DELETE( pDummy );
    }
  }
  else
  {
    // moving downwards
    pElementToMove->moveItem(pTmp);
  }
}


/**
 * Returns the child position at 'pos'. If it does not exist
 * 0 is returned.
 */
// -------------------------------------------------------------------------------
CTreeElement* CTreeElement::getChildAtPosition( int pos )
// -------------------------------------------------------------------------------
{
  if ( pos > childCount()-1 )
    return NULLPTR;

  Q3ListViewItem* pX;
  int pos2 = -1;
  for ( pX = firstChild(); NULLPTR != pX; pX = pX->nextSibling())
  {
    pos2++;
    if ( pos2 == pos )
      return (CTreeElement*)pX;
  }

  return NULLPTR;
}



/**
 * returns true if this Knoten or one of its children
 * is selected right now
 */
// -------------------------------------------------------------------------------
bool CTreeElement::isChildOrSelfSelected( void )
// -------------------------------------------------------------------------------
{
   if (isSelected())
      return true;

   for ( CTreeElement* pElem = (CTreeElement*)firstChild();
         NULLPTR != pElem;
         pElem = (CTreeElement*)pElem->nextSibling() )
   {
      if ( pElem->isChildOrSelfSelected() )
         return true;
   }

   return false;
}

/**
 * find the specified 'QString pattern' within the text/information of the
 * appropriate 'CInformationElement' (evtl. recursive) and append the found
 * "places" as 'SearchListItem's at the list's end.
 */
// -------------------------------------------------------------------------------
void CTreeElement::search( QString pattern, bool recursive, bool caseSensitive,
                          bool SearchOnlyTitles, Q3ListView& list )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpInformationElement )
      return;

   mpInformationElement->search(pattern, recursive, caseSensitive,
   		SearchOnlyTitles, list);
}


/**
 * Returns the first child whose "name"/text(0) equals
 * 'name'. If it does not exist return 0. (searches within direct children
 * only)
 */
// -------------------------------------------------------------------------------
CTreeElement* CTreeElement::findChildWithName( QString name )
// -------------------------------------------------------------------------------
{
  Q3ListViewItem* pX = NULLPTR;
  for (pX = firstChild(); NULLPTR != pX; pX = pX->nextSibling())
  {
    //std::cout<<"***TE::search through "<<x->text(0)<<std::endl;
    if ( pX->text(0) == name )
      return (CTreeElement*)pX;
  }

  return NULLPTR;
}

// -------------------------------------------------------------------------------
void CTreeElement::paintCell( QPainter *p, const QColorGroup &cg,
			    int column, int width, int alignment )
{
    QColorGroup _cg( cg );

	_cg.setColor( QPalette::Text/*QColorGroup::Text*/, mpInformationElement->getTextColor());
//    std::cout << "paintCell: Text color: desired " << mpInformationElement->getTextColor().name().toStdString() <<
//          "actual " << _cg.text().name().toStdString() << std::endl;
    Q3ListViewItem::paintCell( p, _cg, column, width, alignment );

}

