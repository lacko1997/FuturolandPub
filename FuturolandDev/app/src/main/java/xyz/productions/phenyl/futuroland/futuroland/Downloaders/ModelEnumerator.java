package xyz.productions.phenyl.futuroland.futuroland.Downloaders;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.LinkedList;

//2018. 05. 21..

public class ModelEnumerator extends AsyncTask<String,Void,String[][]> {
    private Context ctx;
    public ModelEnumerator(Context ctx){
        this.ctx=ctx;
    }
    @Override
    protected String[][] doInBackground(String... strings) {
        URL modelList = null;
        LinkedList<String> static_modell = new LinkedList<String>();
        LinkedList<String> animated_model = new LinkedList<String>();
        try {
            modelList = new URL(strings[0]);
            HttpURLConnection connection = (HttpURLConnection) modelList.openConnection();
            connection.setDoOutput(false);
            connection.setReadTimeout(5000);
            connection.connect();
            BufferedReader reader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            String line = reader.readLine();
            while (line != null) {
                String items[] = line.split(" ");
                if (items[0].equals("static")) {
                    static_modell.add(items[1]);
                } else if (items[1].equals("animated")) {
                    animated_model.add(items[1]);
                }
                line = reader.readLine();
            }
            reader.close();
            connection.disconnect();
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println(ctx.getFilesDir());
        File file = new File(ctx.getFilesDir().toString() + "/models");
        if (!file.exists()) {
            if (file.mkdir()) {
                File stmodells=new File(file.toString()+"/static");
                File anmodells=new File(file.toString()+"/animated");
                if(!stmodells.mkdir()||!anmodells.mkdir()){
                    Log.e("dirs","animated model directory could net be created");
                }
            }else{
                Log.e("dirs", "models directory not created.");
            }
        }

        String modelNames[][] = new String[3][];
        modelNames[0] = new String[static_modell.size()];
        modelNames[1] = new String[static_modell.size()];
        modelNames[2] =new String[2];

        modelNames[2][0]=file.toString()+"/static";
        modelNames[2][1]=file.toString()+"/animated";
        int at = 0;
        for (String model : static_modell) {
            modelNames[0][at] = model;
            at++;
        }
        for (String model : static_modell) {
            modelNames[0][at] = model;
            at++;
        }
        return modelNames;
    }
}
