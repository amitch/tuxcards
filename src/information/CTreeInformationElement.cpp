/***************************************************************************
                          CTreeInformationElement.cpp  -  description
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

#include "CTreeInformationElement.h"
#include "../global.h"

// -------------------------------------------------------------------------------
CTreeInformationElement::CTreeInformationElement( CInformationElement* pParent,
                         QString description,
                         QString information,
                         InformationFormat* pFormat,
                         QString sIconFileName,
                         bool bOpen )
 : CInformationElement( pParent, description, information, pFormat, sIconFileName)
// -------------------------------------------------------------------------------
{
   setOpen( bOpen );
}


/**
 * Adds the CTreeInformationElement 'element' to this element.
 */
// -------------------------------------------------------------------------------
void CTreeInformationElement::addChild( CTreeInformationElement* pElement )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == pElement )
      return;

   mpChildObjects->append( pElement );
   pElement->setParent( this );

   emit childAdded( pElement );
//  if (!mbBatched) emit(childAdded(element));
}


// -------------------------------------------------------------------------------
bool CTreeInformationElement::isOpen( void )
// -------------------------------------------------------------------------------
{
   return mbOpen;
}


// -------------------------------------------------------------------------------
void CTreeInformationElement::setOpen( bool bOpen )
// -------------------------------------------------------------------------------
{
   mbOpen = bOpen;
   if (!mbBatched) emit propertyChanged();
}


// -------------------------------------------------------------------------------
QString CTreeInformationElement::toStringObsoleted( void )
// -------------------------------------------------------------------------------
{
  QString result="";
  QString h;

  // get own name
  h = mDescription;
  result += QString::number(h.length()) + "*" + h;

  // get own text
  h = mInformation;
  result += QString::number(h.length()) + "*" + h;

  //state whether this Knoten is open or not
  h = ( isOpen() ? "-" : "+" );
  result += h;

  // include iconFilename
  result += mIconFilename+"*";

  int n = childCount();
  result += QString::number(n);

  //jedes Kind hinzuf�gen
  Q3PtrListIterator<CInformationElement> it(*getChildren());
  CTreeInformationElement* x;
  while( (x = (CTreeInformationElement*)it.current()) != 0 ){
    ++it;
    result+=x->toString();
  }

  // add terminationString & header
  result= "*" +result+ "***";
  result= "***" + QString::number(result.length()) + result;

  return result;
}


// -------------------------------------------------------------------------------
void CTreeInformationElement::toXML( QDomDocument xmlDocument, QDomNode parent )
// -------------------------------------------------------------------------------
{
   QDomElement thisElement = xmlDocument.createElement("InformationElement");
   thisElement.setAttribute("informationFormat", getInformationFormat()->toString());
   thisElement.setAttribute("iconFileName", getIconFileName());
   thisElement.setAttribute("isOpen", isOpen() ? "true" : "false" );
   thisElement.setAttribute("isEncripted", isEncryptionEnabled() ? "true" : "false" );

	// Set the tree item and subtree text color
	QString strTextColor;
   if(msubtreeTextColor != Qt::black) {
		strTextColor = QString("%1:%2:%3")
								.arg(msubtreeTextColor.red())
								.arg(msubtreeTextColor.green())
								.arg(msubtreeTextColor.blue());

	   thisElement.setAttribute("subtreeTextColor", strTextColor);

   }

	strTextColor = QString("%1:%2:%3")
							.arg(mtextColor.red())
							.arg(mtextColor.green())
							.arg(mtextColor.blue());

   thisElement.setAttribute("textColor", strTextColor);

//   std::cout << "CTreeInformationElement::toXML: Text color: saved " << strTextColor.toStdString() <<
//		   "was " << mtextColor.name().toStdString() << std::endl;

   // add description
   QDomElement description = xmlDocument.createElement("Description");
   QDomText text = xmlDocument.createTextNode(getDescription());
   description.appendChild(text);
   thisElement.appendChild(description);

   // add information
   QDomElement information = xmlDocument.createElement("Information");
   if ( isEncryptionEnabled() )
   {
	   bool btmpEncryption = false;

 		// If not currently encrypted, encrypt it to save the encrypted data.
      if ( !isCurrentlyEncrypted() )
      {
         encrypt();
         btmpEncryption = true;
      }

      // Do base64 encoding
      QString sB64Representation (getEncryptedData().toBase64().constData());

//      std::cout<<"CTreeInformationElement::toXML: base64 encode  text length " << sB64Representation.length() << " from " << getEncryptedData().size() << std::endl;
      text = xmlDocument.createCDATASection( sB64Representation );

      // Decrypt if done to get the encrypted data for saving.
      if (btmpEncryption)
      	decrypt(msTmpPasswd);
   }
   else
   {
      //text = xmlDocument.createTextNode( getInformation() );
      text = xmlDocument.createCDATASection( getInformation() );
   }

   information.appendChild(text);
   thisElement.appendChild(information);


   // add children
   Q3PtrListIterator<CInformationElement> it(*mpChildObjects);
   CInformationElement* x;
   while( (x = it.current()) != 0 )
   {
      ++it;
      x->toXML(xmlDocument, thisElement);
   }

   parent.appendChild(thisElement);
}


