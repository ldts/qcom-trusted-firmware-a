/*
 * Copyright (c) 2026, Qualcomm Technologies, Inc. and/or its subsidiaries.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <lib/utils_def.h>
#include <xpu3.h>
#include <xpu_target_info.h>

#include <platform_def.h>

#define ANOC2_STATIC_REGION 0
#define MSS_Q6_STATIC_REGION 0

struct rg_domain_ownership ramblur_pimem_mpu_rgs[] = {
	{ 7, APPS_S_DOMAIN },
};

struct rg_partition_range ramblur_pimem_mpu_rg_addr[] = {
	{ 7, 0, 0 },
};

/*
 * MSS_Q6 MPU: no static regions on Lemans (MSS_Q6_STATIC_REGION == 0).
 * Only the UMR entry is set; partition slots are filled dynamically.
 */
struct rg_domain_ownership mss_q6_mpu_rgs[MSS_Q6_STATIC_REGION + 1 + NUM_MODEM_MPU_PARTITIONS] = {
	{ XPU_UMR_RG, APPS_NS_DOMAIN },
};

struct rg_partition_range mss_q6_mpu_rg_addr[MSS_Q6_STATIC_REGION + NUM_MODEM_MPU_PARTITIONS] = {
};

/*
 * SNOC_AGGRE2_MS_MPU_XPU3 (ANOC2): base 0x016a8000.
 * No static regions on Lemans (ANOC2_STATIC_REGION == 0).
 * Only the UMR entry is set; partition slots are filled dynamically.
 */
struct rg_domain_ownership
	anoc2_mpu_rgs[ANOC2_STATIC_REGION + 1 + NUM_MODEM_MPU_PARTITIONS] = {
		{ XPU_UMR_RG, APPS_NS_DOMAIN },
};

struct rg_partition_range
	anoc2_mpu_rg_addr[ANOC2_STATIC_REGION + NUM_MODEM_MPU_PARTITIONS] = {
};

/*
 * CNOC_GEMNOC_MPU_XPU3: base 0x01520000.
 * Per-RG partition data is platform-specific and not provided by
 * XPU_ResourceGroups.xml; left empty to be filled when data is available.
 */
struct rg_domain_ownership gemnoc_cnoc_mpu_rgs[] = {
};

struct rg_partition_range gemnoc_cnoc_mpu_rg_addr[] = {
};

/*
 * CNOC_SS_MPU_XPU3: base 0x01524000.
 * Per-RG partition data is platform-specific and not provided by
 * XPU_ResourceGroups.xml; left empty to be filled when data is available.
 */
struct rg_partition_range cnoc2_ss_mpu_rg_addr[] = {
};

struct rg_domain_ownership cnoc2_ss_mpu_rgs[] = {
};

/*
 * WPSS MPU: not present on Lemans.
 */
static struct rg_domain_ownership wpss_mpu_rgs[] = {
};

static struct rg_partition_range wpss_mpu_addr[] = {
};

/*
 * AOSS_CNOC_MPU_XPU3: base 0x0eff0000, range 0xeff0000-0xeff1eff.
 * Per-RG partition data is platform-specific and not provided by
 * XPU_ResourceGroups.xml; left empty to be filled when data is available.
 */
struct rg_domain_ownership aoss_cnoc_mpu_rgs[] = {
};

struct rg_partition_range aoss_cnoc_mpu_rg_addr[] = {
};

/*
 * MSS_NAV / ANOC1 / modem MS MPUs: dynamic-only; UMR entry only.
 */
struct rg_domain_ownership mss_nav_mpu_rgs[NUM_MSS_NAV_MPU_PARTITIONS + 1] = {
	{ XPU_UMR_RG, APPS_NS_DOMAIN },
};

struct rg_partition_range mss_nav_mpu_rg_addr[NUM_MSS_NAV_MPU_PARTITIONS] = {};

struct rg_domain_ownership anoc1_mpu_rgs[NUM_MSS_NAV_MPU_PARTITIONS + 1] = {
	{ XPU_UMR_RG, APPS_NS_DOMAIN },
};

struct rg_partition_range anoc1_mpu_rg_addr[NUM_MSS_NAV_MPU_PARTITIONS] = {};

struct rg_domain_ownership modem_ms_mpu_rgs[NUM_MSS_NAV_MPU_PARTITIONS + 1] = {
	{ XPU_UMR_RG, APPS_NS_DOMAIN },
};

struct rg_partition_range modem_ms_mpu_rg_addr[NUM_MSS_NAV_MPU_PARTITIONS] = {};

/*
 * Static MPU configuration table.
 *
 * Base addresses sourced from XPU_ResourceGroups.xml:
 *   RAMBLUR_PIMEM_MPU_XPU3       0x00616000
 *   SNOC_AGGRE2_MS_MPU_XPU3      0x016a8000  (ANOC2)
 *   CNOC_GEMNOC_MPU_XPU3         0x01520000
 *   CNOC_SS_MPU_XPU3             0x01524000
 *   AOSS_CNOC_MPU_XPU3           0x0eff0000
 */
struct xpu_instance msm_xpu_cfg[] = {
	{
		0x00616000,
		ARRAY_SIZE(ramblur_pimem_mpu_rgs),
		ramblur_pimem_mpu_rgs,
		ARRAY_SIZE(ramblur_pimem_mpu_rg_addr),
		ramblur_pimem_mpu_rg_addr,
		XPU_TYPE_RAMBLUR_PIMEM_MPU,
		XPU_PROTECTION_STATIC,
	},
	{
		0x016a8000,
		ANOC2_STATIC_REGION + 1,
		anoc2_mpu_rgs,
		ANOC2_STATIC_REGION,
		anoc2_mpu_rg_addr,
		XPU_TYPE_ANOC2_MPU,
		XPU_PROTECTION_STATIC,
	},
	{
		0x01520000,
		ARRAY_SIZE(gemnoc_cnoc_mpu_rgs),
		gemnoc_cnoc_mpu_rgs,
		ARRAY_SIZE(gemnoc_cnoc_mpu_rg_addr),
		gemnoc_cnoc_mpu_rg_addr,
		XPU_TYPE_CNOC_GEMNOC_MPU,
		XPU_PROTECTION_STATIC,
	},
	{
		0x01524000,
		ARRAY_SIZE(cnoc2_ss_mpu_rgs),
		cnoc2_ss_mpu_rgs,
		ARRAY_SIZE(cnoc2_ss_mpu_rg_addr),
		cnoc2_ss_mpu_rg_addr,
		XPU_TYPE_CNOC2_SS_MPU,
		XPU_PROTECTION_STATIC,
	},
	{
		0x0eff0000,
		ARRAY_SIZE(aoss_cnoc_mpu_rgs),
		aoss_cnoc_mpu_rgs,
		ARRAY_SIZE(aoss_cnoc_mpu_rg_addr),
		aoss_cnoc_mpu_rg_addr,
		XPU_TYPE_AOSS_CNOC_MPU,
		XPU_PROTECTION_STATIC,
	},
};

const uint32_t msm_xpu_cfg_count = ARRAY_SIZE(msm_xpu_cfg);

static struct xpu_instance rpm_mpus[] = {
};

struct mpu_ranges msm_mpu_ranges[] = {
	{
		DEVICE_RPM,
		ARRAY_SIZE(rpm_mpus),
		NUM_RPM_MPU_PARTITIONS,
		rpm_mpus,
	},
};

const uint32_t msm_mpu_ranges_count = ARRAY_SIZE(msm_mpu_ranges);
