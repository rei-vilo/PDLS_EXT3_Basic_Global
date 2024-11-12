///
/// @file hV_List_Options.h
/// @brief List of options for Pervasive Displays Library Suite
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @n Content
/// * 3- Font mode, internal MCU for basic edition
/// * 4- Maximum number of fonts
/// * 5- SRAM memory, internal MCU for basic edition
/// * 6- Use self for basic edition
/// * 7- Touch mode, activated or not
/// * 8- Haptic feedback mode, not implemented
/// * 9. Set GPIO expander mode, not implemented
/// * 10. String object for basic edition
/// * 11. Set storage mode, not implemented
/// * 12. Set debug options, not implemented
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

#ifndef hV_LIST_OPTIONS_RELEASE
///
/// @brief Release
///
#define hV_LIST_OPTIONS_RELEASE 805

///
/// @name 1- List of supported Pervasive Displays screens
/// @see hV_List_Screens.h
///

///
/// @name 2- List of pre-configured boards
/// @see hV_List_Boards.h
///

///
/// @name 3- Set font mode
/// @details From header files or from external flash
/// * Basic edition: Terminal font
/// * Evaluation edition: DejaVu font as header
/// * Commercial edition: DejaVu font as either header or external SPI Flash
/// * Viewer edition: DejaVu font as header
///
/// @note USE_FONT_HEADER requires addFont()
/// @note Font Manager requires USE_FONT_HEADER
/// @warning 8- and 16-bit MCUs may limit the size of the fonts. Use 32-bit MCUs for optimal performance.
///
/// @{
#define USE_FONT_TERMINAL 1 ///< Use default Terminal fonts

#define FONT_MODE USE_FONT_TERMINAL ///< Selected option
/// @}

///
/// @brief 4- Maximum number of fonts
/// @details With MCU Flash, based on available memory, check performed at compilation
/// * USE_FONT_TERMINAL: 1..4
/// * USE_FONT_HEADER: 1..64
///
/// With SPI Flash, based on the fonts previously uploaded
/// * USE_FONT_FLASH: eg. 64
///
#if (FONT_MODE == USE_FONT_TERMINAL)
#define MAX_FONT_SIZE 4
#else
#define MAX_FONT_SIZE 64
#endif

///
/// @name 5- Set SRAM memory
/// @details From internal MCU or external SPI
/// * Basic edition: MCU internal SRAM
/// * Commercial edition: MCU internal SRAM
/// * Evaluation edition: MCU internal or SPI external SRAM
/// * Viewer edition: MCU internal SRAM
///
/// @{
#define USE_INTERNAL_MCU 1 ///< Use MCU internal

#define SRAM_MODE USE_INTERNAL_MCU ///< Selected option
/// @}

///
/// @name 6- Use virtual object
/// @details From hV_Screen_Virtual.h for extended compability
/// @note Declare additional variables if USE_hV_SCREEN_SELF
/// @n Virtual object requires ~1 kB bytes.
/// * Basic edition: self option
/// * Evaluation edition: virtual option
/// * Commercial edition: self and virtual options
/// * Viewer edition: virtual option
///
/// @note Recommended: USE_hV_SCREEN_VIRTUAL
/// @warning Issues with virtual function on arm-none-eabi-g++ 4.9.3: use USE_hV_SCREEN_SELF instead.
/// @{
#define USE_hV_SCREEN_SELF 2 ///< Do not use virtual object

#define USE_hV_SCREEN USE_hV_SCREEN_SELF ///< Selected option
/// @}

///
/// @name 7- Set touch mode
/// @details Only two screens are ready for touch
/// * Basic edition: iTC 2.71 BW and iTC 3.70 BW
/// * Evaluation edition: iTC 2.71 BW and iTC 3.70 BW
/// * Commercial edition: iTC 2.71 BW and iTC 3.70 BW
/// * Viewer edition: iTC 2.71 BW and iTC 3.70 BW
///
/// @note Touch uses I2C and polling over interrupt
/// @{
#define USE_TOUCH_NONE 0 ///< Do not use touch
#define USE_TOUCH_YES 1 ///< Use touch

#define TOUCH_MODE USE_TOUCH_NONE ///< Selected option
/// @}

///
/// @name 8- Set haptic feedback mode
/// * Basic edition: no haptic feedback
/// * Evaluation edition: ERM or LRA
/// * Commercial edition: ERM or LRA
/// * Viewer edition: no haptic feedback
///
/// @{
#define USE_HAPTICS_NONE 0 ///< No motor

#define HAPTICS_MODE USE_HAPTICS_NONE ///< Selected option
/// @}

///
/// @name 9- Set GPIO expander mode
/// * Basic edition: no expander
/// * Evaluation edition: PCF8574 or PCA9536
/// * Commercial edition: PCF8574 or PCA9536
/// * Viewer edition: no expander
///
/// @{
#define USE_EXPANDER_NONE 0 ///< No I2C expander

#define EXPANDER_MODE USE_EXPANDER_NONE ///< Selected option
/// @}

///
/// @name 10- Set string mode
/// * Basic edition: String object
/// * Evaluation edition: char array
/// * Commercial edition: String object or char array
/// * Viewer edition: char array
///
/// @{
#define USE_STRING_OBJECT 1

#define STRING_MODE USE_STRING_OBJECT
/// @}

///
/// @name 11- Storage mode
/// * Basic edition: none
/// * Evaluation edition: none
/// * Commercial edition: option
/// * Viewer edition: option
///
/// @{
#define USE_NONE 0 ///< No storage

#define STORAGE_MODE USE_NONE ///< Selected options
/// @}

///
/// @name 12- Debug options
/// * Basic edition: none
/// * Evaluation edition: all
/// * Commercial edition: option
/// * Viewer edition: option
///

#endif // hV_LIST_OPTIONS_RELEASE

