/*
Author : Praveen M
Implementing a UDP communication 
*/

#include <stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
    int c_sock;

    char msg[256];
    char otp[4];

    printf("Enter the phone to get OTP : ");
    fgets(msg, 100, stdin);

    c_sock=socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in client,other;

    client.sin_family=AF_INET;

    client.sin_port=htons(9001);

    client.sin_addr.s_addr=INADDR_ANY;

    socklen_t ad;

    ad=sizeof(other);

    sendto(c_sock,msg,sizeof(msg),0,(struct sockaddr*)&client,sizeof(client));
    printf("client send : %s\n",msg);

    recvfrom(c_sock,otp,sizeof(otp),0,(struct sockaddr*)&other,&ad);
    printf("Received OTP is : ");
    for(int i = 0; i < 4; i++)
    {
        printf("%c", otp[i]);
    }
    
    close(c_sock);
    return 0;
}
