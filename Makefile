make_and_run: map1.o tree1.o leaf.o row.o map2.o tree2.o leaf.o row.o
	gcc -Wall -o map1 map1.c tree1.o leaf.o row.o -g -lm 
	gcc -Wall -o map2 map2.c tree2.o leaf.o row.o -g -lm 
    
	./map1 CLUEdata2018_random.csv output1-Random.txt < input.txt
	./map1 CLUEdata2018_median.csv output1-Median.txt < input.txt
	./map1 CLUEdata2018_sortx.csv output1-Sortx.txt < input.txt
    
	./map2 CLUEdata2018_random.csv output2-Random.txt < input2.txt
	./map2 CLUEdata2018_median.csv output2-Median.txt < input2.txt
	./map2 CLUEdata2018_sortx.csv output2-Sortx.txt < input2.txt
    
map1.o: map1.c tree1.h leaf.h row.h
	gcc -Wall -c map1.c -lm

map2.o: map2.c tree2.h leaf.h row.h
	gcc -Wall -c map2.c -lm

tree1.o: tree1.c tree1.h leaf.h row.h
	gcc -Wall -c tree1.c -lm
    
tree2.o: tree2.c tree2.h leaf.h row.h
	gcc -Wall -c tree2.c -lm

leaf.o: leaf.c leaf.h row.h
	gcc -Wall -c leaf.c -lm

row.o: row.c row.h
	gcc -Wall -c row.c -lm


clean:
	rm map1 map1.o map2 map2.o tree1.o tree2.o row.o