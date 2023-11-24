///
/// @file hV_List_Screens.h
/// @brief List of supported Pervasive Displays screens
/// @note Legacy screens are listed in the corresponding screen libraries
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @n Content
/// * 1- List of supported Pervasive Displays screens
///
/// @author Rei Vilo
/// @date 21 Nov 2023
/// @version 702
///
/// @copyright (c) Rei Vilo, 2010-2023
/// @copyright All rights reserved
///
/// * Basic edition: for hobbyists and for basic usage
/// @n Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
///
/// * Evaluation edition: for professionals or organisations, evaluation only, no commercial usage
/// @n All rights reserved
///
/// * Commercial edition: for professionals or organisations, commercial usage
/// @n All rights reserved
///

// SDK
#include "stdint.h"

#ifndef hV_LIST_SCREENS_RELEASE
///
/// @brief Release
///
#define hV_LIST_SCREENS_RELEASE 702

///
/// @brief Screen type
///
#define eScreen_EPD_EXT3_t uint32_t

///
/// @name Monochrome screens
/// @note Global update mode
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=itc&_sft_product_colour=black-white
/// @{
///
#define eScreen_EPD_EXT3_154 (uint32_t)0x1500 ///< reference xE2154CSxxx
#define eScreen_EPD_EXT3_213 (uint32_t)0x2100 ///< reference xE2213CSxxx
#define eScreen_EPD_EXT3_266 (uint32_t)0x2600 ///< reference xE2266CSxxx
#define eScreen_EPD_EXT3_271 (uint32_t)0x2700 ///< reference xE2271CSxxx
#define eScreen_EPD_EXT3_287 (uint32_t)0x2800 ///< reference xE2287CSxxx
#define eScreen_EPD_EXT3_290 (uint32_t)0x2900 ///< reference xE2290CSxxx
#define eScreen_EPD_EXT3_370 (uint32_t)0x3700 ///< reference xE2370CSxxx
#define eScreen_EPD_EXT3_417 (uint32_t)0x4100 ///< reference xE2417CSxxx
#define eScreen_EPD_EXT3_437 (uint32_t)0x4300 ///< reference xE2437CSxxx
#define eScreen_EPD_EXT3_565 (uint32_t)0x5600 ///< reference xE2565CSxxx
#define eScreen_EPD_EXT3_581 (uint32_t)0x580B ///< reference xE2581CS0Bx
#define eScreen_EPD_EXT3_741 (uint32_t)0x740B ///< reference xE2741CS0Bx
#define eScreen_EPD_EXT3_969 (uint32_t)0x960B ///< reference xE2969CS0Bx
#define eScreen_EPD_EXT3_B98 (uint32_t)0xB90B ///< reference xE2B98CS0Bx
/// @}

///
/// @name Colour black-white-red "Spectra" screens
/// @note Global update mode
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=itc&_sft_product_colour=black-white-red
/// @{
///
#define eScreen_EPD_EXT3_154_BWR (uint32_t)0x101500 ///< reference xE2154CSxxx
#define eScreen_EPD_EXT3_213_BWR (uint32_t)0x102100 ///< reference xE2213CSxxx
#define eScreen_EPD_EXT3_266_BWR (uint32_t)0x102600 ///< reference xE2266CSxxx
#define eScreen_EPD_EXT3_271_BWR (uint32_t)0x102700 ///< reference xE2271CSxxx
#define eScreen_EPD_EXT3_287_BWR (uint32_t)0x102800 ///< reference xE2287CSxxx
#define eScreen_EPD_EXT3_290_BWR (uint32_t)0x102900 ///< reference xE2290CSxxx
#define eScreen_EPD_EXT3_370_BWR (uint32_t)0x103700 ///< reference xE2370CSxxx
#define eScreen_EPD_EXT3_417_BWR (uint32_t)0x104100 ///< reference xE2417CSxxx
#define eScreen_EPD_EXT3_437_BWR (uint32_t)0x104300 ///< reference xE2437CSxxx
#define eScreen_EPD_EXT3_565_BWR (uint32_t)0x105600 ///< reference xE2565CSxxx
#define eScreen_EPD_EXT3_581_0B_BWR (uint32_t)0x10580B ///< reference xE2581CS0Bx
#define eScreen_EPD_EXT3_741_0B_BWR (uint32_t)0x10740B ///< reference xE2741CS0Bx
#define eScreen_EPD_EXT3_969_0B_BWR (uint32_t)0x10960B ///< reference xE2969CS0Bx
#define eScreen_EPD_EXT3_B98_0B_BWR (uint32_t)0x10B90B ///< reference xE2B98CS0Bx
/// @}

