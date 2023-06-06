#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum position
{
    LEFT,
    RIGHT,
    UNDEFINED
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QPoint point;
    QPoint a_point;
    QLine line;
    QLineF roster1;
    QLineF roster2;

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    int getPointPosition(QPoint point, QLine line);
};
#endif // MAINWINDOW_H
