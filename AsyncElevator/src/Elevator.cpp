#include "Elevator.h"

Elevator::Elevator(QObject *object) : QObject(object)
{
    connect(this, &Elevator::newCall, &_controller, &Controller::handleNewElevatorCall);
    connect(&_cabin, &Cabin::cabinMoved, &_controller, &Controller::handleMove);
    connect(&_controller, &Controller::moveCabin, &_cabin, &Cabin::move);
    connect(&_controller, &Controller::stopCabin, &_cabin, &Cabin::startStopping);
    connect(&_controller, &Controller::openCabin, &_cabin, &Cabin::stopped);
    connect(&_cabin, &Cabin::SignalReadyToMove, &_controller, &Controller::handleMove);
}

void Elevator::call(int floor)
{
    emit newCall(floor);
}
