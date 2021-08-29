#include <stdio.h>
#include <unistd.h>
#include "zing.h"

void zing(void) {
	printf("o user %s einai megalo tsakali\n", getlogin());
}
