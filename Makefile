obj-m += driver.o
all:
	gcc -Wall -pedantic -nostdinc -c -ansi main.c
kern:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
