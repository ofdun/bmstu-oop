#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "Elevator.h"

#include <QPushButton>
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
    void buttonPressedSignal(Floor floor);

private slots:
    void onFloor(Floor floor);
    void onButtonPressed(Floor floor);

    void on_floorButton10Down_clicked();
    void on_floorButton9Down_clicked();
    void on_floorButton8Down_clicked();
    void on_floorButton7Down_clicked();
    void on_floorButton6Down_clicked();
    void on_floorButton5Down_clicked();
    void on_floorButton4Down_clicked();
    void on_floorButton3Down_clicked();
    void on_floorButton2Down_clicked();

    void on_floorButton9Up_clicked();
    void on_floorButton8Up_clicked();
    void on_floorButton7Up_clicked();
    void on_floorButton6Up_clicked();
    void on_floorButton5Up_clicked();
    void on_floorButton4Up_clicked();
    void on_floorButton3Up_clicked();
    void on_floorButton2Up_clicked();
    void on_floorButton1Up_clicked();
    
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
    std::unordered_map<int, QPushButton *> buttons;

    Elevator _elevator;
    Ui::MainWindow *ui = nullptr;
};

#endif // MAINWINDOW_HPP
