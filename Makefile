#
# Makefile
#
# Copyright (c) 2019 TakedaHiromasa <t-takeda.work>
#

AR	?= ar
CC	?= gcc
CFLAGS = -O3 -std=c99 -Wall -Wextra -Ideps

SRCDIR = ./src
SRCS   = list.c \
		 list_iterator.c

BINDIR	 = ./bin
BUILDDIR = ./build
OBJDIR	 = ./obj
OBJS	 = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: clean build/liblist.a

$(BUILDDIR)/liblist.a: $(OBJS)
	@mkdir -p $(@D)
	$(AR) rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	rm -fr *.o $(BUILDDIR) $(OBJDIR) $(BINDIR)

test: $(BINDIR)/test
	@./$<

$(BINDIR)/test: $(OBJDIR)/test.o $(OBJS)
	@mkdir -p $(@D)
	$(CC) $^ -o $@