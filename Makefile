build:
	gcc -Wall -g quadtree.c -o quadtree -lm
run: quadtree
	./quadtree
clean:
	rm ./quadtree