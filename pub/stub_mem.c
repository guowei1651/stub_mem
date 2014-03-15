#include <libgen.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	char file[128];
  char function[128];
	int line;
	int size;
} story;

story _VERSION_NAME # list[3][512];

typedef enum
{
	MALLOC_INDEX,
	GETUB_INDEX,
	DDM_INDEX
}alloc_type;

int _VERSION_NAME # malloc_tc[3] = { 0 };

story* _VERSION_NAME # getstory(alloc_type type, int index)
{
	return &_VERSION_NAME # list[type][index];
}

void _VERSION_NAME # printstory (story* p)
{
    printf("%s:%s:%d size = %d\n", 
			  ((p->file == NULL) ?"(null)":p->file),
			  ((p->function == NULL) ? "(null)":p->function),
			  p->line,
			  p->size);
}

void _VERSION_NAME # malloc_count_common(alloc_type type, int size, const char *file, const char *function, int line)
{
	  story *p = NULL;
    file=basename((char *)file);

    p = _VERSION_NAME # getstory(type, _VERSION_NAME # malloc_tc[type]);

    strncpy(p->file, (char*)file, 127);
    strncpy(p->function, (char*)function, 127);
    
    p->line = line;
    p->size = size;

    _VERSION_NAME # malloc_tc[type]++;
    if (_VERSION_NAME # malloc_tc[type] >= (sizeof(_VERSION_NAME # list[0])/sizeof(_VERSION_NAME # list[0][0])))
    	_VERSION_NAME # malloc_tc[type] = 0;

    printf("index = %d type = %d ", _VERSION_NAME # malloc_tc[type], type);
    _VERSION_NAME # printstory(p);
}

int _VERSION_NAME # ShowMallocCount_common(alloc_type type)
{
    int i = 0;
    int sum = 0;

	  story *p = NULL;

    for (i = 0; i < _VERSION_NAME # malloc_tc[type]; i ++){
    	  p = _VERSION_NAME # getstory(type,i);
        printf("index = %d ", i);
        _VERSION_NAME # printstory(p);
        sum += p->size;
    }
    printf("sum = %d\n", sum);

    return sum;
}

void* _VERSION_NAME # _malloc_count(int size, const char *file, const char *function, int line)
{
    _VERSION_NAME # malloc_count_common(MALLOC_INDEX, size, file, function, line);
    return malloc(size);
}

void _VERSION_NAME # ShowMallocCount(void)
{
    int i = 0;
    int sum = 0;

    for (i = 0; i < (sizeof(_VERSION_NAME # malloc_tc)/sizeof(_VERSION_NAME # malloc_tc[0])); i ++){
    	  printf("------------start type is %d-----------\n", i);
        sum += _VERSION_NAME # ShowMallocCount_common(i);
    	  printf("------------end type is %d-----------\n", i);
    }
    printf("total sum = %d\n", sum);
}
