#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QPushButton>

/**
 * \file menubutton.h
 * \brief Class of the buttons of the game control menu.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class MenuButton : public QPushButton
{
public:
    /**
     * \fn MenuButton(QString text)
     * \brief Constructor of the MenuButton class
     * Reset the navigation menu buttons
     */
    MenuButton(QString text);
};

#endif // MENUBUTTON_H
