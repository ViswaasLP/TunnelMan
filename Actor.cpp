#include "Actor.h"
#include "StudentWorld.h"
#include<ctime>

float dist(int x1, int y1, int x2, int y2) {
	float xdist = pow(((float)x2 - (float)x1), 2);
	float ydist = pow(((float)y2 - (float)y1), 2);
	float result = sqrtf((xdist + ydist));
	return result;

}

Actor::Actor(StudentWorld* worldptr, int IMAGE_ID, int x, int y, Direction startdirn, float size, unsigned int depth) : GraphObject(IMAGE_ID, x, y, startdirn, size, depth), Worldptr(worldptr) {
	setVisible(true);
	state = 1;
}

Actor::~Actor() {
	Worldptr = nullptr;
	delete Worldptr;
}

void Actor::setState(int prstate) {
	if (prstate == 1 || prstate == 0)
		state = prstate;
}

StudentWorld *Actor::getWorld() {
	return Worldptr;
}

bool Actor::getState() {
	if (state == 0) {
		return false;
	}
	else {
		return true;
	}

}






int TunnelMan::getdirc() {
	if (this->getDirection() == up)
		return 1;
	else if (this->getDirection() == down)
		return 2;
	else if (this->getDirection() == left)
		return 3;
	else if (this->getDirection() == right)
		return 4;
}


int TunnelMan::getgold() {
	return gold;
}
int TunnelMan::gethitpoints() {
	return hitpoints;
}
int TunnelMan::getsquirt() {
	return squirts;
}
int TunnelMan::getsonar() {
	return sonar;
}
void TunnelMan::reducehitpoints() {
	if(hitpoints>0)
	hitpoints = hitpoints - 2;
}
void TunnelMan::incsquirt() {
	squirts = squirts + 5;
}
void TunnelMan::decsquirt() {
	if(squirts>0)
	squirts = squirts - 1;
}
void TunnelMan::incsonar() {
	sonar++;
}
void TunnelMan::decsonar() {
	if (sonar > 0)
		sonar = sonar - 1;

}
void TunnelMan::incgold() {
	gold = gold + 1;
}
void TunnelMan::decgold() {
	if (gold > 0)
		gold = gold - 1;
}

TunnelMan::TunnelMan(StudentWorld* ptr) : Actor(ptr,TID_PLAYER, 30, 60, right, 1.0, 0) {
	hitpoints = 10;
	squirts = 5;
	sonar = 1;
	gold = 0;
}

