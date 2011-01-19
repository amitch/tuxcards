/***************************************************************************
                          CInformationElement.cpp  -  description
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

#include "CInformationElement.h"
#include "../global.h"
#include "../utilities/strings.h"
#include "../gui/dialogs/searchlistitem.h"

#include <qregexp.h>
//Added by qt3to4:
#include <QPixmap>
#include <Q3PtrList>
#include "../utilities/crypt/StringCrypter.h"


// -------------------------------------------------------------------------------
CInformationElement::CInformationElement( IParent* pParent,
                                        QString sDescription,
                                        QString sInformation,
                                        InformationFormat* pFormat,
                                        QString sIconFileName)
 : mpParent( pParent )
 , mbBatched( false )
 , mDescription( sDescription )
 , mpInformationFormat( pFormat )
 , mInformation( sInformation )
 , mIcon()
 , mIconFilename( sIconFileName )
 , mpChildObjects( NULLPTR )
 , miInformationYPos( 0 )
 , mbIsEncryptionEnabled( false )
 , msTmpPasswd( "" )
 , mEncryptedData()
 , mtextColor (Qt::black)
 , msubtreeTextColor (Qt::black)
// -------------------------------------------------------------------------------
{
   mpChildObjects = new Q3PtrList<CInformationElement>();
   if ( NULLPTR == mpChildObjects )
   {
      std::cout<<"TuxCards-ERROR: in constructor 'CInformationElement'\n"
               <<"NULLPTR == mpChildObjects\n"
               <<"Not enough memory to create objects. TuxCards might crash."
               <<std::endl;
      return;
   }
   mpChildObjects->setAutoDelete( true );

   if (!mbBatched) emit propertyChanged();
}

// -------------------------------------------------------------------------------
CInformationElement::~CInformationElement( void )
// -------------------------------------------------------------------------------
{
   //std::cout<<"\t~CIE: "<<getDescription()<<std::endl;

   if ( NULLPTR != mpChildObjects )
   {
      mpChildObjects->clear();
   }

   DELETE( mpChildObjects );
   mpInformationFormat = NULLPTR;

   if ( NULLPTR != mpParent )
   {
      mpParent->aboutToRemoveElement(this);
      mpParent = NULLPTR;
   }
}




// **************************** IParent ******************************************
// -------------------------------------------------------------------------------
QString CInformationElement::getDescription( void )
// -------------------------------------------------------------------------------
{
  return mDescription;
}
// -------------------------------------------------------------------------------
IParent* CInformationElement::getParent( void )
// -------------------------------------------------------------------------------
{
   return mpParent;
}

// -------------------------------------------------------------------------------
void CInformationElement::removeChild( CInformationElement* pChild )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpChildObjects )
      return;

   // autodeletion is set to true (look at constructor)
   mpChildObjects->removeRef( pChild );
}

// -------------------------------------------------------------------------------
void CInformationElement::aboutToRemoveElement( CInformationElement* pIE )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR != mpParent )
      mpParent->aboutToRemoveElement(pIE);
}
// **************************** IParent - End ************************************



// -------------------------------------------------------------------------------
void CInformationElement::deleteSelf( void )
// -------------------------------------------------------------------------------
{
  //cout<<"IE::deleteSelf(); parent="<<mpParent<<endl;
   if ( NULLPTR == mpParent )
      return;

   mpParent->removeChild(this);
}

// -------------------------------------------------------------------------------
void CInformationElement::setParent( IParent* pParent )
// -------------------------------------------------------------------------------
{
  mpParent = pParent;
}


// -------------------------------------------------------------------------------
void CInformationElement::setBatched( bool b )
// -------------------------------------------------------------------------------
{
   mbBatched = b;
   if (!mbBatched) emit propertyChanged();
}
// -------------------------------------------------------------------------------
bool CInformationElement::isBatched( void ) const
// -------------------------------------------------------------------------------
{
  return mbBatched;
}

// -------------------------------------------------------------------------------
void CInformationElement::addChild( CInformationElement* pElement )
// -------------------------------------------------------------------------------
{
   if ( (NULLPTR == pElement) || (NULLPTR == mpChildObjects) )
      return;

   mpChildObjects->append( pElement );
   // If subtree color is set, set it for this node too
   if(msubtreeTextColor != Qt::black)
	   pElement->setSubTreeTextColor(msubtreeTextColor);

   if (!mbBatched) emit childAdded( pElement );
}
// -------------------------------------------------------------------------------
Q3PtrList<CInformationElement>* CInformationElement::getChildren( void )
// -------------------------------------------------------------------------------
{
  return mpChildObjects;
}
// -------------------------------------------------------------------------------
int CInformationElement::childCount( void ) const
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpChildObjects )
      return 0;

   return mpChildObjects->count();
}


// -------------------------------------------------------------------------------
void CInformationElement::setDescription( QString description )
// -------------------------------------------------------------------------------
{
  mDescription = description;
  if (!mbBatched) emit propertyChanged();
}

// -------------------------------------------------------------------------------
QString CInformationElement::getInformation( void ) const
// -------------------------------------------------------------------------------
{
  return mInformation;
}

// -------------------------------------------------------------------------------
void CInformationElement::setInformation( const QString& information )
// -------------------------------------------------------------------------------
{
  mInformation = information;
  if (!mbBatched) emit propertyChanged();
}


// -------------------------------------------------------------------------------
bool CInformationElement::hasIcon( void ) const
// -------------------------------------------------------------------------------
{
  return !mIcon.isNull();
}

// -------------------------------------------------------------------------------
void CInformationElement::setIcon( QPixmap icon )
// -------------------------------------------------------------------------------
{
  mIcon = icon;
  if (!mbBatched) emit propertyChanged();
}
// -------------------------------------------------------------------------------
void CInformationElement::setIconFileName( const QString& file )
// -------------------------------------------------------------------------------
{
  mIconFilename = file;
  if (!mbBatched) emit propertyChanged();
}
// -------------------------------------------------------------------------------
QString CInformationElement::getIconFileName( void ) const
// -------------------------------------------------------------------------------
{
  return (!mIconFilename.isEmpty() ? mIconFilename : QString("none"));
}

// -------------------------------------------------------------------------------
InformationFormat* CInformationElement::getInformationFormat( void ) const
// -------------------------------------------------------------------------------
{
  return mpInformationFormat;
}

// -------------------------------------------------------------------------------
void CInformationElement::setInformationFormat( InformationFormat* pFormat )
// -------------------------------------------------------------------------------
{
  mpInformationFormat = pFormat;
  if (!mbBatched) emit propertyChanged();
}

// -------------------------------------------------------------------------------
QString CInformationElement::toString( void ) const
// -------------------------------------------------------------------------------
{
  QString result = mDescription+" ["+mpInformationFormat->toString()+"]\n"
                   +mInformation;
  return result;
}

// -------------------------------------------------------------------------------
QString CInformationElement::getTreeString( int tab ) const
// -------------------------------------------------------------------------------
{
  QString result = Strings::spaces(tab)+mDescription+"\n";
  tab++;

  if ( NULLPTR == mpChildObjects )
    return result;

  Q3PtrListIterator<CInformationElement> it(*mpChildObjects);
  CInformationElement* x;
  while( (x = it.current()) != 0 ){
    ++it;
    result += x->getTreeString(tab);
  }

  return result;
}

// -------------------------------------------------------------------------------
void CInformationElement::toXML( QDomDocument xmlDocument, QDomNode parent )
// -------------------------------------------------------------------------------
{
  QDomElement thisElement = xmlDocument.createElement("InformationElement");
  thisElement.setAttribute("informationFormat", getInformationFormat()->toString());
  thisElement.setAttribute("iconFileName", getIconFileName());

  // add description
  QDomElement description = xmlDocument.createElement("Description");
  QDomText text = xmlDocument.createTextNode(getDescription());
  description.appendChild(text);
  thisElement.appendChild(description);

  // add information
  QDomElement information = xmlDocument.createElement("Information");
  text = xmlDocument.createTextNode(getInformation());
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


// -------------------------------------------------------------------------------
CInformationElement* CInformationElement::findChildWithDescription( QString desc )
// -------------------------------------------------------------------------------
{
  Q3PtrListIterator<CInformationElement> it(*mpChildObjects);
  CInformationElement* x;
  while( (x = it.current()) != 0 )
  {
    ++it;
    if (x->getDescription() == desc)
      return x;
  }

  return NULLPTR;
}


/**
 * find the specified 'QString pattern' within the text/information of the
 * appropriate 'CInformationElement' (evtl. recursive) and append the found
 * "places" as 'SearchListItem's at the list's end.
 */
