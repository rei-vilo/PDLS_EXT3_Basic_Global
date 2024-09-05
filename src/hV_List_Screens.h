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
/// @date 21 Aug 2024
/// @version 805
///
/// @copyright (c) Rei Vilo, 2010-2024
/// @copyright All rights reserved
/// @copyright For exclusive use with Pervasive Displays screens
///
/// * Basic edition: for hobbyists and for basic usage
/// @n Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
/// @see https://creativecommons.org/licenses/by-sa/4.0/
///
/// @n Consider the Evaluation or Commercial editions for professionals or organisations and for commercial usage
///
/// * Evaluation edition: for professionals or organisations, evaluation only, no commercial usage
/// @n All rights reserved
///
/// * Commercial edition: for professionals or organisations, commercial usage
/// @n All rights reserved
///
/// * Viewer edition: for professionals or organisations
/// @n All rights reserved
///
/// * Documentation
/// @n All rights reserved
///

// SDK
#include "stdint.h"

#ifndef hV_LIST_SCREENS_RELEASE
///
/// @brief Release
///
#define hV_LIST_SCREENS_RELEASE 805

/// @deprecated Screen name format (8.0.0)
/// * Name format eScreen_EPD_EXT3_<size>_<driver>_<suffix> is deprecated (8.0.0).
/// * Use name format eScreen_EPD_<size>_<film>_<driver> instead (8.0.0).
///

///
/// @brief Screen type
///
#define eScreen_EPD_t uint32_t

///
/// @brief Function for screen macros
///
#define SCREEN(S, F, D) ((uint32_t)((S & 0x0fff) << 16 | (F & 0xff) << 8 | (D & 0xff)))

///
/// @brief Function for extra macros
///
#define EXTRA(E) ((uint32_t)((E & 0x0f) << 28))

///
/// @name Functions for features from screen macros
///
#define SCREEN_SIZE(X) ((uint16_t)((X >> 16) & 0x0fff)) ///< Get size
#define SCREEN_FILM(X) ((uint8_t)((X >> 8) & 0xff)) ///< Get family
#define SCREEN_DRIVER(X) ((uint8_t)(X & 0xff)) ///< Get type
#define SCREEN_EXTRA(X) ((uint8_t)((X >> 28) & 0x0f)) ///< Get extra

///
/// @name Size, mask 0x0fff = 0..4095
/// @{
///
#define SIZE_150 150 ///< 1.50"
#define SIZE_152 152 ///< 1.52"
#define SIZE_154 154 ///< 1.54"
#define SIZE_206 206 ///< 2.06"
#define SIZE_213 213 ///< 2.13"
#define SIZE_215 215 ///< 2.15"
#define SIZE_266 266 ///< 2.66"
#define SIZE_271 271 ///< 2.71"
#define SIZE_287 287 ///< 2.87"
#define SIZE_290 290 ///< 2.90"
#define SIZE_343 343 ///< 3.43"
#define SIZE_350 350 ///< 3.50"
#define SIZE_370 370 ///< 3.70"
#define SIZE_417 417 ///< 4.17"
#define SIZE_437 437 ///< 4.37"
#define SIZE_565 565 ///< 5.65"
#define SIZE_581 581 ///< 5.81"
#define SIZE_741 741 ///< 7.41"
#define SIZE_969 969 ///< 9.69"
#define SIZE_B98 1198 ///< 11.98"
#define SIZE_1198 1198 ///< 11.98", synonym for SIZE_B98
/// @}

///
/// @name Film type, mask 0xff
/// @{
///
#define FILM_C 'C' ///< Film C, Standard
#define FILM_E 'E' ///< Film E, BWR, deprecated
#define FILM_F 'F' ///< Film E, BWR, deprecated
#define FILM_G 'G' ///< Film G, BWY, deprecated
#define FILM_H 'H' ///< Film H, Freezer
#define FILM_J 'J' ///< Film J, BWR, "Spectra"
#define FILM_K 'K' ///< Film K, Fast update + Wide temperature
#define FILM_P 'P' ///< Film P, Fast update
#define FILM_Q 'Q' ///< Film Q, BWRY, "Spectra 4"
/// @}

