kapish: kapish.o doublylinkedlist.o
	gcc kapish.o doublylinkedlist.o -o kapish

kapish.o: kapish.c
	gcc -c kapish.c -o kapish.o -Wall -Werror

doublylinkedlist.o: doublylinkedlist.c
	gcc -c doublylinkedlist.c -o doublylinkedlist.o -Wall -Werror

clean:
	rm -rf *.o kapish