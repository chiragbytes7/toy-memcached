 #include<thread>
#include<string>
#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/epoll.h>

using namespace std;

void thread_function(int x){
	cout << "you asked to print the number....." << x << endl; 
}

void dispatch_to_worker(vector<thread>& thread_pool, int client_sock_fd){
	//pick a thread from thread pool and pass the client fd to that thread
	int chosen = thread_pool[0];
}

class Worker{
public:
	int pipe_fd[2];
	thread worker_thread;
	int epoll_fd;
	
	Worker(){
		if(pipe(pipe_fd) == -1) perror("error creating pipe");
		epoll_fd = epoll_create1(0);
		struct epoll_event event{};
		event.events = EPOLLIN | EPOLLOUT;
		event.data.fd = pipe_fd[0];
		if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, pipe_fd[0], &event) == -1) perror("problem adding the read end of the pipe to the worker epoll");
		else cout << "read end of pipe added to the epoll of the worker";
		int n = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
}

}

int find_worker_in_pool(int current_worker){
	return (current_worker + 1 % 5);
}

void dispatch_to_worker(int current_worker, int client_sock_fd, vector<Worker>& thread_pool){
	int worker_number = find_worker_in_pool(current_worker);
	write(thread_pool[worker_number].pipe_fd[1], &client_socket_fd, sizeof(client_socket_fd));
}

int main(){
	//creating a thread pool here 
	vector<Worker>thread_pool(5);
	int current_worker = 0;
	//listener socket is defined here 
	int listen_fd = socket(AF_NET, SOCK_STREAM, 0);
	struct sockaddr_in sock_addr;
	sock_addr.sin_family = AF_NET;
	sock_addr.sin_port = htons(8080);
	sock_addr.sin_addr.s_addr = INADDR_ANY;

	bind(listen_fd,(struct sockaddr*)&sock_addr, sizeof(sock_addr));
	listen(listen_fd, 5);

	//this is where the listener socket listens to incoming connections
	while(1){
	struct sockaddr_in client_addr;
	int client_sock_fd = accept(sock_addr, (struct sockaddr*)client_addr, sizeof(client_addr));
	printf("new client socket created by listener thread");
	dispatch_to_worker(client_sock_fd);
	}
}
