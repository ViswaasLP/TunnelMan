#ifndef ACTOR_H_
#define ACTOR_H_
#include <string>
#include <cmath>
#include "GraphObject.h"
class StudentWorld;
class Squirt;

class Actor : public GraphObject {
public:
	Actor(StudentWorld* worldptr,int IMAGE_ID, int x, int y, Direction startdirn, float size, unsigned int depth);
	virtual void doSomething() = 0;
	StudentWorld * getWorld();
	bool getState();
	void setState(int prstate);
	
	virtual ~Actor();

private:
	StudentWorld * Worldptr;
	int state;
	/*
	int IMAGE_ID, x, y;
	Direction startdirn;
	float size;
	unsigned int depth;
	*/
};

class TunnelMan : public Actor {
public:
	TunnelMan(StudentWorld* ptr);
	virtual void doSomething();
	virtual ~TunnelMan();

	int getgold();
	int gethitpoints();
	int getsquirt();
	int getsonar();
	void reducehitpoints();
	void incsquirt();
	void decsquirt();
	void incsonar();
	void decsonar();
	void incgold();
	void decgold();
	int getdirc();
	//void dechitpoint();
private:
	Squirt* squirt;
	int hitpoints;
	int squirts;
	int sonar;
	int gold;

};

class Earth : public GraphObject {
public:
	Earth(int x, int y);
	virtual void doSomething();
	virtual ~Earth();
private:
	int x, y;

};

class Boulder : public Actor {
public:
	Boulder(int x, int y, StudentWorld* ptr);
	virtual void doSomething();
	virtual ~Boulder();
private:
	int flag;
	int ticker;
	int sound;
};

class Goodie : public Actor {
public:
	Goodie(int x, int y, StudentWorld* ptr, int ID, Direction dir,int depth, int flag);
	virtual void doSomething() {
		return;
	}
	virtual ~Goodie();


};

class Squirt : public Actor {
public:
	Squirt(int x, int y, StudentWorld* ptr, Direction dir);
	virtual void doSomething();
	virtual ~Squirt();
private:
	int dist;
};

class Gold :public Goodie {
public:
	Gold(int x, int y, StudentWorld* ptr, int flag);
	virtual void doSomething();
	virtual ~Gold();
private:
	int stage;

};

class Oil : public Goodie {
public:
	Oil(int x, int y, StudentWorld* ptr);
	virtual void doSomething();
	virtual ~Oil();
private:
	//int state;
	
};

class Sonar : public Goodie {
public:
	Sonar(int x, int y, StudentWorld *ptr, int flag);
	virtual void doSomething();
	virtual ~Sonar();
private:
	int stage;
	unsigned int ticker;
};

class Water : public Goodie {
public:
	Water(int x, int y, StudentWorld* ptr);
	virtual void doSomething() {
		return;
	}
	virtual ~Water();
};

class RegProtester : public Actor {
public:
	RegProtester(StudentWorld* ptr);
	virtual void doSomething();
	void changedirc();
	virtual ~RegProtester();
private:
	int stage;
	int numsqrs;
	unsigned int ticker;
	int hitpoints;
	int orignum;
	int shoutticker;
};
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
