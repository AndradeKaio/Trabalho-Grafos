import java.io.*;
import java.net.*;
 
public class Grafos 
{
 
   public int Fila [];

   public static String getHtml(String endereco)
   {
      URL url;
      InputStream is = null;
      BufferedReader br;
      String resp = "", line;
 
      try 
      {
         url = new URL(endereco);
         is = url.openStream();  // throws an IOException
         br = new BufferedReader(new InputStreamReader(is));
 
         while ((line = br.readLine()) != null) 
         {
            resp += line + "\n";
         }
 
         is.close();
      } 
      catch (MalformedURLException mue) 
      {
         mue.printStackTrace();
      } 
      catch (IOException ioe) 
      {
         ioe.printStackTrace();
      } 
/*
      try {
      } catch (IOException ioe) {
         ioe.printStackTrace();
      }
*/
      return resp;
   }
   public static void main(String[] args) 
   {
      String endereco = MyIO.readLine(); 
       
      while(endereco.equals("FIM") == false)
      {
         String html = getHtml(endereco);
         System.out.println(endereco + " (numero de bytes obtidos " + html.length() + ")");
         endereco = MyIO.readLine();
      }
   }
}