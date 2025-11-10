#include <Arduino.h>
#include "slave.h"
#include "master.h"


#define RUN_MASTER

#ifdef RUN_MASTER
void setup() {
  setupMaster();
}
void loop() {
  loopMaster();
}
#endif

#ifdef RUN_SLAVE
void setup() {
  setupSlave();
}
void loop() {
  loopSlave();
}
#endif