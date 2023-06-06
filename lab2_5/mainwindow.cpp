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
    QPainter painter(this);
    painter.drawRect(rectangle);
    if(!rectangle.isNull())
    {
        painter.drawEllipse(rectangle.topLeft() - QPoint(20,20), 5, 5);
        painter.drawLine(rectangle.topLeft(), rectangle.topLeft() - QPoint(20,20));
        painter.drawEllipse(rectangle.topRight() - QPoint(-20,20), 5, 5);
        painter.drawLine(rectangle.topRight(), rectangle.topRight() - QPoint(-20,20));
        painter.drawEllipse(rectangle.bottomLeft() - QPoint(20,-20), 5, 5);
        painter.drawLine(rectangle.bottomLeft(), rectangle.bottomLeft() - QPoint(20,-20));
        painter.drawEllipse(rectangle.bottomRight() - QPoint(-20,-20), 5, 5);
        painter.drawLine(rectangle.bottomRight(), rectangle.bottomRight() - QPoint(-20,-20));
    }
    painter.setBrush(Qt::BrushStyle(Qt::BDiagPattern));
    painter.drawRect(rectangle_pale);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    click_position = event->pos();
    if(rectangle.isNull())
    {
        rectangle = QRect(click_position - QPoint(60,40), QSize(120,80));
    }
    else
    {
        QPoint move = click_position - rectangle.center();
        rectangle_pale = rectangle.translated(move);
        if(rectangle_pale.left() > rectangle.right())
        {
            rectangle.setRight(rectangle.right() + move.x()/10);
            rectangle.setLeft(rectangle.left() + move.x()/10);
        }
        if(rectangle_pale.right() < rectangle.left())
        {
            rectangle.setLeft(rectangle.left() + move.x()/10);
            rectangle.setRight(rectangle.right() + move.x()/10);
        }
        if(rectangle_pale.top() > rectangle.bottom())
        {
            rectangle.setBottom(rectangle.bottom() + move.y()/10);
            rectangle.setTop(rectangle.top() + move.y()/10);
        }
        if(rectangle_pale.bottom() < rectangle.top())
        {
            rectangle.setTop(rectangle.top() + move.y()/10);
            rectangle.setBottom(rectangle.bottom() + move.y()/10);
        }
    }
    repaint();
}

/*
    QRect rect1(100,100,150,150);
    QRect rect2(QPoint(255,255), QSize(150,150));
    QRect rect3(QPoint(410, 410), QPoint(560, 560));
    QRect rect4;
    QRect rect5;
    QRect rect6(410, 100, -1, 0);
    QRect rect7(560, 250, -150, -150);
    rect4.setTop(410);
    rect4.setLeft(100);
    rect4.setSize(QSize(150,150));
    painter.setBrush(QBrush(Qt::red));
    painter.drawRect(rect1);
    painter.setBrush(QBrush(Qt::blue));
    painter.drawRect(rect2);
    painter.setBrush(QBrush(Qt::green));
    painter.drawRect(rect3);
    painter.setBrush(QBrush(Qt::yellow));
    painter.drawRect(rect4);
    if(rect5.isNull())
        qDebug("is NULL");
    if(!rect6.isValid())
        qDebug("is INVAlID");
    if(rect7.isEmpty())
        qDebug("is EMPTY");
    painter.setBrush(Qt::black);
    painter.drawRect(rect7);

    QSize size(120,80);
    QPoint top_left(click_position.x()-size.width()/2, click_position.y()-size.height()/2);
    QRect rectangle(top_left, size);
    painter.setBrush(QBrush(Qt::red));
    painter.drawRect(rectangle);
    painter.setBrush(QBrush());
    painter.drawEllipse(rectangle.topLeft() - QPoint(20,20), 5, 5);
    painter.drawLine(rectangle.topLeft(), rectangle.topLeft() - QPoint(20,20));
    painter.drawEllipse(rectangle.topRight() - QPoint(-20,20), 5, 5);
    painter.drawLine(rectangle.topRight(), rectangle.topRight() - QPoint(-20,20));
    painter.drawEllipse(rectangle.bottomLeft() - QPoint(20,-20), 5, 5);
    painter.drawLine(rectangle.bottomLeft(), rectangle.bottomLeft() - QPoint(20,-20));
    painter.drawEllipse(rectangle.bottomRight() - QPoint(-20,-20), 5, 5);
    painter.drawLine(rectangle.bottomRight(), rectangle.bottomRight() - QPoint(-20,-20));

*/
