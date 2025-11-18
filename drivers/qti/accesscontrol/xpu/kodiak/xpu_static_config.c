/*
 * Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <platform_def.h>
#include <xpu_target_info.h>
#include <xpu3.h>

#include <lib/utils_def.h>

#define ANOC2_STATIC_REGION        3
#define MSS_Q6_STATIC_REGION       17

/*
 * RG 20-24 are not added as qc_sec assign them to modem
 */
RGDomainOwnershipType llcc_mpu_rgs[] = {
	{ 0, APPS_S_DOMAIN },
};

RGPrtitionRangeType llcc_mpu_rg_addr[] = {
	{
		0,
		BL31_BASE & 0xfffffffful,
		(BL31_BASE + BL31_SIZE) & 0xfffffffful,
	},
};

RGDomainOwnershipType mss_q6_mpu_rgs[MSS_Q6_STATIC_REGION + 1 +
				     NUM_MODEM_MPU_PARTITIONS] = {
	{ 0,  MSA_DOMAIN },
	{ 1,  MSA_DOMAIN },
	{ 2,  MSA_DOMAIN },
	{ 3,  MSA_DOMAIN },
	{ 4,  MSA_DOMAIN },
	{ 5,  MSA_DOMAIN },
	{ 6,  MSA_DOMAIN },
	{ 7,  MSA_DOMAIN },
	{ 8,  MSA_DOMAIN },
	{ 9,  MSA_DOMAIN },
	{ 10, MSA_DOMAIN },
	{ 11, MSA_DOMAIN },
	{ 12, MSA_DOMAIN },
	{ 13, MSA_DOMAIN },
	{ 14, MSA_DOMAIN },
	{ 15, MSA_DOMAIN },
	{ 16, MSA_DOMAIN },
	{ XPU_UMR_RG, APPS_NS_DOMAIN },
};

RGPrtitionRangeType mss_q6_mpu_rg_addr[MSS_Q6_STATIC_REGION +
				       NUM_MODEM_MPU_PARTITIONS] = {
	{ 0,  0x00008000, 0x007c0000 },
	{ 1,  0x007e0000, 0x00940000 },
	{ 2,  0x00984000, 0x01c00000 },
	{ 3,  0x01dc0000, 0x02000000 },
	{ 4,  0x04000000, 0x06002000 },
	{ 5,  0x06003000, 0x08400000 },
	{ 6,  0x09000000, 0x09800000 },
	{ 7,  0x0b000000, 0x0f00a000 },
	{ 8,  0x0f16d000, 0x0f177000 },
	{ 9,  0x0f178000, 0x0f181000 },
	{ 10, 0x0f185000, 0x0f18b000 },
	{ 11, 0x16000000, 0x17000000 },
	{ 12, 0x146a8000, 0x146ab000 },
	{ 13, 0x80900000, 0x80b00000 },
	{ 14, 0x80860000, 0x80880000 },
	{ 15, 0x146a5000, 0x146a6000 },
	{ 16, 0xffffffff, 0xffffffff },
};

RGDomainOwnershipType anoc2_mpu_rgs[ANOC2_STATIC_REGION + 1 +
				    NUM_MODEM_MPU_PARTITIONS] = {
	{ 0, MSA_DOMAIN },
	{ 6, MSA_DOMAIN },
	{ 7, MSA_DOMAIN },
	{ XPU_UMR_RG, APPS_NS_DOMAIN },
};

RGPrtitionRangeType anoc2_mpu_rg_addr[ANOC2_STATIC_REGION +
				      NUM_MODEM_MPU_PARTITIONS] = {
	{ 0, 0x01e00000, 0x01f00000 },
	{ 6, 0x80900000, 0x80b00000 },
	{ 7, 0x80860000, 0x80880000 },
};

