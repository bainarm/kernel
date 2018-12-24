/*
 * Copyright (C) 2017 Fuzhou Rockchip Electronics Co., Ltd.
 *
 * Copyright (C) 2012-2014 Intel Mobile Communications GmbH
 *
 * Copyright (C) 2008 Texas Instruments.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 */

#include <linux/i2c.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <media/v4l2-subdev.h>
#include <media/videobuf-core.h>
#include <linux/slab.h>
#include <media/v4l2-controls_rockchip.h>
#include "aptina_camera_module.h"

#define AR0144CS_DRIVER_NAME "ar0144cs"

#define AR0144CS_PID_ADDR 0x3000
#define AR0144CS_PID_MAGIC 0x0356
#define AR0144CS_EXT_CLK 24000000

#define AR0144CS_AEC_PK_AGAIN_REG 0x3060 /* gain Bit 0-5 */
#define AR0144CS_FETCH_AGAIN(VAL) (VAL & 0x007f)

#define AR0144CS_AEC_PK_DGAIN_REG 0x305E /* gain Bit 0-5 */
#define AR0144CS_FETCH_DGAIN(VAL) (VAL & 0x07FF)

#define AR0144CS_AEC_PK_LONG_EXPO_REG 0x3012 /* Exposure Bits 0-15 */
#define AR0144CS_FETCH_BYTE_EXP(VAL) (VAL & 0xFFFF) /* 16Bits */
#define AR0144CS_AFPS_ENABLE_REG 0x30ce
#define AR0144CS_AFPS_ENABLE_VAL 0x0020

#define AR0144CS_TIMING_VTS_REG 0x300a
#define AR0144CS_TIMING_HTS_REG 0x300c
#define AR0144CS_INTEGRATION_TIME_MARGIN 1
#define AR0144CS_FINE_INTG_TIME_MIN 0
#define AR0144CS_FINE_INTG_TIME_MAX_MARGIN 0
#define AR0144CS_COARSE_INTG_TIME_MIN 1
#define AR0144CS_COARSE_INTG_TIME_MAX_MARGIN 0
#define AR0144CS_HORIZONTAL_START_REG 0x3004
#define AR0144CS_HORIZONTAL_END_REG 0x3008
#define AR0144CS_VERTICAL_START_REG 0x3002
#define AR0144CS_VERTICAL_END_REG 0x3006
#define AR0144CS_READOUT_FLIP_MIRROR_REG 0x3040
//#define dual_sync

static struct aptina_camera_module ar0144cs;
static struct aptina_camera_module_custom_config ar0144cs_custom_config;

/* ======================================================================== */

