#include "Bullet.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h> // qSin, qCos, qTan
#include "Game.h"
#include "Enemy.h"

extern Game * game;

Bullet::Bullet(QGraphicsItem *parent): QObject(),QGraphicsPixmapItem(parent){
    // set graphics
    setPixmap(QPixmap(":/images/browntowerbullet.png"));

    // connect a timer to move()
    QTimer * move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));
    move_timer->start(50);

    // initialize values
    maxRange = 100;
    distanceTravelled = 0;
}

void Bullet::move(){
    int STEP_SIZE = 30;
    double theta = rotation(); // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    QList<QGraphicsItem*> colliding_items=collidingItems();
        for(int i=0,n=colliding_items.size();i<n;i++){
            if(typeid(*(colliding_items[i]))==typeid(Enemy))
            {
             scene()->removeItem(colliding_items[i]);
             scene()->removeItem(this);
             delete colliding_items[i];
             delete this;
             return;
        }
        }


}

double Bullet::getMaxRange(){
    return maxRange;
}

double Bullet::getDistanceTravelled(){
    return distanceTravelled;
}

void Bullet::setMaxRange(double rng){
maxRange = rng;
}

void Bullet::setDistanceTravelled(double dist){
    distanceTravelled = dist;
}
