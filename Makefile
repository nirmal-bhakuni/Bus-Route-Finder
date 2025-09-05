CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = backend_c/graph.o backend_c/ticket.o backend_c/management.o backend_c/utils.o backend_c/main.o

all: bus_train_route_finder

bus_train_route_finder: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

backend_c/graph.o: backend_c/graph.c backend_c/graph.h
	$(CC) $(CFLAGS) -c $< -o $@

backend_c/ticket.o: backend_c/ticket.c backend_c/ticket.h
	$(CC) $(CFLAGS) -c $< -o $@

backend_c/management.o: backend_c/management.c backend_c/management.h
	$(CC) $(CFLAGS) -c $< -o $@

backend_c/utils.o: backend_c/utils.c backend_c/utils.h
	$(CC) $(CFLAGS) -c $< -o $@

backend_c/main.o: backend_c/main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) bus_train_route_finder

.PHONY: all clean