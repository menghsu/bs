#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	char *str = "message from user-space!";
        printf("%ld\n", syscall(349,20,str));
        return 0;
}

