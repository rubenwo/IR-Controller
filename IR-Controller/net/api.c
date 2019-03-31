/*
* api.c
*
* Created: 3/20/2019 11:18:24 AM
*  Author: Ruben
*/

#include "api.h"

int process_request(Request *req)
{
	if (req->msg_type == Get_Encoding)
	{
		return 0;
	}

	if (req->msg_type == Perform_Command)
	{
		return 0;
	}

	return -1;
}