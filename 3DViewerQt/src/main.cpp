#include <QApplication>

#include "MainWindow.hpp"

int main(int argc, char **argv)
{
    auto a = QApplication(argc, argv);
    auto w = MainWindow();
    w.show();

    return a.exec();
}
