#include "MainWindow.hpp"

#include <vector>
#include <unordered_map>
#include <QColorDialog>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QImage>
#include <QMessageBox>
#include <QMouseEvent>

#include "CreatorManagerCreator.h"
#include "LoadManagerCreator.h"
#include "LoadSceneCommand.h"
#include "ManagerExceptions.h"
#include "MoveCommand.h"
#include "RemoveSceneObjectCommand.h"
#include "RenderManagerCreator.h"
#include "RenderSceneCommand.h"
#include "RotateCommand.h"
#include "ScaleCommand.h"
#include "SceneElementsManagerCreator.h"
#include "SceneManagerCreator.h"
#include "SelectManagerCreator.h"
#include "SelectSceneObjectCommand.h"
#include "SetActiveCameraCommand.h"
#include "TransformManagerCreator.h"
#include "UnselectSceneObjectCommand.h"
#include "ui_MainWindow.h"
#include "transformationConstants.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), tableViewModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    scene = std::make_shared<QGraphicsScene>(this);
    scene->setBackgroundBrush(QBrush(QColor(0xFFFFFF)));

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene.get());

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setModel(tableViewModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::onSelectionRowChanged);

    ui->cameraComboBox->addItem(QString("-1"));
    connect(ui->cameraComboBox, &QComboBox::currentTextChanged,
            this, &MainWindow::onComboBoxTextChange);

    initFacade();
}

void MainWindow::on_loadSceneButton_clicked()
{
    qDebug() << ui->graphicsView->size();
    auto filename = QFileDialog::getOpenFileName(
        nullptr, "Путь до файла со сценой", nullptr,
        "Scene file (*.txt *.csv)");

    if (!filename.isEmpty())
    {
        clearTableView();
        clearComboBox();
        auto loadCommand = std::make_shared<LoadSceneCommand>(filename.toStdString(), [&](size_t id, objType type) {
            addRowToListView(id, type);
            if (type == CAMERA)
                addToComboBox(id);
        });
        facade->execute(loadCommand);

        renderScene();
    }
}

void MainWindow::on_zLeftMoveButton_clicked()
{
    Matrix<double> transformationMatrix{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, -moveStep, 1}
    };

    auto cmd = std::make_shared<MoveCommand>(transformationMatrix);
    facade->execute(cmd);

    renderScene();
}

void MainWindow::on_zRightMoveButton_clicked()
{
    Matrix<double> transformationMatrix{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, moveStep, 1}
    };

    auto cmd = std::make_shared<MoveCommand>(transformationMatrix);
    facade->execute(cmd);

    renderScene();
}

void MainWindow::on_yLeftMoveButton_clicked()
{
    Matrix<double> transformationMatrix{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, moveStep, 0, 1}
    };

    auto cmd = std::make_shared<MoveCommand>(transformationMatrix);
    facade->execute(cmd);

    renderScene();
}

