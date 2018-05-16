package xyz.productions.phenyl.futuroland.futuroland;

import android.content.Context;
import android.graphics.Canvas;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

/**
 * Created by Lacko on 2018. 05. 05..
 */

public class Renderer implements SurfaceHolder.Callback {
    private native void initRenderer(Surface surface);
    private native String reciveMessage();

    @Override
    public void surfaceCreated(SurfaceHolder surfaceHolder) {
        Surface render=surfaceHolder.getSurface();
        initRenderer(render);
    }

    @Override
    public void surfaceChanged(SurfaceHolder surfaceHolder, int i, int i1, int i2) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {

    }
}
