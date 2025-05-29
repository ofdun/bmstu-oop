#include "Controller.h"

#include <iostream>

Controller::Controller(QObject *parent) : QObject(parent)
{
    connect(this, &Controller::signalTargetReached, this, &Controller::handleStanding);
    connect(this, &Controller::signalNewTargetAdded, this, &Controller::handleMove);
    connect(this, &Controller::signalNoTarget, this, &Controller::wait);
    connect(this, &Controller::signalMoveToNewTarget, this, &Controller::handleMove);
    _state = WAITING;
    _direction = UP;
}

void Controller::wait()
{
    if (_state != HANDLE_MOVING && _state != HANDLE_STANDING)
        return;

    _state = WAITING;
    std::cout << "Лифт ждет\n";
}

void Controller::handleMove()
{
    if (_state != HANDLE_MOVING && _state != NEW_CALL && _state != HANDLE_STANDING)
        return;

    if (_state == HANDLE_MOVING)
    {
        _curFloor += _direction;
        emit signalOnFloor(_curFloor);
    }

    std::cout << "Очередь: ";
    for (const auto &a : _toProcess)
        std::cout << a << ' ';
    std::cout << std::endl;

    _state = HANDLE_MOVING;

    if (!_toProcess.empty())
    {
        if (_curFloor > _toProcess.front() && _direction == UP)
            _direction = DOWN;
        else if (_curFloor < _toProcess.front() && _direction == DOWN)
            _direction = UP;
    }
    
    if (_toProcess.empty())
    {
        std::cout << "У контроллера нет целей\n";
        emit signalNoTarget();
    }
    else
    {
        if (_curFloor == _toProcess.front())
            emit signalTargetReached();
        else
        {
            std::cout << "Лифт едет с " << _curFloor << " этажа на " << _curFloor + _direction << " этаж\n";
            emit signalMoveCabin();
        }
    }
}

void Controller::handleStanding()
{
    if (_state != NEW_CALL && _state != HANDLE_STANDING && _state != HANDLE_MOVING)
        return;

    auto was = _state;
    _state = HANDLE_STANDING;

    if (_toProcess.empty())
        emit signalNoTarget();
    else if (_curFloor == _toProcess.front())
    {
        _toProcess.pop_front();
        if (was == HANDLE_MOVING)
            emit signalStopCabin();
        else
            emit signalOpenCabin();
    }
    else
        emit signalMoveToNewTarget();
    
}

void Controller::handleNewElevatorCall(int floor)
{
    auto was = _state;
    _state = NEW_CALL;
    
    insertFloorToProcess(floor);
    if (_curFloor == floor)
        emit signalTargetReached();
    else if (was == WAITING)
        emit signalNewTargetAdded();
}

void Controller::insertFloorToProcess(int floor)
{
    if (std::ranges::find_if(_toProcess.begin(), _toProcess.end(),
        [floor](const auto &a){ return a == floor; }) != _toProcess.end())
        return;
    
    _toProcess.push_back(floor);
    auto cur = _curFloor;
    auto dir = _direction;

    std::sort(_toProcess.begin(), _toProcess.end(), [cur, dir](const auto &a, const auto &b) -> bool {
        bool aGreater = a > cur;
        bool bGreater = b > cur;

        if (aGreater != bGreater)
            return dir == UP ? aGreater : !aGreater;

        if (aGreater)
            return a < b;
        return a > b;
    });
}
