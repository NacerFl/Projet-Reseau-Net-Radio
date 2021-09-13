import java.net.*;
import java.io.*;
import java.lang.*;
import java.util.LinkedList;

public class GestServ implements Runnable{
    public Socket socket; // 
    public String mess; //message récupéré du destinataire
    public String id,ip1,ip2,port1,port2; //[REGI]
    
    public GestServ(Socket s, String mess){
	this.socket = s;
	this.mess = mess;
    }
    
    public void run()
    {
	try{
	    BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
	    PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));

	    LinkedList<GestServ> gs = Gestionnaire.annuaire;
	    
	    switch(this.mess.substring(0,4))
		{
		case "":
		    pw.print("LINB "+ gs.size()+"\r\n");
		    pw.flush();
		    for(GestServ g : gs)
			{
			    pw.print("ITEM "+g.id+" "+g.ip1+" "+g.port1+" "+g.ip2+" "+g.port2+"\r\n");
			    pw.flush();
			}
		    break;
		case "REGI":
		    this.id = this.mess.substring(5,13);
		    this.ip1 = this.mess.substring(14,29);
		    this.port1 = this.mess.substring(30,34);
		    this.ip2 = this.mess.substring(35,50);
		    this.port2 = this.mess.substring(51);

		    // ARE YOU OK ANNIE

		    String str;
		    do{
			pw.print("RUOK\r\n");
			pw.flush();
			//long millis = System.currentTimeMillis();
			str = br.readLine();
			//if(System.currentTimeMillis() - millis > 5000)
			   // break;
			Thread.sleep(5000);
		    }while(str.substring(0,4).equals("IMOK"));
		    break;
		default:
		    System.out.println("Ca ne devrait pas s'afficher");
		}
	    System.out.println("Message recu :"+mess);

	    br.close();
	    pw.close();
	    socket.close();
	    gs.remove(this); // Retrait de l'annuaire pour les diffuseurs, sans importance pour les utilisateurs
	}catch(Exception e){
	    System.out.println(e);
	    e.printStackTrace();
	}
    }
}
