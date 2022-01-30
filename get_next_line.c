/*
** EPITECH PROJECT, 2018
** CPE_getnextline_2018
** File description:
** get_next_line
*/

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char *my_strcpy(char *dest, char const *src)
{
    int counter = 0;

    while (src[counter] != '\0') {
        dest[counter] = src[counter];
        counter ++;
    }
    dest[counter] = src[counter];
    return (dest);
}

char *get_next_line(int fd)
{
    char *buf;
    static char *buffer;
    char *tmp;
    static int i = 0;
    int b = 0;
    int count = 1;
    static int a = -42;

    if (READ_SIZE > 2147483646)
        return (NULL);
    if (a != -42)
	free(buf);
    buf = malloc(sizeof(char) * READ_SIZE);
    if (i == 0) {
        free(buffer);
        buffer = malloc(sizeof(char) * READ_SIZE);
        a = read(fd, buffer, READ_SIZE);
    }
    while (buffer[i] != '\n' && buffer[i] != '\0') {
        if (a == 0 || a == -1)
            return (NULL);
        buf[b] = buffer[i];
        b = b + 1;
        i = i + 1;
        if (i == READ_SIZE) {
            count = count + 1;
            tmp = malloc(sizeof(char) * READ_SIZE * count);
            my_strcpy(tmp, buf);
            free(buf);
            buf = malloc(sizeof(char) * READ_SIZE * count);
            my_strcpy(buf, tmp);
            free(tmp);
            a = read(fd, buffer, READ_SIZE);
            i = 0;
        }
    }
    i = i + 1;
    if (fd == 0)
        i = 0;
    buf[b] = '\0';
    return (buf);
}
