/*
 * Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stddef.h>
#include <limits.h>
#include <stdint.h>
#include <common/debug.h>
#include <lib/utils_def.h>
#include <lib/mmio.h>
#include <arch_helpers.h>
#include <xpu_target_info.h>
#include <xpu3.h>

#define WORD_MASK			0xFFFFFFFF
#define WORD_SHIFT			32

#define INTR_EN_MASK			0x10F
#define DOMAIN_ENABLE_MASK		0x1
#define DOMAIN_LOG_MOD_DIS_MASK		0x2

#define XPU_TYPE_BITMASK		0x3
#define XPU_TYPE_MPU			0x2
#define XPU_PROTECTION_STATIC		0x1
#define XPU_INITIALIZED			0x2

#define XPU3_GCR0_OFFSET		0x0
#define XPU3_SCR0_OFFSET		0x8
#define XPU3_CR0_OFFSET			0x10
#define XPU3_QAD0_GCR0_OFFSET		0x80
#define XPU3_QAD0_CR0_OFFSET		0x90
#define XPU3_QAD1_GCR0_OFFSET		0x100
#define XPU3_QAD1_CR0_OFFSET		0x110
#define XPU3_UMR_GCR0_OFFSET		0x300
#define XPU3_IDR0_OFFSET		0x3F8
#define XPU3_REV_OFFSET			0x3FC
#define XPU3_LOG_MODE_DIS_OFFSET	0x400
#define XPU3_RGn_GCR0_OFFSET		0x1000
#define XPU3_RGn_CR0_OFFSET		0x1010
#define XPU3_RGn_CR1_OFFSET		0x1014
#define XPU3_RGn_CR2_OFFSET		0x1018
#define XPU3_RGn_CR3_OFFSET		0x101C
#define XPU3_RGn_START0_OFFSET		0x1030
#define XPU3_RGn_START1_OFFSET		0x1034
#define XPU3_RGn_END0_OFFSET		0x1038
#define XPU3_RGn_END1_OFFSET		0x103C
#define XPU3_UMR_CR1_OFFSET		0x314
#define XPU3_UMR_CR3_OFFSET		0x31C
#define XPU3_UMR_CR0_OFFSET		0x310
#define XPU3_UMR_CR2_OFFSET		0x318
#define XPU3_RGn_REG_SPACE_SIZE		0x80
#define XPU3_IDR0_NRG_BMSK		0x3FF0000
#define XPU3_IDR0_NRG_SHFT		0x10
#define XPU3_REV_SHFT			0x10
#define XPU3_EAR0_OFFSET		0
#define XPU3_EAR1_OFFSET		1
#define XPU3_ESR_OFFSET			2
#define XPU3_SRRESTORE_OFFSET		3
#define XPU3_ESYNR0_OFFSET		4
#define XPU3_ESYNR1_OFFSET		5
#define XPU3_ESYNR2_OFFSET		6
#define XPU3_ESYNR3_OFFSET		7
#define XPU3_ESYNR4_OFFSET		8

static uint8_t get_xpu_type(xpuInstanceType *xpu)
{
	uintptr_t base = xpu->xpu_base_addr;
	uint32_t raw;
	uint8_t type;

	raw  = mmio_read_32(base + XPU3_IDR0_OFFSET);
	type = (uint8_t)(raw & XPU_TYPE_BITMASK);

	return type;
}

static void dump_log(xpu_t xpu, int type)
{
	char sec_char[2] = { ' ', 0 };
	uint32_t xpu_addr;
	uint32_t offset;

	switch (type) {
	case XPU_ERR_SEC_CTX:
		offset = 0x800;
		sec_char[0] = 'S';
		break;
	case XPU_ERR_NON_SEC_CTX:
		offset = 0x880;
		break;
	default:
		return;
	}

	for (size_t i = 0; i < g_xpu_base_addr_array_count; i++) {
		if (g_xpu_base_addr_array[i].eXpu != xpu)
			continue;

		xpu_addr = g_xpu_base_addr_array[i].base_addr + offset;

		ERROR("%sEAR0 0x%x\n", sec_char,
		      mmio_read_32(xpu_addr + XPU3_EAR0_OFFSET));
		ERROR("%sEAR1 0x%x\n", sec_char,
		      mmio_read_32(xpu_addr + XPU3_EAR1_OFFSET));
		ERROR("%sESR 0x%x\n", sec_char,
		      mmio_read_32(xpu_addr + XPU3_ESR_OFFSET));
		ERROR("%sESYNR0 0x%x\n", sec_char,
		      mmio_read_32(xpu_addr + XPU3_ESYNR0_OFFSET));
		ERROR("%sESYNR1 0x%x\n", sec_char,
		      mmio_read_32(xpu_addr + XPU3_ESYNR1_OFFSET));
		ERROR("%sESYNR2 0x%x\n", sec_char,
		      mmio_read_32(xpu_addr + XPU3_ESYNR2_OFFSET));
		ERROR("%sESYNR3 0x%x\n", sec_char,
		      mmio_read_32(xpu_addr + XPU3_ESYNR3_OFFSET));
		ERROR("%sESYNR4 0x%x\n", sec_char,
		      mmio_read_32(xpu_addr + XPU3_ESYNR4_OFFSET));

		/* clear error (SRRESTORE) as xpu errors are non fatal */
		mmio_write_32(xpu_addr + XPU3_SRRESTORE_OFFSET, 0);

		break;
	}
}

