package com.pedrohlc;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class PHLCTools {
	public static boolean copyFile(String sourcePath, String newPath, boolean sourceDelete){
		File fromF = new File(sourcePath);
		File toF = new File(newPath);
		FileInputStream from = null;
	    FileOutputStream to = null;
	    try {
	    	from = new FileInputStream(fromF);
	    	to = new FileOutputStream(toF);
	    	byte[] buffer = new byte[4096];
	    	int bytesRead;
	    	while ((bytesRead = from.read(buffer)) != -1)
		    	to.write(buffer, 0, bytesRead); // write
	    } catch (IOException e) {
			return false;
		} finally {
	    	if (from != null){
	    		try {
			    	from.close();
			    } catch (IOException e) {
			    	return false;
			    } finally{
			    	if(sourceDelete)
			    		fromF.delete();
			    }
	    	}
	    	if (to != null)
	    		try {
	    			to.close();
	    		} catch (IOException e) {
	    			return false;
	    		}
	    }
	    return true;
	}
}
