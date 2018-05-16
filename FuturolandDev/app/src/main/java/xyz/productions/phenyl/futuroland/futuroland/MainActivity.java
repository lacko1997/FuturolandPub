package xyz.productions.phenyl.futuroland.futuroland;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.SurfaceView;
import android.widget.FrameLayout;
import android.widget.TextView;

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

        surface.getHolder().addCallback(render);
    }
}
