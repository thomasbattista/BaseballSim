#include "Player.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

Player::Player()
{
	first="first"; last = "last";
	contact = 0, power=0, speed = 0, glove=0, arm=0;
}

Player::Player(string f, string l, int c, int p, int s, int g, int a)
{
	first=f; last = l;
	contact = c;
	power=p, speed = s, glove=g, arm=a;
}

int Player::getContact()
{
	return contact;
}

int Player::getPower()
{
	return power;
}

int Player::getSpeed()
{
	return speed;
}

int Player::getGlove()
{
	return glove;
}

int Player::getArm()
{
	return arm;
}

string Player::getInfo()
{
	return first + " " + last + " " + to_string(contact) + " " + to_string(power) + " " + to_string(speed) + " " + to_string(glove) + " " + to_string(arm);      
	
}

ostream &operator<<(ostream &out, const Player &p)
{
	out << p.first << " " << p.last << " ";
	//out << p.contact << " " << p.power << " " << p.speed << " " << p.glove << " " << p.arm;
	return out;	
}

