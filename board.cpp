#include "board.h"

Board::Board(int resolutionWidth, int resolutionHeight, int fieldSize, QString fieldColor, Player *currPlayer, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    currentPlayer = currPlayer;
    paintingEnabled = true;

    int gapSize = 25;
    QScopedPointer<QGraphicsRectItem> rectangle (new QGraphicsRectItem(0,0, fieldSize * rowSize + (gapSize * (rowSize-1)), fieldSize * rowSize + (gapSize * (rowSize-1) ) ) );
    rectangle->setPos(resolutionWidth/2 - rectangle->rect().width()/2, resolutionHeight/2 - rectangle->rect().height()/2);


    for(size_t i = 0; i<rowSize; i++)
    {
        for(size_t j=0; j<rowSize; j++)
        {
            int fieldPositionX = rectangle->x() + fieldSize * j + (j*gapSize);
            int fieldPositionY = rectangle->y() + fieldSize * i + (i*gapSize);

            Field * field = new Field(fieldPositionX, fieldPositionY, fieldSize, fieldColor, currentPlayer, this);
            fields.append(field);
        }
    }
}

Board::~Board()
{
    delete currentPlayer;
}

QVector<Field *> Board::getFields()
{
    return fields;
}

int Board::getRowSize() const
{
    return rowSize;
}

bool Board::checkHorizontally()
{
    int playerOneScoreCounter, playerTwoScoreCounter;
    size_t boardSize = rowSize * rowSize;

    for(size_t row = 0; row < boardSize; row += rowSize)
    {
        playerOneScoreCounter = playerTwoScoreCounter = 0;

        for(size_t column = 0; column < rowSize; column++)
        {
            if(fields[row+column]->getFieldContent() == currentPlayer->getPlayerOne())
                playerOneScoreCounter++;
            if(fields[row+column]->getFieldContent() == currentPlayer->getPlayerTwo())
                playerTwoScoreCounter++;
        }

        if(playerOneScoreCounter == rowSize || playerTwoScoreCounter == rowSize)
        {
            paintWinningRow(row);
            return true;
        }
    }
    return false;
}

bool Board::checkVertically()
{
    int playerOneScoreCounter, playerTwoScoreCounter;
    size_t boardSize = rowSize * rowSize;

    for(size_t column = 0; column < rowSize; column++)
    {
        playerOneScoreCounter = playerTwoScoreCounter =0;

        for(size_t row = 0; row < boardSize; row += rowSize)
        {
            if(fields[column+row]->getFieldContent() == currentPlayer->getPlayerOne())
                playerOneScoreCounter++;
            if(fields[column+row]->getFieldContent() == currentPlayer->getPlayerTwo())
                playerTwoScoreCounter++;
        }

        if(playerOneScoreCounter == rowSize || playerTwoScoreCounter == rowSize)
        {
            paintWinningColumn(column);
            return true;
        }
    }
    return false;
}

bool Board::checkFromTopLeftToBottomRight()
{
    int playerOneScoreCounter = 0, playerTwoScoreCounter = 0;
    size_t boardSize = rowSize * rowSize;

    for(size_t row = 0, column = 0; row < boardSize; row += rowSize, column++)
    {
        if(fields[row+column]->getFieldContent() == currentPlayer->getPlayerOne())
            playerOneScoreCounter++;
        if(fields[row+column]->getFieldContent() == currentPlayer->getPlayerTwo())
            playerTwoScoreCounter++;
    }

    if(playerOneScoreCounter == rowSize || playerTwoScoreCounter == rowSize)
    {
        paintWinningFieldsFromTopLeft();
        return true;
    }

    return false;
}

bool Board::checkFromTopRightToBottomLeft()
{
    int playerOneScoreCounter = 0, playerTwoScoreCounter = 0;
    size_t boardSize = rowSize * rowSize;

    for(size_t row = 0, column = rowSize-1; row < boardSize; row += rowSize, column--)
    {
        if(fields[row+column]->getFieldContent() == currentPlayer->getPlayerOne())
            playerOneScoreCounter++;
        if(fields[row+column]->getFieldContent() == currentPlayer->getPlayerTwo())
            playerTwoScoreCounter++;
    }

    if(playerOneScoreCounter == rowSize || playerTwoScoreCounter == rowSize)
    {
        paintWinningFieldsFromTopRight();
        return true;
    }

    return false;
}

void Board::setBoardEnabled()
{
    for(auto field : fields)
        field->setEnabled();
}

void Board::setBoardDisabled()
{
    for(auto field : fields)
        field->setDisabled();
}

bool Board::logic()
{
    if(checkHorizontally() || checkVertically() || checkFromTopLeftToBottomRight() || checkFromTopRightToBottomLeft())
        return true;
    return false;
}

bool Board::boardIsFull() const
{
    for(auto field : fields)
    {
        if(field->getFieldContent() != currentPlayer->getPlayerOne() && field->getFieldContent() != currentPlayer->getPlayerTwo())
            return false;
    }
    return true;
}

size_t Board::getNumberOfOccupiedFields() const
{
    size_t occupiedFields = 0;
    for(auto field : fields)
    {
        if(field->getFieldContent() == currentPlayer->getPlayerOne() || field->getFieldContent() == currentPlayer->getPlayerTwo())
            occupiedFields++;
    }
    return occupiedFields;
}

void Board::paintWinningRow(size_t startIndex)
{
    if(paintingEnabled)
    {
        QBrush fieldsColor(QString("black"), Qt::SolidPattern);

        for(size_t column = startIndex; column < startIndex+rowSize; column++)
            fields[column]->setBrush(fieldsColor);
    }
}

void Board::paintWinningColumn(size_t startIndex)
{
    if(paintingEnabled)
    {
        QBrush fieldsColor(QString("black"), Qt::SolidPattern);
        size_t boardSize = rowSize*rowSize;

        for(size_t row = startIndex; row < boardSize; row+=rowSize)
            fields[row]->setBrush(fieldsColor);
    }
}

void Board::paintWinningFieldsFromTopLeft()
{
    if(paintingEnabled)
    {
        QBrush fieldsColor(QString("black"), Qt::SolidPattern);
        size_t boardSize = rowSize*rowSize;

        for(size_t row = 0, column = 0; row < boardSize; row += rowSize, column++)
            fields[row+column]->setBrush(fieldsColor);
    }
}

void Board::paintWinningFieldsFromTopRight()
{
    if(paintingEnabled)
    {
        QBrush fieldsColor(QString("black"), Qt::SolidPattern);
        size_t boardSize = rowSize*rowSize;

        for(size_t row = 0, column = rowSize-1; row < boardSize; row += rowSize, column--)
            fields[row+column]->setBrush(fieldsColor);
    }
}

void Board::enablePainting()
{
    paintingEnabled = true;
}

void Board::disablePainting()
{
    paintingEnabled = false;
}
