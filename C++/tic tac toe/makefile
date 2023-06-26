# CC / CXX
# CFLAGS / CXXFLAGS
# LDFLAGS
# LIB
# SRC
# OBJ
# EXEC

CXX = g++
EXEC = out
TEMP = off
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all : $(EXEC)
	
$(EXEC) : $(OBJ)
	$(CXX) -std=c++20 -o $@ $^

%.o : %.cpp
	$(CXX) -std=c++20 -o $@ -c $<

clean :
	rm *.o

mrproper: clean
	rm *.exe

# variables spéciales
# $@ nom cible
# $< nom première dépendance
# $^ liste dépendance
# $? liste dépendance plus récentes de la cible
# $* nom du fichier, sans son extension