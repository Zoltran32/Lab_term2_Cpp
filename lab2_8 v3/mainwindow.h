#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void calculateStupidPath();
    void calculateGridValues();
    QPoint getNodePointClosestToPoint(QPoint point);

    int cell_size;

    QRect ant;
    QRect fly;
    QRect tree;
    QVector<QPoint> path;
    QVector<QVector<int>> node_grid_values;

    QVector<QPoint> test_pos;
};
#endif // MAINWINDOW_H
