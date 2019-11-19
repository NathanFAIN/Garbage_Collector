/*
** EPITECH PROJECT, 2019
** garbage_collector.h
** File description:
** my personal garbage collector in c
*/

#ifndef GARBAGE_COLLECTOR_H_
#define GARBAGE_COLLECTOR_H_

#include <stdlib.h>

#define MALLOC(SIZE)    gc_alloc_ptr_list(SIZE)

extern void *gc_alloc_ptr_list(size_t alloc_size) \
__attribute__ ((returns_nonnull, alloc_size (1)));
void gc_destroy_ptr_list() __attribute__ ((destructor));

#endif
