#ifndef STUB_MEM_H
#define STUB_MEM_H

extern void* _VERSION_NAME # _malloc_count(int size, const char *file, const char *function, int line);

#undef malloc
#define malloc(size) _VERSION_NAME # _malloc_count(size, __FILE__, __FUNCTION__, __LINE__)

#endif
