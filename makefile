# Makefile for creating 'students' program

CCC = g++
CXXFLAGS = -g -Wall
CXXLINK = $(CCC)
LIBS = 
OBJS = main.o StArray.o Student.o Person.o CS_Course.o EE_Course.o Course.o
RM = rm -f
PROG = students

#default traget
all: $(PROG)

# Creating the executable (students)
$(PROG): $(OBJS)
	$(CXXLINK) -o $(PROG) $(OBJS) $(LIBS)
  
# Creating object files using default rules
StArray.o: StArray.H StArray.C Student.H CS_Course.H EE_Course.H Proj.H
Student.o: Student.H Student.C Person.H CS_Course.H EE_Course.H Proj.H
Person.o: Person.H Person.C Proj.H
CS_Course.o: CS_Course.H CS_Course.C Course.H
EE_Course.o: EE_Course.H EE_Course.C Course.H
Course.o: Course.H Course.C
main.o: main.C StArray.H Student.H Person.H CS_Course.H EE_Course.H Course.H Proj.H
  
# Cleaning old files before new make
clean:
	$(RM) $(PROG) *.o *.bak *~ "#"* core