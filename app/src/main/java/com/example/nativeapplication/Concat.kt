package com.example.nativeapplication

object Concat {
    init { System.loadLibrary("concat-jni") }
    external fun concat(args: Collection<String>): String
}