package com.pedrohlc.simplejchat;

import java.awt.BorderLayout;
import java.awt.ComponentOrientation;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.JTextPane;

public class ClientForm extends JFrame
  implements Runnable
{
  private static final long serialVersionUID = 2L;
  private JPanel jContentPane = null;
  private JTextField inputTextField = null;
  private JTextPane outputTextPane = null;
  private JButton sendButton = null;
  private JScrollPane outputScrollPane = null;

  public void println(String value) {
    this.outputTextPane.setText(this.outputTextPane.getText() + value + "\n");
    this.outputTextPane.selectAll();
    int y = this.outputTextPane.getSelectionEnd();
    this.outputTextPane.select(0, y);
    this.outputScrollPane.getVerticalScrollBar().setValue(y);
    if (!isFocused())
      toFront();
  }

  public void sendThisMessage()
  {
    String message = this.inputTextField.getText();
    if (message.length() <= 0) return;
    if ((message.charAt(0) == '/') && 
      (message.contentEquals("/clear"))) {
      this.outputTextPane.setText("");
      this.inputTextField.setText("");
      return;
    }

    Main.client.sendMessage(message);
    this.inputTextField.setText("");
  }

  public void initialize()
  {
    setSize(610, 450);
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
      this.jContentPane.add(getInputTextField(), "South");
      this.jContentPane.add(getSendButton(), "East");
      this.jContentPane.add(getOutputScrollPane(), "Center");
    }
    return this.jContentPane;
  }

  private JTextField getInputTextField()
  {
    if (this.inputTextField == null) {
      this.inputTextField = new JTextField();
      this.inputTextField.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          ClientForm.this.sendThisMessage();
        } } );
    }
    return this.inputTextField;
  }

  public JTextPane getOutputTextPane()
  {
    if (this.outputTextPane == null) {
      this.outputTextPane = new JTextPane();
      this.outputTextPane.setText("Use \"/name <nome>\" para alterar seu nome de exibição.\n");
      this.outputTextPane.setEditable(false);
      this.outputTextPane.setComponentOrientation(ComponentOrientation.LEFT_TO_RIGHT);
    }
    return this.outputTextPane;
  }

  public void run()
  {
    setVisible(true);
  }

  private JButton getSendButton()
  {
    if (this.sendButton == null) {
      this.sendButton = new JButton();
      this.sendButton.setText("Enviar");
      this.sendButton.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          ClientForm.this.sendThisMessage();
        } } );
    }
    return this.sendButton;
  }

  private JScrollPane getOutputScrollPane()
  {
    if (this.outputScrollPane == null) {
      this.outputScrollPane = new JScrollPane();
      this.outputScrollPane.setViewportView(getOutputTextPane());
    }
    return this.outputScrollPane;
  }
}