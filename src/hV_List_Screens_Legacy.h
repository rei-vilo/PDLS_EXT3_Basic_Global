///
/// @file hV_List_Screens_Legacy.h
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
/// @date 21 Mar 2024
/// @version 801
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

#ifndef hV_LIST_SCREENS_LEGACY_RELEASE
///
/// @brief Release
///
#define hV_LIST_SCREENS_LEGACY_RELEASE 801

// Current list
#include "hV_List_Screens.h"

///
/// @name Monochrome screens
/// @note Global update mode
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=itc&_sft_product_colour=black-white
/// @{
///
#define eScreen_EPD_EXT3_154 eScreen_EPD_154_CS_0C ///< reference xE2154CSxxx
#define eScreen_EPD_EXT3_213 eScreen_EPD_213_CS_0C ///< reference xE2213CSxxx
#define eScreen_EPD_EXT3_266 eScreen_EPD_266_HS_09 ///< reference xE2266CSxxx
#define eScreen_EPD_EXT3_271 eScreen_EPD_271_CS_09 ///< reference xE2271CSxxx
#define eScreen_EPD_EXT3_287 eScreen_EPD_287_CS_09 ///< reference xE2287CSxxx
#define eScreen_EPD_EXT3_370 eScreen_EPD_370_CS_0C ///< reference xE2370CSxxx
#define eScreen_EPD_EXT3_417 eScreen_EPD_417_CS_0D ///< reference xE2417CSxxx
#define eScreen_EPD_EXT3_437 eScreen_EPD_437_CS_0C ///< reference xE2437CSxxx
#define eScreen_EPD_EXT3_581 eScreen_EPD_581_CS_0B ///< reference xE2581CS0Bx
#define eScreen_EPD_EXT3_741 eScreen_EPD_741_CS_0B ///< reference xE2741CS0Bx
#define eScreen_EPD_EXT3_969 eScreen_EPD_969_CS_0B ///< reference xE2969CS0Bx
#define eScreen_EPD_EXT3_B98 eScreen_EPD_B98_CS_0B ///< reference xE2B98CS0Bx
/// @}

///
/// @name Colour black-white-red "Spectra" screens
/// @note Global update mode
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=itc&_sft_product_colour=black-white-red
/// @{
///
#define eScreen_EPD_EXT3_154_BWR eScreen_EPD_154_JS_0C ///< reference xE2154CSxxx
#define eScreen_EPD_EXT3_213_BWR eScreen_EPD_213_JS_0C ///< reference xE2213CSxxx
#define eScreen_EPD_EXT3_266_BWR eScreen_EPD_266_JS_0C ///< reference xE2266CSxxx
#define eScreen_EPD_EXT3_271_BWR eScreen_EPD_271_JS_09 ///< reference xE2271CSxxx
#define eScreen_EPD_EXT3_287_BWR eScreen_EPD_287_JS_09 ///< reference xE2287CSxxx
#define eScreen_EPD_EXT3_290_BWR eScreen_EPD_290_JS_0F ///< reference xE2290CSxxx
#define eScreen_EPD_EXT3_370_BWR eScreen_EPD_370_JS_0C ///< reference xE2370CSxxx
#define eScreen_EPD_EXT3_417_BWR eScreen_EPD_741_FS_08 ///< reference xE2417CSxxx
#define eScreen_EPD_EXT3_437_BWR eScreen_EPD_437_JS_08 ///< reference xE2437CSxxx
#define eScreen_EPD_EXT3_565_BWR eScreen_EPD_565_JS_08 ///< reference xE2565CSxxx
#define eScreen_EPD_EXT3_581_0B_BWR eScreen_EPD_581_JS_0B ///< reference xE2581CS0Bx
#define eScreen_EPD_EXT3_741_0B_BWR eScreen_EPD_741_JS_0B ///< reference xE2741CS0Bx
#define eScreen_EPD_EXT3_969_0B_BWR eScreen_EPD_969_JS_0B ///< reference xE2969CS0Bx
#define eScreen_EPD_EXT3_B98_0B_BWR eScreen_EPD_B98_JS_0B ///< reference xE2B98CS0Bx
/// @}

///
/// @name Colour black-white-red-yellow "Spectra 4" screens
/// @note Global update mode
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=itc&_sft_product_colour=black-white-red-yellow
/// @{
///
#define eScreen_EPD_EXT3_154_BWRY eScreen_EPD_154_QS_0F ///< reference xE2154QS0Fx
#define eScreen_EPD_EXT3_213_BWRY eScreen_EPD_213_QS_0F ///< reference xE2213QS0Fx
#define eScreen_EPD_EXT3_266_BWRY eScreen_EPD_266_QS_0F ///< reference xE2266QS0Fx
#define eScreen_EPD_EXT3_417_BWRY eScreen_EPD_417_QS_0A ///< reference xE2417QS0Ax
/// @}

///
/// @name Monochrome touch screens with embedded fast update
/// @note Global and fast update modes
/// @deprecated Partial update is removed. Use fast update instead (7.0.0).
/// @see https://www.pervasivedisplays.com/products
/// @{
///
#define eScreen_EPD_EXT3_271_09_Touch eScreen_EPD_271_PS_09_Touch ///< reference xTP271PGH0x
#define eScreen_EPD_EXT3_270_09_Touch eScreen_EPD_271_PS_09_Touch ///< reference xTP270PGH0x, legacy name
#define eScreen_EPD_EXT3_370_0C_Touch eScreen_EPD_370_PS_0C_Touch ///< reference xTP370PGH0x
#define eScreen_EPD_EXT3_270_Touch eScreen_EPD_271_PS_09_Touch ///< reference xTP270PGH0x, legacy name
#define eScreen_EPD_EXT3_271_Touch eScreen_EPD_271_PS_09_Touch ///< reference xTP271PGH0x, legacy name
#define eScreen_EPD_EXT3_370_Touch eScreen_EPD_370_PS_0C_Touch ///< reference xTP370PGH0x, legacy name
/// @}

