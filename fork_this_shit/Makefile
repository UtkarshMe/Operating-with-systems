
# Add all targets here
BINARIES=simple_fork child_status child_exec

all: $(BINARIES)


simple_fork: simple_fork.o
	gcc -o simple_fork simple_fork.o
simple_fork.o: simple_fork.c
	gcc simple_fork.c -c


child_status: child_status.o
	gcc -o child_status child_status.o
child_status.o: child_status.c
	gcc child_status.c -c


child_exec: child_exec.o
	gcc -o child_exec child_exec.o
child_exec.o: child_exec.c
	gcc child_exec.c -c


.PHONY: clean
clean:
	rm -f *.o $(BINARIES)
