/*
** EPITECH PROJECT, 2019
** garbage_collector.c
** File description:
** functions for garbage collector
*/

#include "garbage_collector.h"

static inline __attribute__((always_inline, returns_nonnull)) \
void *gc_get_ptr_list(void)
{
    static void *ptr_list = NULL;

    return (&ptr_list);
}

inline __attribute__((always_inline, returns_nonnull, alloc_size (1))) \
void *gc_alloc_ptr_list(size_t alloc_size)
{
    void **ptr_list = gc_get_ptr_list();
    void *ptr = malloc(sizeof(void *) + alloc_size);

    (*((void **)ptr)) = (*ptr_list);
    (*ptr_list) = ptr;
    return (ptr + sizeof(void *));
}

void __attribute__ ((destructor)) gc_destroy_ptr_list(void)
{
    void *ptr_list = (*((void **)gc_get_ptr_list()));
    void *ptr;

    while (((ptr) = ptr_list)) {
        ptr_list = (*((void **)ptr_list));
        free(ptr);
    }
}
