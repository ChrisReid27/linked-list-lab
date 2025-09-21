# list/Makefile
#
# Makefile for list implementation and test file.
#
# <Author>

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -gcc

all: list

list: list.c main.c list.h
  $(CC) $(CFlAGS) -o list main.c list.c
	//gcc list.c main.c -o list

clean:
  rm -f list *.o
