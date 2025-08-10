#ifndef LGPIO_H
#define LGPIO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LG_RISING_EDGE 1
#define LG_FALLING_EDGE 2
#define LG_BOTH_EDGES 3

typedef struct {
  uint64_t timestamp; /* alert time in nanoseconds*/
  uint8_t chip;       /* gpiochip device number */
  uint8_t gpio;       /* offset into gpio device */
  uint8_t level;      /* 0=low, 1=high, 2=watchdog */
  uint8_t flags;      /* none defined, ignore report if non-zero */
} lgGpioReport_t;

typedef struct lgGpioAlert_s {
  lgGpioReport_t report;
  int nfyHandle;
} lgGpioAlert_t, *lgGpioAlert_p;

typedef void (*lgGpioAlertsFunc_t)(int num_alerts, lgGpioAlert_p alerts,
                                   void *userdata);

int lgGpiochipOpen(int gpioDev);
int lgGpioSetAlertsFunc(int handle, int gpio, lgGpioAlertsFunc_t cbf,
                        void *userdata);
int lgGpioClaimAlert(int handle, int flags, int edge, int gpio, int timeout);
int lgGpiochipClose(int handle);

#ifdef __cplusplus
}
#endif

#endif  // LGPIO_H
