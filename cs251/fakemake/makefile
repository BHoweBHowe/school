
hmap.o: hmap.c hmap.h
	gcc -c hmap.c

fakemake: fakemake.c hmap.h hmap.o
	gcc fakemake.c hmap.o -o fakemake

clean:
	rm -f *.o fakemake