static struct aptina_camera_module_reg ar0144cs_init_tab_1280_800_25fps[] = {
/*STATE = Master Clock, 49200000*/
#if 0
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F4C, 0x4B3F},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F4C, 0x003F},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F4E, 0x5718},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F4E, 0x0018},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F50, 0x401F},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F50, 0x17DF},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30B0, 0x0028},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3ED6, 0x3CB5},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3ED8, 0x8765},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EDA, 0x8888},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EDC, 0x97FF},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EF8, 0x6522},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EFA, 0x2222},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EFC, 0x6666},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F00, 0xAA05},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EE2, 0x180E},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EE4, 0x0808},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EEA, 0x2A09},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3060, 0x000D},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3092, 0x00CF},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3268, 0x0030},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3786, 0x0006},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F4A, 0x0F70},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x306E, 0x4810},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3064, 0x1802},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EF6, 0x804D},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3180, 0xC08F},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30BA, 0x7623},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3176, 0x0480},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3178, 0x0480},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x317A, 0x0480},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x317C, 0x0480},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x302A, 0x0006},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x302C, 0x0002},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x302E, 0x0009},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3030, 0x00A0},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3036, 0x000C},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30B0, 0x0028},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3038, 0x0001},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31AE, 0x0201},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31AC, 0x0C0C},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B0, 0x002D},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B2, 0x001B},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B4, 0x1565},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B6, 0x110D},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B8, 0x2047},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31BA, 0x0105},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31BC, 0x0004},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3002, 0x0000},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3004, 0x0004},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3006, 0x031F},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3008, 0x0503},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x300A, 0x03B5},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x300C, 0x05D0},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3012, 0x03B4},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x306E, 0x9010},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30A2, 0x0001},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30A6, 0x0001},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3040, 0x0000},
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31D0, 0x0001},
//#else
//{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x301A, 0x00D9}, // RESET_REGISTER
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F4C, 0x4B3F}, // PIX_DEF_1D_DDC_LO_DEF
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F4C, 0x003F}, // PIX_DEF_1D_DDC_LO_DEF
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F4E, 0x5718}, // PIX_DEF_1D_DDC_HI_DEF
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F4E, 0x0018}, // PIX_DEF_1D_DDC_HI_DEF
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F50, 0x401F}, // PIX_DEF_1D_DDC_EDGE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F50, 0x17DF}, // PIX_DEF_1D_DDC_EDGE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30B0, 0x0028}, // DIGITAL_TEST
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3ED6, 0x3CB5}, // DAC_LD_10_11
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3ED8, 0x8765}, // DAC_LD_12_13
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EDA, 0x8888}, // DAC_LD_14_15
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EDC, 0x97FF}, // DAC_LD_16_17
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EF8, 0x6522}, // DAC_LD_44_45
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EFA, 0x2222}, // DAC_LD_46_47
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EFC, 0x6666}, // DAC_LD_48_49
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F00, 0xAA05}, // DAC_LD_52_53
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EE2, 0x180E}, // DAC_LD_22_23
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EE4, 0x0808}, // DAC_LD_24_25
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EEA, 0x2A09}, // DAC_LD_30_31
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3060, 0x000D}, // ANALOG_GAIN
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30FE, 0x00A8}, // NOISE_PEDESTAL
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3092, 0x00CF}, // ROW_NOISE_CONTROL
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3268, 0x0030}, // SEQUENCER_CONTROL
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3786, 0x0006}, // DIGITAL_CTRL_1
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F4A, 0x0F70}, // DELTA_DK_PIX_THRES
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x306E, 0x4810}, // DATAPATH_SELECT
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3064, 0x1802}, // SMIA_TEST
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EF6, 0x804D}, // DAC_LD_42_43
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3180, 0xC08F}, // DELTA_DK_CONTROL
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30BA, 0x7623}, // DIGITAL_CTRL
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3176, 0x0480}, // DELTA_DK_ADJUST_GREENR
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3178, 0x0480}, // DELTA_DK_ADJUST_RED
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x317A, 0x0480}, // DELTA_DK_ADJUST_BLUE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x317C, 0x0480}, // DELTA_DK_ADJUST_GREENB
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31AE, 0x0201}, // SERIAL_FORMAT
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x301A, 0x2058}, // RESET_REGISTER
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3030, 0x0096}, // PLL_MULTIPLIER
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x302E, 0x0006}, // PRE_PLL_CLK_DIV
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x302C, 0x0002}, // VT_SYS_CLK_DIV
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x302A, 0x0005}, // VT_PIX_CLK_DIV
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3038, 0x0001}, // OP_SYS_CLK_DIV
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3036, 0x000A}, // OP_PIX_CLK_DIV
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B0, 0x007A}, // FRAME_PREAMBLE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B2, 0x0045}, // LINE_PREAMBLE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B4, 0x4787}, // MIPI_TIMING_0
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B6, 0x21D6}, // MIPI_TIMING_1
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B8, 0x404A}, // MIPI_TIMING_2
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31BA, 0x0289}, // MIPI_TIMING_3
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31BC, 0x0007}, // MIPI_TIMING_4
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3354, 0x002B}, // MIPI_CNTRL
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31D0, 0x0001}, // COMPANDING
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31AC, 0x0A0A}, // DATA_FORMAT_BITS
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3004, 0x0004}, // X_ADDR_START
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3008, 0x0503}, // X_ADDR_END
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3002, 0x0000}, // Y_ADDR_START
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3006, 0x031F}, // Y_ADDR_END
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3064, 0x1802}, // SMIA_TEST
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3064, 0x1802}, // SMIA_TEST
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30A2, 0x0001}, // X_ODD_INC
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30A6, 0x0001}, // Y_ODD_INC
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x300A, 0x033B}, // FRAME_LENGTH_LINES
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x300C, 0x05D0}, // LINE_LENGTH_PCK
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3012, 0x002E}, // COARSE_INTEGRATION_TIME
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x301E, 0x00A8}, // DATA_PEDESTAL
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3060, 0x0000}, // ANALOG_GAIN
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x301A, 0x2058}, // RESET_REGISTER
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30BA, 0x7623}, // DIGITAL_CTRL
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3ED6, 0x3CB5}, // DAC_LD_10_11
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x317C, 0x0480}, // DELTA_DK_ADJUST_GREENB
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x317A, 0x0480}, // DELTA_DK_ADJUST_BLUE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3178, 0x0480}, // DELTA_DK_ADJUST_RED
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3176, 0x0480}, // DELTA_DK_ADJUST_GREENR
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3ED8, 0x8765}, // DAC_LD_12_13
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EDA, 0x8888}, // DAC_LD_14_15
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EDC, 0x97FF}, // DAC_LD_16_17
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EF6, 0x804D}, // DAC_LD_42_43
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3060, 0x000D}, // ANALOG_GAIN
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30B0, 0x0028}, // DIGITAL_TEST
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x301A, 0x205C}, // RESET_REGISTER
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3064, 0x1882}, // SMIA_TEST
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3064, 0x1982}, // SMIA_TEST
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3028, 0x0010}, // ROW_SPEED
//{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x301A, 0x005C}, // RESET_REGISTER
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3030, 0x004D}, // PLL_MULTIPLIER


