a toy memcached implementation implementation that follows the single listener-thread, multiple worker(via the fd handoff) threads model to support concurrent cache access for a large number of users 
A very basic scheduler is responsible for fd handoff between the listener thread and worker threads
Each worker thread runs an epoll based event loop, so that many clients can be handled concurrently without per-connection threads.

