/********************************************************************************
** Form generated from reading ui file 'IOptionsDialog.ui'
**
** Created: Tue Jan 18 13:48:25 2011
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef IOPTIONSDIALOG_H
#define IOPTIONSDIALOG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
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

class Ui_IOptionsDialog
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *TabWidget2;
    QWidget *tab1;
    QVBoxLayout *vboxLayout1;
    QLabel *TextLabel1_3;
    QHBoxLayout *hboxLayout;
    QCheckBox *autosave;
    QLineEdit *saveMinutes;
    QLabel *TextLabel2_3;
    QSpacerItem *spacerItem;
    QCheckBox *saveWhenLeaving;
    QCheckBox *createBackup;
    Q3GroupBox *groupBox7;
    QHBoxLayout *hboxLayout1;
    QLineEdit *pCommandLine;
    QSpacerItem *spacerItem1;
    QLabel *textLabel1;
    Q3GroupBox *groupBox7_2;
    QHBoxLayout *hboxLayout2;
    QLineEdit *mpIconDirecory;
    QSpacerItem *spacerItem2;
    QWidget *tab4;
    QVBoxLayout *vboxLayout2;
    Q3GroupBox *GroupBox7_2;
    QVBoxLayout *vboxLayout3;
    QPushButton *treeFontButton;
    QLabel *TextLabel2_5_2;
    QLabel *treeFontText;
    QSpacerItem *spacerItem3;
    QSpacerItem *spacerItem4;
    QWidget *tab5;
    QVBoxLayout *vboxLayout4;
    Q3GroupBox *GroupBox7;
    QVBoxLayout *vboxLayout5;
    QPushButton *editorFontButton;
    QLabel *TextLabel2_5;
    QLabel *editorFontText;
    Q3GroupBox *GroupBox5;
    QHBoxLayout *hboxLayout3;
    QLabel *TextLabel1;
    QLineEdit *tabSize;
    QSpacerItem *spacerItem5;
    Q3ButtonGroup *ButtonGroup17;
    QVBoxLayout *vboxLayout6;
    QRadioButton *noWrap;
    QRadioButton *widgetWrap;
    QHBoxLayout *hboxLayout4;
    QRadioButton *columnWrap;
    QLineEdit *wrapColumn;
    QSpacerItem *spacerItem6;
    QHBoxLayout *hboxLayout5;
    QSpacerItem *spacerItem7;
    QPushButton *mpOkButton;
    QPushButton *PushButton19;

    void setupUi(QDialog *IOptionsDialog)
    {
        if (IOptionsDialog->objectName().isEmpty())
            IOptionsDialog->setObjectName(QString::fromUtf8("IOptionsDialog"));
        IOptionsDialog->resize(430, 432);
        vboxLayout = new QVBoxLayout(IOptionsDialog);
        vboxLayout->setSpacing(6);
        vboxLayout->setMargin(11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        TabWidget2 = new QTabWidget(IOptionsDialog);
        TabWidget2->setObjectName(QString::fromUtf8("TabWidget2"));
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        vboxLayout1 = new QVBoxLayout(tab1);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setMargin(11);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        TextLabel1_3 = new QLabel(tab1);
        TextLabel1_3->setObjectName(QString::fromUtf8("TextLabel1_3"));
        TextLabel1_3->setWordWrap(false);

        vboxLayout1->addWidget(TextLabel1_3);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        autosave = new QCheckBox(tab1);
        autosave->setObjectName(QString::fromUtf8("autosave"));
        autosave->setChecked(true);

        hboxLayout->addWidget(autosave);

        saveMinutes = new QLineEdit(tab1);
        saveMinutes->setObjectName(QString::fromUtf8("saveMinutes"));
        saveMinutes->setMaximumSize(QSize(50, 32767));

        hboxLayout->addWidget(saveMinutes);

        TextLabel2_3 = new QLabel(tab1);
        TextLabel2_3->setObjectName(QString::fromUtf8("TextLabel2_3"));
        TextLabel2_3->setWordWrap(false);

        hboxLayout->addWidget(TextLabel2_3);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        vboxLayout1->addLayout(hboxLayout);

        saveWhenLeaving = new QCheckBox(tab1);
        saveWhenLeaving->setObjectName(QString::fromUtf8("saveWhenLeaving"));
        saveWhenLeaving->setChecked(true);

        vboxLayout1->addWidget(saveWhenLeaving);

        createBackup = new QCheckBox(tab1);
        createBackup->setObjectName(QString::fromUtf8("createBackup"));

        vboxLayout1->addWidget(createBackup);

        groupBox7 = new Q3GroupBox(tab1);
        groupBox7->setObjectName(QString::fromUtf8("groupBox7"));
        groupBox7->setColumnLayout(0, Qt::Vertical);
        groupBox7->layout()->setSpacing(6);
        groupBox7->layout()->setMargin(11);
        hboxLayout1 = new QHBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(groupBox7->layout());
        if (boxlayout)
            boxlayout->addLayout(hboxLayout1);
        hboxLayout1->setAlignment(Qt::AlignTop);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        pCommandLine = new QLineEdit(groupBox7);
        pCommandLine->setObjectName(QString::fromUtf8("pCommandLine"));

        hboxLayout1->addWidget(pCommandLine);


        vboxLayout1->addWidget(groupBox7);

        spacerItem1 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacerItem1);

        textLabel1 = new QLabel(tab1);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        vboxLayout1->addWidget(textLabel1);

        groupBox7_2 = new Q3GroupBox(tab1);
        groupBox7_2->setObjectName(QString::fromUtf8("groupBox7_2"));
        groupBox7_2->setColumnLayout(0, Qt::Vertical);
        groupBox7_2->layout()->setSpacing(6);
        groupBox7_2->layout()->setMargin(11);
        hboxLayout2 = new QHBoxLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(groupBox7_2->layout());
        if (boxlayout1)
            boxlayout1->addLayout(hboxLayout2);
        hboxLayout2->setAlignment(Qt::AlignTop);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        mpIconDirecory = new QLineEdit(groupBox7_2);
        mpIconDirecory->setObjectName(QString::fromUtf8("mpIconDirecory"));

        hboxLayout2->addWidget(mpIconDirecory);


        vboxLayout1->addWidget(groupBox7_2);

        spacerItem2 = new QSpacerItem(20, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacerItem2);

        TabWidget2->addTab(tab1, QString());
        tab4 = new QWidget();
        tab4->setObjectName(QString::fromUtf8("tab4"));
        vboxLayout2 = new QVBoxLayout(tab4);
        vboxLayout2->setSpacing(6);
        vboxLayout2->setMargin(11);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        vboxLayout2->setContentsMargins(11, 11, 11, 11);
        GroupBox7_2 = new Q3GroupBox(tab4);
        GroupBox7_2->setObjectName(QString::fromUtf8("GroupBox7_2"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        GroupBox7_2->setFont(font);
        GroupBox7_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        GroupBox7_2->setColumnLayout(0, Qt::Vertical);
        GroupBox7_2->layout()->setSpacing(6);
        GroupBox7_2->layout()->setMargin(11);
        vboxLayout3 = new QVBoxLayout();
        QBoxLayout *boxlayout2 = qobject_cast<QBoxLayout *>(GroupBox7_2->layout());
        if (boxlayout2)
            boxlayout2->addLayout(vboxLayout3);
        vboxLayout3->setAlignment(Qt::AlignTop);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        GroupBox7_2->layout()->setContentsMargins(11, 11, 11, 11);
        treeFontButton = new QPushButton(GroupBox7_2);
        treeFontButton->setObjectName(QString::fromUtf8("treeFontButton"));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        treeFontButton->setFont(font1);

        vboxLayout3->addWidget(treeFontButton);

        TextLabel2_5_2 = new QLabel(GroupBox7_2);
        TextLabel2_5_2->setObjectName(QString::fromUtf8("TextLabel2_5_2"));
        TextLabel2_5_2->setFont(font1);
        TextLabel2_5_2->setWordWrap(false);

        vboxLayout3->addWidget(TextLabel2_5_2);

        treeFontText = new QLabel(GroupBox7_2);
        treeFontText->setObjectName(QString::fromUtf8("treeFontText"));
        treeFontText->setFont(font1);
        treeFontText->setWordWrap(false);

        vboxLayout3->addWidget(treeFontText);

        spacerItem3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout3->addItem(spacerItem3);


        vboxLayout2->addWidget(GroupBox7_2);

        spacerItem4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout2->addItem(spacerItem4);

        TabWidget2->addTab(tab4, QString());
        tab5 = new QWidget();
        tab5->setObjectName(QString::fromUtf8("tab5"));
        vboxLayout4 = new QVBoxLayout(tab5);
        vboxLayout4->setSpacing(6);
        vboxLayout4->setMargin(11);
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        GroupBox7 = new Q3GroupBox(tab5);
        GroupBox7->setObjectName(QString::fromUtf8("GroupBox7"));
        GroupBox7->setFont(font);
        GroupBox7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        GroupBox7->setColumnLayout(0, Qt::Vertical);
        GroupBox7->layout()->setSpacing(6);
        GroupBox7->layout()->setMargin(11);
        vboxLayout5 = new QVBoxLayout();
        QBoxLayout *boxlayout3 = qobject_cast<QBoxLayout *>(GroupBox7->layout());
        if (boxlayout3)
            boxlayout3->addLayout(vboxLayout5);
        vboxLayout5->setAlignment(Qt::AlignTop);
        vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
        GroupBox7->layout()->setContentsMargins(11, 11, 11, 11);
        editorFontButton = new QPushButton(GroupBox7);
        editorFontButton->setObjectName(QString::fromUtf8("editorFontButton"));
        editorFontButton->setFont(font1);

        vboxLayout5->addWidget(editorFontButton);

        TextLabel2_5 = new QLabel(GroupBox7);
        TextLabel2_5->setObjectName(QString::fromUtf8("TextLabel2_5"));
        TextLabel2_5->setFont(font1);
        TextLabel2_5->setWordWrap(false);

        vboxLayout5->addWidget(TextLabel2_5);

        editorFontText = new QLabel(GroupBox7);
        editorFontText->setObjectName(QString::fromUtf8("editorFontText"));
        editorFontText->setFont(font1);
        editorFontText->setWordWrap(false);

        vboxLayout5->addWidget(editorFontText);


        vboxLayout4->addWidget(GroupBox7);

        GroupBox5 = new Q3GroupBox(tab5);
        GroupBox5->setObjectName(QString::fromUtf8("GroupBox5"));
        GroupBox5->setFont(font);
        GroupBox5->setColumnLayout(0, Qt::Vertical);
        GroupBox5->layout()->setSpacing(6);
        GroupBox5->layout()->setMargin(11);
        hboxLayout3 = new QHBoxLayout();
        QBoxLayout *boxlayout4 = qobject_cast<QBoxLayout *>(GroupBox5->layout());
        if (boxlayout4)
            boxlayout4->addLayout(hboxLayout3);
        hboxLayout3->setAlignment(Qt::AlignTop);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        GroupBox5->layout()->setContentsMargins(11, 11, 11, 11);
        TextLabel1 = new QLabel(GroupBox5);
        TextLabel1->setObjectName(QString::fromUtf8("TextLabel1"));
        TextLabel1->setFont(font1);
        TextLabel1->setWordWrap(false);

        hboxLayout3->addWidget(TextLabel1);

        tabSize = new QLineEdit(GroupBox5);
        tabSize->setObjectName(QString::fromUtf8("tabSize"));
        tabSize->setMinimumSize(QSize(0, 0));
        tabSize->setMaximumSize(QSize(40, 32767));
        tabSize->setFont(font1);

        hboxLayout3->addWidget(tabSize);

        spacerItem5 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(spacerItem5);


        vboxLayout4->addWidget(GroupBox5);

        ButtonGroup17 = new Q3ButtonGroup(tab5);
        ButtonGroup17->setObjectName(QString::fromUtf8("ButtonGroup17"));
        ButtonGroup17->setFont(font);
        ButtonGroup17->setColumnLayout(0, Qt::Vertical);
        ButtonGroup17->layout()->setSpacing(6);
        ButtonGroup17->layout()->setMargin(11);
        vboxLayout6 = new QVBoxLayout();
        QBoxLayout *boxlayout5 = qobject_cast<QBoxLayout *>(ButtonGroup17->layout());
        if (boxlayout5)
            boxlayout5->addLayout(vboxLayout6);
        vboxLayout6->setAlignment(Qt::AlignTop);
        vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
        ButtonGroup17->layout()->setContentsMargins(11, 11, 11, 11);
        noWrap = new QRadioButton(ButtonGroup17);
        noWrap->setObjectName(QString::fromUtf8("noWrap"));
        noWrap->setFont(font1);
        noWrap->setChecked(true);

        vboxLayout6->addWidget(noWrap);

        widgetWrap = new QRadioButton(ButtonGroup17);
        widgetWrap->setObjectName(QString::fromUtf8("widgetWrap"));
        widgetWrap->setFont(font1);

        vboxLayout6->addWidget(widgetWrap);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        hboxLayout4->setContentsMargins(0, 0, 0, 0);
        columnWrap = new QRadioButton(ButtonGroup17);
        columnWrap->setObjectName(QString::fromUtf8("columnWrap"));
        columnWrap->setFont(font1);

        hboxLayout4->addWidget(columnWrap);

        wrapColumn = new QLineEdit(ButtonGroup17);
        wrapColumn->setObjectName(QString::fromUtf8("wrapColumn"));
        wrapColumn->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wrapColumn->sizePolicy().hasHeightForWidth());
        wrapColumn->setSizePolicy(sizePolicy);
        wrapColumn->setMinimumSize(QSize(0, 0));
        wrapColumn->setMaximumSize(QSize(40, 32767));
        wrapColumn->setFont(font1);

        hboxLayout4->addWidget(wrapColumn);

        spacerItem6 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout4->addItem(spacerItem6);


        vboxLayout6->addLayout(hboxLayout4);


        vboxLayout4->addWidget(ButtonGroup17);

        TabWidget2->addTab(tab5, QString());

        vboxLayout->addWidget(TabWidget2);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        hboxLayout5->setContentsMargins(0, 0, 0, 0);
        spacerItem7 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout5->addItem(spacerItem7);

        mpOkButton = new QPushButton(IOptionsDialog);
        mpOkButton->setObjectName(QString::fromUtf8("mpOkButton"));
        mpOkButton->setFont(font);

        hboxLayout5->addWidget(mpOkButton);

        PushButton19 = new QPushButton(IOptionsDialog);
        PushButton19->setObjectName(QString::fromUtf8("PushButton19"));

        hboxLayout5->addWidget(PushButton19);


        vboxLayout->addLayout(hboxLayout5);


        retranslateUi(IOptionsDialog);
        QObject::connect(mpOkButton, SIGNAL(released()), IOptionsDialog, SLOT(accept()));
        QObject::connect(PushButton19, SIGNAL(released()), IOptionsDialog, SLOT(reject()));
        QObject::connect(columnWrap, SIGNAL(toggled(bool)), wrapColumn, SLOT(setEnabled(bool)));
        QObject::connect(autosave, SIGNAL(toggled(bool)), saveMinutes, SLOT(setEnabled(bool)));
        QObject::connect(treeFontButton, SIGNAL(clicked()), IOptionsDialog, SLOT(changeTreeFont()));
        QObject::connect(editorFontButton, SIGNAL(clicked()), IOptionsDialog, SLOT(changeEditFont()));

        TabWidget2->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(IOptionsDialog);
    } // setupUi

    void retranslateUi(QDialog *IOptionsDialog)
    {
        IOptionsDialog->setWindowTitle(QApplication::translate("IOptionsDialog", "TuxCards Options", 0, QApplication::UnicodeUTF8));
        TextLabel1_3->setText(QApplication::translate("IOptionsDialog", "<b>Saving</b>", 0, QApplication::UnicodeUTF8));
        autosave->setText(QApplication::translate("IOptionsDialog", "Autosave all", 0, QApplication::UnicodeUTF8));
        saveMinutes->setText(QApplication::translate("IOptionsDialog", "15", 0, QApplication::UnicodeUTF8));
        TextLabel2_3->setText(QApplication::translate("IOptionsDialog", "Minutes", 0, QApplication::UnicodeUTF8));
        saveWhenLeaving->setText(QApplication::translate("IOptionsDialog", "Save Data when leaving TuxCards", 0, QApplication::UnicodeUTF8));
        createBackup->setText(QApplication::translate("IOptionsDialog", "Create Backupfile", 0, QApplication::UnicodeUTF8));
        groupBox7->setTitle(QApplication::translate("IOptionsDialog", "Execute Command after Saving", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("IOptionsDialog", "<b>Look & Feel</b>", 0, QApplication::UnicodeUTF8));
        groupBox7_2->setTitle(QApplication::translate("IOptionsDialog", "Icon Directory", 0, QApplication::UnicodeUTF8));
        TabWidget2->setTabText(TabWidget2->indexOf(tab1), QApplication::translate("IOptionsDialog", "General", 0, QApplication::UnicodeUTF8));
        GroupBox7_2->setTitle(QApplication::translate("IOptionsDialog", "Font", 0, QApplication::UnicodeUTF8));
        treeFontButton->setText(QApplication::translate("IOptionsDialog", "Change current Font", 0, QApplication::UnicodeUTF8));
        TextLabel2_5_2->setText(QApplication::translate("IOptionsDialog", "current Font:", 0, QApplication::UnicodeUTF8));
        treeFontText->setText(QApplication::translate("IOptionsDialog", "Font-Text", 0, QApplication::UnicodeUTF8));
        TabWidget2->setTabText(TabWidget2->indexOf(tab4), QApplication::translate("IOptionsDialog", "Tree", 0, QApplication::UnicodeUTF8));
        GroupBox7->setTitle(QApplication::translate("IOptionsDialog", "Font", 0, QApplication::UnicodeUTF8));
        editorFontButton->setText(QApplication::translate("IOptionsDialog", "Change current Font", 0, QApplication::UnicodeUTF8));
        TextLabel2_5->setText(QApplication::translate("IOptionsDialog", "current Font:", 0, QApplication::UnicodeUTF8));
        editorFontText->setText(QApplication::translate("IOptionsDialog", "Font-Text", 0, QApplication::UnicodeUTF8));
        GroupBox5->setTitle(QApplication::translate("IOptionsDialog", "Tab Spacing", 0, QApplication::UnicodeUTF8));
        TextLabel1->setText(QApplication::translate("IOptionsDialog", "Set Tabsize to", 0, QApplication::UnicodeUTF8));
        ButtonGroup17->setTitle(QApplication::translate("IOptionsDialog", "WordWrap", 0, QApplication::UnicodeUTF8));
        noWrap->setText(QApplication::translate("IOptionsDialog", "no WordWrap", 0, QApplication::UnicodeUTF8));
        widgetWrap->setText(QApplication::translate("IOptionsDialog", "wrap at Window-width", 0, QApplication::UnicodeUTF8));
        columnWrap->setText(QApplication::translate("IOptionsDialog", "wrap at column", 0, QApplication::UnicodeUTF8));
        wrapColumn->setText(QApplication::translate("IOptionsDialog", "45", 0, QApplication::UnicodeUTF8));
        TabWidget2->setTabText(TabWidget2->indexOf(tab5), QApplication::translate("IOptionsDialog", "Editor", 0, QApplication::UnicodeUTF8));
        mpOkButton->setText(QApplication::translate("IOptionsDialog", "&Ok", 0, QApplication::UnicodeUTF8));
        mpOkButton->setShortcut(QApplication::translate("IOptionsDialog", "Alt+O", 0, QApplication::UnicodeUTF8));
        PushButton19->setText(QApplication::translate("IOptionsDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(IOptionsDialog);
    } // retranslateUi

};

namespace Ui {
    class IOptionsDialog: public Ui_IOptionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // IOPTIONSDIALOG_H
