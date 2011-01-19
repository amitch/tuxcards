/***************************************************************************
                          editor.cpp  -  description
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
#include "editor.h"

#include <q3stylesheet.h>
#include <qregexp.h>
//Added by qt3to4:
#include <QKeyEvent>
#include "../CTuxCardsConfiguration.h"
#include "../utilities/strings.h"

#include <qapplication.h>


// -------------------------------------------------------------------------------
Editor::Editor( QWidget *pParent, const char *pName )
  : Q3TextEdit( pParent, pName )
  , mpActiveElement( NULLPTR )
  , SEMAPHORE_TEXT_WAS_SET( FALSE )
// -------------------------------------------------------------------------------
{
  initialize();
}


// -------------------------------------------------------------------------------
Editor::~Editor( void )
// -------------------------------------------------------------------------------
{
   mpActiveElement = NULLPTR;
}



// ************** IView *********************************************************
// -------------------------------------------------------------------------------
void Editor::aboutToRemoveElement( CInformationElement* pIE )
// -------------------------------------------------------------------------------
{
   if ( mpActiveElement == pIE )
   {
      mpActiveElement = NULLPTR;
   }
}
// ************** IView - End ****************************************************


/**
 * returns the complete Text
 */
// -------------------------------------------------------------------------------
QString Editor::getText( void )
// -------------------------------------------------------------------------------
{
  return text();
}



// -------------------------------------------------------------------------------
void Editor::setText( QString text )
// -------------------------------------------------------------------------------
{
  SEMAPHORE_TEXT_WAS_SET = TRUE;
  Q3TextEdit::setText(text);
}




/**
 * Rereads the information from the currently active
 * informationElement; usually in course of the event
 * 'CInformationElement::informationHasChanged()'.
 */
// -------------------------------------------------------------------------------
void Editor::rereadInformation( void )
// -------------------------------------------------------------------------------
{
   if ( NULLPTR == mpActiveElement )
      return;

   setText( mpActiveElement->getInformation() );
}



// -------------------------------------------------------------------------------
void Editor::clear( void )
// -------------------------------------------------------------------------------
{
  initialize();
}



// -------------------------------------------------------------------------------
void Editor::initialize( void )
// -------------------------------------------------------------------------------
{
  setText("");
  Q3TextEdit::setAutoFormatting(AutoNone);
  mpActiveElement = NULLPTR;

  SEMAPHORE_TEXT_WAS_SET = FALSE;
  connect( this, SIGNAL(textChanged()), this, SLOT(sendUndoAvailableSignal()));
  connect( this, SIGNAL(textChanged()), this, SLOT(sendRedoAvailableSignal()));
}



/**
 * This method sends the signal 'undoAvailable()' because the base
 * class (qtextedit qt-3.0.5) does not send it correctly. But the
 * signal is not send whenever the text was set  with 'setText()'
 * method to prevent that the user gets the text from another
 * document while doing an undo.
 */
// -------------------------------------------------------------------------------
void Editor::sendUndoAvailableSignal( void )
// -------------------------------------------------------------------------------
{
  if ( isUndoAvailable() )
  {
    if ( SEMAPHORE_TEXT_WAS_SET )
      SEMAPHORE_TEXT_WAS_SET = FALSE;
    else
      emit undoAvailable( TRUE );
  }
}



/**
 * Similar to the method above ('sendUndoAvailableSignal()').
 * This method sends the signal 'redoAvailable()' because the base
 * class (qtextedit qt-3.0.5) does not send it correctly.
 */
// -------------------------------------------------------------------------------
void Editor::sendRedoAvailableSignal( void )
// -------------------------------------------------------------------------------
{
  if ( isRedoAvailable() )
    emit redoAvailable(true);
}




// -------------------------------------------------------------------------------
void Editor::writeCurrentTextToActiveInformationElement( void )
// -------------------------------------------------------------------------------
{
   if ( !mpActiveElement )
      return;

 	// saving cursor- and scrollbarPositions
//	int line, pos; getCursorPosition(&line, &pos);
//  int verticalScrollBarPosition   = verticalScrollBar()->value();
//  int horizontalScrollBarPosition = horizontalScrollBar()->value();

//  cout<<"vorher: Text "<<getText().contains("<br>")<<endl;
//  printBRs();
   mpActiveElement->setInformation(getText());
//  cout<<"nachher: Text "<<getText().contains("<br>")<<endl;
//  printBRs();

  // reset cursor- and scrollbarPositions
//  setCursorPosition(line, pos);
//  verticalScrollBar()->setValue(verticalScrollBarPosition);
//  horizontalScrollBar()->setValue(horizontalScrollBarPosition);
}


