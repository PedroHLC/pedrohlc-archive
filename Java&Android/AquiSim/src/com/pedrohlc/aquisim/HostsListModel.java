package com.pedrohlc.aquisim;

import javax.swing.AbstractListModel;

import com.pedrohlc.aquisim.HostsManager.Host;

public class HostsListModel extends AbstractListModel<Object> {
	/**
	 * 
	 */
	private static final long serialVersionUID = -4276028522573315788L;
	private HostsManager hstMan;
	
	public HostsListModel(HostsManager hstMan){
		this.hstMan = hstMan;
	}
	
	public int getSize() {
		return hstMan.getHostsList().size();
	}
	public Object getElementAt(int index) {
		Host host = hstMan.getHostsList().get(index);
		return new String(host.getIP() + " " + host.getAddress() + "\n");
	}
}
