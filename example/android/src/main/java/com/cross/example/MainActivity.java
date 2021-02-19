package com.cross.example;


import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

import com.cross.Cross;

public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView textView = findViewById(R.id.textView);
        String url = "http://example.com?key2=value2&key3=value3&key1=VALUE1";
        String result = Cross.signatureUrl(url);
        textView.setText(url + "\n" + result);
    }
}
