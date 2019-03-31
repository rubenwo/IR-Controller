/*
* api.h
*
* Created: 3/20/2019 11:18:10 AM
*  Author: Ruben
*/

#ifndef API_H_
#define API_H_

/*
	M_Type is an enum used to determine which message was sent.
*/
typedef enum
{
	Perform_Command = 0,
	Get_Encoding = 1
} M_Type;

/*
	Encoding_Response is a struct defining the response on a Get_Encoding request from a client.
*/
typedef struct
{
	int e; // TODO: Add Olaf's encoding table
} Encoding_Response;

/*
	Request is a struct defining a request message from a client.
*/
typedef struct
{
	M_Type msg_type;
	char *body;
} Request;

/*
	process_request processes a request. eg. if req is a Get_Encoding request it will send back an appropriate response.
	@param req - This is a pointer to a Request.
*/
int process_request(Request *req);

#endif /* API_H_ */