CFLAGS = -L C:/raylib/raylib/src -I C:/raylib/raylib/src
LFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

main:
	gcc $(CFLAGS) main.c $(LFLAGS) -o main.exe 