// -------------------------------------------------------------------------------
void Editor::setWordWrap( int wordWrap )
// -------------------------------------------------------------------------------
{
  if( wordWrap == 0 )
    Q3TextEdit::setWordWrap(Q3TextEdit::NoWrap);
  else if( wordWrap == 1 )
    Q3TextEdit::setWordWrap(Q3TextEdit::WidgetWidth);
  else
  {
    Q3TextEdit::setWordWrap(Q3TextEdit::FixedColumnWidth);
    Q3TextEdit::setWrapColumnOrWidth(wordWrap);
  }
}



/**
 * Ignores the key combinations we need within 'mainwindow'.
 */
// -------------------------------------------------------------------------------
void Editor::keyPressEvent( QKeyEvent* pKeyEv )
// -------------------------------------------------------------------------------
{
   if ( !pKeyEv )
      return;

   //std::cout<<"key = "<<pKeyEv->key();

   // If
   //   CTRL + S (save)  or
   //   ALT + left  cursor (history one back / previous entry) or
   //   ALT + right cursor (history one forward / next entry)
   //   CTRL + F (shortcut for "Searching")
   // is called, then ignore it.
   if( ( (pKeyEv->state() == Qt::ControlButton)  &&  (pKeyEv->key() == Qt::Key_S) ) ||
       ( (pKeyEv->state() == Qt::AltButton)      &&  (pKeyEv->key() == Qt::Key_Left) ) ||
       ( (pKeyEv->state() == Qt::AltButton)      &&  (pKeyEv->key() == Qt::Key_Right) ) ||
       ( (pKeyEv->state() == Qt::ControlButton)  &&  (pKeyEv->key() == Qt::Key_F) ) )
   {
      //std::cout<<" -> ignore"<<std::endl;
      pKeyEv->ignore();
   }
/*

   // if the shift button is down while pressing return or enter, insert a new paragraph
   else if  ( ( (pKeyEv->state() == Qt::ShiftButton ) || (pKeyEv->state() == Qt::ControlButton ) )
              &&
              ( (Qt::Key_Return == pKeyEv->key()) || (Qt::Key_Enter == pKeyEv->key()) )
            )
   {
      if ( LINEBREAK_MODERN == meLinebreakMode )
      {
         //std::cout<<" -> shift/ctrl + enter/return"<<std::endl;
         Q3TextEdit::keyPressEvent( new QKeyEvent( pKeyEv->type(),  Qt::Key_Return,
                                                  pKeyEv->ascii(), 0 ) );
      }
      else
      {
         Q3TextEdit::keyPressEvent( pKeyEv );
      }
   }
*/
   // Workaround Q3TextEdit's default Enter key behavior of adding a paragraph
   // Add control key pressed to it
   else if  ( (Qt::Key_Return == pKeyEv->key()) || (Qt::Key_Enter == pKeyEv->key()) )
   {
         Q3TextEdit::keyPressEvent( new QKeyEvent( pKeyEv->type(),  Qt::Key_Return,
                                                  pKeyEv->ascii(), Qt::ControlButton ) );
   }

   // CTRL + A -> select all
   else if ( (Qt::ControlButton == pKeyEv->state()) && (Qt::Key_A == pKeyEv->key()) )
   {
      selectAll();
   }

   // CTRL + B -> bold
   else if ( (Qt::ControlButton == pKeyEv->state()) && (Qt::Key_B == pKeyEv->key()) )
   {
      if ( Qt::RichText == textFormat() )
         setBold( !bold() );
   }

   // CTRL + I -> italic
   else if ( (Qt::ControlButton == pKeyEv->state()) && (Qt::Key_I == pKeyEv->key()) )
   {
      if ( Qt::RichText == textFormat() )
         setItalic( !italic() );
   }

   // CTRL + U -> underline
   else if ( (Qt::ControlButton == pKeyEv->state()) && (Qt::Key_U == pKeyEv->key()) )
   {
      if ( Qt::RichText == textFormat() )
         setUnderline( !underline() );
   }

   else
   {
      // otherwise call the super-method
      //std::cout<<std::endl;
      Q3TextEdit::keyPressEvent( pKeyEv );
   }
}


