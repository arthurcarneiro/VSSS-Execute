#include "constantes_campo.h"

constantes_campo::constantes_campo()
{

}

void constantes_campo::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        int x = event->localPos().x();
        int y = event->localPos().y();
        inputQuad[0] = Point2f(event->localPos().x(),event->localPos().y());
        cout << x << "," << y << endl;
        cout << inputQuad[0].x  << "," << inputQuad[0].y << endl;
    }
}
