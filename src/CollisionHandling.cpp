#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

#include "CollisionHandling.h"
#include "Star.h"
#include "Frog.h"
#include "Rope.h"
#include "Spike.h"
#include "Candy.h"
#include "Limit.h"
#include "Bubble.h"
#include "Blower.h"
#include "HatPort.h"
#include "RopeBase.h"
#include "MouseTool.h"
#include "GravityChange.h"

namespace // anonymous namespace — the standard way to make function "static"
{

	// Primary collision-processing functions
	void candyFrog(GameObject& candy, GameObject& frog)
	{
		// To get the actual types and use them:
		Candy& can = static_cast<Candy&>(candy);
		Frog& fro  = static_cast<Frog&>(frog);

		if (fro.checkCollision(can, fro) && fro.getAction() != fro.A_Win)
		{
			Resources::instance().playSound((int)Resources::Sounds::s_WinYummy);
			fro.setDisposed(true);
			can.getBody()->SetAwake(false);
			fro.setAction(fro.A_Win);
			can.setDeleteCandy(true);
		}

		if (fro.getAction() == fro.A_Win && fro.getEnded())
			can.setEnded(true);
		if (can.checkShapeCollision(fro.getFrogZone()) && fro.getAction() != fro.A_Win)
			fro.setAction(fro.A_Almost);
		if (fro.getAction() != fro.A_Win && !can.isCandyLost())
		{
			fro.setAction(fro.A_Waiting);
			if (Resources::instance().getSound((int)Resources::Sounds::s_WaitingYooHoo).getStatus() == sf::Sound::Status::Stopped)
				Resources::instance().playSound((int)Resources::Sounds::s_WaitingYooHoo);
		}
		if (can.isCandyLost())
		{
			Resources::instance().playSound((int)Resources::Sounds::s_LoseOhNo);
			fro.setAction(fro.A_Lose);
		}

		//Candy is lost and animation is finished
		if ((can.isCandyLost() && fro.getEnded()) || (can.isCandyLost() && can.isAnimationEnded()))
			can.setDisposed(true);
	}

	void candyBubble(GameObject& candy, GameObject& bubble)
	{
		Candy& can  = static_cast<Candy&>(candy);
		Bubble& bub = static_cast<Bubble&>(bubble);

		if (bub.checkCollision(can, bub) || can.getCandyBubbled() && !can.isCandyGravity())
		{
			can.setCandyBubbled(true);
			bub.setPosition(can.getObjPosition());
			can.getBody()->SetGravityScale(-5);
			if (can.isCandy2Rope())
				can.getBody()->SetGravityScale(-70 * can.getAmountOfRopes());
		}

		if (bub.isClicked() && can.getCandyBubbled())
		{
			Resources::instance().playSound((int)Resources::Sounds::s_BubblePop);
			can.setCandyBubbled(false);

			if (!can.isCandyGravity())
				can.getBody()->SetGravityScale(10);

			bub.setDisposed(true);
			bub.setClicked(false);
			can.setCandyGravity(false);
		}

		if (can.getDeleteCandy())
			bub.setDisposed(true);
	}

	void candySpike(GameObject& candy, GameObject& spike)
	{
		Candy& can = static_cast<Candy&>(candy);
		Spike& spi = static_cast<Spike&>(spike);

		if (can.getBody()->IsAwake())
			if (spi.checkCollision(can, spi))
			{
				if (Resources::instance().getSound((int)Resources::Sounds::s_CandyCrash).getStatus() == sf::Sound::Status::Stopped)
					Resources::instance().playSound((int)Resources::Sounds::s_CandyCrash);

				can.setAction(can.A_CandyBroken);
				can.setCandyLost(true);
				can.getBody()->SetAwake(false);
			}

		if (!can.isCandyLost())
			can.setAction(can.A_Candy);
	}

	void candyTeleport(GameObject& candy, GameObject& teleport)
	{
		Candy& can = static_cast<Candy&>(candy);
		HatPort& tele = static_cast<HatPort&>(teleport);

		if (tele.checkCollision(can, tele))
		{
			can.setCandyOnTeleport(true);

			if (!can.getCandyTeleported())
			{
				Resources::instance().playSound((int)Resources::Sounds::s_TeleportAlakazam);
				sf::Vector3f telpos = tele.getPairsPositionTP();
				can.getBody()->SetTransform({ telpos.x, telpos.y }, can.getBody()->GetAngle());
				can.setCandyTeleported(true);
				sf::Vector2f angle = tele.getAngleDirction(telpos.z);
				can.getBody()->ApplyLinearImpulse({ angle.x * DEG_360, angle.y * DEG_360 }, can.getBody()->GetWorldCenter(), true);
			}
		}
	}

	void candyStar(GameObject& candy, GameObject& star)
	{
		Candy& can = static_cast<Candy&>(candy);
		Star& sta = static_cast<Star&>(star);

		if (sta.checkCollision(can, sta))
		{
			Resources::instance().playSound((int)Resources::Sounds::s_StarCollected);
			sta.setDisposed(true);
			can.setStar();
		}
	}

	void candyLimit(GameObject& candy, GameObject& limit)
	{
		Candy& can = static_cast<Candy&>(candy);
		Limit& lim = static_cast<Limit&>(limit);

		if (lim.checkCollision(can, lim))
			can.setCandyLost(true);
	}

