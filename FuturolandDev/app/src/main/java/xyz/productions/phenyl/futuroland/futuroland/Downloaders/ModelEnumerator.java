package xyz.productions.phenyl.futuroland.futuroland.Downloaders;

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
import java.util.Iterator;
import java.util.LinkedList;

//2018. 05. 21..

public class ModelEnumerator extends AsyncTask<String,Void,String[]> {
    Context ctx;
    public ModelEnumerator(Context ctx){
        this.ctx=ctx;
    }
    @Override
    protected String[] doInBackground(String... strings) {
        URL modelList=null;
        LinkedList<String> list=new LinkedList<String>();
        try {
            modelList=new URL(strings[0]);
            HttpURLConnection connection= (HttpURLConnection) modelList.openConnection();
            connection.setDoOutput(false);
            connection.setReadTimeout(5000);
            connection.connect();
            BufferedReader reader=new BufferedReader(new InputStreamReader(connection.getInputStream()));
            String line=reader.readLine();
            while(line!=null){
                list.add(line);
                line=reader.readLine();
            }
            reader.close();
            connection.disconnect();
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println(ctx.getFilesDir());
        File file=new File(ctx.getFilesDir().toString()+"/models");
        if(!file.exists()){
            if(!file.mkdir()){
                Log.e("dirs","models directory not created.");
            }
        }

        String modelNames[]=new String[list.size()];
        int at=0;
        for (String model : list) {
            modelNames[at] = model;
            at++;
        }
        return modelNames;
    }
}
