OBJ = main.o Population.o Member.o
all: $(OBJ)
	g++ -o genetic $(OBJ)

main.o: main.cc
	g++ -c main.cc

Population.o: Population.cc Population.h
	g++ -c Population.cc

Member.o: Member.cc Member.h
	g++ -c Member.cc

clean:
	rm *.o genetic
