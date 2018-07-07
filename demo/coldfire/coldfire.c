#include <stdio.h>
#include "coldfire.h"

/* 
   Convert range to new range
*/
float conv_range(float v, float org_min, float org_max,
			float new_min, float new_max)
{
  return v/(org_max-org_min) * (new_max-new_min);
}

int coldfire2data(float *v) {
  int vs, vn;
  int i;
  char cmdline[255];
  FILE *f;
  char data[256];
  char *e;
  char *p;

  /* Fetch ColdFire data using fetch command */
  sprintf(cmdline,"fetch -q %s 2>&1 /dev/null",COLDFIRE_URL);
#ifndef DEBUG
  /* for local debug */
  system(cmdline);
#else
  fprintf(stderr,"fetch -q %s 2>&1 /dev/null",COLDFIRE_URL);
#endif

  /* parse data */
  f=fopen(COLDFIRE_DATA,"r");
  while (fgets(data,256,f) != NULL) {
#ifdef DEBUG
    printf("%s",data);
#endif
  }
  fclose(f);
	 
#ifdef DEBUG
  fprintf(stderr,"Original data='%s'\n",data);
  fprintf(stderr,"\tdata[0]=%d",strtol(data,&e,10));
  fprintf(stderr,"\te=%d\n",e);
  fprintf(stderr,"\tsizeof(v)=%d, strlen(data)=%d\n",sizeof(v),strlen(data));
#endif

  vs=0;
  vn=0;
  for(p=data;p<(data+strlen(data)) && vn<sizeof(v)/sizeof(float);p++) {
#ifdef DEBUG
    fprintf(stderr,"::strtol(p)=%f, e=%d",(float)strtol(p,&e,10),e);
#endif
    v[vn]=(float)strtol(p,&e,10);
#ifdef DEBUG
    fprintf(stderr, "v[%d]=%d, p:%d, errno=%d\n",vn,v[vn],p,errno);
#endif
    p=e;
#ifdef DEBUG
    fprintf(stderr, "v[%d]=%f, errno=%d, p=%d, e=%d\n",vn,v[vn],errno,p,e);
#endif
    while(! isdigit(*p)) {
      p++;
    }
    p--;

    vn++;
  }

#ifdef DEBUG
  printf("Before conv:v[0]=%f,v[1]=%f,v[2]=%f\n",v[0],v[1],v[2]);	
#endif

  for(i=0;i<=sizeof(v)/sizeof(float);i++) {
    v[i]=conv_range(v[i], 0,ACCEL_MAX,0,360);
  }

#ifdef DEBUG
  fprintf(stderr,"After:v[0]=%f,v[1]=%f,v[2]=%f\n",v[0],v[1],v[2]);	
#else
 /* Why cannot remove this fprintf? */
  fprintf(stderr,"After:v[0]=%f,v[1]=%f,v[2]=%f\n",v[0],v[1],v[2]);	
#endif

  return 0;
}
