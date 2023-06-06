#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cell_size = 50;
    origin = QPoint(100,100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush black_brush(Qt::black);
    QBrush white_brush(Qt::white);
    r0 = QRect(origin, QSize(cell_size, cell_size));
    painter.drawRect(r0);
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            QRect r1 = r0.translated(cell_size*i, cell_size*j);
            painter.setBrush((i+j)%2==0 ? white_brush : black_brush);
            painter.drawRect(r1);
        }
    }
    QPoint text_position(origin.x()-10,origin.y()+cell_size/2);
    for(int i = 0; i < 8; i++)
    {
        std::string s = std::to_string(8-i);
        painter.drawText((text_position + QPoint(0, cell_size*i)), s.c_str());
    }
    for(int i = 0; i < 8; i++)
    {
        QChar c = 'A'+i;
        QString label(c);
        painter.drawText((text_position + QPoint(10+cell_size/2+cell_size*i, cell_size*8 - 10)), label);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QRect r(origin, QSize(cell_size*8, cell_size*8));
    QPoint click_position = event->pos();
    if(r.contains(click_position))
    {
        int row = 8 - (click_position.y() - origin.y())/cell_size;
        QChar coll ='A' + (click_position.x() - origin.x())/cell_size;
        qDebug("%c %d", coll, row);
    }
    repaint();
}
