package com.pedrohlc.simplejchat;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Vector;

public class Server
  implements Runnable
{
  private Thread tinstance;
  private ServerSocket sock;
  private int port;
  private Vector<ServerClient> clients;

  public Server()
  {
    this.sock = null;
    this.port = 5000;
    this.clients = new Vector<ServerClient>();
    createSocket();
  }

  public Server(int port) {
    this.sock = null;
    this.port = port;
    this.clients = new Vector<ServerClient>();
    createSocket();
  }
  public int getPort() {
    return this.port; } 
  public void setPort(int value) { this.port = value; }

  private boolean createSocket()
  {
    try {
      this.sock = new ServerSocket(this.port);
    } catch (IOException e) {
      return false;
    }
    return true;
  }

  private Socket getNewClient()
  {
    try
    {
      return this.sock.accept();
    } catch (IOException e) {
      e.printStackTrace();
    }return null;
  }

  public void sendForAll(String message)
  {
    for (ServerClient client : this.clients)
      client.receiveFromSomeone(message);
  }

  public void run() {
    Socket newclient = null;
    int i = 0;
    while ((newclient = getNewClient()) != null) {
      this.clients.add(i, new ServerClient(i, newclient));
      i++;
    }
  }

  public ServerSocket getServerSocket() {
    return this.sock;
  }

  public void startListening() {
    this.tinstance = new Thread(this);
    this.tinstance.start();
  }
}