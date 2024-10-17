#include <stdio.h>
#include <string.h>

char *reserve_memory(int megabytes) {
    char *res = malloc(megabytes * sizeof(char) * 1000000);
    if (res == NULL) {
        perror("error using malloc");
        return NULL;
    }
}

int main(int argc, char **argv) {
    if (argc < 2 || argc > 3) {
        printf("Wrong number of parameters use -h for help.");
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0) {
        char *help_str = "Usage:\n-h -> help\n-n [number of megabytes]\n-t [runtime]\n";
        printf("%s", help_str);
    }
    
    int megabytes = 0;

    char *mem = reserve_memory(megabytes);
    if (mem == NULL) {
        return 1;
    }

    return 0;
}