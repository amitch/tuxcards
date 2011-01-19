/***************************************************************************
                          configgroup.cpp  -  description
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
#include "configgroup.h"
#include <iostream>
//Added by qt3to4:
#include <Q3PtrList>

ConfigGroup::ConfigGroup(QString groupName)
 : entries( NULLPTR )
{
	name=groupName;
	entries=new Q3PtrList<QString>;
}


ConfigGroup::~ConfigGroup(){ DELETE( entries ); }

QString ConfigGroup::getName(){ return name; }
	
void ConfigGroup::addEntry(QString name, QString value){
	entries->append(new QString(name));
	entries->append(new QString(value));
}

void ConfigGroup::changeEntry(QString name, QString value){
	QString* n; int counter=-1; bool done=false;
	
	for ( n=entries->first(); (n!=0 && !done); n=entries->next() ){
		counter++;
		if (counter/2*2==counter
				&& (*n)==name){		// found it -> go on and change it
			entries->remove(counter+1);
			entries->insert(counter+1, new QString(value));
			
			done=true;
		}	
	}

	if(!done) addEntry(name, value);			// if the entry did not ex. -> it is created
}

/**
 * returns the value of the entry 'name'
 * if it is not found '0' is returned
 */	
QString ConfigGroup::getValue(QString name){
	QString* x;     											// to walk through the list
	QString* s=new QString("-1none");			// to hold the result

	//cerr<<"wir suchen: '"<<name<<"'"<<endl;

		
	if (entries->first()){
  	for ( x=entries->first(); (x!=0 && s!=0); x=entries->next() ){
			//cerr<<"  finden: '"<<(*x)<<"'"<<endl;
  		if((*x)==name) s=entries->next();
  		x=entries->next();                   		// go one further (only every 2nd holds a name)
  	}
	}
	
	return ((*s)=="-1none" ? QString("-1none") : (*s));
}

QString ConfigGroup::toString(){
	QString s="["+name+"]\n";
	QString* n;
	
	for ( n=entries->first(); n!=0; n=entries->next() ){
		s.append(*n); 								s.append("=");
		s.append(*(entries->next())); s.append("\n");
	}
	
	return s;
}
