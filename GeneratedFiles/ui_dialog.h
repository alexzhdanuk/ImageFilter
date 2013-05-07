/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Tue 9. Apr 16:13:11 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGraphicsView *graphicsView;
    QPushButton *pushButton_2;
    QPushButton *ButtonTexture;
    QListWidget *listFilter;
    QLabel *label_13;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(858, 655);
        graphicsView = new QGraphicsView(Dialog);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(140, 20, 451, 621));
        pushButton_2 = new QPushButton(Dialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(620, 600, 114, 32));
        ButtonTexture = new QPushButton(Dialog);
        ButtonTexture->setObjectName(QString::fromUtf8("ButtonTexture"));
        ButtonTexture->setGeometry(QRect(740, 600, 111, 31));
        listFilter = new QListWidget(Dialog);
        listFilter->setObjectName(QString::fromUtf8("listFilter"));
        listFilter->setGeometry(QRect(10, 60, 121, 481));
        label_13 = new QLabel(Dialog);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 20, 91, 21));
        QFont font;
        font.setPointSize(12);
        label_13->setFont(font);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Dialog", "Add picture", 0, QApplication::UnicodeUTF8));
        ButtonTexture->setText(QApplication::translate("Dialog", "Add texture", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("Dialog", "\320\244\320\270\320\273\321\214\321\202\321\200\321\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
