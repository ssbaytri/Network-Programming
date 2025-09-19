#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void    print_help(void);
int     mask_to_cidr(const char *mask);
int     cidr_to_mask(char *cidr, int octets[4]);
