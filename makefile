CC=g++

# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.

ifndef PREFIX
	PREFIX := /usr/local
endif


#CFLAGS=-g -c -Wall -std=gnu++11 `GraphicsMagick++-config --cppflags --cxxflags`
#CFLAGS=-g -c -Wall -std=gnu++11  -Wcpp  -I$(PREFIX)/include/ImageMagick-7 
CFLAGS=-g -c -Wall -std=gnu++11 `Magick++-config --cppflags --cxxflags`
#LDFLAGS= -L$(PREFIX)/lib -lMagick++-7.Q16HDRI -lMagickCore-7.Q16HDRI -lMagickWand-7.Q16HDRI
LDFLAGS= `Magick++-config --ldflags --libs`

SOURCES=Neighbourhood.cpp watershedTest.cpp watershedTransform.cpp HoodPoint.cpp
#SOURCES=watershedTest.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=watershedTest

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS) 

.cpp.o:
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) 

clean:
	rm -f *.o $(EXECUTABLE)

