#include <stdio.h>
#include <stdlib.h>
#include "data.h"

#define CAPACITY 10

typedef struct { char *url; char *name; char *password; } record;
size_t capacity = CAPACITY; size_t size = 0; record *rec;

void init_record(record *rec, char *url, char *name, char *password)
 { rec->url = url; rec->name = name; rec->password = password; }

void init_data() { rec = malloc(capacity * sizeof(record)); }

void free_data() { free(rec); }

void set_data(char *url, char *name, char *password)
 { if (size == capacity) { capacity *= 2; rec = realloc(rec, capacity * sizeof(record)); }
   init_record(&rec[size++], url, name, password);
}
