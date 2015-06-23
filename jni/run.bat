adb push H:\users\hellokitty\TestAR\libs\armeabi\libTest.so  /sdcard/
adb push ..\libs\armeabi\libso.so  /sdcard/
adb push ..\libs\armeabi\inject /sdcard/
adb shell su  chmod 777 /sdcard/inject
adb shell su  chmod 777 /sdcard/libso.so
adb shell su  chmod 777 /sdcard/libTest.so
adb shell su -c /sdcard/inject
pause