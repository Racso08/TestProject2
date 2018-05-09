#include <iostream>
#include <fstream>
#include <string>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <zconf.h>

using namespace std;
class Data
{
public:
    char data1[255];
    char val1[255];
};

int main()
{
    int create_socket,new_socket,fd;
    socklen_t addrlen;
    struct sockaddr_in address;
    if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
        cout<<"The socket was created\n";
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;//INADDR_ANY;inet_addr("localhost");
    address.sin_port = htons(4455);
    cout<<"\nworking";
    if (bind(create_socket,(struct sockaddr *)&address,sizeof(address)) == 0)
        cout<<"Binding Socket\n";
    listen(create_socket,3);
    addrlen = sizeof(struct sockaddr_in);
    cout<<"*************************\n";
    new_socket = accept(create_socket,(struct sockaddr *)&address,&addrlen);
    cout<<"*************************\n";
    Data dobj;
    if (new_socket > 0)
    {
        cout<<"The Client "<<inet_ntoa(address.sin_addr)<<" is Connected...\n";//inet_ntoa(address.sin_addr));
        int ch = recv(new_socket,&dobj,1023,0);
        perror("recv");
        cout<<"Status = "<< ch<<"\n";
        ifstream in("binary.txt", ios::binary);
        in.read((char*)&dobj, sizeof(dobj));
        if(ch !=-1)
        {
            cout<<"Client: received "<<dobj.data1<<"\n";
            cout<<"Client: received "<<dobj.val1<<"\n";
            cout<<"Request Completed\n";

        }
        else
            perror("recv");
    }
    else
    {
        cout<<"Client not connected ...\n";
    }
    close(new_socket);
    return close(create_socket);
}