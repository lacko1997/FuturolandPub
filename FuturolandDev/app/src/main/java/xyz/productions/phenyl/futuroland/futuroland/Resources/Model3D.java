package xyz.productions.phenyl.futuroland.futuroland.Resources;

/**
 * Created by Lacko on 2018. 05. 21..
 */

public class Model3D {
    public Model3D(float data[],short index_data[]){
        modelData(data,index_data);
    }
    private native void modelData(float data[],short index_data[]);
}
