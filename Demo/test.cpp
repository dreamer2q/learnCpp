
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handleSignal(int s){
    fprintf(stderr,"test\n");
    if (s == SIGBREAK){
        fprintf(stderr,"receivi signal %d\n",s);
    }
    fprintf(stderr,"this is a signal test %d\n",s);
}


void test(){
    char p;
    for(int i=0;i<100000;i++){
        *(char*)(&p+i) = 1;
    }
    
}

int main() {

    //signal(SIGINT,handleSignal);
    //signal(SIGBREAK,handleSignal);
    //signal(SIGTERM,handleSignal);
    //signal(SIGSEGV,handleSignal);
    //signal(SIGABRT,handleSignal);



    test();

    printf("end");


    return 0;
}