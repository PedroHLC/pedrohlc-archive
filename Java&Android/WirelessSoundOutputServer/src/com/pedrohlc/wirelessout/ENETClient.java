package com.pedrohlc.wirelessout;

import java.util.EnumSet;
import org.bespin.enet.EnetException;
import org.bespin.enet.Packet;
import org.bespin.enet.Peer;

public class ENETClient implements Client {
	private final static EnumSet<Packet.Flag> flags =  EnumSet.of(Packet.Flag.UNRELIABLE_FRAGMENT);
	private Peer peer;
	
	public ENETClient (Peer peer){
		this.peer = peer;
	}

	@Override
	public boolean doConnections() {
		return true;
	}

	@Override
	public boolean send(byte[] data) {
		try {
			peer.send(0, new Packet(data, flags));
			System.out.printf("Hey look, I'm sending something!\n");
		} catch (EnetException e) {
			e.printStackTrace();
			return false;
		}
		return true;
	}

}
