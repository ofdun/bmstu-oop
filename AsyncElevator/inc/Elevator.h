#pragma once

#include <QObject>

#include "Controller.h"
#include "Cabin.h"

#include "Floor.h"

class Elevator : public QObject
{
    Q_OBJECT

    friend class MainWindow;

public:
    explicit Elevator(QObject *object = nullptr);
    
signals:
    void signalNewCall(Floor floor);

public slots:
    void call(Floor floor);

private:
    Controller _controller;
    Cabin _cabin;
};