// -------------------------------------------------------------------------------
void CInformationElement::search( QString pattern, bool recursive, bool caseSensitive,
                                  bool SearchOnlyTitles, Q3ListView& list)
// -------------------------------------------------------------------------------
{
  searchDescription(pattern, caseSensitive, list);
  if (!SearchOnlyTitles)
	  searchInformation(pattern, caseSensitive, list);


  // if recursive -> do so
  if (recursive)
  {
    Q3PtrListIterator<CInformationElement> it(*mpChildObjects);
    CInformationElement* x;
    while( (x = it.current()) != 0 )
    {
      ++it;
      x->search( pattern, true, caseSensitive, SearchOnlyTitles, list );
    }
  }
}


// -------------------------------------------------------------------------------
void CInformationElement::searchLine( QString pattern, bool caseSensitive,
                                      Q3ListView& list, QString line,
                                      int lineNumber, int searchLocation )
// -------------------------------------------------------------------------------
{
  int pos = line.find(pattern, 0, caseSensitive);
  while (pos >= 0)
  {
    // found something -> add it to 'list'

	// Removed everything before the search string
    QString listtext = line;
	listtext.remove(0, pos);

	// Limit length to a certain limit so no wrap around happens.
    listtext.truncate(MAX_SEARCHLIST_STRLEN);
    (void) new SearchListItem( &list, new Path(this), searchLocation,
                               lineNumber, pos, pattern.length(), listtext);

    // prepare for next evtl. occurance within this 'oneLine'
    pos = line.find( pattern, pos+pattern.length(), caseSensitive );
  }
}

