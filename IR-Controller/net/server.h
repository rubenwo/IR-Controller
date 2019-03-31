/*
* server.h
*
* Created: 3/20/2019 11:18:50 AM
*  Author: Ruben
*/

#ifndef SERVER_H_
#define SERVER_H_

/*
    init_server initializes the wifi connection and server. return 0 on success.
*/
int init_server(void);
/*
    update_server is a function used in the update loop for updating server components.
*/
int update_server(void);
#endif /* SERVER_H_ */