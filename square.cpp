#include "square.h"
#include "game.h"

extern Game *game;

#define BLACK 0
#define WHITE 1

Square::Square(QGraphicsItem *parent)
{
    retiredSquare = false;
    highlighted = false;
    piece = nullptr;

    QVector<QPointF> squarePoints;
    squarePoints << QPoint(0,0)
              << QPointF(1, 0)
              << QPointF(1, 1)
              << QPointF(0, 1);

    int SCALE_BY = 100;

    for (size_t i = 0; i < squarePoints.size(); ++i)
        squarePoints[i] *= SCALE_BY;

    QPolygonF square(squarePoints);

    setPolygon(square);
}

void Square::setColor(bool color)
{
    this->color = color;
    highlighted = false;

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);


    if (color == WHITE)
    {
        QColor newColor(255, 206, 161);
        brush.setColor(newColor);
        setBrush(brush);
    }
    else
    {
        QColor newColor(210, 139, 70);
        brush.setColor(newColor);
        setBrush(brush);
    }
}

void Square::highlightOriginal()
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    QColor newColor(120, 148, 88);
    brush.setColor(newColor);
    setBrush(brush);
}

void Square::highlightPath()
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    QColor newColor(68, 114, 166);
    brush.setColor(newColor);
    setBrush(brush);
    highlighted = true;
}

void Square::highlightAttack()
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    QColor newColor(116, 52, 51);
    brush.setColor(newColor);
    setBrush(brush);
    highlighted = true;
}

void Square::unHighlight()
{
    setColor(color);
}

bool Square::isFree(bool fromColor)
{
    if (retiredSquare)
        return false;
    if (this->piece == nullptr)
    {
        highlightPath();
        return true;
    }
    else if (this->piece->color != fromColor)
    {
        highlightAttack();
        return false;
    }
    else
        return false;
}

void Square::movePiece(Square *from)
{
    if (piece != nullptr)
    {
        if (piece->pawn == true) // pawn gets deleted
        {
            if (from->piece->pawnGetExposed())
            {
                game->board->unHighlightAll();
                game->exposedPawn = nullptr;
            }

            if (piece->pawnGetExposed())
                piece->pawnDeleteExposed();
            delete piece;
        }
        else
        {
            if (piece->king)
            {
                game->endGame = true;
                game->changeTurn();
                return;
            }
            game->scene->removeItem(piece);
            if (piece->color == WHITE) // while others get retired
            {
                piece->setPos(game->width() - 105, 170 + game->board->rwSize * 100 );
                game->board->retiredWhites[game->board->rwSize]->piece = piece;
                game->scene->addItem(game->board->retiredWhites[game->board->rwSize]->piece);
                game->board->rwSize++;
            }
            else
            {
                piece->setPos(45, 170 + game->board->rbSize * 100);
                game->board->retiredBlacks[game->board->rbSize]->piece = piece;
                game->scene->addItem(game->board->retiredBlacks[game->board->rbSize]->piece);
                game->board->rbSize++;


            }

            piece = nullptr;
        }
    }

    piece = from->piece;
    from->piece = nullptr;
    piece->setPos(this->pos() );
    piece->setPos(piece->x() + 20, piece->y() + 20);
    piece->pawnDeleteBoost();
    int oldRow = piece->row;
    int oldCol = piece->col;
    piece->row = (piece->y() - 170) / 100;
    piece->col = (piece->x() - 220) / 100;
    if (piece->roque)
    {
        piece->roque = false;
        if (piece->king)
        {
            if (piece->col - oldCol == 2) // right roque
            {
                game->board->board[piece->row][piece->col - 1]->piece = game->board->board[piece->row][piece->col + 1]->piece;
                game->board->board[piece->row][piece->col + 1]->piece = nullptr;
                game->board->board[piece->row][piece->col - 1]->piece->roque = false;
                game->board->board[piece->row][piece->col - 1]->piece->setPos(piece->x() - 100, piece->y());
                game->board->board[piece->row][piece->col - 1]->piece->col = piece->col - 1;
            }
            else if (oldCol - piece->col == 2) // left roque
            {
                game->board->board[piece->row][piece->col + 1]->piece = game->board->board[piece->row][piece->col - 2]->piece;
                game->board->board[piece->row][piece->col - 2]->piece = nullptr;
                game->board->board[piece->row][piece->col + 1]->piece->roque = false;
                game->board->board[piece->row][piece->col + 1]->piece->setPos(piece->x() + 100, piece->y());
                game->board->board[piece->row][piece->col + 1]->piece->col = piece->col + 1;
            }
        }


    }
    if (piece->pawn)
    {
        if (piece->color == BLACK)
        {
            if (piece->row - oldRow == 2)
                piece->pawnSetExposed();
        }
        else if (piece->row - oldRow == -2)
            piece->pawnSetExposed();
    }


    game->changeTurn();
}



void Square::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (game->endGame)
    {
        game->restartGame();
        return;
    }
    if (retiredSquare && (game->trade == false))
        return;
    if (event->button() == Qt::LeftButton)
    {
        if (highlighted == true)
        {
            if (game->trade)
            {
                game->tradeSuccess(this);
            }
            else
                movePiece(game->controlPieceSquare);
        }
        else
        {
            if (game->trade)
                game->tradeClose();
        }
    }

    game->board->unHighlightAll();
    if (game->controlPieceSquare != nullptr)
        game->controlPieceSquare->unHighlight();
    game->controlPieceSquare = nullptr;
    if (event->button() != Qt::LeftButton)
    {
        game->tradeClose();
        return;
    }



    if (piece != nullptr)
    {
        if (game->getTurn() != this->piece->color)
            return;
        game->controlPieceSquare = this;
        highlightOriginal();
        piece->getPathes();
    }

}