void xpu_print_log(void *ctx)
{
	uint32_t err_bitmask[MSM_XPU_ERR_INT_REG_NUM] = { 0 };
	const xpu_intr_reg_dtls_t *p = NULL;
	int err_type = *(int *)ctx;
	uint32_t addr;
	uint32_t mask;

	ERROR("xpu: ISR\n");
	switch (err_type) {
	case XPU_ERR_SEC_CTX:
		ERROR("XPU ERROR: secure\n");
		p = xpu_sec_intr_status_reg;
		break;
	case XPU_ERR_NON_SEC_CTX:
		ERROR("XPU ERROR: non secure\n");
		p = xpu_non_sec_intr_status_reg;
		break;
	default:
		return;
	}

	for (size_t i = 0; i < MSM_XPU_ERR_INT_REG_NUM; i++, p++) {
		addr = p->xpu_intr_reg_addr;
		mask = p->xpu_intr_reg_mask;

		err_bitmask[i] = mmio_read_32(addr) & mask;
	}

	if (MSM_XPU_ERR_INT_REG_NUM == 1) {
		ERROR("XPU INTR 0 >> %08x\n", err_bitmask[0]);
	} else {
		ERROR("XPU INTR 0:1 >> %08x:%08x\n",
		      err_bitmask[0], err_bitmask[1]);
	}

	for (size_t reg = 0; reg < MSM_XPU_ERR_INT_REG_NUM; reg++) {
		xpu_err_pos_to_hal_map_t *row;

		mask = err_bitmask[reg];
		if (!mask)
			continue;

		row = xpu_err_pos_to_hal_map[reg];

		for (size_t i = 0; row[i].bit_mask != 0; i++) {
			const xpu_err_pos_to_hal_map_t *m;

			if (i >= MSM_XPU_ERR_NUM_PER_REG)
				break;

			m = &row[i];

			if (!(m->bit_mask & mask))
				continue;

			if (m->xpu >= XPU_TYPE_COUNT)
				continue;

			if (m->xpu == XPU_TYPE_NONE)
				continue;

			dump_log(m->xpu, err_type);
		}
	}
}

static uint32_t get_nrg(xpuInstanceType *xpu)
{
	uint32_t nrg = 0;

	nrg = mmio_read_32(xpu->xpu_base_addr + XPU3_IDR0_OFFSET) &
	      XPU3_IDR0_NRG_BMSK;

	return (nrg >> XPU3_IDR0_NRG_SHFT) + 1;
}

static void enable_domain(xpuInstanceType *xpu)
{
	uint32_t mask = DOMAIN_ENABLE_MASK;
	uint32_t a = 0;

	/* Already initialized */
	if (xpu->flag & XPU_INITIALIZED)
		return;

	xpu->flag |= XPU_INITIALIZED;

	a = mmio_read_32(xpu->xpu_base_addr + XPU3_GCR0_OFFSET);
	if (a)
		return;

	a = mmio_read_32(xpu->xpu_base_addr + XPU3_REV_OFFSET) >> XPU3_REV_SHFT;
	if (a > 0x3002) {
		mmio_write_32(xpu->xpu_base_addr + XPU3_LOG_MODE_DIS_OFFSET, 1);
		mask |= DOMAIN_LOG_MOD_DIS_MASK;
	}

	mmio_write_32(xpu->xpu_base_addr + XPU3_GCR0_OFFSET, mask);
	mmio_write_32(xpu->xpu_base_addr + XPU3_CR0_OFFSET, INTR_EN_MASK);
	mmio_write_32(xpu->xpu_base_addr + XPU3_QAD0_CR0_OFFSET, INTR_EN_MASK);
	mmio_write_32(xpu->xpu_base_addr + XPU3_QAD0_GCR0_OFFSET, mask);
	mmio_write_32(xpu->xpu_base_addr + XPU3_QAD1_CR0_OFFSET, INTR_EN_MASK);
	mmio_write_32(xpu->xpu_base_addr + XPU3_QAD1_GCR0_OFFSET, mask);

	dmbsy();
	isb();
}

