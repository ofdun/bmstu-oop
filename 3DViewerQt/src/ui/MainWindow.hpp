#pragma once

#include "Facade.h"
#include "enums.h"

#include <QItemSelection>
#include <QGraphicsView>
#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE

namespace Ui
{
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_loadSceneButton_clicked();

    void on_xLeftMoveButton_clicked();
    void on_xRightMoveButton_clicked();
    void on_yLeftMoveButton_clicked();
    void on_yRightMoveButton_clicked();
    void on_zLeftMoveButton_clicked();
    void on_zRightMoveButton_clicked();

    void on_scaleUpButton_clicked();
    void on_scaleDownButton_clicked();

    void on_xLeftRotateButton_clicked();
    void on_xRightRotateButton_clicked();
    void on_yLeftRotateButton_clicked();
    void on_yRightRotateButton_clicked();
    void on_zLeftRotateButton_clicked();
    void on_zRightRotateButton_clicked();

    void on_removeButton_clicked();

private:
    void clearTableView();
    void onSelectionRowChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void addRowToListView(size_t id, objType type);
    bool removeRowByIndex(size_t id);

    void addToComboBox(size_t id);
    bool removeFromComboBox(size_t id);
    bool clearComboBox();
    void onComboBoxTextChange(const QString &text);

    void initFacade();
    void throwMessageBox(const char *text);
    void renderScene() const;

    std::shared_ptr<Facade> facade;
    std::shared_ptr<QGraphicsScene> scene;
    Ui::MainWindow *ui = nullptr;
    QStandardItemModel *tableViewModel = nullptr;
};

