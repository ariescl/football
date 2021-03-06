/*************************************************************************
	> File Name: common.h
	> Author: 
	> Mail: 
	> Created Time: Wed 08 Jul 2020 09:45:24 AM CST
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H

char conf_ans[50]={0};

int socket_create(int port);
void make_non_block(int fd);
void make_block(int fd);
char *get_conf_value(const char *path,const char *key);
#ifdef _D
#define DBG(fmt,args...) printf(fmt,##args);
#else
#define DBG(fmt,args...)
#endif
#endif
