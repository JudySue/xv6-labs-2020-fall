// #include "kernel/types.h"
// #include "user.h"

// void prime(int pp[], int cp[])
// {
//     if(0 == fork())
//     {
//         int num[1];
//         //如果读取不到数据了，就退出
//         if(read(pp[0], num, sizeof(num)) != sizeof(num))
//         {
//             close(pp[0]);
//             close(cp[0]);
//             close(cp[1]);
//             exit(0);
//         }

//         int p = num[0];
//         printf("prime %d\n", num[0]); //打印管道中质数，每次进入子进程管道的第一个数字就是质数

//         while(read(pp[0], num, sizeof(num)) == sizeof(num))
//         {
//             if(num[0] % p != 0)
//             {
//                 write(cp[1], num, sizeof(num));
//             }
//         }
//         close(pp[0]);
//         close(cp[1]);

//         pipe(pp);
//         prime(cp, pp);

//         exit(0);
//     }
//     else
//     {
//         close(pp[0]);
//         close(cp[1]);
//         close(cp[0]);
//         wait(0);
//         exit(0);
//     }

// }

// int main(int argc, char* argv[])
// {
//     int pp[2], cp[2]; /*pp为父进程，cp为子进程*/
//     int i[1]; /*存放一个数字，用于写入管道*/

//     /*初始化两个管道，p[1]为写入，p[0]为读出*/
//     pipe(pp);
//     pipe(cp);

//  //   close(pp[0]);
//     for(i[0] =2; i[0] <= 35; i[0]++)
//     {
//         write(pp[1], i, sizeof(i));
//     }
//     close(pp[1]);
//     prime(pp, cp);

//     exit(0);
//     return 0;
// }

#include "kernel/types.h"
#include "user.h"

void selectnum(int prd)
{

  int num;
  int n;
   int p[2];
    // int addp=0;
    if (fork() == 0)
    {
           
    if(read(prd, &num, 4)==0)
    {
        exit(0);
    }
    printf("prime %d\n", num);
   
    pipe(p);
        close(p[1]);
        selectnum(p[0]);
        exit(0);
    }
    else
    {   
        while (read(prd, &n, 4))
        {
            if (n % num != 0)
            {
                write(p[1], &n, 4);
            }
            close(p[1]);
            close(p[0]);
            wait(0);
            exit(0);
        }
    }
}
int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    if (fork() == 0)
    {

        close(p[1]);
        selectnum(p[0]);

        exit(0);
    }
    else
    {
        for (int i = 2; i <= 35; i++)
        {
            write(p[1], &i, 4);
        }
        wait(0);
    }

    exit(0);
}
