package com.pedrohlc.aquisim;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import com.pedrohlc.aquisim.HostsManager.Host;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.AbstractListModel;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JButton;
import javax.swing.UIManager;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.io.IOException;

import javax.swing.JTextField;

public class Main extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = -2586362764321048906L;
	private JPanel contentPane;
	private HostsManager hstMan;
	private JList<Object> list;
	private JTextField txtWwwfacebookcom;
	private JButton btnAdicionar;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					UIManager.setLookAndFeel(
		                    UIManager.getSystemLookAndFeelClassName());
					Main frame = new Main();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	@SuppressWarnings("serial")
	public Main() {
		setTitle("Aqui Sim!");
		hstMan = HostsManager.getDefaultHostsManager();
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 358);
		setResizable(false);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JLabel lblDescription = new JLabel("<html>Cansado de sites bloqueados pelo tio Fabio?<br>Conheça o \"Aqui Sim!\" um produto livre de sungas!</html>");
		lblDescription.setBounds(5, 5, 430, 30);
		contentPane.add(lblDescription);
		
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBounds(15, 47, 420, 200);
		contentPane.add(scrollPane);
		
		list = new JList<Object>();
		list.setVisibleRowCount(4);
		list.setModel(new HostsListModel(hstMan));
		scrollPane.setViewportView(list);
		
		JButton btnExcluir = new JButton("Desfazer");
		btnExcluir.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				hstMan.remove(list.getSelectedIndex());
				hstMan.saveHosts();
			}
		});
		btnExcluir.setBounds(318, 252, 117, 25);
		contentPane.add(btnExcluir);
		
		btnAdicionar = new JButton("Desbloquear");
		btnAdicionar.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				btnAdicionar.setEnabled(false);
				btnAdicionar.setText("Espere");
				String result = null, addr = txtWwwfacebookcom.getText();
				try {
					 result = RealIPDigger.doMagic(addr);
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				if(result == null)
					JOptionPane.showMessageDialog(contentPane, "Não foi possível localizar este endereço");
				else{
					int location= hstMan.locateByAddr(addr);
					if(location < 0){
						hstMan.addHost(new Host(result, addr));
					}else
						hstMan.setHostIP(location, result);
					hstMan.saveHosts();
				}
				btnAdicionar.setText("Ok! Desbloqueado");
				btnAdicionar.setEnabled(true);
				list.setModel(new HostsListModel(hstMan));
			}
		});
		btnAdicionar.setBounds(287, 321, 148, 25);
		contentPane.add(btnAdicionar);
		
		txtWwwfacebookcom = new JTextField();
		txtWwwfacebookcom.setText("www.facebook.com");
		txtWwwfacebookcom.setBounds(15, 321, 270, 25);
		contentPane.add(txtWwwfacebookcom);
		txtWwwfacebookcom.setColumns(10);
		
		JLabel lblEndereoDoWebsite = new JLabel("Endereço do Website: <tente com e sem o \"www.\">");
		lblEndereoDoWebsite.setBounds(12, 297, 423, 15);
		contentPane.add(lblEndereoDoWebsite);
	}
}
