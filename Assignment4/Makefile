webstore:SecondaryRed Secondary ReadAndProcess Primary main
	g++ SecondaryRed.o Secondary.o ReadAndProcess.o Primary.o main.o -o webstore 
SecondaryRed:
	g++ -std=c++11 -c SecondaryRed.cpp -o SecondaryRed.o
Secondary:
	g++ -std=c++11 -c Secondary.cpp -o Secondary.o
ReadAndProcess:
	g++ -std=c++11 -c ReadAndProcess.cpp -o ReadAndProcess.o
Primary:
	g++ -std=c++11 -c Primary.cpp -o Primary.o 
main:
	g++ -std=c++11 -c main.cpp -o main.o