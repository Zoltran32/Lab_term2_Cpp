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

    bim.dx = -5;
    bim.dy = -5;
    bim.radius = 32;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    QRect screen = contentsRect();
    if(bim.x-bim.radius <= 0 || bim.x+bim.radius >= screen.width())
        bim.dx *= -1;
    if(bim.y-bim.radius <= 0 || bim.y+bim.radius >= screen.height())
        bim.dy *= -1;
    bim.x += bim.dx;
    bim.y += bim.dy;
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawEllipse(QPoint(bim.x, bim.y), bim.radius, bim.radius);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    bim.x = event->x();
    bim.y = event->y();
    repaint();
}
