#include "StudentWorld.h"
#include <string>
#include <vector>
#include "Actor.h"
#include<ctime>
using namespace std;

vector <Actor*> Actors;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
	
	
	
	if (getLives() != 0) {
		time_t t;
		time(&t);
		srand((unsigned int)t);
		
		for (int i = 0; i < 64; i++) {
			for (int j = 0; j < 64; j++) {
				dirtmark[i][j] = 0;
			}
		}
		
		for (int i = 0; i < 60; i++) {
			for (int j = 0; j < 64; j++) {
				if (i >= 4) {
					if (j < 30 || j > 33) {
						dirt[i][j] = new Earth(j, i);
						
					}
				}
				else {
					dirt[i][j] = new Earth(j, i);
					
				}

			}
		}
		int B = (getLevel() / 2) + 2;
		if (B > 9)
			B = 9;
		int G = (5 - getLevel() / 2);
		if (G < 2)
			G = 2;
		int L = (2 + getLevel());
		if (L > 21)
			L = 21;
		total = L + G;
		barrels = L;

		for (int i = 0; i < B; i++) {
			createBoulder();
			Actors.push_back(boulder);
		}
		
		
		int j = 0;
		while (j != total) {
			for (int i = 0; i < G; i++) {
				createGoodie(2);
				Actors.push_back(goodie);
				

			}
			j = G;
			for (int i = 0; i < L; i++) {
				createGoodie(1);
				Actors.push_back(goodie);
				

			}
			j = j + L;
		}
		
		goodie = new Sonar(0, 61, this, 0);
		Actors.push_back(goodie);
		protester = new RegProtester(this);
		Actors.push_back(protester);
		
		
		
		
		
		

		player = new TunnelMan(this);
	}
	return GWSTATUS_CONTINUE_GAME;
}

bool StudentWorld::isearthbtwn(int x1, int x2, int y1, int y2) {
	if (y1 == y2) {
		if (x1 > x2) {
			for (int i = x2; i < x1; i++) {
				for (int j = 0; j < 4; j++) {
					if (dirt[j][i] != nullptr) {
						return false;
					}
				}
			}
			return true;
		}
		else {
			for (int i = x2; i < x1; i++) {
				for (int j = 0; j < 4; j++) {
					if (dirt[j][i] != nullptr) {
						return false;
					}
				}
			}
			return true;
		}
	}
	else if (x1 == x2) {
		if (y1 > y2) {
			for (int i = y2; i < y1; i++) {
				for (int j = 0; j < 4; j++) {
					if (dirt[i][j] != nullptr) {
						return false;
					}
				}
			}
			return true;
		}
		else {
			for (int i = y2; i < y1; i++) {
				for (int j = 0; j < 4; j++) {
					if (dirt[i][j] != nullptr) {
						return false;
					}
				}
			}
			return true;
		}
	}
	else {
		return false;
	}
}
void StudentWorld::dechitpoints() {
	player->reducehitpoints();
}

bool StudentWorld::checkearth(int dir, int x, int y) {
	if (dir == 1) {
		for (int i = 0; i < 4; i++) {
			if (dirt[y + i][x - 4] != nullptr) {
				return false;
			}
		}
		return true;
	}
	else if (dir == 2) {
		for (int i = 0; i < 4; i++) {
			if (dirt[y + i][x + 4] != nullptr) {
				return false;
			}
		}
		return true;
	}
	else if (dir == 3) {
		for (int i = 0; i < 4; i++) {
			if (dirt[y + 4][x - i] != nullptr) {
				return false;
			}
		}
		return true;
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (dirt[y - 4][x + i] != nullptr) {
				return false;
			}
		}
		return true;
	}
}

int StudentWorld::getbarrels() {
	return barrels;
}

void StudentWorld::increasegold() {
	player->incgold();
}

void StudentWorld::decbarrels() {
	barrels = barrels - 1;
}

bool StudentWorld::fallornot(int x, int y) {
	if (dirt[y - 1][x] == nullptr && dirt[y - 1][x + 1] == nullptr && dirt[y - 1][x + 2] == nullptr && dirt[y - 1][x + 3] == nullptr)
		return true;
	else
		return false;
}


int StudentWorld::playercoor(int coor) {
	if(coor==1)
	return player->getX();
	else
		return player->getY();
}




void StudentWorld::createGoodie(int flag) {
	int xcor = rand() % 61;
	int ycor = rand() % 57;
	if (xcor >= 27 && xcor <= 33)
		xcor = xcor + 7;
	if(flag ==1)
		goodie = new Oil(xcor, ycor, this);
	if(flag==2)
		goodie = new Gold(xcor, ycor, this,0);
	if (flag == 3)
		goodie = new Water(xcor, ycor, this);
}

