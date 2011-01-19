# -------------------------------------------------
# Project created by QtCreator 2009-06-29T17:12:16
# -------------------------------------------------
#Added by amitc, temporary to build release on linux
CONFIG=qt threads release

QT += qt3support
QT += xml
TARGET = tuxcards
TEMPLATE = app
SOURCES += src/persister.cpp \
    src/fontsettings.cpp \
    src/CTuxCardsConfiguration.cpp \
    src/commandlineoptions.cpp \
    src/gui/dialogs/CFileEncryptionPasswordDialog.cpp \
    src/main.cpp \
    src/gui/CTreeElement.cpp \
    src/gui/CTree.cpp \
    src/gui/mainwindow.cpp \
    src/gui/editor.cpp \
    src/gui/CSingleEntryView.cpp \
    src/gui/BookmarkButton.cpp \
    src/gui/RecentFileList.cpp \
    src/gui/dialogs/searchposition.cpp \
    src/gui/dialogs/searchlistitem.cpp \
    src/gui/dialogs/searchdialog.cpp \
    src/gui/dialogs/optionsdialog.cpp \
    src/gui/dialogs/iconselectordialog.cpp \
    src/gui/dialogs/iconselector.cpp \
    src/gui/dialogs/CPropertyDialog.cpp \
    src/gui/dialogs/CPasswdDialog.cpp \
    src/information/xmlpersister.cpp \
    src/information/Path.cpp \
    src/information/informationformat.cpp \
    src/information/htmlwriter.cpp \
    src/information/CTreeInformationElement.cpp \
    src/information/converter.cpp \
    src/information/CInformationElementHistory.cpp \
    src/information/CInformationElement.cpp \
    src/information/CInformationCollection.cpp \
    src/utilities/strings.cpp \
    src/utilities/integers.cpp \
    src/utilities/CIconManager.cpp \
    src/utilities/crypt/StringCrypter.cpp \
    src/utilities/crypt/MD5.cpp \
    src/utilities/crypt/BlowFish.cpp \
    src/utilities/iniparser/configparser.cpp \
    src/utilities/iniparser/configgroup.cpp
HEADERS += src/gui/dialogs/searchlistitem.h \
    src/gui/dialogs/searchdialog.h \
    src/gui/dialogs/optionsdialog.h \
    src/gui/dialogs/iconselectordialog.h \
    src/gui/dialogs/iconselector.h \
    src/gui/dialogs/CPropertyDialog.h \
    src/gui/dialogs/CPasswdDialog.h \
    src/gui/dialogs/CFileEncryptionPasswordDialog.h \
    src/gui/dialogs/searchposition.h \
    src/information/Path.h \
    src/information/IView.h \
    src/information/IRemoveElementListener.h \
    src/information/IParent.h \
    src/information/informationformat.h \
    src/information/IHistoryListener.h \
    src/information/htmlwriter.h \
    src/information/CTreeInformationElement.h \
    src/information/converter.h \
    src/information/CInformationElementHistory.h \
    src/information/CInformationElement.h \
    src/information/CInformationCollection.h \
    src/information/xmlpersister.h \
    src/utilities/integers.h \
    src/utilities/CIconManager.h \
    src/utilities/strings.h \
    src/utilities/crypt/MD5.h \
    src/utilities/crypt/BlowFish.h \
    src/utilities/crypt/BlowFish2.h \
    src/utilities/crypt/StringCrypter.h \
    src/utilities/iniparser/configgroup.h \
    src/utilities/iniparser/configparser.h \
    src/version.h \
    src/gui/mainwindow.h \
    src/gui/editor.h \
    src/gui/CTree.h \
    src/gui/CSingleEntryView.h \
    src/gui/BookmarkButton.h \
    src/gui/RecentFileList.h \
    src/gui/CTreeElement.h
FORMS += src/gui/dialogs/IFileEncryptionPasswordDialog.ui \
    src/gui/dialogs/IPropertyDialog.ui \
    src/gui/dialogs/IPasswdDialog.ui \
    src/gui/dialogs/IOptionsDialog.ui
OTHER_FILES += src/information/space15.xpm \
    src/information/format_rtf.xpm \
    src/information/format_rtf.png \
    src/information/format_none.xpm \
    src/information/format_ascii.xpm \
    src/information/format_ascii.png \
    src/information/dot.xpm \
    INSTALL \
    README
