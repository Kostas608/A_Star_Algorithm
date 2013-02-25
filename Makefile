default:
	gcc Main.c -lm -o Astar

clean:
	-rm -f Astar

run:
	./Astar
