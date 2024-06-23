#include "piece.h"
#include "game.h"

extern Game *game;

#define BLACK 0
#define WHITE 1

Piece::Piece()
{

}

Piece::Piece(int row, int col, bool color, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    this->roque = false;
    this->king = false;
    this->pawn = false;
    this->row = row;
    this->col = col;
    this->color = color;
    if (color == 1)
        setPixmap(QPixmap(":/images/D:/Users/user/Downloads/Images/pawn_white.png"));
    else
        setPixmap(QPixmap(":/images/D:/Users/user/Downloads/Images/pawn_black.png"));

}

void Piece::spawn(int row, int col)
{
    if (game->board->board[row][col]->piece == nullptr)
        game->board->board[row][col]->piece = this;
    else
    {
        delete game->board->board[row][col]->piece;
        game->board->board[row][col]->piece = this;
    }

    setPos(220 + col * 100, 170 + row * 100);
    game->scene->addItem(this);
}

void Piece::getPathes()
{

}

void Piece::pawnDeleteBoost()
{

}

void Piece::pawnSetExposed()
{

}

bool Piece::pawnGetExposed()
{
    return false;
}

void Piece::pawnDeleteExposed()
{

}


Pawn::Pawn(int row, int col, bool color, QGraphicsItem *parent)
{
    this->roque = false;
    this->king = false;
    this->pawn = true;
    this->row = row;
    this->col = col;
    this->color = color;
    if (color == 1)
        setPixmap(QPixmap(":/images/D:/Users/user/Downloads/Images/pawn_white.png"));
    else
        setPixmap(QPixmap(":/images/D:/Users/user/Downloads/Images/pawn_black.png"));

    boost = true;
    exposed = false;
}

void Pawn::getPathes()
{
    switch (color)
    {
    case BLACK:
        if (row == 7) // trade request
        {
            tradeHighlight(color);
            return;
        }


        if (boost) //boost path check
        {
            for (size_t i = 1; i < 3; i++)
                if (game->board->board[row + 1 * i][col]->isFree(color) == false)
                {
                    game->board->board[row + 1 * i][col]->unHighlight();
                    break;
                }
        }
        else if (game->board->board[row + 1 ][col]->piece == nullptr)
            game->board->board[row + 1 ][col]->isFree(color); //regular path check

        //attack checks
        if (col > 0)
        {
            if (game->board->board[row][col - 1]->piece != nullptr)
                if (game->board->board[row][col - 1]->piece->pawnGetExposed() == true) // exposed check left
                {
                    game->board->board[row + 1][col - 1]->highlightAttack();
                    game->board->board[row + 1][col - 1]->piece = game->board->board[row][col - 1]->piece;
                    game->board->board[row][col - 1]->piece = nullptr;
                }
            if (game->board->board[row + 1 ][col - 1]->isFree(color))
                game->board->board[row + 1 ][col - 1]->unHighlight();
        }
        if (col < 7)
        {
            if (game->board->board[row][col + 1]->piece != nullptr)
                if (game->board->board[row][col + 1]->piece->pawnGetExposed() == true) // exposed check right
                {
                    game->board->board[row + 1][col + 1]->highlightAttack();
                    game->board->board[row + 1][col + 1]->piece = game->board->board[row][col + 1]->piece;
                    game->board->board[row][col + 1]->piece = nullptr;
                }
            if (game->board->board[row + 1][col + 1]->isFree(color))
                game->board->board[row + 1 ][col + 1]->unHighlight();
        }


        break;
    case WHITE:
        if (row == 0) // trade request
        {
            tradeHighlight(color);
            return;
        }

        if (boost) //boost path check
        {
            for (size_t i = 1; i < 3; i++)
                if (game->board->board[row - 1 * i][col]->isFree(color) == false)
                {
                    game->board->board[row - 1 * i][col]->unHighlight();
                    break;
                }
        }
        else if (game->board->board[row - 1 ][col]->piece == nullptr)
            game->board->board[row - 1 ][col]->isFree(color); //regular path check

        //attack checks
        if (col > 0)
        {
            if (game->board->board[row][col - 1]->piece != nullptr)
                if (game->board->board[row][col - 1]->piece->pawnGetExposed() == true) // exposed check left
                {
                    game->board->board[row - 1][col - 1]->highlightAttack();
                    game->board->board[row - 1][col - 1]->piece = game->board->board[row][col - 1]->piece;
                    game->board->board[row][col - 1]->piece = nullptr;
                }

            if (game->board->board[row - 1 ][col - 1]->isFree(color))
                game->board->board[row - 1 ][col - 1]->unHighlight();
        }
        if (col < 7)
        {
            if (game->board->board[row][col + 1]->piece != nullptr)
                if (game->board->board[row][col + 1]->piece->pawnGetExposed() == true) // exposed check right
                {
                    game->board->board[row - 1][col + 1]->highlightAttack();
                    game->board->board[row - 1][col + 1]->piece = game->board->board[row][col + 1]->piece;
                    game->board->board[row][col + 1]->piece = nullptr;
                }

            if (game->board->board[row - 1][col + 1]->isFree(color))
                game->board->board[row - 1 ][col + 1]->unHighlight();
        }


        break;
    }

}

