/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Wed 08 Jul 2020 03:54:33 PM CST
 ************************************************************************/

#include"head.h"
#include"common.h"
#include"color.h"
int serer_port=0;
char server_ip[20]={0};
int team=-1;
char name[20]={0};
char log_msg[512]={0};

char *conf ="./football.conf";
int main(int argc,char**argv){
    int opt;
    while((opt=getopt(argc,argv,"h:p:t:m:n"))!=-1){
        switch(opt){
            case 't':
                team=atoi(optarg);
                break;
            case 'h':
                strcpy(server_ip,optarg);
                break;
            case 'p':
                serer_port =atoi(optarg);
                break;
            case 'm':
                strcpy(log_msg,optarg);
                break;
            case 'n':
                strcpy(name,optarg);
            default:
                fprintf(stderr,"Usage : %s [-hptmn]\n",argv[0]);
            exit(1);
        
        
        
        
        } 

    }
    if(!serer_port) serer_port=atoi(get_conf_value(conf,"SERVERPORT"));
    if(!team) team=atoi(get_conf_value(conf,"TEAM"));
    if(!strlen(server_ip)) strcpy(server_ip,get_conf_value(conf,"SERVERIP"));
    if(!strlen(name)) strcpy(name,get_conf_value(conf,"NAME"));
    if(!strlen(log_msg)) strcpy(log_msg,get_conf_value(conf,"LOGMSG"));
    DBG("<"GREEN"Conf show"NONE"> : server_ip=%s, port=%d, team= %s, name=%s\n%s",\
        server_ip,serer_port,team?"bule":"red",name,log_msg);




    return 0;
}
