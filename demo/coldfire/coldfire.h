#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int coldfire2data(float *);
#define DEBUG 1

#ifdef DEBUG
#define COLDFIRE_HOST "sacraya.610t.org"
#else
#define COLDFIRE_HOST "192.168.2.201"
#endif
#define COLDFIRE_DATA "new_accel.htm"
#define COLDFIRE_URL "http://"COLDFIRE_HOST"/"COLDFIRE_DATA

#define ACCEL_MAX 4095
#define CF_DATA_NUM 3
#define FRAME_NUM 10

extern int errno;
