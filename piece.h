#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>
#include <QLabel>

class Piece: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Piece();
    Piece(int row, int col, bool color, QGraphicsItem *parent = NULL);


    virtual void spawn(int row, int col);
    virtual void getPathes();
    virtual void pawnDeleteBoost();
    virtual void pawnSetExposed();
    virtual bool pawnGetExposed();
    virtual void pawnDeleteExposed();

    int row;
    int col;
    bool color;
    bool pawn;
    bool roque;
    bool king;

};


class Pawn: public Piece
{
public:
    Pawn(int row, int col, bool color, QGraphicsItem *parent = NULL);

    void getPathes() override;
    void pawnDeleteBoost() override;
    void pawnSetExposed() override;
    bool pawnGetExposed() override;
    void pawnDeleteExposed() override;
    void tradeHighlight(bool tradingColor);

    bool boost;
    bool exposed;
};


class Rook: public Piece
{
public:
    Rook(int row, int col, bool color, QGraphicsItem *parent = NULL);

    void getPathes() override;
};


class Knight: public Piece
{
public:
    Knight(int row, int col, bool color, QGraphicsItem *parent = NULL);

    void getPathes() override;
};


class Bishop: public Piece
{
public:
    Bishop(int row, int col, bool color, QGraphicsItem *parent = NULL);

    void getPathes() override;
};


class Queen: public Piece
{
public:
    Queen(int row, int col, bool color, QGraphicsItem *parent = NULL);

    void getPathes() override;
};


class King: public Piece
{
public:
    King(int row, int col, bool color, QGraphicsItem *parent = NULL);

    void getPathes() override;


};

#endif // PIECE_H
