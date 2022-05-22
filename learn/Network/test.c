
#include <stdio.h>
#include <sys/uio.h>
#include <time.h>
int main(int argc, char *argv[])
{
  struct iovec vec[2];
  char buf1[] = "ABCDEFG";
  char buf2[] = "1234567";
  int str_len;
  time_t t1, t2;
  time(&t1);
  vec[0].iov_base = buf1;
  vec[0].iov_len = 3;
  vec[1].iov_base = buf2;
  vec[1].iov_len = 4;
  for (int cnt = 0; cnt < 1000000; cnt++)
  {
    str_len = writev(1, vec, 2);
    puts("");
    printf("Write bytes: %d \n", str_len);
  }
  time(&t2);
  printf("time= %ld", t2 - t1);
  return 0;
}

/*
#include <stdio.h>
#include <sys/uio.h>
#include <time.h>
int main(int argc, char *argv[])
{
        struct iovec vec[2];
        char buf1[]="ABCDEFG";
        char buf2[]="1234567";
        int str_len1, str_len2;
        time_t t1, t2;
        time(&t1);

        for (int cnt = 0; cnt < 1000000; cnt++){
                str_len1 = write(1, buf1, 3);
                str_len2 = write(1, buf2, 4);
                puts("");
                printf("Write bytes: %d \n", str_len1+str_len2);
        }
        time(&t2);
        printf("time= %ld", t2 - t1);
        return 0;
}
*/
