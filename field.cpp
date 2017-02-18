#include "field.h"

Field::Field(int x, int y, int size, QString color, Player *currPlayer, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    currentPlayer = currPlayer;
    fieldContent = static_cast<QString>(emptyFieldCharacter);
    enabled = true;
    setRect(x, y, size, size);

    QBrush fieldColor(color, Qt::SolidPattern);
    setBrush(fieldColor);
}

Field::~Field()
{
    currentPlayer = nullptr;
}

void Field::setFieldContent(QString content)
{
    fieldContent = content;
}

QString Field::getFieldContent() const
{
    return fieldContent;
}

QString Field::getEmptyFieldCharacter()
{
    return static_cast<QString>(emptyFieldCharacter);
}

void Field::setEnabled()
{
    enabled = true;
}

void Field::setDisabled()
{
    enabled = false;
}

void Field::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    if(fieldContent == static_cast<QString>(emptyFieldCharacter) && enabled)
    {
        fieldContent = currentPlayer->getCurrentPlayer();
        setVisualContent();
        emit roundFinished();
        currentPlayer->changeCurrentPlayer();
    }
}

void Field::setVisualContent()
{
    QGraphicsTextItem * content = new QGraphicsTextItem(fieldContent, this);
    QFont textFont("calibri", rect().width() * 4/5);
    content->setFont(textFont);
    content->setPos(rect().x() + rect().width()/2 - content->boundingRect().width()/2, rect().y() + rect().height()/2 - content->boundingRect().height()/2);
}

