# SDK for the LED Light-Bar on the IEI based Android OS

****
## Contents
* [Overview](#Overview)
* [JNI Library API definition](#JNI_API)
    * setLightBarUserLED
    * setLightBarBreathMode
    * setLightBarHeartBeatMode
    * setLightBarPowerLedSuspendColor
    * setLightBarPowerLedPoweroffState
* [How to import to Android Studio](#JNI_IMPORT)
    * Import to CMAKE configuration
    * For a Java project
    * For a Kotlin project
    * About Security 


* [Frequently Questions](#QA)


****
### Overview
-----------
This documentation is focus on JNI API definition of Light-Bar control for IEI IASO-W10B-IMX8M product.
Users can import this JNI library and calling API to implement selfs own apps, so we also provide an instruction about how to import library.

**Support Hardware: IASO-W10B-IMX8M**

API Features:
* Setting color for one set USER LED with 65535 colors
* Setting Two light-bar as breath mode with a specific color
* Setting Two light-bar as wave mode with a specific color
* Setting a specific blinking color of suspend mode for POWER LED
* Setting 'turn on' or 'turn off' red color for POWER LD in power-off mode