	void candyBlower(GameObject& candy, GameObject& blower)
	{
		Candy& can = static_cast<Candy&>(candy);
		Blower& blo = static_cast<Blower&>(blower);

		blo.setAction(blo.isClicked());

		if (blo.isClicked())
		{
			Resources::instance().playSound((int)Resources::Sounds::s_Blowing);
			blo.setAction(blo.isClicked());

			if (can.checkShapeCollision(blo.getBlowZone()))
			{
				int blowerAngle = blo.getAngle();
				sf::Vector2f angle = blo.getAngleDirction(blowerAngle);
				b2Vec2 wind = { angle.x * 13.25f, angle.y * 13.25f };
				b2Vec2 posi = { can.getBody()->GetWorldCenter() };
				can.getBody()->ApplyForce(wind, posi, true);
				can.getBody()->SetFixedRotation(true);
			}
			else
				blo.setClicked(false);
		}
	}

	void candyRopeBase(GameObject& candy, GameObject& ropeBase) {}

	void candyGravityChange(GameObject& candy, GameObject& gravity)
	{
		Candy& can = static_cast<Candy&>(candy);
		GravityChange& grav = static_cast<GravityChange&>(gravity);

		if (grav.isClicked())
		{
			Resources::instance().playSound((int)Resources::Sounds::s_GravityChange);

			if (!grav.getGravity())
			{
				can.getBody()->SetGravityScale(GRAVITY_SCALE);
				grav.setAction(true);
				if (can.isCandy2Rope())
					can.setCandyGravity(true);
				else
					can.getBody()->SetGravityScale(-GRAVITY_SCALE);
			}
			else
			{
				grav.setAction(false);
				can.setCandyGravity(false);
				can.getBody()->SetGravityScale(GRAVITY_SCALE);
			}

			grav.setClicked(false);
		}
	}

	void ropeMouseTool(GameObject& rope, GameObject& mouseTool)
	{
		Rope& rop		  = static_cast<Rope&>(rope);
		MouseTool& mouseT = static_cast<MouseTool&>(mouseTool);

		auto ropeBox = rop.getRopeBoxes();

		for (auto& ro : ropeBox)
			if (mouseT.lineIntersect(ro.getPosition(), { ro.getPosition().x + 50 , ro.getPosition().y + 50 }))
			{
				Resources::instance().playSound((int)Resources::Sounds::s_CutRope);
				rop.setDisposed(true);
			}
	}


	// secondary collision-processing functions that just
	// implement symmetry: swap the parameters and call a
	// primary function
	void frogCandy(GameObject& frog, GameObject& candy)				{ candyFrog(candy, frog); }
	void starCandy(GameObject& star, GameObject& candy)				{ candyStar(candy, star); }
	void ropeBaseCandy(GameObject& ropeBase, GameObject& candy)		{ candyRopeBase(candy, ropeBase); }
	void spikeCandy(GameObject& spike, GameObject& candy)			{ candySpike(candy, spike); }
	void teleportCandy(GameObject& teleport, GameObject& candy)		{ candyTeleport(candy, teleport); }
	void bubbleCandy(GameObject& bubble, GameObject& candy)			{ candyBubble(candy, bubble); }
	void limitCandy(GameObject& limit, GameObject& candy)			{ candyLimit(candy, limit); }
	void blowerCandy(GameObject& blower, GameObject& candy)			{ candyBlower(candy, blower); }
	void gravityChangeCandy(GameObject& candy, GameObject& gravity) { candyGravityChange(candy, gravity); }
	void mouseToolRope(GameObject& mouseTool, GameObject& rope)		{ ropeMouseTool(rope, mouseTool); }

	using HitFunctionPtr = void (*)(GameObject&, GameObject&);
	// typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
	using Key = std::pair<std::type_index, std::type_index>;
	// std::unordered_map is better, but it requires defining good hash function for pair
	using HitMap = std::map<Key, HitFunctionPtr>;

	HitMap initializeCollisionMap()
	{
		HitMap phm;

		phm[Key(typeid(Candy), typeid(Frog))]		   = &candyFrog;
		phm[Key(typeid(Frog), typeid(Candy))]	       = &frogCandy;

		phm[Key(typeid(Candy), typeid(Star))]		   = &candyStar;
		phm[Key(typeid(Star), typeid(Candy))]		   = &starCandy;

		phm[Key(typeid(Candy), typeid(RopeBase))]	   = &candyRopeBase;
		phm[Key(typeid(RopeBase), typeid(Candy))]	   = &ropeBaseCandy;

		phm[Key(typeid(Candy), typeid(Spike))]		   = &candySpike;
		phm[Key(typeid(Spike), typeid(Candy))]	       = &spikeCandy;

		phm[Key(typeid(Candy), typeid(HatPort))]	   = &candyTeleport;
		phm[Key(typeid(HatPort), typeid(Candy))]	   = &teleportCandy;

		phm[Key(typeid(Candy), typeid(Bubble))]		   = &candyBubble;
		phm[Key(typeid(Bubble), typeid(Candy))]		   = &bubbleCandy;

		phm[Key(typeid(Candy), typeid(Limit))]		   = &candyLimit;
		phm[Key(typeid(Limit), typeid(Candy))]		   = &limitCandy;

		phm[Key(typeid(Candy), typeid(Blower))]		   = &candyBlower;
		phm[Key(typeid(Blower), typeid(Candy))]		   = &blowerCandy;

		phm[Key(typeid(Candy), typeid(GravityChange))] = &candyGravityChange;
		phm[Key(typeid(GravityChange), typeid(Candy))] = &gravityChangeCandy;

		phm[Key(typeid(Rope), typeid(MouseTool))]	   = &ropeMouseTool;
		phm[Key(typeid(MouseTool), typeid(Rope))]	   = &mouseToolRope;

		return phm;
	}

	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		return mapEntry->second;
	}

} // end namespace

void processCollision(GameObject& object1, GameObject& object2)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)
	{
		throw UnknownCollision(object1, object2);
	}

	phf(object1, object2);
}
