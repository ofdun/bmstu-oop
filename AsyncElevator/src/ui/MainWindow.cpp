#include "MainWindow.hpp"

#include <unordered_map>

#include "ui_MainWindow.h"

#define GREEN_BUTTON_STYLESHEET "background-color: green;"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(this, &MainWindow::buttonPressedSignal, &_elevator, &Elevator::newCall);
    connect(&_elevator._controller, &Controller::onFloor, this, &MainWindow::onFloor);

    auto size = ui->floor1->sizeHint();
    ui->floor1->setStyleSheet(GREEN_BUTTON_STYLESHEET);
    ui->floor1->setFixedSize(size);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::onFloor(int floor)
{
    static std::unordered_map<int, QPushButton *> mp {
        {1, ui->floor1},
        {2, ui->floor2},
        {3, ui->floor3},
        {4, ui->floor4},
        {5, ui->floor5},
        {6, ui->floor6},
        {7, ui->floor7},
        {8, ui->floor8},
        {9, ui->floor9},
        {10, ui->floor10},
    };
    
    if (mp.contains(floor - 1))
        mp[floor - 1]->setStyleSheet("");
    if (mp.contains(floor + 1))
        mp[floor + 1]->setStyleSheet("");

    auto size = ui->floor1->sizeHint();
    mp[floor]->setStyleSheet(GREEN_BUTTON_STYLESHEET);
    mp[floor]->setFixedSize(size);
}

void MainWindow::onButtonPressed(int floor)
{
    emit buttonPressedSignal(floor);
}

void MainWindow::on_floorButton1_clicked()
{
    onButtonPressed(1);
}

void MainWindow::on_floorButton2_clicked()
{
    onButtonPressed(2);
}

void MainWindow::on_floorButton3_clicked()
{
    onButtonPressed(3);
}

void MainWindow::on_floorButton4_clicked()
{
    onButtonPressed(4);
}

void MainWindow::on_floorButton5_clicked()
{
    onButtonPressed(5);
}

void MainWindow::on_floorButton6_clicked()
{
    onButtonPressed(6);
}

void MainWindow::on_floorButton7_clicked()
{
    onButtonPressed(7);
}

void MainWindow::on_floorButton8_clicked()
{
    onButtonPressed(8);
}

void MainWindow::on_floorButton9_clicked()
{
    onButtonPressed(9);
}

void MainWindow::on_floorButton10_clicked()
{
    onButtonPressed(10);
}

void MainWindow::on_elevatorButton1_clicked()
{
    onButtonPressed(1);
}

void MainWindow::on_elevatorButton2_clicked()
{
    onButtonPressed(2);
}

void MainWindow::on_elevatorButton3_clicked()
{
    onButtonPressed(3);
}

void MainWindow::on_elevatorButton4_clicked()
{
    onButtonPressed(4);
}

void MainWindow::on_elevatorButton5_clicked()
{
    onButtonPressed(5);
}

void MainWindow::on_elevatorButton6_clicked()
{
    onButtonPressed(6);
}

void MainWindow::on_elevatorButton7_clicked()
{
    onButtonPressed(7);
}

void MainWindow::on_elevatorButton8_clicked()
{
    onButtonPressed(8);
}

void MainWindow::on_elevatorButton9_clicked()
{
    onButtonPressed(9);
}

void MainWindow::on_elevatorButton10_clicked()
{
    onButtonPressed(10);
}