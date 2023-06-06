#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QMouseEvent>

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
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::black));
    for(int i = 0; i < points.size(); i++)
        painter.drawEllipse(points[i], 4,4);
    if(points.size()>3)
    {
        painter.drawLine(points[0], points[1]);
        painter.drawLine(points[0], points[2]);
        painter.drawLine(points[1], points[3]);
        painter.drawLine(points[2], points[3]);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(points.size()<3)
        points.append(event->pos());
    else if(points.size() < 4)
    {
        int minx = 1000000;
        int pointind = 0;
        for(int i = 0; i < points.size(); i++)
        {
            if(minx > points[i].x())
            {
                minx = points[i].x();
                pointind = i;
            }
        }
        QPoint tmp = points[0];
        points[0] = points[pointind];
        points[pointind] = tmp;
        QPoint forthpoint = points[0] + (points[1] - points[0]) + (points[2]-points[0]);
        points.append(forthpoint);
    }
    repaint();
}
