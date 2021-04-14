make_and_run: map2.o tree2.o leaf.o row.o
	gcc -Wall -o map2 map2.c tree2.o leaf.o row.o -g -lm
	./map2 data.csv output.txt < input.txt
	./map2 CLUEdata2018_median.csv output.txt < input.txt    
	./map2 CLUEdata2018_random.csv output.txt < input.txt
	./map2 CLUEdata2018_sortx.csv output.txt < input.txt
    
map2.o: map2.c tree2.h leaf.h row.h
	gcc -Wall -c map2.c -lm

tree2.o: tree2.c tree2.h leaf.h row.h
	gcc -Wall -c tree2.c -lm

leaf.o: leaf.c leaf.h row.h
	gcc -Wall -c leaf.c -lm

row.o: row.c row.h
	gcc -Wall -c row.c -lm


clean:
	rm map2 map2.o tree2.o row.o