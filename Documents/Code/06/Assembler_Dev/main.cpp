#include <QApplication>
#include <QPushButton>
#include <bits/stdc++.h>
using namespace std;
#include "Ui_Dialog.h"
/**
 * 1.先构建好UI(√)
 * 2.根据逻辑弄好各个模块以方便调用
 *
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Ui_Assembler ui;
    QDialog * dialog = new QDialog();
    ui.setupUi(dialog);
    dialog->show();
    return app.exec();
}
