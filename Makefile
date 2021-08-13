all : 
	gcc *.c 
s : 
	gcc server.c print_util.c -o s

c : 
	gcc client.c print_util.c -o c
clean:
	rm s c