// -------------------------------------------------------------------------------
void CInformationElement::searchDescription( QString pattern, bool caseSensitive,
                                             Q3ListView& list)
// -------------------------------------------------------------------------------
{
  searchLine( pattern, caseSensitive, list, mDescription, -1, SearchPosition::SP_NAME );
}

// -------------------------------------------------------------------------------
void CInformationElement::searchInformation( QString pattern, bool caseSensitive,
                                             Q3ListView& list )
// -------------------------------------------------------------------------------
{
  QString text = getInformationText() +"\n";    // add "\n" -> so, the last line is also searched
  QString oneLine;
  int line = -1;  //because first line is 0

  for (QString oneLine = Strings::removeAndReturnFirstLine(text); !oneLine.isNull();
	  oneLine = Strings::removeAndReturnFirstLine(text) )
  {
    line++;
    searchLine( pattern, caseSensitive, list, oneLine, line, SearchPosition::SP_INFORMATION);
  }

/*
  SearchRTF-Idee  (somit kann man regexp. auch in rtf-text suchen/finden)

  1) mit converter.cpp in ascii umwandeln
  2) paragraphenweise suchen, dabei gefundene Stellen als SearchListItem
    in die Liste eintragen.

*/
}


// -------------------------------------------------------------------------------
QString CInformationElement::getInformationText( void ) const
// -------------------------------------------------------------------------------
{
  QString text;

  if ( getInformationFormat() == &InformationFormat::ASCII )
  {
    text = getInformation();
  }
  else
  {
    text = Strings::removeHTMLTags(getInformation());
  }

  return text;
}


/**
 * Appends the specified text to the end of the information
 * of this element.
 */
// -------------------------------------------------------------------------------
void CInformationElement::appendInformation( QString text )
// -------------------------------------------------------------------------------
{
  if ( mpInformationFormat == &InformationFormat::RTF )
  {
    text.replace( QRegExp("\n"), "<br>\n" );
  }

  mInformation += text;
  emit informationHasChanged();
}


// -------------------------------------------------------------------------------
void CInformationElement::setInformationYPos( int iPos )
// -------------------------------------------------------------------------------
{
   miInformationYPos = iPos;
}

// -------------------------------------------------------------------------------
int CInformationElement::getInformationYPos( void ) const
// -------------------------------------------------------------------------------
{
   return miInformationYPos;
}


// -------------------------------------------------------------------------------
// Adds information so that the element has the capability to be encrypted.
// To encrypt the element call 'encrypt()'.
// -------------------------------------------------------------------------------
void CInformationElement::enableEncryption( bool bIsEncryptionEnabled,
                                            const QString& sTmpPasswd )
// -------------------------------------------------------------------------------
{
   mbIsEncryptionEnabled = bIsEncryptionEnabled;
   msTmpPasswd = mbIsEncryptionEnabled ? sTmpPasswd : QString("");
}

// -------------------------------------------------------------------------------
// States whether this element has the capability to be encrypted.
// To encrypt the element call 'encrypt()'.
// -------------------------------------------------------------------------------
bool CInformationElement::isEncryptionEnabled( void ) const
// -------------------------------------------------------------------------------
{
   return mbIsEncryptionEnabled;
}

// -------------------------------------------------------------------------------
// States whether this element is currently encrypted.
// -------------------------------------------------------------------------------
bool CInformationElement::isCurrentlyEncrypted( void ) const
// -------------------------------------------------------------------------------
{
   return ( 0 != mEncryptedData.size() );
}


// -------------------------------------------------------------------------------
// This encrypts the element and makes its contents unreadable.
// -------------------------------------------------------------------------------
void CInformationElement::encrypt( void )
// -------------------------------------------------------------------------------
{
   if ( !mbIsEncryptionEnabled )
      return;

   StringCrypter::encryptString( mInformation, msTmpPasswd, mEncryptedData );
   mInformation = "";
}