void StudentWorld::addsquirt(Actor* ptr){
	Actors.push_back(ptr);
}

void StudentWorld::createBoulder() {
	
	
		int xcor = rand() % 61;
		int ycor = rand() % 57;
		if (ycor < 20)
			ycor = ycor + 20;
		
		if (xcor >= 27 && xcor <= 33)
			xcor = xcor + 7;
		boulder = new Boulder(xcor,ycor, this);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				dirt[ycor + i][xcor + j]->setVisible(false);
				dirtmark[ycor + i][xcor + j] = 1;
			}
		}
}

bool StudentWorld::isboulderthere(int x, int y, int dir) {
	
	if (dir == 1) {
		for (int i = 0; i < 4; i++) {
			if (dirtmark[y+i][x - 1] == 1) {
				return true;
			}
		}
		return false;
	}
	else if (dir == 2) {
		for (int i = 0; i < 4; i++) {
			if (dirtmark[y + i][x + 4] == 1) {
				return true;
			}
		}
		return false;
	}
	else if (dir == 3) {
		for (int i = 0; i < 4; i++) {

			
			if (dirtmark[y + 4][x + i] == 1) {
				return true;
			}
		}
		return false;
	}
	else {
		for (int i = 0; i < 4; i++) {


			if (dirtmark[y - 1][x + i] == 1) {
				return true;
			}
		}
		return false;
	}
	
	
}

void StudentWorld::increaseSonar() {
	player->incsonar();
}

void StudentWorld::digdown() {
	for (int i = 0; i < 4; i++) {
		if (dirt[player->getY()][player->getX() + i] != nullptr) {
			playSound(SOUND_DIG);
			break;
		}
	}
	for (int i = 0; i < 4; i++) {
		
		delete dirt[player->getY()][player->getX() + i];
		dirt[player->getY()][player->getX() + i] = nullptr;
	}
}

void StudentWorld::digup() {
	if (player->getY() == 58) {
		for (int i = 0; i < 4; i++) {
			if(dirt[player->getY() + 2][player->getX() + i] != nullptr){
				playSound(SOUND_DIG);
				break;
			}
		}
		for (int i = 0; i < 4; i++) {
			
			delete dirt[player->getY() + 2][player->getX() + i];
			dirt[player->getY() + 2][player->getX() + i] = nullptr;
		}
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (dirt[player->getY() + 3][player->getX() + i] != nullptr) {
			playSound(SOUND_DIG);
			break;
		}
	}
	for (int i = 0; i < 4; i++) {
		
		delete dirt[player->getY() + 3][player->getX() + i];
		dirt[player->getY() + 3][player->getX() + i] = nullptr;
	}
}

void StudentWorld::digleft() {
	if (player->getY() == 59) {
		if (dirt[player->getY()][player->getX()] != nullptr) {
			playSound(SOUND_DIG);
		}

			delete dirt[player->getY()][player->getX()];
			dirt[player->getY()][player->getX()] = nullptr;
		
	}
	if (player->getY() == 58) {
		for (int i = 0; i < 2; i++) {
			if (dirt[player->getY() + i][player->getX()] != nullptr) {
				playSound(SOUND_DIG);
				break;
			}
		}
		for (int i = 0; i < 2; i++) {

			delete dirt[player->getY() + i][player->getX()];
			dirt[player->getY() + i][player->getX()] = nullptr;
		}
	}
	if (player->getY() == 57) {
		for (int i = 0; i < 3; i++) {
			if(dirt[player->getY() + i][player->getX()] != nullptr){
				playSound(SOUND_DIG);
				break;
			}
		}
		for (int i = 0; i < 3; i++) {

			delete dirt[player->getY() + i][player->getX()];
			dirt[player->getY() + i][player->getX()] = nullptr;
		}
	}
	if (player->getY() < 57) {
		for (int i = 0; i < 4; i++) {
			if (dirt[player->getY() + i][player->getX()] != nullptr) {
				playSound(SOUND_DIG);
				break;
			}
		}
		for (int i = 0; i < 4; i++) {

			delete dirt[player->getY() + i][player->getX()];
			dirt[player->getY() + i][player->getX()] = nullptr;
		}
	}
}

