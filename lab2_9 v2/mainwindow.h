#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ball.h"

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

public slots:
    void update();

private:
    Ui::MainWindow *ui;

    Ball bim;

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
};
#endif // MAINWINDOW_H
