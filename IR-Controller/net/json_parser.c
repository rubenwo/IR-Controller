/*
* json_parser.c
*
* Created: 3/20/2019 11:41:44 AM
*  Author: Ruben
*/

#include "json_parser.h"
/**
* Allocates a fresh unused token from the token pool.
*/
static jsntok_t *jsn_alloc_token(jsn_parser *parser,
								 jsntok_t *tokens, size_t num_tokens)
{
	jsntok_t *tok;
	if (parser->toknext >= num_tokens)
	{
		return NULL;
	}
	tok = &tokens[parser->toknext++];
	tok->start = tok->end = -1;
	tok->size = 0;
#ifdef JSN_PARENT_LINKS
	tok->parent = -1;
#endif
	return tok;
}

/**
* Fills token type and boundaries.
*/
static void jsn_fill_token(jsntok_t *token, jsntype_t type,
						   int start, int end)
{
	token->type = type;
	token->start = start;
	token->end = end;
	token->size = 0;
}

/**
* Fills next available token with JSON primitive.
*/
static int jsn_parse_primitive(jsn_parser *parser, const char *js,
							   size_t len, jsntok_t *tokens, size_t num_tokens)
{
	jsntok_t *token;
	int start;

	start = parser->pos;

	for (; parser->pos < len && js[parser->pos] != '\0'; parser->pos++)
	{
		switch (js[parser->pos])
		{
#ifndef JSN_STRICT
		/* In strict mode primitive must be followed by "," or "}" or "]" */
		case ':':
#endif
		case '\t':
		case '\r':
		case '\n':
		case ' ':
		case ',':
		case ']':
		case '}':
			goto found;
		}
		if (js[parser->pos] < 32 || js[parser->pos] >= 127)
		{
			parser->pos = start;
			return JSN_ERROR_INVAL;
		}
	}
#ifdef JSN_STRICT
	/* In strict mode primitive must be followed by a comma/object/array */
	parser->pos = start;
	return JSN_ERROR_PART;
#endif

found:
	if (tokens == NULL)
	{
		parser->pos--;
		return 0;
	}
	token = jsn_alloc_token(parser, tokens, num_tokens);
	if (token == NULL)
	{
		parser->pos = start;
		return JSN_ERROR_NOMEM;
	}
	jsn_fill_token(token, JSN_PRIMITIVE, start, parser->pos);
#ifdef JSN_PARENT_LINKS
	token->parent = parser->toksuper;
#endif
	parser->pos--;
	return 0;
}

/**
* Fills next token with JSON string.
*/
static int jsn_parse_string(jsn_parser *parser, const char *js,
							size_t len, jsntok_t *tokens, size_t num_tokens)
{
	jsntok_t *token;

	int start = parser->pos;

	parser->pos++;

	/* Skip starting quote */
	for (; parser->pos < len && js[parser->pos] != '\0'; parser->pos++)
	{
		char c = js[parser->pos];

		/* Quote: end of string */
		if (c == '\"')
		{
			if (tokens == NULL)
			{
				return 0;
			}
			token = jsn_alloc_token(parser, tokens, num_tokens);
			if (token == NULL)
			{
				parser->pos = start;
				return JSN_ERROR_NOMEM;
			}
			jsn_fill_token(token, JSN_STRING, start + 1, parser->pos);
#ifdef JSN_PARENT_LINKS
			token->parent = parser->toksuper;
#endif
			return 0;
		}

		/* Backslash: Quoted symbol expected */
		if (c == '\\' && parser->pos + 1 < len)
		{
			int i;
			parser->pos++;
			switch (js[parser->pos])
			{
			/* Allowed escaped symbols */
			case '\"':
			case '/':
			case '\\':
			case 'b':
			case 'f':
			case 'r':
			case 'n':
			case 't':
				break;
			/* Allows escaped symbol \uXXXX */
			case 'u':
				parser->pos++;
				for (i = 0; i < 4 && parser->pos < len && js[parser->pos] != '\0'; i++)
				{
					/* If it isn't a hex character we have an error */
					if (!((js[parser->pos] >= 48 && js[parser->pos] <= 57) || /* 0-9 */
						  (js[parser->pos] >= 65 && js[parser->pos] <= 70) || /* A-F */
						  (js[parser->pos] >= 97 && js[parser->pos] <= 102)))
					{ /* a-f */
						parser->pos = start;
						return JSN_ERROR_INVAL;
					}
					parser->pos++;
				}
				parser->pos--;
				break;
			/* Unexpected symbol */
			default:
				parser->pos = start;
				return JSN_ERROR_INVAL;
			}
		}
	}
	parser->pos = start;
	return JSN_ERROR_PART;
}

