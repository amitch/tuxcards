/********************************************************************************
** Form generated from reading ui file 'IPasswdDialog.ui'
**
** Created: Tue Jan 18 13:49:05 2011
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef IPASSWDDIALOG_H
#define IPASSWDDIALOG_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_IPasswdDialog
{
public:
    QVBoxLayout *vboxLayout;
    QLabel *textLabel3;
    QLabel *mpIEDescription;
    QGridLayout *gridLayout;
    QLineEdit *mpPasswdLineTwo;
    QLabel *textLabel2;
    QLineEdit *mpPasswdLineOne;
    QLabel *textLabel1;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacer1;
    QPushButton *mpOkButton;
    QPushButton *pushButton2;

    void setupUi(QDialog *IPasswdDialog)
    {
        if (IPasswdDialog->objectName().isEmpty())
            IPasswdDialog->setObjectName(QString::fromUtf8("IPasswdDialog"));
        IPasswdDialog->resize(240, 154);
        vboxLayout = new QVBoxLayout(IPasswdDialog);
        vboxLayout->setSpacing(6);
        vboxLayout->setMargin(11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        textLabel3 = new QLabel(IPasswdDialog);
        textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
        QFont font;
        font.setItalic(true);
        textLabel3->setFont(font);
        textLabel3->setWordWrap(false);

        vboxLayout->addWidget(textLabel3);

        mpIEDescription = new QLabel(IPasswdDialog);
        mpIEDescription->setObjectName(QString::fromUtf8("mpIEDescription"));
        mpIEDescription->setAlignment(Qt::AlignCenter);
        mpIEDescription->setWordWrap(false);

        vboxLayout->addWidget(mpIEDescription);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mpPasswdLineTwo = new QLineEdit(IPasswdDialog);
        mpPasswdLineTwo->setObjectName(QString::fromUtf8("mpPasswdLineTwo"));
        mpPasswdLineTwo->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(mpPasswdLineTwo, 1, 1, 1, 1);

        textLabel2 = new QLabel(IPasswdDialog);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setWordWrap(false);

        gridLayout->addWidget(textLabel2, 1, 0, 1, 1);

        mpPasswdLineOne = new QLineEdit(IPasswdDialog);
        mpPasswdLineOne->setObjectName(QString::fromUtf8("mpPasswdLineOne"));
        mpPasswdLineOne->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(mpPasswdLineOne, 0, 1, 1, 1);

        textLabel1 = new QLabel(IPasswdDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        gridLayout->addWidget(textLabel1, 0, 0, 1, 1);


        vboxLayout->addLayout(gridLayout);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacer1);

        mpOkButton = new QPushButton(IPasswdDialog);
        mpOkButton->setObjectName(QString::fromUtf8("mpOkButton"));

        hboxLayout->addWidget(mpOkButton);

        pushButton2 = new QPushButton(IPasswdDialog);
        pushButton2->setObjectName(QString::fromUtf8("pushButton2"));

        hboxLayout->addWidget(pushButton2);


        vboxLayout->addLayout(hboxLayout);

        QWidget::setTabOrder(mpPasswdLineOne, mpPasswdLineTwo);
        QWidget::setTabOrder(mpPasswdLineTwo, mpOkButton);
        QWidget::setTabOrder(mpOkButton, pushButton2);

        retranslateUi(IPasswdDialog);
        QObject::connect(pushButton2, SIGNAL(released()), IPasswdDialog, SLOT(reject()));
        QObject::connect(mpOkButton, SIGNAL(clicked()), IPasswdDialog, SLOT(done()));

        QMetaObject::connectSlotsByName(IPasswdDialog);
    } // setupUi

    void retranslateUi(QDialog *IPasswdDialog)
    {
        IPasswdDialog->setWindowTitle(QApplication::translate("IPasswdDialog", "TuxCards Encryption", 0, QApplication::UnicodeUTF8));
        textLabel3->setText(QApplication::translate("IPasswdDialog", "Please enter a password to encrypt", 0, QApplication::UnicodeUTF8));
        mpIEDescription->setText(QApplication::translate("IPasswdDialog", "'entry name'", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("IPasswdDialog", "Retype", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("IPasswdDialog", "Password", 0, QApplication::UnicodeUTF8));
        mpOkButton->setText(QApplication::translate("IPasswdDialog", "&Ok", 0, QApplication::UnicodeUTF8));
        mpOkButton->setShortcut(QApplication::translate("IPasswdDialog", "Alt+O", 0, QApplication::UnicodeUTF8));
        pushButton2->setText(QApplication::translate("IPasswdDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        pushButton2->setShortcut(QApplication::translate("IPasswdDialog", "Alt+C", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(IPasswdDialog);
    } // retranslateUi

};

namespace Ui {
    class IPasswdDialog: public Ui_IPasswdDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // IPASSWDDIALOG_H