void Pawn::pawnDeleteBoost()
{
    boost = false;
}

void Pawn::pawnSetExposed()
{
    exposed = true;
    if (game->exposedPawn !=nullptr)
        game->exposedPawn->pawnDeleteExposed();
    game->exposedPawn = this;
}

bool Pawn::pawnGetExposed()
{
    return exposed;
}

void Pawn::pawnDeleteExposed()
{
    exposed = false;
    game->exposedPawn = nullptr;
}

void Pawn::tradeHighlight(bool tradingColor)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    QColor newColor(120, 148, 88);
    brush.setColor(newColor);
    if (tradingColor == WHITE)
    {
        for (size_t i = 0; i < 7; i++)
            if (game->board->retiredWhites[i]->piece != nullptr)
            {
                game->board->retiredWhites[i]->setBrush(brush);
                game->board->retiredWhites[i]->highlighted = true;
            }
    }
    else
        for (size_t i = 0; i < 7; i++)
            if (game->board->retiredBlacks[i]->piece != nullptr)
            {
                game->board->retiredBlacks[i]->setBrush(brush);
                game->board->retiredBlacks[i]->highlighted = true;
            }
    game->trade = true;

}

Rook::Rook(int row, int col, bool color, QGraphicsItem *parent)
{
    this->pawn = false;
    this->king = false;
    this->roque = true;
    this->row = row;
    this->col = col;
    this->color = color;
    if (color == 1)
        setPixmap(QPixmap(":/images/D:/Users/user/Downloads/Images/rook_white.png"));
    else
        setPixmap(QPixmap(":/images/D:/Users/user/Downloads/Images/rook_black.png"));
}

void Rook::getPathes()
{
    // top  check
    if (row > 0)
        for (int i = row - 1; i > -1; i--)
            if (game->board->board[i][col]->isFree(color) == false)
                break;
    // right check
    if (col < 7)
        for (int i = col + 1; (i < 8); i++)
            if (game->board->board[row][i]->isFree(color) == false)
                break;

    // bottom  check
    if (row < 7)
        for (int i = row + 1; i < 8; i++)
            if (game->board->board[i][col]->isFree(color) == false)
                break;

    // left check
    if (col > 0)
        for (int i = col - 1; i > -1; i--)
            if (game->board->board[row][i]->isFree(color) == false)
                break;
}

Knight::Knight(int row, int col, bool color, QGraphicsItem *parent)
{
    this->pawn = false;
    this->king = false;
    this->roque = false;
    this->row = row;
    this->col = col;
    this->color = color;
    if (color == 1)
        setPixmap(QPixmap(":/images/D:/Users/user/Downloads/Images/knight_white.png"));
    else
        setPixmap(QPixmap(":/images/D:/Users/user/Downloads/Images/knight_black.png"));
}

void Knight::getPathes()
{

    // tol right check
    if ((row > 1) && (col < 7))
        game->board->board[row - 2][col + 1]->isFree(color);
    if ((row > 0) && (col < 6))
        game->board->board[row - 1][col + 2]->isFree(color);

    // bottom right check
    if ((row < 7) && (col < 6))
        game->board->board[row + 1][col + 2]->isFree(color);
    if ((row < 6) && (col < 7))
        game->board->board[row + 2][col + 1]->isFree(color);

    // bottom left check
    if ((row < 6) && (col > 0))
        game->board->board[row + 2][col - 1]->isFree(color);
    if ((row < 7) && (col > 1))
        game->board->board[row + 1][col - 2]->isFree(color);

    // top left check
    if ((row > 0) && (col > 1))
        game->board->board[row - 1][col - 2]->isFree(color);
    if ((row > 1) && (col > 0))
        game->board->board[row - 2][col - 1]->isFree(color);


}

Bishop::Bishop(int row, int col, bool color, QGraphicsItem *parent)
{
    this->pawn = false;
    this->king = false;
    this->roque = false;
    this->row = row;
    this->col = col;
    this->color = color;
    if (color == 1)
        setPixmap(QPixmap(":/images/D:/Users/user/Downloads/Images/bishop_white.png"));
    else
        setPixmap(QPixmap(":/images/D:/Users/user/Downloads/Images/bishop_black.png"));
}

void Bishop::getPathes()
{
    // top left check
    if ((row > 0) && (col > 0))
        for (int i = row - 1, j = col - 1; ((i > -1) && (j > -1)); i--, j--)
            if (game->board->board[i][j]->isFree(color) == false)
                break;
    // top right check
    if ((row > 0) && (col < 7))
        for (int i = row - 1, j = col + 1; ((i > -1) && (j < 8)); i--, j++)
            if (game->board->board[i][j]->isFree(color) == false)
                break;

    // bottom right check
    if ((row < 7) && (col < 7))
        for (int i = row + 1, j = col + 1; ((i < 8) && (j < 8)); i++, j++)
            if (game->board->board[i][j]->isFree(color) == false)
                break;

    // bottom left check
    if ((row < 7) && (col > 0))
        for (int i = row + 1, j = col - 1; ((i < 8) && (j > -1)); i++, j--)
            if (game->board->board[i][j]->isFree(color) == false)
                break;
}

