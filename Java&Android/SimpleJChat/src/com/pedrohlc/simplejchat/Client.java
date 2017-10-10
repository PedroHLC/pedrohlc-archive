package com.pedrohlc.simplejchat;

import java.awt.Color;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import javax.swing.JTextPane;

public class Client
  implements Runnable
{
  private Socket socket;
  private PrintWriter out;
  private BufferedReader in;
  private ClientForm form;
  private Thread tinstance;

  public Client(String addr, int port)
  {
    try
    {
      this.socket = new Socket(addr, port);
      this.out = new PrintWriter(this.socket.getOutputStream(), true);
      this.in = 
        new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
    } catch (UnknownHostException e) {
      e.printStackTrace();
      System.exit(1);
    } catch (IOException e) {
      e.printStackTrace();
      System.exit(2);
    }

    intialize4Testers();
  }

  public Client(String addr, int port, boolean testing) throws UnknownHostException, IOException {
    if (testing) {
      this.socket = new Socket(addr, port);
      this.out = new PrintWriter(this.socket.getOutputStream(), true);
      this.in = 
        new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
      this.out.println("Te achei no estou com sorte!");
      String message = null;
      if (((message = this.in.readLine()) != null) && 
        (!message.contains("Te achei no estou com sorte!"))) {
        new Exception("");
        return;
      }
    } else {
      new Exception("This inicialization can only be used for tests!");
      return;
    }
  }

  public void intialize4Testers() {
    Main.main.setVisible(false);

    this.form = new ClientForm();
    this.form.initialize();
    this.form.setDefaultCloseOperation(3);

    this.tinstance = new Thread(this);
    this.tinstance.start();

    this.form.run();
  }

  public static void test(String addr, int port) throws UnknownHostException, IOException
  {
  }

  public String readInput()
  {
    try {
      return this.in.readLine();
    } catch (IOException e) {
      e.printStackTrace();
    }return null;
  }

  public void sendMessage(String message)
  {
    this.out.println(message);
  }

  public ClientForm getForm() {
    return this.form;
  }

  public void run()
  {
    String message = null;
    while ((message = readInput()) != null) {
      System.out.println(message);
      if (message.charAt(0) == '/') {
        if (message.startsWith("/boate ")) {
          this.form.println(message.substring(7) + " começou a boate!");
          new Thread() {
            public void run() {
              JTextPane out = Main.client.form.getOutputTextPane();

              for (int i = 0; i < 128; i++) {
                out.setForeground(new Color((int)(Math.random() * 16581375.0D)));
                try {
                  Thread.sleep(50L);
                } catch (InterruptedException e) {
                  e.printStackTrace();
                }
              }

              out.setForeground(Color.BLACK);
            }
          }
          .start();
        }

      }
      else
      {
        this.form.println(message);
      }
    }
  }
}