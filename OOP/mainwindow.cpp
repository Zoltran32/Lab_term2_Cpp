#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>

#include <QKeyEvent>
#include <QLabel>
#include <QLCDNumber>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int window_width = 900;
    int window_height = 600;
    int offset = 5;

    ui->setupUi(this);
    ui->centralWidget->setFixedSize(QSize(window_width + offset*3, window_height + offset*2));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);

    ui_area = QRect(QPoint(offset,offset), QSize(window_width/3 - offset, window_height - offset));
    screen_area = QRect(QPoint(window_width/3 + offset, offset), QSize(2*window_width/3 - offset, window_height - offset));

    createUiWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    int balls_ammount = balls.size();
    for(int i = 0; i < balls_ammount; i++)
    {
        if(balls[i].intersectsBall(ball))
        {
            balls[i].setDx(5*ball.dx());
            balls[i].setDy(5*ball.dy());
        }
        else if(!screen_area.contains(QPoint(static_cast<int>(balls[i].x()), static_cast<int>(balls[i].y()))))
        {
            balls[i].setDx(-5*balls[i].dx());
            balls[i].setDy(-5*balls[i].dy());
        }
        else
        {
           balls[i].applyFriction();
        }
        balls[i].move();
    }
    QPoint target_center = target.topLeft() + QPoint(4,4);
    if((ball.x() - target_center.x() < 2 &&
        ball.x() - target_center.x() > -2 &&
        ball.y() - target_center.y() < 2 &&
        ball.y() - target_center.y() > -2) || !screen_area.contains(target_center))
    {
        ball.setDx(0);
        ball.setDy(0);
    }
    ball.move();
    repaint();
}

void MainWindow::clearScreen()
{
    balls.clear();
    ball.setRadius(0.0f);
    target = QRect();
    spawn_area = QRect();
}

void MainWindow::createUiWidgets()
{
    std::string controls_label = "Press F1 to see control keys\n" \
                                 "Press Esc to clear screen";
    QLabel* buttons_label = new QLabel(QString::fromStdString(controls_label), ui->centralWidget);
    buttons_label->setGeometry(25, 25, 250, 50);

    QPushButton* help_button = new QPushButton(QString::fromStdString("Controls help"), ui->centralWidget);
    help_button->setGeometry(25, 100, 250, 50);
    QPushButton* clear_button = new QPushButton(QString::fromStdString("Clear screen"), ui->centralWidget);
    clear_button->setGeometry(25, 175, 250, 50);
    QPushButton* quit_button = new QPushButton(QString::fromStdString("Quit"), ui->centralWidget);
    quit_button->setGeometry(25, 250, 250, 50);

    QPushButton* a_button = new QPushButton(QString::fromStdString("Speed\nup\nball"), ui->centralWidget);
    a_button->setGeometry(25, 500, 50, 50);
    QPushButton* f_button = new QPushButton(QString::fromStdString("Slow\ndown\nball"), ui->centralWidget);
    f_button->setGeometry(100, 500, 50, 50);

    //TODO
    //connect() creates one-way link: from button - to called method
    //how can we create link from object data to LCD, when LCD is accessible only in this method?
    QLCDNumber* ballVelocityX = new QLCDNumber(ui->centralWidget);
    ballVelocityX->setGeometry(175, 500, 100, 20);
    QLCDNumber* ballVelocityY = new QLCDNumber(ui->centralWidget);
    ballVelocityY->setGeometry(175, 525, 100, 20);

    connect(help_button, SIGNAL(clicked()), SLOT(showControlsHelp()));
    connect(clear_button, SIGNAL(clicked()), SLOT(clearScreen()));
    connect(quit_button, SIGNAL(clicked()), SLOT(close()));
    connect(a_button, SIGNAL(clicked()), SLOT(handleBallAccelerationButton()));
    connect(f_button, SIGNAL(clicked()), SLOT(handleBallFrictionButton()));
}

void MainWindow::showControlsHelp()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Controls help");
    msgBox.setText("Information on control keys");
    msgBox.setInformativeText("Click with Cntrl to place spawn area\n" \
                              "Click with Shift to place reactive balls\n" \
                              "Click outside spawn area to place target\n" \
                              "Click inside spawn area to place ball\n" \
                              "Click ESC to clear screen\n");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::handleBallAccelerationButton()
{
    ball.applyAcceleration();
}

void MainWindow::handleBallFrictionButton()
{
    ball.applyFriction();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    std::string spawn_label = "Spawn Area";
    painter.drawRect(spawn_area);
    if(spawn_area.isValid()) painter.drawText(spawn_area.topLeft() - QPoint(-3, 4), QString::fromStdString(spawn_label));
    if(ball.isValid())
    {
        QPointF ball_center(qreal(ball.x()), qreal(ball.y()));
        painter.drawEllipse(ball_center, qreal(ball.radius()), qreal(ball.radius()));
        painter.drawLine(ball_center, target.center());
    }
    painter.setBrush(QBrush(Qt::green));
    for (int i = 0; i < balls.size(); i++)
    {
        QPointF tmp_ball_center(qreal(balls[i].x()), qreal(balls[i].y()));
        painter.drawEllipse(tmp_ball_center, qreal(balls[i].radius()), qreal(balls[i].radius()));
    }
    painter.setBrush(QBrush(Qt::red));
    if(target.isValid()) painter.drawEllipse(target.center(), 2, 2);

    painter.setBrush(QBrush());
    painter.drawRect(screen_area);
    painter.setBrush(QBrush(QColor(130,130,130)));
    painter.drawRect(ui_area);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint click_pos = event->pos();
    if(screen_area.contains(click_pos))
    {
        if(spawn_area.isValid() && spawn_area.contains(click_pos))
        {
            ball.setX(event->x());
            ball.setY(event->y());
            if(!ball.isValid()) ball.setRadius(16);
        }
        else if(event->modifiers() & Qt::ControlModifier)
        {
            int spawn_size = 64;
            QPoint spawn_top_left = click_pos - QPoint(spawn_size/2, spawn_size/2);
            spawn_area = QRect(spawn_top_left, QSize(spawn_size, spawn_size));
        }
        else if(event->modifiers() & Qt::ShiftModifier)
        {
            Ball tmp_ball(event->x(), event->y(), 0, 0, 32);    //Balls radius will be random ... later
            bool can_place = true;
            for(int i = 0; i < balls.size(); i++)
            {
                if(tmp_ball.intersectsBall(balls[i]))
                {
                    can_place = false;
                    break;
                }
            }
            if(ball.intersectsBall(tmp_ball)) can_place = false;
            if(can_place) balls.append(tmp_ball);
        }
        else
        {
            target = QRect(click_pos - QPoint(4,4), QSize(8,8));
        }
    }
    ball.setMoveTarget(static_cast<float>(target.center().x()), static_cast<float>(target.center().y()));
    repaint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //Don't work
    //QPoint cur = event->pos();
    //qDebug("%d %d", cur.x(), cur.y());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key::Key_Escape)
    {
        balls.clear();
        ball.setRadius(0.0f);
        target = QRect();
        spawn_area = QRect();
    }
    if(event->key() == Qt::Key::Key_F1)
    {
        showControlsHelp();
    }
}
