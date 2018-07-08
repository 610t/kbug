#include <stdio.h>
#include "coldfire.h"

int frame=0;
int old_v[CF_DATA_NUM];

/* 
   Convert range to new range
*/
float conv_range(float v, float org_min, float org_max,
			float new_min, float new_max)
{
  return v/(org_max-org_min) * (new_max-new_min);
}

int coldfire2data(float *v) {
  int i;
  char cmdline[MAX_STR];
  FILE *f;
  char data[MAX_STR];
  char *d;
  char *endp;

  /* Update coldfire data / FRAME_NUM frame */
  frame++;
  if(frame % FRAME_NUM) {
    for(i=0;i<CF_DATA_NUM;i++) {
      v[i]=old_v[i];
      return 0;
    }
  }

  /* Fetch ColdFire data using fetch command */
  sprintf(cmdline,"fetch -q -T 1 %s 2>&1 /dev/null",COLDFIRE_URL);
#ifndef DEBUG
  /* for local debug */
  system(cmdline);
#else
  fprintf(stderr,"fetch -q -T 1 %s 2>&1 /dev/null",COLDFIRE_URL);
#endif

  /* parse data */
  f=fopen(COLDFIRE_DATA,"r");
  while (fgets(data,MAX_STR-1,f) != NULL) {
#ifdef DEBUG
    printf("%s",data);
#endif
  }
  fclose(f);

  /* NULL terminate */
#ifdef DEBUG
  printf("org data=\"%s\"\n",data);
#endif
  for(i=0;i<strlen(data);i++){
    if(data[i]=='\n') {
      data[i]=0;
      break;
    }
  }
#ifdef DEBUG
  printf("null data=\"%s\"\n",data);
#endif

#ifdef DEBUG
  fprintf(stderr,"Original data='%s'\n",data);
  fprintf(stderr,"\tdata[0]=%ld",strtol(data,&e,10));
//  fprintf(stderr,"\tsizeof(v)=%d, strlen(data)=%d\n",sizeof(v),strlen(data));
#endif

  d=data;
  endp=d;
  i=0;
  while(*endp!=0) {
    v[i]=strtol(d,&endp,10);
    printf("v[%d]=%f,",i,v[i]);
    if(*endp==0) break;
    while(!(*endp>='0' && *endp<='9')) {
      endp++;
#ifdef DEBUG
      printf("loop:Rest str[%ld]:\"%s\"%d:\n",(long)endp,endp,(int)*endp);
#endif
      if(*endp==0) break;
    }
    d=endp;
    i++;
    if(i>=CF_DATA_NUM) break;
  }
  printf("\n");

#ifdef DEBUG
  printf("Before conv:");
  for(i=0;i<CF_DATA_NUM;i++) {
    printf("v[%d]=%f,",i,v[i]);	
  }
#endif

  for(i=0;i<=sizeof(v)/sizeof(float);i++) {
    v[i]=conv_range(v[i], 0,ACCEL_MAX,0,360);
  }

#ifdef DEBUG
  printf("After conv:");
  for(i=0;i<CF_DATA_NUM;i++) {
    printf("v[%d]=%f,",i,v[i]);	
  }
#endif

  /* Backup old data */
  for(i=0;i<CF_DATA_NUM;i++){
    old_v[i]=v[i];
  }
  return 0;
}
