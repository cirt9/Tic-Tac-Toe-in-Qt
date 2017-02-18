#include "game.h"

Game::Game(int width, int height, QWidget * /*parent*/)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(width,height);

    initScene(0,0, width, height);
    qsrand(QTime::currentTime().msec());

    board = nullptr;
    currentPlayer = nullptr;
    cpuEnabled = false;
}

Game::~Game()
{
    currentPlayer = nullptr;
}

void Game::initScene(int x, int y, int width, int height)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(x,y,width,height);
    QBrush background("light grey");
    scene->setBackgroundBrush(background);
    setScene(scene);
}

void Game::displayMainMenu()
{
    scene->clear();

    QGraphicsTextItem * title = new QGraphicsTextItem(QString("Tic Tac Toe"));
    QFont titleFont("calibri", 80);
    title->setFont(titleFont);
    title->setPos(this->width()/2 - title->boundingRect().width()/2, this->height()/16);
    scene->addItem(title);

    QGraphicsTextItem * author = new QGraphicsTextItem(QString("Author: Bartlomiej Wojtowicz"));
    QFont authorFont("calibri", 15);
    author->setFont(authorFont);
    author->setPos(this->width() - author->boundingRect().width(), this->height() - author->boundingRect().height());
    scene->addItem(author);

    Button * singleplayerButton = new Button(QString("Player vs Player"), 350, 50, 30);
    singleplayerButton->setPos(this->width() / 2 - singleplayerButton->boundingRect().width()/2 , this->height()/3);
    singleplayerButton->setButtonColor("dark cyan");
    singleplayerButton->setHoverButtonColor("dark gray");
    connect(singleplayerButton, SIGNAL(clicked()), this, SLOT(turnOffCPUAndStart()));
    scene->addItem(singleplayerButton);

    Button * vsCPUButton = new Button(QString("Player vs CPU"), 350, 50, 30);
    vsCPUButton->setPos(this->width() / 2 - vsCPUButton->boundingRect().width()/2 , this->height()/3 + 100);
    vsCPUButton->setButtonColor("dark cyan");
    vsCPUButton->setHoverButtonColor("dark gray");
    connect(vsCPUButton, SIGNAL(clicked()), this, SLOT(turnOnCPUAndStart()));
    scene->addItem(vsCPUButton);

    Button * quitButton = new Button(QString("Quit Game"), 350, 50, 30);
    quitButton->setPos(this->width() / 2 - quitButton->boundingRect().width()/2 , this->height()/3 + 200);
    quitButton->setButtonColor("dark cyan");
    quitButton->setHoverButtonColor("dark gray");
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::turnOffCPUAndStart()
{
   cpuEnabled = false;
   prepareGame();
}

void Game::turnOnCPUAndStart()
{
   cpuEnabled = true;
   prepareGame();
}

void Game::prepareGame()
{
    scene->clear();

    currentPlayer = new Player();
    board = new Board(this->width(), this->height(), 100, QString("dark cyan"), currentPlayer);
    scene->addItem(board);
    cpuPlayer.reset(new CPUPlayer(board, QString("O"), QString("X")));

    connectBoardToSlot(SLOT(checkConditionsOfWinning()));
    if(cpuEnabled)
    {
        whoseTurn = new QGraphicsTextItem(QString("Player: X   CPU: O"));
        connectBoardToSlot(SLOT(CPUTurn()));
        decideWhoStarts();
    }
    else
    {
        whoseTurn = new QGraphicsTextItem(currentPlayer->getCurrentPlayer() + QString("'s turn"));
        connectBoardToSlot(SLOT(updateWhoseTurnText()));
    }

    QFont whoseTurnFont("calibri", 60);
    whoseTurn->setFont(whoseTurnFont);
    whoseTurn->setPos(this->width()/2 - whoseTurn->boundingRect().width()/2, 10);
    scene->addItem(whoseTurn);

    Button * returnButton = new Button(QString("Return"), 120, 70, 30);
    returnButton->setPos(10,this->height() - returnButton->boundingRect().height() - 10);
    returnButton->setButtonColor("dark cyan");
    returnButton->setHoverButtonColor("dark gray");
    connect(returnButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
    scene->addItem(returnButton);
}

void Game::decideWhoStarts()
{
    int decision = rand() % 2;

    if(decision == 1)
        CPUTurn();
}

void Game::CPUTurn()
{
    if(board->logic() || board->boardIsFull())
        checkConditionsOfWinning();
    else
    {
        currentPlayer->changeCurrentPlayer();
        QVector<Field *> fields = board->getFields();

        size_t cpuPlayIndex = cpuPlayer->getBestIndexToPlay(currentPlayer->getCurrentPlayer());

        fields[cpuPlayIndex]->setFieldContent(currentPlayer->getCurrentPlayer());
        fields[cpuPlayIndex]->setVisualContent();
        checkConditionsOfWinning();
        if(board->getNumberOfOccupiedFields() == 1)
            currentPlayer->changeCurrentPlayer();
    }
}

void Game::checkConditionsOfWinning()
{
    if(board->logic())
        displayGameOverWindow(false);
    else if(board->boardIsFull())
        displayGameOverWindow(true);
}

void Game::updateWhoseTurnText()
{
    QString player;

    if(currentPlayer->getCurrentPlayer() == currentPlayer->getPlayerOne())
        player = currentPlayer->getPlayerTwo() + QString("'s turn");

    else if(currentPlayer->getCurrentPlayer() == currentPlayer->getPlayerTwo())
        player = currentPlayer->getPlayerOne() + QString("'s turn");

    whoseTurn->setPlainText(player);
}

void Game::displayGameOverWindow(bool isBoardFull)
{
    board->setBoardDisabled();
    drawPanel(0, 0, this->width(), this->height(), Qt::black, 0.9);

    QString result;
    if(isBoardFull)
        result = "It's a tie";
    else
        result = currentPlayer->getCurrentPlayer() + " Wins";

    QGraphicsTextItem * resultText = new QGraphicsTextItem(result);
    QFont resultFont("calibri", 60);
    resultText->setFont(resultFont);
    resultText->setPos(this->width()/2 - resultText->boundingRect().width()/2, this->height()/16);
    resultText->setDefaultTextColor(Qt::white);
    scene->addItem(resultText);

    Button * playAgainButton = new Button(QString("Play Again"), 380, 70, 30);
    playAgainButton->setPos(this->width() / 2 - playAgainButton->boundingRect().width()/2 , this->height()/2 - 100);
    playAgainButton->setButtonColor("dark cyan");
    playAgainButton->setHoverButtonColor("dark gray");
    if(cpuEnabled)
        connect(playAgainButton, SIGNAL(clicked()), this, SLOT(turnOnCPUAndStart()));
    else
        connect(playAgainButton, SIGNAL(clicked()), this, SLOT(turnOffCPUAndStart()));
    scene->addItem(playAgainButton);

    Button * backToMainMenuButton = new Button(QString("Back To Main Menu"), 380, 70, 30);
    backToMainMenuButton->setPos(this->width() / 2 - backToMainMenuButton->boundingRect().width()/2 , this->height()/2);
    backToMainMenuButton->setButtonColor("dark cyan");
    backToMainMenuButton->setHoverButtonColor("dark gray");
    connect(backToMainMenuButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
    scene->addItem(backToMainMenuButton);
}

void Game::connectBoardToSlot(const char * slot)
{
    QVector<Field *> fields = board->getFields();

    for(auto field : fields)
        connect(field, SIGNAL(roundFinished()), this, slot);
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    QGraphicsRectItem * panel = new QGraphicsRectItem(x,y,width,height);
    QBrush panelColor(color, Qt::SolidPattern);
    panel->setBrush(panelColor);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}
