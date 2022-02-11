import java.io.*;
import java.net.*;
import java.util.*;

class testUDPCon{
    public static void main(String[] args) {
        try {
            System.out.println("Starting");
            String messageStr = "startMsg";
            int server_port = 5560;
            
            DatagramSocket s = new DatagramSocket();
            InetAddress local = InetAddress.getByName("192.168.1.255");

            DatagramPacket p = new DatagramPacket(messageStr.getBytes(), messageStr.getBytes().length, local, server_port);
            int a = 0;
            
            while(a<20){
                System.out.println("Sending");
                s.send(p);
                Thread.sleep(5000);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}