#ifndef _Player_H
#define _Player_H

#include <string>
using namespace std;

//accuracy, pitching, eye, etc.
//First Name, Last Name, Contact, Power, Speed, Glove, Arm 

class Player
{
	private:
		string first;
		string last;
		int contact, power, speed, glove, arm;
	public:
		Player();
		Player(string f, string l, int c, int p, int s, int g, int a);
		int getContact();
		int getPower();
		int getSpeed();
		int getGlove();
		int getArm();
		string getInfo();

		friend std::ostream & operator<<(std::ostream &out, const Player &p);
};

#endif
