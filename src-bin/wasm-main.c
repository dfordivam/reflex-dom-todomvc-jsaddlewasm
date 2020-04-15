#include <stdlib.h>
#include <stdio.h>
#include "HsFFI.h"
#include <unistd.h>
#include "Rts.h"

// Copied from "AppMain_stub.h"

extern HsStablePtr hsAppInit(void);
extern HsInt64 hsAppExecStep(HsStablePtr a1, HsPtr a2, HsInt a3);
extern HsInt64 hsAppExecSync(HsStablePtr a1, HsPtr a2, HsInt a3);
extern HsPtr hsMalloc(HsInt a1);

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

int appExecSync (int dataLen) {
  int ret = hsAppExecSync (hsEnvPtr, jsaddleBuffer, dataLen);
  return ret;
}

HsBool mylib_init(void){
  int argc = 0;
  char *argv[] = { NULL };
  char **pargv = argv;

  RtsConfig conf = defaultRtsConfig;
  /* conf.rts_opts = "-DS -DG"; */
  conf.keep_cafs = true;
  hs_init_ghc(&argc, &pargv, conf);

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
