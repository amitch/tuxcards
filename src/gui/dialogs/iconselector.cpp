/****************************************************************************
** $Id: qt/examples/fileiconview/qfileiconview.cpp   2.3.0   edited 2001-01-26 $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#include "../../global.h"
#include "iconselector.h"

#include <qstringlist.h>
#include <qpixmap.h>
#include <qmime.h>
#include <q3strlist.h>
#include <q3dragobject.h>
#include <qmessagebox.h>
#include <qevent.h>
#include <q3popupmenu.h>
#include <qcursor.h>
#include <qapplication.h>
#include <qmatrix.h>
#include <qpainter.h>
//Added by qt3to4:
#include <QKeyEvent>
#include <Q3ValueList>
#include <Q3CString>
#include <QDropEvent>

#include <stdlib.h>

static const char * folder_icon[]={
    "32 32 11 1",
    "# c #000000",
    "b c #c0c000",
    "d c #585858",
    "a c #ffff00",
    "i c #400000",
    "h c #a0a0a4",
    "e c #000000",
    "c c #ffffff",
    "f c #303030",
    "g c #c0c0c0",
    ". c None",
    "...###..........................",
    "...#aa##........................",
    ".###baaa##......................",
    ".#cde#baaa##....................",
    ".#cccdeebaaa##..##f.............",
    ".#cccccdeebaaa##aaa##...........",
    ".#cccccccdeebaaaaaaaa##.........",
    ".#cccccccccdeebababaaa#.........",
    ".#cccccgcgghhebbbbbbbaa#........",
    ".#ccccccgcgggdebbbbbbba#........",
    ".#cccgcgcgcgghdeebiebbba#.......",
    ".#ccccgcggggggghdeddeeba#.......",
    ".#cgcgcgcggggggggghghdebb#......",
    ".#ccgcggggggggghghghghd#b#......",
    ".#cgcgcggggggggghghghhd#b#......",
    ".#gcggggggggghghghhhhhd#b#......",
    ".#cgcggggggggghghghhhhd#b#......",
    ".#ggggggggghghghhhhhhhdib#......",
    ".#gggggggggghghghhhhhhd#b#......",
    ".#hhggggghghghhhhhhhhhd#b#......",
    ".#ddhhgggghghghhhhhhhhd#b#......",
    "..##ddhhghghhhhhhhhhhhdeb#......",
    "....##ddhhhghhhhhhhhhhd#b#......",
    "......##ddhhhhhhhhhhhhd#b#......",
    "........##ddhhhhhhhhhhd#b#......",
    "..........##ddhhhhhhhhd#b#......",
    "............##ddhhhhhhd#b###....",
    "..............##ddhhhhd#b#####..",
    "................##ddhhd#b######.",
    "..................##dddeb#####..",
    "....................##d#b###....",
    "......................####......"};


static const char * file_icon[] = {
"32 32 20 1",
" 	c None",
".	c #FFFFFF",
"+	c #525254",
"@	c #000000",
"#	c #FFFFFF",
"$	c #DCDCDC",
"%	c #FFDCA8",
"&	c #C3C3C3",
"*	c #585858",
"=	c #303030",
"-	c #A0A0A0",
";	c #000000",
">	c #808080",
",	c #FFC0C0",
"'	c #404000",
")	c #C0C000",
"!	c #FFFFC0",
"~	c #FFA858",
"{	c #C0C0FF",
"]	c #400000",
"        **************=;        ",
"        *&&&&&&&&&&&---';       ",
"        *&###########$&*>;      ",
"        *&############$*&>;     ",
"        *&#############*#&>;    ",
"        *&#############*##$>;   ",
"        *&#############*$##&>;  ",
"        *&#############*&$##$>; ",
"        *&#############>******=;",
"        *&##############$$&&->*;",
"        *&###############$$&&->;",
"        *&################$$&&>;",
"        *&#################$$&-;",
"        *&############!####!$$-;",
"        *&#############!###%$$&;",
"        *&###############!##%#-;",
"        *&###########%#!#%#%$%&;",
"        *&########!####!##%!%#-;",
"        *&#########!#%#%#%#%$%&;",
"        *&###########!##%#%#%$-;",
"        *&#######%#%#%#%$%$%$%-;",
"        *&####!####!##%!%#%#%$-;",
"        *&#####!#%#%#%#%$%$%$%-;",
"        *&#######!##%#%#%$%&%%-;",
"        *&###%#%#%#%$%$%$%$%$%-=",
"        *&#####!##%!%#%#%$%%%&-=",
"        *&###!#%#%#%$%$%$%$%$%-=",
"        *&###!##%#%#%$%&%%%&%&-=",
"        *&#!#%#%$%$%$%$%$%$%&%-=",
"        *&#!%#%!%#%#%$%%%&%&%&-=",
"        *&&&&&-&-&-------------=",
"        ;====================]=;"};

static const char * link_icon[]={
    "32 32 12 1",
    "# c #000000",
    "h c #a0a0a4",
    "b c #c00000",
    "d c #585858",
    "i c #400000",
    "c c #ffffff",
    "e c #000000",
    "g c #c0c0c0",
    "a c #ff0000",
    "f c #303030",
    "n c white",
    ". c None",
    "...###..........................",
    "...#aa##........................",
    ".###baaa##......................",
    ".#cde#baaa##....................",
    ".#cccdeebaaa##..##f.............",
    ".#cccccdeebaaa##aaa##...........",
    ".#cccccccdeebaaaaaaaa##.........",
    ".#cccccccccdeebababaaa#.........",
    ".#cccccgcgghhebbbbbbbaa#........",
    ".#ccccccgcgggdebbbbbbba#........",
    ".#cccgcgcgcgghdeebiebbba#.......",
    ".#ccccgcggggggghdeddeeba#.......",
    ".#cgcgcgcggggggggghghdebb#......",
    ".#ccgcggggggggghghghghd#b#......",
    ".#cgcgcggggggggghghghhd#b#......",
    ".#gcggggggggghghghhhhhd#b#......",
    ".#cgcggggggggghghghhhhd#b#......",
    ".#ggggggggghghghhhhhhhdib#......",
    ".#gggggggggghghghhhhhhd#b#......",
    ".#hhggggghghghhhhhhhhhd#b#......",
    ".#ddhhgggghghghhhhhhhhd#b#......",
    "..##ddhhghghhhhhhhhhhhdeb#......",
    "############hhhhhhhhhhd#b#......",
    "#nnnnnnnnnn#hhhhhhhhhhd#b#......",
    "#nnnnnnnnnn#hhhhhhhhhhd#b#......",
    "#nn#nn#nnnn#ddhhhhhhhhd#b#......",
    "#nn##n##nnn###ddhhhhhhd#b###....",
    "#nnn#####nn#..##ddhhhhd#b#####..",
    "#nnnnn##nnn#....##ddhhd#b######.",
    "#nnnnn#nnnn#......##dddeb#####..",
    "#nnnnnnnnnn#........##d#b###....",
    "############..........####......"};

static const char * folder_locked_icon[]={
    "32 32 12 1",
    "# c #000000",
    "g c #808080",
    "h c #c0c0c0",
    "f c #c05800",
    "c c #ffffff",
    "d c #585858",
    "b c #ffa858",
    "a c #ffdca8",
    "e c #000000",
    "i c #a0a0a4",
    "j c #c0c0c0",
    ". c None",
    "...###..........................",
    "...#aa##........................",
    ".###baaa##......................",
    ".#cde#baaa##....................",
    ".#cccdeeba#######...............",
    ".#cccccde##fffff##..............",
    ".#cccccc##fffgggg#..............",
    ".#ccccccc#ffg####a##............",
    ".#ccccchc#ffg#eebbaa##..........",
    ".#ccccccc#ffg#ddeebbba##........",
    ".#ccchccc#ffg#ihddeebbba##......",
    ".#cccccaa#ffg#ihhhddeeba##......",
    ".#chchhbbaafg#ihhhihidebb#......",
    ".#cchccbbbbaa#ihhihihid#b#......",
    ".#chchhbb#bbbaaiihihiid#b#......",
    ".#hchhcbb#fbbbafhiiiiid#b#......",
    ".#chchhbb#ffgbbfihiiiid#b#......",
    ".#hhhhhbb#ffg#bfiiiiiid#b#......",
    ".#hhhhhbbaffg#bfiiiiiid#b#......",
    ".#iihhhjbbaab#bfiiiiiid#b#......",
    ".#ddiihhh#bbbabfiiiiiid#b#......",
    "..##ddiih#ffbbbfiiiiiid#b#......",
    "....##ddi#ffg#biiiiiiid#b#......",
    "......##d#ffg#iiiiiiiid#b#......",
    "........##ffg#iiiiiiiid#b#......",
    ".........#ffg#iiiiiiiid#b#......",
    ".........#ffg#ddiiiiiid#b###....",
    ".........##fg###ddiiiid#b#####..",
    "...........####.##ddiid#b######.",
    "..................##dddeb#####..",
    "....................##d#b###....",
    "......................####......"};

static QPixmap *iconFolderLockedLarge = 0;
static QPixmap *iconFolderLarge = 0;
static QPixmap *iconFileLarge = 0;
static QPixmap *iconLinkLarge = 0;
static QPixmap *iconFolderLockedSmall = 0;
static QPixmap *iconFolderSmall = 0;
static QPixmap *iconFileSmall = 0;
static QPixmap *iconLinkSmall = 0;

static void cleanup()
{
    DELETE( iconFolderLockedLarge );
    DELETE( iconFolderLarge );
    DELETE( iconFileLarge );
    DELETE( iconLinkLarge );
    DELETE( iconFolderLockedSmall );
    DELETE( iconFolderSmall );
    DELETE( iconFileSmall );
    DELETE( iconLinkSmall );
}

/*****************************************************************************
 *
 * Class IconSelectorDrag
 *
 *****************************************************************************/

