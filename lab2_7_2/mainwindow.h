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
    QPolygon getEllipsePolWithRect(QRect rectangle);
};
#endif // MAINWINDOW_H
