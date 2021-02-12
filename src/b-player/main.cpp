#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    Widget widget;
    widget.show();

    return application.exec();
}
