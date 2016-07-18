#include <stdio.h>
#include <stdlib.h>

#define RGB565(r,g,b)((r >> 3) << 11 | (g >> 2) << 5 | ( b >> 3))
#define MAX_X    319
#define MAX_Y    239

#define LOAD_MAX 3

long myrand(long max)
{
  return((long)((float)random()/RAND_MAX*max));
}

void usage(char *prog)
{
	fprintf(stderr,"Usage: %s [-c]\n",prog);
	exit(-1);
}

int main(int argc,char** argv)
{
    int c;
    int pos,val;
    double avg;
    int i;
    char str[256];
    
    bcm2835_my_init();
    
    LCD_Init();

    if (argc > 1 && *argv[1] == '-') {
        if(argv[1][1] == 'c'){
          LCD_clear(RGB565(255,255,255));
          exit;
        }
    }

    pos=0;
    while(1) 
    {
        getloadavg(&avg,1);
        val=(int)(avg/LOAD_MAX*MAX_Y);

        printf("Input: %d %f(%d)\n",pos,avg,val);

        sprintf(str, "Loadavg: %.2f", avg);
        DisplayString(str,0,0);

        for(i=MAX_Y;i>=MAX_Y-val;i--)
        {
            write_dot(i, pos, RGB565(255,0,0));
        }
        for(;i>=0;i--)
        {
            write_dot(i, pos, RGB565(0,0,0));
        }
        for(i=0;i<val;i++)
        {
            write_dot(i, pos, RGB565(255,255,255));
        }
        pos+=1;
        if(pos>=MAX_X) pos=0;
    }

    return 0 ;
}
