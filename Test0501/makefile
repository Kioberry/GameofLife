vpath %.h include
vpath %.c src
vpath %.c unit_test

objects = game.o test_fun.o 
test:test_main.c $(objects)
	gcc -I include $^ -o $@ -lcheck -lsubunit -lm -lpthread -lSDL2 -lSDL2_image

all:$(objects)
$(objects): %.o : %.c
	gcc -c -I include $< -o $@

.PHONY:clean
clean:
	rm -f *.o *.txt test