///
/// @name Driver type, mask 0xff
/// @{
///
#define DRIVER_5 '5' ///< Driver 5
#define DRIVER_6 '6' ///< Driver 6
#define DRIVER_8 '8' ///< Driver 8
#define DRIVER_9 '9' ///< Driver 9
#define DRIVER_A 'A' ///< Driver A
#define DRIVER_B 'B' ///< Driver B
#define DRIVER_C 'C' ///< Driver C
#define DRIVER_D 'D' ///< Driver D
#define DRIVER_E 'E' ///< Driver E
#define DRIVER_F 'F' ///< Driver F
#define DRIVER_H 'H' ///< Driver H
#define DRIVER_J 'J' ///< Driver J
/// @}

///
/// @name Extra, mask 0x0f = 0..15
/// @{
///
#define EXTRA_TOUCH 1 ///< Touch
#define EXTRA_DEMO 2 ///< Demo
/// @}

///
/// @name Monochrome screens
/// @note Global update mode
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=itc&_sft_product_colour=black-white
/// @{
///
#define eScreen_EPD_154_CS_0C SCREEN(SIZE_154, FILM_C, DRIVER_C) ///< reference xE2154CS0Cx
#define eScreen_EPD_213_CS_0C SCREEN(SIZE_213, FILM_C, DRIVER_C) ///< reference xE2213CS0Cx
#define eScreen_EPD_215_CS_06 SCREEN(SIZE_215, FILM_C, DRIVER_6) ///< reference xE2215CS06x
#define eScreen_EPD_266_CS_09 SCREEN(SIZE_266, FILM_C, DRIVER_9) ///< reference xE2266xS09x
#define eScreen_EPD_266_CS_0C SCREEN(SIZE_266, FILM_C, DRIVER_C) ///< reference xE2266CS0Cx
#define eScreen_EPD_271_CS_09 SCREEN(SIZE_271, FILM_C, DRIVER_9) ///< reference xE2271CS09x
#define eScreen_EPD_287_CS_05 SCREEN(SIZE_287, FILM_C, DRIVER_5) ///< reference xE2287CS05x
#define eScreen_EPD_287_CS_09 SCREEN(SIZE_287, FILM_C, DRIVER_9) ///< reference xE2287CS09x
#define eScreen_EPD_370_CS_0C SCREEN(SIZE_370, FILM_C, DRIVER_C) ///< reference xE2370CS0Cx
#define eScreen_EPD_417_CS_05 SCREEN(SIZE_417, FILM_C, DRIVER_5) ///< reference xE2417CS05x
#define eScreen_EPD_417_CS_0D SCREEN(SIZE_417, FILM_C, DRIVER_D) ///< reference xE2417CS0Dx
#define eScreen_EPD_437_CS_08 SCREEN(SIZE_437, FILM_C, DRIVER_8) ///< reference xE2437CS08x
#define eScreen_EPD_437_CS_0C SCREEN(SIZE_437, FILM_C, DRIVER_C) ///< reference xE2437CS0Cx
#define eScreen_EPD_581_CS_0B SCREEN(SIZE_581, FILM_C, DRIVER_B) ///< reference xE2581CS0Bx
#define eScreen_EPD_741_CS_08 SCREEN(SIZE_741, FILM_C, DRIVER_8) ///< reference xE2741CS08x
#define eScreen_EPD_741_CS_0B SCREEN(SIZE_741, FILM_C, DRIVER_B) ///< reference xE2741CS0Bx
#define eScreen_EPD_969_CS_08 SCREEN(SIZE_969, FILM_C, DRIVER_8) ///< reference xE2969CS08x
#define eScreen_EPD_969_CS_0B SCREEN(SIZE_969, FILM_C, DRIVER_B) ///< reference xE2969CS0Bx
#define eScreen_EPD_B98_CS_0B SCREEN(SIZE_B98, FILM_C, DRIVER_B) ///< reference xE2B98CS0Bx

