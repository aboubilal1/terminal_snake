#include <stdio.h>
#include <synchapi.h>
#include <windows.h>  // For Sleep()
#include <sys/time.h>
#include <conio.h>

#include "../header/grid.h"


int main() {
    // Initialize game grid, snake position, etc.
    // int dir;  // Default right
    // while (1) {  // Game loop
    //     system("cls");
    //     if (kbhit()) {
    //         dir = getch();  // Real-time input
    //         if (dir == 'q') break;  // ESC to quit
    //     }
    //     printf("the pressed key is %d\n", dir);
    //     Sleep(100);
    //     // Update snake position based on dir
    //     // Check collisions, draw, Sleep(100);
    // }
    


    // printf("%f!= %d", (float)(1000/24), (int)5.4);



    // for(int i = 0; i < 5; i++){
    //     for(int j = 0; j < 5; j++)
    //         printf(". ");
    //     printf("\n");
    // }



    grid *g;
    init_grid(&g, 5, 5, '.');
    print_grid(g);

    Sleep(100);

    set_point_in_grid(g, 2, 2, '@');
    

    return 0;
}