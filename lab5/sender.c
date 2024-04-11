#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


void handler_SIGUSR1(int signo) {
    printf("Potwierdzenie otrzymane\n");
}


int main(int argc, char** argv) {
    if(argc < 3) {
        printf("Użycie: %s <pid> <argument>\n", argv[0]);
        return -1;
    }

    printf("process PID: %d\n", getpid());

    // Zarejestruj funkcję obsługi zwrotnej
    signal(SIGUSR1, handler_SIGUSR1);

    // konwersja argumentow
    long pid = strtol(argv[1], NULL, 10);
    long argument = strtol(argv[2], NULL, 10);

    // przechowanie argument trybu w odpowiedniej unii
    union sigval value = {argument};

    // wysylanie sygnalu do catcher
    sigqueue(pid, SIGUSR1, value);
    printf("Sygnał wysłany z argumentem: %ld\n", argument);

    /* Ustaw maski sygnałów, aby tylko SIGUSR1 i SIGINT mogły przerwać zawieszenie */
    // ustawienie maski sygnalu, aby tylko sigusr1 i siging mogly przerywac
    sigset_t maska;
    sigfillset(&maska);

    sigdelset(&maska, SIGUSR1);
    sigdelset(&maska, SIGINT);

    //potwierdzenie
    sigsuspend(&maska);
    return 0;
}
