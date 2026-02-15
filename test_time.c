#include <stdio.h>
#include <sys/time.h>

double getCurrentTime();

double tester(void (*func)());

void print_without_for();

void print_with_for();

void print_with_file();



int main(){
    double average=0;
    for (int i=0; i<5; i++) {
        average += tester(print_without_for);
    }
    printf("%lf\n", average/5);
    
    average=0;
    for (int i=0; i<5; i++) {
        average += tester(print_with_for);
    }
    printf("%lf\n", average/5);
    
    average=0;
    for (int i=0; i<5; i++) {
        average += tester(print_with_for);
    }
    printf("%lf\n", average/5);

    return 0;
}


double getCurrentTime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    // to get the time in seconds using tv.tv_sec + time in macroseconds (divided by 1000000 to be second)
    return tv.tv_sec + tv.tv_usec / 1000000.0;
    
}


double tester(void (*function)()){
    double cpu_time_used, start, end;
    start = getCurrentTime();

    function();

    end = getCurrentTime();

    return (end - start)* 1000.0;
}


void print_without_for(){
    printf(". . . . . \n. . . . .\n. . . . .\n. . . . .\n. . . . .\n");
}


void print_with_for(){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++)
            printf(". ");
        printf("\n");
    }
}
void print_with_file(){
    FILE *fp = fopen("file.txt", "r");
    if (!fp) return;
    char buff[256];
    while (fgets(buff, sizeof(buff), fp)) {
        printf("%s", buff);
    }
    fclose(fp);
}