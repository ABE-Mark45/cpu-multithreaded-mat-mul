all:
	echo Linking and compiling all files
	gcc -g -Wall -pthread matrix.c thread_manager.c mat_mul.c -o matmult.out
	echo Compilation successful. Executable is matmult.out