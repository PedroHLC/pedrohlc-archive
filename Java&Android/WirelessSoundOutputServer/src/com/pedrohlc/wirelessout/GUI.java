package com.pedrohlc.wirelessout;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Mixer;
import javax.swing.DefaultComboBoxModel;
import javax.swing.GroupLayout;
import javax.swing.GroupLayout.Alignment;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.LayoutStyle.ComponentPlacement;
import javax.swing.UIManager;
import javax.swing.border.EmptyBorder;

public class GUI extends JFrame {

	private static final long serialVersionUID = -646523843637791671L;
	private JPanel mainContentPane;
	private JTextField sampleRateField;
	private JTextField channelsNumField;
	private JTextField hostField;
	private JTextField portField;
	private JComboBox<String> audioFormatField;
	private JComboBox<String> mixerField;
	private JComboBox<String> lineField;
	private JComboBox<String> connTpField;
	private JTextField bufferSizeField;
	private Mixer.Info[] mixersInfo;
	//private Line.Info[] linesInfo;
	//private TargetDataLine line;
	private static GUI finstance;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		try {
        	UIManager.setLookAndFeel(
                    UIManager.getSystemLookAndFeelClassName());
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			finstance = new GUI();
			finstance.setVisible(true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Create the frame.
	 */
	public GUI() {
		mixersInfo = AudioSystem.getMixerInfo();
		Vector<String> mixerNames = new Vector<String>();
		for(Mixer.Info mi : mixersInfo)
			mixerNames.add(mi.getDescription());
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 560, 446);
		mainContentPane = new JPanel();
		mainContentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(mainContentPane);
		
		JLabel sampleRateLabel = new JLabel("Amostra (Hz):");
		
		JLabel audioFormatLabel = new JLabel("Formato:");
		
		JLabel channelsNumLabel = new JLabel("Canais:");
		
		JLabel hostLabel = new JLabel("Endereço:");
		
		JLabel managerLabel = new JLabel("Controles:");
		
		JLabel portLabel = new JLabel("Porta:");
		
		JLabel connTpLabel = new JLabel("Conexão:");
		
		sampleRateField = new JTextField();
		sampleRateField.setText("44100");
		sampleRateField.setColumns(10);
		
		audioFormatField = new JComboBox<String>();
		audioFormatField.setModel(new DefaultComboBoxModel<String>(new String[] {"PCM 16bit", "PCM 8bit"}));
		
		connTpField = new JComboBox<String>();
		connTpField.setModel(new DefaultComboBoxModel<String>(new String[] {"ENET", "TCP"}));
		
		channelsNumField = new JTextField();
		channelsNumField.setText("2");
		channelsNumField.setColumns(10);
		
		hostField = new JTextField();
		hostField.setEnabled(false);
		hostField.setEditable(false);
		hostField.setText("0.0.0.0");
		hostField.setColumns(10);
		
		portField = new JTextField();
		portField.setText("44000");
		portField.setColumns(10);
		
		JButton btnrestart = new JButton("(Re)Começar");
		btnrestart.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					String[] argument = new String[]{
							sampleRateField.getText(),
							(audioFormatField.getSelectedIndex() == 0 ? "16" : "8"),
							channelsNumField.getText(),
							portField.getText(),
							bufferSizeField.getText()};
					if(connTpField.getSelectedIndex() == 0)
						new ENETServer(argument);
					else
						new TCPServer(argument);
					Global.setInput(new LocalInput(AudioSystem.getMixer(mixersInfo[mixerField.getSelectedIndex()])));
					Global.instance.start();
				} catch (Exception e1) {
					// TODO Auto-generated catch block
					//e1.printStackTrace();
					JOptionPane.showMessageDialog(finstance, e1.toString());
				}
			}
		});
		
		JButton btnStop = new JButton("Parar");
		btnStop.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(Global.instance != null){
					Global.instance.kill();
					Global.instance = null;
					System.out.println("Stoped!");
				}
			}
		});
		
		JButton btnListen = new JButton("Reproduzir");
		btnListen.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(Global.instance == null)
					return;
				for(Client c : Global.clients)
					if(c instanceof FakeClient)
						return;
				Global.clients.add(new FakeClient());
			}
		});
		
		JLabel mixerLabel = new JLabel("Origem:");
		
		lineField = new JComboBox<String>();
		lineField.setEnabled(false);
		/*lineField.setEditable(true);
		lineField.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				try {
					int selected = lineField.getSelectedIndex();
					if(selected < 0){
						line = null;
						return;
					}
					Port.Info info = (Port.Info) linesInfo[selected];
					Port port = (Port) AudioSystem.getLine(info);
					Line.Info[] infos = AudioSystem.getSourceLineInfo(port.getLineInfo());//new DataLine.Info(TargetDataLine.class, tline.getFormat());
					if(infos.length <= 0){
						line = null;
						JOptionPane.showMessageDialog(finstance, "Incompatible or unavailable sound input device.");
						return;
					}
					line = (TargetDataLine) port;//(TargetDataLine) AudioSystem.getLine(info);
					AudioFormat format = line.getFormat();
					sampleRateField.setText(""+format.getSampleRate());
					audioFormatField.setSelectedIndex((format.getSampleSizeInBits() == 16 ? 0 : 1));
					channelsNumField.setText(""+format.getChannels());
				} catch (LineUnavailableException e1) {
					e1.printStackTrace();
				}
			}
		});*/
		
		mixerField = new JComboBox<String>();
		mixerField.setEditable(true);
		/*mixerField.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				Mixer.Info mi = mixersInfo[mixerField.getSelectedIndex()];
				Mixer m = AudioSystem.getMixer(mi);
				
				linesInfo = (Line.Info[]) m.getTargetLineInfo();
				Vector<String> lineNames = new Vector<String>();
				for(Line.Info li : linesInfo)
					//if(li instanceof DataLine)
						lineNames.add(li.toString());
					//else
						//lineNames.add("ERRO - " + li.toString() + " - Incompatível");
				lineField.setModel(new DefaultComboBoxModel<String>(lineNames));
				lineField.setSelectedIndex(-1);
			}
		});*/
		mixerField.setModel(new DefaultComboBoxModel<String>(mixerNames));
		
		JLabel bufferSizeLabel = new JLabel("Cache (Bytes):");
		
		bufferSizeField = new JTextField();
		bufferSizeField.setText("19300");
		bufferSizeField.setColumns(10);
		
		GroupLayout gl_mainContentPane = new GroupLayout(mainContentPane);
		gl_mainContentPane.setHorizontalGroup(
			gl_mainContentPane.createParallelGroup(Alignment.LEADING)
				.addGroup(gl_mainContentPane.createSequentialGroup()
					.addContainerGap()
					.addGroup(gl_mainContentPane.createParallelGroup(Alignment.LEADING)
						.addGroup(Alignment.TRAILING, gl_mainContentPane.createSequentialGroup()
							.addComponent(mixerLabel)
							.addGap(86)
							.addGroup(gl_mainContentPane.createParallelGroup(Alignment.LEADING)
								.addComponent(lineField, 0, 380, Short.MAX_VALUE)
								.addComponent(mixerField, 0, 380, Short.MAX_VALUE)))
						.addGroup(Alignment.TRAILING, gl_mainContentPane.createSequentialGroup()
							.addComponent(managerLabel)
							.addGap(68)
							.addGroup(gl_mainContentPane.createParallelGroup(Alignment.LEADING)
								.addComponent(btnrestart, GroupLayout.DEFAULT_SIZE, 380, Short.MAX_VALUE)
								.addComponent(btnStop, Alignment.TRAILING, GroupLayout.DEFAULT_SIZE, 380, Short.MAX_VALUE)
								.addComponent(btnListen, GroupLayout.DEFAULT_SIZE, 380, Short.MAX_VALUE)))
						.addGroup(Alignment.TRAILING, gl_mainContentPane.createSequentialGroup()
							.addGroup(gl_mainContentPane.createParallelGroup(Alignment.LEADING)
								.addComponent(sampleRateLabel)
								.addComponent(audioFormatLabel)
								.addComponent(channelsNumLabel)
								.addComponent(hostLabel)
								.addComponent(portLabel)
								.addComponent(connTpLabel))
							.addGap(50)
							.addGroup(gl_mainContentPane.createParallelGroup(Alignment.LEADING)
								.addComponent(sampleRateField, GroupLayout.DEFAULT_SIZE, 376, Short.MAX_VALUE)
								.addComponent(audioFormatField, 0, 376, Short.MAX_VALUE)
								.addComponent(channelsNumField, GroupLayout.DEFAULT_SIZE, 376, Short.MAX_VALUE)
								.addComponent(hostField, GroupLayout.DEFAULT_SIZE, 376, Short.MAX_VALUE)
								.addComponent(portField, GroupLayout.DEFAULT_SIZE, 376, Short.MAX_VALUE)
								.addComponent(connTpField, GroupLayout.DEFAULT_SIZE, 376, Short.MAX_VALUE)))
						.addGroup(Alignment.TRAILING, gl_mainContentPane.createSequentialGroup()
							.addComponent(bufferSizeLabel)
							.addGap(44)
							.addComponent(bufferSizeField, GroupLayout.DEFAULT_SIZE, 376, Short.MAX_VALUE)))
					.addContainerGap())
		);
		gl_mainContentPane.setVerticalGroup(
			gl_mainContentPane.createParallelGroup(Alignment.TRAILING)
				.addGroup(gl_mainContentPane.createSequentialGroup()
					.addContainerGap()
					.addGroup(gl_mainContentPane.createParallelGroup(Alignment.BASELINE)
						.addComponent(mixerLabel)
						.addComponent(mixerField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
					.addPreferredGap(ComponentPlacement.RELATED)
					.addComponent(lineField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
					.addPreferredGap(ComponentPlacement.RELATED, 44, Short.MAX_VALUE)
					.addGroup(gl_mainContentPane.createParallelGroup(Alignment.BASELINE)
						.addComponent(sampleRateLabel)
						.addComponent(sampleRateField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
					.addPreferredGap(ComponentPlacement.RELATED)
					.addGroup(gl_mainContentPane.createParallelGroup(Alignment.BASELINE)
						.addComponent(audioFormatField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
						.addComponent(audioFormatLabel))
					.addPreferredGap(ComponentPlacement.RELATED)
					.addGroup(gl_mainContentPane.createParallelGroup(Alignment.BASELINE)
						.addComponent(channelsNumField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
						.addComponent(channelsNumLabel))
					.addPreferredGap(ComponentPlacement.RELATED)
					.addGroup(gl_mainContentPane.createParallelGroup(Alignment.BASELINE)
						.addComponent(hostField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
						.addComponent(hostLabel))
					.addPreferredGap(ComponentPlacement.RELATED)
					.addGroup(gl_mainContentPane.createParallelGroup(Alignment.BASELINE)
						.addComponent(bufferSizeField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
						.addComponent(bufferSizeLabel))
					.addPreferredGap(ComponentPlacement.RELATED)
					.addGroup(gl_mainContentPane.createParallelGroup(Alignment.BASELINE)
						.addComponent(portField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
						.addComponent(portLabel))
					.addPreferredGap(ComponentPlacement.RELATED)
					.addGroup(gl_mainContentPane.createParallelGroup(Alignment.BASELINE)
						.addComponent(connTpField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
						.addComponent(connTpLabel))
					.addGap(63)
					.addGroup(gl_mainContentPane.createParallelGroup(Alignment.BASELINE)
						.addComponent(btnrestart)
						.addComponent(managerLabel))
					.addPreferredGap(ComponentPlacement.RELATED)
					.addComponent(btnStop, GroupLayout.PREFERRED_SIZE, 25, GroupLayout.PREFERRED_SIZE)
					.addPreferredGap(ComponentPlacement.RELATED)
					.addComponent(btnListen)
					.addContainerGap())
		);
		mainContentPane.setLayout(gl_mainContentPane);
	}
}
