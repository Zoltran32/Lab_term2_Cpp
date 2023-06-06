#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QPainter>

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

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint click_pos = event->pos();
    if(!tree.isValid())
    {
        QPoint p = getNodePointClosestToPoint(click_pos);
        qDebug("%d %d", p.x(), p.y());
    }
    repaint();
}

QPoint MainWindow::getNodePointClosestToPoint(QPoint point)
{
    //I don't like this
    QPoint node_point_tl(point.x()/cell_size, point.y()/cell_size);
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
    switch(index)
    {
        case 1:
            return cell.topRight();
        case 2:
            return cell.bottomRight();
        case 3:
            return cell.bottomLeft();
        default:
            return cell.topLeft();
    }
    return node_point_tl;
}
