CC = gcc
CFLAGS = -Wall -Iinclude

all: matrix_test data_loader_test tiff_test

matrix_test: tests/matrix_test.c src/matrix.c
	$(CC) $(CFLAGS) $^ -o $@

data_loader_test: tests/data_loader_test.c src/data_loader.c src/matrix.c src/tiff.c
	$(CC) $(CFLAGS) $^ -o $@

tiff_test: tests/tiff_test.c src/tiff.c src/matrix.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f matrix_test data_loader_test tiff_test
