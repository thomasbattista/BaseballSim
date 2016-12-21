#include <string>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Team.h"
using namespace std;

Team::Team()
{
	name = "City";	
	for (int i=0; i<25; i++)
	{
		players[i] = Player();
	}
}

Team::Team(string s)
{
	
	
	ifstream file(s);
	string f, l, con, pow, spe, glo, arm;
	int c, p, sp, g, a;
	getline (file, name, '\n' );
	for (int i=0; file.good() && i<25; i++)
	{
		getline (file, f, ',' );
		getline (file, l, ',' );
		getline (file, con, ',' );
		getline (file, pow, ',' );
		getline (file, spe, ',' );
		getline (file, glo, ',' );
		getline (file, arm, '\n' );		
		
		c = stoi(con);
		p = stoi(pow);
		sp = stoi(spe);
		g = stoi(glo);
		a = stoi(arm);
		players[i] = Player(f,l,c,p,sp,g,a); 
	}
	for (int i=0; i<9; i++)
	{
		order[i] = players[i];
		pos[i] = players[i];
	}
}

void Team::setOrder()
{
	cout << *this;	
	cout << "please select batting order" << endl;
	int temp;
	string s;
	for (int i=0; i<9; i++)
	{
		cout << "batting in slot number " << i+1 << ": ";
		cin >> s;
		if (!isdigit(s[0]))
		{
			cout << "sorry, please input a the player's number" << endl;
			i--;
		}
		else
		{
			temp = stoi(s);
			if (temp <1 || temp >25)
			{
				cout << "sorry, please input a the player's number (1-25) " << endl;
				i--;
			}
			else
				order[i] = players[temp-1];
		}
	}
}

void Team::setPos()
{	
	cout << "please select postions" << endl;
	int temp;
	string s;
	for (int i=0; i<9; i++)
	{
	  
		cout << "position number " << i+1 << ": ";
		cin >> s;
		if (!isdigit(s[0]))
		{
			cout << "sorry, please input a the player's batting position " << endl;
			i--;
		}
		else
		{
			temp = stoi(s);
			if (temp <1 || temp >9)
			{
				cout << "sorry, please input a the player's batting position (1-9) " << endl;
				i--;
			}
			else
				pos[i] = order[temp-1];
		}
	}
}


void Team::printLineup()
{
	for (int i=0; i<9; i++)
	{
		cout << i+1 << " " << order[i] << endl;
	}
}

void Team::printPos()
{
	for (int i=0; i<9; i++)
	{
		cout << i+1 << " " << pos[i] << endl;
	}
}

string Team::getName()
{
	return name;
}

Player Team::getBatter(int i)
{
	return order[i];
}

Player Team::getFielder(int i)
{
	return pos[i];
}



ostream &operator<<(ostream &out, const Team &t)
{
	out << t.name<<endl;// << " " << p.last;
	for (int i=0; i< 25; i++)
	{
		cout << i+1 << " " << t.players[i] << endl;
	}
	return out;	
}

