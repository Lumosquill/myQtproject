/********************************************************************************
** Form generated from reading UI file 'gamewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWIDGET_H
#define UI_GAMEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Gamewidget
{
public:

    void setupUi(QWidget *Gamewidget)
    {
        if (Gamewidget->objectName().isEmpty())
            Gamewidget->setObjectName("Gamewidget");
        Gamewidget->resize(800, 600);

        retranslateUi(Gamewidget);

        QMetaObject::connectSlotsByName(Gamewidget);
    } // setupUi

    void retranslateUi(QWidget *Gamewidget)
    {
        Gamewidget->setWindowTitle(QCoreApplication::translate("Gamewidget", "Gamewidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Gamewidget: public Ui_Gamewidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWIDGET_H
