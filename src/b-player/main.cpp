#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    Widget widget;
    application.setWindowIcon(QIcon(":/icon/b-player.ico"));
    widget.show();

    return application.exec();
}
