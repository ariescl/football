/*************************************************************************
	> File Name: sub_reactor.c
	> Author: 
	> Mail: 
	> Created Time: Thu 09 Jul 2020 03:43:47 PM CST
 ************************************************************************/

#include"head.h"


void *sub_reactor(void * arg){
    struct task_quene *taskQuene=(struct task_quene*)arg;
    pthread_t *tid=(pthread_t *)calloc(NTHREAD,sizeof(pthread_t));
    for(int i=0;i<NTHREAD;i++){
        pthread_create(&tid[i],NULL,thread_run,(void*)taskQuene);

    }
    struct epoll_event ev,events[MAX];
    while(1){
        DBG(L_RED"Sub Reactor"NONE":Epoll Waiting...\n");
        int nfds=epoll_wait(taskQuene->epollfd,events,MAX,-1);
        if(nfds<0){
            perror("epoll_Wait");
            exit(1);

        }
        for(int i=0;i<nfds;i++){
            struct User *user=(struct User*)event[i].data.ptr;
            DBG(L_RED"Sub Reator"NONE": %s Ready\n",user->name);
            if(events[i].events&EPOLLIN){
                task_quene_push(taskQuene,user);

            }
        }
    }
    return NULL;
}
