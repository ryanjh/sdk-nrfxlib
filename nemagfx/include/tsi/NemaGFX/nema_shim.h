/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef NEMA_SHIM_H__
#define NEMA_SHIM_H__

void nema_irq_reset(void);
void nema_irq_set(void);
bool nema_check_irq(void);
void nema_sysirq_reset(void);
void nema_sysirq_set(void);
bool nema_check_sysirq(void);
int nema_get_clid(void);
void nema_error_set(unsigned long int error);

#endif
