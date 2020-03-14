fixedframes : FixedFrames.o GameClock.o
	g++ -o fixedframes FixedFrames.o GameClock.o
FixedFrames.o : FixedFrames.cpp
	g++ -c FixedFrames.cpp
GameClock.o : GameClock.cpp GameClock.h
	g++ -c GameClock.cpp