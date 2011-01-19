/***************************************************************************
                          xmlpersister.cpp  -  description
                             -------------------
    begin                : Mit Aug 14 2002
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

#include "xmlpersister.h"
#include "../global.h"
#include <q3ptrlist.h>
#include <q3textedit.h>
//Added by qt3to4:
#include <Q3TextStream>

QString XMLPersister::mpathOfLastActiveElement("");

/************************ loading **********************************/

// -------------------------------------------------------------------------------
CInformationCollection* XMLPersister::createInformationCollection( QFile& xmlFile )
// -------------------------------------------------------------------------------
{
   QDomDocument xmlDocument( "tuxcards_data_file" );
   bool bResult = createDomDocumentFromFile( xmlFile, xmlDocument );

   if ( bResult )
   {
      return createInformationCollection( xmlDocument );
   }

   return NULLPTR;
}

// -------------------------------------------------------------------------------
CInformationCollection* XMLPersister::createInformationCollection( QString xmlString )
// -------------------------------------------------------------------------------
{
//   	std::cout << "XMLPersister::createInformationCollection: str: " << xmlString << std::endl;
   QDomDocument* xmlDocument = createDomDocumentFromString(xmlString);
   if ( NULLPTR != xmlDocument )
   {
      return createInformationCollection( *xmlDocument );
   }

   return NULLPTR;
}

// -------------------------------------------------------------------------------
CInformationCollection* XMLPersister::createInformationCollection( QDomDocument& doc )
// -------------------------------------------------------------------------------
{
   // create the collection
   CInformationCollection* collection = new CInformationCollection();
   CTreeInformationElement* e = new CTreeInformationElement();

   collection->registerAsListenerOf( e );

   if ( !doc.documentElement().isNull() )
   {
      QDomElement* pDomElem = parseCollection(collection, doc.documentElement() );

      if ( NULLPTR != pDomElem )
      {
         parseElementAttributes(*pDomElem, *e);
         parseChildrenOf(*pDomElem, *e);
      }
   }
   collection->setRootElement( e );
   return collection;
}



// Parses collection data (attributes and last active note) and return the root
// information element(node.)
// -------------------------------------------------------------------------------
QDomElement* XMLPersister::parseCollection(CInformationCollection* collection, QDomNode node)
// -------------------------------------------------------------------------------
{
  QDomElement* retVal = NULLPTR;

  if ( node.isElement() )
  {
    QDomElement elem = node.toElement();
    //cout<<"element; tagname= "<<elem.tagName()<<endl;

    if ( elem.tagName() == "InformationCollection" )
    {
    	// Go through collection attributes
	   QDomNamedNodeMap attributes = elem.attributes();
	   QString s = ( attributes.namedItem("isEncrypted").isNull() ? QString("false") : attributes.namedItem("isEncrypted").toAttr().value() );
	   bool bCollectionIsEncrypted = ((s == "true") ? true : false);
	   collection->setEncrypted (bCollectionIsEncrypted);

    	// Save the last
      QDomNode child = node.firstChild();
      QDomElement domElem_LastActiveElement = child.toElement();
      mpathOfLastActiveElement = domElem_LastActiveElement.text();
      //std::cout<<"xmlpersister -> lastActiveElement = "<<mpathOfLastActiveElement<<std::endl;

	// Skip first note, it is a global setting
      retVal = new QDomElement( child.nextSibling().toElement() );
    }
    // For dropped items and backwards compatibility
    else if ( elem.tagName() == "InformationElement" )
    {
    	retVal = new QDomElement( elem );
    }
  }

  return retVal;
}


// -------------------------------------------------------------------------------
void XMLPersister::parseChildrenOf( QDomNode& node, CTreeInformationElement& parent )
// -------------------------------------------------------------------------------
{
   QDomNode child = node.firstChild();
   while ( !child.isNull() )
   {
      parseNode(child, parent);
      child = child.nextSibling();
   }
}


// -------------------------------------------------------------------------------
void XMLPersister::parseNode( QDomNode& node,
                                     CTreeInformationElement& informationElement )
// -------------------------------------------------------------------------------
{
   if ( node.isElement() )
   {
      QDomElement elem = node.toElement();
      //cout<<"element; tagname= "<<elem.tagName()<<endl;

      if ( elem.tagName() == "Description" )
      {
         informationElement.setDescription( elem.text() );
      }
      else if ( elem.tagName() == "Information" )
      {
         // If the current element is encrypted
         if (informationElement.isEncryptionEnabled())
         {
            // do base64 decoding & set as encrypted data
            QByteArray encryptedData = QByteArray::fromBase64(elem.text().toAscii());
            informationElement.setEncryptedData( encryptedData );
         }
         else
         {
            informationElement.setInformation( elem.text() );
         }
      }
      else if ( elem.tagName() == "InformationElement" ) {
      	// Else recursively add next sub tree.
         CTreeInformationElement* e = new CTreeInformationElement( &informationElement );
         parseElementAttributes( elem, *e );
         informationElement.addChild( e );
         parseChildrenOf( node, *e );
      }
   }
}

