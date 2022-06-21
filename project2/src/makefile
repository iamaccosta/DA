Proj2: main.o App.o Scenarios.o
	g++ main.o App.o Scenarios.o -o proj2

main.o: main.cpp
	g++ -c main.cpp

App.o: App.cpp
	g++ -c App.cpp

Scenarios.o: Scenarios.cpp
	g++ -c Scenarios.cpp
	
clean:
	rm *.o proj2