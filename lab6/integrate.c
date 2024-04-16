#include <printf.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define min(a, b) (a < b ? a : b)

typedef unsigned long long ull;

// parametry calkki
double range_start = 0.0;
double range_stop = 1.0;

//funkcja calki
double f(double x){
    return 4/(x*x + 1);
}


/**
 * @brief function calculating integral in given range
 *
 * @param interval_start start of the interval
 * @param interval_stop end of the interval
 * @param fun pointer to the function that will be integrated
 * @param interval_width width of the single rectangle
 * @param number_of_intervals number of rectangles that will be used to calculate integral
 */
// kalulator calki
double calculate_integral(double interval_start, double interval_stop, double (*fun)(double), double interval_width, ull number_of_intervals){
    if(interval_stop - interval_start < interval_width)
        return fun((interval_start + interval_stop)/ 2.0)*(interval_stop - interval_start);

    double sum = 0.0;
    for(ull i = 0; i < number_of_intervals; i++){
        sum += fun((interval_start + interval_width/2.0));
        interval_start += interval_width;
    }

    return sum * interval_width;
}


int main(int argc, char** argv) {
    // if we didn't get 3 arguments we cannot proceed
    if(argc < 3) {
        printf("Usage: %s <interval_width> <number_of_processes>\n", argv[0]);
        return 1;
    }

    //konwersja zmiennych
    double interval_width = atof(argv[1]);
    long num_of_processes = atol(argv[2]);

    //sprawdzam czy jest wystarczająco przedziałóœ dla procesów
    if(ceil((range_stop - range_start)/interval_width) < num_of_processes) {
        printf("To much processes needed for given interval range");
        return -1;
    }

    /**
     * calculate number of intervals per process
    */
    //obliczam liczbe przedzialow na proces
    ull total_intervals_count = (ull)ceil((double)(range_stop - range_start)/interval_width);
    ull intervals_per_process = total_intervals_count/num_of_processes;


    double interval_start = range_start;
    double interval_stop = range_start;

    // tworze file descriptions dla potokow
    int pipes_fd[num_of_processes][2];

    //przekazuje zadania do procesow
    for(int i = 0; i < num_of_processes; i++){
        interval_stop = min(range_stop, interval_start + intervals_per_process*interval_width);

        // create pipe for integral result
        if(pipe(pipes_fd[i]) < 0) {
            printf("Failed to create pipe\n");
            return -1;
        }

        pid_t pid = fork();

        if(pid == 0){
            // zamykam wyjscie potoku w child process
            close(pipes_fd[i][0]);

            // licze calke
            double integral_result = calculate_integral(interval_start, interval_stop, f, interval_width, intervals_per_process);

            //wpisuje wynik do potokku
            if(write(pipes_fd[i][1], &integral_result, sizeof(integral_result)) < 0) {
                printf("Failed to write to the pipe\n");
                return -1;
            }

            exit(0);
        }

        // zamykam wejscie do potoku w parent process
        close(pipes_fd[i][1]);

        interval_start = interval_stop;
    }

    double sum = 0.0;

    // czytam wyniki w kazdym z potokow i sumuje
    for(int i = 0; i < num_of_processes; i++){
        double integral_result;
        if(read(pipes_fd[i][0], &integral_result, sizeof(integral_result)) < 0) {
            printf("Failed to read from the pipe\n");
            return -1;
        }
        sum += integral_result;
    }

    printf("total result: %lf\n", sum);

    return 0;
}