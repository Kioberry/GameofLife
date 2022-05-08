vpath %.h include
vpath %.c src
vpath %.c unit_test

objects = utility.o game.o test_fun.o 
test:test_main.c $(objects)
	gcc -I include $^ -o $@ -lcheck -lsubunit -lm -lpthread

all:$(objects)
$(objects): %.o : %.c
	gcc -c -I include $< -o $@

.PHONY:clean
clean:
	rm *.o