void TunnelMan::doSomething() {
	int ch;

	if (getWorld()->getKey(ch) == true) {
		switch (ch) {
		case KEY_PRESS_LEFT:
			if (getDirection() == left) {
				if (getX() != 0 && getWorld()->isboulderthere(this->getX(), this->getY(), 1) == false) {
					moveTo(getX() - 1, getY());
					if (getX() != 0) {
						 
						
						getWorld()->digleft();
					}
				}
				else if (getX() == 0 || getWorld()->isboulderthere(this->getX(), this->getY(), 1) == true) {
					moveTo(getX(), getY());
					
					

					getWorld()->digleft();
				}
			}
			else {
				setDirection(left);
			}
			break;


		case KEY_PRESS_RIGHT:
			if (getDirection() == right) {
				if (getX() < 60 && getWorld()->isboulderthere(this->getX(), this->getY(), 2) == false) {
					moveTo(getX() + 1, getY());

					
					getWorld()->digright();
				}
				
				else if (getX() >= 60 || getWorld()->isboulderthere(this->getX(), this->getY(), 2) == true ) {
					moveTo(getX(), getY());
					
					
				}
			}
			else {
				setDirection(right);
			}
			break;

		case KEY_PRESS_DOWN:
			if (getDirection() == down) {
				if (getY() != 0 && getWorld()->isboulderthere(this->getX(), this->getY(), 4) == false) {
					moveTo(getX(), getY() - 1);
					if (getY() != 0) {
						
						getWorld()->digdown();
					}
				}
				else if (getY() == 0 || getWorld()->isboulderthere(this->getX(), this->getY(), 4) == true) {
					moveTo(getX(), getY());
					
					getWorld()->digdown();
				}
			}
			else {
				setDirection(down);
			}
			break;
		case KEY_PRESS_UP:
			if (getDirection() == up) {
				if (getY() != 60 && getWorld()->isboulderthere(this->getX(), this->getY(), 3) == false) {
					moveTo(getX(), getY() + 1);
					if (getY() < 57) {
						
						getWorld()->digup();
					}
				}
				else if (getY() >= 60 || getWorld()->isboulderthere(this->getX(), this->getY(), 3) == true) {
					moveTo(getX(), getY());
					
				}
			}
			else {
				setDirection(up);
			}
			break;
		case KEY_PRESS_ESCAPE:
			getWorld()->decLives();
			break;
		case KEY_PRESS_SPACE:
			if (getsquirt() > 0) {
				decsquirt();
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				if (getDirection() == down) {
					squirt = new Squirt(getX(), getY() - 4, getWorld(), down);
					getWorld()->addsquirt(squirt);
				}
				else if (getDirection() == up) {
					squirt = new Squirt(getX(), getY() + 4, getWorld(), up);
					getWorld()->addsquirt(squirt);
				}
				else if (getDirection() == left) {
					squirt = new Squirt(getX() - 4, getY(), getWorld(), left);
					getWorld()->addsquirt(squirt);
				}
				else if (getDirection() == right) {
					squirt = new Squirt(getX() + 4, getY(), getWorld(), right);
					getWorld()->addsquirt(squirt);
				}

			}
			//default:

		}
	}
}


Earth::Earth(int x, int y) : GraphObject(TID_EARTH, x, y, right, 0.25, 3) {
	setVisible(true);
}





void Earth::doSomething() {
	return;
}


Boulder::Boulder(int x, int y, StudentWorld* ptr) : Actor(ptr, TID_BOULDER, x, y, down, 1.0, 1) {
	flag = 0;
	ticker = 0;
	sound = 0;
}

void Boulder::doSomething() {
	if (getState() == false) {
		return;
	}
	else if (getState() == true && flag == 0) {
		if (getWorld()->fallornot(this->getX(), this->getY()))
			flag = 1;
	}
	else if (getState() == true && flag == 1) {
		if (ticker != 30)
			ticker++;
		else if (ticker == 30) {
			if (sound == 0) {
				getWorld()->playSound(SOUND_FALLING_ROCK);
				sound = 1;
				getWorld()->freedirt(getX(), getY());
			}
			if (getWorld()->fallornot(this->getX(), this->getY()) != false) {
				//if(getWorld()->boulderdie(this->getX(), this->getY()) == false)
				moveTo(getX(), getY() - 1);
				if (getWorld()->boulderdie(this->getX(), this->getY()) == true) {
					getWorld()->playSound(SOUND_PLAYER_GIVE_UP);
					getWorld()->decLives();
				}
			}
			else {
				this->setState(0);
				this->setVisible(false);
			}
			return;

		}
	}
}




Goodie::Goodie(int x, int y, StudentWorld * ptr, int ID, Direction dir, int depth, int flag) : Actor(ptr, ID, x, y, dir, 1.0, depth) {
	if (flag == 0) {
		setVisible(false);
	}
	else if(flag == 1) {
		setVisible(true);
	}
	
	
}





Squirt::Squirt(int x, int y, StudentWorld* ptr, Direction dir): Actor(ptr,TID_WATER_SPURT,x,y,dir,1.0,1){

	dist = 0;
}

