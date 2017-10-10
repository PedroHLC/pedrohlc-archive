package com.pedrohlc.simplejchat;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.UnknownHostException;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

public class Main extends JFrame
{
  public static final int port = 1337;
  public static final String version = "1.2.2.1";
  public static Server server;
  public static Main main = null;
  public static Client client;
  private static final long serialVersionUID = 1L;
  private JPanel jContentPane = null;
  private JButton beServerButton = null;
  private JButton beClientButton = null;
  private JTextField addrTextField = null;
  private JButton luckyButton = null;
  public static Client founded = null;

  private JButton getBeServerButton()
  {
    if (this.beServerButton == null) {
      this.beServerButton = new JButton();
      this.beServerButton.setText("Quero ser cliente!!");
      this.beServerButton.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          Main.client = new Client(Main.this.addrTextField.getText(), Main.port);
        } } );
    }
    return this.beServerButton;
  }

  private JButton getBeClientButton()
  {
    if (this.beClientButton == null) {
      this.beClientButton = new JButton();
      this.beClientButton.setText("Quero ser servidor!!");
      this.beClientButton.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          Main.server = new Server();
          Main.server.startListening();
          Main.client = new Client("127.0.0.1", Main.port);
        } } );
    }
    return this.beClientButton;
  }

  private JTextField getAddrTextField()
  {
    if (this.addrTextField == null) {
      this.addrTextField = new JTextField();
      this.addrTextField.setText("127.0.0.1");
      this.addrTextField.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          Main.client = new Client(Main.this.addrTextField.getText(), Main.port);
        } } );
    }
    return this.addrTextField;
  }

  private JButton getLuckyButton()
  {
    if (this.luckyButton == null) {
      this.luckyButton = new JButton();
      this.luckyButton.setText("Estou com sorte!");
      this.luckyButton.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          String temp = "192.168.";
          String ip = null;
          Main.founded = null;
          for (int x = 0; x < 256; x++) {
            for (int y = 1; y < 256; y++) {
              try {
                ip = temp + x + "." + y;
                System.out.println("Tentando conectar à " + ip);
                new Thread() {
                  private String ip;

                  public void run() { try { Client test = new Client(this.ip, Main.port, true);
                      Main.founded = test; } catch (UnknownHostException localUnknownHostException) {
                    } catch (IOException localIOException) {
                    } }

                  public void go(String ip) {
                    this.ip = ip;
                    start();
                  }
                }
                .go(ip); } catch (Exception localException) {
              }
              if (Main.founded != null) break;
            }
            if (Main.founded != null) break;
          }
          if (Main.founded != null) {
            Main.client = Main.founded;
            Main.client.intialize4Testers();
          } else {
            Main.server = new Server();
            Main.server.startListening();
            Main.client = new Client("127.0.0.1", Main.port);
          }
        } } );
    }
    return this.luckyButton;
  }

  public static void main(String[] args)
  {
    SwingUtilities.invokeLater(new Runnable() {
      public void run() {
        Main thisClass = new Main();
        thisClass.setDefaultCloseOperation(3);
        thisClass.setVisible(true);
      }
    });
  }

  public Main()
  {
    main = this;
    initialize();
  }

  private void initialize()
  {
    setSize(300, 220);
    Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
    setLocation((dim.width - getWidth()) / 2, (dim.height - getHeight()) / 2);
    setContentPane(getJContentPane());
    setTitle("SimpleJChat");
  }

  private JPanel getJContentPane()
  {
    if (this.jContentPane == null) {
      this.jContentPane = new JPanel();
      this.jContentPane.setLayout(new BorderLayout());
      this.jContentPane.add(getBeServerButton(), "West");
      this.jContentPane.add(getBeClientButton(), "East");
      this.jContentPane.add(getAddrTextField(), "South");
      this.jContentPane.add(getLuckyButton(), "North");
    }
    return this.jContentPane;
  }
}