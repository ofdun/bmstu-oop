#pragma once
#include "Doors.h"

#include <QObject>

class Cabin : public QObject
{
    Q_OBJECT
    
    static constexpr int MOVING_TIMER_TIME = 1000;
    static constexpr int STOPPING_TIMER_TIME = 500;

public:
    explicit Cabin(QObject *parent = nullptr);
    ~Cabin() override = default;

signals:
    void SignalReadyToMove();
    void openDoors();
    void cabinMoved();
    void cabinStopped();

public slots:
    void move(); // KA1
    void startStopping(); // KA2
    void stopped(); // KA3
    void readyToMove(); // KA4

private:

    enum State
    {
        MOVING,
        STOPPING,
        STOPPED,
        READY_TO_MOVE,
    };

    State _state;
    Doors _doors;
    QTimer _movingTimer;
    QTimer _stoppingTimer;
};