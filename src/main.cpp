/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Son Mär 26 23:04:15 CEST 2000
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

#include <QApplication>
#include "./gui/mainwindow.h"

#include "commandlineoptions.h"
#include <qstylefactory.h>

int main(int argc, char* argv[]){

  if (argc > 1 ){
    CommandLineOptions(argc, argv);
  }

  QApplication app(argc, argv);

  MainWindow tux(argc>1 ? argv[1] : "");
  app.setMainWidget( &tux );
  return app.exec();

}
