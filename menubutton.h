#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QPushButton>

/**
 * \file menubutton.h
 * \brief Class of the buttons of the menu.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class MenuButton : public QPushButton
{
public:
    /**
     * \fn MenuButton(QString text)
     * \brief Constructor of the MenuButton class
     * \param text, text of the button
     * Reset the buttons
     */
    MenuButton(QString text);
};

#endif // MENUBUTTON_H
