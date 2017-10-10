package com.pedrohlc.wirelessout;

import java.net.InetSocketAddress;

import org.bespin.enet.EnetException;
import org.bespin.enet.Host;
import org.bespin.enet.MutableInteger;
import org.bespin.enet.Packet;
import org.bespin.enet.Peer;

public class ENETTester {
	public static class ENETStream {
		//private int bufferSize;
		private InetSocketAddress addr = null;
		private Host host = null;
		private Peer peer = null;
		
		public boolean isWorking() {
			return (host != null);
		}

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

		public boolean connect() {
			try {
				this.peer = this.host.connect(this.addr, 0, 0);
			} catch (EnetException e) {
				e.printStackTrace();
				return false;
			}
			return true;
		}

		public void disconnect() {
			try {
				this.host.finalize();
				this.host = null;
			} catch (Throwable e) {
				e.printStackTrace();
			}
		}

		public byte[] listen() {
			Packet pack;
			try {
				pack = this.peer.receive(new MutableInteger(0));
				if(pack != null){
					System.out.printf("Package received!\n");
					return pack.getBytes().array();
				}
			} catch (EnetException e) {
				e.printStackTrace();
			}
			return null;
		}

		public boolean prepare() {
			try {
				this.host = new Host(new InetSocketAddress("127.0.0.1", 44001), 1, 1, 0, 0);
				return true;
			} catch (EnetException e) {
				e.printStackTrace();
			}
			return false;
		}

		public String name() {
			return "ENET:RAWAUDIO";
		}

	}
	
	public static void main(String[] args){
		ENETStream test = new ENETStream();
		test.prepare();
		test.setServerAddr("127.0.0.1", 44000, 19300);
		test.connect();
		while(true)
			test.listen();
	}

}
