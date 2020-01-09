#include <stdlib.h>
#include <stdio.h>
#include "HsFFI.h"
#include "AppMain_stub.h"
#include <unistd.h>

HsStablePtr hsEnvPtr = NULL;

char* jsaddleBuffer = NULL;

char* jsaddleBufferAlloc(int size) {
  if (size == 0) {
    return NULL;
  }
  if (jsaddleBuffer) { return jsaddleBuffer;}
  jsaddleBuffer = (char*) hsMalloc(size);
  return jsaddleBuffer;
}

int appExecStep (int dataLen) {
  int ret = hsAppExecStep (hsEnvPtr, jsaddleBuffer, dataLen);
  return ret;
}

HsBool mylib_init(void){
  int argc = 0;
  char *argv[] = { NULL };
  char **pargv = argv;

  hs_init(&argc, &pargv);

  hsEnvPtr = hsAppInit();

  return HS_BOOL_TRUE;
}

void mylib_end(void){
  hs_exit();
}

int main(int argc, char * argv[]) {
  mylib_init();
  printf("Haskell initialization done");
  _Exit(0);
  /* mylib_end(); */
}