IconSelectorDrag::IconSelectorDrag( QWidget * dragSource, const char* name )
    : Q3IconDrag( dragSource, name )
{
}

const char* IconSelectorDrag::format( int i ) const
{
    if ( i == 0 )
	return "application/x-qiconlist";
    else if ( i == 1 )
	return "text/uri-list";
    else
	return 0;
}

QByteArray IconSelectorDrag::encodedData( const char* mime ) const
{
    QByteArray a;
    if ( QString( mime ) == "application/x-qiconlist" ) {
	a = Q3IconDrag::encodedData( mime );
    } else if ( QString( mime ) == "text/uri-list" ) {
	QString s = urls.join( "\r\n" );
	a.resize( s.length() );
	memcpy( a.data(), s.latin1(), s.length() );
    }
    return a;
}

bool IconSelectorDrag::canDecode( QMimeSource* e )
{
    return e->provides( "application/x-qiconlist" ) ||
	e->provides( "text/uri-list" );
}

void IconSelectorDrag::append( const Q3IconDragItem &item, const QRect &pr,
			     const QRect &tr, const QString &url )
{
    Q3IconDrag::append( item, pr, tr );
    urls << url;
}

/*****************************************************************************
 *
 * Class IconSelectorItem
 *
 *****************************************************************************/