void MainWindow::on_zLeftRotateButton_clicked()
{
    auto cos_ = std::cos(rotationStep);
    auto sin_ = std::sin(rotationStep);
    Matrix<double> transformationMatrix{
        {cos_, -sin_, 0, 0},
        {sin_, cos_, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    auto cmd = std::make_shared<RotateCommand>(transformationMatrix);
    facade->execute(cmd);

    renderScene();
}

void MainWindow::on_zRightRotateButton_clicked()
{
    auto cos_ = std::cos(-rotationStep);
    auto sin_ = std::sin(-rotationStep);
    Matrix<double> transformationMatrix{
        {cos_, -sin_, 0, 0},
        {sin_, cos_, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    auto cmd = std::make_shared<RotateCommand>(transformationMatrix);
    facade->execute(cmd);

    renderScene();
}

void MainWindow::on_removeButton_clicked()
{
    auto selected = ui->tableView->selectionModel()->selectedIndexes();
    std::vector<size_t> ids;
    for (const auto &index : selected)
    {
        if (index.column() != 0)
            continue;

        QString idStr = index.data().toString();
        size_t id = idStr.toUInt();

        ids.push_back(id);

        auto cmd = std::make_shared<RemoveSceneObjectCommand>(id);
        facade->execute(cmd);
    }

    for (const auto &id : ids)
    {
        removeRowByIndex(id);
        removeFromComboBox(id);
    }

    renderScene();
}

void MainWindow::clearTableView()
{
    if (tableViewModel)
        tableViewModel->clear();
}

void MainWindow::onSelectionRowChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    for (const QModelIndex &index : selected.indexes())
    {
        if (index.column() != 0)
            continue;

        QString idStr = index.data().toString();
        size_t id = idStr.toUInt();

        auto cmd = std::make_shared<SelectSceneObjectCommand>(id);
        facade->execute(cmd);
    }

    for (const QModelIndex &index : deselected.indexes())
    {
        if (index.column() != 0)
            continue;

        QString idStr = index.data().toString();
        size_t id = idStr.toUInt();

        auto cmd = std::make_shared<UnselectSceneObjectCommand>(id);
        facade->execute(cmd);
    }
}

void MainWindow::addRowToListView(size_t id, objType type)
{
    std::unordered_map<objType, std::string> mp = {
        {MODEL, "Model"},
        {CAMERA, "Camera"},
    };

    QList<QStandardItem *> row;
    row << new QStandardItem(QString::number(id));
    row << new QStandardItem(QString::fromStdString(mp[type]));
    tableViewModel->appendRow(row);

    tableViewModel->setHorizontalHeaderLabels({"ID", "Тип"});
}

void MainWindow::addToComboBox(size_t id)
{
    ui->cameraComboBox->addItem(QString::number(id));
}

bool MainWindow::removeFromComboBox(size_t id)
{
    QString targetText = QString::number(id);
    int index = ui->cameraComboBox->findText(targetText);

    if (index == -1)
        return false;

    ui->cameraComboBox->removeItem(index);
    return true;
}

void MainWindow::onComboBoxTextChange(const QString &text)
{
    size_t id = text.toUInt();

    auto cmd = std::make_shared<SetActiveCameraCommand>(id);
    facade->execute(cmd);

    renderScene();
}

bool MainWindow::clearComboBox()
{
    ui->cameraComboBox->clear();
    ui->cameraComboBox->addItem(QString("-1"));
    return true;
}

bool MainWindow::removeRowByIndex(size_t id)
{
    QAbstractItemModel *model = ui->tableView->model();

    for (int row = 0; row < model->rowCount(); ++row)
    {
        QModelIndex index = model->index(row, 0);
        bool ok;
        int currentId = model->data(index).toInt(&ok);

        if (ok && currentId == id)
        {
            return model->removeRow(row);
        }
    }

    tableViewModel->setHorizontalHeaderLabels({"ID", "Тип"});

    return false;
}

void MainWindow::on_yLeftRotateButton_clicked()
{
    auto cos_ = std::cos(rotationStep);
    auto sin_ = std::sin(rotationStep);
    Matrix<double> transformationMatrix{
        {cos_, 0, sin_, 0},
        {0, 1, 0, 0},
        {-sin_, 0, cos_, 0},
        {0, 0, 0, 1}
    };

    auto cmd = std::make_shared<RotateCommand>(transformationMatrix);
    facade->execute(cmd);

    renderScene();
}

void MainWindow::on_yRightRotateButton_clicked()
{
    auto cos_ = std::cos(-rotationStep);
    auto sin_ = std::sin(-rotationStep);
    Matrix<double> transformationMatrix{
        {cos_, 0, sin_, 0},
        {0, 1, 0, 0},
        {-sin_, 0, cos_, 0},
        {0, 0, 0, 1}
    };

    auto cmd = std::make_shared<RotateCommand>(transformationMatrix);
    facade->execute(cmd);

    renderScene();
}

void MainWindow::on_xLeftRotateButton_clicked()
{
    auto cos_ = std::cos(rotationStep);
    auto sin_ = std::sin(rotationStep);
    Matrix<double> transformationMatrix{
        {1, 0, 0, 0},
        {0, cos_, -sin_, 0},
        {0, sin_, cos_, 0},
        {0, 0, 0, 1}
    };

    auto cmd = std::make_shared<RotateCommand>(transformationMatrix);
    facade->execute(cmd);

    renderScene();
}

void MainWindow::on_xRightRotateButton_clicked()
{
    auto cos_ = std::cos(-rotationStep);
    auto sin_ = std::sin(-rotationStep);
    Matrix<double> transformationMatrix{
        {1, 0, 0, 0},
        {0, cos_, -sin_, 0},
        {0, sin_, cos_, 0},
        {0, 0, 0, 1}
    };

    auto cmd = std::make_shared<RotateCommand>(transformationMatrix);
    facade->execute(cmd);

    renderScene();
}

void MainWindow::on_scaleDownButton_clicked()
{
    auto curScaleStep = 1.0 / scaleStep;
    Matrix<double> transformationMatrix{
        {curScaleStep, 0, 0, 0},
        {0, curScaleStep, 0, 0},
        {0, 0, curScaleStep, 0},
        {0, 0, 0, 1}
    };

    auto cmd = std::make_shared<ScaleCommand>(transformationMatrix);
    facade->execute(cmd);

    renderScene();
}

void MainWindow::on_scaleUpButton_clicked()
{
    Matrix<double> transformationMatrix{
        {scaleStep, 0, 0, 0},
        {0, scaleStep, 0, 0},
        {0, 0, scaleStep, 0},
        {0, 0, 0, 1}
    };

    auto cmd = std::make_shared<ScaleCommand>(transformationMatrix);
    facade->execute(cmd);

    renderScene();
}

void MainWindow::on_yRightMoveButton_clicked()
{
    Matrix<double> transformationMatrix{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, -moveStep, 0, 1}
    };

    auto cmd = std::make_shared<MoveCommand>(transformationMatrix);
    facade->execute(cmd);

    renderScene();
}

void MainWindow::on_xLeftMoveButton_clicked()
{
    Matrix<double> transformationMatrix{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {-moveStep, 0, 0, 1}
    };

    auto cmd = std::make_shared<MoveCommand>(transformationMatrix);
    facade->execute(cmd);

    renderScene();
}

void MainWindow::on_xRightMoveButton_clicked()
{
    Matrix<double> transformationMatrix{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {moveStep, 0, 0, 1}
    };

    auto cmd = std::make_shared<MoveCommand>(transformationMatrix);
    facade->execute(cmd);

    renderScene();
}

void MainWindow::throwMessageBox(const char *text)
{
    auto box = QMessageBox();
    box.setText(QString::fromStdString(text));
    box.exec();
}

void MainWindow::initFacade()
{
    auto solution = std::make_shared<ManagerSolution>();

    solution->registrate(LOAD, &CreatorManagerCreator::createCreator<LoadManagerCreator>);
    solution->registrate(SCENE_ELEMENTS, &CreatorManagerCreator::createCreator<SceneElementsManagerCreator>);
    solution->registrate(RENDER, &CreatorManagerCreator::createCreator<RenderManagerCreator>);
    solution->registrate(SCENE, &CreatorManagerCreator::createCreator<SceneManagerCreator>);
    solution->registrate(SELECT, &CreatorManagerCreator::createCreator<SelectManagerCreator>);
    solution->registrate(TRANSFORM, &CreatorManagerCreator::createCreator<TransformManagerCreator>);

    facade = std::make_shared<Facade>(scene, solution);
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    scene->setSceneRect(QRectF(QPointF(0, 0), ui->graphicsView->size()));
}

void MainWindow::renderScene() const
{
    ui->graphicsView->scene()->clear();
    try
    {
        facade->execute(std::make_shared<RenderSceneCommand>());
    }
    catch (const NoCameraSetException &)
    {
        std::cout << "WARN: Camera is not set\n";
    }
}

MainWindow::~MainWindow()
{
    scene.reset();

    delete tableViewModel;
    delete ui;
}
