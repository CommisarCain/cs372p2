
/*
Description: This program responds to requests from a client
Input:
*/
#include <dirent.h>
#include <stdio.h>
#include "str.c"
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>


#define BACKLOG 10

int sendall(int client, char* msg, int* msg_len){
	int total = 0;
	int remain = *msg_len;
	int n;

	while(total < *msg_len){
		n = send(client, msg+total, remain, 0);
		if(n == -1){
			break;
		}
		total += n;
		remain -= n;
	}
	*msg_len = total;
	if(n== -1){
		return -1;
	}
	else{
		return 0;
	}


}

//Returns socket descriptor based on input
int send_client_msg(struct STR* c_addr, struct STR* c_port, struct STR* to_send){
  ///////ALL USED FOR CONNECTING TO A TARGET HOST.........
  int client;
  struct addrinfo hint, *re, *q;
	memset(&hint, 0, sizeof hint);
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
  /*CRITICAL INFO
  setting up connection procedure:
  1. fill out addrinfo struct with target parameters, struct is not full
  2. pass to get addr with ip, port, and addrinfo struct pointer
  3. passed pointer is first node in linked list of results, these results
  are addrinfo structs but they have all members filled out, including
  the sockaddr struct which is used to get sockets!!!!
  4.The socket is then listened or use connect-this is where target addr & port
  matter. everything else is self up to this point.
  */
	//make sure address info is reasonable
  //argv[1] = ip, 2 = port , all of self not target connection
	if(getaddrinfo(c_addr->str, c_port->str, &hint, &re) != 0)
		printf("ERROR GETTING ADDRESS\n");

  //iterate over addr linked list to try and find a valid entry
  //I do not understand why there would be invlid entries :(
  for(q = re; q!= NULL; q = q->ai_next){
    //is the data valid to get a socket?
		if((client = socket(q->ai_family, q->ai_socktype, q->ai_protocol)) == -1){
			perror("client : socket failed to aquire\n");
			continue;
		}
    //ok we have a socket, can it be used to connect?
		if(connect(client, q->ai_addr, q->ai_addrlen) == -1){
		close(client);
		perror("client : connect, this socket did not work \n");
		//error("Error Connecting");
		continue;
		}
		break;
	}
	if(q == NULL){
		fprintf(stderr, "Client: failed to connect\n");
		return -1;
	}

  //if we got this far then we have a valid connection on "client"
  int* them_size;
  int tempi = 0;
  tempi = (int) str_length(to_send);
  them_size = &tempi;
  int result = sendall(client, to_send->str, them_size);

  return 0;

}


int main(int argc, char* argv[]){

  struct STR *client_addr, *client_data_port, *my_addr, *my_port, *msg;
  client_addr = new_str(15);
  client_data_port = new_str(15);
  my_addr = new_str(15);
  msg = new_str(100);
  char temp [100];
  char ip[15] = "127.0.0.1";
  int serv_sock;

  memset(temp, '\0', 100);

  int client;
  struct addrinfo hints, *res, *p, *servinfo;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
  struct sockaddr_storage their_addr; // connector's address information
  socklen_t sin_size;
  int yes=1;
  int rv;
  char s[INET6_ADDRSTRLEN];


  if(argc != 2){
    printf("Usage: ./ftserver server_port \n");
    exit(0);
  }

//////////////////////GET DOWN TO BUSINESS////////////////
copy_to(my_addr, ip);
my_port = new_str_with(15, argv[1]);


if ((rv = getaddrinfo("127.0.0.1", argv[1], &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
}

// loop through all the results and bind to the first we can
for(p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype,
            p->ai_protocol)) == -1) {
        perror("server: socket");
        continue;
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
            sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
        close(sockfd);
        perror("server: bind");
        continue;
    }

    break;
}

freeaddrinfo(servinfo); // all done with this structure

if (p == NULL)  {
    fprintf(stderr, "server: failed to bind\n");
    exit(1);
}

if (listen(sockfd, BACKLOG) == -1) {
    perror("listen");
    exit(1);
}

printf("server: waiting for connections...\n");

   while(1) {  // main accept() loop
       sin_size = sizeof their_addr;
       new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
       if (new_fd == -1) {
           perror("accept");
           continue;
       }

       printf("server: got connection from client \n");

       int numb = 0;

       numb = 0;
       numb = recv(new_fd, temp, 100, 0);
       temp[numb] = '\0';
       send(new_fd, temp, 6, 0);
       printf("the reported port: %s\n",temp );
       copy_to(client_data_port, temp);


       memset(temp, '\0', 100);
       numb = 0;
       numb = recv(new_fd, temp, 100, 0);
       temp[numb] = '\0';

       copy_to(msg, temp);
       if(msg->str[0] == '1'){

         struct STR* fl = new_str(1024);

         DIR *d;
         struct dirent *dir;
         d = opendir(".");
         if (d) {
           while ((dir = readdir(d)) != NULL) {
             sprintf(fl->str,"%s, %s\n", dir->d_name, fl->str);
           }
         closedir(d);
         }



         char f[1026];
         char f2[] = "1,";
         memset(f, '\0', 100);
         sprintf(f,"%s%s",f2,fl->str);

         struct STR* fl2 = new_str_with(150, f);
         send_client_msg(my_addr, client_data_port, fl2);
         free_str(fl);
         free_str(fl2);

       }
       else if(msg->str[0] == '2'){

				struct STR* tlf = get_delim_at_with(msg->str, 1, ',');
        struct STR* tl = new_str(4000);

				char tt[4002];
        char t2[] = "1,";
				char t3[] = "2,";
				char line[400];
        memset(tt, '\0', 4002);

				int exists = 0;

        DIR *d;
        struct dirent *dir;
        d = opendir(".");
        if (d) {
          while ((dir = readdir(d)) != NULL) {
            if(compare_string(dir->d_name, tlf->str)){
							exists = 1;
						}
          }
        closedir(d);
        }
				//exists = 1;
				if(exists){
          clear_str(tl);
					FILE *fp;
          printf("ready to open file\n" );
					fp = fopen(tlf->str, "r");
          printf("opened the file!\n");
					while(fgets(line, 399, fp) != NULL){
						sprintf(tl->str, "%s%s", tl->str, line);
					}

					fclose(fp);
					sprintf(tt,"%s%s",t3,tl->str);
				}
				else{
					sprintf(tt, "1,File Not Found");
				}



        struct STR* tl2 = new_str_with(150, tt);
        send_client_msg(my_addr, client_data_port, tl2);
        free_str(tl);
        free_str(tl2);

       }
       else{
         struct STR* ts = get_delim_at_with(msg->str, 1, ',');
         char t[100];
         char t2[] = "1,";
         memset(t, '\0', 100);
         sprintf(t,"%s%s",t2,ts->str);
         struct STR* ts2 = new_str_with(150, t);
         send_client_msg(my_addr, client_data_port, ts2);
         free_str(ts);
         free_str(ts2);

       }




       memset(temp, '\0', 100);
       close(new_fd);  // parent doesn't need this
   }














free_str(my_addr);
free_str(client_addr);
free_str(client_data_port);
free_str(my_port);
free_str(msg);














}