#define eScreen_EPD_213_HS_09 SCREEN(SIZE_213, FILM_H, DRIVER_9) ///< reference xE2213HS09x
#define eScreen_EPD_266_HS_09 SCREEN(SIZE_266, FILM_H, DRIVER_9) ///< reference xE2266HS09x
/// @}

///
/// @name Legacy monochrome screens
/// @note Global update mode
/// @{
///
#define eScreen_EPD_581_CS_08 SCREEN(SIZE_581, FILM_C, DRIVER_8) ///< reference xE2581CS08x, previous type
#define eScreen_EPD_741_CS_08 SCREEN(SIZE_741, FILM_C, DRIVER_8) ///< reference xE2741CS08x, previous type
#define eScreen_EPD_969_CS_08 SCREEN(SIZE_969, FILM_C, DRIVER_8) ///< reference xE2969CS08x, previous type
#define eScreen_EPD_B98_CS_08 SCREEN(SIZE_1198, FILM_C, DRIVER_8) ///< reference xE2B98CS08x, previous type
/// @}

///
/// @name Colour black-white-red "Spectra" screens
/// @note Global update mode
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=itc&_sft_product_colour=black-white-red
/// @{
///
#define eScreen_EPD_213_ES_09 SCREEN(SIZE_213, FILM_E, DRIVER_9) ///< reference xE2213ES09x
#define eScreen_EPD_287_ES_05 SCREEN(SIZE_287, FILM_E, DRIVER_5) ///< reference xE2287ES05x

#define eScreen_EPD_154_FS_09 SCREEN(SIZE_154, FILM_F, DRIVER_9) ///< reference xE2154FS09x
#define eScreen_EPD_266_FS_09 SCREEN(SIZE_266, FILM_F, DRIVER_9) ///< reference xE2266FS09x
#define eScreen_EPD_271_FS_09 SCREEN(SIZE_271, FILM_F, DRIVER_9) ///< reference xE2271FS09x
#define eScreen_EPD_287_FS_09 SCREEN(SIZE_287, FILM_F, DRIVER_9) ///< reference xE2287FS09x
#define eScreen_EPD_370_FS_08 SCREEN(SIZE_370, FILM_F, DRIVER_8) ///< reference xE2370FS08x
#define eScreen_EPD_417_FS_05 SCREEN(SIZE_417, FILM_F, DRIVER_5) ///< reference xE2417FS05x
#define eScreen_EPD_437_FS_08 SCREEN(SIZE_437, FILM_F, DRIVER_8) ///< reference xE2437FS08x
#define eScreen_EPD_581_FS_08 SCREEN(SIZE_581, FILM_F, DRIVER_8) ///< reference xE2581FS08x
#define eScreen_EPD_741_FS_08 SCREEN(SIZE_741, FILM_F, DRIVER_8) ///< reference xE2741FS08x
#define eScreen_EPD_B98_FS_08 SCREEN(SIZE_B98, FILM_F, DRIVER_8) ///< reference xE2B98FS08x

#define eScreen_EPD_154_GS_09 SCREEN(SIZE_154, FILM_G, DRIVER_9) ///< reference xE2154GS09x
#define eScreen_EPD_213_GS_09 SCREEN(SIZE_213, FILM_G, DRIVER_9) ///< reference xE2213GS09x
#define eScreen_EPD_266_GS_09 SCREEN(SIZE_266, FILM_G, DRIVER_9) ///< reference xE2266GS09x
#define eScreen_EPD_417_GS_05 SCREEN(SIZE_417, FILM_G, DRIVER_5) ///< reference xE2417GS05x
#define eScreen_EPD_437_GS_08 SCREEN(SIZE_437, FILM_G, DRIVER_8) ///< reference xE2437GS08x
#define eScreen_EPD_741_GS_08 SCREEN(SIZE_741, FILM_G, DRIVER_8) ///< reference xE2741GS08x
#define eScreen_EPD_B98_GS_08 SCREEN(SIZE_B98, FILM_G, DRIVER_8) ///< reference xE2B98GS08x

