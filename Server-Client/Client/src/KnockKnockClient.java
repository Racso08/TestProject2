import java.io.*;
import java.net.*;

public class KnockKnockClient
{
    public static void main(String[] args) throws IOException
    {
        Socket kkSocket = null;
        ObjectOutputStream oos=null;
        Sample s;
        String str="hello dude";

        try{
            kkSocket = new Socket("localhost", 4455);
            oos = new ObjectOutputStream(kkSocket.getOutputStream());
        }
        catch (UnknownHostException e)
        {
            System.err.println("Don't know about host: 192.168.1.137.");
            System.exit(1);
        }
        catch (IOException e)
        {
            System.err.println("Couldn't get I/O for the connection to: 192.168.1.137.");
            System.exit(1);
        }
        s=new Sample();

        oos.writeObject(str);

        System.out.println("name :" + s.name);
        System.out.println("age  :" + s.value);
        kkSocket.close();
    }
}
class Sample implements Serializable
{
    String name="xyz";
    int value=10;
}