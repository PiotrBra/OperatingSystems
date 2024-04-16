#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_NAME "./calculator_fifo"
#define BUFFER_SIZE 256

int main() {
    // Tworzymy potok nazwany
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("Błąd tworzenia potoku nazwanego");
        exit(EXIT_FAILURE);
    }

    printf("Podaj przedział, w jakim chcesz policzyć całkę (np. 0.0 1.0): ");
    fflush(stdout);

    // Odczytujemy przedział od użytkownika
    char input[BUFFER_SIZE];
    fgets(input, BUFFER_SIZE, stdin);

    // Otwieramy potok nazwany do zapisu
    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("Błąd otwierania potoku nazwanego do zapisu");
        exit(EXIT_FAILURE);
    }

    // Przesyłamy przedział przez potok nazwany
    if (write(fd, input, strlen(input)) == -1) {
        perror("Błąd zapisu do potoku nazwanego");
        exit(EXIT_FAILURE);
    }

    close(fd);

    // Otwieramy potok nazwany do odczytu
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("Błąd otwierania potoku nazwanego do odczytu");
        exit(EXIT_FAILURE);
    }

    // Odczytujemy wynik z potoku nazwanego
    char result[BUFFER_SIZE];
    if (read(fd, result, BUFFER_SIZE) == -1) {
        perror("Błąd odczytu z potoku nazwanego");
        exit(EXIT_FAILURE);
    }

    // Wyświetlamy wynik
    printf("Wynik całkowania: %s", result);

    close(fd);

    // Usuwamy potok nazwany
    if (unlink(FIFO_NAME) == -1) {
        perror("Błąd usuwania potoku nazwanego");
        exit(EXIT_FAILURE);
    }

    return 0;
}

