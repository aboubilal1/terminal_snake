:: to generat the executable
gcc -Wall -Wextra -std=c11 body_part.h node.h app.c body_ds.c dir_queue.c grid.c snake.c -o program.exe

:: call the executable
program.exe