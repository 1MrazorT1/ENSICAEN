/********************************************************************************
** Form generated from reading UI file 'grandprix.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRANDPRIX_H
#define UI_GRANDPRIX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "gpcontrolview.h"
#include "gpmapview.h"

QT_BEGIN_NAMESPACE

class Ui_GrandPrix
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_5;
    QSplitter *splitter_4;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    GPMapView *mapview;
    QSplitter *splitter;
    QSplitter *splitter_2;
    QSplitter *splitter_3;
    GPMapView *driverview;
    QPlainTextEdit *log;
    GPControlView *controlview;

    void setupUi(QMainWindow *GrandPrix)
    {
        if (GrandPrix->objectName().isEmpty())
            GrandPrix->setObjectName(QString::fromUtf8("GrandPrix"));
        GrandPrix->resize(859, 575);
        centralWidget = new QWidget(GrandPrix);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter_5 = new QSplitter(centralWidget);
        splitter_5->setObjectName(QString::fromUtf8("splitter_5"));
        splitter_5->setOrientation(Qt::Horizontal);
        splitter_4 = new QSplitter(splitter_5);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter_4->sizePolicy().hasHeightForWidth());
        splitter_4->setSizePolicy(sizePolicy);
        splitter_4->setMinimumSize(QSize(0, 551));
        splitter_4->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter_4);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        mapview = new GPMapView(layoutWidget);
        mapview->setObjectName(QString::fromUtf8("mapview"));
        sizePolicy.setHeightForWidth(mapview->sizePolicy().hasHeightForWidth());
        mapview->setSizePolicy(sizePolicy);
        mapview->setMinimumSize(QSize(0, 300));

        verticalLayout->addWidget(mapview);

        splitter_4->addWidget(layoutWidget);
        splitter = new QSplitter(splitter_4);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        splitter_2 = new QSplitter(splitter);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        sizePolicy.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy);
        splitter_2->setOrientation(Qt::Vertical);
        splitter_3 = new QSplitter(splitter_2);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        splitter_3->setHandleWidth(6);
        driverview = new GPMapView(splitter_3);
        driverview->setObjectName(QString::fromUtf8("driverview"));
        sizePolicy.setHeightForWidth(driverview->sizePolicy().hasHeightForWidth());
        driverview->setSizePolicy(sizePolicy);
        driverview->setMinimumSize(QSize(200, 200));
        splitter_3->addWidget(driverview);
        log = new QPlainTextEdit(splitter_3);
        log->setObjectName(QString::fromUtf8("log"));
        sizePolicy.setHeightForWidth(log->sizePolicy().hasHeightForWidth());
        log->setSizePolicy(sizePolicy);
        log->setReadOnly(true);
        splitter_3->addWidget(log);
        splitter_2->addWidget(splitter_3);
        splitter->addWidget(splitter_2);
        splitter_4->addWidget(splitter);
        splitter_5->addWidget(splitter_4);
        controlview = new GPControlView(splitter_5);
        controlview->setObjectName(QString::fromUtf8("controlview"));
        splitter_5->addWidget(controlview);

        gridLayout->addWidget(splitter_5, 0, 1, 1, 1);

        GrandPrix->setCentralWidget(centralWidget);

        retranslateUi(GrandPrix);

        QMetaObject::connectSlotsByName(GrandPrix);
    } // setupUi

    void retranslateUi(QMainWindow *GrandPrix)
    {
        GrandPrix->setWindowTitle(QString());
        log->setPlainText(QString());
    } // retranslateUi

};

namespace Ui {
    class GrandPrix: public Ui_GrandPrix {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRANDPRIX_H
