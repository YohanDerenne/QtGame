#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>
#include "configuration.h"
#include "menubutton.h"
#include "map.h"
#include <QDebug>

/**
 * \file menu.h
 * \brief Class of the game control menu.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class Menu : public QGraphicsScene
{
public:
    /**
     * \fn Menu()
     * \brief Constructor of the Menu class
     * Set up the navigation menu
     */
    Menu();
    /**
     * \fn ~Menu()
     * \brief destructor of the Info class
     * Removes objects from the navigation menu
     */
    ~Menu();


    /**
     * \fn QList<MenuButton *> getButtonList() const
     * \brief Accessor of the "buttonList" attribute.
     * \return a QList<MenuButton *> value of the buttonList attribute of the "Menu" object.
     */
    QList<MenuButton *> getButtonList() const;


    /**
     * \fn MenuButton *getQuitBtn() const
     * \brief Accessor of the "QuitBtn" attribute.
     * \return a MenuButtonThe object value of the QuitBtn attribute of the "Menu"
     */
    MenuButton *getQuitBtn() const;

private:
    QList<MenuButton *> buttonList;
    MenuButton * QuitBtn;

};

#endif // MENU_H
