package com.pedrohlc.simplejchat.android;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.TextView.OnEditorActionListener;

public class Main extends Activity {
	
	protected static Main i = null;
	protected static int port = 5000;
	protected static String ip = null;
	private EditText edtIP = null;
	private byte choosedOption = 0;
	private static boolean simple = false;
	public static boolean founded = false;
	private byte[] tryingIp = null; 
	private TextView lblOption1, lblOption2, lblOption3;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Main.i = this;
        setContentView(R.layout.main);
        //
        this.edtIP = ((EditText) findViewById(R.id.edtIP));
        this.edtIP.setImeOptions(EditorInfo.IME_ACTION_DONE);
        //
    	lblOption1 = ((TextView) findViewById(R.id.labelOption1));
    	lblOption2 = ((TextView) findViewById(R.id.labelOption2));
    	lblOption3 = ((TextView) findViewById(R.id.labelOption3));
    	((ImageButton) findViewById(R.id.btnLucky)).setOnClickListener(new View.OnClickListener() {
			@Override public void onClick(View v) {
				setOption((byte)0);
			}
		});
    	((ImageButton) findViewById(R.id.btnClient)).setOnClickListener(new View.OnClickListener() {
			@Override public void onClick(View v) {
				setOption((byte)1);
			}
		});
    	((ImageButton) findViewById(R.id.btnServer)).setOnClickListener(new View.OnClickListener() {
			@Override public void onClick(View v) {
				setOption((byte)2);
			}
		});
        //
        ((Button) findViewById(R.id.btnStart)).setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				go();
			}
		});
        //
        this.edtIP.setOnEditorActionListener(new OnEditorActionListener() {
        	@Override
			public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
        		if (event != null) {
        	        if (!event.isShiftPressed()) {
        	        	go();
        	            return true;
        	        }
        	        return false;
        	    }
        		go();
        	    return true;
			}
        });       	
    }
    
    public byte getOption(){	return this.choosedOption; };
    
    public void setOption(byte num){
    	this.edtIP.setVisibility((num == 1) ? EditText.VISIBLE : EditText.GONE);
    	if(!simple){
    		lblOption1.setVisibility((num == 0) ? EditText.VISIBLE : EditText.GONE);
    		lblOption2.setVisibility((num == 1) ? EditText.VISIBLE : EditText.GONE);
    		lblOption3.setVisibility((num == 2) ? EditText.VISIBLE : EditText.GONE);
    	}
    	this.choosedOption = num;
    };
    
    public void goToActivity(Class<?> to){
    	Intent intent = new Intent(this, to).setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
    	this.finish();
    	startActivity(intent);
    }
    
   private void beALuckGuy(){
    	setContentView(R.layout.searching);
    	tryingIp = new byte[]{0, 0};
    	String ipbase = "192.168.";
    	Thread tryt;
    	founded = false;
    	while(!founded){
    		Main.ip = ipbase + tryingIp[0] + "." + tryingIp[1];
    		tryt = new Thread(tryIp);
    		tryt.start();
    		if((tryingIp[0] == (byte)255) & ((tryingIp[1] == (byte)255)))
    			break;
    		else
    			if(tryingIp[1] == (byte)255){
    				tryingIp[1] = 0;
    				tryingIp[0]++;
    			}else
    				tryingIp[1]++;
    		
    	}
    }
    
    private void go(){
    	switch(getOption()){
		case 1:
			Main.ip = ((TextView) findViewById(R.id.edtIP)).getText().toString();
			goToActivity(Client.class);
			break;
		case 2:
			Main.ip = "127.0.0.1";
			goToActivity(Server.class);
			break;
		default:
			beALuckGuy();
		}
    }
    
    private Runnable tryIp = new Runnable(){
    	@Override
		public void run() {
    		new ClientReception(new String(ip));
		}
    };
}