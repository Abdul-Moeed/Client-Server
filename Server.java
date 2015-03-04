import java.net.*;
import java.io.*;

public class Server extends Thread
{
   private ServerSocket serverSocket;
   
   public Server(int port) throws IOException
   {
      serverSocket = new ServerSocket(port);
      //serverSocket.setSoTimeout(10000);
   }

   public void run()

   {
      while(true)
      {
         try
         {
            System.out.println("S: Waiting for client on port " +
            serverSocket.getLocalPort() + "...");
            Socket server = serverSocket.accept();
            System.out.println("S: Just connected to "
                  + server.getRemoteSocketAddress());
            DataInputStream in =
                  new DataInputStream(server.getInputStream());
            System.out.println("S: "+in.readUTF());
            DataOutputStream out =
                 new DataOutputStream(server.getOutputStream());
            out.writeUTF("Thank you for connecting to "
              + server.getLocalSocketAddress() + "\nGoodbye!");
          
            //read and write file from client
            get_file(in);
            
            server.close();
         }catch(SocketTimeoutException s)
         {
            System.out.println("S: Socket timed out!");
            break;
         }catch(IOException e)
         {
            e.printStackTrace();
            break;
         }
      }
   }
   
   public static void main(String [] args)
   {
      int port = Integer.parseInt(args[0]);
      try
      {
         Thread t = new Server(port);
         t.start();
      }catch(IOException e)
      {
         e.printStackTrace();
      }
   }
   
   public void get_file(DataInputStream in) throws IOException{
	   //read file
	   int length;
	   String line;
	   String file_name;
	   
	   file_name = in.readUTF();
       length = Integer.parseInt(in.readUTF());
       PrintWriter writer = new PrintWriter(file_name+"_recieved.txt", "UTF-8");
       for(int i=0; i<length; i++){
    	   line = in.readUTF();
    	   writer.println(line);
       }
       writer.close();
   }
}
