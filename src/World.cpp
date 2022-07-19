#include "World.h"

World::World()
	: m_animation(Resources::instance().animationData((int)Resources::Object::o_GameBackground), m_gameBackground),
	  m_isLvlRunning(false), m_isReset(false), m_isLose(false),
	  m_ptrFrog(nullptr), m_numOfRopes(INITIALIZE), m_world(GRAVITY)
	
{
	m_gameBackground.setTexture(Resources::instance().getTexture(Resources::Textures::t_GameBackground));
	m_animation.action(Action::A_Level1);
}

World::~World()
{
}

void World::drawWorld(sf::RenderWindow& window, sf::Time deltaTime)
{
	window.draw(m_gameBackground);

	for (auto& singleStatic : m_NonPhysicsObjV)
		singleStatic->drawObject(window);

	for (auto& rope : m_ropesV)
		if (rope.getBody())
			rope.drawRope(window);

	if (!m_candy.getDeleteCandy())
		m_candy.drawObject(window);

	m_dataToolBar.drawDataToolBar(window);
	m_mouseTool.drawMouseMarker(window, deltaTime);
}

//Update board with every movement 
void World::updateWorld(sf::Time deltaTime)
{
	m_dataToolBar.setAction(m_candy.getStarScore());
	m_dataToolBar.updateDataToolBar(deltaTime, m_levelManager);
	m_candy.setCandyOnTeleport(false);
	m_candy.update(deltaTime);
	m_lvlData._timeLeft -= deltaTime.asSeconds();

	// Erase sprite according to term - if object is disposed and not our lovely Frog Om Num
	m_NonPhysicsObjV.erase(std::remove_if(
		m_NonPhysicsObjV.begin() + 1, m_NonPhysicsObjV.end(),
		[](auto& m_NonPhysicsObjV)
		{
			//Return answer if this static object needs to be erased.
			return m_NonPhysicsObjV->isDisposed();
		}), m_NonPhysicsObjV.end());

	if (m_ptrFrog->isDisposed() && m_candy.isEnded())
		m_isLvlRunning = false;

	if (m_candy.isDisposed() ||
		(m_lvlData._timeLeft < 0 && m_levelManager.isHaveTimer()))
		m_isLose = true;

	for (auto& i : m_ropesV)
		if (i.isDisposed() && i.getBody())
		{
			i.eraseRope(&m_world);
			i.destroyBody();
			--m_numOfRopes;
		}

	if (m_numOfRopes > 0)
		m_candy.setCandy2Rope(true);
	else
		m_candy.setCandy2Rope(false);

	if (m_candy.isCandyGravity())
		m_world.SetGravity({ 0,-10 });
	else
		m_world.SetGravity(GRAVITY);		

	m_candy.setAmountOfRope(m_numOfRopes);

	for (auto& stat : m_NonPhysicsObjV)
	{
		stat->update(deltaTime);
		processCollision(m_candy, *stat);
	}

	if (!m_candy.getCandyOnTeleport())
		m_candy.setCandyTeleported(false);
	else
		for (auto& i : m_ropesV)
			i.setDisposed(true);
}

void World::handleClick(sf::Vector2f posStart, sf::Vector2f posEnd)
{
	if (!m_candy.isCandyLost() && !m_ptrFrog->isDisposed())
		if (sqrt(pow(posEnd.x - posStart.x, 2) + pow(posEnd.y - posStart.y, 2)) < 5)
		{
			for (auto& stat : m_NonPhysicsObjV)
				if (stat->checkContain(posStart))
					stat->setClicked(true);

			switch (m_dataToolBar.checkClick(posStart))
			{
			case RESET_INDEX:
				m_isReset = true;
				updateLevel();
				break;

			default:
				break;
			}
			m_mouseTool.eraseLine();
		}
		else
		{
			m_mouseTool.CreateLine(posStart, posEnd);

			for (auto& i : m_ropesV)
				processCollision(m_mouseTool, i);
		}
}

