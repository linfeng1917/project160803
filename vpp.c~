#!/bin/bash
set -x
make tree_clean V=android_Release
make tree_clean V=hexagon_Release_dynamic_toolv72_v60
make tree V=hexagon_Release_dynamic_toolv72_v60
make tree V=android_Release
#adb root
#adb wait-for-device
#adb remount
adb push android_Release/ship/libitm_qcom_hvx_test /data/local
adb push android_Release/ship/libitm_qcom_hvx_test.so /data/local
adb push hexagon_Release_dynamic_toolv72_v60/ship/libitmo_skel.so /vendor/lib/rfsa/adsp
#adb wait-for-device
#adb shell sync
#adb remount