#endif
#if 0
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x302A, 0x0004}, // VT_PIX_CLK_DIV
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x302C, 0x0002}, // VT_SYS_CLK_DIV
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x302E, 0x0008}, // PRE_PLL_CLK_DIV
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3030, 0x00C6}, // PLL_MULTIPLIER
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3036, 0x0008}, // OP_PIX_CLK_DIV
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3038, 0x0001}, // OP_SYS_CLK_DIV
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30B0, 0x0028}, // DIGITAL_TEST
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B0, 0x0047}, // FRAME_PREAMBLE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B2, 0x0026}, // LINE_PREAMBLE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B4, 0x1C87}, // MIPI_TIMING_0
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B6, 0x2218}, // MIPI_TIMING_1
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B8, 0x404B}, // MIPI_TIMING_2
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31BA, 0x020A}, // MIPI_TIMING_3
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31BC, 0x8008}, // MIPI_TIMING_4
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31AE, 0x0201}, // SERIAL_FORMAT
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3002, 0x0000}, // Y_ADDR_START
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3004, 0x0004}, // X_ADDR_START
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3006, 0x031F}, // Y_ADDR_END
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3008, 0x0503}, // X_ADDR_END
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x300A, 0x033B}, // FRAME_LENGTH_LINES
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x300C, 0x05D0}, // LINE_LENGTH_PCK
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3012, 0x033A}, // COARSE_INTEGRATION_TIME
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31AC, 0x0808}, // DATA_FORMAT_BITS
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x306E, 0x9010}, // DATAPATH_SELECT
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30A2, 0x0001}, // X_ODD_INC
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30A6, 0x0001}, // Y_ODD_INC
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3082, 0x0003}, // OPERATION_MODE_CTRL
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3084, 0x0003}, // OPERATION_MODE_CTRL_CB
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x308C, 0x0028}, // Y_ADDR_START_CB
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x308A, 0x0004}, // X_ADDR_START_CB
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3090, 0x02F7}, // Y_ADDR_END_CB
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x308E, 0x0503}, // X_ADDR_END_CB
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30AA, 0x033A}, // FRAME_LENGTH_LINES_CB
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x303E, 0x05D0}, // LINE_LENGTH_PCK_CB
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3016, 0x0339}, // COARSE_INTEGRATION_TIME_CB
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30AE, 0x0001}, // X_ODD_INC_CB
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30A8, 0x0001}, // Y_ODD_INC_CB
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3040, 0x0000}, // READ_MODE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31D0, 0x0001}, // COMPANDING
//{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x301A, 0x005C}, // RESET_REGISTER

