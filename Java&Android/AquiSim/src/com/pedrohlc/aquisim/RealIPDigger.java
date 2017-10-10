package com.pedrohlc.aquisim;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.net.URL;
import java.net.URLEncoder;

public class RealIPDigger {
	@SuppressWarnings("deprecation")
	public static String doMagic(String addr) throws IOException{
		byte[] newaddrb = addr.getBytes();
		for(int i=0; i<addr.length(); i++){newaddrb[i] += 1;}
		addr = new String(newaddrb);
		URL url = new URL("http://www.pedrohlc.com/digip.php?addr="+URLEncoder.encode(addr));
		System.out.println(url);
		DataInputStream dis = new DataInputStream(new BufferedInputStream(url.openStream()));
		String result = new String();
		while ((result += dis.readLine()) != null) {
			break;
		}
		dis.close();
		if(result.length() < 8)
			return null;
		return result;
	}
}
