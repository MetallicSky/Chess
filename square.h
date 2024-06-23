#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QBrush>
#include "piece.h"




class Square:public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    Square(QGraphicsItem *parent = NULL);

    void setColor(bool color);
    void highlightOriginal();
    void highlightPath();
    void highlightAttack();
    void unHighlight();
    bool isFree(bool color);
    void movePiece(Square* from);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    bool color;
    bool highlighted;
    bool retiredSquare;
    Piece *piece;

signals:
    void clicked();

};

#endif // SQUARE_H
