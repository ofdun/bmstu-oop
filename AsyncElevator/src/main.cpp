#include <QApplication>
#include <iostream>
#include <vector>

#include "Cabin.h"
#include "Doors.h"
#include "ui/MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto w = MainWindow();
    w.show();
    
    // Doors doors;
    // Cabin cabin;
    //
    // QTimer timer;
    //
    // timer.setSingleShot(1);
    //
    // std::cout << "1";
    // timer.start(1000);
    // std::cout << "1";
    
    // Doors doors;
    // doors.opening();
    //
    // auto test = [&doors]() {
    //     std::cout << "test() вызван через 2.5 секунды\n";
    //     doors.opening();
    // };
    //
    // QTimer::singleShot(2500, test);
    
    return app.exec();
}