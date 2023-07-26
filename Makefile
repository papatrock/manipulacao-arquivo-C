CFLAGS = -Wall -std=c99

objs = gps.o liblista.o funcao.o

all = gps

gps: $(objs)
	gcc $(CFLAGS) -o gps $(objs)

gps.o: gps.c funcao.h
	gcc $(CFLAGS) -c gps.c 

funcao.o: funcao.c funcao.h liblista.h
	gcc $(CFLAGS) -c funcao.c 

liblista.o: liblista.c liblista.h funcao.h
	gcc $(CFLAGS) -c liblista.c


clean:
	rm -f *~ *.o

purge: clean
	rm -f gps
