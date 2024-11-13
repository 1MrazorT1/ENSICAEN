/********************************************************************************
** Form generated from reading UI file 'gpcontrolview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GPCONTROLVIEW_H
#define UI_GPCONTROLVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "gpmapselector.h"

QT_BEGIN_NAMESPACE

class Ui_GPControlView
{
public:
    QVBoxLayout *verticalLayout;
    GPMapSelector *gpMapSelector;
    QGroupBox *driverGroupBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *cbFollow;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QComboBox *cbNextCarMode;
    QHBoxLayout *horizontalLayout_2;
    QLabel *delayLabel1;
    QSlider *delaySlider;
    QLabel *delayLabel2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pbRun;
    QToolButton *tbStep;
    QToolButton *tbTenSteps;
    QPushButton *abortbutton;
    QSpacerItem *horizontalSpacer;
    QToolButton *tbStderr;

    void setupUi(QWidget *GPControlView)
    {
        if (GPControlView->objectName().isEmpty())
            GPControlView->setObjectName(QString::fromUtf8("GPControlView"));
        GPControlView->resize(250, 364);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GPControlView->sizePolicy().hasHeightForWidth());
        GPControlView->setSizePolicy(sizePolicy);
        GPControlView->setMinimumSize(QSize(250, 0));
        GPControlView->setMaximumSize(QSize(250, 16777215));
        verticalLayout = new QVBoxLayout(GPControlView);
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        gpMapSelector = new GPMapSelector(GPControlView);
        gpMapSelector->setObjectName(QString::fromUtf8("gpMapSelector"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(gpMapSelector->sizePolicy().hasHeightForWidth());
        gpMapSelector->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(gpMapSelector);

        driverGroupBox = new QGroupBox(GPControlView);
        driverGroupBox->setObjectName(QString::fromUtf8("driverGroupBox"));
        sizePolicy1.setHeightForWidth(driverGroupBox->sizePolicy().hasHeightForWidth());
        driverGroupBox->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(driverGroupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(GPControlView);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_2);

        cbFollow = new QComboBox(GPControlView);
        cbFollow->setObjectName(QString::fromUtf8("cbFollow"));

        horizontalLayout_3->addWidget(cbFollow);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(GPControlView);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(label_3);

        cbNextCarMode = new QComboBox(GPControlView);
        cbNextCarMode->setObjectName(QString::fromUtf8("cbNextCarMode"));

        horizontalLayout_4->addWidget(cbNextCarMode);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        delayLabel1 = new QLabel(GPControlView);
        delayLabel1->setObjectName(QString::fromUtf8("delayLabel1"));
        sizePolicy.setHeightForWidth(delayLabel1->sizePolicy().hasHeightForWidth());
        delayLabel1->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(delayLabel1);

        delaySlider = new QSlider(GPControlView);
        delaySlider->setObjectName(QString::fromUtf8("delaySlider"));
        delaySlider->setMaximum(20);
        delaySlider->setPageStep(1);
        delaySlider->setSliderPosition(1);
        delaySlider->setOrientation(Qt::Horizontal);
        delaySlider->setTickPosition(QSlider::NoTicks);
        delaySlider->setTickInterval(2);

        horizontalLayout_2->addWidget(delaySlider);

        delayLabel2 = new QLabel(GPControlView);
        delayLabel2->setObjectName(QString::fromUtf8("delayLabel2"));

        horizontalLayout_2->addWidget(delayLabel2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pbRun = new QPushButton(GPControlView);
        pbRun->setObjectName(QString::fromUtf8("pbRun"));

        horizontalLayout->addWidget(pbRun);

        tbStep = new QToolButton(GPControlView);
        tbStep->setObjectName(QString::fromUtf8("tbStep"));

        horizontalLayout->addWidget(tbStep);

        tbTenSteps = new QToolButton(GPControlView);
        tbTenSteps->setObjectName(QString::fromUtf8("tbTenSteps"));

        horizontalLayout->addWidget(tbTenSteps);

        abortbutton = new QPushButton(GPControlView);
        abortbutton->setObjectName(QString::fromUtf8("abortbutton"));

        horizontalLayout->addWidget(abortbutton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        tbStderr = new QToolButton(GPControlView);
        tbStderr->setObjectName(QString::fromUtf8("tbStderr"));

        horizontalLayout->addWidget(tbStderr);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(GPControlView);

        QMetaObject::connectSlotsByName(GPControlView);
    } // setupUi

    void retranslateUi(QWidget *GPControlView)
    {
        GPControlView->setWindowTitle(QCoreApplication::translate("GPControlView", "Form", nullptr));
        driverGroupBox->setTitle(QCoreApplication::translate("GPControlView", "Driver selection", nullptr));
        label_2->setText(QCoreApplication::translate("GPControlView", "Follow", nullptr));
        label_3->setText(QCoreApplication::translate("GPControlView", "Order", nullptr));
        delayLabel1->setText(QCoreApplication::translate("GPControlView", "Slow", nullptr));
        delayLabel2->setText(QCoreApplication::translate("GPControlView", "Fast", nullptr));
        pbRun->setText(QCoreApplication::translate("GPControlView", "Run", nullptr));
        tbStep->setText(QCoreApplication::translate("GPControlView", ">", nullptr));
        tbTenSteps->setText(QCoreApplication::translate("GPControlView", ">>", nullptr));
        abortbutton->setText(QCoreApplication::translate("GPControlView", "Abort", nullptr));
        tbStderr->setText(QCoreApplication::translate("GPControlView", "StdErr", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GPControlView: public Ui_GPControlView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GPCONTROLVIEW_H
