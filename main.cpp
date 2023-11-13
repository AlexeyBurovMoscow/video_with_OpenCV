#include "searchgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SearchGUI w;
    w.show();

    return a.exec();
}
