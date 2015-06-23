package com.example.testar;

import java.util.HashMap;
import java.util.Map;

import com.example.testar.R.id;

import android.app.Activity;
import android.content.Context;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;


public class MainActivity extends Activity {
	private final Map<String, ClassLoader> mLoaders = new HashMap<String, ClassLoader>();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		Button btn = (Button) findViewById(R.id.button1);
		final TextView textView = (TextView)findViewById(R.id.textView1);
		btn.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				WifiManager wifi = (WifiManager) getSystemService(Context.WIFI_SERVICE);
				WifiInfo info = wifi.getConnectionInfo();
				System.out.println("Wifi mac :" + info.getMacAddress());
				textView.setText(info.getMacAddress());
				// System.out.println("return " + test());
				//InjectApplication ia = (InjectApplication) getApplication();
				//System.out.println(ia.test());
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	private String test() {
		return "real";
	}
}
