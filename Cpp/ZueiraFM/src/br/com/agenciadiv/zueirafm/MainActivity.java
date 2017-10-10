package br.com.agenciadiv.zueirafm;

import com.spoledge.aacdecoder.AACPlayer;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity {
	public static AACPlayer player = null;
	
	protected static final String BASE = "icy://198.100.145.144:",
		HITS_PORT = "9660",
		BALADAS_PORT = "9346",
		ROCK_PORT = "9894",
		BOSTANEJO_PORT = "9314";
	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		if (player == null){
		    try {
		        java.net.URL.setURLStreamHandlerFactory( new java.net.URLStreamHandlerFactory(){
		            public java.net.URLStreamHandler createURLStreamHandler( String protocol ) {
		                if ("icy".equals( protocol )) return new com.spoledge.aacdecoder.IcyURLStreamHandler();
		                return null;
		            }
		        });
		    }
		    catch (Throwable t) {}
			
			player = new AACPlayer();
		}
		setContentView(R.layout.activity_main);
		
		((Button) findViewById(R.id.btn_start_rock)).setOnClickListener(new OnClickListener(){
			@Override public void onClick(View arg0) {
				player.stop();
				player.playAsync(BASE+ROCK_PORT);
			}});
		
		((Button) findViewById(R.id.btn_start_hits)).setOnClickListener(new OnClickListener(){
			@Override public void onClick(View arg0) {
				player.stop();
				player.playAsync(BASE+HITS_PORT);
			}});
		
		((Button) findViewById(R.id.btn_start_balada)).setOnClickListener(new OnClickListener(){
			@Override public void onClick(View arg0) {
				player.stop();
				player.playAsync(BASE+BALADAS_PORT);
			}});
		
		((Button) findViewById(R.id.btn_start_serta)).setOnClickListener(new OnClickListener(){
			@Override public void onClick(View arg0) {
				player.stop();
				player.playAsync(BASE+BOSTANEJO_PORT);
			}});
		
		((Button) findViewById(R.id.btn_stop)).setOnClickListener(new OnClickListener(){
			@Override public void onClick(View arg0) {
				player.stop();
			}});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
