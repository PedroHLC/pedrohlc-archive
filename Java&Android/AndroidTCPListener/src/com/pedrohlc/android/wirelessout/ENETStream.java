package com.pedrohlc.android.wirelessout;

import java.net.InetSocketAddress;

import org.bespin.enet.EnetException;
import org.bespin.enet.Host;
import org.bespin.enet.MutableInteger;
import org.bespin.enet.Packet;
import org.bespin.enet.Peer;

public class ENETStream implements IStream {
	//private int bufferSize;
	private InetSocketAddress addr = null;
	private Host host = null;
	private Peer peer = null;

	@Override
	public boolean isWorking() {
		return (host != null);
	}

	@Override
	public boolean setServerAddr(String hostaddr, int port, int bufferSize) {
		try {
			this.addr = new InetSocketAddress(hostaddr, port);
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
		//this.bufferSize = bufferSize;
		return true;
	}

	@Override
	public boolean connect() {
		try {
			this.peer = this.host.connect(this.addr, 0, 0);;
			System.out.printf("Seems like we're online!\n");
		} catch (EnetException e) {
			e.printStackTrace();
			return false;
		}
		return true;
	}

	@Override
	public void disconnect() {
		try {
			this.host.finalize();
			this.host = null;
		} catch (Throwable e) {
			e.printStackTrace();
		}
	}

	@Override
	public byte[] listen() {
		Packet pack;
		try {
			pack = this.peer.receive(new MutableInteger(1));
			if(pack != null){
				return pack.getBytes().array();
			}else{
				System.out.printf("null package");
			}
		} catch (EnetException e) {
			e.printStackTrace();
		}
		return null;
	}

	@Override
	public boolean prepare() {
		try {
			this.host = new Host(null, 1, 1, 0, 0);
			return true;
		} catch (EnetException e) {
			e.printStackTrace();
		}
		return false;
	}

	@Override
	public String name() {
		return "ENET:RAWAUDIO";
	}

}
