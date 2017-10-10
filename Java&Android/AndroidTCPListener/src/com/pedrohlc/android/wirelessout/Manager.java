package com.pedrohlc.android.wirelessout;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class Manager extends Activity {
	
	private static Service service;
	//private Button playBtn, stopBtn;
	private Button switchBtn;
	private EditText hostEdt;
	protected static SharedPreferences mainPref, cfgPref;
	protected static String cfgName;
	private static final String cfgDefaultName = "quick";
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_manager);
        
        if(mainPref == null){
        	cfgName = cfgDefaultName;
        	mainPref = getSharedPreferences("main", 0);
        	cfgPref = getSharedPreferences("cfg_"+mainPref.getString("lastCfg", cfgDefaultName), 0);
        }
        
        switchBtn = (Button) findViewById(R.id.buttonSwitch);
        hostEdt = (EditText) findViewById(R.id.editHostName);
        
        hostEdt.setText(cfgPref.getString("hostEdtTxt", "192.168.0.3"));
        
        if(service == null)
        	service = new Service();
        
        
        
        switchBtn.setOnClickListener(new OnClickListener(){
			@Override public void onClick(View arg0) {
				saveHost();
				if(service.isWorking())
					stop();
				else
					play();
				updateSwitchButtonBackground();
			}});
    }
    
    public void updateSwitchButtonBackground(){
    	if(service.isWorking())
        	switchBtn.setText(R.string.man_lbl_mainswitch_on);
        else
        	switchBtn.setText(R.string.man_lbl_mainswitch_off);
    }

    private void saveHost() {
    	Editor edit = Manager.cfgPref.edit();
    	edit.putString("hostEdtTxt", hostEdt.getText().toString());
        edit.commit();
	}
    
    private void openSettings() {
    	Intent intent = new Intent(this, SettingsActivity.class).setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
    	this.startActivity(intent);
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
    	System.out.println("Selected menu: " + item.getItemId());
    	switch(item.getItemId()){
    		case 0:
    			openSettings();
    			return true;
    	}
    	return super.onOptionsItemSelected(item);
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        //getMenuInflater().inflate(R.menu.activity_manager, menu);
    	menu.add(R.string.menu_settings);
        return true;
    }
    
    private boolean play(){
    	boolean stereo = (cfgPref.getInt("chCfgSpinnerPos", SettingsActivity.chCfgSpinnerPosDefault) == 0 );
        boolean b16 = (cfgPref.getInt("audFmtSpinnerPos", SettingsActivity.audFmtSpinnerPosDefault) == 0 );
        IStream stream = null;
        switch(Manager.cfgPref.getInt("streamFmtSpinnerPos", SettingsActivity.streamFmtSpinnerPosDefault)){
        case 0:
            stream = new ENETStream();
            break;
        case 1:
            stream = new TCPStream();
            break;
        case 2:
        	stream = new UDPStream();
        	break;
        case 3:
        	stream = new RTPStream();
        	break;
        }
        
        if(stream != null){
        	int bufferSize = Integer.valueOf(cfgPref.getString("bufferSzEdtTxt", SettingsActivity.bufferSzEdtTxtDefault));
        	boolean result = service.start(stream, 
        		hostEdt.getText().toString(), 
        		Integer.valueOf(cfgPref.getString("portEdtTxt", SettingsActivity.portEdtTxtDefault)), 
        		bufferSize, 
        		Integer.valueOf(cfgPref.getString("sampleRateEdtTxt", SettingsActivity.sampleRateEdtTxtDefault)),
        		stereo, b16);
        	/**I keep you my dirty little code!*/
        	if(!result){
        		AlertDialog.Builder dialog = new AlertDialog.Builder(this);
        		dialog.setTitle("Error");
        		dialog.setMessage(service.getLastError());
        		dialog.setNeutralButton("OK", null);
        		dialog.create();
        		dialog.show();
        	}
        	return result;
        }
        
        else return false;
    }
    
    private void stop(){
    	service.stop();
    }
    
    public static Service getService(){
    	return service;
    }
    
    @Override
    public void onStop(){
    	if(service == null || !service.isWorking()){
    		//service.destroy();
    		service = null;
    		this.finish();
    	}
    	super.onStop();
    }
}
