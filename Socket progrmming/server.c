/*
Author : Praveen M
Implementing a UDP communication
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
    int s_sock;
    char msg[256];

    s_sock=socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in server, other;

    server.sin_family=AF_INET;

    server.sin_port=htons(9001);

    server.sin_addr.s_addr=INADDR_ANY;

    socklen_t add;

    bind(s_sock,(struct sockaddr*)&server,sizeof(server));
    add=sizeof(other);
    
    recvfrom(s_sock,msg,sizeof(msg),0,(struct sockaddr*)&other,&add);
    printf("server msg : %s\n",msg);

    int num = rand() % 10000 + 1;
    char otp[4];
    sprintf(otp, "%d", num);

    sendto(s_sock,otp,sizeof(otp),0,(struct sockaddr*)&other,sizeof(other));
    printf("OTP sent is : %s\n", otp);

    return 0;
}
