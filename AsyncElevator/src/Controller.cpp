#include "Controller.h"

#include "Floor.h"

#include <iostream>

Controller::Controller(QObject *parent) : QObject(parent)
{
    connect(this, &Controller::signalTargetReached, this, &Controller::handleStanding);
    connect(this, &Controller::signalNewTargetAdded, this, &Controller::handleMove);
    connect(this, &Controller::signalNoTarget, this, &Controller::wait);
    connect(this, &Controller::signalMoveToNewTarget, this, &Controller::handleMove);
    _state = WAITING;
    _direction = UP;

    _sortingFunction = [this](const Floor &a, const Floor &b) -> bool {
        auto aDir = a.direction == NONE ? _direction : a.direction;
        auto bDir = b.direction == NONE ? _direction : b.direction;
        
        if (aDir != bDir)
            return aDir == _direction;
        
        bool aGreater = a.floor > _curFloor;
        bool bGreater = b.floor > _curFloor;

        if (aGreater != bGreater)
            return _direction == UP ? aGreater : !aGreater;

        if (aDir == UP)
        {
            if (aGreater)
                return a.floor < b.floor;
            return a.floor > b.floor;
        } else
        {
            if (aGreater)
                return a.floor > b.floor;
            return a.floor < b.floor;
        }
    };
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

    auto was = _state;
    _state = HANDLE_MOVING;

    if (!_toProcess.empty())
    {
        if (_curFloor > _toProcess.front().floor && _direction == UP)
        {
            _direction = DOWN;
            std::ranges::sort(_toProcess, _sortingFunction);
        }
        else if (_curFloor < _toProcess.front().floor && _direction == DOWN)
        {
            _direction = UP;
            std::ranges::sort(_toProcess, _sortingFunction);
        }
    }

    if (was == HANDLE_MOVING || was == NEW_CALL)
    {
        _curFloor += _direction;
        emit signalOnFloor({_curFloor, NONE});
    }
    
    std::cout << "Очередь: ";
    for (const auto &a : _toProcess)
        std::cout << a.floor << ' ';
    std::cout << std::endl;

    
    if (_toProcess.empty())
    {
        std::cout << "У контроллера нет целей\n";
        emit signalNoTarget();
    }
    else
    {
        if (_curFloor == _toProcess.front().floor)
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
    else if (_curFloor == _toProcess.front().floor)
    {
        while (!_toProcess.empty() && _curFloor == _toProcess.front().floor)
            _toProcess.pop_front();
        
        if (was == HANDLE_MOVING)
            emit signalStopCabin();
        else
            emit signalOpenCabin();
    }
    else
        emit signalMoveToNewTarget();
    
}

void Controller::handleNewElevatorCall(Floor floor)
{
    auto was = _state;
    _state = NEW_CALL;
    
    insertFloorToProcess(floor);
    if (_curFloor == floor.floor)
        emit signalTargetReached();
    else if (was == WAITING)
        emit signalNewTargetAdded();
}

void Controller::insertFloorToProcess(Floor floor)
{
    if (std::ranges::find_if(_toProcess.begin(), _toProcess.end(),
        [floor](const auto &a){ return a.floor == floor.floor && a.direction == floor.direction; }) != _toProcess.end())
        return;
    
    _toProcess.push_back(floor);
    std::ranges::sort(_toProcess, _sortingFunction);
}
