CC=gcc
CFLAGS=-g -Wall
OBJECTS=main.o guessword.o flashcard.o hangman.o managedic.o
TARGET=EnglishStudyProgram

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(TARGET)

clean: 
	rm -f *.o 
	rm -f $(TARGET)
