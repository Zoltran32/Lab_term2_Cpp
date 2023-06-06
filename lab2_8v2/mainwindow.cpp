#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QPainter>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cell_size = 50;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect screen = contentsRect();
    for(int i = 0; i < screen.width(); i += cell_size)
        painter.drawLine(QPoint(i,0), QPoint(i,screen.height()));
    for(int i = 0; i < screen.height(); i += cell_size)
        painter.drawLine(QPoint(0,i), QPoint(screen.width(), i));
    painter.setBrush(QBrush(Qt::green));
    painter.drawEllipse(tree);
    painter.setBrush(QBrush(Qt::red));
    painter.drawRect(ant);
    painter.setBrush(QBrush(Qt::cyan));
    painter.drawRect(fly);
    painter.setBrush(QBrush(Qt::yellow));
    for(int i = 0; i < path.size(); i++)
        painter.drawRect(QRect(path[i]-QPoint(5,5), QSize(10,10)));
    painter.setBrush(QBrush());
    std::string label = "Tree";
    painter.drawText(tree.center(), label.c_str());
    label = "Ant";
    painter.drawText(ant.center(), label.c_str());
    label = "Fly";
    painter.drawText(fly.center(), label.c_str());

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint click_pos = event->pos();
    //DRY violation
    QPoint p = getNodePointClosestToPoint(click_pos);
    if(!tree.isValid())
    {
        tree = QRect(p - QPoint(125,125), QSize(250,250));
    }
    else if(!ant.isValid())
    {
        QRect ant_tmp(p - QPoint(30,30), QSize(60,60));
        if(!ant_tmp.intersects(tree))
            ant = ant_tmp;
    }
    else if(!fly.isValid())
    {
        QRect fly_tmp(p - QPoint(45,45), QSize(90,90));
        if((!fly_tmp.intersects(tree)) && (!fly_tmp.intersects(ant)))
            fly = fly_tmp;
    }
    else
    {
        calculateStupidPath();
    }
    repaint();
}

void MainWindow::calculateStupidPath()
{
    QPoint ant_pos = ant.center();
    QPoint fly_pos = fly.center();
    recount:
    while(abs(ant_pos.x() - fly_pos.x()) > 5)
    {
        int dir_x = 1;
        if(ant_pos.x() > fly_pos.x())
            dir_x = -1;
        ant_pos = QPoint(ant_pos.x()+cell_size*dir_x, ant_pos.y());
        if(!tree.contains(ant_pos))
            path.append(ant_pos);
        else
        {
            int dir_y = 1;
            if(tree.contains(ant_pos + QPoint(0,cell_size)))
                dir_y= -1;
            ant_pos = QPoint(ant_pos.x()-cell_size*dir_x, ant_pos.y() + cell_size*dir_y);
            path.append(ant_pos);
        }
    }
    while(abs(ant_pos.y() - fly_pos.y()) > 5)
    {
        int dir_y = 1;
        if(ant_pos.y() > fly_pos.y())
            dir_y = -1;
        ant_pos = QPoint(ant_pos.x(), ant_pos.y()+cell_size*dir_y);
        if(!tree.contains(ant_pos))
            path.append(ant_pos);
        else
        {
            int dir_x = 1;
            if(tree.contains(ant_pos + QPoint(cell_size, 0)))
                dir_x= -1;
            ant_pos = QPoint(ant_pos.x() + cell_size*dir_x, ant_pos.y()-cell_size*dir_y);
            path.append(ant_pos);
        }
    }
    if(abs(ant_pos.x() - fly_pos.x()) > 5)
        goto recount;
}

QPoint MainWindow::getNodePointClosestToPoint(QPoint point)
{
    //I don't like this
    QPoint node_point_tl((point.x()/cell_size)*cell_size, (point.y()/cell_size)*cell_size);
    QRect cell(node_point_tl, QSize(cell_size, cell_size));
    QVector<QVector2D> vectors;
    vectors.append(QVector2D(point - cell.topLeft()));
    vectors.append(QVector2D(cell.topRight() - point));
    vectors.append(QVector2D(cell.bottomRight() - point));
    vectors.append(QVector2D(cell.bottomLeft() - point));
    int minLength = 1000000;
    int index = -1;
    for(int i = 0; i < vectors.size(); i++)
    {
        if(minLength > vectors[i].lengthSquared())
        {
            minLength = vectors[i].lengthSquared();
            index = i;
        }
    }
    QPoint node_point;
    switch(index)
    {
        case 1:
            node_point = cell.topRight();
            break;
        case 2:
            node_point = cell.bottomRight();
            break;
        case 3:
            node_point = cell.bottomLeft();
            break;
        default:
            node_point = cell.topLeft();
            break;
    }
    return node_point;
}
