/*
* api.h
*
* Created: 3/20/2019 11:18:10 AM
*  Author: Ruben
*/

#ifndef API_H_
#define API_H_

typedef enum
{
	Perform_Command = 0,
	Get_Encoding = 1
} M_Type;

typedef struct
{
	// TODO: Add Olaf's encoding table
} Encoding_Response;

typedef struct
{
	M_Type msg_type;
	char *body;
} Request;

int process_request(Request *req);

#endif /* API_H_ */