/**
* Parse JSON string and fill tokens.
*/
int jsn_parse(jsn_parser *parser, const char *js, size_t len,
			  jsntok_t *tokens, unsigned int num_tokens)
{
	int r;
	int i;
	jsntok_t *token;
	int count = parser->toknext;

	for (; parser->pos < len && js[parser->pos] != '\0'; parser->pos++)
	{
		char c;
		jsntype_t type;

		c = js[parser->pos];
		switch (c)
		{
		case '{':
		case '[':
			count++;
			if (tokens == NULL)
			{
				break;
			}
			token = jsn_alloc_token(parser, tokens, num_tokens);
			if (token == NULL)
				return JSN_ERROR_NOMEM;
			if (parser->toksuper != -1)
			{
				tokens[parser->toksuper].size++;
#ifdef JSN_PARENT_LINKS
				token->parent = parser->toksuper;
#endif
			}
			token->type = (c == '{' ? JSN_OBJECT : JSN_ARRAY);
			token->start = parser->pos;
			parser->toksuper = parser->toknext - 1;
			break;
		case '}':
		case ']':
			if (tokens == NULL)
				break;
			type = (c == '}' ? JSN_OBJECT : JSN_ARRAY);
#ifdef JSN_PARENT_LINKS
			if (parser->toknext < 1)
			{
				return JSN_ERROR_INVAL;
			}
			token = &tokens[parser->toknext - 1];
			for (;;)
			{
				if (token->start != -1 && token->end == -1)
				{
					if (token->type != type)
					{
						return JSN_ERROR_INVAL;
					}
					token->end = parser->pos + 1;
					parser->toksuper = token->parent;
					break;
				}
				if (token->parent == -1)
				{
					if (token->type != type || parser->toksuper == -1)
					{
						return JSN_ERROR_INVAL;
					}
					break;
				}
				token = &tokens[token->parent];
			}
#else
			for (i = parser->toknext - 1; i >= 0; i--)
			{
				token = &tokens[i];
				if (token->start != -1 && token->end == -1)
				{
					if (token->type != type)
					{
						return JSN_ERROR_INVAL;
					}
					parser->toksuper = -1;
					token->end = parser->pos + 1;
					break;
				}
			}
			/* Error if unmatched closing bracket */
			if (i == -1)
				return JSN_ERROR_INVAL;
			for (; i >= 0; i--)
			{
				token = &tokens[i];
				if (token->start != -1 && token->end == -1)
				{
					parser->toksuper = i;
					break;
				}
			}
#endif
			break;
		case '\"':
			r = jsn_parse_string(parser, js, len, tokens, num_tokens);
			if (r < 0)
				return r;
			count++;
			if (parser->toksuper != -1 && tokens != NULL)
				tokens[parser->toksuper].size++;
			break;
		case '\t':
		case '\r':
		case '\n':
		case ' ':
			break;
		case ':':
			parser->toksuper = parser->toknext - 1;
			break;
		case ',':
			if (tokens != NULL && parser->toksuper != -1 &&
				tokens[parser->toksuper].type != JSN_ARRAY &&
				tokens[parser->toksuper].type != JSN_OBJECT)
			{
#ifdef JSN_PARENT_LINKS
				parser->toksuper = tokens[parser->toksuper].parent;
#else
				for (i = parser->toknext - 1; i >= 0; i--)
				{
					if (tokens[i].type == JSN_ARRAY || tokens[i].type == JSN_OBJECT)
					{
						if (tokens[i].start != -1 && tokens[i].end == -1)
						{
							parser->toksuper = i;
							break;
						}
					}
				}
#endif
			}
			break;
#ifdef JSN_STRICT
		/* In strict mode primitives are: numbers and booleans */
		case '-':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 't':
		case 'f':
		case 'n':
			/* And they must not be keys of the object */
			if (tokens != NULL && parser->toksuper != -1)
			{
				jsntok_t *t = &tokens[parser->toksuper];
				if (t->type == JSN_OBJECT ||
					(t->type == JSN_STRING && t->size != 0))
				{
					return JSN_ERROR_INVAL;
				}
			}
#else
		/* In non-strict mode every unquoted value is a primitive */
		default:
#endif
			r = jsn_parse_primitive(parser, js, len, tokens, num_tokens);
			if (r < 0)
				return r;
			count++;
			if (parser->toksuper != -1 && tokens != NULL)
				tokens[parser->toksuper].size++;
			break;

#ifdef JSN_STRICT
		/* Unexpected char in strict mode */
		default:
			return JSN_ERROR_INVAL;
#endif
		}
	}

	if (tokens != NULL)
	{
		for (i = parser->toknext - 1; i >= 0; i--)
		{
			/* Unmatched opened object or array */
			if (tokens[i].start != -1 && tokens[i].end == -1)
			{
				return JSN_ERROR_PART;
			}
		}
	}

	return count;
}

/**
* Creates a new parser based over a given  buffer with an array of tokens
* available.
*/
void jsn_init(jsn_parser *parser)
{
	parser->pos = 0;
	parser->toknext = 0;
	parser->toksuper = -1;
}