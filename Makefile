CXX := g++
CXXFLAGS := -g -ggdb -std=c++17 -O0
INCFLAGS := -Iinclude

SRCDIR := ./src
OBJDIR := ./obj
TARGETDIR := ./bin
TARGET := $(notdir $(CURDIR))

SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

.PHONY: clean

all: create $(TARGETDIR)/$(TARGET)

A2: create/A2 $(SRCDIR)/A2/bin/A2 A2Data

$(SRCDIR)/A2/bin/A2: $(patsubst $(SRCDIR)/A2/%.cpp, ./src/A2/$(OBJDIR)/%.o, $(wildcard $(SRCDIR)/A2/*.cpp))
	$(CXX) -o $@ $^ $(INCFLAGS) $(CXXFLAGS)

$(SRCDIR)/A2/$(OBJDIR)/%.o: $(SRCDIR)/A2/%.cpp
	$(CXX) -c $< -o $@ $(INCFLAGS) $(CXXFLAGS)

A2Data:
	cp $(SRCDIR)/A2/states.csv ./src/A2/$(TARGETDIR)


$(TARGETDIR)/$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(INCFLAGS) $(CXXFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@ $(INCFLAGS) $(CXXFLAGS)

create:
	mkdir -p $(OBJDIR)
	mkdir -p $(TARGETDIR)

create/A2:
	mkdir -p ./src/A2/$(OBJDIR)
	mkdir -p ./src/A2/$(TARGETDIR)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(TARGETDIR)

clean/A2:
	rm -rf ./src/A2/$(OBJDIR)
	rm -rf ./src/A2/$(TARGETDIR)
