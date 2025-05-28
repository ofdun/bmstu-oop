#pragma once
#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
    static constexpr int STARTING_FLOOR = 1;

public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller() override = default;

signals:
    void targetReached();
    void moveToNewTarget();
    void newTargetAdded();
    void noTarget();
    
    void moveCabin();
    void stopCabin();
    void openCabin();

    void onFloor(int floor); // для ui
    
public slots:
    void wait(); // KO1
    void handleMove(); // KO2
    void handleStanding(); // KO3
    void handleNewElevatorCall(int floor); // KO4

private:
    void insertFloorToProcess(int floor);

    enum Direction
    {
        UP = 1,
        DOWN = -1,
    };
    
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
    std::deque<int> _toProcess;
};