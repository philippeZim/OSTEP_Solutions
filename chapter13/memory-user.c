#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



char *reserve_memory(int megabytes) {
    char *res = malloc(megabytes * sizeof(char) * 1000000);
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

    clock_t start_time = clock();
    int megabytes;
    int time_in_ms = -1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            char *help_str = "Usage:\n-h -> help\n-n [number of megabytes]\n-t [runtime in ms]\n";
            printf("%s", help_str);
            return 1;
        } else if (strcmp(argv[i], "-n") == 0) {
            megabytes = atoi(argv[i+1]);
            i++;
        } else if (strcmp(argv[i], "-t") == 0) {
            time_in_ms = atoi(argv[i+1]);
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
    if (time_in_ms == -1) {
        while(1) {
            for (int i = 0; i < megabytes * 1000000; i++) {
                printf("%c", mem[i]);
            }
        }
    } else {
        while(1) {
            printf("1");
            for (int i = 0; i < megabytes * 1000000; i++) {
                printf("%c", mem[i]);

                if ((((double) (clock() - start_time)) / CLOCKS_PER_SEC) * 1000 >= time_in_ms) {
                    return 0;
                } 
            }
        }
    }
    

    return 0;
}