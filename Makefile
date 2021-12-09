CC = g++
STD11 = -std=c++11
CFLAGS = -g
OPT = -O2
DEPS = milp.h parser.h
OBJ = bb.o milp.o parser.o
INCLUDE = 
LIBS = 

main: bb

bb: $(OBJ) bb.o
	$(CC) -o $@ $^ $(OPT) $(STD11) $(LIBS) $(INCLUDE)

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(OPT) $(STD11) $(LIBS) $(INCLUDE)

clean:
	rm *.o
