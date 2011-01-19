#!/bin/bash
#QTDIR=/usr/lib/qt3
QTDIR=/usr/lib/qt3/
QT_LIBRARY_PATH=/usr/lib/
QMAKESPEC=cygwin-g++

export QTDIR QT_LIBRARY_PATH QMAKESPEC
umask 0002
