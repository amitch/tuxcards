/***************************************************************************
                          configparser.cpp  -  description
                             -------------------
    begin                : Fri Apr 28 2000
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

#include "../../global.h"
#include "configparser.h"
#include <iostream>
//Added by qt3to4:
#include <Q3TextStream>
#include <Q3PtrList>

/**
 * Constructor
 * opens file 'fileName' and tries to read it ('fileName' should be absolute)
 *
 * if file exists/is readable & if at least one 'ConfigGroup' was found (i.e
 * something like "[GroupName]") -> 'ready' is set to true
 *
 * !!! lines that have only an 'enter' or 'return' cannot be read correctly !!!
 * -> if you want to have a clear line -> put a 'space' at the first position of that line
 */
ConfigParser::ConfigParser(QString fileName, bool writeAtOnce){
	this->fileName=fileName;
	this->writeAtOnce=writeAtOnce;
	
	ready=false; currentGroup=0;
	list=new Q3PtrList<ConfigGroup>;
	
	QFile f(fileName);
	if(f.exists() && f.open(QIODevice::ReadOnly) ) {	// file opened successfully
		
		Q3TextStream t( &f );         						// use a text stream
		QString s;
		
		while ( !t.eof() ) {         			// until end of file...
			QString s=t.readLine();

			if( !((s.left(1)=="#") || (s.left(1)==" ")) ){	// ignore comments(they start with ' ' or '#')
				if (s.left(1)=="["){													// group found

					//extract name
					int i=s.find(']');	
					if (i==-1) i=s.length()-1;									// error in config-file -> it is "overridden"
				
					ready=true;
					currentGroup=new ConfigGroup(s.mid(1, i-1));

					list->append(currentGroup);
				}else{																			  // config-entry expected
					if(currentGroup){														//check whether a group is set
						int i=s.find('=');	
						if (i==-1) i=s.length()-2;									// error in config-file -> it is "overridden"
				
						currentGroup->addEntry( s.left(i), s.mid(i+1) );
					}
					
					
				}
 			}// if no comment
		
		}// while not eof
		f.close();
	}// if file exists

	//cerr<<"\nreading configuration:\n"<<toString()<<"---"<<endl;
}

ConfigParser::~ConfigParser(){
	DELETE( list );
	DELETE( currentGroup );
}

/**
 * states whether config-file was read correctly
 */
bool ConfigParser::correct(){ return ready; }

/**
 * if a group with the name 'g' exists -> this one is set to 'currentGroup'
 * -> if not -> a group called 'g' is created and set to 'currentGroup'
 */
void ConfigParser::setGroup(QString g){

	ConfigGroup* x;     // to walk through the list
	ConfigGroup* y=0;		// to hold the result
	
	for( x=list->first(); (x!=0 && y==0); x=list->next() )		
		if (x->getName() == g) y=x;

	if(!y){
		y=new ConfigGroup(g);
		list->append(y);
		if (writeAtOnce) writeChanges();
	}
	currentGroup=y;
}

QString ConfigParser::getCurrentGroup(){
	return currentGroup->getName();
}

/**
 * returns the value of the entry 'name'
 * if it does not exist -> the 'alternative' is returned
 */
QString ConfigParser::readEntry(QString name, QString alternative){
	QString s=currentGroup->getValue(name);
	return (s=="-1none" ? alternative : s);
}

/**
 * returns the value of the entry 'name'
 * if it does not exist -> the 'alternative' is returned
 *
 * same as 'readEntry(..)' only that the value is interpreted as int
 */
int ConfigParser::readNumEntry(QString name, int alternative){
	QString s=currentGroup->getValue(name);
	return (s=="-1none" ? alternative : s.toInt() );
}

/**
 * changes the value of 'name' to 'value'
 * if an entry called 'name' does not ex. -> it is created
 */	
void ConfigParser::changeEntry(QString name, QString value){
	currentGroup->changeEntry(name, value);
	
	if (writeAtOnce) writeChanges();
}
/**
 * same methode as above, only that we handle an 'int' and not a 'QString'
 */
void ConfigParser::changeEntry(QString name, int value){
	currentGroup->changeEntry(name, QString::number(value));
	
	if (writeAtOnce) writeChanges();
}

/**
 * writes the current configuration to file
 */
void ConfigParser::writeChanges(){
	QFile f(fileName);
	
	if ( f.open(QIODevice::WriteOnly) ) {
		Q3TextStream t( &f );
		t<<toString();

		f.close();
	}	
}


QString ConfigParser::toString(){
  QString s="#\n"
            "# TuxCards Configuration File\n"
            "#\n";
	ConfigGroup* x;
	
	for( x=list->first(); x!=0; x=list->next() )
		s.append(x->toString());

	return s;
}
