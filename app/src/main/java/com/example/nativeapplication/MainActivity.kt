package com.example.nativeapplication

import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.concat.Concat

class MainActivity : AppCompatActivity() {
    private var count = 0
    private val concat = Concat()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val resultTv = findViewById<TextView>(R.id.result_tv)
        val button = findViewById<Button>(R.id.button)

        resultTv.text = concat.concat(arrayListOf("Count: ", count.toString()))

        button.setOnClickListener {
            count++
            resultTv.text = concat.concat(arrayListOf("Count: ", count.toString()))
        }
    }
}