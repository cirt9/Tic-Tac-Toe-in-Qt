#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QFont>
#include <player.h>

class Field : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    static const char emptyFieldCharacter = ' ';
    QString fieldContent;
    Player * currentPlayer;
    bool enabled;

    void mousePressEvent(QGraphicsSceneMouseEvent * = nullptr);

public:
    Field(int x=0, int y=0, int size=100, QString color="white", Player * currPlayer = nullptr, QGraphicsItem * parent = nullptr);
    ~Field();

    void setFieldContent(QString content);
    QString getFieldContent() const;

    static QString getEmptyFieldCharacter();

    void setEnabled();
    void setDisabled();

    void setVisualContent();

signals:
    void roundFinished();
};

#endif // FIELD_H