#else
//{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x301A, 0x00D9}, // RESET_REGISTER
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F4C, 0x4B3F}, // PIX_DEF_1D_DDC_LO_DEF
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F4C, 0x003F}, // PIX_DEF_1D_DDC_LO_DEF
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F4E, 0x5718}, // PIX_DEF_1D_DDC_HI_DEF
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F4E, 0x0018}, // PIX_DEF_1D_DDC_HI_DEF
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F50, 0x401F}, // PIX_DEF_1D_DDC_EDGE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F50, 0x17DF}, // PIX_DEF_1D_DDC_EDGE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30B0, 0x0028}, // DIGITAL_TEST
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3ED6, 0x3CB5}, // DAC_LD_10_11
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3ED8, 0x8765}, // DAC_LD_12_13
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EDA, 0x8888}, // DAC_LD_14_15
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EDC, 0x97FF}, // DAC_LD_16_17
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EF8, 0x6522}, // DAC_LD_44_45
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EFA, 0x2222}, // DAC_LD_46_47
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EFC, 0x6666}, // DAC_LD_48_49
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F00, 0xAA05}, // DAC_LD_52_53
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EE2, 0x180E}, // DAC_LD_22_23
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EE4, 0x0808}, // DAC_LD_24_25
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EEA, 0x2A09}, // DAC_LD_30_31
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3060, 0x000D}, // ANALOG_GAIN
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3092, 0x00CF}, // ROW_NOISE_CONTROL
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3268, 0x0030}, // SEQUENCER_CONTROL
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3786, 0x0006}, // DIGITAL_CTRL_1
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3F4A, 0x0F70}, // DELTA_DK_PIX_THRES
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x306E, 0x4810}, // DATAPATH_SELECT
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3064, 0x1802}, // SMIA_TEST
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3EF6, 0x804D}, // DAC_LD_42_43
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3180, 0xC08F}, // DELTA_DK_CONTROL
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30BA, 0x7623}, // DIGITAL_CTRL
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3176, 0x0480}, // DELTA_DK_ADJUST_GREENR
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3178, 0x0480}, // DELTA_DK_ADJUST_RED
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x317A, 0x0480}, // DELTA_DK_ADJUST_BLUE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x317C, 0x0480}, // DELTA_DK_ADJUST_GREENB
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x302A, 0x0006}, // VT_PIX_CLK_DIV
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x302C, 0x0001}, // VT_SYS_CLK_DIV
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x302E, 0x0004}, // PRE_PLL_CLK_DIV
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3030, 0x0042}, // PLL_MULTIPLIER
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3036, 0x000C}, // OP_PIX_CLK_DIV
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3038, 0x0001}, // OP_SYS_CLK_DIV
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30B0, 0x0028}, // DIGITAL_TEST
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31AE, 0x0202}, // SERIAL_FORMAT
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31AC, 0x0C0C}, // DATA_FORMAT_BITS
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B0, 0x0042}, // FRAME_PREAMBLE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B2, 0x002E}, // LINE_PREAMBLE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B4, 0x2633}, // MIPI_TIMING_0
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B6, 0x210E}, // MIPI_TIMING_1
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31B8, 0x20C7}, // MIPI_TIMING_2
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31BA, 0x0105}, // MIPI_TIMING_3
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x31BC, 0x0004}, // MIPI_TIMING_4
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3002, 0x0000}, // Y_ADDR_START
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3004, 0x0004}, // X_ADDR_START
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3006, 0x031F}, // Y_ADDR_END
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3008, 0x0503}, // X_ADDR_END
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x300A, 0x0339}, // FRAME_LENGTH_LINES
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x300C, 0x05D0}, // LINE_LENGTH_PCK
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3012, 0x0330}, // COARSE_INTEGRATION_TIME
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30A2, 0x0001}, // X_ODD_INC
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30A6, 0x0001}, // Y_ODD_INC
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3040, 0x0000}, // READ_MODE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3040, 0x0400}, // READ_MODE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30A8, 0x0003}, // Y_ODD_INC_CB
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3040, 0x0C00}, // READ_MODE
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x30AE, 0x0003}, // X_ODD_INC_CB
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3064, 0x1882}, // SMIA_TEST
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3064, 0x1982}, // SMIA_TEST
{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x3028, 0x0010}, // ROW_SPEED
//{APTINA_CAMERA_MODULE_REG_TYPE_DATA, 0x301A, 0x005C}, // RESET_REGISTER         
#endif
};

/* ======================================================================== */

static struct aptina_camera_module_config ar0144cs_configs[] = {
	{
		.name = "1280x800_25fps",
		.frm_fmt = {
			.width = 1280,
			.height = 800,
			.code = MEDIA_BUS_FMT_SGRBG12_1X12
		},
		.frm_intrvl = {
			.interval = {
				.numerator = 1,
				.denominator = 60
			}
		},
		.auto_exp_enabled = false,
		.auto_gain_enabled = false,
		.auto_wb_enabled = false,
		.reg_table = (void *)ar0144cs_init_tab_1280_800_25fps,
		.reg_table_num_entries =
			ARRAY_SIZE(ar0144cs_init_tab_1280_800_25fps),
		.v_blanking_time_us = 3078,
		.max_exp_gain_h = 16,
		.max_exp_gain_l = 0,
		PLTFRM_CAM_ITF_MIPI_CFG(0, 2, 396, AR0144CS_EXT_CLK)
	}

};

/*--------------------------------------------------------------------------*/

