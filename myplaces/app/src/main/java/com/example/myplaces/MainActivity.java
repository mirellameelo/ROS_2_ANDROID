package com.example.myplaces;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {

    Button conection;
    Socket s;
    PrintWriter writer;
    TextView number;
    int i = 0;
    String mens;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        conection = (Button) findViewById(R.id.conection);
        number = (TextView) findViewById(R.id.number);

        onBtnClick();
    }


    public void onBtnClick() {

        conection.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                BackGroundTask b1 = new BackGroundTask();
                b1.execute();
            }

        });

    }

    class BackGroundTask extends AsyncTask<String, Void, Void> {

        Handler h = new Handler();
        @Override
        protected Void doInBackground(String... voids) {
            try {
                //String msg = voids[0];
                mens = String.valueOf(i);

                if(s == null){
                    s = new Socket("172.22.41.37",6000);
                    writer = new PrintWriter(s.getOutputStream());
                }
                writer.write(mens);
                writer.flush();
                //writer.close();
                i = i+1;
                Log.i("i", "CONNECTED");
                h.post(new Runnable() {
                    @Override
                    public void run() {
                        //Toast toast = Toast.makeText(getApplicationContext(), mens, Toast.LENGTH_SHORT);
                        //toast.show();
                        number.setText(mens);
                    }
                });
            }
            catch (IOException e) {
                e.printStackTrace();
            }
            return null;
        }
    }
}
