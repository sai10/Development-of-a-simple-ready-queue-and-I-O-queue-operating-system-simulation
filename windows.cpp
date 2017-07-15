
// THIS CODE IS THE SIMULTION OF THE MENTIONED PROJECT IN WINDOWS OS


#include<math.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<queue>
#include <windows.h>
using namespace std;

 typedef struct process
 {
     int pid;
     double cut,irt,wt;
     double rq_t;
 };



void createProcess();
double callExec(process);
double accessIOQ(process);


process p;
int k=0;
int count_p = 0;
int count_z = 0;

LARGE_INTEGER frequency;        // ticks per second
LARGE_INTEGER t1, t2;           // ticks

queue <process> readyqueue;
queue <process> ioqueue;
queue <process> finqueue;
queue <process> tempqueue;

int main()
{
    int num;
    while(1)
    {
        cout<<endl<<"____________________"<<endl;
        createProcess();
        count_p++;
        if(count_z==25)
            break;
    }
    //cout<<endl<<"tot proc:"<<count_p;
    //cout<<finqueue.size();
    //cout<<ioqueue.size();
}


void createProcess()
{
    //process p ;
    p.pid = ++k;
    p.cut=0;
    p.irt=0;
    p.wt=0;
    p.rq_t=0;

    readyqueue.push(p);

    QueryPerformanceFrequency(&frequency);

    // start timer
    QueryPerformanceCounter(&t1);

    readyqueue.front().cut += callExec(readyqueue.front());
   //cout<<endl<<readyqueue.front().cut<<endl;
   //cout<<endl<<readyqueue.size()<<endl;

    srand(time(NULL));
    int r = (p.pid+rand()) % 3;

    //cout<<endl<<"random "<<r<<endl;
    if(r==0)
        count_z++;

    switch(r)
    {
    case 0:

        QueryPerformanceCounter(&t2);

    // compute and print the elapsed time in millisec
        p.rq_t = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
        //cout<<endl<<"size "<<readyqueue.size();
        //cout<<endl<<"front pid"<<readyqueue.front().pid;
        //cout<<endl<<"rq_t:"<<p.rq_t<<endl;
        readyqueue.front().wt += p.rq_t  + readyqueue.front().irt ;
        finqueue.push(readyqueue.front());
        cout<<endl<<"Process ID (PID): "<<readyqueue.front().pid;
        cout<<endl<<"CPU Usage time(CUT) : "<<readyqueue.front().cut;
        cout<<endl<<"IO time(IRT) : "<<readyqueue.front().irt;
        cout<<endl<<"Waiting time(WT) : "<<readyqueue.front().wt<<endl;
        readyqueue.pop();
        //cout<<endl<<"after popping pid "<<readyqueue.front().pid;
        break;
    case 1:
        tempqueue.push(readyqueue.front());
        readyqueue.pop();
        readyqueue.push(tempqueue.front());
        tempqueue.pop();
        //cout<<endl<<"from the back:"<<readyqueue.back().pid<<endl;
        break;
    case 2:
        readyqueue.front().irt+=accessIOQ(readyqueue.front());
        tempqueue.push(readyqueue.front());
        ioqueue.push(readyqueue.front());
        readyqueue.pop();
        readyqueue.push(tempqueue.front());
        tempqueue.pop();
        break;
    }
}

double callExec(process p)
{

    srand(time(NULL));
    int r = rand() % 10000;
    double elapsedTime;
    int i,j;

    // get ticks per second
    QueryPerformanceFrequency(&frequency);

    // start timer
    QueryPerformanceCounter(&t1);

    for(i=0;i<r;i++)
        j=sin(i);

    // stop timer
    QueryPerformanceCounter(&t2);

    // compute and print the elapsed time in millisec
    p.cut = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
    //cout << p.t2 << " ms.\n";
    return p.cut;
}

double accessIOQ(process p)
{
    srand(time(NULL));
    int r = (p.pid+rand()) % 100;
    p.irt=r;
    return p.irt;
}
