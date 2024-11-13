import java.io.*;

import static java.lang.Thread.sleep;

public class FileCopy {
    public String original;
    private String copy;
    private int temp;
    private int number_bytes_written;

    public FileCopy(String original, String copy){
        this.original = original;
        this.copy = copy;
        this.temp = 0;
        this.number_bytes_written = 0;
    }

    public void duplicateFile(){
        try(InputStream text_original = new FileInputStream(this.original);
            OutputStream copy = new FileOutputStream(this.copy)){
            int bytesRead;
            while((bytesRead = text_original.read()) != -1){
                copy.write(bytesRead);
                this.number_bytes_written++;
                sleep(this.temp);
            }
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    public void setTemporisation(int temp){
        this.temp = temp;
    }

    public int getNumberBytesCopied(){
        return(this.number_bytes_written);
    }
}