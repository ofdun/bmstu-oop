#include "MainWindow.hpp"

#include <unordered_map>

#include "ui_MainWindow.h"
#include "Floor.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(this, &MainWindow::buttonPressedSignal, &_elevator, &Elevator::call);
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

void MainWindow::onFloor(Floor floor)
{
    if (buttons.contains(floor.floor - 1))
    {
        auto pal = buttons[floor.floor - 1]->palette();
        pal.setColor(QPalette::Button, QColor(Qt::gray));
        buttons[floor.floor - 1]->setAutoFillBackground(true);
        buttons[floor.floor - 1]->setPalette(pal);
        buttons[floor.floor - 1]->update();
    }
    if (buttons.contains(floor.floor + 1))
    {
        auto pal = buttons[floor.floor + 1]->palette();
        pal.setColor(QPalette::Button, QColor(Qt::gray));
        buttons[floor.floor + 1]->setAutoFillBackground(true);
        buttons[floor.floor + 1]->setPalette(pal);
        buttons[floor.floor + 1]->update();
    }

    auto pal = buttons[floor.floor]->palette();
    pal.setColor(QPalette::Button, QColor(Qt::green));
    buttons[floor.floor]->setAutoFillBackground(true);
    buttons[floor.floor]->setPalette(pal);
    buttons[floor.floor]->update();
}

void MainWindow::onButtonPressed(Floor floor)
{
    emit buttonPressedSignal(floor);
}

void MainWindow::on_elevatorButton1_clicked()
{
    onButtonPressed({1, ::NONE});
}

void MainWindow::on_elevatorButton2_clicked()
{
    onButtonPressed({2, ::NONE});
}

void MainWindow::on_elevatorButton3_clicked()
{
    onButtonPressed({3, ::NONE});
}

void MainWindow::on_elevatorButton4_clicked()
{
    onButtonPressed({4, ::NONE});
}

void MainWindow::on_elevatorButton5_clicked()
{
    onButtonPressed({5, ::NONE});
}

void MainWindow::on_elevatorButton6_clicked()
{
    onButtonPressed({6, ::NONE});
}

void MainWindow::on_elevatorButton7_clicked()
{
    onButtonPressed({7, ::NONE});
}

void MainWindow::on_elevatorButton8_clicked()
{
    onButtonPressed({8, ::NONE});
}

void MainWindow::on_elevatorButton9_clicked()
{
    onButtonPressed({9, ::NONE});
}

void MainWindow::on_elevatorButton10_clicked()
{
    onButtonPressed({10, ::NONE});
}

void MainWindow::on_floorButton10Down_clicked()
{
    onButtonPressed({10, ::DOWN});
}

void MainWindow::on_floorButton9Down_clicked()
{
    onButtonPressed({9, ::DOWN});
}

void MainWindow::on_floorButton8Down_clicked()
{
    onButtonPressed({8, ::DOWN});
}

void MainWindow::on_floorButton7Down_clicked()
{
    onButtonPressed({7, ::DOWN});
}

void MainWindow::on_floorButton6Down_clicked()
{
    onButtonPressed({6, ::DOWN});
}

void MainWindow::on_floorButton5Down_clicked()
{
    onButtonPressed({5, ::DOWN});
}

void MainWindow::on_floorButton4Down_clicked()
{
    onButtonPressed({4, ::DOWN});
}

void MainWindow::on_floorButton3Down_clicked()
{
    onButtonPressed({3, ::DOWN});
}

void MainWindow::on_floorButton2Down_clicked()
{
    onButtonPressed({2, ::DOWN});
}

void MainWindow::on_floorButton9Up_clicked()
{
    onButtonPressed({9, ::UP});
}

void MainWindow::on_floorButton8Up_clicked()
{
    onButtonPressed({8, ::UP});
}

void MainWindow::on_floorButton7Up_clicked()
{
    onButtonPressed({7, ::UP});
}

void MainWindow::on_floorButton6Up_clicked()
{
    onButtonPressed({6, ::UP});
}

void MainWindow::on_floorButton5Up_clicked()
{
    onButtonPressed({5, ::UP});
}

void MainWindow::on_floorButton4Up_clicked()
{
    onButtonPressed({4, ::UP});
}

void MainWindow::on_floorButton3Up_clicked()
{
    onButtonPressed({3, ::UP});
}

void MainWindow::on_floorButton2Up_clicked()
{
    onButtonPressed({2, ::UP});
}

void MainWindow::on_floorButton1Up_clicked()
{
    onButtonPressed({1, ::UP});
}
