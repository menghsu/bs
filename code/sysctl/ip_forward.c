#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/sysctl.h>

int _sysctl(struct __sysctl_args *args );

int
main(int argc, char ** argv)
{
   struct __sysctl_args args;
   int old;
   int new = 0;
   int oldlth;
   int name[] = { CTL_NET, NET_IPV4, NET_IPV4_FORWARD };

   memset(&args, 0, sizeof(struct __sysctl_args));
   oldlth = sizeof(int);
   args.name = name;
   args.nlen = sizeof(name)/sizeof(name[0]);
   args.oldval = &old;
   args.oldlenp = &oldlth;
   args.newval = &new;
   args.newlen = 4;

   printf("Input the ip_forword value(0 or 1):");
   scanf("%d",&new);

   if (syscall(SYS__sysctl, &args) == -1) {
       perror("_sysctl");
       exit(EXIT_FAILURE);
   }
   printf("The ip_forword old value is : %d\n", old);
   printf("The ip_forword new value is : %d\n", new);
   exit(EXIT_SUCCESS);
}
