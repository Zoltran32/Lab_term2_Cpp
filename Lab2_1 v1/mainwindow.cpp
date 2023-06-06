#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //qDebug("test message");
    QPainter painter(this);
    //QBrush brush(Qt::red);
    QBrush brush(QColor(0,128,128, 50));
    QPen pen(Qt::green, 5);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawLine(0,0,100,100);
    painter.drawLine(x-5,y-5,x+5,y+5);
    painter.drawLine(x-5,y+5,x+5,y-5);
    painter.drawRect(100,100,60,40);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug("click x = %d , y = %d", event->x(), event->y());
    x = event->x();
    y = event->y();
    repaint();
    if(event->modifiers()&Qt::ControlModifier)
        qDebug("click + cntrl");
    if(event->modifiers()&Qt::ShiftModifier)
        qDebug("click + shift");
    if(event->modifiers()&Qt::AltModifier)
        qDebug("click + alt");
}

