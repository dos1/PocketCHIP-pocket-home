#include "BatteryMonitor.h"
#include "Utils.h"

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
       
BatteryMonitor::BatteryMonitor( )
  : Thread( "BatteryMonitor" ) {
  status.percentage = 0;
  status.isCharging = 0;
}

BatteryMonitor::~BatteryMonitor( ) {
}

const BatteryStatus& BatteryMonitor::getCurrentStatus( ) {
  return status;
}

void BatteryMonitor::updateStatus() {
  FILE* file = fopen("/usr/lib/pocketchip-batt/charging", "r");
  fscanf(file, "%d", &status.isCharging);
  fclose(file);

  file = fopen("/usr/lib/pocketchip-batt/gauge", "r");
  fscanf(file, "%d", &status.percentage);
  fclose(file);
}

void BatteryMonitor::run( ) {
  while( !threadShouldExit() ) {
    updateStatus();
    wait(5000);
  }
}
