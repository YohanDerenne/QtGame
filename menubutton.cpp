#include "menubutton.h"
#include <QFont>

MenuButton::MenuButton(QString text)
{
    this->setText(text);
    this->resize(400,100);
    QFont font;
    font.setBold(true);
    font.setPixelSize(29);
    setFont(font);
}
