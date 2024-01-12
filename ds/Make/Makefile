TARGETS := slist bit_arr cbuff dlist sorted_list p_queue

CC = gcc

SRC_DIRS := ./src
INC_DIRS := ./include
TEST_DIRS := ./test

# Add a prefix to INC_DIRS. So './include' would become '-iquote./include'. 
# GCC understands this flag
INC_FLAGS := $(addprefix -iquote,$(INC_DIRS))

CPPFLAGS := $(INC_FLAGS) -ansi -pedantic-errors -Wall -Wextra
DEBUG_FLAG = -g
RELEASE_FLAGS := -DNDEBUG -O3

ifeq '$(findstring release,$(MAKECMDGOALS))' 'release'
$(eval CPPFLAGS += $(RELEASE_FLAGS))
else
$(eval CPPFLAGS += $(DEBUG_FLAG))
endif

# Adding math.h flag to LDFLAGS
LDFLAGS += -lm


p_queue.out: sorted_list.o dlist.o p_queue_test.o
	$(CC) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

p_queue_test.o: $(SRC_DIRS)/p_queue.c $(INC_DIRS)/p_queue.h $(TEST_DIRS)/p_queue_test.c
	$(CC) $(CPPFLAGS) -c $^ -o $@ $(LDFLAGS)


sorted_list.o: $(SRC_DIRS)/sorted_list.c $(INC_DIRS)/sorted_list.h
	$(CC) $(CPPFLAGS) -c $^ -o $@ $(LDFLAGS)

dlist.o: $(SRC_DIRS)/dlist.c 
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)



fooer.out: foo.o main.o
	$(CC) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

main.o: main.c
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

foo.o: foo.c
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

.PHONY: clean, all, debug, release
clean:
	-@rm -f *.o
	-@rm -f *.out
	@echo 'cleaning done'

all: $(TARGETS)

debug: $(filter $(MAKECMDGOALS),$(TARGETS))
	
release: $(filter $(MAKECMDGOALS),$(TARGETS))

$(TARGETS): %: %.o %_test.o
	$(CC) $(CPPFLAGS) $^ -o $(addsuffix .out,$@) $(LDFLAGS)

%.o: $(SRC_DIRS)/%.c
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

%_test.o: $(TEST_DIRS)/%_test.c
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)
