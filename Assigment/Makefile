PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = Assigment.o

USER_LIBS = -lcurl

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -g
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -O2
else
	$(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

all:	Assigment

Assigment:	$(OBJS)
	$(CXX) -o $@ $^ 


%.o:	$(PROJECT_ROOT)%.c
	$(CC)  -c $(CFLAGS) $(CPPFLAGS)   -o $@ $< 

clean:
	rm -fr Assigment $(OBJS)
