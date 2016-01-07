# Makefile for creating 'CourseGraph' program

CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS = -lStack
OBJS = main.o DependGraph.o
RM = rm -f
PROG = CourseGraph

# Creating the exectuable (CourseGraph)
$(PROG):$(OBJS)
	$(CCLINK) -o $(PROG) -L. $(OBJS) $(LIBS)

# Creating object files using default rules
main.o: main.c DependGraph.h Defines.h Stack.h
DependGraph.o: DependGraph.h DependGraph.c Defines.h Stack.h

# Cleaning old files before new make
clean:
	$(RM) $(PROG) *.o *.bak *~ "#"* core