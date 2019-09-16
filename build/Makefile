exe: main.o Collision.o opencvdraw.o
	g++ -o exe.out main.o collision.o opencvdraw.o $(shell pkg-config --cflags --libs opencv)

main.o: ../main.cpp
	g++ -c ../main.cpp -std=c++11

Collision.o: ../include/collision.cpp
	g++ -c ../include/collision.cpp -std=c++11

opencvdraw.o: ../include/opencvdraw.cpp
	g++ -c ../include/opencvdraw.cpp -std=c++11

clean:
	rm -f *.o