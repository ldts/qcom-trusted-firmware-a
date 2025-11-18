/*
 * Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _VMIDMT_INTERNAL_H_
#define _VMIDMT_INTERNAL_H_

#include <stdint.h>
#include <vmidmt_hal.h>

#define MSM_VMIDMT_ERR_INT_STATUS_REG_NUM   1
#define MSM_VMIDMT_ERR_NUM_PER_REG          32

#define VMIDMT_ERR_OPT ( \
	HAL_VMIDMT_ERROR_O_SMCFCFG_EN | \
	HAL_VMIDMT_ERROR_O_USFCFG_EN  | \
	HAL_VMIDMT_ERROR_O_GCFGFIE    | \
	HAL_VMIDMT_ERROR_O_GCFGFRE    | \
	HAL_VMIDMT_ERROR_O_GFIE)

/* Default MemType when not overridden (implementation defined). */
#define MSM_VMIDMT_MEMTYPE_DEFAULT          0xFF
#define MSM_VMIDMT_MEMTYPE_STRONGLY_ORDERED 0

typedef struct {
	/* Bit position in status register */
	uint8_t bit_pos;
	/* Corresponding HAL VMIDMT index */
	uint8_t vmidmt;
} vmidmt_err_pos_to_hal_map_t;

typedef struct {
	uint8_t  table;       /* VMIDMT master port ID */
	uint8_t  err_opt;     /* Error reporting options */
	HAL_vmidmt_SecureStatusDetType *ssd_table; /* Pointer to SSD table */
	uint8_t  ssd_table_num_elements; /* Number of elements in SSD table */
	uint8_t  static_cfg;  /* 1 if configured statically at boot; 0 if master
			       * is power-collapsed at boot and configured at
			       * runtime after power-up
			       */
} vmidmt_cfg_t;

typedef struct {
	uint8_t  table;       /* VMIDMT master port ID */
	uint8_t  index;       /* Master index before VMID mapping */
	uint32_t sid_list[5]; /* List of SIDs */
	uint8_t  num_sids;    /* Number of SIDs in this list */
	uint8_t  vmid;        /* VMID to assign */
	uint8_t  static_cfg;  /* 1 if configured statically at boot; 0 if master
			       * is power-collapsed at boot and configured at
			       * runtime after power-up
			       */
	uint8_t  memattr;     /* If non-default, use supplied memory attributes */
} vmidmt_map_t;

#endif /* _VMIDMT_INTERNAL_H_ */

