#include "Enemy.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>

#include <QDebug>
Enemy::Enemy(QList<QPointF> pointsToFollow, QGraphicsItem *parent){
    // set graphics
    setPixmap(QPixmap(":/images/enemy.png"));

    // set points
    points = pointsToFollow;
    point_index = 0;
    dest = points[0];
    rotateToPoint(dest);

    // connect timer to move_forward
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moveForward()));
    timer->start(150);
}

void Enemy::rotateToPoint(QPointF p){
    QLineF ln(pos(),p);
    setRotation(-1 * ln.angle());
}

void Enemy::moveForward(){
    // if close to dest, rotate to next dest
    QLineF ln(pos(),dest);

    if (ln.length() < 5){
        point_index++;
        // last point reached
        if (point_index >= points.size()){
            return;
        }
        // last point not reached
        dest = points[point_index];
        rotateToPoint(dest);
    }

    // move enemy forward at current angle
    int STEP_SIZE = 5;
    double theta = rotation(); // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);
}
