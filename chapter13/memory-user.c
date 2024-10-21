#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


char *reserve_memory(int megabytes) {
    char *res = malloc((size_t)megabytes * sizeof(char) * 1000000);
    if (res == NULL) {
        perror("error using malloc");
        return NULL;
    }
    return res;
}


int main(int argc, char **argv) {
    if (argc != 2 && argc != 3 && argc != 5) {
        printf("Wrong number of parameters use -h for help.");
        return 1;
    }

    printf("%d\n", getpid());

    clock_t start_time = clock();
    int megabytes = -1;
    int time_in_s = -1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            char *help_str = "Usage:\n-h -> help\n-n [number of megabytes]\n-t [runtime in s]\n";
            printf("%s", help_str);
            return 1;
        } else if (strcmp(argv[i], "-n") == 0) {
            megabytes = atoi(argv[i+1]);
            i++;
        } else if (strcmp(argv[i], "-t") == 0) {
            time_in_s = atoi(argv[i+1]);
            i++;
        } else {
            printf("Error parsing parameters, use -h for help");
            return 1;
        }
    }


    char *mem = reserve_memory(megabytes);
    if (mem == NULL) {
        return 1;
    }
    while (1) {
        for (size_t i = 0; i < (size_t)megabytes * 1000000; i++) {
            mem[i] = 'Z';
        }

        printf("Memory touched %d megabytes\n", megabytes);

        if (time_in_s != -1) {
            double elapsed_time = ((double)(clock() - start_time)) / CLOCKS_PER_SEC;
            if (elapsed_time >= time_in_s) {
                printf("Program finished after %d seconds\n", time_in_s);
                free(mem);
                return 0;
            }
        }
    }
    free(mem);
    return 0;
}