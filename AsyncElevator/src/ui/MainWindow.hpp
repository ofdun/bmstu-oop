#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "Elevator.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

signals:
    void buttonPressedSignal(int floor);

private slots:
    void onFloor(int floor);
    void onButtonPressed(int floor);
    
    void on_floorButton1_clicked();
    void on_floorButton2_clicked();
    void on_floorButton3_clicked();
    void on_floorButton4_clicked();
    void on_floorButton5_clicked();
    void on_floorButton6_clicked();
    void on_floorButton7_clicked();
    void on_floorButton8_clicked();
    void on_floorButton9_clicked();
    void on_floorButton10_clicked();
    
    void on_elevatorButton1_clicked();
    void on_elevatorButton2_clicked();
    void on_elevatorButton3_clicked();
    void on_elevatorButton4_clicked();
    void on_elevatorButton5_clicked();
    void on_elevatorButton6_clicked();
    void on_elevatorButton7_clicked();
    void on_elevatorButton8_clicked();
    void on_elevatorButton9_clicked();
    void on_elevatorButton10_clicked();

private:

    Elevator _elevator;
    Ui::MainWindow *ui = nullptr;
};

#endif // MAINWINDOW_HPP
