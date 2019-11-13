#ifndef CONSTANTES_CAMPO_H
#define CONSTANTES_CAMPO_H

#include <QMouseEvent>
#include <iostream>
#include "configuracao.h"

//using namespace configuracao;
class constantes_campo
{
public:
    constantes_campo();
    void mousePressEvent(QMouseEvent *event);
    Point2f inputQuad[4];
    Point2f outputQuad[4];
};

#endif // CONSTANTES_CAMPO_H