#define eScreen_EPD_154_JS_0C SCREEN(SIZE_154, FILM_J, DRIVER_C) ///< reference xE2154JS0Cx
#define eScreen_EPD_213_JS_0C SCREEN(SIZE_213, FILM_J, DRIVER_C) ///< reference xE2213JS0Cx
#define eScreen_EPD_266_JS_0C SCREEN(SIZE_266, FILM_J, DRIVER_C) ///< reference xE2266JS0Cx
#define eScreen_EPD_271_JS_09 SCREEN(SIZE_271, FILM_J, DRIVER_9) ///< reference xE2271JS09x
#define eScreen_EPD_287_JS_09 SCREEN(SIZE_287, FILM_J, DRIVER_9) ///< reference xE2287JS09x
#define eScreen_EPD_290_JS_0F SCREEN(SIZE_290, FILM_J, DRIVER_F) ///< reference xE2290JS0Fx
#define eScreen_EPD_370_JS_0C SCREEN(SIZE_370, FILM_J, DRIVER_C) ///< reference xE2370JS0Cx
#define eScreen_EPD_417_JS_0D SCREEN(SIZE_417, FILM_J, DRIVER_D) ///< reference xE2417JS0Dx
#define eScreen_EPD_437_JS_08 SCREEN(SIZE_437, FILM_J, DRIVER_8) ///< reference xE2437JS08x
#define eScreen_EPD_565_JS_08 SCREEN(SIZE_565, FILM_J, DRIVER_8) ///< reference xE2565JS08x
#define eScreen_EPD_581_JS_0B SCREEN(SIZE_581, FILM_J, DRIVER_B) ///< reference xE2581JS0Bx
#define eScreen_EPD_741_JS_0B SCREEN(SIZE_741, FILM_J, DRIVER_B) ///< reference xE2741JS0Bx
#define eScreen_EPD_969_JS_08 SCREEN(SIZE_969, FILM_J, DRIVER_8) ///< reference xE2969JS08x
#define eScreen_EPD_969_JS_0B SCREEN(SIZE_969, FILM_J, DRIVER_B) ///< reference xE2969JS0Bx
#define eScreen_EPD_B98_JS_0B SCREEN(SIZE_B98, FILM_J, DRIVER_B) ///< reference xE2B98JS0Bx
/// @}

///
/// @name Colour black-white-red-yellow "Spectra 4" screens
/// @note Global update mode
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=itc&_sft_product_colour=black-white-red-yellow
/// @{
///
#define eScreen_EPD_154_QS_0F SCREEN(SIZE_154, FILM_Q, DRIVER_F) ///< reference xE2154QS0Fx
#define eScreen_EPD_213_QS_0F SCREEN(SIZE_213, FILM_Q, DRIVER_F) ///< reference xE2213QS0Fx
#define eScreen_EPD_266_QS_0F SCREEN(SIZE_266, FILM_Q, DRIVER_F) ///< reference xE2266QS0Fx
#define eScreen_EPD_417_QS_0A SCREEN(SIZE_417, FILM_Q, DRIVER_A) ///< reference xE2417QS0Ax
/// @}

///
/// @name Monochrome touch screens with embedded fast update
/// @note Global and fast update modes
/// @deprecated Partial update is removed. Use fast update instead (7.0.0).
/// @see https://www.pervasivedisplays.com/products
/// @{
///
#define eScreen_EPD_271_PS_09_Touch SCREEN(SIZE_271, FILM_P, DRIVER_9) | EXTRA(EXTRA_TOUCH) ///< reference xE2271PS09x
#define eScreen_EPD_271_KS_09_Touch SCREEN(SIZE_271, FILM_K, DRIVER_9) | EXTRA(EXTRA_TOUCH) ///< reference xE2271KS09x
#define eScreen_EPD_343_PS_0B_Touch SCREEN(SIZE_343, FILM_P, DRIVER_B) | EXTRA(EXTRA_TOUCH) ///< reference xE2343PS0Bx
#define eScreen_EPD_370_PS_0C_Touch SCREEN(SIZE_370, FILM_P, DRIVER_C) | EXTRA(EXTRA_TOUCH) ///< reference xE2370PS0Cx
/// @}

