#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIGNATURES 100
#define MAX_SIGNATURE_LENGTH 256

int load_signatures(const char *filename, char signatures[][MAX_SIGNATURE_LENGTH]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Could not open signature file: %s\n", filename);
        return 0;
    }

    int count = 0;
    while (fgets(signatures[count], MAX_SIGNATURE_LENGTH, file) && count < MAX_SIGNATURES) {
        signatures[count][strcspn(signatures[count], "\n")] = '\0';
        count++;
    }

    fclose(file);
    return count; 
}

void scan_file(const char *filename, char signatures[][MAX_SIGNATURE_LENGTH], int signature_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file to scan: %s\n", filename);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        for (int i = 0; i < signature_count; i++) {
            if (strstr(line, signatures[i]) != NULL) {
                printf("Malware signature found in %s: %s\n", filename, signatures[i]);
                fclose(file);
                return; 
            }
        }
    }

    printf("No malware signatures found in %s.\n", filename);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file_to_scan>\n", argv[0]);
        return 1;
    }

    char signatures[MAX_SIGNATURES][MAX_SIGNATURE_LENGTH];
    int signature_count = load_signatures("res/signatures.txt", signatures); // Pass the signatures array

    if (signature_count == 0) {
        printf("No signatures loaded. Exiting...\n");
        return 1;
    }

    scan_file(argv[1], signatures, signature_count);

    return 0;
}
