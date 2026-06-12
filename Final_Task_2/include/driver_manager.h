#ifndef DRIVER_MANAGER_H
#define DRIVER_MANAGER_H

#include "../include/common.h"

void create_driver(Driver *drivers, int *drivers_count);
void send_task(Driver *drivers, int drivers_count, pid_t pid, int timer);
void get_status(Driver *drivers, int drivers_count, pid_t pid);
void get_drivers(Driver* drivers, int drivers_count);

#endif
