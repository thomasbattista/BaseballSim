#ifndef _Team_H
#define _Team_H

#include <string>
#include "Player.h"
using namespace std;

//accuracy, pitching, eye, etc.

class Team
{
	private:
		string name;
		Player players[25];
        Player order[9], pos[9];
	public:
		Team();
		Team(string s);
        void setOrder();
        void setPos();
        void printLineup();
        void printPos();
		string getName();
		Player getBatter(int i);
		Player getFielder(int i);
		friend std::ostream & operator<<(std::ostream &out, const Team &t);
};

#endif
