#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QProcess>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "board.h"


class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget* parent = NULL);

    void start();
    void changeTurn();
    bool getTurn();
    void tradeSuccess(Square * prisoner);
    void tradeClose();
    void restartGame();

    bool endGame;
    bool trade;
    QGraphicsScene *scene;
    Board * board;
    Square* controlPieceSquare;
    Piece* exposedPawn;
private:

    QGraphicsTextItem *turnText;
    bool turn;
};

#endif // GAME_H
