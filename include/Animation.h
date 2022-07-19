
//---------------------------------- Include Section-----------------------------------
#pragma once
#include <SFML/Graphics.hpp>

#include "AnimationData.h"
#include "Resources.h"
#include "Macros.h"

//---------------------------------- Class Section-------------------------------------

class Animation
{
public:
    Animation(const AnimationData&, sf::Sprite&);

    void action(int action);
    void update(sf::Time delta);
    bool animationEnded() const;

private:
    void updateFrame();

    int m_frameIndex;               //The current frame out of the animation sheet
    int m_action;                   //Objects's action enum
    bool m_end;                     //True when reaching the end of an animation sheet
    const AnimationData& m_data;    //Saves the object's data of animation
    sf::Sprite& m_sprite;           //The sprite that shows the current frame out of the animation sheet

    sf::Time m_elapsed = {};        //The time that passed since we last checked
};