// -------------------------------------------------------------------------------
// This decrypts the element and makes its contents readable.
// Returns 'true' if everything is correct and element could be decrypted.
// -------------------------------------------------------------------------------
bool CInformationElement::decrypt( const QString& sPasswd )
// -------------------------------------------------------------------------------
{
	int iError;

	// Ignore empty encrypted data fields.
	// This typically would happen only for manually updates entries or bugs in Tuxcards
	if (mEncryptedData.size() == 0)
		return true;

   iError = StringCrypter::decryptString( mEncryptedData, sPasswd, mInformation );
   if ( StringCrypter::NO_ERROR == iError )
   {
      msTmpPasswd = sPasswd;
      mEncryptedData.resize(0);
   }
   else if (  StringCrypter::ERROR_INVALID_FILEHEADER == iError )
   {
      // this should never happen (if the user does not touch the data)
      std::cout<<"StringCrypter::ERROR_INVALID_FILEHEADER"<<std::endl;
   }

   return (StringCrypter::NO_ERROR == iError);
}


// -------------------------------------------------------------------------------
const QByteArray& CInformationElement::getEncryptedData() const
// -------------------------------------------------------------------------------
{
   return mEncryptedData;
}

// -------------------------------------------------------------------------------
void CInformationElement::setEncryptedData( const QByteArray& data )
// -------------------------------------------------------------------------------
{
   mEncryptedData = data;
   mbIsEncryptionEnabled = true;
}


// By enabling encryption, will save this item and it's subtree as encrypted
// -------------------------------------------------------------------------------
void CInformationElement::enableEncryptionForElementTree(QString& password)
{
	// Enable encryption for this entry and leave it unencrypted.
	enableEncryption(true, password);

	// Go through all children and call the same function for them.
	Q3PtrListIterator<CInformationElement> it(*mpChildObjects);
	CInformationElement* x;
	while( (x = it.current()) != 0 )
	{
    	x->enableEncryptionForElementTree(password);
	    ++it;
	}
}

// Will save this item and it's subtree as unencrypted
// -------------------------------------------------------------------------------
void CInformationElement::disableEncryptionForElementTree()
{
	// Disable encryption for this entry and leave it unencrypted.
	enableEncryption(false, QString(""));

	// Go through all children and call the same function for them.
	Q3PtrListIterator<CInformationElement> it(*mpChildObjects);
	CInformationElement* x;
	while( (x = it.current()) != 0 )
	{
    	x->disableEncryptionForElementTree();
	    ++it;
	}
}

// Will return true, if any of the element in the tree is encrypted.
// -------------------------------------------------------------------------------
bool CInformationElement::checkEncryptionForElementTree()
{
	if (isEncryptionEnabled())
		return true;

	// Go through all children and call the same function for them.
	Q3PtrListIterator<CInformationElement> it(*mpChildObjects);
	CInformationElement* x;
	while( (x = it.current()) != 0 )
	{
    	if (x->checkEncryptionForElementTree())
    		return true;
	    ++it;
	}
	return false;
}

// Decrypt's this element and it's children in the tree.
// -------------------------------------------------------------------------------
bool CInformationElement::decryptTree(QString password)
{
	bool bCorrectPasswd;

	// Decrypt this entry.
	if (isCurrentlyEncrypted()) {
//        std::cout << "Decrypting: " << mDescription.toStdString() << std::endl;
		bCorrectPasswd = decrypt(password);
		if (!bCorrectPasswd)
			return bCorrectPasswd;
	}

	// Go through all children and call the same function for them.
	Q3PtrListIterator<CInformationElement> it(*mpChildObjects);
	CInformationElement* x;
	while( (x = it.current()) != 0 )
	{
		if (x->isCurrentlyEncrypted()) {
	    	bCorrectPasswd = x->decryptTree(password);
			if (!bCorrectPasswd)
				return bCorrectPasswd;
		}
	    ++it;
	}
	return true;
}

// -------------------------------------------------------------------------------
void CInformationElement::setTextColor(QColor& c)
{
	mtextColor = c;
}

// -------------------------------------------------------------------------------
QColor CInformationElement:: getTextColor() const
{
	return mtextColor;
}

// -------------------------------------------------------------------------------
void CInformationElement::setSubTreeTextColor(QColor& c)
{
	// Set text color for current entry.
	msubtreeTextColor = mtextColor = c;

	// Go through all children and call the same function for them.
	Q3PtrListIterator<CInformationElement> it(*mpChildObjects);
	CInformationElement* x;
	while( (x = it.current()) != 0 )
	{
    	x->setSubTreeTextColor(c);
	    ++it;
	}
}
