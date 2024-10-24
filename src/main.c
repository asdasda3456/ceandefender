#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIGNATURES 1024
#define MAX_SIGNATURE_LENGTH 8192

int load_signatures(const char *filename, char signatures[][MAX_SIGNATURE_LENGTH]) {
    FILE *file = fopen(filename, "r");
    if(!file) {
        perror("COULD NOT OPEN SIGNATURE FILE\n");
        return -1;
    }

    int count = 0;
    while(fgets(signatures[count], MAX_SIGNATURE_LENGTH, file) && count < MAX_SIGNATURES) {
        signatures[count][strcspn(signatures[count], "\n")] = 0;
        count++;
    }

    fclose(file);
    return count;
}

void scan_file(const char *filename, char signatures[][MAX_SIGNATURE_LENGTH], int signature_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("COULD NOT OPEN FILE TO SCAN : %s", filename);
        return -1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        for (int i = 0; i < signature_count; i++) {
            if (strstr(line, signatures[i]) != NULL) {
                printf("malware signature found in %s: %s\n", filename, signatures[i]);
                fclose(file);
                return;
            }
        }
    }

    printf("no malware signature found in %s", filename);
    fclose(file);
}

int main(int argc, char *argv[]) {
    printf("= = = = = = = = = = = = = = = = = =\n");
    printf("      WELCOME TO CEANDEFENDER     \n");
    printf("= = = = = = = = = = = = = = = = = =\n");
    
    return 0;
}   
