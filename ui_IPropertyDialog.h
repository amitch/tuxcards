/********************************************************************************
** Form generated from reading ui file 'IPropertyDialog.ui'
**
** Created: Tue Jan 18 13:49:05 2011
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef IPROPERTYDIALOG_H
#define IPROPERTYDIALOG_H

#include <Qt3Support/Q3ButtonGroup>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IPropertyDialog
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *tabWidget;
    QWidget *Widget8;
    QVBoxLayout *vboxLayout1;
    QLabel *textLabel1;
    QHBoxLayout *hboxLayout;
    QLineEdit *mpNameLine;
    QComboBox *mpTextFormatChoser;
    Q3ButtonGroup *buttonGroup1;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout1;
    QRadioButton *mpNoIconRB;
    QSpacerItem *spacer2;
    QRadioButton *mpUseIconRB;
    QPushButton *mpIconButton;
    QLabel *mpIconLocLabel;
    QLabel *mpLocationLabel;
    Q3ButtonGroup *mpEncryptionPanel;
    QHBoxLayout *hboxLayout2;
    QVBoxLayout *vboxLayout3;
    QCheckBox *mpEncryptCheckBox;
    QSpacerItem *spacer4;
    QGridLayout *gridLayout;
    QLabel *textLabel1_2;
    QLineEdit *mpPasswdLineTwo;
    QLabel *textLabel1_3;
    QLineEdit *mpPasswdLineOne;
    QHBoxLayout *hboxLayout3;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *mpButtonApply;
    QPushButton *pButtonCancel;

    void setupUi(QDialog *IPropertyDialog)
    {
        if (IPropertyDialog->objectName().isEmpty())
            IPropertyDialog->setObjectName(QString::fromUtf8("IPropertyDialog"));
        IPropertyDialog->resize(417, 294);
        IPropertyDialog->setMaximumSize(QSize(600, 32767));
        IPropertyDialog->setSizeGripEnabled(true);
        vboxLayout = new QVBoxLayout(IPropertyDialog);
        vboxLayout->setSpacing(6);
        vboxLayout->setMargin(11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        tabWidget = new QTabWidget(IPropertyDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        Widget8 = new QWidget();
        Widget8->setObjectName(QString::fromUtf8("Widget8"));
        vboxLayout1 = new QVBoxLayout(Widget8);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setMargin(11);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        textLabel1 = new QLabel(Widget8);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        vboxLayout1->addWidget(textLabel1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        mpNameLine = new QLineEdit(Widget8);
        mpNameLine->setObjectName(QString::fromUtf8("mpNameLine"));
        mpNameLine->setFocusPolicy(Qt::StrongFocus);

        hboxLayout->addWidget(mpNameLine);

        mpTextFormatChoser = new QComboBox(Widget8);
        mpTextFormatChoser->setObjectName(QString::fromUtf8("mpTextFormatChoser"));
        mpTextFormatChoser->setMinimumSize(QSize(0, 35));

        hboxLayout->addWidget(mpTextFormatChoser);


        vboxLayout1->addLayout(hboxLayout);

        buttonGroup1 = new Q3ButtonGroup(Widget8);
        buttonGroup1->setObjectName(QString::fromUtf8("buttonGroup1"));
        QFont font;
        font.setBold(true);
        buttonGroup1->setFont(font);
        buttonGroup1->setColumnLayout(0, Qt::Vertical);
        buttonGroup1->layout()->setSpacing(6);
        buttonGroup1->layout()->setMargin(11);
        vboxLayout2 = new QVBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(buttonGroup1->layout());
        if (boxlayout)
            boxlayout->addLayout(vboxLayout2);
        vboxLayout2->setAlignment(Qt::AlignTop);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        mpNoIconRB = new QRadioButton(buttonGroup1);
        mpNoIconRB->setObjectName(QString::fromUtf8("mpNoIconRB"));
        QFont font1;
        font1.setBold(false);
        mpNoIconRB->setFont(font1);
        mpNoIconRB->setChecked(true);

        hboxLayout1->addWidget(mpNoIconRB);

        spacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacer2);

        mpUseIconRB = new QRadioButton(buttonGroup1);
        mpUseIconRB->setObjectName(QString::fromUtf8("mpUseIconRB"));
        mpUseIconRB->setFont(font1);
        mpUseIconRB->setChecked(false);

        hboxLayout1->addWidget(mpUseIconRB);

        mpIconButton = new QPushButton(buttonGroup1);
        mpIconButton->setObjectName(QString::fromUtf8("mpIconButton"));
        mpIconButton->setEnabled(false);
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mpIconButton->sizePolicy().hasHeightForWidth());
        mpIconButton->setSizePolicy(sizePolicy);
        mpIconButton->setMinimumSize(QSize(32, 32));

        hboxLayout1->addWidget(mpIconButton);


        vboxLayout2->addLayout(hboxLayout1);

        mpIconLocLabel = new QLabel(buttonGroup1);
        mpIconLocLabel->setObjectName(QString::fromUtf8("mpIconLocLabel"));
        mpIconLocLabel->setEnabled(false);
        mpIconLocLabel->setFont(font1);
        mpIconLocLabel->setWordWrap(false);

        vboxLayout2->addWidget(mpIconLocLabel);

        mpLocationLabel = new QLabel(buttonGroup1);
        mpLocationLabel->setObjectName(QString::fromUtf8("mpLocationLabel"));
        mpLocationLabel->setEnabled(false);
        mpLocationLabel->setFont(font1);
        mpLocationLabel->setFrameShape(QFrame::Box);
        mpLocationLabel->setFrameShadow(QFrame::Raised);
        mpLocationLabel->setWordWrap(false);

        vboxLayout2->addWidget(mpLocationLabel);


        vboxLayout1->addWidget(buttonGroup1);

        mpEncryptionPanel = new Q3ButtonGroup(Widget8);
        mpEncryptionPanel->setObjectName(QString::fromUtf8("mpEncryptionPanel"));
        mpEncryptionPanel->setMaximumSize(QSize(0, 0));
        mpEncryptionPanel->setFont(font);
        mpEncryptionPanel->setColumnLayout(0, Qt::Vertical);
        mpEncryptionPanel->layout()->setSpacing(6);
        mpEncryptionPanel->layout()->setMargin(11);
        hboxLayout2 = new QHBoxLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(mpEncryptionPanel->layout());
        if (boxlayout1)
            boxlayout1->addLayout(hboxLayout2);
        hboxLayout2->setAlignment(Qt::AlignTop);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setSpacing(6);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        mpEncryptCheckBox = new QCheckBox(mpEncryptionPanel);
        mpEncryptCheckBox->setObjectName(QString::fromUtf8("mpEncryptCheckBox"));
        mpEncryptCheckBox->setFont(font1);

        vboxLayout3->addWidget(mpEncryptCheckBox);

        spacer4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout3->addItem(spacer4);


        hboxLayout2->addLayout(vboxLayout3);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textLabel1_2 = new QLabel(mpEncryptionPanel);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setEnabled(false);
        textLabel1_2->setFont(font1);
        textLabel1_2->setWordWrap(false);

        gridLayout->addWidget(textLabel1_2, 0, 0, 1, 1);

        mpPasswdLineTwo = new QLineEdit(mpEncryptionPanel);
        mpPasswdLineTwo->setObjectName(QString::fromUtf8("mpPasswdLineTwo"));
        mpPasswdLineTwo->setEnabled(false);
        mpPasswdLineTwo->setFont(font1);
        mpPasswdLineTwo->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(mpPasswdLineTwo, 1, 1, 1, 1);

        textLabel1_3 = new QLabel(mpEncryptionPanel);
        textLabel1_3->setObjectName(QString::fromUtf8("textLabel1_3"));
        textLabel1_3->setEnabled(false);
        textLabel1_3->setFont(font1);
        textLabel1_3->setWordWrap(false);

        gridLayout->addWidget(textLabel1_3, 1, 0, 1, 1);

        mpPasswdLineOne = new QLineEdit(mpEncryptionPanel);
        mpPasswdLineOne->setObjectName(QString::fromUtf8("mpPasswdLineOne"));
        mpPasswdLineOne->setEnabled(false);
        mpPasswdLineOne->setFont(font1);
        mpPasswdLineOne->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(mpPasswdLineOne, 0, 1, 1, 1);


        hboxLayout2->addLayout(gridLayout);


        vboxLayout1->addWidget(mpEncryptionPanel);

        tabWidget->addTab(Widget8, QString());

        vboxLayout->addWidget(tabWidget);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setMargin(0);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        Horizontal_Spacing2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(Horizontal_Spacing2);

        mpButtonApply = new QPushButton(IPropertyDialog);
        mpButtonApply->setObjectName(QString::fromUtf8("mpButtonApply"));
        mpButtonApply->setAutoDefault(true);
        mpButtonApply->setDefault(true);

        hboxLayout3->addWidget(mpButtonApply);

        pButtonCancel = new QPushButton(IPropertyDialog);
        pButtonCancel->setObjectName(QString::fromUtf8("pButtonCancel"));
        pButtonCancel->setAutoDefault(true);

        hboxLayout3->addWidget(pButtonCancel);


        vboxLayout->addLayout(hboxLayout3);

        QWidget::setTabOrder(mpNameLine, mpTextFormatChoser);
        QWidget::setTabOrder(mpTextFormatChoser, mpNoIconRB);
        QWidget::setTabOrder(mpNoIconRB, mpIconButton);
        QWidget::setTabOrder(mpIconButton, mpEncryptCheckBox);
        QWidget::setTabOrder(mpEncryptCheckBox, mpPasswdLineOne);
        QWidget::setTabOrder(mpPasswdLineOne, mpButtonApply);
        QWidget::setTabOrder(mpButtonApply, pButtonCancel);
        QWidget::setTabOrder(pButtonCancel, tabWidget);

        retranslateUi(IPropertyDialog);
        QObject::connect(mpNoIconRB, SIGNAL(toggled(bool)), mpLocationLabel, SLOT(setDisabled(bool)));
        QObject::connect(mpNoIconRB, SIGNAL(toggled(bool)), mpIconLocLabel, SLOT(setDisabled(bool)));
        QObject::connect(mpNoIconRB, SIGNAL(toggled(bool)), mpIconButton, SLOT(setDisabled(bool)));
        QObject::connect(pButtonCancel, SIGNAL(clicked()), IPropertyDialog, SLOT(reject()));
        QObject::connect(mpButtonApply, SIGNAL(clicked()), IPropertyDialog, SLOT(accept()));
        QObject::connect(mpEncryptCheckBox, SIGNAL(toggled(bool)), textLabel1_3, SLOT(setEnabled(bool)));
        QObject::connect(mpEncryptCheckBox, SIGNAL(toggled(bool)), mpPasswdLineOne, SLOT(setEnabled(bool)));
        QObject::connect(mpEncryptCheckBox, SIGNAL(toggled(bool)), textLabel1_2, SLOT(setEnabled(bool)));
        QObject::connect(mpEncryptCheckBox, SIGNAL(toggled(bool)), mpPasswdLineTwo, SLOT(setEnabled(bool)));

        mpTextFormatChoser->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(IPropertyDialog);
    } // setupUi

    void retranslateUi(QDialog *IPropertyDialog)
    {
        IPropertyDialog->setWindowTitle(QApplication::translate("IPropertyDialog", "Property Dialog", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("IPropertyDialog", "<b>Entry Name</b>", 0, QApplication::UnicodeUTF8));
        mpTextFormatChoser->clear();
        mpTextFormatChoser->insertItems(0, QStringList()
         << QApplication::translate("IPropertyDialog", "ASCII", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IPropertyDialog", "RTF", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        mpTextFormatChoser->setProperty("toolTip", QVariant(QApplication::translate("IPropertyDialog", "Chose the Text Format", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP
        buttonGroup1->setTitle(QApplication::translate("IPropertyDialog", "Icon", 0, QApplication::UnicodeUTF8));
        mpNoIconRB->setText(QApplication::translate("IPropertyDialog", "No icon", 0, QApplication::UnicodeUTF8));
        mpUseIconRB->setText(QApplication::translate("IPropertyDialog", "Specify an icon", 0, QApplication::UnicodeUTF8));
        mpIconButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        mpIconButton->setProperty("toolTip", QVariant(QApplication::translate("IPropertyDialog", "Choose a file for the icon", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP
        mpIconLocLabel->setText(QApplication::translate("IPropertyDialog", "Icon Location", 0, QApplication::UnicodeUTF8));
        mpLocationLabel->setText(QApplication::translate("IPropertyDialog", "/Icon/Location", 0, QApplication::UnicodeUTF8));
        mpEncryptionPanel->setTitle(QApplication::translate("IPropertyDialog", "Encryption", 0, QApplication::UnicodeUTF8));
        mpEncryptCheckBox->setText(QApplication::translate("IPropertyDialog", "Encrypt Entry", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("IPropertyDialog", "Password:", 0, QApplication::UnicodeUTF8));
        textLabel1_3->setText(QApplication::translate("IPropertyDialog", "Retype:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mpPasswdLineOne->setProperty("toolTip", QVariant(QApplication::translate("IPropertyDialog", "Enter Password for Encryption", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP
        tabWidget->setTabText(tabWidget->indexOf(Widget8), QApplication::translate("IPropertyDialog", "Properties", 0, QApplication::UnicodeUTF8));
        mpButtonApply->setText(QApplication::translate("IPropertyDialog", "&Apply", 0, QApplication::UnicodeUTF8));
        mpButtonApply->setShortcut(QApplication::translate("IPropertyDialog", "Alt+A", 0, QApplication::UnicodeUTF8));
        pButtonCancel->setText(QApplication::translate("IPropertyDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        pButtonCancel->setShortcut(QString());
        Q_UNUSED(IPropertyDialog);
    } // retranslateUi


protected:
    enum IconID
    {
        image0_ID,
        image1_ID,
        unknown_ID
    };
    static QPixmap qt_get_icon(IconID id)
    {
    static const unsigned char image0_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x16,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xc4, 0xb4, 0x6c, 0x3b, 0x00, 0x00, 0x02,
    0xd3, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0x9d, 0x95, 0x3f, 0x68, 0x1b,
    0x57, 0x1c, 0xc7, 0x3f, 0x2e, 0x37, 0xfc, 0x04, 0x1e, 0x74, 0x90, 0x82,
    0x04, 0x1d, 0x72, 0xe0, 0xa1, 0x27, 0x32, 0x54, 0xa6, 0x81, 0xb6, 0xb8,
    0x83, 0x0d, 0x1d, 0xe2, 0x51, 0xab, 0x9b, 0x42, 0x9b, 0x6e, 0xce, 0x28,
    0x5a, 0x5a, 0x70, 0x87, 0x82, 0x3b, 0x18, 0x77, 0x2a, 0xee, 0x52, 0x42,
    0x97, 0xd2, 0xc5, 0x20, 0x02, 0xa5, 0x31, 0x24, 0x44, 0x2e, 0x24, 0x3d,
    0x19, 0x0a, 0xbd, 0x21, 0x46, 0x2f, 0x83, 0xe1, 0x0c, 0x35, 0xdc, 0x41,
    0x03, 0x12, 0x44, 0xf0, 0x7e, 0xa0, 0x07, 0xe9, 0x70, 0x96, 0x6c, 0xf9,
    0xa4, 0x34, 0xf1, 0x6f, 0xb8, 0x83, 0xf7, 0xe3, 0x7d, 0xde, 0xf7, 0x7d,
    0xee, 0xcf, 0x9b, 0x8b, 0xa2, 0x08, 0x80, 0x87, 0xfb, 0x0f, 0x5f, 0x00,
    0xe0, 0x40, 0x9d, 0x9e, 0xdd, 0x4f, 0xc7, 0xac, 0xb3, 0xc5, 0x9e, 0xcb,
    0xdb, 0xea, 0x14, 0x86, 0xd0, 0xfc, 0xa2, 0x39, 0xf7, 0xe7, 0xd6, 0xad,
    0x17, 0xcd, 0x4f, 0xea, 0x78, 0x9c, 0xab, 0xd5, 0x8f, 0x56, 0xb9, 0x4c,
    0xa9, 0xa6, 0x6c, 0x6e, 0xfd, 0xc8, 0x08, 0xca, 0x52, 0xe3, 0x1c, 0xf8,
    0x74, 0xf5, 0xc5, 0xeb, 0x8b, 0x53, 0x27, 0x77, 0x4d, 0x97, 0x5a, 0x58,
    0x9b, 0xda, 0x8b, 0xf6, 0x7f, 0x67, 0xd9, 0x4b, 0x58, 0xbb, 0x11, 0xc2,
    0x52, 0x03, 0x76, 0x37, 0x27, 0x13, 0x5f, 0xb6, 0xa2, 0x9f, 0x37, 0x58,
    0xbb, 0x11, 0x52, 0x5d, 0x5e, 0x87, 0xdd, 0x26, 0x0c, 0x62, 0xde, 0x18,
    0x6f, 0x67, 0xe4, 0xf3, 0x35, 0x6b, 0xe7, 0xb3, 0x1a, 0x6b, 0x4b, 0x41,
    0x0e, 0x7d, 0xd0, 0x84, 0x67, 0x31, 0x38, 0x8a, 0x2a, 0xba, 0xa6, 0x3b,
    0x13, 0x32, 0xd1, 0x73, 0xd0, 0xf9, 0xe1, 0x63, 0x1a, 0xef, 0x85, 0x54,
    0xaf, 0x37, 0xce, 0xa0, 0x1e, 0xe0, 0x51, 0x54, 0x31, 0xcb, 0xe3, 0x45,
    0xc7, 0xed, 0xaf, 0x3f, 0x60, 0xf5, 0xdd, 0x20, 0x87, 0x76, 0xbe, 0x87,
    0x7e, 0x0e, 0xb5, 0x40, 0x72, 0x7c, 0x0e, 0xfc, 0x3a, 0x2a, 0xa2, 0x6f,
    0x57, 0x08, 0x2a, 0xfe, 0x19, 0xf4, 0x99, 0x19, 0x43, 0xcd, 0x11, 0x98,
    0x7f, 0xa7, 0xa8, 0xf8, 0xbf, 0xb2, 0x7b, 0x3b, 0x84, 0xf5, 0x45, 0xfc,
    0xb7, 0xea, 0x85, 0xa4, 0xe6, 0x18, 0xe2, 0x14, 0x6e, 0x3f, 0x96, 0xa2,
    0x8a, 0x97, 0x39, 0xb6, 0x7b, 0x3b, 0x94, 0xde, 0x0e, 0x29, 0xc9, 0x32,
    0xbd, 0xdf, 0x76, 0xf0, 0x2f, 0x24, 0x1d, 0x41, 0xdb, 0xf7, 0xdb, 0x73,
    0x63, 0xb0, 0x75, 0x16, 0x78, 0x89, 0xe3, 0x27, 0x5d, 0x4a, 0x95, 0x32,
    0x5c, 0x09, 0xb1, 0x87, 0x11, 0x0c, 0xfa, 0x58, 0x07, 0x25, 0x04, 0x73,
    0xa2, 0xc4, 0xff, 0xc0, 0xed, 0x83, 0x1c, 0x0a, 0xaf, 0xaa, 0xc2, 0x5a,
    0x82, 0x93, 0x7d, 0x78, 0xe7, 0x7d, 0xc8, 0x0c, 0xfa, 0xa4, 0x4d, 0xff,
    0x38, 0x41, 0x5c, 0x40, 0x3c, 0x48, 0x31, 0xa9, 0x4e, 0x40, 0x27, 0xc1,
    0xb3, 0x6a, 0x68, 0xb1, 0x4e, 0xf3, 0xb4, 0x9e, 0x60, 0x8f, 0x0c, 0x49,
    0xd6, 0x27, 0x19, 0x28, 0x49, 0x0f, 0x54, 0x85, 0xcd, 0x03, 0x41, 0x44,
    0x26, 0xa6, 0x15, 0xde, 0x8a, 0x09, 0xc7, 0x9a, 0x8f, 0x05, 0x59, 0x07,
    0xae, 0xd5, 0xb1, 0x07, 0xfb, 0x98, 0x38, 0xa2, 0xf3, 0x34, 0xc1, 0x5a,
    0x25, 0x76, 0x42, 0xeb, 0x71, 0x9f, 0xf5, 0x9b, 0xab, 0xdc, 0xd9, 0x6d,
    0x4f, 0x07, 0x8f, 0x54, 0xd4, 0xc2, 0x1a, 0x0c, 0x01, 0x2c, 0x38, 0xc5,
    0xaa, 0x52, 0xf2, 0xae, 0x62, 0x4f, 0x52, 0x4c, 0xfc, 0x37, 0x9d, 0xa7,
    0x09, 0xd1, 0x73, 0x25, 0x3e, 0xb2, 0x88, 0xc0, 0xf6, 0x57, 0xeb, 0xd8,
    0x41, 0xaf, 0xb0, 0xd1, 0xe9, 0x2a, 0xdc, 0x29, 0xd4, 0x29, 0x1b, 0x5f,
    0x7e, 0xce, 0xf2, 0xc2, 0x55, 0x7c, 0xa7, 0xb4, 0xfe, 0x32, 0xa4, 0x0e,
    0x4c, 0xa6, 0xac, 0x7f, 0xba, 0x86, 0x08, 0x94, 0xe7, 0x05, 0xed, 0xdb,
    0xd9, 0xe0, 0xf1, 0x07, 0x32, 0xb4, 0x80, 0x62, 0x51, 0xcc, 0x1f, 0x77,
    0x00, 0xd8, 0xf8, 0xa9, 0x45, 0x59, 0x04, 0x7f, 0x61, 0x91, 0x95, 0x0f,
    0x43, 0x56, 0x44, 0x28, 0x97, 0x85, 0xaa, 0xef, 0x53, 0x16, 0x48, 0xd0,
    0xc2, 0xc3, 0x2f, 0xfe, 0x2b, 0x0e, 0x63, 0xd4, 0x01, 0x4e, 0xf9, 0x75,
    0xaf, 0xc3, 0xbd, 0x47, 0x5d, 0x64, 0xbe, 0xca, 0xf6, 0x37, 0x0d, 0x5a,
    0x9d, 0x14, 0x9c, 0x22, 0x22, 0x08, 0xa0, 0xcf, 0x7b, 0x64, 0x0a, 0x25,
    0xaf, 0xf8, 0xe5, 0x16, 0x54, 0x04, 0x0b, 0x41, 0x7e, 0x42, 0x0c, 0x7a,
    0x24, 0x49, 0xca, 0x2f, 0xdf, 0xdd, 0x22, 0x4e, 0x94, 0x7b, 0x71, 0x4a,
    0xfd, 0x5a, 0x40, 0xf0, 0xa6, 0x8f, 0x7f, 0xa5, 0x82, 0x78, 0x00, 0x0a,
    0x4e, 0x31, 0x26, 0x9b, 0x9d, 0x78, 0xbc, 0xa2, 0x8e, 0x2f, 0x6c, 0x6f,
    0x6d, 0x93, 0x1c, 0x27, 0x54, 0x2a, 0x8a, 0xcc, 0x0b, 0x61, 0x10, 0xe0,
    0x0b, 0xe0, 0x8d, 0x8e, 0x2c, 0x45, 0x9d, 0x4c, 0x1e, 0x63, 0x85, 0xc4,
    0xc3, 0xfc, 0x88, 0x89, 0x0f, 0xd3, 0x71, 0x12, 0x55, 0xc5, 0x5a, 0x05,
    0x67, 0xa9, 0xfa, 0x42, 0x96, 0x25, 0x64, 0xa3, 0xd5, 0x87, 0x39, 0x78,
    0x14, 0x62, 0x66, 0xe2, 0xd6, 0xdd, 0x16, 0xad, 0xbb, 0xad, 0x8b, 0x66,
    0x2e, 0x5d, 0xff, 0x01, 0x3f, 0x24, 0x84, 0xd6, 0x63, 0x67, 0xb3, 0x23,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

    static const unsigned char image1_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x16,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xc4, 0xb4, 0x6c, 0x3b, 0x00, 0x00, 0x03,
    0x7f, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0xad, 0x95, 0x3f, 0x68, 0x1b,
    0x67, 0x18, 0xc6, 0x7f, 0x2a, 0x57, 0xfa, 0x1e, 0xc8, 0x70, 0x07, 0x2a,
    0xdc, 0x81, 0x0c, 0xbe, 0xa1, 0x83, 0x4c, 0x33, 0xd8, 0x10, 0x88, 0x0d,
    0x19, 0x2c, 0xf0, 0x10, 0x85, 0x14, 0xea, 0x51, 0xc1, 0x59, 0x92, 0xcd,
    0x4e, 0xa1, 0xb5, 0xd3, 0x21, 0x76, 0x9b, 0xa5, 0x5d, 0x4a, 0xc6, 0x96,
    0x42, 0xa9, 0x33, 0x04, 0xaa, 0x42, 0x0b, 0xc9, 0x54, 0x4d, 0xc1, 0x1d,
    0x4a, 0x94, 0x42, 0x8a, 0x35, 0x18, 0x7a, 0x01, 0x0f, 0x27, 0x88, 0xc9,
    0x09, 0x2a, 0xb8, 0x1b, 0x0c, 0xf7, 0x0e, 0x1f, 0xa8, 0xc3, 0xe9, 0x8f,
    0x15, 0xc9, 0x9d, 0xfa, 0x2c, 0xdf, 0xdd, 0xf7, 0xe7, 0xb9, 0xe7, 0x7d,
    0xdf, 0xe7, 0x7b, 0xaf, 0xd0, 0x6a, 0xb5, 0x78, 0x1b, 0x47, 0x7f, 0xfc,
    0xd6, 0x77, 0x1c, 0x1f, 0x35, 0x19, 0x02, 0xa8, 0x01, 0x0c, 0x24, 0x46,
    0xc1, 0x40, 0x9a, 0xa6, 0x60, 0x09, 0xd7, 0x6f, 0x5c, 0x2f, 0x4c, 0x1d,
    0x1e, 0xc0, 0x9a, 0x35, 0x29, 0x22, 0xac, 0xae, 0xd7, 0xf0, 0x4a, 0x1e,
    0x98, 0x7c, 0x97, 0x1a, 0x45, 0x2c, 0x41, 0xcf, 0x94, 0xb8, 0x17, 0xd3,
    0x6e, 0xb7, 0x79, 0xfe, 0xfb, 0xf3, 0xfe, 0xa3, 0x9f, 0x1f, 0x71, 0xf0,
    0xc3, 0xc1, 0xd4, 0x07, 0x66, 0x12, 0x63, 0xc0, 0x29, 0x3a, 0xd8, 0x73,
    0xf6, 0x68, 0xca, 0x26, 0x7f, 0xb6, 0xe7, 0x6c, 0xc4, 0x91, 0xd1, 0xe9,
    0xbd, 0x4f, 0xf7, 0xb8, 0x7d, 0xeb, 0x76, 0xff, 0xe0, 0xf1, 0x24, 0xf9,
    0x6c, 0x62, 0x72, 0x85, 0x17, 0xc1, 0xb6, 0x6d, 0xfc, 0x92, 0x4f, 0xf8,
    0x6e, 0x48, 0x75, 0xbd, 0x8a, 0xaa, 0x52, 0xbf, 0x55, 0xef, 0x37, 0x1e,
    0x37, 0x46, 0xe4, 0x33, 0x89, 0x87, 0x61, 0xff, 0x17, 0x44, 0x84, 0xe8,
    0x75, 0x84, 0x88, 0x50, 0xdf, 0xac, 0x83, 0x05, 0x0f, 0xbf, 0x79, 0xd8,
    0xdf, 0xfd, 0x7c, 0xb7, 0x70, 0xb1, 0x62, 0x55, 0xb4, 0x13, 0x91, 0x3d,
    0x7d, 0x42, 0xf8, 0xac, 0x49, 0xf4, 0x3a, 0x26, 0xd8, 0xbc, 0x89, 0x7f,
    0x96, 0x11, 0x97, 0x7d, 0x96, 0x3f, 0xbe, 0x89, 0xa2, 0x84, 0xaf, 0x42,
    0xee, 0x6c, 0xdd, 0xc1, 0x2f, 0xf9, 0x88, 0x40, 0x30, 0x1f, 0x8c, 0x28,
    0x0a, 0xb3, 0x5c, 0xf1, 0xe6, 0xfe, 0x4e, 0x7f, 0x75, 0xbe, 0xc2, 0x4f,
    0x9a, 0xd2, 0x2d, 0x7b, 0x38, 0x8e, 0xcb, 0x46, 0x27, 0xc6, 0x8e, 0x22,
    0x0e, 0x2f, 0x55, 0xa8, 0xdd, 0xdb, 0xc7, 0x9f, 0xf7, 0x49, 0x92, 0x84,
    0xf8, 0x34, 0xa6, 0x7b, 0x1a, 0x11, 0x45, 0x1d, 0xc2, 0x57, 0x7f, 0x13,
    0xf7, 0x52, 0xb6, 0xef, 0x6e, 0x17, 0xa6, 0x14, 0xbf, 0xa9, 0xd7, 0xfb,
    0x95, 0xcb, 0xab, 0x7c, 0x17, 0xbe, 0x20, 0xd8, 0xdc, 0xa2, 0xb6, 0xbe,
    0x46, 0x50, 0x0e, 0xe0, 0xc1, 0x17, 0x34, 0xcf, 0x42, 0x8e, 0x54, 0xa9,
    0x99, 0x7c, 0xaf, 0x2b, 0x2e, 0x5a, 0x52, 0x6c, 0x6b, 0x10, 0xbb, 0xc9,
    0x68, 0xbd, 0x6c, 0x00, 0xf0, 0xce, 0x04, 0xe9, 0x47, 0x1b, 0xfd, 0xd5,
    0xab, 0x55, 0x9e, 0x9c, 0xb4, 0x91, 0x1b, 0x75, 0xaa, 0xd7, 0x6a, 0x2c,
    0x56, 0x16, 0xb1, 0x4f, 0x23, 0xec, 0x92, 0x47, 0xaa, 0x29, 0xcb, 0x1f,
    0x2e, 0x8f, 0x5d, 0x41, 0x86, 0x23, 0x82, 0x08, 0x78, 0x8e, 0x8b, 0x53,
    0x72, 0x11, 0x64, 0x9a, 0xd8, 0x5f, 0xf0, 0x69, 0x9d, 0x84, 0xb4, 0x8b,
    0x0e, 0xd5, 0xb5, 0x2a, 0xc1, 0x07, 0x79, 0xce, 0xb2, 0x76, 0x08, 0xbd,
    0x2e, 0x11, 0x82, 0x17, 0x2c, 0xe0, 0x8a, 0x40, 0x96, 0x01, 0x0a, 0x46,
    0x11, 0xb1, 0xb1, 0x05, 0xdc, 0x39, 0x41, 0xd1, 0x69, 0xe2, 0xe0, 0xf2,
    0x0a, 0xa2, 0x8a, 0xf8, 0x3e, 0xbe, 0xe7, 0x8f, 0x17, 0x9e, 0x35, 0x49,
    0xa2, 0x88, 0x76, 0x49, 0x70, 0x8b, 0x36, 0xd9, 0xd0, 0x8a, 0x66, 0x5c,
    0x7e, 0x47, 0x1c, 0xc4, 0x62, 0xe4, 0xa6, 0x11, 0xf1, 0x7b, 0xf7, 0xf7,
    0xfa, 0xc9, 0x71, 0x48, 0xa3, 0x13, 0xe2, 0x97, 0x1c, 0x44, 0xf2, 0x0d,
    0xc9, 0x97, 0xfb, 0xd8, 0x45, 0x97, 0xe6, 0x9f, 0x2d, 0xd6, 0xae, 0x6d,
    0xe0, 0x7b, 0x1e, 0x36, 0x90, 0x69, 0x0a, 0x46, 0x41, 0x13, 0xc4, 0x64,
    0x28, 0x29, 0x62, 0x8d, 0xfd, 0x3f, 0x22, 0xf6, 0x1d, 0x97, 0x60, 0xa9,
    0xc2, 0x76, 0xf3, 0xb0, 0x80, 0x25, 0x88, 0x25, 0x64, 0xed, 0x23, 0x44,
    0x21, 0x7a, 0xd9, 0xe2, 0x50, 0xc0, 0x2f, 0xb9, 0xd0, 0x6e, 0x13, 0xf7,
    0x62, 0x30, 0x8c, 0x94, 0x9f, 0xf7, 0xfd, 0x70, 0x9c, 0x70, 0x85, 0x9d,
    0xa6, 0x83, 0x45, 0x48, 0xff, 0x6a, 0x91, 0xfd, 0xda, 0x20, 0x3a, 0x0e,
    0x71, 0x3b, 0x11, 0xc1, 0x95, 0x25, 0x2a, 0xbd, 0x84, 0xa8, 0xd7, 0x45,
    0xde, 0x77, 0x08, 0x16, 0x14, 0xa7, 0x28, 0x39, 0x29, 0x90, 0x6a, 0x3a,
    0x68, 0x58, 0x3a, 0x49, 0x1c, 0x9f, 0xc6, 0x48, 0x39, 0xcf, 0xeb, 0xd2,
    0xd3, 0x26, 0x49, 0x37, 0xa5, 0x01, 0x54, 0x2e, 0x55, 0x58, 0x54, 0xa5,
    0x6a, 0xb9, 0xc4, 0xbd, 0x2e, 0x1d, 0x47, 0x58, 0x29, 0x82, 0x23, 0x92,
    0x17, 0xce, 0x80, 0x9a, 0x74, 0xe0, 0x05, 0x9d, 0x56, 0xfc, 0x75, 0x37,
    0x64, 0x25, 0x8d, 0xb1, 0x3f, 0xdb, 0xea, 0x27, 0x8e, 0x4d, 0x53, 0x60,
    0xe7, 0xee, 0x0e, 0xe1, 0x71, 0x9b, 0xc3, 0x93, 0x10, 0x2c, 0x25, 0x16,
    0xa8, 0x5d, 0x5d, 0x21, 0xf0, 0xfc, 0x81, 0x52, 0xcd, 0x15, 0x1a, 0xc0,
    0x64, 0xa3, 0xb4, 0x4c, 0x10, 0xef, 0xfe, 0xd2, 0x1c, 0x35, 0x90, 0x1f,
    0xbf, 0xff, 0xb6, 0xbf, 0x7f, 0xef, 0x2b, 0xbc, 0xb2, 0x43, 0xe0, 0xf9,
    0xbc, 0x70, 0x1d, 0x32, 0x55, 0x56, 0xca, 0x7e, 0x5e, 0xd8, 0x81, 0xba,
    0x09, 0x52, 0xa3, 0xa8, 0x49, 0x66, 0xe7, 0x78, 0x08, 0xd7, 0x71, 0x10,
    0x21, 0xaf, 0xbe, 0xc0, 0xca, 0x95, 0x65, 0x54, 0xb3, 0xb1, 0x42, 0x40,
    0x75, 0x58, 0xb8, 0x64, 0x90, 0x0e, 0x1d, 0x8d, 0x13, 0xae, 0x38, 0x8f,
    0x6c, 0x50, 0xe5, 0xb1, 0x5f, 0x33, 0xc4, 0x02, 0x0c, 0x79, 0x81, 0xf4,
    0xdc, 0xfc, 0x90, 0x34, 0x8f, 0x81, 0xe1, 0x9d, 0xbc, 0xb0, 0x1f, 0xc7,
    0xbd, 0x08, 0x3b, 0x15, 0x32, 0x93, 0x62, 0x1b, 0xc8, 0xc8, 0xf2, 0xd1,
    0xa4, 0x83, 0xf0, 0x87, 0xca, 0x93, 0x91, 0x1b, 0xd2, 0x7f, 0xd2, 0xe9,
    0x1c, 0x9f, 0x47, 0x27, 0x8a, 0xd8, 0xfe, 0x64, 0x17, 0x25, 0x57, 0xf8,
    0xf6, 0xef, 0x09, 0xa3, 0x60, 0xc9, 0xe4, 0x3b, 0xe4, 0x97, 0xd9, 0xe4,
    0x9a, 0x67, 0xb6, 0xcd, 0xff, 0x03, 0xff, 0x02, 0xc0, 0x7c, 0xb0, 0x4e,
    0xd2, 0x81, 0x97, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44,
    0xae, 0x42, 0x60, 0x82
};

    switch (id) {
        case image0_ID:  { QImage img; img.loadFromData(image0_data, sizeof(image0_data), "PNG"); return QPixmap::fromImage(img); }
        case image1_ID:  { QImage img; img.loadFromData(image1_data, sizeof(image1_data), "PNG"); return QPixmap::fromImage(img); }
        default: return QPixmap();
    } // switch
    } // icon

};

namespace Ui {
    class IPropertyDialog: public Ui_IPropertyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // IPROPERTYDIALOG_H