/********************************************************************************
** Form generated from reading UI file 'gpprogression.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GPPROGRESSION_H
#define UI_GPPROGRESSION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GPProgression
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QProgressBar *progressBar;

    void setupUi(QWidget *GPProgression)
    {
        if (GPProgression->objectName().isEmpty())
            GPProgression->setObjectName(QString::fromUtf8("GPProgression"));
        GPProgression->resize(429, 54);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GPProgression->sizePolicy().hasHeightForWidth());
        GPProgression->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(GPProgression);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(GPProgression);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        progressBar = new QProgressBar(GPProgression);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        horizontalLayout->addWidget(progressBar);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(GPProgression);

        QMetaObject::connectSlotsByName(GPProgression);
    } // setupUi

    void retranslateUi(QWidget *GPProgression)
    {
        GPProgression->setWindowTitle(QCoreApplication::translate("GPProgression", "Form", nullptr));
        label->setText(QCoreApplication::translate("GPProgression", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GPProgression: public Ui_GPProgression {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GPPROGRESSION_H
