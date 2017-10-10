package com.pedrohlc.aquisim;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

public class HostsManager {
	private static final String HostsPathOnLinux = "/etc/hosts";
	private static final String HostsPathOverWindows = "\\System32\\drivers\\etc\\hosts";
	private static final String ErrorImpossibleReading = "Não foi possivel abrir arquivo mágico. Você está no Windows ou Linux?";
	private static final String ErrorImpossibleWriting = "Ohhh! Você tem que rodar o programa como administrador... ok?";
	private static final String ErrorWhileWriting = "Ops... Não deu pra mudar o arquivo...";
	public static JFrame frame = null;
	
	public static String getDefaultHostsPath(){
		String os = System.getProperty("os.name").toLowerCase();
		if(os.indexOf("win") >= 0){
			return System.getenv("WINDIR") + HostsPathOverWindows;
		}else if(os.indexOf("nix") >= 0 || os.indexOf("nux") >= 0){
			return HostsPathOnLinux;
		}else{
			return null;
		}
	}
	
	public static class Host{
		private String ip;
		private String addr;
		public Host(String ip, String addr){
			this.ip = ip;
			this.addr = addr;
		}
		public String getIP(){ return ip; }
		public void setIP(String value){ ip = value; }
		public String getAddress(){ return addr; }
		public void setAddress(String value){ addr = value; }
	}
	
	private static HostsManager defaultInstance = null;
	
	public static HostsManager getDefaultHostsManager(){
		if(defaultInstance == null){
			defaultInstance = new HostsManager();
			defaultInstance.load(getDefaultHostsPath());
		}
		return defaultInstance;
	}
	
	private File file;
	private OutputStreamWriter fileOutput;
	private FileOutputStream fileOutputStream;
	private ArrayList<Host> hostsList;
	
	private void createOutputStream() throws FileNotFoundException{
		fileOutputStream = new FileOutputStream(file);
		fileOutput = new OutputStreamWriter(fileOutputStream);
	}
	
	private void closeOutputStream() throws IOException{
		fileOutput.close();
		fileOutputStream.close();
	}
	
	private void load(String hostsPath){
		file = new File(hostsPath);
		BufferedReader fileInput = null;
		try {
			fileInput = new BufferedReader(new InputStreamReader(new FileInputStream(file)));
		} catch (FileNotFoundException e1) {
			System.out.println(ErrorImpossibleReading);
			JOptionPane.showMessageDialog(frame, ErrorImpossibleReading);
		}
		if(fileInput == null)
			System.exit(-1);
		hostsList = new ArrayList<Host>();
		try {
			String line = null;
			int cmtat, lenght;
			while((line = fileInput.readLine()) != null){
				if((cmtat = line.indexOf('#')) >= 0)
					line = line.subSequence(0, cmtat).toString();
				if((lenght = line.length()) >= 4){
					String ip = new String();
					String addr = new String();
					boolean what = false;
					for(int i=0; i < lenght; i++){
						char c = line.charAt(i);
						if(c == ' ' || c == '\t')
							what = true;
						else
							if(what)
								addr += c;
							else
								ip += c;
					}
					hostsList.add(new Host(ip, addr));
				}
			}
		} catch (IOException e) {}
		try {
			createOutputStream();
			if(fileOutput == null)
				System.exit(-2);
			saveHosts();
			closeOutputStream();
		} catch (IOException e1) {
			System.out.println(ErrorImpossibleWriting);
			JOptionPane.showMessageDialog(frame, ErrorImpossibleWriting);
		}
	}
	
	@SuppressWarnings("unchecked")
	public ArrayList<Host> getHostsList() {
		return (ArrayList<Host>) hostsList.clone();
	}
	
	public void addHost(Host value){
		hostsList.add(value);
	}
	
	public boolean saveHosts(){
		try {
			createOutputStream();
		} catch (FileNotFoundException e) {
			onSaveError(e, 1);
			return false;
		}
		for(Host host: hostsList){
			try {
				if(fileOutput == null)
					System.exit(-2);
				fileOutput.write(host.getIP() + " " + host.getAddress() + "\n");
			} catch (IOException e) {
				onSaveError(e, 2);
				return false;
			}
		}
		try {
			closeOutputStream();
		} catch (IOException e) {
			onSaveError(e, 3);
			return false;
		}
		return true;
	}

	private void onSaveError(IOException exception, int part){
		System.out.println(ErrorWhileWriting + "("+part+")");
		exception.printStackTrace();
		JOptionPane.showMessageDialog(frame, ErrorWhileWriting + "("+part+")");
	}
	
	public void remove(int selectedIndex) {
		hostsList.remove(selectedIndex);
	}
	
	public int locateByAddr(String addr) {
		addr = addr.toLowerCase();
		Host h;
		for(int i=0; i<hostsList.size(); i++){
			h = hostsList.get(i);
			if(h != null)
				if(h.getAddress().toLowerCase().compareTo(addr) == 0)
					return i;  
		}
		return -1;
	}
	
	public int locateByIP(String ip) {
		ip = ip.toLowerCase();
		Host h;
		for(int i=0; i<hostsList.size(); i++){
			h = hostsList.get(i);
			if(h != null)
				if(h.getIP().toLowerCase().compareTo(ip) == 0)
					return i;  
		}
		return -1;
	}
	
	public void setHostIP(int index, String ip){
		hostsList.get(index).setIP(ip);
	}
	
	public void setHostAddress(int index, String addr){
		hostsList.get(index).setAddress(addr);
	}
}
