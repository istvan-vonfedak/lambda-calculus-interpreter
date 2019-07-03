CC = g++
CDFLAGS =
SRC = main.cpp lexicalAnalyser.cpp parser.cpp betaReducer.cpp
OBJ = $(SRC:%.cpp=%.o)
EXE = lambdaReducer

all: $(EXE)
	@echo Done!
	@echo
	@echo Usage: ./$(EXE)
	@echo \ \ \ or: ./$(EXE) -debug

$(EXE): $(OBJ)
	@echo Linking...
	@$(CC) $(OBJ) -o $@

$(OBJ): $(SRC)
	@echo Compiling...
	@$(CC) $(CDFLAGS) -c $(SRC) $<

clean:
	@echo Cleaning up...
	@rm -f *.o
	@rm -f *.core
	@rm -f *.out
	@rm -f $(EXE)
