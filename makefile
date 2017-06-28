CC=g++

# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-g -c -Wall -std=gnu++11 
LDFLAGS=

SOURCES=Neighbourhood.cpp watershedTest.cpp watershedTransform.cpp Point.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=watershedTest

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

#all:watershedTest

#watershedTest: Neighbourhood.o watershedTest.o watershedTransform.o
#	$(CC) Neighbourhood.o watershedTest.o watershedTransform.o -o test

#Neighbourhood.o: Neighbourhood.cpp
#	$(CC) $(CFLAGS) Neighbourhood.cpp

#watershedTest.o: watershedTest.cpp
#	$(CC) $(CFLAGS) watershedTest.cpp

#watershedTransform.o: watershedTransform.cpp
#	$(CC) $(CFLAGS) watershedTransform.cpp

clean:
	rm -f *.o $(EXECUTABLE)

