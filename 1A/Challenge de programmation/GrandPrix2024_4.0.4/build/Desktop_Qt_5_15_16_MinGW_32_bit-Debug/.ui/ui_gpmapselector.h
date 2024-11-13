/********************************************************************************
** Form generated from reading UI file 'gpmapselector.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GPMAPSELECTOR_H
#define UI_GPMAPSELECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GPMapSelector
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *listMap;

    void setupUi(QWidget *GPMapSelector)
    {
        if (GPMapSelector->objectName().isEmpty())
            GPMapSelector->setObjectName(QString::fromUtf8("GPMapSelector"));
        GPMapSelector->resize(400, 298);
        verticalLayout = new QVBoxLayout(GPMapSelector);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(GPMapSelector);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        listMap = new QListWidget(GPMapSelector);
        listMap->setObjectName(QString::fromUtf8("listMap"));

        verticalLayout->addWidget(listMap);


        retranslateUi(GPMapSelector);

        QMetaObject::connectSlotsByName(GPMapSelector);
    } // setupUi

    void retranslateUi(QWidget *GPMapSelector)
    {
        GPMapSelector->setWindowTitle(QCoreApplication::translate("GPMapSelector", "Form", nullptr));
        label->setText(QCoreApplication::translate("GPMapSelector", "<html><head/><body><p><span style=\" font-weight:600;\">Map selection</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GPMapSelector: public Ui_GPMapSelector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GPMAPSELECTOR_H
