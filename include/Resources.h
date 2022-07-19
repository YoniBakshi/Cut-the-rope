#pragma once

#include <vector>
#include <sstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "AnimationData.h"

class Resources
{
public:
	enum class Object
	{
		o_Frog,
		o_Candy,
		o_Limit,
		o_Rope,
		o_RopeBase,
		o_Star,
		o_Spike,
		o_Teleport,
		o_TeleportAngle,
		o_Blower,
		o_Bubble,
		o_StarScore,
		o_GameBackground,
		o_Total
	};

	enum class Textures
	{
		t_Frog,
		t_Candy,
		t_Limit,
		t_Rope,
		t_RopeBase,
		t_Star,
		t_Spike,
		t_HatPort,
		t_Blower,
		t_Bubble,
		t_GravityCange,
		t_MenuBackground,
		t_GameBackground,
		t_HelpData,
		t_StartMsg,
		t_LevelUpMsg,
		t_LoseMsg,
		t_WinMsg,
		t_Start,
		t_Help,
		t_Exit,
		t_Back,
		t_Reset,
		t_StarScore,
		t_Total
	};

	enum class Fonts
	{
		f_Mangat,
		f_CandyFont,
		f_Total
	};

	enum class Sounds
	{
		s_ButtonClicked,
		s_TeleportAlakazam,
		s_DoorOpen,
		s_KnockDoor,
		s_LoseOhNo,
		s_LoseCartoon,
		s_WinYummy,
		s_WinYay,
		s_Blowing,
		s_GravityChange,
		s_StarCollected,
		s_CandyCrash,
		s_BubblePop,
		s_Bubble2Candy,
		s_WaitingYooHoo,
		s_CutRope,
		s_ByeBye,
		s_Total
	};
	
	~Resources() = default;

	static Resources& instance();
	const sf::Texture& getTexture(Textures index_texture) const;
	const sf::Font& getFont(Fonts index_font)			  const;
	const sf::Sound& getSound(int index_sound)			  const;
	sf::Music& getMenuMusic();											// no const - return referenced member
	sf::Music& getGameMusic();											// no const - return referenced member
	void playSound(int index);
	void configureText(sf::Text& txt, sf::Color fillColor, sf::Color outlineColor) const;

	const AnimationData& animationData(int object) { return m_data[object]; }

private:
	//Constructor
	Resources();
	Resources(const Resources&) = default;				//Make sure - Cancel the option to clone or to  
	Resources& operator= (const Resources&) = default;

	void loadSounds();
	void loadTextures();
	void loadFonts();
	void loadAnimation();

	std::vector<sf::SoundBuffer> m_soundBuffer;
	std::vector<sf::Sound>		 m_sounds;
	std::vector<sf::Texture>	 m_texture;
	std::vector<sf::Font>		 m_font;

	std::vector<AnimationData>	 m_data;				// The animation data for each object

	sf::Music					 m_menuMusic;
	sf::Music					 m_gameMusic;
};
