/***************************************************************************
                          search.cpp  -  description
                             -------------------
    begin                : Sun Mar 26 2000
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
#include "searchdialog.h"
#include <iostream>

#include <qtabwidget.h>
#include <qlayout.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <QLabel>

// -------------------------------------------------------------------------------
SearchDialog::SearchDialog( QWidget* pParent )
  : QDialog( pParent, "searchWindow", false )
// -------------------------------------------------------------------------------
{
   setMinimumWidth(550);					// height is set in 'go(..)' and 'setUp(..)'

   // general Layout
   Q3VBoxLayout* layout = new Q3VBoxLayout( this, 5, 5 );
   QTabWidget*  tabWidget = new QTabWidget( this );

   // search tab
   Q3VBox* pTab = new Q3VBox( tabWidget );
   pTab->setMargin(10);
   pTab->setSpacing(5);


   // general layout
//   QVBox* main=new QVBox(this); main->setMargin(10); main->setSpacing(5);

   // top
   Q3HBox* search=new Q3HBox( pTab ); search->setSpacing(10);
   (void) new QLabel("Search for:", search);
   edit=new QLineEdit( search ); edit->setMinimumWidth(200);
   QPushButton* go=new QPushButton( "Go", search );
   go->setDefault(TRUE);
   QPushButton* cancel=new QPushButton("Cancel", search);
   Q3ButtonGroup* cgroup = new Q3ButtonGroup(2, Qt::Horizontal, pTab);
   caseSensitive = new QCheckBox("Case &Sensitive", cgroup);
   searchTitles = new QCheckBox("Search Only &Titles", cgroup);

   // middle
   Q3ButtonGroup* bgroup = new Q3ButtonGroup(3, Qt::Horizontal, "Search in ...", pTab);
   bgroup->setMinimumHeight(50);
   QRadioButton* rb1 = new QRadioButton(".. &Whole tree", bgroup);
   rb1->setChecked(TRUE); tell(0);
   (void) new QRadioButton(".. active Entry and &Children", bgroup);
   (void) new QRadioButton(".. active &Entry only", bgroup);

   // bottom
   list=new Q3ListView( pTab ); //list->setMinimumHeight(70);
   list->addColumn("Entry"); list->addColumn("SearchResult");
   list->setColumnWidth(0, 150); list->setColumnWidth(1, 350);
   list->setSorting(-1);

   status=new QLabel("", pTab);

   // Communication
   connect( bgroup, SIGNAL(pressed(int)), this, SLOT(tell(int)) );
   connect( edit, SIGNAL(returnPressed()),this, SLOT(startSearching()) );
   connect( go, SIGNAL(clicked()),        this, SLOT(startSearching()) );
   connect( cancel, SIGNAL(clicked()),    this, SLOT(reject()) );
   connect( list, SIGNAL(selectionChanged(Q3ListViewItem*)), this, SLOT(selectionChange(Q3ListViewItem*)) );


   // search tab created
   tabWidget->insertTab( pTab, "Search" );
   layout->addWidget( tabWidget );
}



// -------------------------------------------------------------------------------
int SearchDialog::setUp( CTreeElement* rootTreeElement,
                                                   CTreeElement* activeTreeElement)
// -------------------------------------------------------------------------------
{
  this->rootTreeElement   = rootTreeElement;
  this->activeTreeElement = activeTreeElement;
  status->setText("");

  list->hide();
  this->resize(550, 150);

  edit->selectAll();
  edit->setFocus();

  show();
  return exec();
}



/**
 * start searching
 */
// -------------------------------------------------------------------------------
void SearchDialog::startSearching( void )
// -------------------------------------------------------------------------------
{
  status->setText("Searching ...");

  // clear list
  Q3ListViewItem* dummy;
  if ( list->firstChild() )
  {
    // 'list' is not empty
    dummy = list->firstChild();
    list->setSelected(dummy, true);

    while(list->childCount()>1)
    {
      Q3ListViewItem* pNextSibling = dummy->nextSibling();
      DELETE( pNextSibling );
    }
  }
  else
  {
    dummy = 0;
  }

  // showing list
  list->show();
  resize(550, 350);

  QString text=edit->text();
  if (text.length()==0) return;
  int mode=whatMode();

  // searching
  if (mode==0)              // search whole tree
    rootTreeElement->search(edit->text(), true, caseSensitive->isOn(),
    												searchTitles->isOn(), *list);
  else if(mode==1)          // search active entry and children
    activeTreeElement->search(edit->text(), true, caseSensitive->isOn(),
    												searchTitles->isOn(), *list);
  else if(mode==2)          // search active entry only
    activeTreeElement->search(edit->text(), false, caseSensitive->isOn(),
    												searchTitles->isOn(), *list);


  // remove rest of old list if exists (select an item above
  //                                    or below and delete 'x')
  bool resultsShown=false;
  if (dummy && (list->childCount()>1)){
    if (dummy->itemBelow())
      list->setSelected(dummy->itemBelow(),true);
    else
      list->setSelected(dummy->itemAbove(),true);

    DELETE( dummy );
    status->setText("<b>"+QString::number(list->childCount())+" matches found.</b>");
    resultsShown=true;
  }else if(dummy && (list->childCount()==1)){
    // no new item, but an old undeleted one
    list->hide(); this->resize(550, 150);
    status->setText("<b>No match found.</b>");
    resultsShown=true;
  }else{
    status->setText("<b>"+QString::number(list->childCount())+" matches found.</b>");
    resultsShown=true;
  }

  // exceptional case; not really expected
  if (!resultsShown)
    status->setText("<b>"+QString::number(list->childCount())+" matches found.</b>");
}



// -------------------------------------------------------------------------------
void SearchDialog::tell(int id)
// -------------------------------------------------------------------------------
{ choice=id; }


// -------------------------------------------------------------------------------
QString SearchDialog::getText( void )
// -------------------------------------------------------------------------------
{ return edit->text(); }


// -------------------------------------------------------------------------------
int SearchDialog::whatMode( void )
// -------------------------------------------------------------------------------
{ return choice; }



// -------------------------------------------------------------------------------
void SearchDialog::selectionChange( Q3ListViewItem* x )
// -------------------------------------------------------------------------------
{
  emit makeVisible( ((SearchListItem*)x)->getSearchPosition() );
/*  emit makeVisible((CTreeElement*)( ((SearchListItem*)x) ->getReferenceKnoten() ),
                    ((SearchListItem*)x) ->getLine(),
                    ((SearchListItem*)x) ->getPos(),
                    ((SearchListItem*)x) ->getLen()   );
*/
}

/**
 * this is a slot which is called from 'Tree' as soon
 * as a CTreeElement is deleted
 */
// -------------------------------------------------------------------------------
void SearchDialog::close( void )
// -------------------------------------------------------------------------------
{ reject(); }
