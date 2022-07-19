//---------------------------------- Include Section -----------------------------------
#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

//---------------------------------- Class Section -----------------------------------
struct AnimationData
{
    //Each animation has a frame sheet that is represented by a Rect, and there's a vector saving all animations
    //and is reffered by an enum (int)
    using ListType = std::vector<sf::IntRect>;
    using DataType = std::unordered_map<int, ListType>;
    DataType m_animeMap;                                //Holds the frames sheet of the animation
};
