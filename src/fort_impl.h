#ifndef FORT_IMPL_H
#define FORT_IMPL_H

#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS /* To disable warnings for unsafe functions */
#endif

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "fort.h"



#define FORT_COL_SEPARATOR '|'

#define FORT_UNUSED  __attribute__((unused))

#define F_MALLOC fort_malloc
#define F_FREE fort_free
#define F_CALLOC fort_calloc
#define F_REALLOC fort_realloc
#define F_STRDUP fort_strdup
#define F_WCSDUP fort_wcsdup

#define F_CREATE(type) ((type *)F_CALLOC(sizeof(type), 1))

#define MAX(a,b) ((a) > (b) ? (a) : b)
#define MIN(a,b) ((a) < (b) ? (a) : b)


enum PolicyOnNull
{
    Create,
    DoNotCreate
};


enum F_BOOL
{
    F_FALSE = 0,
    F_TRUE = 1
};


#define STR_2_CAT_(arg1, arg2) \
    arg1##arg2
#define STR_2_CAT(arg1, arg2) \
    STR_2_CAT_(arg1, arg2)

#define UNIQUE_NAME_(prefix) \
    STR_2_CAT(prefix,__COUNTER__)
#define UNIQUE_NAME(prefix) \
    UNIQUE_NAME_(prefix)



/*****************************************************************************
 *               LOGGER
 *****************************************************************************/
#define SYS_LOG_ERROR(...)



/*****************************************************************************
 *               DEFAULT_SIZES
 * ***************************************************************************/
#define DEFAULT_STR_BUF_SIZE 1024
#define DEFAULT_VECTOR_CAPACITY 10



struct fort_table_options;
struct fort_column_options;
struct fort_row;
struct vector;
struct fort_cell;
struct string_buffer;
struct separator
{
    int enabled;
};

typedef struct fort_table_options fort_table_options_t;
struct fort_context
{
    fort_table_options_t *table_options;
    size_t row;
    size_t column;
};
typedef struct fort_context context_t;
typedef struct fort_column_options fort_column_options_t;
typedef struct vector vector_t;
typedef struct fort_cell fort_cell_t;
typedef struct string_buffer string_buffer_t;
typedef struct fort_row fort_row_t;
typedef struct fort_table FTABLE;
typedef struct separator separator_t;




/*****************************************************************************
 *               LIBFORT helpers
 *****************************************************************************/

extern void *(*fort_malloc)(size_t size);
extern void (*fort_free)(void *ptr);
extern void *(*fort_calloc)(size_t nmemb, size_t size);
extern void *(*fort_realloc)(void *ptr, size_t size);
void set_memory_funcs(void *(*f_malloc)(size_t size), void (*f_free)(void *ptr));


char *fort_strdup(const char* str);
wchar_t *fort_wcsdup(const wchar_t* str);
size_t number_of_columns_in_format_string(const char *fmt);
int snprint_n_chars(char *buf, size_t length, size_t n, char ch);
int wsnprint_n_chars(wchar_t *buf, size_t length, size_t n, wchar_t ch);


#define CHCK_RSLT_ADD_TO_WRITTEN(statement) \
    do { \
        tmp = statement; \
        if (tmp < 0) {\
            goto clear; \
        } \
        written += tmp; \
    } while(0)


#define CHECK_NOT_NEGATIVE(x) \
    do { if (x < 0) goto fort_fail; } while (0)

#endif /* FORT_IMPL_H */
