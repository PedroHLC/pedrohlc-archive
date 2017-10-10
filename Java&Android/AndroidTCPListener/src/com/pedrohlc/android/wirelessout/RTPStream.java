package com.pedrohlc.android.wirelessout;

import java.util.ArrayList;

public class RTPStream extends UDPStream {
	
	public byte[] listen(){
		return getPayload(super.listen());
	}
	
	private byte[] getPayload(byte[] rtpPacketBuffer){
		if(rtpPacketBuffer == null)
			return null;
		DataPacket rtpPacket = decodeRTPPacket(new ChannelBuffer(rtpPacketBuffer));
		return rtpPacket.data;
	}
	
	//From: http://snipplr.com/view/57978/rtp-packet-handler/
    public static DataPacket decodeRTPPacket(ChannelBuffer buffer) throws IndexOutOfBoundsException {
    	if (buffer.readableBytes() < 12) {
    		throw new IllegalArgumentException("A RTP packet must be at least 12 octets long");
    	}
    	
    	// Version, Padding, eXtension, CSRC Count
    	DataPacket packet = new DataPacket();
    	byte b = buffer.readByte();
    	packet.version = 2;
    	boolean padding = (b & 0x20) > 0; // mask 0010 0000
    	boolean extension = (b & 0x10) > 0; // mask 0001 0000
    	int contributingSourcesCount = b & 0x0f; // mask 0000 1111
    	
    	// Marker, Payload Type
    	b = buffer.readByte();
    	packet.marker = (b & 0x80) > 0; // mask 0000 0001
    	packet.payloadType = (b & 0x7f); // mask 0111 1111
    	
    	packet.sequenceNumber = buffer.readUnsignedShort();
    	packet.timestamp = buffer.readUnsignedInt();
    	packet.ssrc = buffer.readUnsignedInt();
    	
    	// Read extension headers & data
    	if (extension) {
    		packet.extensionHeaderData = buffer.readShort();
    		packet.extensionData = new byte[buffer.readUnsignedShort()];
    		buffer.readBytes(packet.extensionData);
    	}
    	
    	// Read CCRC's
    	if (contributingSourcesCount > 0) {
    		packet.contributingSourceIds = new ArrayList<Long>(contributingSourcesCount);
    		for (int i = 0; i < contributingSourcesCount; i++) {
    			long contributingSource = buffer.readUnsignedInt();
    			packet.contributingSourceIds.add(contributingSource);
    		}
    	}
    	
    	if (!padding) {
    		// No padding used, assume remaining data is the packet
    		byte[] remainingBytes = new byte[buffer.readableBytes()];
    		buffer.readBytes(remainingBytes);
    		packet.data = remainingBytes;
    	} else {
    		// Padding bit was set, so last byte contains the number of padding octets that should be discarded.
    		short lastByte = buffer.getUnsignedByte(buffer.readerIndex() + buffer.readableBytes() - 1);
    		byte[] dataBytes = new byte[buffer.readableBytes() - lastByte];
    		buffer.readBytes(dataBytes);
    		packet.data = dataBytes;
    		// Discard rest of buffer.
    		buffer.skipBytes(buffer.readableBytes());
    	}
    	
    	return packet;
    }
    
    /**
     * ºººººººººººººººººººººººººººººººººººººººººººººº
     * --- My dirty code adaptations
     * ºººººººººººººººººººººººººººººººººººººººººººººº
     **/
    
    public static class DataPacket{

		public ArrayList<Long> contributingSourceIds;
		public byte[] extensionData;
		public short extensionHeaderData;
		public long ssrc;
		public long timestamp;
		public short sequenceNumber;
		public int payloadType;
		public boolean marker;
		public int version;
		public byte[] data;
    }
    
    public static class ChannelBuffer{
    	private byte[] value;
    	private int location;
    	public ChannelBuffer(byte[] value){
    		this.value = value;
    		this.location = 0;
    	}
		public void skipBytes(int num) {
			this.location += num;
		}
		public byte getUnsignedByte(int i) {
			return (byte) (value[i] & 0xff);
		}
		public byte readUnsignedByte() {
			return (byte) (readByte() & 0xff);
		}
		public int readerIndex() {
			return location;
		}
		public int readUnsignedInt() {
			return (readUnsignedByte() << 24) | (readUnsignedByte() << 16) | (readUnsignedByte() << 8) | readUnsignedByte();
		}
		public short readUnsignedShort() {
			return (short) ((readUnsignedByte() << 8) + readUnsignedByte());

		}
		public short readShort() {
			return (short) ((readByte() << 8) + readByte());
		}
		public int readBytes(byte[] extensionData) {
			long end;
			if(value.length < (extensionData.length + location)){
				end = value.length - location - 1;
				System.out.println("WARNING: RTP trying to read more data than is available.");
			}else
				end = extensionData.length;
			for(int i=0; i<end; i++){
				extensionData[i] = value[location];
				this.location++;
			}
			return extensionData.length;
		}
		public byte readByte() {
			byte result = value[location];
			this.location++;
			return result;
		}
		public int readableBytes() {
			return value.length - location;
		}
		
		public String name() {
			return "RTP:RAWAUDIO";
		}
    }
}