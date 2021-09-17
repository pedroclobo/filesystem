CC=gcc
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -g

all:: proj2
proj2:
	$(CC) $(CFLAGS) src/*.c -o proj2
tests::
	$(MAKE) $(MFLAGS) -C tests
clean::
	rm -f proj2 a.out *.o core tests/*.diff *.zip *.*~
zip::
	zip proj2.zip src/*.c src/*.h
