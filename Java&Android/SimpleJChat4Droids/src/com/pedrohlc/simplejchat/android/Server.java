package com.pedrohlc.simplejchat.android;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

public class Server extends Activity {
	
	protected static Server i = null;
	protected static ServerReception r = null;
	
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Server.i = this;
        Server.r = new ServerReception();
        Intent intent = new Intent(this, Client.class).setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
    	startActivity(intent);
	}
	
	public static void sendForAll(String message){
		r.sendForAll(message);
	}
	
	@Override
	public void onDestroy(){
		if(r != null)
			r.destroy();
		super.onDestroy();
		System.exit(0);
	}
}