void StudentWorld::digright() {
	
	if (player->getY() == 59) {

		if (dirt[player->getY()][player->getX() + 3]!=nullptr)
			playSound(SOUND_DIG);

			delete dirt[player->getY()][player->getX() + 3];
			dirt[player->getY()][player->getX() + 3] = nullptr;
		
	}
	if (player->getY() == 58) {
		for (int i = 0; i < 2; i++) {
			if (dirt[player->getY() + i][player->getX() + 3] != nullptr) {
				playSound(SOUND_DIG);
				break;
			}
		}

		for (int i = 0; i < 2; i++) {


			delete dirt[player->getY() + i][player->getX() + 3];
			dirt[player->getY() + i][player->getX() + 3] = nullptr;
		}
	}
	if (player->getY() == 57) {
		for (int i = 0; i < 3; i++) {
			if (dirt[player->getY() + 1][player->getX() + 3] != nullptr) {
				playSound(SOUND_DIG);
				break;
			}
		}
		for (int i = 0; i < 3; i++) {

			delete dirt[player->getY() + i][player->getX() + 3];
			dirt[player->getY() + i][player->getX() + 3] = nullptr;
		}
	}
	if (player->getY() < 57) {
		for (int i = 0; i < 4; i++) {
			if (dirt[player->getY() + i][player->getX() + 3] != nullptr) {
				playSound(SOUND_DIG);
				break;
			}
		}
		for (int i = 0; i < 4; i++) {

			delete dirt[player->getY() + i][player->getX() + 3];
			dirt[player->getY() + i][player->getX() + 3] = nullptr;
		}
	}
}

void StudentWorld::setGameText() {
	string level = to_string(getLevel());
	string lives = to_string(getLives());
	string health = to_string(10 * (player->gethitpoints()));
	string squirts = to_string(player->getsquirt());
	string gold = to_string(player->getgold());
	string barrels = to_string(getbarrels());
	string sonar = to_string(player->getsonar());
	string score = to_string(getScore());
	string s = "Score: " + score + "  Lvl: "+ level+ "  Lives: " + lives + "  Hlth: "+health+"%";
	string s1 = "  Wtr: " + squirts + "  Gld: " + gold + "  Sonar: " + sonar + "  Oil Left: " + barrels;
	s = s + s1;
	setGameStatText(s);

}
void StudentWorld::freedirt(int x, int y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			dirtmark[y + i][x + j] = 0;
		}
	}
}
bool StudentWorld::boulderdie(int x, int y) {
	if (player->getdirc() == 1 || player->getdirc() == 4) {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 4; j++) {
				int vx = x - i;
				int vy = y - j;
				if (vx == player->getX() && vy == player->getY())
					return true;
			}
		}
		return false;
	}
	else if (player->getdirc() == 2) {
		for (int i = 0; i < 7; i++) {
			int vx = x - i;
			if (vx == player->getX() && (y-1)==player->getY())
				return true;
		}
		return false;
	}
	else{
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 4; j++) {
				int vx = x + i;
				int vy = y - j;
				if (vx == player->getX() && vy == player->getY())
					return true;
			}
		}
		return false;

	}

}

int StudentWorld::move()
{
	setGameText();
	int lives = getLives();
	player->doSomething();
	for (unsigned int i = 0; i < Actors.size(); i++) {


		Actors[i]->doSomething();
		if (Actors[i]->getState() == false) //new code
			Actors.erase(Actors.begin() + i); //new code
		if (getbarrels() == 0)
			return GWSTATUS_FINISHED_LEVEL;
	}

	if (getLives() != lives ) {
		return GWSTATUS_PLAYER_DIED;
	}
	if (player->gethitpoints() == 0) {
		playSound(SOUND_PLAYER_GIVE_UP);
		return GWSTATUS_PLAYER_DIED;
	}
	
	
	 
		

		

	// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	//decLives();
	return GWSTATUS_CONTINUE_GAME;
}


void StudentWorld::cleanUp() {
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 64; j++) {
			dirtmark[i][j] = 0;
		}
	}
	vector <Actor*>::iterator it;
	for (it = Actors.begin(); it!=Actors.end(); ){
		
			delete *it;
	it = Actors.erase(it);
}
	delete player;
	
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 64; j++) {
			if (i >= 4) {
				if (j < 30 || j > 33) {
					if (dirt[i][j] != nullptr)
						delete dirt[i][j];

				}
			}
			else {
				if (dirt[i][j] != nullptr)
					delete dirt[i][j];

			}

		}
	}
	

}


StudentWorld::~StudentWorld() {
	vector <Actor*>::iterator it;
	for (it = Actors.begin(); it != Actors.end(); ) {

		delete *it;
		it = Actors.erase(it);
	}
	delete player;
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 64; j++) {
			if (i >= 4) {
				if (j < 30 || j > 33) {
					if (dirt[i][j] != nullptr)
						delete dirt[i][j];

				}
			}
			else {
				if (dirt[i][j] != nullptr)
					delete dirt[i][j];

			}

		}
	}


	
}


// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
