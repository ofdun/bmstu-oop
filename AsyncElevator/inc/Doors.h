#pragma once

#include <QObject>
#include <QTimer>

class Doors : public QObject
{
    Q_OBJECT

    static constexpr int CLOSING_TIMER_TIME = 1000;
    static constexpr int OPENING_TIMER_TIME = 1000;
    static constexpr int BEING_OPENED_TIMER_TIME = 1000;

public:
    Doors();
    ~Doors() override = default;

signals:
    void signalClosed();

public slots:
    void close(); // Д1
    void opening(); // Д2
    void open(); // Д3
    void closing(); // Д4

private:
    enum State {
        CLOSED,
        CLOSING,
        OPENED,
        OPENING,
    };
    
    State _state;

    QTimer _closingTimer;
    QTimer _openingTimer;
    QTimer _openedTimer;
};