# -------------------------------------------------
# Project created by QtCreator 2009-05-08T16:30:18
# -------------------------------------------------
QT += qt3support \
    testlib
QT -= gui
TARGET = tests
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    ../src/utilities/crypt/BlowFish.cpp \
    ../src/utilities/crypt/StringCrypter.cpp \
    ../src/utilities/crypt/MD5.cpp
