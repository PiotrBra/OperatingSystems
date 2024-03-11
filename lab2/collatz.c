#include<stdio.h>

int collatz_conjecture(int input){
    if(input%2 == 1)
        return 3*input +1;
    else
        return input/2;
}

int test_collatz_convergence(int input, int max_iter){
    for(int i=0;i<max_iter;i++){
        input = collatz_conjecture(input);
        if(input == 1) return 1;
    }
    return -1;
}
