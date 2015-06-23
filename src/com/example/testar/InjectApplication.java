package com.example.testar;

import java.lang.reflect.Method;

import android.app.Application;
import android.util.Log;

public class InjectApplication extends Application {
	static {
		System.loadLibrary("so");
	}

	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		//test();
		super.onCreate();
	}

	public native String test();
}
