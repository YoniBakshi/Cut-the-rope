//---------------------------------- Include Section -----------------------------------
#include "Animation.h"

//---------------------------------- Const Section -------------------------------------
const auto AnimationTime = sf::seconds(0.1f); // the speed of the animation's frames
const float ANI_TIME = 0.2;

//---------------------------------- Class Implementation ------------------------------

// constructor - initialize all the members
Animation::Animation(const AnimationData& data, sf::Sprite& sprite)
	: m_data(data), m_sprite(sprite),
	  m_action(INITIALIZE), m_frameIndex(INITIALIZE), m_end(false)
{
	updateFrame();
}

//show the action out of the frames sheet
void Animation::action(int action)
{
	if (m_action == action)
		return;

	m_action = action;
	m_frameIndex = INITIALIZE;
	m_end = false;
	updateFrame();
}

//update the current animation according to the time that passed
void Animation::update(sf::Time delta)
{
	m_elapsed += delta;
	auto AnimTime = AnimationTime;

	if (m_elapsed >= AnimTime)
	{
		m_elapsed -= AnimTime;
		++m_frameIndex;
		m_frameIndex %= m_data.m_animeMap.find(m_action)->second.size();
		if (m_frameIndex == m_data.m_animeMap.find(m_action)->second.size() - 1)
			m_end = true;

		updateFrame();
	}
}

//returns true when thr frames sheet reached its end
bool Animation::animationEnded() const { return m_end; }

//update sprite according to the current frame out of the frames sheet
void Animation::updateFrame()
{
	m_sprite.setTextureRect(m_data.m_animeMap.find(m_action)->second[m_frameIndex]);
}