Queen::Queen(int row, int col, bool color, QGraphicsItem *parent)
{
    this->pawn = false;
    this->king = false;
    this->roque = false;
    this->row = row;
    this->col = col;
    this->color = color;
    if (color == 1)
        setPixmap(QPixmap(":/images/D:/Users/user/Downloads/Images/queen_white.png"));
    else
        setPixmap(QPixmap(":/images/D:/Users/user/Downloads/Images/queen_black.png"));
}

void Queen::getPathes()
{
    // from rook

    // top  check
    if (row > 0)
        for (int i = row - 1; i > -1; i--)
            if (game->board->board[i][col]->isFree(color) == false)
                break;
    // right check
    if (col < 7)
        for (int i = col + 1; (i < 8); i++)
            if (game->board->board[row][i]->isFree(color) == false)
                break;

    // bottom  check
    if (row < 7)
        for (int i = row + 1; i < 8; i++)
            if (game->board->board[i][col]->isFree(color) == false)
                break;

    // left check
    if (col > 0)
        for (int i = col - 1; i > -1; i--)
            if (game->board->board[row][i]->isFree(color) == false)
                break;

    // from bishop

    // top left check
    if ((row > 0) && (col > 0))
        for (int i = row - 1, j = col - 1; ((i > -1) && (j > -1)); i--, j--)
            if (game->board->board[i][j]->isFree(color) == false)
                break;
    // top right check
    if ((row > 0) && (col < 7))
        for (int i = row - 1, j = col + 1; ((i > -1) && (j < 8)); i--, j++)
            if (game->board->board[i][j]->isFree(color) == false)
                break;

    // bottom right check
    if ((row < 7) && (col < 7))
        for (int i = row + 1, j = col + 1; ((i < 8) && (j < 8)); i++, j++)
            if (game->board->board[i][j]->isFree(color) == false)
                break;

    // bottom left check
    if ((row < 7) && (col > 0))
        for (int i = row + 1, j = col - 1; ((i < 8) && (j > -1)); i++, j--)
            if (game->board->board[i][j]->isFree(color) == false)
                break;
}

King::King(int row, int col, bool color, QGraphicsItem *parent)
{
    this->pawn = false;
    this->roque = true;
    this->king = true;
    this->row = row;
    this->col = col;
    this->color = color;
    if (color == 1)
        setPixmap(QPixmap(":/images/D:/Users/user/Downloads/Images/king_white.png"));
    else
        setPixmap(QPixmap(":/images/D:/Users/user/Downloads/Images/king_black.png"));
}

void King::getPathes()
{
    // roque check;
    if (roque)
    {
        bool Lpath1 = game->board->board[row][col - 1]->piece == nullptr;
        bool Lpath2 = game->board->board[row][col - 2]->piece == nullptr;
        bool Lpath3 = game->board->board[row][col - 3]->piece == nullptr;
        bool Lpath4Rook = game->board->board[row][col - 4]->piece != nullptr;
        Lpath4Rook = game->board->board[row][col - 4]->piece->roque;

        bool Rpath1 = game->board->board[row][col + 1]->piece == nullptr;
        bool Rpath2 = game->board->board[row][col + 2]->piece == nullptr;
        bool Rpath3Rook = game->board->board[row][col + 3]->piece != nullptr;
        Rpath3Rook = game->board->board[row][col + 3]->piece->roque;

        bool Lroque = Lpath1 && Lpath2 && Lpath3 && Lpath4Rook;
        bool Rroque = Rpath1 && Rpath2 && Rpath3Rook;

        if (Lroque)
        {
            game->board->board[row][col - 2]->highlightPath();
            game->board->board[row][col - 4]->highlightOriginal();
        }
        if (Rroque)
        {
            game->board->board[row][col + 2]->highlightPath();
            game->board->board[row][col + 3]->highlightOriginal();
        }
    }

    // top  check
    if (row > 0)
        game->board->board[row - 1][col]->isFree(color);
    // right check
    if (col < 7)
        game->board->board[row ][col + 1]->isFree(color);

    // bottom  check
    if (row < 7)
        game->board->board[row + 1][col]->isFree(color);

    // left check
    if (col > 0)
        game->board->board[row][col - 1]->isFree(color);


    // top left check
    if ((row > 0) && (col > 0))
        game->board->board[row - 1][col - 1]->isFree(color);
    // top right check
    if ((row > 0) && (col < 7))
        game->board->board[row - 1][col + 1]->isFree(color);

    // bottom right check
    if ((row < 7) && (col < 7))
        game->board->board[row + 1][col + 1]->isFree(color);

    // bottom left check
    if ((row < 7) && (col > 0))
        game->board->board[row + 1][col - 1]->isFree(color);
}