void Squirt::doSomething() {
	if (getState() == false) {
		return;
	}
	else if (dist < 4) {
		dist++;
		if (getDirection() == right) {
			if (getWorld()->checkearth(2, getX(), getY()) == true && getWorld()->isboulderthere(getX(), getY(), 4) == false) {
				setVisible(true);
				moveTo(getX() + 1, getY());
			}
			else {
				setVisible(false);
				setState(0);
			}
		}
		else if (getDirection() == left) {
			if (getWorld()->checkearth(1, getX(), getY()) == true && getWorld()->isboulderthere(getX(), getY(), 3) == false) {
				setVisible(true);
				moveTo(getX() - 1, getY());
			}
			else {
				setVisible(false);
				setState(0);
			}
		}
		else if (getDirection() == up) {
			if (getWorld()->checkearth(3, getX(), getY()) == true && getWorld()->isboulderthere(getX(), getY(), 1) == false) {

				setVisible(true);
				moveTo(getX(), getY() + 1);
			}
			else {
				setVisible(false);
				setState(0);
			}
		}
		else if (getDirection() == down) {
			if (getWorld()->checkearth(4, getX(), getY()) == true && getWorld()->isboulderthere(getX(), getY(), 2) == false) {
				setVisible(true);
				moveTo(getX(), getY() - 1);
			}
			else {
				setVisible(false);
				setState(0);
			}
		}
	}
	else if (dist == 4) {
		setVisible(false);
		setState(0);
	}
}


Oil::Oil(int x, int y, StudentWorld* ptr): Goodie(x, y, ptr,TID_BARREL,right, 2,0) {}


void Oil::doSomething() {
	if (getState() == false) {
		return;
	}
	else if (getState() == true) {
		if (isVisible() == false) {

			float distance = dist(this->getX(), this->getY(), getWorld()->playercoor(1), getWorld()->playercoor(2));
			if (distance <= 4.00) {
				this->setVisible(true);
				return;
			}


		}
		else if (isVisible() == true) {
			float distance = dist(this->getX(), this->getY(), getWorld()->playercoor(1), getWorld()->playercoor(2));
			if (distance <= 3.00) {
				getWorld()->playSound(SOUND_FOUND_OIL);
				getWorld()->increaseScore(1000);
				getWorld()->decbarrels();
				this->setState(0);
				this->setVisible(false);
				return;
			}
		}
	}

}

Gold::Gold(int x, int y, StudentWorld* ptr, int flag) : Goodie(x, y, ptr,TID_GOLD,right,2,flag){
	stage = 0;
}

void Gold::doSomething() {
	if (getState() == false) {
		return;
	}
	else if (getState() == true && stage == 0) {
		if (isVisible() == false) {

			float distance = dist(this->getX(), this->getY(), getWorld()->playercoor(1), getWorld()->playercoor(2));
			if (distance <= 4.00) {
				this->setVisible(true);
				return;
			}


		}
		else if (isVisible() == true) {
			float distance = dist(this->getX(), this->getY(), getWorld()->playercoor(1), getWorld()->playercoor(2));
			if (distance <= 3.00) {
				getWorld()->playSound(SOUND_GOT_GOODIE);
				getWorld()->increasegold();
				getWorld()->increaseScore(10);
				this->setState(0);
				this->setVisible(false);
				return;
			}
		}

	}
}

Sonar::Sonar(int x, int y, StudentWorld* ptr, int flag) : Goodie(x, y, ptr, TID_SONAR, right, 2, flag) {
	stage = 1;
	ticker = 0;
}





void Sonar::doSomething() {

	if (isVisible() == false && stage == 0) {
		return;
	}
	if (getState() == true && stage == 1) {
		ticker++;
		if (ticker >= 100 && ticker <= (300 - (10 * getWorld()->getLevel()))) {
			this->setVisible(true);
			float distance = dist(this->getX(), this->getY(), getWorld()->playercoor(1), getWorld()->playercoor(2));
			if (distance <= 3.00) {
				getWorld()->playSound(SOUND_GOT_GOODIE);
				getWorld()->increaseSonar();
				getWorld()->increaseScore(75);
				this->setState(0);
				stage = 0;
				this->setVisible(false);
				return;
			}

		}
		else if (ticker > (300 - (10 * getWorld()->getLevel()))) {
			this->setState(0);
			stage = 0;
			this->setVisible(false);
			return;
		}
	}
}



