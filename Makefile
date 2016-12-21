all: playball

playball: baseball.o Player.o Team.o
	g++ baseball.o Player.o Team.o -o playball

baseball.o: baseball.cpp Player.h
	g++ -c -g -std=c++11 baseball.cpp -o baseball.o

Player.o: Player.cpp Player.h
	g++ -c -g -std=c++11 Player.cpp -o Player.o

Team.o: Team.cpp Team.h
	g++ -c -g -std=c++11 Team.cpp -o Team.o

clean:
	rm -f *.o playball
