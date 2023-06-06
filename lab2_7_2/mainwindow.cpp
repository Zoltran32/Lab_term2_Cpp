#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <string>

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
    QVector<QPoint> tr_points = {QPoint(100,100),QPoint(200,200),QPoint(100,300)};
    QVector<QPoint> tr_points_2= {QPoint(300,125),QPoint(300,325),QPoint(150,175)};
    QPolygon tr(tr_points);
    QPolygon tr2(tr_points_2);
    painter.drawPolygon(tr);
    painter.drawPolygon(tr2);
    QRect e1_r(100,100,400,200);
    QPolygon e1 = getEllipsePolWithRect(e1_r);
    painter.drawRect(e1_r);
    painter.drawPolygon(e1);
    for(int i = 0; i < e1.size(); i++)
        painter.drawEllipse(e1[i],5,5);
    std::string message((tr.intersects(e1) ? "tr1 Intersects e1" : "tr1 Not Intersects e1"));
    painter.drawText(QPoint(50,50), message.c_str());
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

}

QPolygon MainWindow::getEllipsePolWithRect(QRect rect)
{
    int x0 = rect.center().x();
    int y0 = rect.center().y();
    int a = rect.width()/2;
    int b = rect.height()/2;
    int offset = a/8;
    //Too many copy-paste
    QVector<QPoint> e_points;
    for(int i = 0; i < 8; i++)
    {
        int x = x0 - a + offset*i;
        int y = y0 - b*sqrt(a*a -(x-x0)*(x-x0))/a;
        e_points.append(QPoint(x,y));
    }
    for(int i = 0; i < 8; i++)
    {
        int x = x0 + offset*i;
        int y = y0 - b*sqrt(a*a -(x-x0)*(x-x0))/a;
        e_points.append(QPoint(x,y));
    }
    for(int i = 0; i < 8; i++)
    {
        int x = x0 + a - offset*i;
        int y = y0 + b*sqrt(a*a -(x-x0)*(x-x0))/a;
        e_points.append(QPoint(x,y));
    }
    for(int i = 0; i < 8; i++)
    {
        int x = x0 - offset*i;
        int y = y0 + b*sqrt(a*a -(x-x0)*(x-x0))/a;
        e_points.append(QPoint(x,y));
    }
    QPolygon ell_pol(e_points);
    return ell_pol;
}

