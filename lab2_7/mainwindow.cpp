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
    QRect s = contentsRect();
    pool = QRect(QPoint(s.width()/3,s.height()/3), QSize(s.width()/3,s.height()/3));
    generateRoundFlowers(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect screen = contentsRect();
    painter.setBrush(QBrush(grass));
    painter.drawRect(screen);
    painter.setBrush(QBrush(water));
    painter.drawRect(pool);
    painter.setBrush(QBrush(flower));
    painter.drawRects(flowers_rects);
    painter.setBrush(round_flower);
    for(int i = 0; i < round_flowers_rects.size(); i++)
        painter.drawEllipse(round_flowers_rects[i]);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint click_point = event->pos();
    QRect f(click_point, pool.size()/10);
    if(rectCanBePlaced(f))
    {
        if(event->modifiers() & Qt::ShiftModifier)
        {
            f.setSize(QSize(f.height(), f.height()));
            round_flowers_rects.append(f);
        }
        else
        {
            flowers_rects.append(f);
        }
    }
    repaint();
}

void MainWindow::generateRoundFlowers(int rounds_ammount)
{
    QPoint pos(5,5);
    for(int i = 0; i < rounds_ammount; i++)
    {
        QRect r(pos, QSize(25, 25)); //radius applied here
        if(rectCanBePlaced(r))
            round_flowers_rects.append(r);
        pos += QPoint(10*i, 0);
        if(pos.x() > contentsRect().width())
            pos = QPoint(5, pos.y()+10*i);
    }
}

bool MainWindow::rectCanBePlaced(QRect f)
{
    QPoint offset(pool.size().width()/20 - 1, pool.size().height()/20 - 1);
    QRect pool_placable(pool.topLeft() + offset, pool.bottomRight() - offset);
    if(pool_placable.intersects(f))
        return false;
    for(int i = 0; i < flowers_rects.size(); i++)
        if(flowers_rects[i].intersects(f))
            return  false;
    for(int i = 0; i < round_flowers_rects.size(); i++)
        if(round_flowers_rects[i].intersects(f))
            return false;
    return true;
}
