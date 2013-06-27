#ifndef USEFULSTRING_H_INCLUDED
#define USEFULSTRING_H_INCLUDED

#include <string.h>
#include <stdlib.h>

void remchars(char *str, char c);
void remcnks(char *str, char *cnk);
void replchars(char *str, char c1, char c2);
void replcnks(char *str, char *cnk1, char *cnk2);
void reverse(char *str);



#endif // USEFULSTRING_H_INCLUDED
