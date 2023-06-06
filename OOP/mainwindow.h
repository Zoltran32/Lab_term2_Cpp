#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ball.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void update();

private slots:
    void clearScreen();
    void showControlsHelp();
    void handleBallAccelerationButton();
    void handleBallFrictionButton();

private:
    Ui::MainWindow *ui;

    Ball ball;
    QRect spawn_area;
    QRect target;
    QRect ui_area;
    QRect screen_area;
    QVector<Ball> balls;

    void createUiWidgets();

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