/**
 * Responses to the change of the active informationelement.
 * Saves the information of the old one and displays the new one.
 */
// -------------------------------------------------------------------------------
void Editor::activeInformationElementChanged( CInformationElement* pElement )
// -------------------------------------------------------------------------------
{
/*  QMimeSourceFactory::defaultFactory()->setPixmap("newImg", QPixmap("/home/alex/aufgehoben/bilder/alex.gif"));
  setText( " Hier ist ein Bild <img source=\"newImg\">." );
return;
*/

   if ( !pElement )
      return;

   //std::cout<<"Editor::activeInformationElementChanged()"<<std::endl;
   //std::cout<<"\tnew Element: "<<pElement->getDescription()<<std::endl;
   if ( mpActiveElement )
   {
      disconnect( mpActiveElement, SIGNAL(informationHasChanged()), this, SLOT(rereadInformation()) );

      writeCurrentTextToActiveInformationElement();
      mpActiveElement->setInformationYPos( contentsY() );
   }

   if ( pElement->getInformationFormat() == &InformationFormat::RTF )
   {
      emit formatRecognized( InformationFormat::RTF );
      setTextFormat( Qt::RichText );
   }
   else if ( pElement->getInformationFormat() == &InformationFormat::ASCII )
   {
      emit formatRecognized( InformationFormat::ASCII );
      setTextFormat( Qt::PlainText );
   }

   setText( pElement->getInformation() );
   sync();
   setContentsPos( 0, pElement->getInformationYPos() );

   mpActiveElement = pElement;
   connect( mpActiveElement, SIGNAL(informationHasChanged()), this, SLOT(rereadInformation()) );
}


// -------------------------------------------------------------------------------
void Editor::printBRs( void )
// -------------------------------------------------------------------------------
{
  std::cout<<countBRs()<<std::endl;
}


// -------------------------------------------------------------------------------
int Editor::countBRs( void )
// -------------------------------------------------------------------------------
{
   if ( !mpActiveElement )
      return 0;

   return mpActiveElement->getInformation().count("<br />");
}


/**
 * Override the regular paste() methode, so that lines are
 * not separated by each other with an blank line.
 */
// -------------------------------------------------------------------------------
void Editor::paste()
// -------------------------------------------------------------------------------
{
   //QClipboard *cb = QApplication::clipboard();
   //for (int i=0; i<20; i++)
   //    std::cout<<"\tformat="<<cb->data()->format(i)<<std::endl;

   // Selection clipboard, applies only to X11 (Unix) systems
   if (QApplication::clipboard()->supportsSelection())
     adaptClipboardText( QClipboard::Selection );

   adaptClipboardText( QClipboard::Clipboard );

//   QByteArray pasteType ("text/html");
//   Q3TextEdit::pasteSubType(pasteType);
   Q3TextEdit::paste();
   return;

}


/**
 * Auxiliar method that takes the text from the clipboard - using the
 * specified 'mode' -, replaces all '\n' within that text and writes
 * it back to the clipboard.
 */
// -------------------------------------------------------------------------------
void Editor::adaptClipboardText( QClipboard::Mode mode )
// -------------------------------------------------------------------------------
{
    QClipboard* pCb = QApplication::clipboard();
    if ( NULLPTR == pCb )
      return;


    // Printing format strings
    const QMimeData *mimeData = pCb->mimeData(mode);

    if(mimeData) {
    	QStringList mimeFormatList = mimeData->formats ();

    	std::cout << "adaptClipboardText: Printing mime formats" << std::endl;
        for (int i = 0; i < mimeFormatList.size(); ++i)
        	std::cout << mimeFormatList.at(i).toLocal8Bit().constData() << std::endl;
    }

    QString text = pCb->text(mode);
	QStringList mimeFormatList = pCb->mimeData(mode)->formats();

    if (!text.isEmpty() && !mimeFormatList.contains("application/x-qrichtext"))
    {
    	// do not create new paragraphs
    	text = text.replace(QRegExp("\\n"), QChar( 0x2028));
    	pCb->setText( text, mode );
    }


    const QMimeData *mimeData2 = pCb->mimeData(mode);
    if(mimeData2) {
    	QStringList mimeFormatList = mimeData2->formats ();

    	std::cout << "adaptClipboardText: Printing mime formats, after" << std::endl;
        for (int i = 0; i < mimeFormatList.size(); ++i)
        	std::cout << mimeFormatList.at(i).toLocal8Bit().constData() << std::endl;
    }
}
