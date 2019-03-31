/*
* json_parser.h
*
* Created: 3/20/2019 11:41:33 AM
*  Author: Ruben
*/

#ifndef JSONPARSER_H_
#define JSONPARSER_H_

#include <stddef.h>

/**
* JSON type identifier. Basic types are:
* 	o Object
* 	o Array
* 	o String
* 	o Other primitive: number, boolean (true/false) or null
*/
typedef enum
{
	JSN_UNDEFINED = 0,
	JSN_OBJECT = 1,
	JSN_ARRAY = 2,
	JSN_STRING = 3,
	JSN_PRIMITIVE = 4
} jsntype_t;

enum jsnerr
{
	/* Not enough tokens were provided */
	JSN_ERROR_NOMEM = -1,
	/* Invalid character inside JSON string */
	JSN_ERROR_INVAL = -2,
	/* The string is not a full JSON packet, more bytes expected */
	JSN_ERROR_PART = -3
};

/**
* JSON token description.
* type		type (object, array, string etc.)
* start	start position in JSON data string
* end		end position in JSON data string
*/
typedef struct
{
	jsntype_t type;
	int start;
	int end;
	int size;
#ifdef JSN_PARENT_LINKS
	int parent;
#endif
} jsntok_t;

/**
* JSON parser. Contains an array of token blocks available. Also stores
* the string being parsed now and current position in that string
*/
typedef struct
{
	unsigned int pos;	 /* offset in the JSON string */
	unsigned int toknext; /* next token to allocate */
	int toksuper;		  /* superior token node, e.g parent object or array */
} jsn_parser;

/**
* Create JSON parser over an array of tokens
*/
void jsn_init(jsn_parser *parser);

/**
* Run JSON parser. It parses a JSON data string into and array of tokens, each describing
* a single JSON object.
*/
int jsn_parse(jsn_parser *parser, const char *js, size_t len,
			  jsntok_t *tokens, unsigned int num_tokens);

#endif /* JSONPARSER_H_ */