///
/// @name Colour black-white-red-yellow "Spectra 4" screens
/// @note Global update mode
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=itc&_sft_product_colour=black-white-red-yellow
/// @{
///
#define eScreen_EPD_EXT3_154_BWRY (uint32_t)0x20150F ///< reference xE2154QS0Fx
#define eScreen_EPD_EXT3_213_BWRY (uint32_t)0x20210F ///< reference xE2213QS0Fx
#define eScreen_EPD_EXT3_266_BWRY (uint32_t)0x20260F ///< reference xE2266QS0Fx
#define eScreen_EPD_EXT3_417_BWRY (uint32_t)0x20410A ///< reference xE2417QS0Ax
/// @}

///
/// @name Monochrome touch screens with embedded fast update
/// @note Global and fast update modes
/// @deprecated Partial update is removed. Use fast update instead (7.0.0).
/// @see https://www.pervasivedisplays.com/products
/// @{
///
#define eScreen_EPD_EXT3_271_09_Touch (uint32_t)0x032709 ///< reference xTP271PGH0x
#define eScreen_EPD_EXT3_270_09_Touch (uint32_t)0x032709 ///< reference xTP270PGH0x, legacy name
#define eScreen_EPD_EXT3_370_0C_Touch (uint32_t)0x03370C ///< reference xTP370PGH0x
#define eScreen_EPD_EXT3_270_Touch (uint32_t)0x032709 ///< reference xTP270PGH0x, legacy name
#define eScreen_EPD_EXT3_271_Touch (uint32_t)0x032709 ///< reference xTP271PGH0x, legacy name
#define eScreen_EPD_EXT3_370_Touch (uint32_t)0x03370C ///< reference xTP370PGH0x, legacy name
/// @}

/// @name Monochrome screens with embedded fast update
/// @note Global and fast update modes
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=pu+itc
/// @{
///
#define eScreen_EPD_EXT3_154_0C_Fast (uint32_t)0x01150C ///< reference xE2154PS0Cx
#define eScreen_EPD_EXT3_213_0E_Fast (uint32_t)0x01210E ///< reference xE2213PS0Ex
#define eScreen_EPD_EXT3_266_0C_Fast (uint32_t)0x01260C ///< reference xE2266PS0Cx
#define eScreen_EPD_EXT3_271_09_Fast (uint32_t)0x012709 ///< reference xE2271PS09x
#define eScreen_EPD_EXT3_270_09_Fast (uint32_t)0x012709 ///< reference xE2271PS09x, legacy name
#define eScreen_EPD_EXT3_287_09_Fast (uint32_t)0x012809 ///< reference xE2287PS09x
#define eScreen_EPD_EXT3_370_0C_Fast (uint32_t)0x01370C ///< reference xE2370PS0Cx
#define eScreen_EPD_EXT3_417_0D_Fast (uint32_t)0x01410D ///< reference xE2417PS0Dx
#define eScreen_EPD_EXT3_437_0C_Fast (uint32_t)0x01430C ///< reference xE2437PS0Cx
/// @todo eScreen_EPD_EXT3_581_0B_Fast not tested
#define eScreen_EPD_EXT3_581_0B_Fast (uint32_t)0x01580B ///< reference xE2581PS0Bx, not tested
/// @todo eScreen_EPD_EXT3_741_0B_Fast not tested
#define eScreen_EPD_EXT3_741_0B_Fast (uint32_t)0x01740B ///< reference xE2741PS0Bx, not tested
/// @todo eScreen_EPD_EXT3_969_0B_Fast not tested
#define eScreen_EPD_EXT3_969_0B_Fast (uint32_t)0x01960B ///< reference xE2969PS0Bx, not tested
/// @todo eScreen_EPD_EXT3_B98_0B_Fast not tested
#define eScreen_EPD_EXT3_B98_0B_Fast (uint32_t)0x01B90B ///< reference xE2B98PS0Bx, not tested
/// @}