static void set_mpu_permissions(xpuInstanceType *xpu, uint32_t rg_num)
{
	uintptr_t base = xpu->xpu_base_addr;
	uintptr_t cr0, cr1, cr2, cr3;
	uint32_t rg, perm_r, perm_w;
	int i;

	if (get_xpu_type(xpu) != XPU_TYPE_MPU)
		return;

	for (i = 0; i < xpu->part_range_arr_size; i++) {
		rg = xpu->partition_range[i].rg_num;

		if (rg_num != XPU_RG_ALL && rg != rg_num)
			continue;

		if (i >= xpu->owner_arr_size)
			break;

		perm_r = xpu->rg_owner[i].perm_r;
		perm_w = xpu->rg_owner[i].perm_w;

		if (xpu->rg_owner[i].rg_num == XPU_UMR_RG ||
		    (!perm_r && !perm_w))
			continue;

		cr1 = base + XPU3_RGn_CR1_OFFSET +
			XPU3_RGn_REG_SPACE_SIZE * rg;
		cr3 = base + XPU3_RGn_CR3_OFFSET +
			XPU3_RGn_REG_SPACE_SIZE * rg;
		cr0 = base + XPU3_RGn_CR0_OFFSET +
			XPU3_RGn_REG_SPACE_SIZE * rg;
		cr2 = base + XPU3_RGn_CR2_OFFSET +
			XPU3_RGn_REG_SPACE_SIZE * rg;

		/* Set permissions */
		mmio_write_32(cr1, perm_r);
		mmio_write_32(cr3, perm_w);

		if (perm_r & APPS_S_DOMAIN)
			mmio_write_32(cr0, 1);

		if (perm_w & APPS_S_DOMAIN)
			mmio_write_32(cr2, 1);
	}

	if (i >= xpu->owner_arr_size)
		goto out;

	/* Handle UMR region */
	if ((xpu->rg_owner[i].rg_num == XPU_UMR_RG) &&
	    (xpu->rg_owner[i].perm_r || xpu->rg_owner[i].perm_w)) {

		perm_r = xpu->rg_owner[i].perm_r;
		perm_w = xpu->rg_owner[i].perm_w;

		cr1 = base + XPU3_UMR_CR1_OFFSET;
		cr3 = base + XPU3_UMR_CR3_OFFSET;
		cr0 = base + XPU3_UMR_CR0_OFFSET;
		cr2 = base + XPU3_UMR_CR2_OFFSET;

		mmio_write_32(cr1, perm_r);
		mmio_write_32(cr3, perm_w);

		if (perm_r & APPS_S_DOMAIN)
			mmio_write_32(cr0, 1);

		if (perm_w & APPS_S_DOMAIN)
			mmio_write_32(cr2, 1);
	}
out:
	dmbsy();
	isb();
}

static void set_mpu_dynamic_permissions(xpuInstanceType *xpu,
					uint32_t rg_num,
					uint32_t perm_r,
					uint32_t perm_w)
{
	uintptr_t base = xpu->xpu_base_addr;
	uintptr_t cr1, cr3;
	uint32_t rg;

	if (get_xpu_type(xpu) != XPU_TYPE_MPU)
		return;

	for (size_t i = 0; i < xpu->part_range_arr_size; i++) {
		rg = xpu->partition_range[i].rg_num;

		if (rg_num != XPU_RG_ALL && rg != rg_num)
			continue;

		cr1 = base + XPU3_RGn_CR1_OFFSET +
			XPU3_RGn_REG_SPACE_SIZE * rg;
		cr3 = base + XPU3_RGn_CR3_OFFSET +
			XPU3_RGn_REG_SPACE_SIZE * rg;

		mmio_write_32(cr1, perm_r);
		mmio_write_32(cr3, perm_w);
	}
}

static void program_mpu_partitions(xpuInstanceType *xpu, uint32_t rg_num)
{
	uint32_t start_lo, start_hi, end_lo, end_hi;
	uintptr_t base = xpu->xpu_base_addr;
	uintptr_t start0, start1, end0, end1;
	uintptr_t start_addr, end_addr;
	uint32_t rg;

	if (get_xpu_type(xpu) != XPU_TYPE_MPU)
		return;

	for (size_t i = 0; i < xpu->part_range_arr_size; i++) {
		rg = xpu->partition_range[i].rg_num;

		if (rg_num != XPU_RG_ALL && rg != rg_num)
			continue;

		start_addr = xpu->partition_range[i].start_addr;
		end_addr   = xpu->partition_range[i].end_addr;

		start_lo = (uint32_t)(start_addr & WORD_MASK);
		start_hi = (uint32_t)(start_addr >> WORD_SHIFT);
		end_lo   = (uint32_t)(end_addr & WORD_MASK);
		end_hi   = (uint32_t)(end_addr >> WORD_SHIFT);

		start0 = base + XPU3_RGn_START0_OFFSET +
			XPU3_RGn_REG_SPACE_SIZE * rg;
		start1 = base + XPU3_RGn_START1_OFFSET +
			 XPU3_RGn_REG_SPACE_SIZE * rg;
		end0   = base + XPU3_RGn_END0_OFFSET +
			 XPU3_RGn_REG_SPACE_SIZE * rg;
		end1   = base + XPU3_RGn_END1_OFFSET +
			 XPU3_RGn_REG_SPACE_SIZE * rg;

		/* Set the specified address range in the partition */
		mmio_write_32(start0, start_lo);
		mmio_write_32(start1, start_hi);
		mmio_write_32(end0, end_lo);
		mmio_write_32(end1, end_hi);
	}

	dmbsy();
	isb();
}

