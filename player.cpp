#include "player.h"

Player::Player(int startingPlayer)
{
    if(startingPlayer == 1)
        currentPlayer = static_cast<QString>(playerOneCharacter);
    else
        currentPlayer = static_cast<QString>(playerTwoCharacter);
}

QString Player::getPlayerOne() const
{
    return static_cast<QString>(playerOneCharacter);
}

QString Player::getPlayerTwo() const
{
    return static_cast<QString>(playerTwoCharacter);
}

QString Player::getCurrentPlayer() const
{
    return currentPlayer;
}

void Player::changeCurrentPlayer()
{
    if(currentPlayer == static_cast<QString>(playerOneCharacter))
        currentPlayer = static_cast<QString>(playerTwoCharacter);

    else if(currentPlayer == static_cast<QString>(playerTwoCharacter))
        currentPlayer = static_cast<QString>(playerOneCharacter);
}