IconSelectorItem::IconSelectorItem( IconSelector *parent, QFileInfo *fi )
    : Q3IconViewItem( parent, fi->fileName() ), itemFileName( fi->filePath() ),
      itemFileInfo( fi ), checkSetText( FALSE )
{
    vm = IconSelector::Large;

    if ( itemFileInfo->isDir() )
	itemType = Dir;
    else if ( itemFileInfo->isFile() )
	itemType = File;
    if ( itemFileInfo->isSymLink() )
	itemType = Link;

    viewModeChanged( ( (IconSelector*)iconView() )->viewMode() );

    if ( itemFileInfo->fileName() == "." ||
	 itemFileInfo->fileName() == ".." )
	setRenameEnabled( FALSE );

    checkSetText = TRUE;

    QObject::connect( &timer, SIGNAL( timeout() ),
		      iconView(), SLOT( openFolder() ) );
}

void IconSelectorItem::paintItem( QPainter *p, const QColorGroup &cg ){
  if ( itemFileInfo->isSymLink() ) {
	  QFont f( p->font() );
	  f.setItalic( TRUE );
	  p->setFont( f );
  }

  Q3IconViewItem::paintItem( p, cg );
}

void IconSelectorItem::viewModeChanged( IconSelector::ViewMode m ){
    vm = m;
    setDropEnabled( itemType == Dir && QDir( itemFileName ).isReadable() );
    calcRect();
}

