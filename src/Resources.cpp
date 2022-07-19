#include <fstream>
#include <stdexcept>

#include "Resources.h"

//---------------------------------- Const Section ------------------------------------

const std::string TXTURE_ERR = "Failed to load texture.\nPress any key to continue...",
				  FONT_ERR = "Failed to load font.\nPress any key to continue...";

//---------------------------------- Namespace Section --------------------------------
namespace
{
	AnimationData readAnimation(std::string fileName)
		// get a file name the contain the coordinate of the animmation;
	{
		auto file = std::ifstream(fileName);
		int numAnime,							// num of the animation in the file
			numOfFrame;							// coordinate for single frame 

		file >> numAnime;
		auto animations = AnimationData{};

		for (int animationKey = 0; animationKey < numAnime; animationKey++)
		{
			file >> numOfFrame;
			sf::Vector2i size,					// x for width, y for heigh
						 currentStart;			// coordinate in the pictute
			sf::Vector2f originStart;

			for (int frameIndex = 0; frameIndex < numOfFrame; frameIndex++)
			{
				file >> currentStart.x >> currentStart.y >> size.x >> size.y;
				animations.m_animeMap[animationKey].emplace_back(currentStart, size);
			}
		}
		return animations;
	}
}

Resources::Resources()
{
	loadTextures();
	loadFonts();
	loadSounds();
	loadAnimation();
}

/* Clone the texture so each object will hold a copy of map
 * Be in use when we are needed to erase something from map
 * such as : Bubble / Star.	*/
Resources& Resources::instance()
{
	// The object inst is created once and can be reached everywhere in the game
	try
	{
		static Resources inst;
		return inst;
	}
	catch (std::exception& e)
	{
		sf::Font font;
		font.loadFromFile("mangat.ttf");			// There is no default font in sf::Text 

		sf::RenderWindow window(sf::VideoMode(1200, 500), "Exception", sf::Style::Default | sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
		sf::Text exc;
		exc.setFont(font);
		exc.setCharacterSize(50);
		exc.setPosition({ 20, 20 });
		exc.setFillColor(sf::Color::White);
		exc.setString(e.what());

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed: window.close(); exit(EXIT_FAILURE); break;

				case sf::Event::KeyPressed: window.close(); exit(EXIT_FAILURE); break;

				case sf::Event::MouseButtonReleased: window.close(); exit(EXIT_FAILURE); break;
				}
			}

			window.clear();
			window.draw(exc);
			window.display();
		}
	}
}

const sf::Texture& Resources::getTexture(Textures index_texture) const
{
	return m_texture[(int)index_texture];
}

const sf::Font& Resources::getFont(Fonts index_font) const
{
	return m_font[(int)index_font];
}

sf::Music& Resources::getMenuMusic()
{
	return m_menuMusic;
}

sf::Music& Resources::getGameMusic()
{
	return m_gameMusic;
}

// Plays the wanted sound effect 
void Resources::playSound(int index)
{
	m_sounds[index].play();
}

const sf::Sound& Resources::getSound(int index_sound) const
{
	return m_sounds[index_sound];
}

void Resources::configureText(sf::Text& txt, sf::Color fillColor, sf::Color outlineColor) const
{
	// Set parameters to print data text while playing
	txt.setFont(Resources::instance().getFont(Resources::Fonts::f_Mangat));
	txt.setColor(fillColor);
	txt.setOutlineThickness(2);
	txt.setOutlineColor(outlineColor);
	txt.setCharacterSize(37);
	txt.setLetterSpacing(2);
}

void Resources::loadSounds()
{
	// If one of the sounds could not open, do not throw an exceptions,
	// the game can continue without it.
	m_menuMusic.openFromFile("The Chordettes - Lollipop(Menu Music).wav");
	m_gameMusic.openFromFile("50Cent - Candy Shop(Instrumental Remix)(Game Music).wav");

	m_soundBuffer.resize((int)Sounds::s_Total);

	m_soundBuffer[(int)Sounds::s_ButtonClicked].loadFromFile("ButtonClick.wav");
	m_soundBuffer[(int)Sounds::s_TeleportAlakazam].loadFromFile("AlakazamTeleport.wav");
	m_soundBuffer[(int)Sounds::s_ByeBye].loadFromFile("ByeBye.wav");
	m_soundBuffer[(int)Sounds::s_KnockDoor].loadFromFile("DoorKnock.wav");
	m_soundBuffer[(int)Sounds::s_DoorOpen].loadFromFile("DoorOpen.wav");
	m_soundBuffer[(int)Sounds::s_LoseCartoon].loadFromFile("LoseCartoon.wav");
	m_soundBuffer[(int)Sounds::s_WinYummy].loadFromFile("WinYummyEffect.wav");
	m_soundBuffer[(int)Sounds::s_WinYay].loadFromFile("WinYay.wav");
	m_soundBuffer[(int)Sounds::s_StarCollected].loadFromFile("StarCollectedEffect.wav");
	m_soundBuffer[(int)Sounds::s_Bubble2Candy].loadFromFile("Bubble2CandyEffect.wav");
	m_soundBuffer[(int)Sounds::s_BubblePop].loadFromFile("BubblePopEffect.wav");
	m_soundBuffer[(int)Sounds::s_Blowing].loadFromFile("BlowingEffect.wav");
	m_soundBuffer[(int)Sounds::s_GravityChange].loadFromFile("GravityEffect.wav");
	m_soundBuffer[(int)Sounds::s_WaitingYooHoo].loadFromFile("WaitingYoohooEffect.wav");
	m_soundBuffer[(int)Sounds::s_CutRope].loadFromFile("CutRopeEffect.wav");
	m_soundBuffer[(int)Sounds::s_LoseOhNo].loadFromFile("OhNoEffect.wav");
	m_soundBuffer[(int)Sounds::s_CandyCrash].loadFromFile("CandyCrashEffect.wav");

	for (int i = 0; i < m_soundBuffer.size(); ++i)
		m_sounds.push_back(sf::Sound(m_soundBuffer[i]));
}

