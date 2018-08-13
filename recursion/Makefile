DEPEND_FILE = depend_file

CC = gcc

SRCS = *.c
COMMON_OBJS =
TARGET = factorial
INCLUDE_PATH=../include
CFLAGS = -I$(INCLUDE_PATH) -g -ggdb
LFLAGS = -lm -lcriterion

.SUFFIXES : .c .o

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPEND_FILE)
endif
.DEFAULT_GOAL := all

all : $(TARGET)

#$(TARGET) : $(OBJS)
#	$(CC) -o $@ $(OBJS) $(LFLAGS)

factorial : factorial.o
	$(CC) $(CFLAGS) -o $@ $? $(COMMON_OBJS) $(LFLAGS)

depend :
	$(CC) $(CFLAGS) -MM $(SRCS) > $(DEPEND_FILE)

clean :
	rm -f *.o $(OBJS) $(TARGET) a.out
