#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player
{
private:
    QString currentPlayer;
    static const char playerOneCharacter = 'X';
    static const char playerTwoCharacter = 'O';

public:
    Player(int startingPlayer = 1);
    ~Player(){;}

    QString getPlayerOne() const;
    QString getPlayerTwo() const;
    QString getCurrentPlayer() const;
    void changeCurrentPlayer();
};

#endif // PLAYER_H
