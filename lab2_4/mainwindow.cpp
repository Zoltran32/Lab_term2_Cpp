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
    //painter.drawLine(QLine(QPoint(200,100), QPoint(100,200)));
    //painter.drawLine(QLine(100,100,200,200));
    painter.drawLine(line);
    QPoint vector = line.p2() - line.p1();
    painter.drawLine(QPoint(), line.p2() - line.p1());
    QLine normal1(line.p2(), line.p2() - QPoint(-vector.y(),vector.x()));
    QLine normal2(line.p2(), line.p2() - QPoint(vector.y(), -vector.x()));
    painter.drawLine(normal1);
    painter.drawLine(normal2);
    int dp1 = line.p1().dotProduct(line.p2(), normal1.p2());
    //int dp2 = line.p1().dotProduct(line.p2(), normal2.p2());
    roster1 = QLineF(line.p2(), line.p2()+vector);
    roster1.setAngle(QLineF(line).angle() + 15);
    roster2 = QLineF(line.p2(), line.p2()+vector);
    roster2.setAngle(QLineF(line).angle() - 15);
    QLineF roster3(roster1.p2(), roster2.p2());
    painter.drawLine(roster1);
    painter.drawLine(roster2);
    painter.drawLine(roster3);
    QVector<QPointF> roster_points = {line.p2(), roster1.p2(), roster2.p2()};
    QPolygonF roster(roster_points);
    painter.setBrush(QBrush(Qt::yellow));
    painter.drawPolygon(roster);
    painter.setBrush(QBrush(Qt::red));
    if(dp1 > 0)
    {
        painter.drawEllipse(normal1.p2(), 5,5);
        painter.setBrush(QBrush(Qt::green));
        painter.drawEllipse(normal2.p2(), 5,5);
    }
    else
    {
        painter.drawEllipse(normal2.p2(), 5,5);
        painter.setBrush(QBrush(Qt::green));
        painter.drawEllipse(normal1.p2(), 5,5);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(!point.isNull() && (event->modifiers() != Qt::ControlModifier))
    {
        line.setP1(point);
        line.setP2(event->pos());
    }
    point = event->pos();
    if(event->modifiers() & Qt::ControlModifier)
    {
        a_point = event->pos();
        int flag_line = getPointPosition(a_point, line);
        QPoint vector = line.p2() - line.p1();
        QLine normal1(line.p1(), line.p1() - QPoint(-vector.y(), vector.x()));
        QLine normal2(line.p2(), line.p2() - QPoint(-vector.y(), vector.x()));
        int flag_n1 = getPointPosition(a_point, normal1);
        int flag_n2 = getPointPosition(a_point, normal2);
        int flag_r1 = getPointPosition(a_point, roster1.toLine());
        int flag_r2 = getPointPosition(a_point, roster2.toLine());
        if(flag_r1 == RIGHT && flag_r2 == LEFT)
            qDebug("VISIBLE");
        if(flag_n1 == LEFT)
            qDebug("BACK");
        else if(flag_n2 == RIGHT)
            qDebug("FRONT");
        else
        {
            qDebug("SIDE");
            if(flag_line == LEFT)
                qDebug("LEFT");
            else
                qDebug("RIGHT");
        }
    }
    repaint();
}

int MainWindow::getPointPosition(QPoint point, QLine line)
{
    QPoint a = line.p2() - line.p1();
    QPoint b = point - line.p1();
    int number = a.x()*b.y() - a.y()*b.x();
    if(number > 0)
        return RIGHT;
    if(number < 0)
        return LEFT;
    return UNDEFINED;
}