/**
 * Move this element one position upwards within the sibling
 * list. If moving upwards is not possible nothing is done.
 */
// -------------------------------------------------------------------------------
void CTreeInformationElement::moveOneUp( void )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpParent )
   {
      std::cout<<"parent == 0 -> moving not possible"<<std::endl;
      return;
   }

   ((CTreeInformationElement*)mpParent)->moveChildOneUp(this);
}


/**
 * Move the specified child element one position upwards within
 * children list. If moving upwards is not possible or the given
 * element is not a child of this element nothing is done.
 */
// -------------------------------------------------------------------------------
void CTreeInformationElement::moveChildOneUp( CTreeInformationElement* pChild )
// -------------------------------------------------------------------------------
{
   int pos = mpChildObjects->findRef( pChild );
   if ( (pos == -1) || (pos == 0) )
   {
      //std::cout<<"child not found or at first position -> moving not possible"<<std::endl;
      return;
   }

   bool tmpAutoDelete = mpChildObjects->autoDelete();
   mpChildObjects->setAutoDelete( false );              // do not kill the pointer
   mpChildObjects->remove( pos );
   mpChildObjects->setAutoDelete( tmpAutoDelete );

   mpChildObjects->insert( pos-1, pChild );

   if (!mbBatched) emit childMoved(pos, pos-1);

   //std::cout<<getTreeString(1)<<std::endl;
}

/**
 * Move this element one position upwards within the sibling
 * list. If moving upwards is not possible nothing is done.
 */
// -------------------------------------------------------------------------------
void CTreeInformationElement::moveOneDown( void )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpParent )
   {
      std::cout<<"parent == 0 -> moving not possible"<<std::endl;
      return;
   }

   ((CTreeInformationElement*)mpParent)->moveChildOneDown(this);
}

/**
 * Move the specified child element one position downwards within
 * children list. If moving downwards is not possible or the given
 * element is not a child of this element nothing is done.
 */
// -------------------------------------------------------------------------------
void CTreeInformationElement::moveChildOneDown( CTreeInformationElement* pChild )
// -------------------------------------------------------------------------------
{
   int pos = mpChildObjects->findRef( pChild );
   if ( (pos == -1) || (pos == childCount()-1) )
   {
      return;
   }

   bool tmpAutoDelete = mpChildObjects->autoDelete();
   mpChildObjects->setAutoDelete( false );              // do not kill the pointer
   mpChildObjects->remove( pos );
   mpChildObjects->setAutoDelete( tmpAutoDelete );

   mpChildObjects->insert( pos+1, pChild );

   if (!mbBatched) emit childMoved(pos, pos+1);

}

