#include "game.h"

#define BLACK 0
#define WHITE 1

Game::Game(QWidget* parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 1000);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1200, 1000);
    setScene(scene);
    turn = BLACK; // because we change it to WHITE later

    controlPieceSquare = nullptr;
    exposedPawn = nullptr;
    endGame = false;

}

void Game::start()
{
    scene->clear();

    board = new Board();
    board->placeSquares(200, 150);
    board->placePieces();

    QGraphicsRectItem *leftPanel = new QGraphicsRectItem(0, 0, 150, scene->height());
    QGraphicsRectItem *rightPanel = new QGraphicsRectItem(scene->width() - 150, 0, 150, scene->height());

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    QColor whiteColor(255, 206, 161);
    brush.setColor(whiteColor);
    leftPanel->setBrush(brush);

    QColor blackColor(210, 139, 70);
    brush.setColor(blackColor);
    rightPanel->setBrush(brush);

    leftPanel->setOpacity(1);
    rightPanel->setOpacity(1);

    scene->addItem(leftPanel);
    scene->addItem(rightPanel);

    turnText = new QGraphicsTextItem();
    changeTurn();
    turnText->setPos(160, 5);
    scene->addItem(turnText);

    board->placeRetirees();
}

bool Game::getTurn()
{
    return turn;
}

void Game::tradeSuccess(Square* prisoner)
{
    prisoner->piece->setPos(controlPieceSquare->piece->pos());
    prisoner->piece->row = controlPieceSquare->piece->row;
    prisoner->piece->col = controlPieceSquare->piece->col;
    scene->removeItem(controlPieceSquare->piece);
    delete controlPieceSquare->piece;
    controlPieceSquare->piece = prisoner->piece;
    prisoner->piece = nullptr;
    if (prisoner->color == BLACK)
        for (size_t i = 0; i < 7; i++)
            board->retiredWhites[i]->setColor(BLACK);
    else
        for (size_t i = 0; i < 7; i++)
            board->retiredBlacks[i]->setColor(WHITE);
    trade = false;
    changeTurn();
}

void Game::tradeClose()
{
    for (size_t i = 0; i < 7; i++)
    {
        board->retiredWhites[i]->setColor(BLACK);
        board->retiredBlacks[i]->setColor(WHITE);
    }
    trade = false;
}

void Game::restartGame()
{
    QProcess::startDetached(QApplication::applicationFilePath());
    exit(12);
}

void Game::changeTurn()
{
    QFont font("Arial", 40);
    turnText->setFont(font);

    if (endGame)
    {
        QFont font1("Arial", 30);
        turnText->setFont(font1);
        turnText->setPlainText(QString("Congratulations! Click to restart the game"));
        return;
    }

    if (turn == WHITE)
    {
        turnText->setPlainText(QString("BLACK"));
        turn = BLACK;
    }
    else
    {
        turnText->setPlainText(QString("WHITE"));
        turn = WHITE;
    }

    if (exposedPawn != nullptr)
        if (turn == exposedPawn->color) // exposed status can only be 1 at a time and lasts only 1 turn
        {
            exposedPawn->pawnDeleteExposed();
            exposedPawn == nullptr;
        }

    controlPieceSquare = nullptr;

}