QPixmap* IconSelectorItem::pixmap() const{
  switch(itemType){
  case Dir:{
    if(!QDir(itemFileName).isReadable()){
	    if( vm == IconSelector::Small ) return iconFolderLockedSmall;
	    else  return iconFolderLockedLarge;
	  }else{
	    if( vm == IconSelector::Small ) return iconFolderSmall;
	    else return iconFolderLarge;
    }
  }break;

  case Link:{
	   if( vm == IconSelector::Small ) return iconLinkSmall;
	   else return iconLinkLarge;
  }break;

  default:{
    QString s=itemFileName.right(4).lower();
    if( (s==".xpm"  || s==".gif" || s==".png" || s==".jpg"
                    || s==".bmp" || s==".xbm" || s==".pnm"
                    || s=="jpeg" || s==".mng" )
                    && QFile(itemFileName).size()<10000){
      QPixmap* p=new QPixmap(itemFileName);
      return p;
    }else{
      if(vm == IconSelector::Small) return iconFileSmall;
	    else                            return iconFileLarge;
    }
  }break;
  }//switch done.
}

IconSelectorItem::~IconSelectorItem(){
    DELETE( itemFileInfo );
}

void IconSelectorItem::setText( const QString &text ){
    if ( checkSetText ) {
	if ( text == "." || text == "." || text.isEmpty() )
	    return;
	QDir dir( itemFileInfo->dir() );
	if ( dir.rename( itemFileInfo->fileName(), text ) ) {
	    itemFileName = itemFileInfo->dirPath( TRUE ) + "/" + text;
	    DELETE( itemFileInfo );
	    itemFileInfo = new QFileInfo( itemFileName );
	    Q3IconViewItem::setText( text );
	}
    } else {
	Q3IconViewItem::setText( text );
    }
}

bool IconSelectorItem::acceptDrop( const QMimeSource *e ) const{
    if ( type() == Dir && e->provides( "text/uri-list" ) &&
	 dropEnabled() )
	return TRUE;

    return FALSE;
}

void IconSelectorItem::dropped( QDropEvent *e, const Q3ValueList<Q3IconDragItem> & ){
    timer.stop();

    if ( !Q3UriDrag::canDecode( e ) ) {
	e->ignore();
	return;
    }

    Q3StrList lst;
    Q3UriDrag::decode( e, lst );

    QString str;
    if ( e->action() == QDropEvent::Copy )
	str = "Copy\n\n";
    else
	str = "Move\n\n";
    for ( uint i = 0; i < lst.count(); ++i )
	str += QString( "   %1\n" ).arg( lst.at( i ) );
    str += QString( "\n"
		    "To\n\n"
		    "	%1" ).arg( filename() );

    QMessageBox::information( iconView(), e->action() == QDropEvent::Copy ? "Copy" : "Move" , str, "Not Implemented" );
    if ( e->action() == QDropEvent::Move )
	QMessageBox::information( iconView(), "Remove" , str, "Not Implemented" );
    e->acceptAction();
}

void IconSelectorItem::dragEntered(){
    if ( type() != Dir ||
	 type() == Dir && !QDir( itemFileName ).isReadable() )
	return;

    ( (IconSelector*)iconView() )->setOpenItem( this );
    timer.start( 1500 );
}

void IconSelectorItem::dragLeft(){
    if ( type() != Dir ||
	 type() == Dir && !QDir( itemFileName ).isReadable() )
	return;

    timer.stop();
}

/*****************************************************************************
 *
 * Class IconSelector
 *
 *****************************************************************************/

