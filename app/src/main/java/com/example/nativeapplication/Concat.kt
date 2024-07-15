package com.example.nativeapplication

object Concat {
    init { System.loadLibrary("concat") }
    external fun concat(args: Collection<String>): String
}