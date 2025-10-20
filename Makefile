# Makefile for Lab 3 – Processes and Pipes
# Author: Johan Lingani (PrinceAudacity)
# Description: Builds pipe-based interprocess communication programs

CC = gcc
CFLAGS = -Wall -std=c99 -Werror

# Targets
TARGET1 = pipes1
TARGET2 = pipes2
TARGET3 = pipes3

SRC1 = pipes_processes1.c
SRC2 = pipes_processes2.c
SRC3 = pipes_processes3.c

all: $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET1): $(SRC1)
	$(CC) $(CFLAGS) -o $(TARGET1) $(SRC1)

$(TARGET2): $(SRC2)
	$(CC) $(CFLAGS) -o $(TARGET2) $(SRC2)

$(TARGET3): $(SRC3)
	$(CC) $(CFLAGS) -o $(TARGET3) $(SRC3)

clean:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3)
