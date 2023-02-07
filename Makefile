options:
	@echo Options: client or server

client: five_clients.o
	gcc -g five_clients.o -lpthread -o client

server: db.o query.o validate.o thread_server.o
	gcc -g  db.o query.o validate.o thread_server.o -lpthread -o server

db.o: db.c
	gcc -g -Wall -c db.c

query.o: query.c
	gcc -g -Wall -c query.c

validate.o: validate.c
	gcc -g -Wall -c validate.c

thread_server.o: thread_server.c 
	gcc -g -Wall -c thread_server.c

five_clients.o: five_clients.c 
	gcc -g -Wall -c five_clients.c

clean:
	@rm -f *.o server client