CC=g++


default:
	mkdir -p compiled
	$(CC) -fPIC -Wall -shared libc/stegaxor.cpp -o compiled/stegaxor.so