/// @name Monochrome screens with embedded fast update
/// @note Global and fast update modes
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=pu+itc
/// @{
///
#define eScreen_EPD_154_PS_0C SCREEN(SIZE_154, FILM_P, DRIVER_C) ///< reference xE2154PS0Cx
#define eScreen_EPD_213_PS_0E SCREEN(SIZE_213, FILM_P, DRIVER_E) ///< reference xE2213PS0Ex
#define eScreen_EPD_266_PS_0C SCREEN(SIZE_266, FILM_P, DRIVER_C) ///< reference xE2266PS0Cx
#define eScreen_EPD_271_PS_09 SCREEN(SIZE_271, FILM_P, DRIVER_9) ///< reference xE2271PS09x
#define eScreen_EPD_287_PS_09 SCREEN(SIZE_287, FILM_P, DRIVER_9) ///< reference xE2287PS09x
/// @todo eScreen_EPD_343_PS_0B not tested
#define eScreen_EPD_343_PS_0B SCREEN(SIZE_343, FILM_P, DRIVER_B) ///< reference xE2343PS0Bx
#define eScreen_EPD_370_PS_0C SCREEN(SIZE_370, FILM_P, DRIVER_C) ///< reference xE2370PS0Cx
#define eScreen_EPD_417_PS_0D SCREEN(SIZE_417, FILM_P, DRIVER_D) ///< reference xE2417PS0Dx
#define eScreen_EPD_437_PS_0C SCREEN(SIZE_437, FILM_P, DRIVER_C) ///< reference xE2437PS0Cx
/// @todo eScreen_EPD_581_PS_0B not tested
#define eScreen_EPD_581_PS_0B SCREEN(SIZE_581, FILM_P, DRIVER_B) ///< reference xE2581PS0Bx, not tested
// /// @todo eScreen_EPD_741_PS_0B not tested
// #define eScreen_EPD_741_PS_0B SCREEN(SIZE_741, FILM_P, DRIVER_B) ///< reference xE2741PS0Bx, not tested
// /// @todo eScreen_EPD_969_PS_0B not tested
// #define eScreen_EPD_969_PS_0B SCREEN(SIZE_969, FILM_P, DRIVER_B) ///< reference xE2969PS0Bx, not tested
// /// @todo eScreen_EPD_B98_PS_0B not tested
// #define eScreen_EPD_B98_PS_0B SCREEN(SIZE_B98, FILM_P, DRIVER_B) ///< reference xE2B98PS0Bx, not tested
/// @}

