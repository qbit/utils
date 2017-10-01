CC=cc

all: bin/battery bin/ac bin/pledge

clean:
	rm -f bin/*

bin/battery: battery.c
	${CC} $> -o $@

bin/ac: ac.c
	${CC} $> -o $@

bin/pledge: pledge.c
	${CC} $> -o $@

install:
	cp bin/* ~/bin/
