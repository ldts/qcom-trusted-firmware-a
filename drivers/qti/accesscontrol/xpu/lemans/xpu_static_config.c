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

struct rg_domain_ownership llcc_mpu_rgs[] = {
	{ 0, APPS_S_DOMAIN },
};

struct rg_partition_range llcc_mpu_rg_addr[] = {
	{ 0, BL31_BASE, BL31_BASE + BL31_SIZE },
};

struct rg_domain_ownership gemnoc_cnoc_mpu_rgs[] = {
	{ 6,           APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
	{ 19,          APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
	{ 24,          APPS_S_DOMAIN,  MSA_DOMAIN,      MSA_DOMAIN     },
	{ 25,          APPS_S_DOMAIN,  MSA_DOMAIN,      MSA_DOMAIN     },
	{ 26,          APPS_S_DOMAIN },
	{ 27,          APPS_S_DOMAIN,  0,               APPS_NS_DOMAIN },
	{ 28,          APPS_S_DOMAIN,  0,               APPS_NS_DOMAIN },
	{ 29,          APPS_S_DOMAIN },
	{ 30,          APPS_S_DOMAIN },
	{ XPU_UMR_RG,  APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
};

struct rg_partition_range gemnoc_cnoc_mpu_rg_addr[] = {
	{ 6,           0x0C200000 & 0xffffffffL,  0x0C300000 & 0xffffffffL },
	{ 19,          0x09A36000 & 0xffffffffL,  0x09A37000 & 0xffffffffL },
	{ 24,          0x0C263000 & 0xffffffffL,  0x0C264000 & 0xffffffffL },
	{ 25,          0x0C265000 & 0xffffffffL,  0x0C266000 & 0xffffffffL },
	{ 26,          0x0C251000 & 0xffffffffL,  0x0C253000 & 0xffffffffL },
	{ 27,          0x01790000 & 0xffffffffL,  0x01792000 & 0xffffffffL },
	{ 28,          0x09A30000 & 0xffffffffL,  0x09A32000 & 0xffffffffL },
	{ 29,          0x016B0000 & 0xffffffffL,  0x016B2000 & 0xffffffffL },
	{ 30,          0x0ACAC000 & 0xffffffffL,  0x0ACAD000 & 0xffffffffL },

};

struct rg_partition_range cnoc_ss_mpu_rg_addr[] = {
	{ 0,           0x0168A000 & 0xffffffffL,  0x01690000 & 0xffffffffL },
	{ 1,           0x01693000 & 0xffffffffL,  0x0169B000 & 0xffffffffL },
	{ 2,           0x09000000 & 0xffffffffL,  0x09A32000 & 0xffffffffL },
	{ 6,           0x00634000 & 0xffffffffL,  0x00635000 & 0xffffffffL },
	{ 7,           0x014C0000 & 0xffffffffL,  0x014D4000 & 0xffffffffL },
	{ 9,           0x016C0000 & 0xffffffffL,  0x016D0000 & 0xffffffffL },
	{ 10,          0x01700000 & 0xffffffffL,  0x01711000 & 0xffffffffL },
	{ 11,          0x016D9000 & 0xffffffffL,  0x016FB000 & 0xffffffffL },
	{ 12,          0x01718000 & 0xffffffffL,  0x01727000 & 0xffffffffL },
	{ 13,          0x09A36000 & 0xffffffffL,  0x09A37000 & 0xffffffffL },
	{ 14,          0x260C0000 & 0xffffffffL,  0x260CD000 & 0xffffffffL },
	{ 15,          0x260D1000 & 0xffffffffL,  0x260D7000 & 0xffffffffL },
	{ 17,          0x2A0D1000 & 0xffffffffL,  0x2A0D7000 & 0xffffffffL },
	{ 20,          0x04858000 & 0xffffffffL,  0x04859000 & 0xffffffffL },
	{ 24,          0x00636000 & 0xffffffffL,  0x00637000 & 0xffffffffL },
	{ 25,          0x0176B000 & 0xffffffffL,  0x0177B000 & 0xffffffffL },
	{ 29,          0x088E3000 & 0xffffffffL,  0x088E4000 & 0xffffffffL },
	{ 30,          0x00638000 & 0xffffffffL,  0x00639000 & 0xffffffffL },
	{ 31,          0x016E0000 & 0xffffffffL,  0x016E2000 & 0xffffffffL },
	{ 32,          0x010D2000 & 0xffffffffL,  0x010D3000 & 0xffffffffL },
	{ 33,          0x0C200000 & 0xffffffffL,  0x0C210000 & 0xffffffffL },
	{ 40,          0x0C263000 & 0xffffffffL,  0x0C264000 & 0xffffffffL },
	{ 41,          0x0C265000 & 0xffffffffL,  0x0C266000 & 0xffffffffL },
	{ 42,          0x0C251000 & 0xffffffffL,  0x0C253000 & 0xffffffffL },
	{ 43,          0x01790000 & 0xffffffffL,  0x01792000 & 0xffffffffL },
};

struct rg_domain_ownership cnoc_ss_mpu_rgs[] = {
	{ 0,           APPS_S_DOMAIN },
	{ 1,           APPS_S_DOMAIN },
	{ 2,           APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
	{ 6,           APPS_S_DOMAIN },
	{ 7,           APPS_S_DOMAIN },
	{ 9,           APPS_S_DOMAIN },
	{ 10,          APPS_S_DOMAIN },
	{ 11,          APPS_S_DOMAIN },
	{ 12,          APPS_S_DOMAIN },
	{ 13,          APPS_S_DOMAIN },
	{ 14,          APPS_S_DOMAIN },
	{ 15,          APPS_S_DOMAIN },
	{ 17,          APPS_S_DOMAIN },
	{ 20,          APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
	{ 24,          APPS_S_DOMAIN },
	{ 25,          APPS_S_DOMAIN },
	{ 29,          APPS_S_DOMAIN },
	{ 30,          APPS_S_DOMAIN },
	{ 31,          APPS_S_DOMAIN },
	{ 32,          APPS_S_DOMAIN },
	{ 33,          APPS_S_DOMAIN },
	{ 40,          APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
	{ 41,          APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
	{ 42,          APPS_S_DOMAIN },
	{ 43,          APPS_S_DOMAIN },
};

/* MDSS_0_MDSS APU - Display subsystem protection
 * RG0 and RG3 are assigned to TZ (APPS_S_DOMAIN)
 */
struct rg_domain_ownership mdss_0_mdss_apu_rgs[] = {
	{ 0,           APPS_S_DOMAIN },
	{ 3,           APPS_S_DOMAIN },
	{ XPU_UMR_RG,  APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
};

/* MDSS_1_MDSS APU - Display subsystem protection
 * RG0 and RG3 are assigned to TZ (APPS_S_DOMAIN)
 */
struct rg_domain_ownership mdss_1_mdss_apu_rgs[] = {
	{ 0,           APPS_S_DOMAIN },
	{ 3,           APPS_S_DOMAIN },
	{ XPU_UMR_RG,  APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
};

/** For RGs 24, 25 and 29, start and end address are substracted with
  *       Base address 0x0b000000 as per policy.
  * RG 24, start = 0xc200000, end = 0xc210000
  * RG 25, start = 0xc310000, end = 0xc3f1000
  * RG 29, start = 0xc400000, end = 0xec00000
  */
struct rg_partition_range aoss_cnoc_mpu_rg_addr[] = {
	{ 10,          0x0C266000 & 0xffffffffL,  0x0C270000 & 0xffffffffL },
	{ 16,          0xFFFFFFFF & 0xffffffffL,  0xFFFFFFFF & 0xffffffffL },
	{ 18,          0x0C272000 & 0xffffffffL,  0x0C273000 & 0xffffffffL },
	{ 19,          0x0C240000 & 0xffffffffL,  0x0C251000 & 0xffffffffL },
	{ 21,          0x0C263000 & 0xffffffffL,  0x0C264000 & 0xffffffffL },
	{ 22,          0x0C265000 & 0xffffffffL,  0x0C266000 & 0xffffffffL },
	{ 23,          0x0C251000 & 0xffffffffL,  0x0C253000 & 0xffffffffL },
	{ 24,          0x0C200000 & 0xffffffffL,  0x0C210000 & 0xffffffffL },
};

struct rg_domain_ownership aoss_cnoc_mpu_rgs[] = {
	{ 10,          APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
	{ 16,          APPS_S_DOMAIN },
	{ 18,          APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
	{ 19,          APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
	{ 21,          APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
	{ 22,          APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
	{ 23,          APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
	{ 24,          APPS_S_DOMAIN,  APPS_NS_DOMAIN,  APPS_NS_DOMAIN },
};

struct xpu_instance msm_xpu_cfg[] = {
	{
		0x09230000,
		ARRAY_SIZE(llcc_mpu_rgs),
		llcc_mpu_rgs,
		ARRAY_SIZE(llcc_mpu_rg_addr),
		llcc_mpu_rg_addr,
		XPU_TYPE_LLCC_BROADCAST_MPU,
		XPU_PROTECTION_STATIC,
	},
	{
		0x0933E000,
		ARRAY_SIZE(llcc_mpu_rgs),
		llcc_mpu_rgs,
		ARRAY_SIZE(llcc_mpu_rg_addr),
		llcc_mpu_rg_addr,
		XPU_TYPE_LLCC_BROADCAST_MPU,
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
		ARRAY_SIZE(cnoc_ss_mpu_rgs),
		cnoc_ss_mpu_rgs,
		ARRAY_SIZE(cnoc_ss_mpu_rg_addr),
		cnoc_ss_mpu_rg_addr,
		XPU_TYPE_CNOC2_SS_MPU,
		XPU_PROTECTION_STATIC,
	},
	{
		0x0EFF0000,
		ARRAY_SIZE(aoss_cnoc_mpu_rgs),
		aoss_cnoc_mpu_rgs,
		ARRAY_SIZE(aoss_cnoc_mpu_rg_addr),
		aoss_cnoc_mpu_rg_addr,
		XPU_TYPE_AOSS_CNOC_MPU,
		XPU_PROTECTION_STATIC,
	},
	{
		0x0AEC8000,
		ARRAY_SIZE(mdss_0_mdss_apu_rgs),
		mdss_0_mdss_apu_rgs,
		0,
		NULL,
		XPU_TYPE_MDSS_0_MDSS_APU,
		XPU_PROTECTION_STATIC,
	},
	{
		0x00616000,
		ARRAY_SIZE(ramblur_pimem_mpu_rgs),
		ramblur_pimem_mpu_rgs,
		ARRAY_SIZE(ramblur_pimem_mpu_rg_addr),
		ramblur_pimem_mpu_rg_addr,
		XPU_TYPE_AOSS_CNOC_MPU,
		XPU_PROTECTION_STATIC,
	},

};
const uint32_t msm_xpu_cfg_count = ARRAY_SIZE(msm_xpu_cfg);

struct mpu_ranges msm_mpu_ranges[] = { };
const uint32_t msm_mpu_ranges_count = ARRAY_SIZE(msm_mpu_ranges);
