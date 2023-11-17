///
/// @file hV_List_Options.h
/// @brief List of options for Pervasive Displays Library Suite
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @n Content
/// * 3- Font mode, internal MCU or external SPI Flash
/// * 4- Maximum number of fonts
/// * 5- SRAM memory, internal MCU or external SPI
/// * 6- Use self or virtual object
/// * 7- Touch mode, activated or not
/// * 8- Haptic feedback mode, activated or not
/// * 9. Set GPIO expander mode, not implemented
/// * 10. String object of char array options for string.
/// * 11. Set storage mode, serial console by default
///
/// @author Rei Vilo
/// @date 21 Oct 2023
/// @version 701
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

#ifndef hV_LIST_OPTIONS_RELEASE
///
/// @brief Release
///
#define hV_LIST_OPTIONS_RELEASE 701

///
/// @name 3- Set font mode
/// @details From header files or from external flash
/// * Basic edition: Terminal font
/// * Evaluation edition: DejaVu font as header
/// * Commercial edition: DejaVu font as either header or external SPI Flash
/// @note USE_FONT_HEADER requires addFont()
/// @note Font Manager requires USE_FONT_HEADER
/// @warning 8- and 16-bit MCUs may limit the size of the fonts. Use 32-bit MCUs for optimal performance.
///
/// @{
#define USE_FONT_TERMINAL 1 ///< Use default Terminal fonts
#define USE_FONT_HEADER 2 ///< Use fonts from header files
#define USE_FONT_FLASH 3 ///< Use fonts from external SPI Flash memory
#define USE_FONT_INTERNAL 4 ///< Use fonts from internal CGU

#define FONT_MODE USE_FONT_HEADER ///< Selected option
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
///
/// @{
#define USE_INTERNAL_MCU 1 ///< Use MCU internal
#define USE_EXTERNAL_SPI 2 ///< Use SPI External

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
/// @note Recommended: USE_hV_SCREEN_VIRTUAL
/// @warning Issues with virtual function on arm-none-eabi-g++ 4.9.3: use USE_hV_SCREEN_SELF instead.
/// @{
#define USE_hV_SCREEN_VIRTUAL 1 ///< Use virtual object
#define USE_hV_SCREEN_SELF 2 ///< Do not use virtual object

#define USE_hV_SCREEN USE_hV_SCREEN_VIRTUAL ///< Selected option
/// @}

///
/// @name 7- Set touch mode
/// @details Only two screens are ready for touch
/// * Basic edition: iTC 2.71 BW and iTC 3.70 BW
/// * Evaluation edition: iTC 2.71 BW and iTC 3.70 BW
/// * Commercial edition: iTC 2.71 BW and iTC 3.70 BW
/// @note Touch uses I2C and polling over interrupt
/// @{
#define USE_TOUCH_NONE 0 ///< Do not use touch
#define USE_TOUCH_YES 1 ///< Use touch

#define TOUCH_MODE USE_TOUCH_YES ///< Selected option
/// @}

///
/// @brief 8- Set haptic feedback mode
/// * Basic edition: no haptic feedback
/// * Evaluation edition: ERM or LRA
/// * Commercial edition: ERM or LRA
///
/// @{
#define USE_HAPTICS_NONE 0 ///< No motor
#define USE_DRV2605L_ERM 1 ///< DRV2605L with ERM = eccentric rotating mass
#define USE_DRV2605L_LRA 2 ///< DRV2605L with LRA = linear resonant actuator

#define HAPTICS_MODE USE_HAPTICS_NONE ///< Selected option
/// @}

///
/// @brief 9- Set GPIO expander mode
/// * Basic edition: no expander
/// * Evaluation edition: PCF8574 or PCA9536
/// * Commercial edition: PCF8574 or PCA9536
///
/// @{
#define USE_EXPANDER_NONE 0 ///< No I2C expander
#define USE_I2C_PCF8574 1 ///< PCF8574 8 ports GPIO I2C 100 kHz expander
#define USE_I2C_PCA9536 2 ///< PCA9536 4 ports GPIO I2C 400 kHz expander
#define USE_I2C_TCA6408 3 ///< TCA6408 8 ports GPIO I2C 400 kHz expander

#define EXPANDER_MODE USE_EXPANDER_NONE ///< Selected option
/// @}

///
/// @brief 10- Set string mode
/// * Basic edition: String object
/// * Evaluation edition: char array
/// * Commercial edition: String object or char array
///
/// @{
#define USE_STRING_OBJECT 1
#define USE_CHAR_ARRAY 2

#define STRING_MODE USE_CHAR_ARRAY
/// @}

///
/// @brief 11- Storage mode
/// * Basic edition: none
/// * Evaluation edition: none
/// * Commercial edition: option
///
/// @note Options can be combined
/// @code {.cpp}
/// #define STORAGE_MODE (USE_SD_CARD | USE_SPI_FLASH)
/// #define STORAGE_MODE (USE_LINUX_FILES | USE_SERIAL_CONSOLE)
/// @endcode
///
/// @{
#define USE_NONE 0 ///< No storage
#define USE_SD_CARD 1 ///< SD card
#define USE_SPI_FLASH 2 ///< External SPI Flash
#define USE_SERIAL_CONSOLE 4 ///< Serial console for writing only
#define USE_LINUX_FILES 8 ///< For Linux native applications

#define STORAGE_MODE USE_SERIAL_CONSOLE ///< Selected options
/// @}

#endif // hV_LIST_OPTIONS_RELEASE