/**
 * parses the attributes for a CTreeInformationElement
 */
// -------------------------------------------------------------------------------
void XMLPersister::parseElementAttributes( QDomElement& elem,
                                        CTreeInformationElement& informationElem )
// -------------------------------------------------------------------------------
{
   QDomNamedNodeMap attributes = elem.attributes();

   QString s = ( attributes.namedItem("informationFormat").isNull() ? QString("ASCII") : attributes.namedItem("informationFormat").toAttr().value() );
   informationElem.setInformationFormat(InformationFormat::getByString(s));
   //cout<<"XMLP::parseAttr; format= "<<s<<endl;

   s = ( attributes.namedItem("iconFileName").isNull() ? QString("") : attributes.namedItem("iconFileName").toAttr().value() );
   informationElem.setIconFileName(s);
   //cout<<"XMLP::parseAttr; iconFileName ="<<s<<endl;


   s = ( attributes.namedItem("isOpen").isNull() ? QString("false") : attributes.namedItem("isOpen").toAttr().value() );
   informationElem.setOpen( s=="true" ? true : false );
   //cout<<"XMLP::parseAttr; isOpen ="<<s<<endl;

   s = ( attributes.namedItem("isEncripted").isNull() ? QString("false") : attributes.namedItem("isEncripted").toAttr().value() );
   if (s=="true")
   		informationElem.enableEncryption(true, "");

	if (!attributes.namedItem("textColor").isNull()) {
		s = attributes.namedItem("textColor").toAttr().value();
		int red = s.section( ':', 0, 0 ).toInt();
		int green = s.section( ':', 1, 1 ).toInt();
		int blue = s.section( ':', 2, 2 ).toInt();
		QColor c(red, green, blue);
		informationElem.setTextColor(c);

//	   std::cout << "XMLPersister::parseElementAttributes: Text color: read " << s.toStdString() <<
//			   "restored " << c.name().toStdString() << std::endl;
	}

	if (!attributes.namedItem("subtreeTextColor").isNull()) {
		s = attributes.namedItem("subtreeTextColor").toAttr().value();
		int red = s.section( ':', 0, 0 ).toInt();
		int green = s.section( ':', 1, 1 ).toInt();
		int blue = s.section( ':', 2, 2 ).toInt();
		QColor c(red, green, blue);
		informationElem.setSubTreeTextColor(c);
	}

}


// -------------------------------------------------------------------------------
// Returns 'true' if the dom-document could be created correctly.
// -------------------------------------------------------------------------------
bool XMLPersister::createDomDocumentFromFile( QFile& xmlFile, QDomDocument& doc )
// -------------------------------------------------------------------------------
{
   bool bRetVal = FALSE;

   if ( !xmlFile.open( QIODevice::ReadOnly ) )
      return bRetVal;

   bRetVal = doc.setContent( &xmlFile );
   xmlFile.close();

   return bRetVal;

//  QDomDocument* doc = new QDomDocument( "tuxcards_data_file" );
//  if ( !xmlFile.open( IO_ReadOnly ) )
//    return 0;
//  if ( !doc->setContent( &xmlFile ) ) {
//      xmlFile.close();
//      return 0;
//  }
//  xmlFile.close();
//
//  return doc;
}

// -------------------------------------------------------------------------------
QDomDocument* XMLPersister::createDomDocumentFromString( QString xmlString )
// -------------------------------------------------------------------------------
{
   QDomDocument* doc = new QDomDocument( "tuxcards_data_file" );
   if ( !doc->setContent(xmlString) ) {
   		delete doc;
      return NULLPTR;
   }

   return doc;
}


// -------------------------------------------------------------------------------
QString XMLPersister::getPathOfLastActiveElement( void )
// -------------------------------------------------------------------------------
{
   return mpathOfLastActiveElement;
}


/************************ saving ***********************************/
// -------------------------------------------------------------------------------
void XMLPersister::save( CInformationCollection& collection, QString fileName )
// -------------------------------------------------------------------------------
{
   // TODO: save something like a version string with it (like: "TuxCardsV0.5")
   QString s = collection.toXML();

   QFile f(fileName);
   if ( f.open(QIODevice::WriteOnly) )
   {
      Q3TextStream t( &f );
      t.setEncoding(Q3TextStream::UnicodeUTF8);
      t<<s;
      f.close();
   }
}
