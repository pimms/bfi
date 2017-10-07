LIBS=
CXX := gcc
CFLAGS = -Wall -g

SOURCEDIR := src
OBJECTDIR := obj
BUILDDIR := build


UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
	#CFLAGS += -L/opt/local/lib
	#CFLAGS += -I/opt/local/include
endif


# Get all .c files
SRC := $(shell find $(SOURCEDIR) -name '*.c')

# Get all the .o files
OBJECTS := $(addprefix $(OBJECTDIR)/,$(notdir $(SRC:%.c=%.o)))

# Name of application
NAME = bfi

all: $(NAME)

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c
	$(CXX) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CXX) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

clean:
	@echo "** Removing object files and executable..."
	rm -f $(NAME) $(OBJECTS)
