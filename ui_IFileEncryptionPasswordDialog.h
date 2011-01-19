/********************************************************************************
** Form generated from reading ui file 'IFileEncryptionPasswordDialog.ui'
**
** Created: Tue Jan 18 13:49:05 2011
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef IFILEENCRYPTIONPASSWORDDIALOG_H
#define IFILEENCRYPTIONPASSWORDDIALOG_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IFileEncryptionPasswordDialog
{
public:
    QLabel *textLabel1;
    QLineEdit *leFilePassword;
    QWidget *Layout1;
    QHBoxLayout *hboxLayout;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    QLabel *tlFileName;

    void setupUi(QDialog *IFileEncryptionPasswordDialog)
    {
        if (IFileEncryptionPasswordDialog->objectName().isEmpty())
            IFileEncryptionPasswordDialog->setObjectName(QString::fromUtf8("IFileEncryptionPasswordDialog"));
        IFileEncryptionPasswordDialog->resize(419, 193);
        IFileEncryptionPasswordDialog->setSizeGripEnabled(true);
        IFileEncryptionPasswordDialog->setModal(true);
        textLabel1 = new QLabel(IFileEncryptionPasswordDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(30, 20, 360, 20));
        textLabel1->setWordWrap(false);
        leFilePassword = new QLineEdit(IFileEncryptionPasswordDialog);
        leFilePassword->setObjectName(QString::fromUtf8("leFilePassword"));
        leFilePassword->setGeometry(QRect(30, 90, 350, 31));
        leFilePassword->setEchoMode(QLineEdit::Password);
        Layout1 = new QWidget(IFileEncryptionPasswordDialog);
        Layout1->setObjectName(QString::fromUtf8("Layout1"));
        Layout1->setGeometry(QRect(80, 140, 300, 32));
        hboxLayout = new QHBoxLayout(Layout1);
        hboxLayout->setSpacing(6);
        hboxLayout->setMargin(0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        Horizontal_Spacing2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(Layout1);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout->addWidget(buttonOk);

        buttonCancel = new QPushButton(Layout1);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        hboxLayout->addWidget(buttonCancel);

        tlFileName = new QLabel(IFileEncryptionPasswordDialog);
        tlFileName->setObjectName(QString::fromUtf8("tlFileName"));
        tlFileName->setGeometry(QRect(30, 50, 360, 20));
        tlFileName->setWordWrap(false);

        retranslateUi(IFileEncryptionPasswordDialog);
        QObject::connect(buttonOk, SIGNAL(clicked()), IFileEncryptionPasswordDialog, SLOT(accept()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), IFileEncryptionPasswordDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(IFileEncryptionPasswordDialog);
    } // setupUi

    void retranslateUi(QDialog *IFileEncryptionPasswordDialog)
    {
        IFileEncryptionPasswordDialog->setWindowTitle(QApplication::translate("IFileEncryptionPasswordDialog", "File Encryption Password", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("IFileEncryptionPasswordDialog", "Please enter password for:", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("IFileEncryptionPasswordDialog", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("IFileEncryptionPasswordDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
        tlFileName->setText(QApplication::translate("IFileEncryptionPasswordDialog", "filepath", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(IFileEncryptionPasswordDialog);
    } // retranslateUi

};

namespace Ui {
    class IFileEncryptionPasswordDialog: public Ui_IFileEncryptionPasswordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // IFILEENCRYPTIONPASSWORDDIALOG_H
