#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


/** deklarujemy status jako zmienną volatile, aby uniknąć optymalizacji przez kompilator.
 * Bez volatile kod będzie działał z flagą -O0, ale nie z -O2, ponieważ kompilator nie widzi ścieżki prowadzącej
 * do zmiany tej zmiennej (ponieważ funkcja obsługi jest wywoływana przez system, a nie bezpośrednio przez nasz program),
 * więc optymalizuje każde użycie tej zmiennej tak, jakby była stałą wartością.
 *
 * Musimy jasno powiedzieć kompilatorowi, że nie chcemy optymalizować zmiennej
*/

//volatile mowi kompilatorowi zeby nie opytmalizowac zmiennej
volatile int status = -1;
volatile int liczba_zmian_statusu = 0;

/**
 * @brief Funkcja obsługi argumentu, aktualizuje bieżący status na podstawie argumentu dostarczonego z sygnału
 *
 * @param argument argument dostarczony z sygnału
*/
//obsluga argumentow

void handler(int argument){
    liczba_zmian_statusu++;
    status = argument;

}


//funkcja oblusgi akcji sygnalu, wywolywana po otrzymaniu sygnalu przez proces
void action_SIGUSR1(int signo, siginfo_t *info, void *extra){
    /* Pobierz informacje ze struktury info o sygnale */
    int int_val = info->si_int;
    printf("Otrzymano status: %d od pid: %d\n", int_val, info->si_pid);

    /* Zaktualizuj bieżący status */
    handler(int_val);

    /* Wyślij sygnał zwrotny do nadawcy */
    kill(info->si_pid, SIGUSR1);
}

int main() {
    /* Wyświetl PID bieżącego procesu */
    printf("PID: %d\n", getpid());


    /* Zarejestruj nową akcję sygnału */
    struct sigaction action;
    action.sa_sigaction = action_SIGUSR1;    // zarejestruj funkcję zwrotną
    action.sa_flags = SA_SIGINFO;           // ustaw flagę na SA_SIGINFO, aby obsługa była wywoływana z wszystkimi 3 argumentami
    sigemptyset(&action.sa_mask);           // wyczyść wszystkie maski sygnałów podczas obsługi

    sigaction(SIGUSR1, &action, NULL);      //rejestracja akcji sygnału

    while(1) {
        switch(status){
            case 1:
                for(int i = 1; i <= 100; i++){
                    printf("%i, ", i);
                }
                printf("\n");
                status = -1;
                break;
            case 2:
                printf("Dotychczas status zmienił się %d razy\n", liczba_zmian_statusu);
                status = -1;
                break;
            case 3:
                printf("Otrzymano sygnał zakończenia! Zamykanie...\n");
                exit(0);
                break;
            default:
                break;
        }
    }
}
