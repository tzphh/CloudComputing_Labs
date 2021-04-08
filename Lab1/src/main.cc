#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include "sudoku.h"

#define Numphread 10//线程数
char Answer[Task_num][128];//存储答案
char puzzle[Task_num][128];//存储数独
int total=0;//数独总数
int succeed_solve=0;//已经解决的
int Sid=0;//当前的数独序号
bool shutdown=false;
int Tdata[Task_num];//线程运行函数的参数
pthread_t th[Task_num];
pthread_mutex_t mutex;//定义一个锁
pthread_mutex_t mmutex;
int recvAJob()           //获取一个任务
{
    int currentJobID = 0;
    pthread_mutex_lock(&mutex);
    if (Sid>=total){
        pthread_mutex_unlock(&mutex);
        return -1;//所有任务已解决
    }
    currentJobID=Sid++;
    if (currentJobID==total-1){       //最后一个任务
        shutdown=true;
    }
    pthread_mutex_unlock(&mutex);
    return currentJobID;
}
void *pthread_solve(void *args)
{
    bool (*solve)(int,int[],int,int[])=solve_sudoku_basic;//使用basic算法
    //bool (*solve)(int,int[],int,int[])=solve_sudoku_dancing_links
    int board[N];
    int spaces[N];//空格位置
    while (!shutdown)
    {
        int id=recvAJob();            //获取任务
        if (id==-1)
            break;
        int t=input(puzzle[id],board,spaces);
        if (solve(0,board,t,spaces)){
            if (!solved(board))
                assert(0);
            for (int i=0;i<N;i++)//保存结果
                Answer[id][i] = char('0' + board[i]);
            pthread_mutex_lock(&mutex);
            succeed_solve++;
            pthread_mutex_unlock(&mutex);//处理下一行
        }
        else{
            printf("第%d,行数独无解\n", id);
        }
    }
}
void Print()
{
    for(int i=0;i<total; i++)
        printf("No %d : %s\n",i+1,Answer[i]);
    printf("成功解决的数独个数为%d\n",succeed_solve);
}
int64_t now()
{
    struct timeval tv;
    gettimeofday(&tv, NULL); // 获取当前精确时间
    return tv.tv_sec * 1000000 + tv.tv_usec;
}
int main(int argc, char *argv[])
{
    init_neighbors();//初始化
    int64_t start = now();//开始计时
    FILE* fp = fopen(argv[1],"r");
    for (int i = 0; i <Numphread; i++){
        if (pthread_create(&th[i], NULL, pthread_solve,(void*)&Tdata[i])!=0){//创建线程
            perror("pthread_create failed");
            exit(1);
        }
    }
    while (fgets(puzzle[total], sizeof puzzle, fp) != NULL){//输入并统计总的个数
        if (strlen(puzzle[total]) >= N){
            pthread_mutex_lock(&mutex);
            total++;
            pthread_mutex_unlock(&mutex);
        }
    }
    for (int i = 0; i < Numphread; i++)
        pthread_join(th[i], NULL);
    printf("数独解法如下所示:\n" );//打印结果
    Print();
    int64_t end = now();
    double sec = (end - start) / 1000000.0;
    printf("%f sec %f ms each %d\n", sec, 1000 * sec / total, total); // 输出运行时间
    return 0;
}
