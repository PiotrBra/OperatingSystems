#include <stdio.h>

#if defined(ONE)
//one by one
void reverse(FILE* input, FILE* output){
    fseek(input, -1, SEEK_END);
    long long bytes_to_read = ftell(input) + 1;

    while(bytes_to_read > 0){

        fprintf(output, "%c", getc(input));
        bytes_to_read--;
        fseek(input, -2, SEEK_CUR);
    } 
}

#else
//1024 byte blocks
#define BUFFER_SIZE 1024
void reverse(FILE* input, FILE* output){
    fseek(input, 0, SEEK_END);
    long long bytes_left = ftell(input);
    char buffer[BUFFER_SIZE];
    
    while(bytes_left > 0){

        long long bytes_to_read = bytes_left > BUFFER_SIZE ? BUFFER_SIZE : bytes_left;
        fseek(input, -bytes_to_read, SEEK_CUR);
        size_t bytes_read = fread(buffer, sizeof(char), bytes_to_read, input);

        char c;
        for(int i = 0; i < bytes_read/2; i++){
            c = buffer[i];
            buffer[i] = buffer[bytes_read - 1 - i];
            buffer[bytes_read - 1 - i] = c;
        }

        fwrite(buffer, sizeof(char), bytes_read, output);
        fseek(input, -BUFFER_SIZE, SEEK_CUR);
        
        bytes_left -= bytes_read;
    }
}

#endif


int main(int argc, char** argv) {
    if (argc != 3) { 
        printf("Usage: reverse <input_file> <output_file>\n");
        return -1;
    }

    FILE* input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Error: Cannot open file '%s'\n", argv[1]);
        return -1;
    }

    FILE* output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("Error: Cannot open file '%s'\n", argv[2]);
        return -1;
    }

    reverse(input, output);

    fclose(input);
    fclose(output);
}