/// @name Monochrome screens with embedded fast update and wide temperature
/// @note Global and fast update modes
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=pu+itc&_sft_temperature_range=m15c-to-p60c
/// @{
///
#define eScreen_EPD_EXT3_150_0J_Wide (uint32_t)0x49154A ///< reference xE2150KS0Jx
#define eScreen_EPD_EXT3_152_0J_Wide (uint32_t)0x49154A ///< reference xE2152KS0Jx
#define eScreen_EPD_EXT3_154_0C_Wide (uint32_t)0x09150C ///< reference xE2154KS0Cx
#define eScreen_EPD_EXT3_206_0E_Wide (uint32_t)0x09200E ///< reference xE2206KS0Ex
#define eScreen_EPD_EXT3_213_0E_Wide (uint32_t)0x09210E ///< reference xE2213KS0Ex
#define eScreen_EPD_EXT3_266_0C_Wide (uint32_t)0x09260C ///< reference xE2266KS0Cx
#define eScreen_EPD_EXT3_271_09_Wide (uint32_t)0x092709 ///< reference xE2271KS09x
/// @todo eScreen_EPD_EXT3_287_09_Wide not tested
#define eScreen_EPD_EXT3_287_09_Wide (uint32_t)0x092809 ///< reference xE2287PS09x, not tested
#define eScreen_EPD_EXT3_290_0F_Wide (uint32_t)0x09290F ///< reference xE2290KS0Fx
#define eScreen_EPD_EXT3_370_0C_Wide (uint32_t)0x09370C ///< reference xE2370KS0Cx
#define eScreen_EPD_EXT3_417_0D_Wide (uint32_t)0x09410D ///< reference xE2417KS0Dx
/// @todo eScreen_EPD_EXT3_437_0C_Wide not tested
#define eScreen_EPD_EXT3_437_0C_Wide (uint32_t)0x09430C ///< reference xE2437KS0Cx, not tested
#define eScreen_EPD_EXT3_581_06_Wide (uint32_t)0x09580B ///< reference xE2581KS0Bx
/// @todo eScreen_EPD_EXT3_741_0B_Wide not tested
#define eScreen_EPD_EXT3_741_0B_Wide (uint32_t)0x09740B ///< reference xE2741KS0Bx, not tested
/// @todo eScreen_EPD_EXT3_969_0B_Wide not tested
#define eScreen_EPD_EXT3_969_0B_Wide (uint32_t)0x09960B ///< reference xE2969KS0Bx, not tested
/// @todo eScreen_EPD_EXT3_B98_0B_Wide not tested
#define eScreen_EPD_EXT3_B98_0B_Wide (uint32_t)0x09B90B ///< reference xE2B98KS0Bx, not tested
/// @}

///
/// @name Frame-buffer sizes
/// @details
/// * Black-white-red screens and monochrome screens
/// @n Frame-buffer size = width * height / 8 * depth, uint32_t
/// @n Depth = 2
/// * Black-white-red_yellow screens
/// @n Frame-buffer size = width * height / 4 * depth, uint32_t
/// @n Depth = 1
/// @{
///
#define frameSize_EPD_EXT3_150 (uint32_t)(10000) ///< reference xE2150xS0xx
#define frameSize_EPD_EXT3_152 (uint32_t)(10000) ///< reference xE2152xS0xx
#define frameSize_EPD_EXT3_154 (uint32_t)(5776) ///< reference xE2154xS0xx
#define frameSize_EPD_EXT3_206 (uint32_t)(7936) ///< reference xE2206xS0xx
#define frameSize_EPD_EXT3_213 (uint32_t)(5512) ///< reference xE2213xS0xx
#define frameSize_EPD_EXT3_266 (uint32_t)(11248) ///< reference xE2266xS0xx
#define frameSize_EPD_EXT3_270 (uint32_t)(11616) ///< reference xE2271xS0xx, legacy name
#define frameSize_EPD_EXT3_271 (uint32_t)(11616) ///< reference xE2271xS0xx
#define frameSize_EPD_EXT3_287 (uint32_t)(9472) ///< reference xE2287xS0xx
#define frameSize_EPD_EXT3_290 (uint32_t)(16128) ///< reference xE2290xS0xx
#define frameSize_EPD_EXT3_350 (uint32_t)(24960) ///< reference xE2350xS0xx
#define frameSize_EPD_EXT3_370 (uint32_t)(24960) ///< reference xE2370xS0xx
#define frameSize_EPD_EXT3_417 (uint32_t)(30000) ///< reference xE2417xS0xx
#define frameSize_EPD_EXT3_437 (uint32_t)(21120) ///< reference xE2437xS0xx
#define frameSize_EPD_EXT3_565 (uint32_t)(33600) ///< reference xE2565xS0xx
#define frameSize_EPD_EXT3_581 (uint32_t)(46080) ///< reference xE2581xS0xx
#define frameSize_EPD_EXT3_741 (uint32_t)(96000) ///< reference xE2741xS0xx
#define frameSize_EPD_EXT3_969 (uint32_t)(161280) ///< reference xE2969xS0xx
#define frameSize_EPD_EXT3_B98 (uint32_t)(184320) ///< reference xE21198xS0xx
/// @}

#endif // hV_LIST_SCREENS_RELEASE

