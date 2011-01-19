/***************************************************************************
                          CInformationElement.h  -  description
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
#ifndef CINFORMATIONELEMENT_H
#define CINFORMATIONELEMENT_H

#include "IParent.h"
#include <iostream>
#include <qstring.h>
//Added by qt3to4:
#include <QPixmap>
#include <Q3PtrList>
#include "informationformat.h"
#include <qobject.h>
#include <q3listview.h>
#include <q3textedit.h>

#include <qdatetime.h>

#include <Qt/qdom.h>


class CInformationElement : public QObject,
                            public IParent
{
  Q_OBJECT
public:
  CInformationElement( IParent* pParent,
                     QString sDescription="", QString sInformation="",
                     InformationFormat* pFormat=&InformationFormat::NONE,
                     QString sIconFileName = "none");
  ~CInformationElement( void );

  // ************* IParent *****************************************
  virtual QString  getDescription( void );
  virtual IParent* getParent( void );
  virtual void     removeChild( CInformationElement* pChild );
  virtual void     aboutToRemoveElement( CInformationElement* pIE );
  // ************* IParent - End ***********************************

  void setBatched( bool );
  bool isBatched( void ) const;

  virtual void addChild( CInformationElement* pElement );
  Q3PtrList<CInformationElement>* getChildren( void );
  int childCount( void ) const;
  void setParent( IParent* pParent = 0 );

  void deleteSelf( void );

  void    setDescription( QString );
  QString getInformation( void ) const;
  void    setInformation( const QString& );
  QString getInformationText( void ) const;
  void    appendInformation( QString text );

  bool    hasIcon( void ) const;
  void    setIcon(QPixmap);
  void    setIconFileName( const QString& );
  QString getIconFileName( void ) const;

  InformationFormat* getInformationFormat( void ) const;
  void    setInformationFormat( InformationFormat* );

  QString toString( void ) const;
  QString getTreeString(int tab=0) const;
  virtual void toXML( QDomDocument xmlDocument, QDomNode parent );

  void search( QString pattern, bool recursive, bool caseSensitive, bool SearchOnlyTitles,
  						Q3ListView& list );

  CInformationElement* findChildWithDescription( QString desc );


  void  setInformationYPos( int iPos );
  int   getInformationYPos( void ) const;

  void  enableEncryption( bool bIsEncryptionEnabled, const QString& sTmpPasswd  );
  bool  isEncryptionEnabled( void ) const;
  bool  isCurrentlyEncrypted( void ) const;
  void  encrypt( void );
  bool  decrypt( const QString& sPasswd );
  const QByteArray& getEncryptedData() const;
  void  setEncryptedData( const QByteArray& data );

	void enableEncryptionForElementTree(QString& password);
	void disableEncryptionForElementTree();
	bool checkEncryptionForElementTree();
	bool decryptTree(QString password);

	void setTextColor(QColor& c);
	QColor getTextColor() const;
	void setSubTreeTextColor(QColor& c);

signals:
  void propertyChanged( void );
  void childAdded( CInformationElement* );
  void childMoved( int oldPos, int newPos );
  void informationHasChanged( void );


protected:
   // Returns a pointer to the parent element. If this informationElement
   // is the root element, then the mpParent ptr contains a pointer to the
   // collection.
  IParent*            mpParent;

  // this should reduce update-behavior;
  // if batched==true -> the signal 'propertyChanged()' is not emitted
  bool                mbBatched;

  QString             mDescription;
  InformationFormat*  mpInformationFormat;
  QString             mInformation;
  QPixmap             mIcon;
  QString             mIconFilename;

  Q3PtrList<CInformationElement>* mpChildObjects;

  int                 miInformationYPos;


  bool                mbIsEncryptionEnabled;
  QString             msTmpPasswd;
  QByteArray          mEncryptedData;

  QColor 			  mtextColor;
  QColor 			  msubtreeTextColor;

private:
  void searchLine( QString pattern, bool caseSensitive, Q3ListView& list, QString oneLine,
                  int lineNumber, int searchLocation );
  void searchDescription( QString pattern, bool caseSensitive, Q3ListView& list );
  void searchInformation( QString pattern, bool caseSensitive, Q3ListView& list );
};
#endif

