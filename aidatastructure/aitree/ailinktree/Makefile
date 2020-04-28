AI_OBJ := ai_link_tree
AI_COMPLIER := gcc
AI_CFLAGS := -Wall -lm

.PHONY : clean
all:$(AI_OBJ)

$(AI_OBJ) : $(AI_OBJ).o
	$(AI_COMPLIER) $(AI_CFLAGS) -o $@ $<
	

%.o : %.c
	$(AI_COMPLIER) -c $(AI_CFLAGS) -o $@ $<


clean:
	-rm -rf $(AI_OBJ) *.o
