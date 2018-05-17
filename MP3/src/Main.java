import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.Path;
import javazoom.jl.player.Player;

//link de descarga de la libreria: http://www.javazoom.net/javalayer/sources.html

class MP3 {
    private String filename;
    private Player player;

    // constructor that takes the name of an MP3 file
    public MP3(String filename) {

        this.filename = filename;
    }

    public void close() {
        if (player != null) player.close();
    }

    // play the MP3 file to the sound card
    public void play() {
        try {
            File file = new File(filename);
            //byte[] bytesArray = new byte[(int) file.length()];
            byte[] bytesArray = new byte[7260924/2];    ///Testeo de la mitad de los bytes de la cancion

            System.out.println((int) file.length());    /// cantidad total de bytes

            FileInputStream fis = new FileInputStream(file);
            fis.read(bytesArray); //read file into bytes[]
            fis.close();

            //for(int i = 0; i<bytesArray.length;i++){
              //  System.out.println(bytesArray[i]);
            //}

            //FileInputStream fis = new FileInputStream(filename);
            ByteArrayInputStream data = new ByteArrayInputStream(bytesArray);
            BufferedInputStream bis = new BufferedInputStream(data);
            player = new Player(bis);
        } catch (Exception e) {
            System.out.println("Problem playing file " + filename);
            System.out.println(e);
        }

        // run in new thread to play in background
        new Thread() {
            public void run() {
                try {
                    player.play();
                } catch (Exception e) {
                    System.out.println(e);
                }
            }
        }.start();


    }


    // test client
    public static void main(String[] args) throws IOException {
        
        String filename = "/home/racso/Project#2/Bella.mp3";
        MP3 mp3 = new MP3(filename);
        mp3.play();

        // do whatever computation you like, while music plays
        int N = 4000;
        double sum = 0.0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                sum += Math.sin(i + j);
            }
        }
        System.out.println(sum);

        // when the computation is done, stop playing it
        mp3.close();

        // play from the beginning
        mp3 = new MP3(filename);
        mp3.play();



    }
}