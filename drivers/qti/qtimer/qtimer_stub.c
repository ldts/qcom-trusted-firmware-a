/*
 * Copyright (c) 2025 Qualcomm Technologies, Inc. and/or its subsidiaries.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <drivers/qti/qtimer/qtimer.h>
#include <common/debug.h>

void qti_qtimer_init(void)
{
}

uint64_t qti_qtimer_get_raw(void)
{
	WARN("Qtimer not supported\n");
	return 0LL;
}

uint64_t qti_qtimer_get_usec(void)
{
	WARN("Qtimer not supported.\n");
	return 0LL;
}

