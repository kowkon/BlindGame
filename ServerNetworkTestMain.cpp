#include <iostream>
#include "NetworkModule.h"
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#define PAYLOAD_MAX 200
using namespace std;
main(){

ServerNetworkModule network;
int size;
Command *cmd_send,*cmd_recv;
cmd_send =(Command *) malloc(PAYLOAD_MAX);
cmd_recv =(Command *) malloc(PAYLOAD_MAX);
memset(cmd_send, 0 ,PAYLOAD_MAX);
memset(cmd_recv, 0 ,PAYLOAD_MAX);
cmd_send->commandType = CREATE ;

char ptr[8]="mustafa";
//perror("...");

memcpy(cmd_send->context, ptr ,8);

cmd_send->length=sizeof(Command)+8;
network.init(5000);
network.listenClient();
//
size=network.sendData(cmd_send,cmd_send->length);
cout << size << endl ;
size=network.recvData(cmd_recv,PAYLOAD_MAX);
cout << cmd_recv->context << endl ;
close(network.getFd());
}