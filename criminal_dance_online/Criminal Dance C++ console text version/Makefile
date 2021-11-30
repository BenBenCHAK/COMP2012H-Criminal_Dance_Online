EXE := Criminal_Dance_console_text_version.exe
SOURCES := Card.cpp GameEngine.cpp main.cpp Player.cpp
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))

COMPILER := g++
COMPILER_FLAGS := -std=c++11

ifeq (Windows_NT, $(OS))
RM := del
else
RM := rm -f
endif

.PHONY: all
all: $(EXE)

$(EXE): $(OBJECTS)
	$(COMPILER) -o $@ $^

%.o: %.cpp
	$(COMPILER) $(COMPILER_FLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) $(EXE) $(OBJECTS)
