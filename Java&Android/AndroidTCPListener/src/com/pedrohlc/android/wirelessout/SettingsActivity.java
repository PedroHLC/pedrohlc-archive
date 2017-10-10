package com.pedrohlc.android.wirelessout;

import android.os.Bundle;
import android.app.Activity;
import android.content.SharedPreferences.Editor;
import android.widget.EditText;
import android.widget.Spinner;

public class SettingsActivity extends Activity {

	private Spinner chCfgSpinner, audFmtSpinner, streamFmtSpinner;
	private EditText portEdt, bufferSzEdt, sampleRateEdt;
	
	public static final Integer chCfgSpinnerPosDefault = 0,
			audFmtSpinnerPosDefault = 0,
			streamFmtSpinnerPosDefault = 0;
	public static final String portEdtTxtDefault = "44000",
			bufferSzEdtTxtDefault = "9600",
			sampleRateEdtTxtDefault = "44100",
			hostEdtTxtDefault = "192.168.0.3";
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);
        
        chCfgSpinner = (Spinner) findViewById(R.id.spinnerChannelConfig);
        audFmtSpinner = (Spinner) findViewById(R.id.spinnerAudioFormat);
        streamFmtSpinner = (Spinner) findViewById(R.id.spinnerStreamFormat);
        portEdt = (EditText) findViewById(R.id.editHostPort);
        bufferSzEdt = (EditText) findViewById(R.id.editBufferSize);
        sampleRateEdt = (EditText) findViewById(R.id.editSampleRate);
        
        loadConfiguration();
    }
    
    @Override
    public void onStop() {
    	saveConfiguration();
    	super.onStop();
    }
    
    private void loadConfiguration() {
    	chCfgSpinner.setSelection(Manager.cfgPref.getInt("chCfgSpinnerPos", chCfgSpinnerPosDefault));
        audFmtSpinner.setSelection(Manager.cfgPref.getInt("audFmtSpinnerPos", audFmtSpinnerPosDefault));
        streamFmtSpinner.setSelection(Manager.cfgPref.getInt("streamFmtSpinnerPos", streamFmtSpinnerPosDefault));
        
        portEdt.setText(Manager.cfgPref.getString("portEdtTxt", portEdtTxtDefault));
        bufferSzEdt.setText(Manager.cfgPref.getString("bufferSzEdtTxt", bufferSzEdtTxtDefault));
        sampleRateEdt.setText(Manager.cfgPref.getString("sampleRateEdtTxt", sampleRateEdtTxtDefault));
    }
    
    private void saveConfiguration() {
    	Editor edit = Manager.cfgPref.edit();
    	edit.putInt("chCfgSpinnerPos", chCfgSpinner.getSelectedItemPosition());
    	edit.putInt("audFmtSpinnerPos", audFmtSpinner.getSelectedItemPosition());
    	edit.putInt("streamFmtSpinnerPos", streamFmtSpinner.getSelectedItemPosition());
        
    	edit.putString("portEdtTxt", portEdt.getText().toString());
    	edit.putString("bufferSzEdtTxt", bufferSzEdt.getText().toString());
    	edit.putString("sampleRateEdtTxt", sampleRateEdt.getText().toString());
        edit.commit();
        
        edit = Manager.mainPref.edit();
        edit.putString("lastCfg", Manager.cfgName);
        edit.commit();
    }
}
