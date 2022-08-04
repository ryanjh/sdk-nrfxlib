/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef NEMA_SYS_DEFS_H__
#define NEMA_SYS_DEFS_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef NEMA_MEM_POOL_CL
#define NEMA_MEM_POOL_CL     0
#endif

#ifndef NEMA_MEM_POOL_FB
#define NEMA_MEM_POOL_FB     0
#endif

#ifndef NEMA_MEM_POOL_ASSETS
#define NEMA_MEM_POOL_ASSETS 0
#endif

#ifdef NEMA_MULTI_THREAD
#define TLS_VAR __thread
#else
#define TLS_VAR
#endif

#endif
