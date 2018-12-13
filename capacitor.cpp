#include "capacitor.h"
#include <QDebug>
Capacitor::Capacitor(unsigned int INDEX)
{
    index=INDEX;
    name="C"+QString::number(index);
    value="0";
    pixmap = new QPixmap(":/resources/capacitor.png");
    width=pixmap->width();
    height=pixmap->height();
    bound=new QRectF(-width/2.,-height/2.,width,height);

    ports.append(QPoint(anker_x,anker_y-4));
    ports.append(QPoint(anker_x,anker_y+4));
}
Capacitor::~Capacitor(){
    index_list.remove(index);
    delete pixmap;
    delete bound;
}

QRectF Capacitor::boundingRect() const{
    return *bound;
}
void Capacitor::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(-width/2,-height/2,*pixmap);
    qreal currentRotation = rotation();
    qDebug() << "Rotation = " << currentRotation << endl;
    painter->rotate(-currentRotation);
    if(fabs(rotation()-0)<1e-6){
        painter->drawText(21,-46,name);
        painter->drawText(21,50,value);
    }else if(fabs(rotation()-90)<1e-6){
        painter->drawText(-55,-21,name);
        painter->drawText(42,-21,value);
    }else if(fabs(rotation()-180)<1e-6){
        painter->drawText(21,-46,name);
        painter->drawText(21,50,value);
    }else if(fabs(rotation()-270)<1e-6){
        painter->drawText(-55,-21,name);
        painter->drawText(42,-21,value);
    }
    painter->rotate(currentRotation);
}
void Capacitor::rotate(){
    this->setRotation(this->rotation()+90);
    if(fabs(rotation()-360)<1e-6)
        this->setRotation(0);
    ports[0]=QPoint(-(ports[0].y()-anker_y)+anker_x,(ports[0].x()-anker_x)+anker_y); //rotate 90 degrees
    ports[1]=QPoint(-(ports[1].y()-anker_y)+anker_x,(ports[1].x()-anker_x)+anker_y);
    qDebug() << port1 << " , " << port2 << endl;
}
void Capacitor::moveTo(const QPointF scenePoint){
    QPoint oldAnker=QPoint(anker_x,anker_y);
    anker_x=round(scenePoint.x())/pixPerAnker;
    anker_y=round(scenePoint.y())/pixPerAnker;
    setPos(anker_x*pixPerAnker,anker_y*pixPerAnker);
    ports[0]+=getAnkerPoint()-oldAnker;
    ports[1]+=getAnkerPoint()-oldAnker;
}
void Capacitor::set(QString cname,QString cvalue)
{
    name=cname;
    value=cvalue;
}
QSet<unsigned> Capacitor::index_list;