RGDomainOwnershipType gemnoc_cnoc_mpu_rgs[] = {
	{ 0,  APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 1,  APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 2,  APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 3,  MSA_DOMAIN },
	{ 4,  APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 5,  APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 6,  APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 7,  APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 8,  APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 9,  APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 10, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 11, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 12, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 13, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 14, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 15, MSA_DOMAIN },
	{ 16, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 17, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 18, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 19, APPS_S_DOMAIN,  APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 23, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN },
	{ 24, APPS_S_DOMAIN, MSA_DOMAIN, MSA_DOMAIN },
	{ 25, APPS_S_DOMAIN, MSA_DOMAIN, MSA_DOMAIN },
	{ 26, APPS_S_DOMAIN },
	{ 27, APPS_S_DOMAIN, 0, APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 28, APPS_S_DOMAIN, 0, APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 29, APPS_S_DOMAIN },
	{ 30, APPS_S_DOMAIN },
	{ 31, APPS_S_DOMAIN },
	{ 32, APPS_S_DOMAIN },
	{ 33, APPS_S_DOMAIN },
	{ 34, APPS_S_DOMAIN },
	{ 35, APPS_S_DOMAIN },
	{ 36, APPS_S_DOMAIN },
	{ 37, APPS_S_DOMAIN },
	{ 38, APPS_S_DOMAIN },
	{ 39, APPS_S_DOMAIN },
	{ XPU_UMR_RG, APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
};

RGPrtitionRangeType gemnoc_cnoc_mpu_rg_addr[] = {
	{ 0,  0x0080000 & 0xffffffffL, 0x0500000 & 0xffffffffL },
	{ 1,  0x0c310000 & 0xffffffffL, 0x0c3f1000 & 0xffffffffL },
	{ 2,  0x00800000 & 0xffffffffL, 0x00b00000 & 0xffffffffL },
	{ 3,  0x010d2000 & 0xffffffffL, 0x010d3000 & 0xffffffffL },
	{ 4,  0x00780000 & 0xffffffffL, 0x007a0000 & 0xffffffffL },
	{ 5,  0x09000000 & 0xffffffffL, 0x09800000 & 0xffffffffL },
	{ 6,  0x0c200000 & 0xffffffffL, 0x0c290000 & 0xffffffffL },
	{ 7,  0x01520000 & 0xffffffffL, 0x01528000 & 0xffffffffL },
	{ 8,  0x01680000 & 0xffffffffL, 0x016b2000 & 0xffffffffL },
	{ 9,  0x016e0000 & 0xffffffffL, 0x01740000 & 0xffffffffL },
	{ 10, 0x01c00000 & 0xffffffffL, 0x01c20000 & 0xffffffffL },
	{ 11, 0x01e00000 & 0xffffffffL, 0x02000000 & 0xffffffffL },
	{ 12, 0x0eff03fc & 0xffffffffL, 0x0f400000 & 0xffffffffL },
	{ 13, 0x06000000 & 0xffffffffL, 0x08000000 & 0xffffffffL },
	{ 14, 0x0c400000 & 0xffffffffL, 0x0ec00000 & 0xffffffffL },
	{ 15, 0x010c3000 & 0xffffffffL, 0x010c4000 & 0xffffffffL },
	{ 16, 0x0b2c0000 & 0xffffffffL, 0x0b2e0000 & 0xffffffffL },
	{ 17, 0x0b4c0000 & 0xffffffffL, 0x0b4d0000 & 0xffffffffL },
	{ 18, 0x0bbf0000 & 0xffffffffL, 0x0bbf2000 & 0xffffffffL },
	{ 19, 0x0c2a0000 & 0xffffffffL, 0x0c300000 & 0xffffffffL },
	{ 23, 0x0b600000 & 0xffffffffL, 0x0b7f0000 & 0xffffffffL },
	{ 24, 0x010ca000 & 0xffffffffL, 0x010cc000 & 0xffffffffL },
	{ 25, 0x01530000 & 0xffffffffL, 0x01533000 & 0xffffffffL },
	{ 26, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 27, 0x00634000 & 0xffffffffL, 0x00635000 & 0xffffffffL },
	{ 28, 0x00636000 & 0xffffffffL, 0x00637000 & 0xffffffffL },
	{ 29, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 30, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 31, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 32, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 33, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 34, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 35, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 36, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 37, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 38, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 39, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
};

RGPrtitionRangeType cnoc2_ss_mpu_rg_addr[] = {
	{ 0,  0x01680000 & 0xffffffffL, 0x01686000 & 0xffffffffL },
	{ 1,  0x01686000 & 0xffffffffL, 0x01688000 & 0xffffffffL },
	{ 2,  0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 3,  0x0168b000 & 0xffffffffL, 0x0168e000 & 0xffffffffL },
	{ 4,  0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 5,  0x0168e000 & 0xffffffffL, 0x01696000 & 0xffffffffL },
	{ 6,  0x01500000 & 0xffffffffL, 0x01506000 & 0xffffffffL },
	{ 7,  0x01510000 & 0xffffffffL, 0x0151d000 & 0xffffffffL },
	{ 8,  0x016e0000 & 0xffffffffL, 0x016e3000 & 0xffffffffL },
	{ 9,  0x016f2000 & 0xffffffffL, 0x01706000 & 0xffffffffL },
	{ 10, 0x016e8000 & 0xffffffffL, 0x016e9000 & 0xffffffffL },
	{ 11, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 12, 0x0170b000 & 0xffffffffL, 0x01710000 & 0xffffffffL },
	{ 13, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 15, 0x0a0cf000 & 0xffffffffL, 0x0a0d0000 & 0xffffffffL },
	{ 16, 0x01740000 & 0xffffffffL, 0x0174d000 & 0xffffffffL },
	{ 17, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 19, 0x06858000 & 0xffffffffL, 0x06859000 & 0xffffffffL },
	{ 20, 0x00100000 & 0xffffffffL, 0x00500000 & 0xffffffffL },
	{ 21, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 22, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 23, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 24, 0x01720000 & 0xffffffffL, 0x01731000 & 0xffffffffL },
	{ 25, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 26, 0x01758000 & 0xffffffffL, 0x01760000 & 0xffffffffL },
	{ 27, 0x016e6000 & 0xffffffffL, 0x016e7000 & 0xffffffffL },
	{ 28, 0x088e2000 & 0xffffffffL, 0x088e3000 & 0xffffffffL },
	{ 29, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 30, 0x000b0000 & 0xffffffffL, 0x000c0000 & 0xffffffffL },
	{ 31, 0x010d2000 & 0xffffffffL, 0x010d3000 & 0xffffffffL },
	{ 32, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 33, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 34, 0x01e00000 & 0xffffffffL, 0x02000000 & 0xffffffffL },
	{ 35, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 36, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 37, 0x0c310000 & 0xffffffffL, 0x0f400000 & 0xffffffffL },
	{ 38, 0x08b1c000 & 0xffffffffL, 0x08b1f000 & 0xffffffffL },
	{ 39, 0x016a0000 & 0xffffffffL, 0x016b2000 & 0xffffffffL },
	{ 40, 0x01522000 & 0xffffffffL, 0x01528000 & 0xffffffffL },
	{ 41, 0x0152c000 & 0xffffffffL, 0x01533000 & 0xffffffffL },
	{ 42, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 43, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 44, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 45, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 46, 0x00634000 & 0xffffffffL, 0x00635000 & 0xffffffffL },
	{ 47, 0x00636000 & 0xffffffffL, 0x00637000 & 0xffffffffL },
};

RGDomainOwnershipType cnoc2_ss_mpu_rgs[] = {
	{ 0,  APPS_S_DOMAIN },
	{ 1,  MSA_DOMAIN },
	{ 2,  APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      MSA_DOMAIN | APPS_NS_DOMAIN },
	{ 3,  MSA_DOMAIN },
	{ 4,  APPS_S_DOMAIN },
	{ 5,  APPS_S_DOMAIN },
	{ 6,  APPS_S_DOMAIN },
	{ 7,  APPS_S_DOMAIN },
	{ 8,  APPS_S_DOMAIN },
	{ 9,  APPS_S_DOMAIN },
	{ 10, APPS_S_DOMAIN },
	{ 11, APPS_S_DOMAIN },
	{ 12, APPS_S_DOMAIN },
	{ 13, APPS_S_DOMAIN },
	{ 15, APPS_S_DOMAIN },
	{ 16, APPS_S_DOMAIN },
	{ 17, MSA_DOMAIN },
	{ 19, APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 20, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 21, APPS_S_DOMAIN },
	{ 22, APPS_S_DOMAIN },
	{ 23, APPS_S_DOMAIN },
	{ 24, APPS_S_DOMAIN },
	{ 25, APPS_S_DOMAIN },
	{ 26, APPS_S_DOMAIN },
	{ 27, APPS_S_DOMAIN },
	{ 28, APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_S_DOMAIN },
	{ 29, APPS_S_DOMAIN },
	{ 30, MSA_DOMAIN },
	{ 31, MSA_DOMAIN },
	{ 32, APPS_S_DOMAIN },
	{ 33, APPS_S_DOMAIN },
	{ 34, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 35, APPS_S_DOMAIN },
	{ 36, APPS_S_DOMAIN },
	{ 37, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 38, APPS_S_DOMAIN },
	{ 39, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 40, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 41, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 42, APPS_S_DOMAIN },
	{ 43, APPS_S_DOMAIN },
	{ 44, APPS_S_DOMAIN },
	{ 45, APPS_S_DOMAIN },
	{ 46, APPS_S_DOMAIN, 0, APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 47, APPS_S_DOMAIN, 0, APPS_NS_DOMAIN | MSA_DOMAIN },
};

static RGDomainOwnershipType wpss_mpu_rgs[] = {
	{ 0,  APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 1,  APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 2,  APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 3,  APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 4,  APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 5,  APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 6,  APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 7,  APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 8,  APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 9,  APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 10, APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 11, APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 12, APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 13, APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 14, APPS_S_DOMAIN, APPS_NS_DOMAIN },
	{ 15, APPS_S_DOMAIN },
	{ 16, APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 17, APPS_S_DOMAIN, APPS_NS_DOMAIN, APPS_NS_DOMAIN },
	{ 18, APPS_S_DOMAIN, APPS_NS_DOMAIN },
	{ 19, APPS_S_DOMAIN, APPS_NS_DOMAIN },
	{ 20, APPS_S_DOMAIN },
	{ 21, APPS_S_DOMAIN },
	{ 22, APPS_S_DOMAIN },
	{ 23, APPS_S_DOMAIN },
	{ XPU_UMR_RG, APPS_S_DOMAIN },
};

static RGPrtitionRangeType wpss_mpu_addr[] = {
	{ 0,  0x80c00000 & 0xffffffffL, 0x81800000 & 0xffffffffL },
	{ 1,  0x60000000 & 0xffffffffL, 0x64000000 & 0xffffffffL },
	{ 2,  0x16000000 & 0xffffffffL, 0x17000000 & 0xffffffffL },
	{ 3,  0x14680000 & 0xffffffffL, 0x146ab000 & 0xffffffffL },
	{ 4,  0x0b2f0000 & 0xffffffffL, 0x0f400000 & 0xffffffffL },
	{ 5,  0x09200000 & 0xffffffffL, 0x09658000 & 0xffffffffL },
	{ 6,  0x091cc000 & 0xffffffffL, 0x091e3000 & 0xffffffffL },
	{ 7,  0x09080000 & 0xffffffffL, 0x09081000 & 0xffffffffL },
	{ 8,  0x00634000 & 0xffffffffL, 0x00635000 & 0xffffffffL },
	{ 9,  0x06000000 & 0xffffffffL, 0x08000000 & 0xffffffffL },
	{ 10, 0x01c00000 & 0xffffffffL, 0x01ff0000 & 0xffffffffL },
	{ 11, 0x00636000 & 0xffffffffL, 0x00637000 & 0xffffffffL },
	{ 12, 0x010dc000 & 0xffffffffL, 0x010dd000 & 0xffffffffL },
	{ 13, 0x00100000 & 0xffffffffL, 0x004d9000 & 0xffffffffL },
	{ 14, 0x004fc000 & 0xffffffffL, 0x004fd000 & 0xffffffffL },
	{ 15, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 16, 0x09ae0000 & 0xffffffffL, 0x09c70000 & 0xffffffffL },
	{ 17, 0x80900000 & 0xffffffffL, 0x80a0d000 & 0xffffffffL },
	{ 18, 0x80aff000 & 0xffffffffL, 0x80b00000 & 0xffffffffL },
	{ 19, 0x80860000 & 0xffffffffL, 0x80880000 & 0xffffffffL },
	{ 20, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 21, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 22, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 23, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
};

RGDomainOwnershipType aoss_cnoc_mpu_rgs[] = {
	{ 24, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 25, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
	{ 26, NO_DOMAIN, NO_DOMAIN, NO_DOMAIN },
	{ 27, NO_DOMAIN, NO_DOMAIN, NO_DOMAIN },
	{ 29, APPS_S_DOMAIN, APPS_NS_DOMAIN | MSA_DOMAIN,
	      APPS_NS_DOMAIN | MSA_DOMAIN },
};

/*
 * For RGs 24, 25 and 29, start and end address are subtracted
 * with base address 0x0b000000 as per policy:
 *  - RG 24, start = 0xc200000, end = 0xc210000
 *  - RG 25, start = 0xc310000, end = 0xc3f1000
 *  - RG 29, start = 0xc400000, end = 0xec00000
 */
RGPrtitionRangeType aoss_cnoc_mpu_rg_addr[] = {
	{ 24, 0x01200000 & 0xffffffffL, 0x01210000 & 0xffffffffL },
	{ 25, 0x01310000 & 0xffffffffL, 0x013f1000 & 0xffffffffL },
	{ 26, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 27, 0xffffffff & 0xffffffffL, 0xffffffff & 0xffffffffL },
	{ 29, 0x01400000 & 0xffffffffL, 0x03c00000 & 0xffffffffL },
};

RGDomainOwnershipType mss_nav_mpu_rgs[NUM_MSS_NAV_MPU_PARTITIONS + 1] = {
	{ XPU_UMR_RG, APPS_NS_DOMAIN },
};

RGPrtitionRangeType mss_nav_mpu_rg_addr[NUM_MSS_NAV_MPU_PARTITIONS] = {
};

RGDomainOwnershipType anoc1_mpu_rgs[NUM_MSS_NAV_MPU_PARTITIONS + 1] = {
	{ XPU_UMR_RG, APPS_NS_DOMAIN },
};

RGPrtitionRangeType anoc1_mpu_rg_addr[NUM_MSS_NAV_MPU_PARTITIONS] = {
};

RGDomainOwnershipType modem_ms_mpu_rgs[NUM_MSS_NAV_MPU_PARTITIONS + 1] = {
	{ XPU_UMR_RG, APPS_NS_DOMAIN },
};

RGPrtitionRangeType modem_ms_mpu_rg_addr[NUM_MSS_NAV_MPU_PARTITIONS] = {
};

xpuInstanceType msm_xpu_cfg[] = {
	{
		0x0922e000,
		ARRAY_SIZE(llcc_mpu_rgs),
		llcc_mpu_rgs,
		ARRAY_SIZE(llcc_mpu_rg_addr),
		llcc_mpu_rg_addr,
		XPU_TYPE_LLCC_BROADCAST_MPU,
		1,
	},
	{
		0x092ae000,
		ARRAY_SIZE(llcc_mpu_rgs),
		llcc_mpu_rgs,
		ARRAY_SIZE(llcc_mpu_rg_addr),
		llcc_mpu_rg_addr,
		XPU_TYPE_LLCC_BROADCAST_MPU,
		1,
	},
	{
		0x016a8000,
		ANOC2_STATIC_REGION + 1,
		anoc2_mpu_rgs,
		ANOC2_STATIC_REGION,
		anoc2_mpu_rg_addr,
		XPU_TYPE_ANOC2_MPU,
		1,
	},
	{
		0x091fc000,
		MSS_Q6_STATIC_REGION + 1,
		mss_q6_mpu_rgs,
		MSS_Q6_STATIC_REGION,
		mss_q6_mpu_rg_addr,
		XPU_TYPE_MSS_Q6_MPU,
		1,
	},
	{
		0x0152c000,
		ARRAY_SIZE(gemnoc_cnoc_mpu_rgs),
		gemnoc_cnoc_mpu_rgs,
		ARRAY_SIZE(gemnoc_cnoc_mpu_rg_addr),
		gemnoc_cnoc_mpu_rg_addr,
		XPU_TYPE_CNOC_GEMNOC_MPU,
		1,
	},
	{
		0x01530000,
		ARRAY_SIZE(cnoc2_ss_mpu_rgs),
		cnoc2_ss_mpu_rgs,
		ARRAY_SIZE(cnoc2_ss_mpu_rg_addr),
		cnoc2_ss_mpu_rg_addr,
		XPU_TYPE_CNOC2_SS_MPU,
		1,
	},
	{
		0x08b14000,
		ARRAY_SIZE(wpss_mpu_rgs),
		wpss_mpu_rgs,
		ARRAY_SIZE(wpss_mpu_addr),
		wpss_mpu_addr,
		XPU_TYPE_WPSS_MPU,
		1,
	},
	{
		0x0eff0000,
		ARRAY_SIZE(aoss_cnoc_mpu_rgs),
		aoss_cnoc_mpu_rgs,
		ARRAY_SIZE(aoss_cnoc_mpu_rg_addr),
		aoss_cnoc_mpu_rg_addr,
		XPU_TYPE_AOSS_CNOC_MPU,
		1,
	},
};

const uint32_t msm_xpu_cfg_count = ARRAY_SIZE(msm_xpu_cfg);

xpuInstanceType modem_mpus[] = {
	{
		0x016a8000,
		ARRAY_SIZE(anoc2_mpu_rgs),
		anoc2_mpu_rgs,
		ARRAY_SIZE(anoc2_mpu_rg_addr),
		anoc2_mpu_rg_addr,
		XPU_TYPE_ANOC2_MPU,
		0,
	},
	{
		0x091fc000,
		ARRAY_SIZE(mss_q6_mpu_rgs),
		mss_q6_mpu_rgs,
		ARRAY_SIZE(mss_q6_mpu_rg_addr),
		mss_q6_mpu_rg_addr,
		XPU_TYPE_MSS_Q6_MPU,
		0,
	},
};

xpuInstanceType mss_nav_mpus[] = {
	{
		0x016a0000,
		ARRAY_SIZE(mss_nav_mpu_rgs),
		mss_nav_mpu_rgs,
		ARRAY_SIZE(mss_nav_mpu_rg_addr),
		mss_nav_mpu_rg_addr,
		XPU_TYPE_MSS_NAV_MPU,
		0,
	},
	{
		0x016b0000,
		ARRAY_SIZE(anoc1_mpu_rgs),
		anoc1_mpu_rgs,
		ARRAY_SIZE(anoc1_mpu_rg_addr),
		anoc1_mpu_rg_addr,
		XPU_TYPE_ANOC1_MPU,
		0,
	},
	{
		0x091fe000,
		ARRAY_SIZE(modem_ms_mpu_rgs),
		modem_ms_mpu_rgs,
		ARRAY_SIZE(modem_ms_mpu_rg_addr),
		modem_ms_mpu_rg_addr,
		XPU_TYPE_MSS_MPU,
		0,
	},
};

mpuRangesType msm_mpu_ranges[] = {
	{
		DEVICE_MODEM,
		ARRAY_SIZE(modem_mpus),
		NUM_MODEM_MPU_PARTITIONS,
		modem_mpus,
	},
	{
		DEVICE_MSS_NAV,
		ARRAY_SIZE(mss_nav_mpus),
		NUM_MSS_NAV_MPU_PARTITIONS,
		mss_nav_mpus,
	},
};

const uint32_t msm_mpu_ranges_count = ARRAY_SIZE(msm_mpu_ranges);

