#pragma once
#include "World.h"
#include "Menu.h"
#include "GameObject.h"

class Controller
{
public:
    enum t_mode { t_Menu, t_Play, t_LevelUP, t_Lose, t_FinishScreen };

    Controller();

    void run();

private:
    void runMenu();
    void runGame();
    void setGame();
    void playingMode();
    void draw();
    void handleEvents();
    void updateGameObjects();
    void gameMessage();
    void WinScreen();

    bool m_run;
    int m_mode;

    sf::RenderWindow    m_window{ { WINDOW_WIDTH, WINDOW_HEIGHT }, "Cut The Rope", sf::Style::Fullscreen };
    Menu                m_menu;
    World               m_world;
    sf::Listener        m_sounds;          // Controlls all the sounds
    sf::Clock           m_gameClock;
    sf::Vector2f        m_posStartClick,
                        m_posEndClick;
    sf::Sprite          m_levelUpMsg, 
                        m_loseMsg,
                        m_winMsg,
                        m_startMsg;
};
