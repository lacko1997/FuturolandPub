package xyz.productions.phenyl.futuroland.futuroland;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceView;
import android.widget.FrameLayout;
import android.widget.TextView;

import xyz.productions.phenyl.futuroland.futuroland.Downloaders.ModelEnumerator;
import xyz.productions.phenyl.futuroland.futuroland.Utils.Hasher;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("native-lib");
    }

    Renderer render=new Renderer();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        SurfaceView surface=findViewById(R.id.renderer);
        TextView text=findViewById(R.id.sample_text);

        Hasher hasher=new Hasher("265a06261153216");
        Log.e("hash",hasher.getHash());

        surface.getHolder().addCallback(render);
        Log.e("files",getFilesDir().toString());
        new ModelEnumerator(this).execute("futuroland");
    }

    private native void start();
    private native void pause();
    private native void stop();

    @Override
    protected void onStart() {
        super.onStart();
    }

    @Override
    protected void onPause() {
        super.onPause();
        pause();
    }

    protected void onResume() {
        super.onResume();
        start();
    }

    @Override
    protected void onStop() {
        super.onStop();
        stop();
    }
}
