#include "utils.h"

unsigned char abs(char v)
{
	return v * ((v > 0) - (v < 0));
}