package com.example.concat

class Concat {
    init { System.loadLibrary("concat-jni") }
    external fun concat(args: Collection<String>): String
}
