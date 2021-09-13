import java.net.*;
import java.io.*;
import java.util.LinkedList;
    
public class Gestionnaire{
    
    public static LinkedList<GestServ> annuaire = new LinkedList<GestServ>();
    private static final int MAX_DIFF = 5;
    
    public static void main(String[]args)
    {
	int port = 5555;
	if (args.length>0)
	    port = Integer.parseInt(args[0]);
	else
	    {
		System.out.println("Erreur, il faut entrer un numero du port en argument");
		System.exit(0);
	    }
	try{
	    ServerSocket server = new ServerSocket(port);

	    // On va creer un fichier txt contenant l'IP et le port du gestionnaire
	    try{ 
		File file = new File("gestionnaire.txt");
		if(file.createNewFile())
		    System.out.println("Fichier cree : "+file.getName());
		else
		    System.out.println("Fichier de gestionnaire deja existant");
		
		FileWriter fw = new FileWriter(file, false); // Efface le contenu du fichier avant d'ecrire
		fw.write(InetAddress.getLocalHost().getHostAddress()+"\n"+port);
		fw.close();
	    }catch(IOException e){
		System.out.println("Erreur à la création du fichier\n***Gestionnaire interrompu***");
		System.exit(0);
	    }

	    //Acceptation de nouvelles connexions entrantes
		System.out.println("before while");
	    while(true)
		{
			System.out.println("je suis dans le while");
		    Socket socket = server.accept();
			System.out.println("je suis dans le accept");
		    BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
		    PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
		    System.out.println("before bool");
		    boolean accept=true; // 
		    String mess = br.readLine();
		     System.out.println("readline");
		    GestServ gs = new GestServ(socket, mess);

		    
		    System.out.println("Message recu :"+mess);
		    switch(mess.substring(0,4))    // Test si le message recu est correct
			{
			case "REGI":   //Si un diffuseur veut s'inscrire
			    System.out.println("Request REGI");
			    if(annuaire.size() < MAX_DIFF) //Si le gestionnaire a de la place...
				{
				    annuaire.addLast(gs);
				    pw.write("REOK\r\n");
				    pw.flush();
				}
			    else
				{                             // Sinon on n'accepte pas la connexion
				    pw.write("RENO\r\n");
				    pw.flush();
				    accept = false;
				    System.out.println("Annuaire Plein");
				}
			    break;
			    
			case "LIST":
			    System.out.println("Request LIST");
			    break;
			    
			default:             //Pour un message non conforme, on ferme directement la socket
			    accept = false;
			    System.out.println("Type de message non reconnu !");
			}
		    
		    if(accept){
			Thread t = new Thread(gs);
			t.start();
		    }
		    else
			socket.close();
		}
	}catch(Exception e) {
	    System.out.println(e);
	    e.printStackTrace();
	}
    }
}
