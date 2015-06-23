LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE:= so

LOCAL_SRC_FILES := so.cpp MethodHooker.cpp

LOCAL_LDLIBS+= 

LOCAL_CFLAGS    := -I./jni/include/ -I./jni/dalvik/vm/ -I./jni/dalvik -DHAVE_LITTLE_ENDIAN

LOCAL_LDFLAGS	:=	-L./jni/lib/  -L$(SYSROOT)/usr/lib -llog -ldvm -landroid_runtime  -lart

LOCAL_STATIC_LIBRARIES := hookart

LOCAL_SHARED_LIBRARIES :=
include $(BUILD_SHARED_LIBRARY)

#------------------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_MODULE:= hookart

LOCAL_SRC_FILES :=  art.cpp

LOCAL_CFLAGS    :=  -I./jni/include/ -I./jni/art-kitkat-mr1.1-release/runtime/ \
					-I./jni/gtest/include/
					
LOCAL_LDFLAGS	:=	-L./jni/lib/  -L$(SYSROOT)/usr/lib -lart

LOCAL_LDLIBS+= -llog

LOCAL_CPPFLAGS := 	-std=c++1y

LOCAL_SHARED_LIBRARIES := 

include $(BUILD_STATIC_LIBRARY)

#------------------------------------------------------------------------

include $(CLEAR_VARS)

LOCAL_MODULE:= Test

LOCAL_SRC_FILES := Test.c

LOCAL_LDLIBS+= -L./jni/lib -llog

LOCAL_CFLAGS    := -I./jni/include/ -I./jni/dalvik/vm/ -I./jni/dalvik -fPIC -shared

LOCAL_SHARED_LIBRARIES := 

include $(BUILD_SHARED_LIBRARY)

#------------------------------------------------------------------------

include $(CLEAR_VARS)

LOCAL_MODULE:= inject

LOCAL_SRC_FILES := inject.c shellcode.s

LOCAL_LDLIBS := 

LOCAL_CFLAGS :=  

include $(BUILD_EXECUTABLE)