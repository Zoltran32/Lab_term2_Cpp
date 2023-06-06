#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Circle
{
    QPoint center;
    int radius;

    bool intersects(const Circle &circle)
    {
        if((circle.center - this->center).manhattanLength() < 2*circle.radius)
            return true;
        return false;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage grass = QImage(":new/prefix1/img/grass25x25.png");
    QImage water = QImage(":new/prefix1/img/water25x25.png");
    QImage flower = QImage(":new/prefix1/img/flower25x25.png");
    QImage round_flower = QImage(":new/prefix1/img/round_flower25x25.png");
    QVector<QRect> flowers_rects;
    QVector<QRect> round_flowers_rects;
    QRect pool;

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void generateRoundFlowers(int rounds_ammount);
    bool rectCanBePlaced(QRect f);
};
#endif // MAINWINDOW_H