void Resources::loadTextures()
{
	m_texture.resize((int)Textures::t_Total);

	if (!m_texture[(int)Textures::t_Candy].loadFromFile("AnimationCandy.png")		   ||
		!m_texture[(int)Textures::t_Frog].loadFromFile("AnimationFrog.png")			   ||
		!m_texture[(int)Textures::t_Blower].loadFromFile("AnimationBlower.png")		   ||
		!m_texture[(int)Textures::t_StarScore].loadFromFile("AnimationStarScore.png")  ||
		!m_texture[(int)Textures::t_Star].loadFromFile("AnimationStar.png")			   ||
		!m_texture[(int)Textures::t_RopeBase].loadFromFile("RopeBase.png")			   ||
		!m_texture[(int)Textures::t_Bubble].loadFromFile("Bubble.png")				   ||
		!m_texture[(int)Textures::t_Rope].loadFromFile("Rope.png")					   ||
		!m_texture[(int)Textures::t_Spike].loadFromFile("Spike.png")				   ||
		!m_texture[(int)Textures::t_HatPort].loadFromFile("HatTeleport.png")		   ||
		!m_texture[(int)Textures::t_Limit].loadFromFile("Limit.png")				   ||
		!m_texture[(int)Textures::t_GravityCange].loadFromFile("GravityCange.png")	   ||

		!m_texture[(int)Textures::t_HelpData].loadFromFile("HelpData.png")			   ||
		!m_texture[(int)Textures::t_Start].loadFromFile("Start.png")				   ||
		!m_texture[(int)Textures::t_Help].loadFromFile("Help.png")					   ||
		!m_texture[(int)Textures::t_Exit].loadFromFile("Exit.png")					   ||
		!m_texture[(int)Textures::t_Back].loadFromFile("Back.png")					   ||
		!m_texture[(int)Textures::t_Reset].loadFromFile("Reset.png")				   ||

		!m_texture[(int)Textures::t_MenuBackground].loadFromFile("MenuBackground.png") ||
		!m_texture[(int)Textures::t_GameBackground].loadFromFile("GameBackground.png") ||

		!m_texture[(int)Textures::t_StartMsg].		loadFromFile("StartMsg.png")	   ||
		!m_texture[(int)Textures::t_LevelUpMsg].	loadFromFile("LevelUpMsg.png")	   ||
		!m_texture[(int)Textures::t_LoseMsg].		loadFromFile("LoseMsg.png")		   ||
		!m_texture[(int)Textures::t_WinMsg].		loadFromFile("WinMsg.png"))

		throw std::runtime_error(TXTURE_ERR);
}

void Resources::loadFonts()
{
	m_font.resize((int)Fonts::f_Total);
	if (!m_font[(int)Fonts::f_Mangat].loadFromFile("mangat.ttf")						||
		!m_font[(int)Fonts::f_CandyFont].loadFromFile("SweetNight.otf"))
		throw std::runtime_error(FONT_ERR);
}

void Resources::loadAnimation()
{
	m_data.resize((int)Object::o_Total);

	m_data[(int)Object::o_Candy]		  = readAnimation("Candy.txt");
	m_data[(int)Object::o_Frog]			  = readAnimation("Frog.txt");
	m_data[(int)Object::o_Blower]		  = readAnimation("Blower.txt");
	m_data[(int)Object::o_Star]			  = readAnimation("Star.txt");
	m_data[(int)Object::o_StarScore]	  = readAnimation("StarScore.txt");
	m_data[(int)Object::o_GameBackground] = readAnimation("GameBackground.txt");
}
