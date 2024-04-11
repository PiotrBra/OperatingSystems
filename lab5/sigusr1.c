#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

// Obsługa sygnału SIGUSR1
void sigusr1_handler(int signum) {
    printf("Received SIGUSR1 signal\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <none|ignore|handler|mask>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Ustawienie reakcji na sygnał SIGUSR1
    if (strcmp(argv[1], "none") == 0) {
        // Nie zmienia reakcji na sygnał
    } else if (strcmp(argv[1], "ignore") == 0) {
        signal(SIGUSR1, SIG_IGN); // Ignorowanie sygnału
    } else if (strcmp(argv[1], "handler") == 0) {
        signal(SIGUSR1, sigusr1_handler); // Instalacja obsługi sygnału
    } else if (strcmp(argv[1], "mask") == 0) {
        sigset_t mask;
        sigemptyset(&mask);
        sigaddset(&mask, SIGUSR1);
        sigprocmask(SIG_BLOCK, &mask, NULL); // Maskowanie sygnału
    } else {
        fprintf(stderr, "Invalid argument: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Wysłanie sygnału SIGUSR1 do samego siebie
    raise(SIGUSR1);

    // Sprawdzenie, czy wiszący/oczekujący sygnał jest widoczny
    sigset_t pending_signals;
    sigpending(&pending_signals);
    if (sigismember(&pending_signals, SIGUSR1)) {
        printf("SIGUSR1 is pending\n");
    } else {
        printf("No pending signals\n");
    }

    // Oczekiwanie na sygnał SIGUSR1
    pause();

    return 0;
}
