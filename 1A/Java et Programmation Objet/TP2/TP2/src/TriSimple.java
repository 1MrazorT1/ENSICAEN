import java.util.ArrayList;

public class TriSimple {
    int taille;
    int increment;
    ArrayList<Integer> tableau;
    public TriSimple(int i, int j){
        this.taille=i;
        this.increment=j;
        this.tableau=new ArrayList<Integer>();
    }
    public void inserer(int entier) {
        if(this.tableau.isEmpty()){
            this.tableau.add(entier);
        }else {
            int i = 0;
            while (i < this.tableau.size() && entier > this.tableau.get(i)) {
                i = i + 1;
            }
            this.tableau.add(i,entier);
        }
    }
    public void supprimer(int entier){
        int i=0;
        while(i<this.tableau.size()){
            if(this.tableau.get(i)==entier){
                this.tableau.remove(i);
                return;
            }
            i=i+1;
        }
        return;
    }
    public String toString(){
        String str="La taille du tableau est "+Integer.parseInt(String.valueOf(this.tableau.size()))+"\n";
        str=str+"Le tableau :";
        for(int i=0;i<this.tableau.size();i++){
            str=str+Integer.parseInt(String.valueOf(this.tableau.get(i)))+" ,";
        }
        str=str+".";
        return str;
    }
}
