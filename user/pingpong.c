#include "kernel/types.h"
#include "user.h"

int main(int argc, char* argv[])
{
     if(argc != 1){
        printf("please input pingpong!\n"); //检查参数数量是否正确
        exit(-1);
    }

    int pp[2], cp[2]; /*pp为父进程管道，cp为子进程管道*/
    char buf[5];

    pipe(pp); /*正常创建后，p[1]为管道写入端，p[0]为管道读出端*/
    pipe(cp);

    if(0 == fork())
    {
       // close(cp[0]);
      //  close(pp[1]);
        read(pp[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
        write(cp[1],"pong",4);
        close(cp[1]);
        close(pp[0]);
    }
    else
    {
       // close(cp[1]);
      //  close(pp[0]);
        write(pp[1],"ping",4);    
        read(cp[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
        close(cp[0]);
        close(pp[1]);

    }

    exit(0); //确保进程退出
}