package xyz.productions.phenyl.futuroland.futuroland.Downloaders;

import android.content.Context;
import android.os.AsyncTask;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.SocketTimeoutException;
import java.net.URL;
import java.util.ArrayList;
import java.util.LinkedList;

import xyz.productions.phenyl.futuroland.futuroland.Resources.Model3D;

/**
 * Created by Lacko on 2018. 05. 21..
 */

public class ModelDownloader extends AsyncTask<String,Void,Integer>{
    Context ctx;
    public ModelDownloader(Context ctx){
        this.ctx=ctx;
    }

    @Override
    protected Integer doInBackground(String... strings) {
        Model3D model;
        URL url;
        try {
            File modelFile=ctx.getFilesDir();
            ArrayList<Float> pos=new ArrayList<Float>();
            ArrayList<Float> tex=new ArrayList<Float>();
            ArrayList<Float> norm=new ArrayList<Float>();
            LinkedList<String> faces=new LinkedList<String>();

            url=new URL(strings[0]);
            HttpURLConnection conn= (HttpURLConnection) url.openConnection();
            conn.setConnectTimeout(5000);
            conn.setReadTimeout(5000);
            conn.connect();

            BufferedReader reader=new BufferedReader(new InputStreamReader(conn.getInputStream()));
            String line=reader.readLine();
            while(line!=null){
                if(line.startsWith("v ")){
                    String attr[]=line.split(" ");
                    pos.add(Float.parseFloat(attr[1]));
                    pos.add(Float.parseFloat(attr[2]));
                    pos.add(Float.parseFloat(attr[3]));
                }else if(line.startsWith("vn ")){
                    String attr[]=line.split(" ");
                    tex.add(Float.parseFloat(attr[1]));
                    tex.add(Float.parseFloat(attr[2]));
                }else if(line.startsWith("vt ")){
                    String attr[]=line.split(" ");
                    norm.add(Float.parseFloat(attr[1]));
                    norm.add(Float.parseFloat(attr[2]));
                    norm.add(Float.parseFloat(attr[3]));
                }else if(line.startsWith("f ")){
                    faces.add(line);
                }

                line=reader.readLine();
            }
            float data[]=new float[8*(pos.size()/3)];
            for(int i=0;i<pos.size()/3;i++){
                data[i*8]=pos.get(i*3);
                data[i*8+1]=pos.get(i*3+1);
                data[i*8+2]=pos.get(i*3+2);
            }
            LinkedList<Short> index=new LinkedList<Short>();
            for (String face : faces) {
                String elements[] = face.split(" ");
                for (int i = 1; i < 4; i++) {
                    String inds[] = elements[i].split("/");
                    short pos_ind = Short.parseShort(inds[0]);
                    short tex_ind = Short.parseShort(inds[1]);
                    short norm_ind = Short.parseShort(inds[2]);

                    data[pos_ind * 8 + 3] = tex.get(tex_ind * 2);
                    data[pos_ind * 8 + 4] = tex.get(tex_ind * 2 + 1);

                    data[pos_ind * 8 + 5] = norm.get(norm_ind * 3);
                    data[pos_ind * 8 + 6] = norm.get(norm_ind * 3 + 1);
                    data[pos_ind * 8 + 7] = norm.get(norm_ind * 3 + 2);

                    index.add(pos_ind);
                }
            }
            short index_data[]=new short[index.size()];
            int at=0;
            for(short ind:index){
                index_data[at]=ind;
                at++;
            }
            model=new Model3D(data,index_data);
            return 0;
        } catch (MalformedURLException e) {
            return -1;
        }catch(SocketTimeoutException ex){
            return -2;
        }catch (IOException e) {
            return -3;
        }
    }
}
