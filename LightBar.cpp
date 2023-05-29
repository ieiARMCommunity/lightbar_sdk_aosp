//
// IEI World Corp.
// Created by Wig Cheng on 2023/5/3
// Revision: v1.0
//
#include <jni.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <android/log.h>

#define LOG_TAG "ieilightbar"
static char *BAR_PATH_1 = "/sys/bus/i2c/drivers/tlc591xx/1-0060/leds";
static char *BAR_PATH_2 = "/sys/bus/i2c/drivers/tlc591xx/3-0060/leds";

extern "C"
JNIEXPORT void JNICALL
Java_com_ieiworld_testprogram_1prebuilt_1lightbar_NativeMethods_setLightBarUserLED(JNIEnv *env,
                                                                             jobject thiz,
                                                                             jint bar_num,
                                                                             jint led_num,
                                                                             jint red_brightness,
                                                                             jint green_brightness,
                                                                             jint blue_brightness) {
    char *BAR_PATH = (char*)NULL;
    char FINAL_PATH[128] = {0};
    char RED_BRIGHTNESS[4] = {0};
    char GREEN_BRIGHTNESS[4] = {0};
    char BLUE_BRIGHTNESS[4] = {0};
    int file_fd = 0;

    /* Setting bar_num path */
    if(bar_num == 1) {
        BAR_PATH="/sys/bus/i2c/drivers/tlc591xx/1-0060/leds";
    } else if(bar_num == 2) {
        BAR_PATH="/sys/bus/i2c/drivers/tlc591xx/3-0060/leds";
    } else {
        return;
    }

    /* Setting red color with brightness */
    sprintf(FINAL_PATH, "%s/i2c%d_led_red_%02d/brightness", BAR_PATH, bar_num * 2, (led_num-1));
    file_fd = open(FINAL_PATH,O_RDWR);

    if(file_fd < 0) {
        return;
    }
    sprintf(RED_BRIGHTNESS, "%d", red_brightness);
    write(file_fd, RED_BRIGHTNESS, strlen(RED_BRIGHTNESS));
    close(file_fd);


    /* Setting green color with brightness */
    memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
    sprintf(FINAL_PATH, "%s/i2c%d_led_green_%02d/brightness", BAR_PATH, bar_num * 2, (led_num-1));
    file_fd = open(FINAL_PATH,O_RDWR);

    if(file_fd < 0) {
        return;
    }
    sprintf(GREEN_BRIGHTNESS, "%d", green_brightness);
    write(file_fd, GREEN_BRIGHTNESS, strlen(GREEN_BRIGHTNESS));
    close(file_fd);


    /* Setting blue color with brightness */
    memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
    sprintf(FINAL_PATH, "%s/i2c%d_led_blue_%02d/brightness", BAR_PATH, bar_num * 2, (led_num-1));
    file_fd = open(FINAL_PATH,O_RDWR);

    if(file_fd < 0) {
        return;
    }
    sprintf(BLUE_BRIGHTNESS, "%d", blue_brightness);
    write(file_fd, BLUE_BRIGHTNESS, strlen(BLUE_BRIGHTNESS));
    close(file_fd);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ieiworld_testprogram_1prebuilt_1lightbar_NativeMethods_clearLightBarLED(JNIEnv *env, jobject thiz) {


    char *BRIGHTNESS = "0";
    char FINAL_PATH[128] = {0};
    int led_cnt;
    int file_fd = 0;

    /* clear red status */
    for(led_cnt = 0; led_cnt < 4; led_cnt++) {
        // bar-1
        memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
        sprintf(FINAL_PATH, "%s/i2c2_led_red_%02d/brightness", BAR_PATH_1, led_cnt);

        file_fd = open(FINAL_PATH,O_RDWR);
        if(file_fd < 0) {
            return;
        }
        write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
        close(file_fd);

        // bar-2
        memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
        sprintf(FINAL_PATH, "%s/i2c4_led_red_%02d/brightness", BAR_PATH_2, led_cnt);

        file_fd = open(FINAL_PATH,O_RDWR);
        if(file_fd < 0) {
            return;
        }
        write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
        close(file_fd);
    }


    // clear green status
    for(led_cnt = 0; led_cnt < 4; led_cnt++) {
        // bar-1
        memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
        sprintf(FINAL_PATH, "%s/i2c2_led_green_%02d/brightness", BAR_PATH_1, led_cnt);

        file_fd = open(FINAL_PATH,O_RDWR);
        if(file_fd < 0) {
            return;
        }
        write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
        close(file_fd);

        // bar-2
        memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
        sprintf(FINAL_PATH, "%s/i2c4_led_green_%02d/brightness", BAR_PATH_2, led_cnt);

        file_fd = open(FINAL_PATH,O_RDWR);
        if(file_fd < 0) {
            return;
        }
        write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
        close(file_fd);
    }

    // clear blue status
    for(led_cnt = 0; led_cnt < 4; led_cnt++) {
        // bar-1
        memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
        sprintf(FINAL_PATH, "%s/i2c2_led_blue_%02d/brightness", BAR_PATH_1, led_cnt);

        file_fd = open(FINAL_PATH,O_RDWR);
        if(file_fd < 0) {
            return;
        }
        write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
        close(file_fd);

        // bar-2
        memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
        sprintf(FINAL_PATH, "%s/i2c4_led_blue_%02d/brightness", BAR_PATH_2, led_cnt);

        file_fd = open(FINAL_PATH,O_RDWR);
        if(file_fd < 0) {
            return;
        }
        write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
        close(file_fd);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ieiworld_testprogram_1prebuilt_1lightbar_NativeMethods_setLightBarBreathMode(JNIEnv *env,
                                                                                      jobject thiz,
                                                                                          jstring specific_color
                                                                                      ) {
    char BRIGHTNESS[4] = {0};
    char FINAL_PATH[128] = {0};
    const int max_brightness = 100;
    const char *target_color_str = env->GetStringUTFChars(specific_color, 0);
    int led_cnt, brightness_cnt, loop_counter;
    int red_flag, green_flag, blue_flag;
    int file_fd = 0;

    if(strcmp(target_color_str, "red") == 0) {
        red_flag = 1;
        green_flag = 0;
        blue_flag = 0;
        loop_counter = 1;
    } else if(strcmp(target_color_str, "green") == 0) {
        red_flag = 0;
        green_flag = 1;
        blue_flag = 0;
        loop_counter = 1;
    } else if(strcmp(target_color_str, "blue") == 0) {
        red_flag = 0;
        green_flag = 0;
        blue_flag = 1;
        loop_counter = 1;
    } else if(strcmp(target_color_str, "yellow") == 0) {
        red_flag = 1;
        green_flag = 1;
        blue_flag = 0;
        loop_counter = 2;
    } else if(strcmp(target_color_str, "cyan") == 0) {
        red_flag = 0;
        green_flag = 1;
        blue_flag = 1;
        loop_counter = 2;
    } else if(strcmp(target_color_str, "magenta") == 0) {
        red_flag = 1;
        green_flag = 0;
        blue_flag = 1;
        loop_counter = 2;
    } else if(strcmp(target_color_str, "white") == 0) {
        red_flag = 1;
        green_flag = 1;
        blue_flag = 1;
        loop_counter = 4;
    } else {
        red_flag = 0;
        green_flag = 0;
        blue_flag = 1;
        loop_counter = 1;
    }

    for(brightness_cnt = 0; brightness_cnt <= max_brightness; brightness_cnt+=loop_counter) {
        for(led_cnt = 0; led_cnt < 4; led_cnt++) {

            if(red_flag == 1) {
                // bar-1
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c2_led_red_%02d/brightness", BAR_PATH_1, led_cnt);

                file_fd = open(FINAL_PATH,O_RDWR);
                if(file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                sprintf(BRIGHTNESS, "%d", brightness_cnt);

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);

                // bar-2
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c4_led_red_%02d/brightness", BAR_PATH_2, led_cnt);

                file_fd = open(FINAL_PATH,O_RDWR);
                if(file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                sprintf(BRIGHTNESS, "%d", brightness_cnt);

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);
            }

            if(green_flag == 1) {
                // bar-1
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c2_led_green_%02d/brightness", BAR_PATH_1, led_cnt);

                file_fd = open(FINAL_PATH,O_RDWR);
                if(file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                sprintf(BRIGHTNESS, "%d", brightness_cnt);

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);

                // bar-2
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c4_led_green_%02d/brightness", BAR_PATH_2, led_cnt);

                file_fd = open(FINAL_PATH,O_RDWR);
                if(file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                sprintf(BRIGHTNESS, "%d", brightness_cnt);

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);
            }

            if(blue_flag == 1) {
                // bar-1
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c2_led_blue_%02d/brightness", BAR_PATH_1, led_cnt);

                file_fd = open(FINAL_PATH,O_RDWR);
                if(file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                sprintf(BRIGHTNESS, "%d", brightness_cnt);

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);

                // bar-2
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c4_led_blue_%02d/brightness", BAR_PATH_2, led_cnt);

                file_fd = open(FINAL_PATH,O_RDWR);
                if(file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                sprintf(BRIGHTNESS, "%d", brightness_cnt);

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);
            }
        }
        usleep(500);
    }

    for(brightness_cnt = max_brightness; brightness_cnt >= 0; brightness_cnt-=loop_counter) {
        for(led_cnt = 0; led_cnt < 4; led_cnt++) {
            // bar-1
            // red
            if (red_flag == 1) {
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c2_led_red_%02d/brightness", BAR_PATH_1, led_cnt);

                file_fd = open(FINAL_PATH, O_RDWR);
                if (file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                sprintf(BRIGHTNESS, "%d", brightness_cnt);

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);

                // bar-2
                // red
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c4_led_red_%02d/brightness", BAR_PATH_2, led_cnt);

                file_fd = open(FINAL_PATH, O_RDWR);
                if (file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                sprintf(BRIGHTNESS, "%d", brightness_cnt);

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);

            }

            // green
            if (green_flag == 1) {
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c2_led_green_%02d/brightness", BAR_PATH_1, led_cnt);

                file_fd = open(FINAL_PATH, O_RDWR);
                if (file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                sprintf(BRIGHTNESS, "%d", brightness_cnt);

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);

                // bar-2
                // green
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c4_led_green_%02d/brightness", BAR_PATH_2, led_cnt);

                file_fd = open(FINAL_PATH, O_RDWR);
                if (file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                sprintf(BRIGHTNESS, "%d", brightness_cnt);

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);

            }

            // blue
            if (blue_flag == 1) {
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c2_led_blue_%02d/brightness", BAR_PATH_1, led_cnt);

                file_fd = open(FINAL_PATH, O_RDWR);
                if (file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                sprintf(BRIGHTNESS, "%d", brightness_cnt);

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);

                // bar-2
                // blue
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c4_led_blue_%02d/brightness", BAR_PATH_2, led_cnt);

                file_fd = open(FINAL_PATH, O_RDWR);
                if (file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                sprintf(BRIGHTNESS, "%d", brightness_cnt);

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);

            }
        }
        usleep(500);
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_ieiworld_testprogram_1prebuilt_1lightbar_NativeMethods_setLightBarWaveMode(JNIEnv *env,
                                                                                      jobject thiz,
                                                                                    jstring specific_color) {
    char BRIGHTNESS[4] = {0};
    char FINAL_PATH[128] = {0};
    const int max_brightness = 100;
    int led_cnt, wav_cnt, loop_counter;
    const char *target_color_str = env->GetStringUTFChars(specific_color, 0);
    int red_flag, green_flag, blue_flag;
    int file_fd = 0;

    if(strcmp(target_color_str, "red") == 0) {
        red_flag = 1;
        green_flag = 0;
        blue_flag = 0;
        loop_counter = 1;
    } else if(strcmp(target_color_str, "green") == 0) {
        red_flag = 0;
        green_flag = 1;
        blue_flag = 0;
        loop_counter = 1;
    } else if(strcmp(target_color_str, "blue") == 0) {
        red_flag = 0;
        green_flag = 0;
        blue_flag = 1;
        loop_counter = 1;
    } else if(strcmp(target_color_str, "yellow") == 0) {
        red_flag = 1;
        green_flag = 1;
        blue_flag = 0;
        loop_counter = 2;
    } else if(strcmp(target_color_str, "cyan") == 0) {
        red_flag = 0;
        green_flag = 1;
        blue_flag = 1;
        loop_counter = 2;
    } else if(strcmp(target_color_str, "magenta") == 0) {
        red_flag = 1;
        green_flag = 0;
        blue_flag = 1;
        loop_counter = 2;
    } else if(strcmp(target_color_str, "white") == 0) {
        red_flag = 1;
        green_flag = 1;
        blue_flag = 1;
        loop_counter = 4;
    } else {
        red_flag = 0;
        green_flag = 0;
        blue_flag = 1;
        loop_counter = 1;
    }


    for(wav_cnt = 0; wav_cnt < 4; wav_cnt++) {
        for(led_cnt = 0; led_cnt < 4; led_cnt++) {

            //red
            if (red_flag == 1) {
                // bar-1
                // red
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c2_led_red_%02d/brightness", BAR_PATH_1, led_cnt);

                file_fd = open(FINAL_PATH, O_RDWR);
                if (file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                if (wav_cnt == led_cnt)
                    sprintf(BRIGHTNESS, "%d", max_brightness);
                else
                    sprintf(BRIGHTNESS, "0");

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);

                // bar-2

                // red
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c4_led_red_%02d/brightness", BAR_PATH_2, led_cnt);

                file_fd = open(FINAL_PATH, O_RDWR);
                if (file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                if (wav_cnt == led_cnt)
                    sprintf(BRIGHTNESS, "%d", max_brightness);
                else
                    sprintf(BRIGHTNESS, "0");

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);
            }

            // green
            if (green_flag == 1) {
                // bar-1
                // red
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c2_led_green_%02d/brightness", BAR_PATH_1, led_cnt);

                file_fd = open(FINAL_PATH, O_RDWR);
                if (file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                if (wav_cnt == led_cnt)
                    sprintf(BRIGHTNESS, "%d", max_brightness);
                else
                    sprintf(BRIGHTNESS, "0");

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);

                // bar-2

                // red
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c4_led_green_%02d/brightness", BAR_PATH_2, led_cnt);

                file_fd = open(FINAL_PATH, O_RDWR);
                if (file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                if (wav_cnt == led_cnt)
                    sprintf(BRIGHTNESS, "%d", max_brightness);
                else
                    sprintf(BRIGHTNESS, "0");

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);
            }

            // blue
            if (blue_flag == 1) {
                // bar-1
                // red
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c2_led_blue_%02d/brightness", BAR_PATH_1, led_cnt);

                file_fd = open(FINAL_PATH, O_RDWR);
                if (file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                if (wav_cnt == led_cnt)
                    sprintf(BRIGHTNESS, "%d", max_brightness);
                else
                    sprintf(BRIGHTNESS, "0");

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);

                // bar-2

                // red
                memset(FINAL_PATH, 0, sizeof(FINAL_PATH));
                sprintf(FINAL_PATH, "%s/i2c4_led_blue_%02d/brightness", BAR_PATH_2, led_cnt);

                file_fd = open(FINAL_PATH, O_RDWR);
                if (file_fd < 0) {
                    return;
                }
                memset(BRIGHTNESS, 0, sizeof(BRIGHTNESS));
                if (wav_cnt == led_cnt)
                    sprintf(BRIGHTNESS, "%d", max_brightness);
                else
                    sprintf(BRIGHTNESS, "0");

                write(file_fd, BRIGHTNESS, strlen(BRIGHTNESS));
                close(file_fd);
            }
        }
        usleep(300000);
    }
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_ieiworld_testprogram_1prebuilt_1lightbar_NativeMethods_setLightBarPowerLedSuspendColor(JNIEnv *env,
                                                                                    jobject thiz,
                                                                                    jstring specific_color) {

    const char *target_color_str = env->GetStringUTFChars(specific_color, 0);
    FILE *ps;
    char FINAL_CMD[64]={0};

    if(strcmp(target_color_str, "red") && strcmp(target_color_str, "green") && strcmp(target_color_str, "blue")
    && strcmp(target_color_str, "yellow") && strcmp(target_color_str, "cyan") && strcmp(target_color_str, "magenta")
    && strcmp(target_color_str, "white"))
        return 1;

    sprintf(FINAL_CMD, "fw_setenv leds.suspend_color %s", target_color_str);

    if((ps = popen(FINAL_CMD, "w")) == NULL ) {
        __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "popen failed");
        return 1;
    }

    pclose(ps);

    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_ieiworld_testprogram_1prebuilt_1lightbar_NativeMethods_setLightBarPowerLedPoweroffState(JNIEnv *env,
                                                                                                jobject thiz,
                                                                                                jstring on_flag) {
    const char *target_onoff_str = env->GetStringUTFChars(on_flag, 0);
    FILE *ps;
    char FINAL_CMD[64]={0};

    if(strcmp(target_onoff_str, "on") && strcmp(target_onoff_str, "off"))
        return 1;

    sprintf(FINAL_CMD, "fw_setenv leds.poweroff_state %s", target_onoff_str);

    if((ps = popen(FINAL_CMD, "w")) == NULL ) {
        __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "popen failed");
        return 1;
    }

    pclose(ps);

    return 0;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_ieiworld_testprogram_1prebuilt_1lightbar_NativeMethods_getLightBarPowerLedStatus(JNIEnv *env,
                                                                                          jobject thiz,
                                                                                          jstring mode) {
    const char *target_mode_str = env->GetStringUTFChars(mode, 0);
    FILE *ps;
    char FINAL_CMD[64]={0}, MODE_BUF[32] = {0};
    char GETS_BUF[32]={0}, RET_BUF[8] = {0};

    if(strcmp(target_mode_str, "suspend") == 0)
        sprintf(MODE_BUF, "leds.suspend_color");
    else if(target_mode_str, "poweroff")
        sprintf(MODE_BUF, "leds.poweroff_state");
    else
        return env->NewStringUTF("fail input parameter");

    sprintf(FINAL_CMD, "fw_printenv %s", MODE_BUF);

    if((ps = popen(FINAL_CMD, "r")) == NULL )
        __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "popen failed");

    fgets(GETS_BUF, sizeof(GETS_BUF),ps);

    if(strcmp(target_mode_str, "suspend") == 0)
        sscanf(GETS_BUF,"leds.suspend_color=%s", &RET_BUF);
    else if(strcmp(target_mode_str, "poweroff") == 0)
        sscanf(GETS_BUF,"leds.poweroff_state=%s", &RET_BUF);

    pclose(ps);

    return env->NewStringUTF(RET_BUF);
}

