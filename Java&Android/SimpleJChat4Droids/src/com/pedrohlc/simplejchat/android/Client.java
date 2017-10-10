package com.pedrohlc.simplejchat.android;

import android.app.Activity;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.text.Editable;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.TextView.OnEditorActionListener;

public class Client extends Activity {
	
	protected static Client i = null;
	protected static ClientReception r = null;
	private EditText edtInput = null;
	private EditText edtOutput = null;
	private String buffer = null;
	protected static int outTextColor = Color.BLACK;
	private NotificationManager notfmgr = null;
	private PendingIntent pendIntent = null;
	
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Client.i = this;
        if(Client.r == null)
        	Client.r = new ClientReception(null);
        else
        	Client.r.start();
        //
        setContentView(R.layout.client);
        //
        notfmgr = (NotificationManager)getSystemService(NOTIFICATION_SERVICE);
        pendIntent = PendingIntent.getActivity(this, 0, this.getIntent(), 0);
        //
        edtInput = ((EditText) findViewById(R.id.edtInput));
        edtInput.setImeOptions(EditorInfo.IME_ACTION_DONE);
        //
        edtOutput = ((EditText) findViewById(R.id.edtOutput));
        edtOutput.setKeyListener(null);
        edtOutput.setText("Use \"/name <nome>\" para alterar seu nome de exibição.\n");
        //
        ((Button) findViewById(R.id.btnSend)).setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v) {
				send();
			}
        });
        //
        edtInput.setOnEditorActionListener(new OnEditorActionListener() {
        	@Override
			public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
        		if (event != null) {
        	        if (!event.isShiftPressed()) {
        	        	send();
        	            return true;
        	        }
        	        return false;
        	    }
        		send();
        	    return true;
			}
        });
        //
        ((Button) findViewById(R.id.btnExit)).setOnClickListener(new OnClickListener(){
        	@Override
        	public void onClick(View v) {
        		Client.i.finish();
        	}
        });
        //
	}
	
	public void println(String str){
		buffer = str + "\n";
		runOnUiThread(println);
		notificate(str);
	}
	
	public void notificate(String str){
		Notification notif = new Notification();
        notif.vibrate = new long[]{100, 200, 100, 200};
		notif.setLatestEventInfo(this, "SimpleJChat", str, this.pendIntent);
		notfmgr.notify(R.string.newmsg, notif);
	}
	
	private void send(){
		String str = edtInput.getText().toString();
		if((str != null) & (str.length() > 0)){
			r.sendMsg(str);
			edtInput.setText("");
			InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
			imm.hideSoftInputFromWindow(edtInput.getWindowToken(), 0);
		}
	}
	
	public void boate(){
		runOnUiThread(boate);
	}
	
	public void clear(){
		edtOutput.setText("");
	}
	
	@Override
	public void onDestroy(){
		if(Server.i != null)
			Server.i.finish();
		if(r != null)
			r.destroy();
		super.onDestroy();
		System.exit(0);
	}
	
	public EditText getOutput(){	return edtOutput;	}
	public EditText getInput(){	return edtInput;	}
	
	private Runnable println = new Runnable(){
		@Override
		public void run() {
			Editable outtext = edtOutput.getText();
			if(outtext == null)
				edtOutput.setText(buffer);
			else
				edtOutput.setText(outtext.toString() + buffer);
			edtOutput.selectAll();
			edtOutput.setSelection(edtOutput.getSelectionEnd(), edtOutput.getSelectionEnd());
		}
	};
	
	//BOATE
	private Runnable updateOutTextColor = new Runnable(){
		@Override
		public void run() {
			edtOutput.setTextColor(outTextColor);
		}
	};
	
	public void setOutTextColor(int color){
		outTextColor = color;
		i.runOnUiThread(updateOutTextColor);
	}
	
	private Runnable boate = new Runnable(){
		@Override
		public void run() {
			for (int i = 0; i < 128; i++) {
				setOutTextColor((int)(Math.random() * Color.WHITE));
				try{
					Thread.sleep(50L);
				}catch (InterruptedException e){
					e.printStackTrace();
				}
			}
			setOutTextColor(Color.BLACK);
		}
	};
	
}
