//
// Created by Morisummer on 2021/10/16.
//

#ifndef ASSEMBLER_DEV_UI_DIALOG_H
#define ASSEMBLER_DEV_UI_DIALOG_H
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <string>
#include <QPushButton>
#include "Handle.h"
QT_BEGIN_NAMESPACE

/**
 * 比较重要的两点：
 * 1.继承QObject
 * 2.slots
 */
class Ui_Assembler: public QObject
{
public:
    QLabel *label;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    string filename;
    void setupUi(QDialog *Assembler)
    {
        if (Assembler->objectName().isEmpty())
            Assembler->setObjectName(QString::fromUtf8("Assembler"));
        Assembler->resize(329, 224);
        label = new QLabel(Assembler);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 10, 131, 21));
        widget = new QWidget(Assembler);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(40, 50, 241, 161));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);

        retranslateUi(Assembler);
        QObject::connect(pushButton_2, SIGNAL(clicked()), lineEdit, SLOT(clear()));
        QMetaObject::connectSlotsByName(Assembler);
        QObject::connect(pushButton, &QPushButton::clicked, this, &Ui_Assembler::getfilename);
    } // setupUi

    void retranslateUi(QDialog *Assembler)
    {
        Assembler->setWindowTitle(QCoreApplication::translate("Assembler", "Assembler", nullptr));
        label->setText(QCoreApplication::translate("Assembler", "\350\257\267\350\276\223\345\205\245\346\226\207\344\273\266\347\273\235\345\257\271\350\267\257\345\276\204", nullptr));
        pushButton->setText(QCoreApplication::translate("Assembler", "ok", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Assembler", "clear", nullptr));
    } // retranslateUi
public slots:
    void getfilename(){
        filename = this->lineEdit->text().toStdString(); //得到文本框的内容
        op(filename);
        handle(filename);

    };
};

namespace Ui {
    class Assembler: public Ui_Assembler {};
} // namespace Ui



QT_END_NAMESPACE

#endif //ASSEMBLER_DEV_UI_DIALOG_H
