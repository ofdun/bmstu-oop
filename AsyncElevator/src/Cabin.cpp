#include "Cabin.h"

#include <iostream>

Cabin::Cabin(QObject *parent) : QObject(parent)
{
    connect(this, &Cabin::signalCabinStopped, &_doors, &Doors::opening);
    connect(&_doors, &Doors::signalClosed, this, &Cabin::readyToMove);
    
    connect(&_stoppingTimer, &QTimer::timeout, this, &Cabin::stopped);
    _state = READY_TO_MOVE;
}

void Cabin::move()
{
    if (_state != MOVING && _state != READY_TO_MOVE)
        return;

    _state = MOVING;
    std::cout << "Кабина движется\n";
    _movingTimer.start(MOVING_TIMER_TIME);
}

void Cabin::startStopping()
{
    if (_state != MOVING)
        return;

    _movingTimer.stop();

    _state = STOPPING;
    std::cout << "Кабина останавливается\n";
    _stoppingTimer.start(STOPPING_TIMER_TIME);
}

void Cabin::stopped()
{
    if (_state != STOPPING && _state != READY_TO_MOVE && _state != STOPPED)
        return;

    auto was = _state;
    _state = STOPPED;
    
    if (was == STOPPING)
       _stoppingTimer.stop();
    
    std::cout << "Кабина готова к загрузке/разгрузке\n";
    
    emit signalCabinStopped();
}

void Cabin::readyToMove()
{
    if (_state != STOPPED)
        return;

    _state = READY_TO_MOVE;
    std::cout << "Кабина готова к движению\n";

    emit signalReadyToMove();
}