/// @name Monochrome screens with embedded fast update and wide temperature
/// @note Global and fast update modes
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=pu+itc&_sft_temperature_range=m15c-to-p60c
/// @{
///
#define eScreen_EPD_150_KS_0J SCREEN(SIZE_150, FILM_K, DRIVER_J) ///< reference xE2150KS0Jx
#define eScreen_EPD_152_KS_0J SCREEN(SIZE_152, FILM_K, DRIVER_J) ///< reference xE2152KS0Jx
#define eScreen_EPD_154_KS_0C SCREEN(SIZE_154, FILM_K, DRIVER_C) ///< reference xE2154KS0Cx
#define eScreen_EPD_206_KS_0E SCREEN(SIZE_206, FILM_K, DRIVER_E) ///< reference xE2206KS0Ex
#define eScreen_EPD_213_KS_0E SCREEN(SIZE_213, FILM_K, DRIVER_E) ///< reference xE2213KS0Ex
#define eScreen_EPD_266_KS_0C SCREEN(SIZE_266, FILM_K, DRIVER_C) ///< reference xE2266KS0Cx
#define eScreen_EPD_271_KS_09 SCREEN(SIZE_271, FILM_K, DRIVER_9) ///< reference xE2271KS09x
#define eScreen_EPD_271_KS_0C SCREEN(SIZE_271, FILM_K, DRIVER_C) ///< reference xE2271KS0Cx
#define eScreen_EPD_290_KS_0F SCREEN(SIZE_290, FILM_K, DRIVER_F) ///< reference xE2290KS0Fx
/// @todo eScreen_EPD_350_KS_0C not tested
#define eScreen_EPD_350_KS_0C SCREEN(SIZE_350, FILM_K, DRIVER_C) ///< reference xE2350KS0Cx)
#define eScreen_EPD_370_KS_0C SCREEN(SIZE_370, FILM_K, DRIVER_C) ///< reference xE2370KS0Cx
#define eScreen_EPD_417_KS_0D SCREEN(SIZE_417, FILM_K, DRIVER_D) ///< reference xE2417KS0Dx
/// @todo eScreen_EPD_437_KS_0C not tested
#define eScreen_EPD_437_KS_0C SCREEN(SIZE_437, FILM_K, DRIVER_C) ///< reference xE2437KS0Cx, not tested
/// @todo eScreen_EPD_581_KS_0B not tested
#define eScreen_EPD_581_KS_0B SCREEN(SIZE_581, FILM_K, DRIVER_B) ///< reference xE2581KS0Bx, not tested
// /// @todo eScreen_EPD_741_KS_0B not tested
// #define eScreen_EPD_741_KS_0B SCREEN(SIZE_741, FILM_K, DRIVER_B) ///< reference xE2741KS0Bx, not tested
// /// @todo eScreen_EPD_969_KS_0B not tested
// #define eScreen_EPD_969_KS_0B SCREEN(SIZE_969, FILM_K, DRIVER_B) ///< reference xE2969KS0Bx, not tested
// /// @todo eScreen_EPD_B98_KS_0B not tested
// #define eScreen_EPD_B98_KS_0B SCREEN(SIZE_B98, FILM_K, DRIVER_B) ///< reference xE2B98KS0Bx, not tested
/// @}

///
/// @name Frame-buffer sizes
/// @details
/// * Black-white-red screens and monochrome screens
/// @n Frame-buffer size = width * height / 8 * depth, uint32_t
/// @n Depth = 2
/// * Black-white-red-yellow screens
/// @n Frame-buffer size = width * height / 4 * depth, uint32_t
/// @n Depth = 1
/// @{
///
#define frameSize_EPD_150 (uint32_t)(10000) ///< reference xE2150xS0xx
#define frameSize_EPD_152 (uint32_t)(10000) ///< reference xE2152xS0xx
#define frameSize_EPD_154 (uint32_t)(5776) ///< reference xE2154xS0xx
#define frameSize_EPD_206 (uint32_t)(7936) ///< reference xE2206xS0xx
#define frameSize_EPD_213 (uint32_t)(5512) ///< reference xE2213xS0xx
#define frameSize_EPD_266 (uint32_t)(11248) ///< reference xE2266xS0xx
#define frameSize_EPD_270 (uint32_t)(11616) ///< reference xE2271xS0xx, legacy name
#define frameSize_EPD_271 (uint32_t)(11616) ///< reference xE2271xS0xx
#define frameSize_EPD_287 (uint32_t)(9472) ///< reference xE2287xS0xx
#define frameSize_EPD_290 (uint32_t)(16128) ///< reference xE2290xS0xx
#define frameSize_EPD_343 (uint32_t)(22344) ///< reference xE2343xS0xx
#define frameSize_EPD_350 (uint32_t)(24960) ///< reference xE2350xS0xx
#define frameSize_EPD_370 (uint32_t)(24960) ///< reference xE2370xS0xx
#define frameSize_EPD_417 (uint32_t)(30000) ///< reference xE2417xS0xx
#define frameSize_EPD_437 (uint32_t)(21120) ///< reference xE2437xS0xx
#define frameSize_EPD_565 (uint32_t)(33600) ///< reference xE2565xS0xx
#define frameSize_EPD_581 (uint32_t)(46080) ///< reference xE2581xS0xx
#define frameSize_EPD_741 (uint32_t)(96000) ///< reference xE2741xS0xx
#define frameSize_EPD_969 (uint32_t)(161280) ///< reference xE2969xS0xx
#define frameSize_EPD_B98 (uint32_t)(184320) ///< reference xE21198xS0xx
/// @}

#endif // hV_LIST_SCREENS_RELEASE

