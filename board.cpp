#include "board.h"
#include "game.h"

#define BLACK 0
#define WHITE 1

extern Game* game;

Board::Board()
{
    rbSize = 0;
    rwSize = 0;
}

void Board::placeSquares(int x_original, int y_original)
{
    int side = 100;
    int x = x_original;
    int y = y_original;

    bool color = WHITE;

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            Square* square = new Square();
            square->setPos(x, y);
            square->setColor(color);
            board[i][j] = square;
            game->scene->addItem(board[i][j]);
            x+= side;

            if (color == WHITE)
                color = BLACK;
            else
                color = WHITE;
        }
        x = x_original;
        y += side;

        if (color == WHITE)
            color = BLACK;
        else
            color = WHITE;
    }

    char number('8');
    char character('A');
    QFont Font("Times", 40);
    for (size_t i = 0; i < 8; i++)
    {
        QString str = QChar(character);
        QGraphicsTextItem *char0 = new QGraphicsTextItem(str);
        char0->setFont(Font);
        char0->setPos(229 + 100 * i, 95);
        game->scene->addItem(char0);

        QGraphicsTextItem *char1 = new QGraphicsTextItem(str);
        char1->setFont(Font);
        char1->setPos(229 + 100 * i, 937);
        game->scene->addItem(char1);


        str = QChar(number);

        QGraphicsTextItem *num0 = new QGraphicsTextItem(str);

        num0->setFont(Font);

        num0->setPos(165, 166 + i * 100);
        game->scene->addItem(num0);

        QGraphicsTextItem *num1 = new QGraphicsTextItem(str);

        num1->setFont(Font);

        num1->setPos(1000, 165 + i * 100);
        game->scene->addItem(num1);


        character++;
        number--;
    }



}

void Board::placePieces()
{
    bool color = BLACK;

    for (size_t i = 1; i < 8; i += 5)
    {

        for (size_t j = 0; j < 8; j++)
        {
            Pawn* piece = new Pawn(i, j, color);
            piece->spawn(i, j);
        }

        if (color == WHITE)
            color = BLACK;
        else
            color = WHITE;
    }


    for (size_t i = 0; i < 8; i += 7)
    {

        for (size_t j = 0; j < 8; j += 7)
        {
            Rook* piece = new Rook(i, j, color);
            piece->spawn(i, j);
        }

        if (color == WHITE)
            color = BLACK;
        else
            color = WHITE;
    }

    for (size_t i = 0; i < 8; i += 7)
    {

        for (size_t j = 1; j < 7; j += 5)
        {
            Knight* piece = new Knight(i, j, color);
            piece->spawn(i, j);
        }

        if (color == WHITE)
            color = BLACK;
        else
            color = WHITE;
    }

    for (size_t i = 0; i < 8; i += 7)
    {

        for (size_t j = 2; j < 6; j += 3)
        {
            Bishop* piece = new Bishop(i, j, color);
            piece->spawn(i, j);
        }

        if (color == WHITE)
            color = BLACK;
        else
            color = WHITE;
    }

    for (size_t i = 0; i < 8; i += 7)
    {

        Queen* piece = new Queen(i, 3, color);
        piece->spawn(i, 3);

        if (color == WHITE)
            color = BLACK;
        else
            color = WHITE;
    }

    for (size_t i = 0; i < 8; i += 7)
    {

        King* piece = new King(i, 4, color);
        piece->spawn(i, 4);

        if (color == WHITE)
            color = BLACK;
        else
            color = WHITE;
    }
}

void Board::unHighlightAll()
{
    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            board[i][j]->unHighlight();
    if (game->exposedPawn != nullptr)
    {
        if (game->exposedPawn->color == WHITE)
        {
            board[game->exposedPawn->row][game->exposedPawn->col]->piece = game->exposedPawn;
            if (game->exposedPawn == board[game->exposedPawn->row + 1][game->exposedPawn->col]->piece)
                board[game->exposedPawn->row + 1][game->exposedPawn->col]->piece = nullptr;
        }
        else
        {
            board[game->exposedPawn->row][game->exposedPawn->col]->piece = game->exposedPawn;
            if (game->exposedPawn == board[game->exposedPawn->row - 1][game->exposedPawn->col]->piece)
                board[game->exposedPawn->row - 1][game->exposedPawn->col]->piece = nullptr;
        }
    }
}


void Board::placeRetirees()
{
    for (size_t i = 0; i < 7; i++)
    {
        Square* square1 = new Square();
        square1->retiredSquare = true;
        square1->setColor(WHITE);
        square1->setPos(25, 150 + i * 100);
        retiredBlacks[i] = square1;
        game->scene->addItem(retiredBlacks[i]);

        Square* square2 = new Square();
        square2->retiredSquare = true;
        square2->setColor(BLACK);
        square2->setPos(game->width() - 125, 150 + i * 100);
        retiredWhites[i] = square2;
        game->scene->addItem(retiredWhites[i]);
    }
}