Water::Water(int x, int y, StudentWorld*ptr) : Goodie(x, y, ptr, TID_WATER_POOL, right, 2, 1) {}

void RegProtester::doSomething() {
	if (getState() == false) {
		return;
	}
	else if (getState() == true && ticker < (3 - (getWorld()->getLevel() / 4))) {
		ticker++;
	}
	if (getState() == true && ticker == (3 - (getWorld()->getLevel() / 4))) {
		shoutticker++;
		ticker = 0;
		numsqrs = numsqrs - 1;
		float distance = dist(this->getX(), this->getY(), getWorld()->playercoor(1), getWorld()->playercoor(2));
		if (distance <= 4.00 && shoutticker >= 15) {
			getWorld()->playSound(SOUND_PROTESTER_YELL);
			getWorld()->dechitpoints();
			shoutticker = 0;
			return;
		}

		if (numsqrs > 0) {
			if (getX() == getWorld()->playercoor(1) || getY() == getWorld()->playercoor(2)) {
				if (getWorld()->isearthbtwn(getX(), getWorld()->playercoor(1), getY(), getWorld()->playercoor(2))) {
					if (getX() == getWorld()->playercoor(1)) {
						if (getY() > getWorld()->playercoor(2)) {
							setDirection(down);
						}
						else {
							setDirection(up);
						}
					}
					else if (getY() == getWorld()->playercoor(2)) {
						if (getX() > getWorld()->playercoor(1)) {
							setDirection(left);
						}
						else {
							setDirection(right);
						}
					}
				}

			}
			if (getDirection() == left) {
				if (getWorld()->checkearth(1, getX(), getY()) != false && getX() > 0)
					this->moveTo(getX() - 1, getY());
				else {
					changedirc();
				}
			}
			else if (getDirection() == right) {
				if (getWorld()->checkearth(2, getX(), getY()) != false && getX() < 60)
					this->moveTo(getX() + 1, getY());
				else {
					changedirc();
				}
			}
			else if (getDirection() == up) {
				if (getWorld()->checkearth(3, getX(), getY()) != false && getY() < 60)
					this->moveTo(getX(), getY() + 1);
				else {
					changedirc();
				}
			}
			else if (getDirection() == down) {
				if (getWorld()->checkearth(4, getX(), getY()) != false && getY() > 3)
					this->moveTo(getX(), getY() - 1);
				else {
					changedirc();
				}
			}

		}
		else if (numsqrs == 0) {
			changedirc();
		}

	}
}

RegProtester::RegProtester(StudentWorld * ptr) : Actor(ptr, TID_PROTESTER, 60, 60, left, 1.0, 0) {
	time_t t;
	time(&t);
	srand((unsigned int)t);
	stage = 0;
	ticker = 0;
	hitpoints = 5;
	shoutticker = 5;
	numsqrs = rand() % 60;
	if (numsqrs <= 8)
		numsqrs = numsqrs + 9;
	orignum = numsqrs;
}

void RegProtester::changedirc() {
	int randdirc = rand() % 4;
	numsqrs = orignum;
	if (randdirc == 0) {
		this->setDirection(left);
	}
	else if (randdirc == 1) {
		this->setDirection(right);
	}
	else if (randdirc == 0) {
		this->setDirection(up);
	}
	else if (randdirc == 0) {
		this->setDirection(down);
	}
}


TunnelMan::~TunnelMan() {}
Earth::~Earth() {}
Boulder::~Boulder() {}
Goodie::~Goodie(){}
Oil::~Oil(){}
Water::~Water(){}
Squirt::~Squirt(){}
Gold::~Gold(){}
RegProtester::~RegProtester(){}
Sonar::~Sonar(){}



// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