static int ar0144cs_set_flip(struct aptina_camera_module *cam_mod,
	struct pltfrm_camera_module_reg reglist[],
	int len)
{
	int i, value = 0, mode = 0;

	mode = aptina_camera_module_get_flip_mirror(cam_mod);
	aptina_camera_module_pr_debug(cam_mod,
		"mode %d\n", mode);

	if (mode == -1) {
		aptina_camera_module_pr_err(
			cam_mod,
			"dts don't set flip, return!\n");
		return 0;
	}

	if (mode == APTINA_FLIP_BIT_MASK)
		value = 0x8000;
	else if (mode == APTINA_MIRROR_BIT_MASK)
		value = 0x4000;
	else if (mode == (APTINA_FLIP_BIT_MASK |
		APTINA_MIRROR_BIT_MASK))
		value = 0xc000;
	else
		value = 0x0000;

	for (i = 0; i < len; i++)
		if (reglist[i].reg == AR0144CS_READOUT_FLIP_MIRROR_REG)
			reglist[i].val = value;

	return 0;

}

/*--------------------------------------------------------------------------*/

static int ar0144cs_g_vts(struct aptina_camera_module *cam_mod, u32 *vts)
{
	u32 value;
	int ret;

	ret = aptina_camera_module_read_reg_table(
		cam_mod,
		AR0144CS_TIMING_VTS_REG,
		&value);
	if (IS_ERR_VALUE(ret))
		goto err;
	aptina_camera_module_pr_debug(cam_mod, "updated vts = %d,vts_min=%d\n", value, cam_mod->vts_min);
	*vts = value;

	return 0;
err:
	aptina_camera_module_pr_err(cam_mod,
			"failed with error (%d)\n", ret);
	return ret;
}

static int ar0144cs_auto_adjust_fps(struct aptina_camera_module *cam_mod,
	u32 exp_time)
{
	int ret;
	u32 vts;

	if ((exp_time + AR0144CS_COARSE_INTG_TIME_MAX_MARGIN) > cam_mod->vts_min)
		vts = exp_time + AR0144CS_COARSE_INTG_TIME_MAX_MARGIN;
	else
		vts = cam_mod->vts_min;

	ret = aptina_camera_module_write_reg(cam_mod,
		AR0144CS_TIMING_VTS_REG,
		vts & 0xFFFF);

	if (IS_ERR_VALUE(ret)) {
		aptina_camera_module_pr_err(cam_mod, "failed with error (%d)\n", ret);
	} else {
		aptina_camera_module_pr_info(cam_mod, "updated vts = %d,vts_min=%d\n",
			vts, cam_mod->vts_min);
		cam_mod->vts_cur = vts;
	}
	return ret;
}

static int ar0144cs_set_vts(struct aptina_camera_module *cam_mod,
	u32 vts)
{
	int ret = 0;

	if (vts < cam_mod->vts_min)
		return ret;

	ret = aptina_camera_module_write_reg(cam_mod,
		AR0144CS_TIMING_VTS_REG,
		vts & 0xFFFF);

	if (IS_ERR_VALUE(ret)) {
		aptina_camera_module_pr_err(cam_mod, "failed with error (%d)\n", ret);
	} else {
		aptina_camera_module_pr_debug(cam_mod, "updated vts = %d,vts_min=%d\n",
			vts, cam_mod->vts_min);
		cam_mod->vts_cur = vts;
	}
	return ret;
}

static int ar0144cs_write_aec(struct aptina_camera_module *cam_mod)
{
	int ret = 0;

	aptina_camera_module_pr_debug(cam_mod,
		"exp_time = %d, gain = %d, flash_mode = %d\n",
		cam_mod->exp_config.exp_time,
		cam_mod->exp_config.gain,
		cam_mod->exp_config.flash_mode);
	/*
	 * if the sensor is already streaming, write to shadow registers,
	 * if the sensor is in SW standby, write to active registers,
	 * if the sensor is off/registers are not writeable, do nothing
	 */
	if ((cam_mod->state == APTINA_CAMERA_MODULE_SW_STANDBY) ||
		(cam_mod->state == APTINA_CAMERA_MODULE_STREAMING)) {
		u32 tgain = cam_mod->exp_config.gain;
		u32 exp_time = cam_mod->exp_config.exp_time;
		u32 again, dgain;

		mutex_lock(&cam_mod->lock);
		tgain = tgain * cam_mod->exp_config.gain_percent / 100;

		if (tgain < 256) { /* 1x~2x */
			again = 0x00;
			dgain = tgain;
		} else if (tgain < 512) { /* 2x~4x */
			again = 0x10;
			dgain = tgain >> 1;
		} else if (tgain < 1024) { /* 4x~8x*/
			again = 0x20;
			dgain = tgain >> 2;
		} else { /* 8x~ */
			again = 0x30;
			dgain = tgain >> 3;
		}

		if (!IS_ERR_VALUE(ret) && cam_mod->auto_adjust_fps)
		ret = ar0144cs_auto_adjust_fps(cam_mod,
				cam_mod->exp_config.exp_time);
		/*GROUPED_PARAMETER_HOLD*/
		ret |= aptina_camera_module_write_reg(cam_mod,
			0x3022, 0x01);

		ret |= aptina_camera_module_write_reg(cam_mod,
			AR0144CS_AEC_PK_AGAIN_REG,
			AR0144CS_FETCH_AGAIN(again));

		ret |= aptina_camera_module_write_reg(cam_mod,
			AR0144CS_AEC_PK_DGAIN_REG,
			AR0144CS_FETCH_DGAIN(dgain));

		ret |= aptina_camera_module_write_reg(cam_mod,
			AR0144CS_AEC_PK_LONG_EXPO_REG,
			AR0144CS_FETCH_BYTE_EXP(exp_time));

		if (!cam_mod->auto_adjust_fps)
			ret |= ar0144cs_set_vts(cam_mod, cam_mod->exp_config.vts_value);

		/* GROUPED_PARAMETER_HOLD*/
		ret |= aptina_camera_module_write_reg(cam_mod,
			0x3022, 0x00);
		mutex_unlock(&cam_mod->lock);
	}

	if (IS_ERR_VALUE(ret))
		aptina_camera_module_pr_err(cam_mod,
			"failed with error (%d)\n", ret);
	return ret;
}