IconSelector::IconSelector( const QString &dir, QWidget *parent, const char *name )
    : Q3IconView( parent, name ), viewDir( dir ), newFolderNum( 0 )
    , openItem( NULLPTR )
{
  if ( !iconFolderLockedLarge ) {
    qAddPostRoutine( cleanup );
    QMatrix m;
    m.scale( 0.6, 0.6 );
    QPixmap iconpix( folder_locked_icon );
    iconFolderLockedLarge = new QPixmap( folder_locked_icon );
    iconpix = iconpix.xForm( m );
    iconFolderLockedSmall = new QPixmap( iconpix );
    iconpix = QPixmap( folder_icon );
    iconFolderLarge = new QPixmap( folder_icon );
    iconpix = iconpix.xForm( m );
    iconFolderSmall = new QPixmap( iconpix );
    iconpix = QPixmap( file_icon );
    iconFileLarge = new QPixmap( file_icon );
    iconpix = iconpix.xForm( m );
    iconFileSmall = new QPixmap( iconpix );
    iconpix = QPixmap( link_icon );
    iconLinkLarge = new QPixmap( link_icon );
    iconpix = iconpix.xForm( m );
    iconLinkSmall = new QPixmap( iconpix );
  }

  vm = Large;

  setGridX( 75 );
  setResizeMode( Adjust );
  setWordWrapIconText( FALSE );

  connect( this, SIGNAL( doubleClicked( Q3IconViewItem * ) ),
    this, SLOT( itemDoubleClicked( Q3IconViewItem * ) ) );
  connect( this, SIGNAL( returnPressed( Q3IconViewItem * ) ),
    this, SLOT( itemDoubleClicked( Q3IconViewItem * ) ) );
  connect( this, SIGNAL( dropped( QDropEvent *, const Q3ValueList<Q3IconDragItem> & ) ),
    this, SLOT( slotDropped( QDropEvent *, const Q3ValueList<Q3IconDragItem> & ) ) );
  connect( this, SIGNAL( rightButtonPressed( Q3IconViewItem *, const QPoint & ) ),
    this, SLOT( slotRightPressed( Q3IconViewItem * ) ) );

  setHScrollBarMode( AlwaysOff );
  setVScrollBarMode( Auto );

  setAutoArrange( TRUE );
  setSorting( TRUE );
}

void IconSelector::openFolder(){
	if( !openItem ) return;
	if( openItem->type() != IconSelectorItem::Dir ||
	    openItem->type() == IconSelectorItem::Dir &&
	    !QDir( openItem->itemFileName ).isReadable() )
		return;

	openItem->timer.stop();
	setDirectory( openItem->itemFileName );
}

void IconSelector::setDirectory(const QString &dir){
  viewDir=QDir(dir);
  readDir(viewDir);
}

void IconSelector::setDirectory(const QDir &dir){
  viewDir=dir;
  readDir(viewDir);
}

void IconSelector::newDirectory()
{
    setAutoArrange( FALSE );
    selectAll( FALSE );
    if ( viewDir.mkdir( QString( "New Folder %1" ).arg( ++newFolderNum ) ) ) {
	QFileInfo *fi = new QFileInfo( viewDir, QString( "New Folder %1" ).arg( newFolderNum ) );
	IconSelectorItem *item = new IconSelectorItem( this, new QFileInfo( *fi ) );
	item->setKey( QString( "000000%1" ).arg( fi->fileName() ) );
	DELETE( fi );
	repaintContents( contentsX(), contentsY(), contentsWidth(), contentsHeight(), FALSE );
	ensureItemVisible( item );
	item->setSelected( TRUE, TRUE );
	setCurrentItem( item );
	repaintItem( item );
	qApp->processEvents();
	item->rename();
    }
    setAutoArrange( TRUE );
}

QDir IconSelector::currentDir(){
	return viewDir;
}

static bool isRoot( const QString& /*s*/ )
{
#if defined(_OS_UNIX_)
    if ( s == "/" )
	return TRUE;
#elif defined(_OS_WIN32_)
    QString p = s;
    if ( p.length() == 3 &&
	 p.right( 2 ) == ":/" )
	return TRUE;
    if ( p[ 0 ] == '/' && p[ 1 ] == '/' ) {
	int slashes = p.contains( '/' );
	if ( slashes <= 3 )
	    return TRUE;
	if ( slashes == 4 && p[ (int)p.length() - 1 ] == '/' )
	    return TRUE;
    }
#endif

    return FALSE;
}

