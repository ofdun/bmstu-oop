#include "MainWindow.hpp"

#include <unordered_map>

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(this, &MainWindow::buttonPressedSignal, &_elevator, &Elevator::signalNewCall);
    connect(&_elevator._controller, &Controller::signalOnFloor, this, &MainWindow::onFloor);

    buttons = {
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

    
    for (const auto &it : buttons)
    {
        auto pal = it.second->palette();
        if (it.first == 1)
            pal.setColor(QPalette::Button, QColor(Qt::green));
        else
            pal.setColor(QPalette::Button, QColor(Qt::gray));
        it.second->setAutoFillBackground(true);
        it.second->setPalette(pal);
        it.second->update();
    }
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::onFloor(int floor)
{
    if (buttons.contains(floor - 1))
    {
        auto pal = buttons[floor - 1]->palette();
        pal.setColor(QPalette::Button, QColor(Qt::gray));
        buttons[floor - 1]->setAutoFillBackground(true);
        buttons[floor - 1]->setPalette(pal);
        buttons[floor - 1]->update();
    }
    if (buttons.contains(floor + 1))
    {
        auto pal = buttons[floor + 1]->palette();
        pal.setColor(QPalette::Button, QColor(Qt::gray));
        buttons[floor + 1]->setAutoFillBackground(true);
        buttons[floor + 1]->setPalette(pal);
        buttons[floor + 1]->update();
    }

    auto pal = buttons[floor]->palette();
    pal.setColor(QPalette::Button, QColor(Qt::green));
    buttons[floor]->setAutoFillBackground(true);
    buttons[floor]->setPalette(pal);
    buttons[floor]->update();
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