/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** test GC main
*/

#include "garbage_collector.h"

int main(void)
{
    void *ptr = MALLOC(sizeof(void *));
    ptr = MALLOC(sizeof(void *));
    ptr = MALLOC(sizeof(void *));

    (void) ptr;
    return (0);
}