void IconSelector::readDir( const QDir &dir ){
	if( !dir.isReadable() ) return;

  if( isRoot( dir.absPath() ) ) emit disableUp();
  else                          emit enableUp();

  clear();

  emit directoryChanged( dir.absPath() );

  QFileInfoList files = dir.entryInfoList( QDir::DefaultFilter, QDir::DirsFirst | QDir::Name );

  emit startReadDir( files.count() );

  QFileInfo fi;
  bool allowRename = FALSE, allowRenameSet = FALSE;
  for (QList<QFileInfo>::iterator it = files.begin(); it != files.end(); it++) {
		fi = *it;
		if( fi.fileName() == ".." && ( fi.dirPath() == "/"
		                                 || fi.dirPath().isEmpty() ) )
	    continue;

		emit readNextDir();
		IconSelectorItem *item = new IconSelectorItem( this, new QFileInfo( fi ) );
		if( fi.isDir() )
			item->setKey( QString( "000000%1" ).arg( fi.fileName() ) );
		else
			item->setKey( fi.fileName() );
		if( !allowRenameSet ){
	    if( !QFileInfo( fi.absFilePath() ).isWritable()
	         || item->text() == "." || item->text() == ".." )
				allowRename = FALSE;
	    else
				allowRename = TRUE;
	    if( item->text() == "." || item->text() == ".." )
				allowRenameSet = FALSE;
	    else
				allowRenameSet = TRUE;
		}
		item->setRenameEnabled( allowRename );
	}//for

//    if ( !QFileInfo( dir.absPath() ).isWritable() )
//	emit disableMkdir();
//    else
//	emit enableMkdir();

	emit readDirDone();
}

void IconSelector::itemDoubleClicked( Q3IconViewItem *i )
{
    IconSelectorItem *item = ( IconSelectorItem* )i;

    if ( item->type() == IconSelectorItem::Dir ) {
	viewDir = QDir( item->filename() );
	readDir( viewDir );
    } else if ( item->type() == IconSelectorItem::Link &&
		QFileInfo( QFileInfo( item->filename() ).readLink() ).isDir() ) {
	viewDir = QDir( QFileInfo( item->filename() ).readLink() );
	readDir( viewDir );
    }
}

Q3DragObject *IconSelector::dragObject()
{
    if ( !currentItem() )
	return 0;

    QPoint orig = viewportToContents( viewport()->mapFromGlobal( QCursor::pos() ) );
    IconSelectorDrag *drag = new IconSelectorDrag( viewport() );
    drag->setPixmap( *currentItem()->pixmap(),
 		     QPoint( currentItem()->pixmapRect().width() / 2, currentItem()->pixmapRect().height() / 2 ) );
    for ( IconSelectorItem *item = (IconSelectorItem*)firstItem(); item;
	  item = (IconSelectorItem*)item->nextItem() ) {
	if ( item->isSelected() ) {
	    Q3IconDragItem id;
	    id.setData( Q3CString( item->filename().toUtf8() ) );
	    drag->append( id,
			  QRect( item->pixmapRect( FALSE ).x() - orig.x(),
				 item->pixmapRect( FALSE ).y() - orig.y(),
				 item->pixmapRect().width(), item->pixmapRect().height() ),
			  QRect( item->textRect( FALSE ).x() - orig.x(),
				 item->textRect( FALSE ).y() - orig.y(),
				 item->textRect().width(), item->textRect().height() ),
			  QString( item->filename() ) );
	}
    }

    return drag;
}

void IconSelector::keyPressEvent( QKeyEvent *e ){
	if(e->key() == Qt::Key_N && ( e->state() & Qt::ControlButton ))
		newDirectory();
  else
		Q3IconView::keyPressEvent(e);
}

