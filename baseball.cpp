#include <iostream>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include <fstream>
#include <cstdlib>
#include "Player.h"
#include "Team.h"

using namespace std;

string getOutcome(Player b, Player p)
{
	int i = (rand() % 100)+1; //rand%acc*10 +1
	if (i == 1)
		return "HB";
	else if (i <=10)
		return "BB";

	int power = b.getPower();
	int contact = b.getContact();
	int arm = p.getArm();
	if (arm >=9)
	{
		power++;
	}

	contact = rand() % contact +1;
	arm = rand() %arm +1;
	
	if (contact + 3 <=arm)
		return "K";
	else if (contact +2 == arm && power >1)
		power--;
	else if (contact > arm+3)
		power++;
	if (contact > arm+6)
		power++;
	
	power = rand() % power +1;
	
	if (contact > 7 && power < 4)
		return "1B";	
	else if (power <= 2)
		return "GO";
	else if (contact <=1)
		return "PO";
	else if (power <=6 && contact > 4)
		return "1B";
	else if (power <=5)
		return "FO";
	else if (power <=8)
		return "2B";
	else if (power >=9)
		return "HR";
	else
		return "3B";

}

int main(int argc, const char *argv[])
{
	if (argc!=3)
	{
		cout << "please have two teams as command line args" << endl;
		exit(0);
	}	
	
	Player p;

	Team away(argv[1]);
	Team home(argv[2]);

	/*home.setOrder();
	home.printLineup();
	home.setPos();
	home.printPos();*/
	
	srand (time(0));

	
	int inn=1, outs=0, awayRuns=0, homeRuns=0,awayBat=1,homeBat=1;
	bool isTop= true, endOfInning;		
	bool bases[3] = {false,false,false};
	string outcome="",tbinning, selection;
	
	while (true)// (inn <=9 ||  (awayRuns == homeRuns)) 9
	{
		if (isTop)
		{		
		  
			tbinning = "↑ " + to_string(inn);
			//cout << "0 - pitch to  1 - intentionally walk  2 - pitch out "<<endl;
			cout << "Batting: " << away.getBatter(awayBat -1) << "    Pitching: " << home.getFielder(1 -1) << endl;
			cout << "\n  " + to_string(bases[1]) +  "                " << away.getName() << ": " + to_string(awayRuns) + 
						"    " << home.getName() << ": " + to_string(homeRuns) << endl;		
			cout <<  to_string(bases[2]) + "   " + to_string(bases[0])  + "              " + tbinning + "           Outs " + to_string(outs)<<endl;
		  top:			
			cout << "Make selection () 0 - pitch to  1 - intentionally walk  2 - pitch out  3 - print: " ;//<< endl;
            selection = cin.get();
            if (selection == "walk" || selection == "BB" || selection == "bb" || selection == "1")
            {
                cin.ignore();
                outcome = "BB";
				cin.ignore();
            } 
            else if (selection == "pitch out" || selection == "2" )
			{
				//stealodds decreased by 2;
				//walk increased by 25%
			}
			else if (selection == "print" || selection == "3"|| selection == "p") // format eventually
			{
				cin.ignore();	
				//print runners on base		
				cout << away.getBatter(awayBat -1).getInfo()<< endl;
				cout << home.getFielder(1 -1).getInfo()<<endl<<endl;
				goto top;
			}
			else
			    outcome=getOutcome(away.getBatter(awayBat -1),home.getFielder(1 -1));
			
			awayBat++;
			if (awayBat >9)		
				awayBat=1;
		}
		else //bottom of the inning
		{
		 
			if (inn >=9 && homeRuns>awayRuns)
			{
				cout << "\n\n Game Over ";
				break;
			}
			tbinning = "↓ " + to_string(inn);	
			//cout << "steal? (y/n)" << endl;
            //cin >> selection;
			
			cout << "Batting: " << home.getBatter(homeBat -1) << "    Pitching: " <<  away.getFielder(1 -1) <<endl;
			cout << "\n  " + to_string(bases[1]) +  "                " << away.getName() << ": " + to_string(awayRuns) + 
						"    " << home.getName() << ": " + to_string(homeRuns) << endl;		
			cout <<  to_string(bases[2]) + "   " + to_string(bases[0])  + "              " + tbinning + "           Outs " + to_string(outs)<<endl;
		   bottom:			
			cout << "Make selection: " ;//<< endl;
            selection = cin.get();

			if (selection == "print" || selection == "3" || selection == "p")
			{
				cin.ignore();				
				//print runners on base				
				cout << home.getBatter(homeBat -1).getInfo()<<endl;
				cout << away.getFielder(1 -1).getInfo()<<endl<<endl;
				goto bottom;
			}

            outcome=getOutcome(home.getBatter(homeBat -1), away.getFielder(1 -1));
			
			homeBat++;
			if (homeBat >9)		
				homeBat=1;
		}
		cout << outcome +"  ";

		if (outcome == "BB" || outcome == "HB")
		{
			if (bases[0] == true && bases[1] == true && bases[2] == true)
			{
				if (isTop==true)
					awayRuns++;
				else
					homeRuns++;
			}
			else if(bases[0] == true && bases[1] == true)
				bases[2] = true;
			else if(bases[0] == true)
				bases[1] = true;
			else
				bases[0] = true;
			cout << "BB or HBP";
		}
		else if (outcome == "1B")
		{
			if (bases[2])
			{
				if (isTop==true)
					awayRuns++;
				else
					homeRuns++;
				bases[2] = false;
			}
			
			if (bases[1])
			{
				bases[2]=true;
				bases[1]=false;
			}

			if(bases[0])
				bases[1]=true;
			
			bases[0]=true;
			cout << "Single";
		}
		else if (outcome == "2B")
		{
			if (bases[2])
			{
				if (isTop==true)
					awayRuns++;
				else
					homeRuns++;
				bases[2] = false;
			}
			if (bases[1])
			{
				if (isTop==true)
					awayRuns++;
				else
					homeRuns++;
				bases[1] = false;
			}
			if (bases[0])
			{
				bases[2]=true;
				bases[0]=false;
			}

			bases[1] = true;

			cout << "Double";
		}
		else if (outcome == "3B")
		{
			for (bool b : bases)
			{
				if (b)
				{
					if (isTop==true)
						awayRuns++;
					else
						homeRuns++;
				}

			}			
			bases[0] = false;		
			bases[1] = false;
			bases[2] = true;
			cout << "Triple";
		}

		else if (outcome == "HR")
		{

			for(int i=0; i<=3; i++)
			{
				if (i == 3 || bases[i])
				{
					if (isTop==true)
						awayRuns++;
					else
						homeRuns++;
				}
				if (i<3)				
					bases[i]=false;
			}
			cout << "Home Run";
		}	
		else if(outcome == "GO")
		{
			outs++;
			if ( (bases[2] && outs<3 && !bases[0]) || (bases[2] && outs<2) )
			{
					bases[2]=false;
					if (isTop==true)
						awayRuns++;
					else
						homeRuns++;
												
			}
			if (bases[0] && outs <3)
			{				
					bases[0]=false;
					outs++;					
					if(bases[1])
					{
						bases[1]=false;
						bases[2]=true;
					}
			}			
			

			cout << "A ground out occured ";			
		}
		else if(outcome == "FO")
		{
			outs++;
			if (bases[2] && outs<3)
			{
					bases[2]=false;
					if (isTop==true)
						awayRuns++;
					else
						homeRuns++;
					
			}
			cout << "A fly out occured ";			
		}
		else
		{
			outs++;
			cout << "An out occured ";		
		}
				

		if (outs >=3)
		{
			
			if (!isTop) //bottom
			{
				
				cout << "\n\n  " + to_string(bases[1]) +  "                " << away.getName() << ": " + to_string(awayRuns) + 
						"    " << home.getName() << ": " + to_string(homeRuns) << endl;		
				cout <<  to_string(bases[2]) + "   " + to_string(bases[0])  + "              " + tbinning + "           Outs " + to_string(outs);
				cout <<"\n\n*********************************************************************************************   "<<endl;
				tbinning = "↑ " + to_string(inn);				
			}		
			else
			{
				
				cout << "\n\n  " + to_string(bases[1]) +  "                " << away.getName() << ": " + to_string(awayRuns) + 
							"    " << home.getName() << ": " + to_string(homeRuns) << endl;		
				cout <<  to_string(bases[2]) + "   " + to_string(bases[0])  + "              " + tbinning + "           Outs " + to_string(outs);	
				cout <<"\n\n*********************************************************************************************   "<<endl;
				tbinning = "↓ " + to_string(inn);
			} //↑
			if ( (!isTop && inn >=9 &&  (awayRuns != homeRuns) )  || (isTop && inn ==9 && homeRuns>awayRuns))
			{
				cout << "\n Game Over \n\n";
				break;
			}
			if (!isTop) //bottom
			{
				inn++;
			}
			
			isTop = !isTop;
			
			
			for (int i=0; i<3; i++)
			{
				bases[i] = false;
			}
			outs=0;
			selection = cin.get();
			//cout << endl;
		}			
		cout<<endl<<endl;
	}/**/
}
