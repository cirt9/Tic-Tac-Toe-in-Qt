#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QFont>
#include <QBrush>
#include <QGraphicsRectItem>
#include <button.h>
#include <player.h>
#include <board.h>
#include <QVector>
#include <field.h>
#include <cpuplayer.h>
#include <QScopedPointer>
#include <QTime>

class Game : public QGraphicsView
{
    Q_OBJECT
private:
    QGraphicsScene * scene;
    Board * board;
    Player * currentPlayer;
    QScopedPointer<CPUPlayer> cpuPlayer;
    QGraphicsTextItem * whoseTurn;
    bool cpuEnabled;

    void initScene(int x, int y, int width, int height);
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity = 1.0);

    void connectBoardToSlot(const char * slot);
    void displayGameOverWindow(bool isBoardFull);
    void prepareGame();
    void decideWhoStarts();

private slots:
    void turnOffCPUAndStart();
    void turnOnCPUAndStart();
    void CPUTurn();
    void checkConditionsOfWinning();
    void updateWhoseTurnText();

public:
    Game(int width = 1024, int height = 768, QWidget * /*parent*/ = nullptr);
    ~Game();

public slots:
    void displayMainMenu();

};

#endif // GAME_H
