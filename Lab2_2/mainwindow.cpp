#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    selection_radius = 25;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush point_brush(Qt::black);
    QBrush selector_brush(QColor(200,200,0,200));
    painter.setBrush(point_brush);

    for(int i = 0; i < points.size(); i++)
    {
        painter.drawEllipse(points[i], 2, 2);
    }
    if(select_point.isNull() != true)
    {
        painter.setBrush(selector_brush);
        painter.drawEllipse(select_point, selection_radius, selection_radius);
        painter.setBrush(point_brush);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()&Qt::LeftButton)
    {
        points.append(event->pos());
    }
    else if(event->button()&Qt::RightButton)
    {
        select_point = event->pos();
        for(int i = 0; i < points.size(); i++)
        {
            int distance_square = points_distance_square(points[i], select_point);
            if(distance_square < selection_radius*selection_radius)
            {
                selected_points_indexes.append(i);
            }
        }
    }
    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()&Qt::RightButton)
    {
        select_point = QPoint();
        selected_points_indexes.clear();
    }
    repaint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::RightButton)
    {
        QPoint dp = event->pos() - select_point;
        select_point = event->pos();
        for(int i = 0; i < points.size(); i++)
        {
            int distance_square = points_distance_square(points[i], select_point);
            if((distance_square < selection_radius*selection_radius) && (selected_points_indexes.indexOf(i) == -1))
            {
                selected_points_indexes.append(i);
            }
        }
        for(int i = 0; i < selected_points_indexes.size(); i++)
        {
            points[selected_points_indexes[i]] += dp;
        }
    }
    repaint();
}

int MainWindow::points_distance_square(QPoint p1, QPoint p2)
{
    int dx = p2.x() - p1.x();
    int dy = p2.y() - p1.y();
    return dx*dx + dy*dy;
}
