#include <stdio.h>
#include "prog1_2.h"

int main(int ac, char* av[]) {

    unsigned int crc32;
    int err;
    FILE *file = fopen(av[1], "rb");
    char* k = "";

    if(ac < 2) {
        printf("needs an argument\n");
        fclose(file);
        return 0;
    }
 
    if (ac > 2) {
        for(int i = 2; i < ac; i++) {
            if(av[i] != NULL) 
                k = av[i];
            err = crc32_Compute(file, &crc32, k);
            printf("%08x\n", crc32);
        }
    }
    else {
        err = crc32_Compute(file, &crc32, k);
        printf("%08x\n", crc32);
    }

    fclose(file);
    return 0;
    
}
