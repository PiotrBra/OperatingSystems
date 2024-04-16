#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

#define FIFO_NAME "./calculator_fifo"
#define BUFFER_SIZE 256

double f(double x) {
    return 4 / (x * x + 1);
}

double calculate_integral(double interval_start, double interval_stop, double interval_width) {
    double sum = 0.0;
    double x;
    for (x = interval_start; x < interval_stop; x += interval_width) {
        sum += f(x) * interval_width;
    }
    return sum;
}

int main() {
    // Otwieramy potok nazwany do odczytu
    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("Błąd otwierania potoku nazwanego do odczytu");
        exit(EXIT_FAILURE);
    }

    // Odczytujemy przedział z potoku nazwanego
    char input[BUFFER_SIZE];
    if (read(fd, input, BUFFER_SIZE) == -1) {
        perror("Błąd odczytu z potoku nazwanego");
        exit(EXIT_FAILURE);
    }

    close(fd);

    // Parsujemy przedział
    double interval_start, interval_stop;
    sscanf(input, "%lf %lf", &interval_start, &interval_stop);

    // Obliczamy wartość całki w przedziale
    double integral_result = calculate_integral(interval_start, interval_stop, 0.0001);

    // Otwieramy potok nazwany do zapisu
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("Błąd otwierania potoku nazwanego do zapisu");
        exit(EXIT_FAILURE);
    }

    // Przesyłamy wynik przez potok nazwany
    char result[BUFFER_SIZE];
    snprintf(result, BUFFER_SIZE, "%lf\n", integral_result);
    if (write(fd, result, strlen(result)) == -1) {
        perror("Błąd zapisu do potoku nazwanego");
        exit(EXIT_FAILURE);
    }

    close(fd);

    return 0;
}

