package com.cross;

public class Cross {
    static {
        System.loadLibrary("cross");
    }
    public static native String signatureUrl(String url);
}
