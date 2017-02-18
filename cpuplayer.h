#ifndef CPUPLAYER_H
#define CPUPLAYER_H

#include <board.h>
#include <field.h>
#include <player.h>
#include <QVector>
#include <limits>
#include <QTime>

class CPUPlayer
{
private:
    Board * board;
    QString humanPlayerSign;
    QString cpuPlayerSign;

    struct Move
    {
        Move() {}
        Move(int moveScore) : score(moveScore) {}

        size_t index;
        int score;
    };

    Move minimax(QString player);
    int getIndexOfBestMoveWhenPlayerIsCPU(QVector<Move> & moves);
    int getIndexOfBestMoveWhenPlayerIsHuman(QVector<Move> & moves);
    int getCPUFirstMove() const;

public:
    CPUPlayer(Board * boardPtr, QString humanSign, QString aiPlayerSign);

    int getBestIndexToPlay(QString currentPlayer);
};

#endif // CPUPLAYER_H
