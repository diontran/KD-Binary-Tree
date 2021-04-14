make_and_run: map1.o tree1.o leaf.o row.o
	gcc -Wall -o map1 map1.c tree1.o leaf.o row.o -g -lm
	./map1 data.csv output.txt < input.txt
    
map1.o: map1.c tree1.h leaf.h row.h
	gcc -Wall -c map1.c -lm

tree1.o: tree1.c tree1.h leaf.h row.h
	gcc -Wall -c tree1.c -lm

leaf.o: leaf.c leaf.h row.h
	gcc -Wall -c leaf.c -lm

row.o: row.c row.h
	gcc -Wall -c row.c -lm


clean:
	rm map1 map1.o tree1.o row.o