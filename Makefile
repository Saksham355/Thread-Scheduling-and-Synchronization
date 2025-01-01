all: Q1 Q2 Q3 Q4i Q4ii 
Q1: Q1.c
	gcc -o Q1 Q1.c
Q2: Q2.c
	gcc -o Q2 Q2.c
Q3: Q3.c
	gcc -o Q3 Q3.c
Q4i: Q4i.c
	gcc -o Q4i Q4i.c
Q4ii: Q4ii.c
	gcc -o Q4ii Q4ii.c

clean: 
	rm -f Q1 Q2 Q3 Q4i Q4ii