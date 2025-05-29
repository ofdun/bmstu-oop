#include "Doors.h"

#include <QTimer>
#include <iostream>

Doors::Doors()
{
    _state = CLOSED;
    connect(&_openingTimer, &QTimer::timeout, this,&Doors::open);
    connect(&_closingTimer, &QTimer::timeout, this, &Doors::close);
    connect(&_openedTimer, &QTimer::timeout, this, &Doors::closing);
}

void Doors::close()
{
    if (_state != CLOSING)
        return;

    _state = CLOSED;
    std::cout << "Двери закрыты\n";
    emit signalClosed();
}

void Doors::closing()
{
    if (_state != OPENED)
        return;

    _closingTimer.start(CLOSING_TIMER_TIME);
    _state = CLOSING;
    std::cout << "Двери начинают закрываться\n";
}

void Doors::open()
{
    if (_state != OPENING)
        return;

    _openedTimer.start(BEING_OPENED_TIMER_TIME);
    _state = OPENED;
    std::cout << "Двери открыты\n";
}

void Doors::opening()
{
    if (_state != CLOSED && _state != CLOSING)
        return;

    if (_state == CLOSED)
        _openingTimer.start(OPENING_TIMER_TIME);
    else if (_state == CLOSING)
    {
        _openingTimer.start(OPENING_TIMER_TIME + _closingTimer.remainingTime());
        _closingTimer.stop();
    }

    _state = OPENING;
    std::cout << "Двери начинают открываться\n";
}
