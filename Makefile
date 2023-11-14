# Makefile
# Authors: Gonçalo Bárias (ist1103124)
#          Raquel Braunschweig (ist1102624)

CXX ?= g++
LD ?= g++
FORMATTER ?= clang-format

SRC := src
INCLUDE_DIRS := $(SRC)/user $(SRC)/server $(SRC)/
INCLUDES = $(addprefix -I, $(INCLUDE_DIRS))

USER_SOURCES := $(wildcard $(SRC)/user/*.cpp)
SERVER_SOURCES := $(wildcard $(SRC)/server/*.cpp)
LIB_SOURCES := $(wildcard $(SRC)/lib/*.cpp)
SOURCES := $(USER_SOURCES) $(SERVER_SOURCES) $(LIB_SOURCES)

USER_HEADERS := $(USER_SOURCES:.cpp=.hpp)
SERVER_HEADERS := $(SERVER_SOURCES:.c=.hpp)
LIB_HEADERS := $(LIB_SOURCES:.c=.hpp)
HEADERS := $(USER_HEADERS) $(SERVER_SOURCES) $(LIB_HEADERS)

USER_OBJECTS := $(USER_SOURCES:.cpp=.o)
SERVER_OBJECTS := $(SERVER_SOURCES:.c=.o)
LIB_OBJECTS := $(LIB_SOURCES:.c=.o)
OBJECTS := $(USER_OBJECTS) $(SERVER_OBJECTS) $(LIB_OBJECTS)

USER_EXEC := user
SERVER_EXEC := AS
TARGET_EXECS := $(USER_EXEC) $(SERVER_EXEC)

# vpath %.hpp <DIR> tells make to look for header files in <DIR>
vpath # clears VPATH
vpath %.hpp $(INCLUDE_DIRS)

# CXXFLAGS is a variable that defines the compiler flags
CXXFLAGS = -std=c++17
CXXFLAGS += $(INCLUDES)
# Warnings
CXXFLAGS += -fdiagnostics-color=always -Wall -Werror -Wextra -Wcast-align -Wconversion -Wfloat-equal -Wformat=2 -Wnull-dereference -Wshadow -Wsign-conversion -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wno-sign-compare

LDFLAGS = -std=c++17
LDFLAGS += $(INCLUDES)
LDFLAGS += -pthread

# optional debug symbols: run make DEBUG=yes to activate them
ifeq ($(strip $(DEBUG)), yes)
  CXXFLAGS += -g -fsanitize=address
endif

# optional O3 optimization symbols: run make OPTIM=no to deactivate them
ifeq ($(strip $(OPTIM)), no)
  CXXFLAGS += -O0
else
  CXXFLAGS += -O3
endif

.PHONY: all clean fmt fmt-check package

# must be the first target in the Makefile
all: $(TARGET_EXECS)

$(USER_EXEC): $(USER_OBJECTS) $(LIB_OBJECTS)
$(SERVER_EXEC): $(SERVER_OBJECTS) $(LIB_OBJECTS)

clean:
	rm -f $(TARGET_EXECS) $(OBJECTS) proj_GXX.zip readme.txt

fmt: $(SOURCES) $(HEADERS)
	$(FORMATTER) -i $^

fmt-check: $(SOURCES) $(HEADERS)
	$(FORMATTER) -n --Werror $^

package: clean
	cp README.md readme.txt
	zip proj_GXX.zip $(SOURCES) $(HEADERS) Makefile .clang-format readme.txt docs/*.xlsx