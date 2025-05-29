#pragma once

#include <QObject>

#include "Controller.h"
#include "Cabin.h"

class Elevator : public QObject
{
    Q_OBJECT

    friend class MainWindow;

public:
    explicit Elevator(QObject *object = nullptr);
    
signals:
    void signalNewCall(int floor);

public slots:
    void call(int floor);

private:
    Controller _controller;
    Cabin _cabin;
};