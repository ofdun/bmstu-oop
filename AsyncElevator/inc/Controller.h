#pragma once
#include <QObject>

#include "Floor.h"

class Controller : public QObject
{
    Q_OBJECT
    static constexpr int STARTING_FLOOR = 1;

public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller() override = default;

signals:
    void signalTargetReached();
    void signalMoveToNewTarget();
    void signalNewTargetAdded();
    void signalNoTarget();
    
    void signalMoveCabin();
    void signalStopCabin();
    void signalOpenCabin();

    void signalOnFloor(Floor floor); // для ui
    
public slots:
    void wait(); // KO1
    void handleMove(); // KO2
    void handleStanding(); // KO3
    void handleNewElevatorCall(Floor floor); // KO4

private:
    void insertFloorToProcess(Floor floor);

    using SortingFunction = std::function<bool(const Floor &, const Floor &)>;
    
    enum State
    {
        WAITING,
        HANDLE_MOVING,
        HANDLE_STANDING,
        NEW_CALL,
    };

    int _curFloor = STARTING_FLOOR;
    State _state;
    Direction _direction;
    std::deque<Floor> _toProcess;
    SortingFunction _sortingFunction;
};