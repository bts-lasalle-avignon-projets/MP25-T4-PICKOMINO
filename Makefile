TARGET = pickomino.out
MAIN = main

DOSSIER_INCLUDE = ./src
DOSSIER_SRC = ./src
DOSSIER_TESTS = ./tests

HEADERS := $(wildcard $(DOSSIER_INCLUDE)/*.h)
SRC := $(wildcard $(DOSSIER_SRC)/*.cpp)
OBJ := $(strip $(patsubst %.cpp, %.o, $(SRC)))

CFLAGS = -std=c++11 -Wall -I$(DOSSIER_INCLUDE)
LDFLAGS =
CXX = g++ $(CFLAGS) -c
LD = g++ -o
RM = rm -f

# Compilation de l'exécutable principal
all: $(TARGET)

$(TARGET): $(OBJ)
	$(LD) $@ $(LDFLAGS) $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CFLAGS) -o $@ $<


testUnitaire: $(DOSSIER_TESTS)/testUnitaire.out
	$(DOSSIER_TESTS)/testUnitaire.out

testCalculScore: $(DOSSIER_TESTS)/testCalculScore.out
	$(DOSSIER_TESTS)/testCalculScore.out

testGarderDe: $(DOSSIER_TESTS)/testGarderDe.out
	$(DOSSIER_TESTS)/testGarderDe.out

$(DOSSIER_TESTS)/testUnitaire.out: $(DOSSIER_TESTS)/testUnitaire.o $(DOSSIER_TESTS)/testCalculScore.o $(DOSSIER_SRC)/plateau.o $(DOSSIER_SRC)/ihm.o $(DOSSIER_SRC)/joueur.o $(DOSSIER_SRC)/jeu.o
	$(LD) $@ $(LDFLAGS) $^

$(DOSSIER_TESTS)/testCalculScore.out: $(DOSSIER_TESTS)/testUnitaire.o $(DOSSIER_TESTS)/testCalculScore.o $(DOSSIER_SRC)/plateau.o $(DOSSIER_SRC)/ihm.o
	$(LD) $@ $(LDFLAGS) $^

$(DOSSIER_TESTS)/testGarderDe.out: $(DOSSIER_TESTS)/testUnitaire.o $(DOSSIER_TESTS)/testGarderDe.o $(DOSSIER_SRC)/plateau.o $(DOSSIER_SRC)/ihm.o
	$(LD) $@ $(LDFLAGS) $^
	
$(DOSSIER_TESTS)/testUnitaire.o: $(DOSSIER_TESTS)/testUnitaire.cpp $(HEADERS)
	$(CXX) -o $@ $<

$(DOSSIER_TESTS)/testCalculScore.o: $(DOSSIER_TESTS)/testCalculScore.cpp $(HEADERS)
	$(CXX) -o $@ $<

$(DOSSIER_TESTS)/testGarderDe.o: $(DOSSIER_TESTS)/testGarderDe.cpp $(HEADERS)
	$(CXX) -o $@ $<

# Nettoyage des fichiers générés
.PHONY: clean cleanall

clean:
	$(RM) $(DOSSIER_SRC)/*.o $(DOSSIER_SRC)/*.*~ $(DOSSIER_TESTS)/*.o $(DOSSIER_TESTS)/*.*~

cleanall:
	$(RM) $(DOSSIER_SRC)/*.o $(DOSSIER_SRC)/*.*~ $(TARGET) $(DOSSIER_TESTS)/*.o $(DOSSIER_TESTS)/*.*~
