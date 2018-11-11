#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
class Actor;
class TunnelMan;
class Earth;
class Boulder;
class Oil;
class Goodie;
class Gold;
class Water;
class RegProtester;


#include <string>



// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
	}

	virtual int init();

	virtual int move();
	virtual void cleanUp();
	virtual ~StudentWorld();
	void digup();
	void digdown();
	void digright();
	void digleft();
	void createBoulder();
	void createGoodie(int flag);
	int playercoor(int coor);
	bool fallornot(int x, int y);
	void increasegold();
	int getbarrels();
	void decbarrels();
	void increaseSonar();
	void setGameText();
	bool boulderdie(int x, int y);
	bool checkearth(int dir, int x, int y);
	bool isboulderthere(int x, int y, int dir);
	void freedirt(int x, int y);
	bool isearthbtwn(int x1, int x2, int y1, int y2);
	void dechitpoints();
	void addsquirt(Actor* ptr);


private:
	int barrels;
	TunnelMan * player;
	Boulder * boulder;
	Earth * dirt[60][64];
	int dirtmark[64][64];
	Goodie* goodie;
	int total;
	RegProtester* protester;
};

#endif // STUDENTWORLD_H_
