#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    count = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //QPoint p1(100, 100), p2(400, 400);
    //painter.drawLine(p1,p2);
    for(int i = 1; i < count; i++)
        painter.drawLine(points[i-1], points[i]);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint position = event->pos();
    points.append(position);
    count++;
    //qDebug("%d", count);
    if(event->modifiers()&Qt::ControlModifier)
    {
        points.clear();
        count = 0;
    }
    if(event->modifiers()&Qt::AltModifier)
    {
        QPoint newpos = event->pos();
        if (count > 2)
            position = points[count-2];
        else
            position = points[points.size()-1];
        QPoint move(newpos.x() - position.x(), newpos.y() - position.y());
        //qDebug("coord of alt pressedmove direction %d, %d", newpos.x(), newpos.y());
        //qDebug("old coords? %d, %d", position.x(), position.y());
        //qDebug("move direction %d, %d", move.x(), move.y());
        for(int i = 0; i < points.size() - 1 ; i++)
        {
            points[i].rx() += move.x();
            points[i].ry() += move.y();
        }
    }
    repaint();
}

#if 0
//Old lab code from void MainWindow::mousePressEvent(QMouseEvent *event)
qDebug("click x = %d , y = %d", event->x(), event->y());
x = event->x();
y = event->y();
if(event->modifiers()&Qt::ControlModifier)
    qDebug("click + cntrl");
if(event->modifiers()&Qt::ShiftModifier)
    qDebug("click + shift");
if(event->modifiers()&Qt::AltModifier)
    qDebug("click + alt");

//Old lab code from void MainWindow::paintEvent(QPaintEvent *event)
//qDebug("test message");
//QBrush brush(Qt::red);
QBrush brush(QColor(0,128,128, 50));
QPen pen(Qt::green, 5);
painter.setBrush(brush);
painter.setPen(pen);
painter.drawLine(0,0,100,100);
painter.drawLine(x-5,y-5,x+5,y+5);
painter.drawLine(x-5,y+5,x+5,y-5);
painter.drawRect(100,100,60,40);
QImage flower(":/new/prefix1/img/flower.jpg");
QImage grass(":/new/prefix1/img/grass16x16.GIF");
QBrush brush2;
brush2.setTextureImage(grass);
painter.setBrush(brush2);
painter.drawRect(contentsRect());
painter.setBrush(brush);
painter.drawImage(QRect(100,100,200,300), flower);
#endif
