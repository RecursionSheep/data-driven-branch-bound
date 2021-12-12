CC = g++
STD11 = -std=c++11
CFLAGS = -g
OPT = -O2
DEPS = milp.h parser.h treenode.h lp.h
OBJ = bb.o milp.o parser.o treenode.o lp.o
INCLUDE = -I ../gurobi911/linux64/include
LIBS = -L ../gurobi911/linux64/lib -lgurobi_c++ -lgurobi91

main: bb

bb: $(OBJ) bb.o
	$(CC) -o $@ $^ $(OPT) $(STD11) $(LIBS) $(INCLUDE)

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(OPT) $(STD11) $(LIBS) $(INCLUDE)

clean:
	rm *.o
