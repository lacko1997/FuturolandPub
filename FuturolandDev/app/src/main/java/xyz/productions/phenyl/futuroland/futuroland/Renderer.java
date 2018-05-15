package xyz.productions.phenyl.futuroland.futuroland;

import android.content.Context;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

/**
 * Created by Lacko on 2018. 05. 05..
 */

public class Renderer extends SurfaceView {
    public Renderer(Context context) {
        super(context);
        Surface renderSurface=this.getHolder().getSurface();
        initRenderer(renderSurface);
    }
    private native void initRenderer(Surface surface);
    private native String reciveMessage();
}