static int ar0144cs_g_ctrl(struct aptina_camera_module *cam_mod, u32 ctrl_id)
{
	int ret = 0;

	aptina_camera_module_pr_debug(cam_mod, "\n");

	switch (ctrl_id) {
	case V4L2_CID_GAIN:
	case V4L2_CID_EXPOSURE:
	case V4L2_CID_FLASH_LED_MODE:
		/* nothing to be done here */
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (IS_ERR_VALUE(ret))
		aptina_camera_module_pr_debug(cam_mod,
			"failed with error (%d)\n", ret);
	return ret;

}

/*--------------------------------------------------------------------------*/

static int ar0144cs_filltimings(struct aptina_camera_module_custom_config *custom)
{
	int i, j;
	struct aptina_camera_module_config *config;
	struct aptina_camera_module_timings *timings;
	struct aptina_camera_module_reg *reg_table;
	int reg_table_num_entries;

	for (i = 0; i < custom->num_configs; i++) {
		config = &custom->configs[i];
		reg_table = config->reg_table;
		reg_table_num_entries = config->reg_table_num_entries;
		timings = &config->timings;
		for (j = 0; j < reg_table_num_entries; j++) {
			switch (reg_table[j].reg) {
			case AR0144CS_TIMING_VTS_REG:
				timings->frame_length_lines = reg_table[j].val;
				break;
			case AR0144CS_TIMING_HTS_REG:
				timings->line_length_pck = reg_table[j].val;
				break;
			case AR0144CS_HORIZONTAL_START_REG:
				timings->crop_horizontal_start =
					reg_table[j].val;
				break;
			case AR0144CS_VERTICAL_START_REG:
				timings->crop_vertical_start = reg_table[j].val;
				break;
			case AR0144CS_HORIZONTAL_END_REG:
				timings->crop_horizontal_end = reg_table[j].val;
				break;
			case AR0144CS_VERTICAL_END_REG:
				timings->crop_vertical_end = reg_table[j].val;
				break;
			}
		}

		timings->vt_pix_clk_freq_hz =
			config->frm_intrvl.interval.denominator
			* timings->frame_length_lines
			* timings->line_length_pck;
		timings->coarse_integration_time_min =
			AR0144CS_COARSE_INTG_TIME_MIN;
		timings->coarse_integration_time_max_margin =
			AR0144CS_COARSE_INTG_TIME_MAX_MARGIN;

		/* aptina Sensor do not use fine integration time. */
		timings->fine_integration_time_min =
			AR0144CS_FINE_INTG_TIME_MIN;
		timings->fine_integration_time_max_margin =
			AR0144CS_FINE_INTG_TIME_MAX_MARGIN;
	}
	return 0;
}

/*--------------------------------------------------------------------------*/

static int ar0144cs_g_timings(struct aptina_camera_module *cam_mod,
			    struct aptina_camera_module_timings *timings)
{
		int ret = 0;
		unsigned int vts;
	
		if (IS_ERR_OR_NULL(cam_mod->active_config))
			goto err;
	
		*timings = cam_mod->active_config->timings;
	
		vts = (!cam_mod->vts_cur) ?
			timings->frame_length_lines :
			cam_mod->vts_cur;
	
		if (cam_mod->frm_intrvl_valid)
			timings->vt_pix_clk_freq_hz =
				cam_mod->frm_intrvl.interval.denominator
				* vts
				* timings->line_length_pck;
		else
			timings->vt_pix_clk_freq_hz =
				cam_mod->active_config->frm_intrvl.interval.denominator
				* vts
				* timings->line_length_pck;
	
		timings->frame_length_lines = vts;
	
		return ret;
	err:
		aptina_camera_module_pr_err(cam_mod,
			"failed with error (%d)\n", ret);
		return ret;

}

/*--------------------------------------------------------------------------*/

static int ar0144cs_s_ctrl(struct aptina_camera_module *cam_mod, u32 ctrl_id)
{
	int ret = 0;

	aptina_camera_module_pr_debug(cam_mod, "\n");

	switch (ctrl_id) {
	case V4L2_CID_GAIN:
	case V4L2_CID_EXPOSURE:
		ret = ar0144cs_write_aec(cam_mod);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (IS_ERR_VALUE(ret))
		aptina_camera_module_pr_debug(cam_mod,
			"failed with error (%d) 0x%x\n", ret, ctrl_id);
	return ret;

}

/*--------------------------------------------------------------------------*/

static int ar0144cs_s_ext_ctrls(struct aptina_camera_module *cam_mod,
				 struct aptina_camera_module_ext_ctrls *ctrls)
{
	int ret = 0;

	/* Handles only exposure and gain together special case. */
	if (ctrls->count == 1)
		ret = ar0144cs_s_ctrl(cam_mod, ctrls->ctrls[0].id);
	if (ctrls->ctrls[0].id == V4L2_CID_GAIN ||
		ctrls->ctrls[0].id == V4L2_CID_EXPOSURE)
		ret = ar0144cs_write_aec(cam_mod);
	else
		ret = -EINVAL;

	if (IS_ERR_VALUE(ret))
		aptina_camera_module_pr_debug(cam_mod,
			"failed with error (%d)\n", ret);

	return ret;

}

/*--------------------------------------------------------------------------*/

static int ar0144cs_start_streaming(struct aptina_camera_module *cam_mod)
{
		int ret = 0;
		struct i2c_client *client = v4l2_get_subdevdata(&cam_mod->sd);

		aptina_camera_module_pr_info(cam_mod,
		"i2c:0x%x active config=%s\n",
		client->addr, cam_mod->active_config->name);

		ret = ar0144cs_g_vts(cam_mod, &cam_mod->vts_min);
		if (IS_ERR_VALUE(ret))
			goto err;

	#ifdef dual_sync 
		mutex_lock(&cam_mod->lock);
		ret = aptina_camera_module_write_reg(cam_mod, 0x301a, 0x0958);
		mutex_unlock(&cam_mod->lock);
	#else
		ret = aptina_camera_module_write_reg(cam_mod, 0x301a, 0x205c);
	#endif

		if (IS_ERR_VALUE(ret))
			goto err;

		msleep(25);
		return 0;
	err:
		aptina_camera_module_pr_err(cam_mod,
			"failed with error (%d)\n", ret);
		return ret;

}

/*--------------------------------------------------------------------------*/

static int ar0144cs_stop_streaming(struct aptina_camera_module *cam_mod)
{
		int ret = 0;
		struct i2c_client *client = v4l2_get_subdevdata(&cam_mod->sd);

		aptina_camera_module_pr_info(cam_mod,"i2c:0x%x active config=%s\n",
		client->addr, cam_mod->active_config->name);

		mutex_lock(&cam_mod->lock);
		ret = aptina_camera_module_write_reg(cam_mod, 0x301a, 0x2058);
		mutex_unlock(&cam_mod->lock);
		if (IS_ERR_VALUE(ret))
			goto err;

		msleep(25);
		return 0;
	err:
		aptina_camera_module_pr_err(cam_mod, "failed with error (%d)\n", ret);
		return ret;

}

/*--------------------------------------------------------------------------*/

static int ar0144cs_check_camera_id(struct aptina_camera_module *cam_mod)
{
		u32 pid;
		int ret = 0;
	
		ret = aptina_camera_module_read_reg(cam_mod,
			2, AR0144CS_PID_ADDR, &pid);

		if (IS_ERR_VALUE(ret)) {
			aptina_camera_module_pr_err(cam_mod,
				"register read failed, camera module powered off?\n");
			goto err;
		}
	
		if (pid == AR0144CS_PID_MAGIC) {
			aptina_camera_module_pr_info(cam_mod,
				"successfully detected camera ID 0x%04x\n", pid);
		} else {
			aptina_camera_module_pr_err(cam_mod,
				"wrong camera ID, expected 0x%04x, detected 0x%04x\n",
				AR0144CS_PID_MAGIC, pid);
			ret = -EINVAL;
			goto err;
		}
		return 0;
	err:
		aptina_camera_module_pr_err(cam_mod, "failed with error (%d)\n", ret);
		return ret;

}

/* ======================================================================== */
/* This part is platform dependent */
/* ======================================================================== */

static struct v4l2_subdev_core_ops ar0144cs_camera_module_core_ops = {
	.g_ctrl = aptina_camera_module_g_ctrl,
	.s_ctrl = aptina_camera_module_s_ctrl,
	.s_ext_ctrls = aptina_camera_module_s_ext_ctrls,
	.s_power = aptina_camera_module_s_power,
	.ioctl = aptina_camera_module_ioctl
};

static struct v4l2_subdev_video_ops ar0144cs_camera_module_video_ops = {
	.s_frame_interval = aptina_camera_module_s_frame_interval,
	.g_frame_interval = aptina_camera_module_g_frame_interval,
	.s_stream = aptina_camera_module_s_stream
};

static struct v4l2_subdev_pad_ops ar0144cs_camera_module_pad_ops = {
	.enum_frame_interval = aptina_camera_module_enum_frameintervals,
	.get_fmt = aptina_camera_module_g_fmt,
	.set_fmt = aptina_camera_module_s_fmt,
};

static struct v4l2_subdev_ops ar0144cs_camera_module_ops = {
	.core = &ar0144cs_camera_module_core_ops,
	.video = &ar0144cs_camera_module_video_ops,
	.pad = &ar0144cs_camera_module_pad_ops
};

static struct aptina_camera_module_custom_config ar0144cs_custom_config = {
	.start_streaming = ar0144cs_start_streaming,
	.stop_streaming = ar0144cs_stop_streaming,
	.s_ctrl = ar0144cs_s_ctrl,
	.g_ctrl = ar0144cs_g_ctrl,
	.s_ext_ctrls = ar0144cs_s_ext_ctrls,
	.s_vts = ar0144cs_auto_adjust_fps,
	.g_timings = ar0144cs_g_timings,
	.set_flip = ar0144cs_set_flip,
	.check_camera_id = ar0144cs_check_camera_id,
	.configs = ar0144cs_configs,
	.num_configs = ARRAY_SIZE(ar0144cs_configs),
	.power_up_delays_ms = {5, 30, 30},
	/*
	 * 0: Exposure time valid fileds;
	 * 1: Exposure gain valid fileds;
	 * (2 fileds == 1 frames)
	 */
	.exposure_valid_frame = {4, 4}
};

static int ar0144cs_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	static int i;
	dev_info(&client->dev, "probing device num %d...\n", i);

	ar0144cs_filltimings(&ar0144cs_custom_config);
	v4l2_i2c_subdev_init(&ar0144cs.sd,
		client, &ar0144cs_camera_module_ops);
	ar0144cs.sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	ar0144cs.custom = ar0144cs_custom_config;
	mutex_init(&ar0144cs.lock);
	dev_info(&client->dev, "probing device num %d successful\n", i);
	return 0;
}

/* ======================================================================== */

static int ar0144cs_remove(struct i2c_client *client)
{
	struct aptina_camera_module *cam_mod = i2c_get_clientdata(client);

	dev_info(&client->dev, "removing device...\n");

	if (!client->adapter)
		return -ENODEV;
	mutex_destroy(&cam_mod->lock);
	aptina_camera_module_release(cam_mod);

	dev_info(&client->dev, "removed\n");
	return 0;
}

static const struct i2c_device_id ar0144cs_id[] = {
	{ AR0144CS_DRIVER_NAME, 0 },
	{ }
};

static const struct of_device_id ar0144cs_of_match[] = {
	{.compatible = "aptina,ar0144cs-v4l2-i2c-subdev"},
	{},
};

MODULE_DEVICE_TABLE(i2c, ar0144cs_id);

static struct i2c_driver ar0144cs_i2c_driver = {
	.driver = {
		.name = AR0144CS_DRIVER_NAME,
		.of_match_table = ar0144cs_of_match
	},
	.probe = ar0144cs_probe,
	.remove = ar0144cs_remove,
	.id_table = ar0144cs_id,
};

module_i2c_driver(ar0144cs_i2c_driver);

MODULE_DESCRIPTION("SoC Camera driver for ar0144cs");
MODULE_AUTHOR("zack.zeng");
MODULE_LICENSE("GPL");
