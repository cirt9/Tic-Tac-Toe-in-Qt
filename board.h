#ifndef BOARD_H
#define BOARD_H

#include <field.h>
#include <player.h>
#include <QVector>
#include <QGraphicsRectItem>
#include <QObject>
#include <QBrush>

class Board : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    static const int rowSize = 3;

    Player * currentPlayer;
    QVector<Field *> fields;
    bool paintingEnabled;

    bool checkHorizontally();
    bool checkVertically();
    bool checkFromTopLeftToBottomRight();
    bool checkFromTopRightToBottomLeft();

    void paintWinningRow(size_t startIndex);
    void paintWinningColumn(size_t startIndex);
    void paintWinningFieldsFromTopLeft();
    void paintWinningFieldsFromTopRight();

public:
    Board(int resolutionWidth = 1024, int resolutionHeight = 768, int fieldSize = 100, QString fieldColor = "blue", Player * currPlayer = nullptr, QGraphicsItem * parent = nullptr);
    ~Board();

    QVector<Field *> getFields();
    int getRowSize() const;

    void setBoardEnabled();
    void setBoardDisabled();
    void enablePainting();
    void disablePainting();

    bool logic();
    bool boardIsFull() const;
    size_t getNumberOfOccupiedFields() const;
};

#endif // BOARD_H