static void set_region_ownership(xpuInstanceType *xpu, uint32_t rg_num)
{
	uintptr_t base = xpu->xpu_base_addr;
	uint32_t rg, owner;
	uintptr_t gcr0;

	for (size_t i = 0; i < xpu->owner_arr_size; i++) {
		owner = xpu->rg_owner[i].owner_domain;
		rg = xpu->rg_owner[i].rg_num;

		/* Handle unmapped region ownership */
		if (rg == XPU_UMR_RG) {
			gcr0 = base + XPU3_UMR_GCR0_OFFSET;
			mmio_write_32(gcr0, owner);
			continue;
		}

		/* Apply to ALL or specific region */
		if (rg_num != XPU_RG_ALL && rg != rg_num)
			continue;

		gcr0 = base + XPU3_RGn_GCR0_OFFSET +
			XPU3_RGn_REG_SPACE_SIZE * rg;

		/* Set the specified domain as the owner */
		mmio_write_32(gcr0, owner);
	}
}

void xpu_lock_down_assets(xpuInstanceType *xpus, uint8_t xpu_count)
{
	for (size_t i = 0; i < xpu_count; i++, xpus++) {
		if (!(xpus->flag & XPU_PROTECTION_STATIC))
			continue;

		enable_domain(xpus);
		program_mpu_partitions(xpus, XPU_RG_ALL);
		set_region_ownership(xpus, XPU_RG_ALL);
		set_mpu_permissions(xpus, XPU_RG_ALL);
	}
}

int xpu_lock_down_assets_dynamic(xpuInstanceType *xpus, uint8_t xpu_count,
				 uint32_t xpu_id, uint32_t rg_num,
				 uint32_t perm_r, uint32_t perm_w)
{
	uint32_t i;

	for (i = 0; i < xpu_count; i++, xpus++) {
		if (xpus->xpu_id == xpu_id)
			break;
	}

	if (i >= xpu_count)
		return -1;

	enable_domain(xpus);
	program_mpu_partitions(xpus, rg_num);
	set_region_ownership(xpus, rg_num);
	set_mpu_dynamic_permissions(xpus, rg_num, perm_r, perm_w);

	return 0;
}

void xpu_master_mpu_init(mpuRangesType *ranges, const uint32_t range_count)
{
	mpuRangesType *range_ptr = ranges;
	uint32_t owner_sz, part_sz;
	uint32_t rg_start;
	uint32_t dev_cnt;

	for (size_t i = 0; i < range_count; i++, range_ptr++) {
		xpuInstanceType *mpu_ptr = range_ptr->mpus;

		for (size_t j = 0; j < range_ptr->mpus_count; j++, mpu_ptr++) {
			RGDomainOwnershipType *owner_ptr;
			RGPrtitionRangeType *part_ptr;
			size_t start_owner;
			size_t start_part;

			dev_cnt  = range_ptr->device_prtn_cnt;
			owner_sz = mpu_ptr->owner_arr_size;
			part_sz  = mpu_ptr->part_range_arr_size;

			rg_start = get_nrg(mpu_ptr) - dev_cnt;

			/* Initialize RG ownership entries */
			start_owner = owner_sz - dev_cnt;
			owner_ptr = mpu_ptr->rg_owner + start_owner;

			for (size_t k = start_owner; k < owner_sz;
			      k++, owner_ptr++) {
				owner_ptr->owner_domain = NO_DOMAIN;
				owner_ptr->rg_num = rg_start + k - start_owner;
			}

			/* Initialize partition ranges */
			start_part = part_sz - dev_cnt;
			part_ptr = mpu_ptr->partition_range + start_part;

			for (size_t k = start_part; k < part_sz;
			      k++, part_ptr++) {
				part_ptr->start_addr = 0xfffffffful;
				part_ptr->end_addr   = 0xfffffffful;
				part_ptr->rg_num = rg_start + k - start_part;
			}

			enable_domain(mpu_ptr);
		}
	}
}

