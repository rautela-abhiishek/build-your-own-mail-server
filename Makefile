flags=-02 -Wall -std=c2x
ldflags=-lbu

.PHONY: all clean


all: clean email client

email:email.o
cc $(flags) $^ -o $@ $(lsflags)

email.o: email.c email.h
cc $(flags) -c $<

client.o: client.c email.h
cc $(flags) -c $<

client: client.o
cc $(flags) $^ -o $@ $(ldflags)

client.o: client.c email.h
cc $(flags) -c $<

clean: 
rm -f *.o email client
