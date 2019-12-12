#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jsmn/jsmn.h"

/* https://zserge.com/jsmn/ */
    /* https://github.com/zserge/jsmn/blob/master/example/simple.c */

/* http://www.mark-fink.de/2019-01-20-structured-jsmn-json-parser-sample/ */
    /* https://github.com/finklabs/esp32/blob/master/jsmn_demo/test/main/test_app.c */

typedef struct
{

} fields;

typedef struct
{

} records;

typedef struct
{
    fields  fields[17];
    records records[25];
} el_data;

int createJSON           (char *JSON_STRING);
int parse_sense_object   (char *JSON_STRING, jsmntok_t *token, int *i);
int parse_records_object (char *JSON_STRING, jsmntok_t *token, int *i);
int jsoneq               (char *JSON_STRING, jsmntok_t *token, char *string);

int main(void)
{
    FILE        *file;
    char         buffer[4096];

    file =  fopen("Data.json", "r");
            fread(&buffer, sizeof(char), 4096, file);
            if(file == NULL)
                return 1;
            fclose(file);

    createJSON(buffer);

    return EXIT_SUCCESS;
}

int createJSON(char *JSON_STRING)
{
    int array_size;
    int i, j, r;
	jsmn_parser p;
	jsmntok_t tokens[1024]; 
	jsmn_init(&p);

	r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), tokens, sizeof(tokens)/sizeof(tokens[0]));
	if (r < 0)
    {
		printf("Failed to parse JSON: %d\n", r);
		return EXIT_FAILURE;
	}

	for (i = 1; i < r; i++) 
    {  
		if (jsoneq(JSON_STRING, &tokens[i], "fields") == 0)
        {
            i++;
            array_size = tokens[i].size;
			printf("- Fields:\n");
            printf("  Size of array: %d\n", array_size);
            i++;
			for (j = 0; j < array_size; j++) 
            {
                printf("%2d", j);
                parse_sense_object(JSON_STRING, tokens, &i);
			}
            i--;  /*This is to make i be 17, so that it checks "user" */
		}
        else if (jsoneq(JSON_STRING, &tokens[i], "records") == 0)
        {
            i++;
            array_size = tokens[i].size;
			printf("- Records:\n");
            printf("  Size of object: %d\n", array_size);
            i++;
			for (j = 0; j < array_size; j++) 
            {
                printf("%2d ", j);
                parse_records_object(JSON_STRING, tokens, &i);
			}
		}
        else
        {
			printf("Unexpected key: %.*s\n", tokens[i].end - tokens[i].start, JSON_STRING + tokens[i].start);
		}
	}

    return EXIT_SUCCESS;
}

int parse_sense_object(char *JSON_STRING, jsmntok_t *token, int *i) 
{
    int k;
    int array_size = token[(*i)].size;

    (*i)++; 
    for (k = 0; k < array_size; k++) 
    {
        if (jsoneq(JSON_STRING, &token[(*i)], "type") == 0)
        {
            (*i)++;  
            printf("  Type: %.*s\n", token[(*i)].end - token[(*i)].start, JSON_STRING + token[(*i)].start);
        }
        else if (jsoneq(JSON_STRING, &token[(*i)], "id") == 0)
        {
            (*i)++; 
            printf("    Id: %.*s\n", token[(*i)].end - token[(*i)].start, JSON_STRING + token[(*i)].start);
        }
        else
        {
            printf("XUnexpected key: %.*s\n", token[(*i)].end - token[(*i)].start, JSON_STRING + token[(*i)].start);
        }
        (*i)++;
    }

  return EXIT_SUCCESS;
}

int parse_records_object(char *JSON_STRING, jsmntok_t *token, int *i)
{
    int k;
    int array_size = token[(*i)].size;

    (*i)++; 
    for (k = 0; k < array_size; k++) 
    {
        printf("   %8.*s", token[(*i)].end - token[(*i)].start, JSON_STRING + token[(*i)].start);
        (*i)++;
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int jsoneq(char *JSON_STRING, jsmntok_t *token, char *string) 
{
    if (token->type == JSMN_STRING && (int) strlen(string) == token->end - token->start &&
        strncmp(JSON_STRING + token->start, string, token->end - token->start) == 0)
    {
        return 0;
    }
    return -1;
}