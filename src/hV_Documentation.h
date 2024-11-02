///
/// @file hV_Documentation.h
/// @brief Documentation for the Pervasive Displays Library Suite
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @mainpage Pervasive Displays Library Suite - Basic edition
///
/// @details The Pervasive Displays Library Suite is specifically designed for the [Pervasive Displays](https://www.pervasivedisplays.com/) e-paper screens and EXT3 extension board.
///
/// @image html Logo-PDI-text-320.jpeg
/// @image latex Logo-PDI-text-320.pdf width=10cm
///
/// It provides a high-level interface to drive the e-paper screens with global and fast update, supports capacitive touch and haptic feed-back.
///
/// @b Variants
///
/// The basic edition includes different variants and supports
///
/// * **PDLS_EXT3_Basic_Global** for [monochrome screens](https://www.pervasivedisplays.com/products-e-ink-display/?_sft_product_colour=black-white) (film `C`) and [colour (black-white-red)](https://www.pervasivedisplays.com/products-e-ink-display/?_sft_product_colour=black-white-red) (film `J`),
/// * **PDLS_EXT3_Basic_Fast** for [monochrome screens with embedded fast update](https://www.pervasivedisplays.com/products-e-ink-display/?_sft_etc_itc=pu) (film `P`),
/// * **PDLS_EXT3_Basic_Wide** for [monochrome screens with wide temperature and embedded fast update](https://www.pervasivedisplays.com/products-e-ink-display/?_sft_etc_itc=pu&_sft_temperature_range=m15c-to-p60c) (film `K`),
/// * **PDLS_EXT3_Basic_Touch** for [monochrome screens with capacitive touch](https://www.pervasivedisplays.com/products-e-ink-display/?_sft_etc_itc=tp),
/// * **PDLS_EXT3_Basic_BWRY** for [black-white-red-yellow screens](https://www.pervasivedisplays.com/products-e-ink-display/?_sft_product_colour=black-white-red-yellow) (film `Q`);
///
/// the boards
///
/// * [EPD Extension Kit Gen 3 (EXT3 or EXT3-1)](https://www.pervasivedisplays.com/product/epd-extension-kit-gen-3-EXT3/),
/// * [Touch Expansion Board for EXT3 (EXT3-Touch)](https://www.pervasivedisplays.com/product/touch-expansion-board-ext3-touch/);
///
/// the kits
///
/// * [EPD Pico Kit (EPDK-266)](https://www.pervasivedisplays.com/product/epd-pico-kit-epdk/), which includes a Raspberry Pi Pico RP2040, an EXT3-1 extension board and a 2.66&quot; monochrome panel,
/// * [EPD Pico Kit Touch (EPDK-271-Touch)](https://www.pervasivedisplays.com/product/touch-expansion-board-ext3-touch/#tab-3), which includes a Raspberry Pi Pico RP2040, an EXT3-1 and EXT3-Touch boards and a 2.71&quot;-Touch monochrome panel with embedded fast update.
///
/// @b Documentation
///
/// The documentation includes two documents:
///
/// * This **Reference manual** lists all the objects and functions, with details for their parameters and returned results.
///
/// * The [User guide](https://pdls.pervasivedisplays.com/userguide/index.html) focuses on how to use the different libraries, with commented examples.
///
/// Additionally, the **[Wiki](https://docs.pervasivedisplays.com/)** provides a gradual introduction to the e-paper technology and how to use it.
///
/// @author Rei Vilo
/// @date 21 Oct 2024
/// @version 807
///
/// @copyright (c) Rei Vilo, 2010-2024
/// @copyright All rights reserved
/// @copyright For exclusive use with Pervasive Displays screens
/// @copyright Portions (c) Pervasive Displays, 2010-2024
///
/// * Basic edition: for hobbyists and for basic usage
/// @n Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
/// ([summary](https://creativecommons.org/licenses/by-sa/4.0/deed.en) and [legal code](https://creativecommons.org/licenses/by-sa/4.0/legalcode.en))
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
/// @b Disclaimer
///
/// The software, including the related documentation, is provided to you "as is," and we make no express or implied warranties whatsoever with respect to its functionality, operability, or use, including, without limitation, any implied warranties of merchantability, fitness for a particular purpose, or infringement. We expressly disclaim any liability whatsoever for any direct, indirect, consequential, incidental or special damages, including, without limitation, lost revenues, lost profits, losses resulting from business interruption or loss of data, regardless of the form of action or legal theory under which the liability may be asserted, even if advised of the possibility or likelihood of such damages.
///
/// @page Examples Examples
///
/// Examples are under the examples folders.
///
/// * Common
///     * Common_Colours.ino
/// @image html T2_PALET.jpg
/// @image latex T2_PALET.jpg width=8cm
///     * Common_Fonts.ino
/// @image html T2_FONTS.jpg
/// @image latex T2_FONTS.jpg width=8cm
///     * Common_Orientation.ino
/// @image html T2_ORIEN.jpg
/// @image latex T2_ORIEN.jpg width=8cm
///     * Common_Forms.ino
/// @image html T2_FORMS.jpg
/// @image latex T2_FORMS.jpg width=8cm
///     * Common_Text.ino
/// @image html T2_CHARA.jpg
/// @image latex T2_CHARA.jpg width=8cm
///     * Common_WhoAmI.ino
/// @image html T2_WHOAMI.jpg
/// @image latex T2_WHOAMI.jpg width=8cm
///
/// * Fast update
///     * Common_Speed.ino
/// @image html Global.jpeg
/// @image latex Global.jpeg width=8cm
///     * Fast_Speed.ino
/// @image html Fast.jpeg
/// @image latex Fast.jpeg width=8cm
///
/// * Black-White-Red-Yellow
///     * BWRY_Colours.ino
/// @image html BWRY_Colours.png
/// @image latex BWRY_Colours.png width=8cm
///     * BWRY_Palette.ino
/// @image html BWRY_Palette.png
/// @image latex BWRY_Palette.png width=8cm
///     * BWRY_Contrasts.ino
/// @image html BWRY_Contrasts.jpg
/// @image latex BWRY_Contrasts.jpg width=8cm
///

