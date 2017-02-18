#include "cpuplayer.h"

CPUPlayer::CPUPlayer(Board *boardPtr, QString humanSign, QString aiPlayerSign)
{
    board = boardPtr;
    humanPlayerSign = humanSign;
    cpuPlayerSign = aiPlayerSign;
}

int CPUPlayer::getBestIndexToPlay(QString currentPlayer)
{
    if(board->getNumberOfOccupiedFields() == 0)
        return getCPUFirstMove();

    board->disablePainting();

    Move move = minimax(currentPlayer);

    board->enablePainting();
    return move.index;
}

int CPUPlayer::getCPUFirstMove() const
{
    int corner = rand() % 4+1;

    if(corner == 1)
        return 0;
    if(corner == 2)
        return board->getRowSize() - 1;
    if(corner == 3)
        return board->getRowSize() * (board->getRowSize()-1);
    if(corner == 4)
        return board->getRowSize() * board->getRowSize() - 1;
    return 0;
}

CPUPlayer::Move CPUPlayer::minimax(QString player)
{
    if(board->logic())
    {
        if(player == humanPlayerSign)
            return Move(10);
        else
            return Move(-10);
    }
    else if(board->boardIsFull())
        return Move(0);

    QVector<Move> moves;
    QVector<Field *> fields = board->getFields();

    for(int i=0; i < fields.size(); i++)
    {
        if(fields[i]->getFieldContent() == Field::getEmptyFieldCharacter())
        {
            Move move;
            move.index = i;

            fields[i]->setFieldContent(player);

            if(player == cpuPlayerSign)
                move.score = minimax(humanPlayerSign).score;
            else
                move.score = minimax(cpuPlayerSign).score;

            moves.push_back(move);
            fields[i]->setFieldContent(Field::getEmptyFieldCharacter());
        }
    }

    int bestMoveIndex = 0;

    if(player == cpuPlayerSign)
        bestMoveIndex = getIndexOfBestMoveWhenPlayerIsCPU(moves);
    else
        bestMoveIndex = getIndexOfBestMoveWhenPlayerIsHuman(moves);

    return moves[bestMoveIndex];
}

int CPUPlayer::getIndexOfBestMoveWhenPlayerIsCPU(QVector<Move> & moves)
{
    int bestMove = 0;
    int bestScore = std::numeric_limits<int>::min();

    for(int i=0; i<moves.size(); i++)
    {
        if(moves[i].score > bestScore)
        {
            bestMove = i;
            bestScore = moves[i].score;
        }
    }

    return bestMove;
}

int CPUPlayer::getIndexOfBestMoveWhenPlayerIsHuman(QVector<CPUPlayer::Move> &moves)
{
    int bestMove = 0;
    int bestScore = std::numeric_limits<int>::max();

    for(int i=0; i<moves.size(); i++)
    {
        if(moves[i].score < bestScore)
        {
            bestMove = i;
            bestScore = moves[i].score;
        }
    }

    return bestMove;
}
