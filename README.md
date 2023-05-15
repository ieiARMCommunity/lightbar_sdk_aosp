# SDK for the LED Light-Bar on the IEI based Android OS

****
## Contents
* [Overview](#Overview)
* [JNI Library API definition](#JNI-API)
    * setLightBarUserLED
    * clearLightBarLED
    * setLightBarBreathMode
    * setLightBarWaveMode
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



****
### <a name="JNI-API"></a>JNI Library API definition
-----------

#### setLightBarUserLED
It’s an useful API for one LED setting directly, note that calling this API can config one LED set at the same time, so user can implement a loop to calling multiple LED set such as for loop.


Prototype:
    
    setLightBarUserLED(JNIEnv *env, jobjec thiz, jint bar_num, jint led_num, jint red_brightness, jint green_brightness, jint blue_brightness)
    
    - Input argument 1: bar_num with int type
    IASO-W10B-IMX8M has two light-bars, choose 1st light-bar or 2nd light-bar is necessary, so input value is "1" or "2".
    - Input argument 2: led_num with int type
    As above figure, every red border is one LED set, so input value is the one of "1" to "4".
    - Input argument 3: red_brightness with int type
    Select red LED color, value is from "0" to "100"
    - Input argument 4: green_brightness with int type
    Select green LED color, value is from "0" to "100"
    - Input argument 5: blue_brightness with int type
    Select blue LED color, value is from "0" to "100"
   
Example: setting 2nd light-bar and LED1-1 as blue light with 100% brightness, user can calling API as follows:
   
   
    setLightBarUserLED("2", "1", "blue", "100");


#### clearLightBarLED
An useful API which can clear all USER-LED status to "turn off" status.

Prototype:
    
    clearLightBarLED(JNIEnv *env, jobject thiz)
    

#### setLightBarBreathMode
Force two light-bar into breath mode with one time period, if developer wants to running breath mode infinity, please create a service with thread first, and calling this api in a loop of thread. 

Prototype:
    
    setLightBarBreathMode(JNIEnv *env, jobject thiz, jstring specific_color)
    
    - Input argument 1: specific_color with string type
    a string prototype with color name as follows support list: “red”, “green”, “blue”, “yellow”, “cyan”, “magenta”, “white”, default color is blue
    
    
#### setLightBarWaveMode
Force two light-bar into wave mode with one time period, if developer wants to running wave mode infinity, please create a service with thread first, and calling this api in a loop of thread. 

Prototype:
    
    setLightBarWaveMode(JNIEnv *env, jobject thiz, jstring specific_color)
    
    - Input argument 1: specific_color with string type
    a string prototype with color name as follows support list: “red”, “green”, “blue”, “yellow”, “cyan”, “magenta”, “white”, default color is blue

