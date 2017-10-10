package com.pedrohlc;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;

public class FileDownloader {
	protected static final long dwlBufferLength = 32;
	protected static final String dwlSuffix = ".part";
	
	private String location;
	private String destination;
	private FileOutputStream fos;
	private ReadableByteChannel rbc;
	private HttpURLConnection httpConn;
	private boolean finished = false;
	private long actual;
	private long size;
	
	public FileDownloader(String llocation, String ldestination){
		this.location = llocation;
		this.destination = ldestination;
	}
	
	public void start() throws MalformedURLException, IOException{
		finished = false;
		URL url = new URL(location);
		httpConn = (HttpURLConnection) url.openConnection();
		size = httpConn.getContentLength();
		InputStream rbs = httpConn.getInputStream();
		rbc = Channels.newChannel(rbs);
		fos = new FileOutputStream(destination + FileDownloader.dwlSuffix);
		if(size <= 0)
			size = Long.MAX_VALUE;
		actual = 0;
	}
	
	public boolean tick() throws IOException{
		long result = fos.getChannel().transferFrom(rbc, actual, dwlBufferLength);
		actual += result;
		if (result == 0){
			size = actual;
			finish();
			return true;
		}else
			return false;
	}
	
	public void finish() throws IOException{
		if(finished)
			return;
		else
			finished = true;
		fos.close();
	    rbc.close();
	    httpConn.disconnect();
	    PHLCTools.copyFile((destination + FileDownloader.dwlSuffix), destination, true);
	}
	
	public Long getSize(){ return this.size; }
	public Long getPosition(){ return this.actual; }
	public HttpURLConnection getConnection(){ return this.httpConn; }
	
	public static void instantDownloadFile(String location, String destination) throws MalformedURLException, IOException{
		URL url = new URL(location);
		ReadableByteChannel rbc = Channels.newChannel(url.openStream());
		String tmpDestination = destination + FileDownloader.dwlSuffix;
	    FileOutputStream fos = new FileOutputStream(tmpDestination);
	    while(fos.getChannel().transferFrom(rbc, 0, Long.MAX_VALUE) != 0);
	    fos.close();
	    rbc.close();
	    PHLCTools.copyFile(tmpDestination, destination, true);
	}
}
