#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include <square.h>


class Board
{
public:
    Board();

    void placeSquares(int x, int y);
    void placePieces();
    void unHighlightAll();
    void placeRetirees();

    Square* board[8][8];
    Square* retiredWhites[7];
    size_t rwSize;
    Square* retiredBlacks[7];
    size_t rbSize;

};

#endif // BOARD_H
