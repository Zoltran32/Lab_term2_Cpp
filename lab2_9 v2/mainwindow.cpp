#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);

    bim.setDx(-5);
    bim.setDy(-5);
    bim.setRadius(32);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    QRect screen = contentsRect();
    if(bim.getX()-bim.getRadius() <= 0 || bim.getX()+bim.getRadius() >= screen.width())
        bim.setDx(-1*bim.getDx());
    if(bim.getY()-bim.getRadius() <= 0 || bim.getY()+bim.getRadius() >= screen.height())
        bim.setDy(-1*bim.getDy());
    bim.setX(bim.getX() + bim.getDx());
    bim.setY(bim.getY() + bim.getDy());

    repaint();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    bim.draw(&painter);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    bim.setX(event->x());
    bim.setY(event->y());
    repaint();
}
