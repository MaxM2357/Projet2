SRCS = salesman.c town.c tour.c tsp.c easyppm.c
OBJS = $(SRCS:%.c=%.o)
CC = gcc
PROG = salesman
FILE = xy-belgium-towns.csv

CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99
LDFLAGS = -lm

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: clean run

clean:
	$(RM) $(OBJS) $(PROG)

run: $(PROG)
	./$(PROG) $(FILE)

runwin: $(PROG)
	$(PROG).exe