void IconSelector::slotDropped( QDropEvent *e, const Q3ValueList<Q3IconDragItem> & )
{
    if ( openItem )
	openItem->timer.stop();
    if ( !Q3UriDrag::canDecode( e ) ) {
	e->ignore();
	return;
    }

    Q3StrList lst;
    Q3UriDrag::decode( e, lst );

    QString str;
    if ( e->action() == QDropEvent::Copy )
	str = "Copy\n\n";
    else
	str = "Move\n\n";
    for ( uint i = 0; i < lst.count(); ++i )
	str += QString( "   %1\n" ).arg( lst.at( i ) );
    str += QString( "\n"
		    "To\n\n"
		    "	%1" ).arg( viewDir.absPath() );

    QMessageBox::information( this, e->action() == QDropEvent::Copy ? "Copy" : "Move" , str, "Not Implemented" );
    if ( e->action() == QDropEvent::Move )
	QMessageBox::information( this, "Remove" , str, "Not Implemented" );
    e->acceptAction();
    openItem = 0;
}

void IconSelector::viewLarge()
{
    setViewMode( Large );
}

void IconSelector::viewSmall()
{
    setViewMode( Small );
}

void IconSelector::viewBottom()
{
    setItemTextPos( Bottom );
}

void IconSelector::viewRight()
{
    setItemTextPos( Right );
}

void IconSelector::flowEast()
{
    setHScrollBarMode( AlwaysOff );
    setVScrollBarMode( Auto );
    setArrangement( LeftToRight );
}

void IconSelector::flowSouth()
{
    setVScrollBarMode( AlwaysOff );
    setHScrollBarMode( Auto );
    setArrangement( TopToBottom );
}

void IconSelector::sortAscending()
{
    sort( TRUE );
}

void IconSelector::sortDescending()
{
    sort( FALSE );
}

void IconSelector::itemTextTruncate()
{
    setWordWrapIconText( FALSE );
}

void IconSelector::itemTextWordWrap()
{
    setWordWrapIconText( TRUE );
}

void IconSelector::slotRightPressed( Q3IconViewItem *item ){
  if( !item ){ // right pressed on viewport
  	Q3PopupMenu menu( this );

  	menu.insertItem( "&Large view", this, SLOT( viewLarge() ) );
  	menu.insertItem( "&Small view", this, SLOT( viewSmall() ) );
  	menu.insertSeparator();
  	menu.insertItem( "Text at the &bottom", this, SLOT( viewBottom() ) );
  	menu.insertItem( "Text at the &right", this, SLOT( viewRight() ) );
  	menu.insertSeparator();
  	menu.insertItem( "Arrange l&eft to right", this, SLOT( flowEast() ) );
  	menu.insertItem( "Arrange t&op to bottom", this, SLOT( flowSouth() ) );
  	menu.insertSeparator();
  	menu.insertItem( "&Truncate item text", this, SLOT( itemTextTruncate() ) );
  	menu.insertItem( "&Wordwrap item text", this, SLOT( itemTextWordWrap() ) );
  	menu.insertSeparator();
  	menu.insertItem( "Arrange items in &grid", this, SLOT( arrangeItemsInGrid() ) );
  	menu.insertSeparator();
  	menu.insertItem( "Sort &ascending", this, SLOT( sortAscending() ) );
  	menu.insertItem( "Sort &descending", this, SLOT( sortDescending() ) );

  	menu.setMouseTracking( TRUE );
  	menu.exec( QCursor::pos() );
  }else{ // on item
  	Q3PopupMenu menu( this );

  	int RENAME_ITEM = menu.insertItem( "Rename Item" );
  	int REMOVE_ITEM = menu.insertItem( "Remove Item" );

  	menu.setMouseTracking( TRUE );
  	int id = menu.exec( QCursor::pos() );

  	if ( id == -1 )
  	    return;

  	if ( id == RENAME_ITEM && item->renameEnabled() ) {
  	    item->rename();
  	} else if ( id == REMOVE_ITEM ) {
  	    DELETE( item );
  	    QMessageBox::information( this, "Not implemented!", "Deleting files not implemented yet,\n"
  				      "The item has only been removed from the view! " );
  	}
	}// on item
}

void IconSelector::setViewMode( ViewMode m )
{
    if ( m == vm )
	return;

    vm = m;
    IconSelectorItem *item = (IconSelectorItem*)firstItem();
    for ( ; item; item = (IconSelectorItem*)item->nextItem() )
	item->viewModeChanged( vm );

    arrangeItemsInGrid();
}