bool World::updateLevel()
{
	//first-> enter teleport, (x,y)->position, z->angel
	//second-> exit teleport, (x,y)->position, z->angel 
	std::pair<sf::Vector3f, sf::Vector3f> teleport;
	auto ground = sf::RectangleShape();
	unsigned int type, angle;
	sf::Vector2f loc;
	Rope rope;

	if (!m_isLose && !m_isReset)
		m_isLvlRunning = m_levelManager.scanBoardFile();

	if (m_isLvlRunning)
	{
		resetData();
		m_lvlData._timeLeft = m_levelManager.getTimer();
		std::vector<std::pair<sf::Vector2f, sf::Vector2f>> map = m_levelManager.getCurrentMapVec();

		for (int i = 0; i < map.size(); ++i)
		{
			loc.x = map[i].first.x;
			loc.y = map[i].first.y;
			type = map[i].second.x;
			angle = map[i].second.y;
			switch (type)
			{
			case FROG:
				m_NonPhysicsObjV.push_back(std::make_unique<Frog>(loc));
				m_ptrFrog = m_NonPhysicsObjV[m_NonPhysicsObjV.size() - 1].get();
				break;

			case LIMIT:
				if (loc.x == WINDOW_WIDTH / 2)
					m_NonPhysicsObjV.push_back(std::make_unique<Limit>(loc, false));
				else
					m_NonPhysicsObjV.push_back(std::make_unique<Limit>(loc, true));
				break;

			case CANDY:
				if (m_candy.getBody() == nullptr)
					m_candy.createBody(&m_world, loc, false);

				m_candy.setPosition(loc);
				break;

			case ROPE:
				rope.createBody(&m_world, loc, true);
				rope.setPosition(loc);
				rope.createRope(rope.getBody(), angle, m_candy.getBody(), &m_world,
								rope.getBody()->GetPosition(), m_candy.getBody()->GetPosition());

				m_ropesV.push_back(rope);
				++m_numOfRopes;
				break;

			case ROPE_BASE:
				m_NonPhysicsObjV.push_back(std::make_unique<RopeBase>(loc));
				break;

			case STAR:
				m_NonPhysicsObjV.push_back(std::make_unique<Star>(loc));
				break;

			case BUBBLE:
				m_NonPhysicsObjV.push_back(std::make_unique<Bubble>(loc));
				break;

			case SPIKE:
				m_NonPhysicsObjV.push_back(std::make_unique<Spike>(loc, angle));
				break;

			case BLOWER:
				m_NonPhysicsObjV.push_back(std::make_unique<Blower>(loc, angle));
				break;

			case GRAVITY_SET:
				m_NonPhysicsObjV.push_back(std::make_unique<GravityChange>(loc));
				break;

			case TELEPORT:
				teleport.first.x = loc.x, teleport.first.y = loc.y, teleport.first.z = angle;
				teleport.second.x = map[++i].first.x, teleport.second.y = map[i].first.y, teleport.second.z = map[i].second.y;
				m_NonPhysicsObjV.push_back(std::make_unique<HatPort>(teleport.first, teleport.second));
				m_NonPhysicsObjV.push_back(std::make_unique<HatPort>(teleport.second, teleport.first));
				break;
			default:
				break;
			}
		}
	}

	return m_isLvlRunning;
}

void World::setAction(int action)
{
	switch (action)
	{
	case A_Level1:
		m_animation.action(Action::A_Level1);
		break;
	case A_Level2:
		m_animation.action(Action::A_Level2);
		break;
	case A_Level3:
		m_animation.action(Action::A_Level3);
		break;
	case A_Level4:
		m_animation.action(Action::A_Level4);
		break;
	default:
		break;
	}
}

void World::stepBox2dWorld()
{
	m_world.Step(TIMESTEP, VELOCITYITERATIONS, POSITIONITERATIONS);

	auto position = m_candy.getBody()->GetPosition();
	auto angle = m_candy.getBody()->GetAngle();
	m_candy.setPosition(convertb2Vec2ToVec2f(position));

	for (auto& rope : m_ropesV)
		if (rope.getBody())
			rope.updateRope();
}

//Type conversion funcs
sf::Vector2f World::convertb2Vec2ToVec2f(b2Vec2 pos) const { return sf::Vector2f({ pos.x , pos.y }); }

void World::resetData()
{
	resetCandy();
	resetMembers();

	if (!m_isLose && !m_isReset)
		setAction(m_levelManager.getLevelNumber() - 1);
}

void World::resetCandy()
{
	m_candy.initializeStarScore();
	m_candy.setDisposed(false);
	m_candy.setDeleteCandy(false);
	m_candy.setCandyLost(false);
	m_candy.setCandyBubbled(false);
	m_candy.setCandy2Rope(false);
	m_candy.setCandyGravity(false);
	m_candy.setEnded(false);

	if (m_candy.getBody())
	{
		m_world.DestroyBody(m_candy.getBody());
		m_candy.destroyBody();
	}
}
void World::resetMembers()
{
	m_lvlData._timeLeft = m_levelManager.getTimer();
	m_dataToolBar.resetDataToolBar();
	m_ptrFrog = nullptr;
	m_isLose = false;
	m_isReset = false;
	m_ropesV.clear();
	m_NonPhysicsObjV.clear();
	m_numOfRopes = INITIALIZE;

	for (auto& i : m_ropesV)
		if (i.getBody())
		{
			i.eraseRope(&m_world);
			i.destroyBody();
		}
}

void World::resetLevel()
{
	m_levelManager.resetLevelManager();
}

bool World::isLevelRunning() const
{
	return m_isLvlRunning;
}

void World::playGameMusic() const
{
	Resources::instance().getGameMusic().setLoop(true);
	Resources::instance().getGameMusic().setVolume(65.f);
	Resources::instance().getGameMusic().play();
}

bool World::getIsLose() const
{
	return m_isLose;
}