/*
 * art.c
 *
 *  Created on: 2014Äê2ÔÂ23ÈÕ
 *      Author: Administrator
 */

#include "stdint.h"
#include "android/log.h"
#define ANDROID_SMP 0
#include "jni.h"
#include "interpreter/interpreter.h"
#include "entrypoints\interpreter\interpreter_entrypoints.h"
#include "mirror/art_method.h"
#include "MethodHooker.h"
#include "thread.h"
#define ALOG(...) __android_log_print(ANDROID_LOG_VERBOSE, __VA_ARGS__)

art::mirror::ArtMethod *GetNativeMethod(JNIEnv *jenv){
	jclass clazzTarget = jenv->FindClass("java/lang/Object");
//	if (ClearException(jenv)) {
//		ALOG("Exception","GetNativeMethod[Can't find class:%s in bootclassloader","java/lang/Object");
//	}

	jmethodID method = jenv->GetMethodID(clazzTarget,"notifyAll","()V");
	if(method==NULL){
		ALOG("Exception","GetNativeMethod[Can't find method:%s","notifyAll");
		return false;
	}
	return reinterpret_cast<art::mirror::ArtMethod*>(method);
}

bool getOffsetOfAccessFlags(art::mirror::ArtMethod* method,uint32_t *AccessFlags){
	size_t objSize = sizeof(art::mirror::ArtMethod);
	uint8_t *mem = (uint8_t*)malloc(objSize);
	art::mirror::ArtMethod *tmp = (art::mirror::ArtMethod*)mem;
	tmp->SetAccessFlags(0xAA);
	for(uint32_t i = 0 ; i < objSize ; i ++){
		uint32_t *v = (uint32_t*)(mem + i);
		if(*v == 0xAA){
			tmp->SetAccessFlags(0xBB);
			if(*v == 0xBB){
				*AccessFlags = *((uint32_t*)(((uint8_t*)method) + i));
				return true;
			}
		}
	}
	return false;
}

void Abort_(){
	art::Runtime::Abort();
}

bool HookArtMethod(JNIEnv *jenv,jmethodID jmethod){
	art::mirror::ArtMethod* method = reinterpret_cast<art::mirror::ArtMethod*>(jmethod);

	uint32_t flag;
	if(false == getOffsetOfAccessFlags(method,&flag)){
		ALOG("getOffsetOfAccessFlags","failed");
		return false;
	}

	ALOG("getOffsetOfAccessFlags_","offset:%d",flag);

	method->SetAccessFlags(flag | kAccNative);
	uint32_t new_code_off = 0;
	method->SetCodeItemOffset(new_code_off);

	method->SetEntryPointFromInterpreter(GetNativeMethod(jenv)->GetEntryPointFromInterpreter());
	//ALOG("getOffsetOfAccessFlags","code item :%d",method->GetCodeItemOffset());
	//ALOG("getOffsetOfAccessFlags","EntryPointFromInterpreter:%d",method->GetEntryPointFromInterpreter());
	//ALOG("getOffsetOfAccessFlags","GetEntryPointFromCompiledCode:%d",method->GetEntryPointFromCompiledCode());
	//ALOG("getOffsetOfAccessFlags","%d",art::artInterpreterToCompiledCodeBridge);
	return true;
}