/// @name Monochrome screens with embedded fast update
/// @note Global and fast update modes
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=pu+itc
/// @{
///
#define eScreen_EPD_EXT3_154_0C_Fast eScreen_EPD_154_PS_0C ///< reference xE2154PS0Cx
#define eScreen_EPD_EXT3_213_0E_Fast eScreen_EPD_213_PS_0E ///< reference xE2213PS0Ex
#define eScreen_EPD_EXT3_266_0C_Fast eScreen_EPD_266_PS_0C ///< reference xE2266PS0Cx
#define eScreen_EPD_EXT3_271_09_Fast eScreen_EPD_271_PS_09 ///< reference xE2271PS09x
#define eScreen_EPD_EXT3_270_09_Fast eScreen_EPD_271_PS_09 ///< reference xE2271PS09x, legacy name
#define eScreen_EPD_EXT3_287_09_Fast eScreen_EPD_287_PS_09 ///< reference xE2287PS09x
#define eScreen_EPD_EXT3_370_0C_Fast eScreen_EPD_370_PS_0C ///< reference xE2370PS0Cx
#define eScreen_EPD_EXT3_417_0D_Fast eScreen_EPD_417_PS_0D ///< reference xE2417PS0Dx
#define eScreen_EPD_EXT3_437_0C_Fast eScreen_EPD_437_PS_0C ///< reference xE2437PS0Cx
// /// @todo eScreen_EPD_EXT3_581_0B_Fast not tested
// #define eScreen_EPD_EXT3_581_0B_Fast eScreen_EPD_581_PS_0B ///< reference xE2581PS0Bx, not tested
// /// @todo eScreen_EPD_EXT3_741_0B_Fast not tested
// #define eScreen_EPD_EXT3_741_0B_Fast eScreen_EPD_741_PS_0B ///< reference xE2741PS0Bx, not tested
/// @todo eScreen_EPD_EXT3_969_0B_Fast not tested
// #define eScreen_EPD_EXT3_969_0B_Fast eScreen_EPD_969_PS_0B ///< reference xE2969PS0Bx, not tested
// /// @todo eScreen_EPD_EXT3_B98_0B_Fast not tested
// #define eScreen_EPD_EXT3_B98_0B_Fast eScreen_EPD_B98_PS_0B ///< reference xE2B98PS0Bx, not tested
/// @}

/// @name Monochrome screens with embedded fast update and wide temperature
/// @note Global and fast update modes
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=pu+itc&_sft_temperature_range=m15c-to-p60c
/// @{
///
#define eScreen_EPD_EXT3_150_0J_Wide eScreen_EPD_150_KS_0J ///< reference xE2150KS0Jx
#define eScreen_EPD_EXT3_152_0J_Wide eScreen_EPD_152_KS_0J ///< reference xE2152KS0Jx
#define eScreen_EPD_EXT3_154_0C_Wide eScreen_EPD_154_KS_0C ///< reference xE2154KS0Cx
#define eScreen_EPD_EXT3_206_0E_Wide eScreen_EPD_206_KS_0E ///< reference xE2206KS0Ex
#define eScreen_EPD_EXT3_213_0E_Wide eScreen_EPD_213_KS_0E ///< reference xE2213KS0Ex
#define eScreen_EPD_EXT3_266_0C_Wide eScreen_EPD_266_KS_0C ///< reference xE2266KS0Cx
#define eScreen_EPD_EXT3_271_09_Wide eScreen_EPD_271_KS_09 ///< reference xE2271KS09x
// /// @todo eScreen_EPD_EXT3_287_09_Wide not tested
// #define eScreen_EPD_EXT3_287_09_Wide eScreen_EPD_287_KS_09 ///< reference xE2287PS09x, not tested
#define eScreen_EPD_EXT3_290_0F_Wide eScreen_EPD_290_KS_0F ///< reference xE2290KS0Fx
#define eScreen_EPD_EXT3_370_0C_Wide eScreen_EPD_370_KS_0C ///< reference xE2370KS0Cx
#define eScreen_EPD_EXT3_417_0D_Wide eScreen_EPD_417_KS_0D ///< reference xE2417KS0Dx
// /// @todo eScreen_EPD_EXT3_437_0C_Wide not tested
// #define eScreen_EPD_EXT3_437_0C_Wide eScreen_EPD_437_KS_0C ///< reference xE2437KS0Cx, not tested
// #define eScreen_EPD_EXT3_581_06_Wide eScreen_EPD_581_KS_0B ///< reference xE2581KS0Bx
// /// @todo eScreen_EPD_EXT3_741_0B_Wide not tested
// #define eScreen_EPD_EXT3_741_0B_Wide eScreen_EPD_741_KS_0B ///< reference xE2741KS0Bx, not tested
// /// @todo eScreen_EPD_EXT3_969_0B_Wide not tested
// #define eScreen_EPD_EXT3_969_0B_Wide eScreen_EPD_969_KS_0B ///< reference xE2969KS0Bx, not tested
// /// @todo eScreen_EPD_EXT3_B98_0B_Wide not tested
// #define eScreen_EPD_EXT3_B98_0B_Wide eScreen_EPD_B98_KS_0B ///< reference xE2B98KS0Bx, not tested
/// @}

#endif // hV_LIST_SCREENS_LEGACY_RELEASE

