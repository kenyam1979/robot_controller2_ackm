#include "lgpio.h"

int lgGpiochipOpen(int gpioDev) {
  if (gpioDev != 4) {
    return -1;  // Invalid device number
  }

  return 0;  // Placeholder for actual implementation
}

int lgGpioSetAlertsFunc(int handle, int gpio, lgGpioAlertsFunc_t cbf,
                        void *userdata) {
  if (handle != 0) {
    return -1;  // Invalid handle number
  }
  return 0;  // Placeholder for actual implementation
}

int lgGpioClaimAlert(int handle, int flags, int edge, int gpio, int timeout) {
  if (handle != 0) {
    return -1;  // Invalid handle number
  }
  return 0;  // Placeholder for actual implementation
}

int lgGpiochipClose(int handle) {
  if (handle != 0) {
    return -1;  // Invalid handle number
  }
  return 0;  // Placeholder for actual implementation
}
