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
    //lets belive that 50x50 grid is big enought
    for(int i = 0; i < 50; i++)
    {
        node_grid_values.append(QVector<int>());
        for(int j = 0; j < 50; j++)
        {
            node_grid_values[i].append(0);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //-------------- Grid lines --------------------------
    QRect screen = contentsRect();
    for(int i = 0; i < screen.width(); i += cell_size)
        painter.drawLine(QPoint(i,0), QPoint(i,screen.height()));
    for(int i = 0; i < screen.height(); i += cell_size)
        painter.drawLine(QPoint(0,i), QPoint(screen.width(), i));

    //--------------- Tree, ant, fly ---------------------------------
    painter.setBrush(QBrush(Qt::green));
    painter.drawEllipse(tree);
    painter.setBrush(QBrush(Qt::red));
    painter.drawRect(ant);
    painter.setBrush(QBrush(Qt::cyan));
    painter.drawRect(fly);

    //---------------- Info ----------------------------------------------
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
    for(int i = 0; i < test_pos.size(); i++)
        painter.drawRect(QRect(test_pos[i]-QPoint(5,5), QSize(10,10)));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint click_pos = event->pos();
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
    else if(path.size() == 0)
    {
        calculateStupidPath();
        calculateGridValues();
    }
    repaint();
}

void MainWindow::calculateStupidPath()
{
    QPoint ant_pos = ant.center();
    QPoint fly_pos = fly.center();
    recount:
    //For some reason tree.center(), ant.center(), fly.center() can be (100, 99) or (99, 100) or (99,99)
    while(abs(ant_pos.x() - fly_pos.x()) > 5) //Handler
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
    while(abs(ant_pos.y() - fly_pos.y()) > 5)  //Handler
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
    if(abs(ant_pos.x() - fly_pos.x()) > 5)  //Handler
        goto recount;
}

void MainWindow::calculateGridValues() //Not done yet
{
    //----------------------- calculate obstacle value -----------------------------
    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            QPoint node_point(cell_size*j, cell_size*i);
            if(tree.contains(node_point))
                node_grid_values[i][j] = -1;
        }
    }

    // ----------------- get ant and fly nodes ---------------------------------------
    QPoint ant_center = ant.center();
    int errX = ant.center().x() % 10;
    int errY = ant.center().y() % 10;
    ant_center += QPoint(10-errX, 10-errY);
    int ant_x = ant_center.x() / cell_size;
    int ant_y = ant_center.y() / cell_size;
    QPoint fly_center = fly.center();
    errX = fly.center().x() % 10;
    errY = fly.center().y() % 10;
    ant_center += QPoint(10-errX, 10-errY);
    int fly_x = fly_center.x() / cell_size;
    int fly_y = fly_center.y() / cell_size;

    int i = 1;
    while(i < 6)
    {
        if((ant_x - i)>0 && (ant_y)>0)
        {
            if(node_grid_values[ant_x][ant_y-i] == 0)
                node_grid_values[ant_x][ant_y-i]++;
            if(node_grid_values[ant_x+i][ant_y] == 0)
               node_grid_values[ant_x+i][ant_y]++;
            if(node_grid_values[ant_x][ant_y+i] == 0)
                node_grid_values[ant_x][ant_y+i]++;
            if(node_grid_values[ant_x-i][ant_y] == 0)
                node_grid_values[ant_x-i][ant_y]++;
        }
        i++;
    }
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

//--------------------------------------------------------------------
/*
//Old wave visualisation
QPoint ant_pos = ant.center();
for(int i = 1; i <= path.size(); i++) //FIXME
{
    QPoint n = QPoint(0, -cell_size*i) + ant_pos;
    QPoint e = QPoint(cell_size*i, 0) + ant_pos;
    QPoint s = QPoint(0, cell_size*i) + ant_pos;
    QPoint w = QPoint(-cell_size*i, 0) + ant_pos;
    painter.drawLine(n,w);
    painter.drawLine(n,e);
    painter.drawLine(s,w);
    painter.drawLine(s,e);
    std::string path_label = std::to_string(i);
    painter.drawText(n, path_label.c_str());
    painter.drawText(e, path_label.c_str());
    painter.drawText(s, path_label.c_str());
    painter.drawText(w, path_label.c_str());
    if(i > 1)
    {
        QPoint l = n;
        while(l != e)
        {
            l = l + QPoint(cell_size, cell_size);
            painter.drawText(l, path_label.c_str());
        }
        while(l != s)
        {
            l = l + QPoint(-cell_size, cell_size);
            painter.drawText(l, path_label.c_str());
        }
        while(l != w)
        {
            l = l + QPoint(-cell_size, -cell_size);
            painter.drawText(l, path_label.c_str());
        }
        while(l != n)
        {
            l = l + QPoint(cell_size, -cell_size);
            painter.drawText(l, path_label.c_str());
        }
    }
}
*/
//--------------------------------------------------------------------
