import java.math.BigInteger;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Enumeration;

import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;

import net.minecraft.client.Minecraft;

public class MumfreyBypass {
	public static final String client_version = "5.2N",
								enc_key = "aG5v1Br3gbE3nrWt",
								hEX = "0123456789ABCDEF",
								auth_prefix = "/auth",
								auth_base = "&6 &4 &2 &0",
								author = "Cracked by pedro.laracampos@gmail.com";

	public static void magic(pe packet3chat, Minecraft craft) {
		String send = auth_base;
		if (packet3chat.a.equalsIgnoreCase(send.replaceAll("(&([a-fk0-9]))", "§$2"))) {
			String userkey = getuserkey();
			craft.h.a(auth_prefix
					+ crazy_named(new StringBuilder()
							.append(client_version).append(craft.h.l).toString()) + " "
					+ userkey);
		} else {
			craft.v.a(packet3chat.a);
		}
	}

	@SuppressWarnings("rawtypes")
	public static String getuserkey() {
		try {
			Enumeration networkInterfaces = NetworkInterface
					.getNetworkInterfaces();
			while (networkInterfaces.hasMoreElements()) {
				NetworkInterface network = (NetworkInterface) networkInterfaces
						.nextElement();
				byte[] mac = network.getHardwareAddress();

				if ((mac != null) && (mac.length > 0)) {
					StringBuilder sb = new StringBuilder();
					for (int i = 0; i < mac.length; i++) {
						sb.append(String.format("%02X%s",
								new Object[] { Byte.valueOf(mac[i]),
										i < mac.length - 1 ? "-" : "" }));
					}
					try {
						return crazy_named(encrypt(enc_key,
								new StringBuilder().append(new String(sb))
										.append(network.getName()).append("::")
										.append(network.hashCode()).toString()));
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		} catch (SocketException e) {
			e.printStackTrace();
		}

		return null;
	}

	public static String encrypt(String seed, String cleartext)
			throws Exception {
		byte[] rawKey = getRawKey(seed.getBytes());
		byte[] result = encrypt(rawKey, cleartext.getBytes());
		return toHex(result);
	}

	public static String decrypt(String seed, String encrypted)
			throws Exception {
		byte[] rawKey = getRawKey(seed.getBytes());
		byte[] enc = toByte(encrypted);
		byte[] result = decrypt(rawKey, enc);
		return new String(result);
	}

	private static byte[] getRawKey(byte[] seed) throws Exception {
		KeyGenerator kgen = KeyGenerator.getInstance("AES");
		SecureRandom sr = SecureRandom.getInstance("SHA1PRNG");
		sr.setSeed(seed);
		kgen.init(128, sr);
		SecretKey skey = kgen.generateKey();
		byte[] raw = skey.getEncoded();
		return raw;
	}

	private static byte[] encrypt(byte[] raw, byte[] clear) throws Exception {
		SecretKeySpec skeySpec = new SecretKeySpec(raw, "AES");
		Cipher cipher = Cipher.getInstance("AES");
		cipher.init(1, skeySpec);
		byte[] encrypted = cipher.doFinal(clear);
		return encrypted;
	}

	private static byte[] decrypt(byte[] raw, byte[] encrypted)
			throws Exception {
		SecretKeySpec skeySpec = new SecretKeySpec(raw, "AES");
		Cipher cipher = Cipher.getInstance("AES");
		cipher.init(2, skeySpec);
		byte[] decrypted = cipher.doFinal(encrypted);
		return decrypted;
	}

	public static String toHex(String txt) {
		return toHex(txt.getBytes());
	}

	public static String fromHex(String hex) {
		return new String(toByte(hex));
	}

	public static byte[] toByte(String hexString) {
		int len = hexString.length() / 2;
		byte[] result = new byte[len];
		for (int i = 0; i < len; i++)
			result[i] = Integer.valueOf(hexString.substring(2 * i, 2 * i + 2),
					16).byteValue();
		return result;
	}

	public static String toHex(byte[] buf) {
		if (buf == null)
			return "";
		StringBuffer result = new StringBuffer(2 * buf.length);
		for (int i = 0; i < buf.length; i++) {
			appendHex(result, buf[i]);
		}
		return result.toString();
	}

	private static void appendHex(StringBuffer sb, byte b) {
		sb.append(hEX.charAt(b >> 4 & 0xF)).append(hEX.charAt(b & 0xF));
	}

	public static String crazy_named(String s) {
		String toEnc = s;
		MessageDigest mdEnc = null;
		try {
			mdEnc = MessageDigest.getInstance("MD5");
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}

		mdEnc.update(toEnc.getBytes(), 0, toEnc.length());
		String md5 = new BigInteger(1, mdEnc.digest()).toString(16);
		return md5;
	}
}
