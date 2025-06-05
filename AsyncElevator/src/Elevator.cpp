#include "Elevator.h"

#include "Floor.h"

Elevator::Elevator(QObject *object) : QObject(object)
{
    connect(this, &Elevator::signalNewCall, &_controller, &Controller::handleNewElevatorCall);
    connect(&_cabin._movingTimer, &QTimer::timeout, &_controller, &Controller::handleMove);
    connect(&_controller, &Controller::signalMoveCabin, &_cabin, &Cabin::move);
    connect(&_controller, &Controller::signalStopCabin, &_cabin, &Cabin::startStopping);
    connect(&_controller, &Controller::signalOpenCabin, &_cabin, &Cabin::stopped);
    connect(&_cabin, &Cabin::signalReadyToMove, &_controller, &Controller::handleMove);
}

void Elevator::call(Floor floor)
{
    emit signalNewCall(floor);
}
