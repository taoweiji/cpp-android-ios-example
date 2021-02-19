package com.cross.example;


import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

import com.cross.Cross;

public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Cross.initXLog(this);
        setContentView(R.layout.activity_main);
        TextView textView = findViewById(R.id.textView);
        textView.setText(new Cross().stringFromJNI());
    }
}
