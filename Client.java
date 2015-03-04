import java.net.*;
import java.io.*;

public class Client
{
   public static void main(String [] args)
   {
      String serverName = "localhost";//args[0];
      int port = 55556;//Integer.parseInt(args[1]);
      try
      {
         System.out.println("C: Connecting to " + serverName
                             + " on port " + port);
         Socket client = new Socket(serverName, port);
         System.out.println("C: Just connected to "
                      + client.getRemoteSocketAddress());
         OutputStream outToServer = client.getOutputStream();
         DataOutputStream out =
                       new DataOutputStream(outToServer);

         out.writeUTF("Hello from "
                      + client.getLocalSocketAddress());
         InputStream inFromServer = client.getInputStream();
         DataInputStream in =
                        new DataInputStream(inFromServer);
         System.out.println("C: Server says " + in.readUTF());
         
         Reader fr = new Reader();
         String file_name = "file";
         fr.read_file(file_name+".txt");
         out.writeUTF(file_name);
         out.writeUTF(Integer.toString(fr.total_lines));
         for(int i=0;i<fr.total_lines;i++){
        	 out.writeUTF(fr.instructions.get(i));
         }
         
         client.close();
      }catch(IOException e)
      {
         e.printStackTrace();
      }
   }
}
