import java.io.File;

public class affichage_2_sec extends Thread {
    public FileCopy fc;
    public long original_size;

    public affichage_2_sec(FileCopy fc) {
        this.fc = fc;
        this.original_size = new File(fc.original).length();
    }
    public void run(){
        while(fc.getNumberBytesCopied() != this.original_size){
            System.out.println("Number of bytes copied: " + fc.getNumberBytesCopied());
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}