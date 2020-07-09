/*************************************************************************
	> File Name: thread_pool.c
	> Author: 
	> Mail: 
	> Created Time: Thu 09 Jul 2020 02:49:18 PM CST
 ************************************************************************/

#include"head.h"

void do_work(struct User *user){
    DBG("In do_work %s\n",user->name);
}

void task_quene_init(struct task_quene *taskQuene,int sum, int epollfd){
    taskQuene->sum=sum;
    taskQuene->epollfd=epollfd;
    taskQuene->team=calloc(sum,sizeof(void *));
    taskQuene->head=taskQuene->tail=0;
    pthread_mutex_init(&taskQuene->mutex,NULL);
    pthread_cond_init(&taskQuene->cond,NULL);

}

void task_quene_push(struct task_quene*taskQuene,struct User *user){
    pthread_mutex_lock(&task_quene->mutex);
    taskQuene->team[taskQuene->tail]=user;
    DBG(L_GREEN"Thread Pool"NONE":Task push %d\n",user->name);
    if(++taskQuene->tail==taskQuene->sum){
        DBG(L_GREEN"Thread Pool"NONE":Task Quene END\n");
        taskQuene->tail =0;
    }

    pthread_cond_signal(&taskQuene->cond);
    pthread_mutex_unlock(&taskQuene->mutex);


}

struct User *task_quene_pop(struct task_quene *taskQuene){
    pthread_mutex_lock(&taskQuene->mutex);
    while(taskQuene->tail==taskQuene->head){
        DBG(L_GREEN"Thread Pool"NONE":Task Quene Empty, Waiting For Task\n");
        pthread_mutex_wait(&taskQuene->cond,&taskQuene->mutex);
    }
    struct User *user =taskQuene->team[taskQuene->head];
   DBG(L_GREEN"Thread Pool"NONE":Task Pop%s\n",user->name);
    if(++taskQuene->head==taskQuene->sum){
        DBG(L_GREEN"Thread Pool"NONE":Task Quene End\nn");
        taskQuene->head=0;
    }
    pthread_mutex_unlock(&taskQuene->mutex);
    return user;

}


void *thread_run(void *arg){
    pthread_detach(pthread_self());
    struct task_quene *taskQuene=(struct task_quene *)arg;
    while(1){
        struct User * user=task_quene_pop(taskQuene);
        do_work(user);
        
    }
}
