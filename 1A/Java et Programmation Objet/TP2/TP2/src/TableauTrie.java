import java.util.ArrayList;

public class TableauTrie implements Ordonnable{
    int taille;
    int increment;
    ArrayList<EntiersOrdonnables> tableau;
    public TableauTrie(int i, int j){
        this.taille=i;
        this.increment=j;
        this.tableau=new ArrayList<EntiersOrdonnables>();
    }

    @Override
    public boolean egal(Object o) {
        return false;
    }

    public int compareTo(Object o, int i){
        if(o instanceof EntiersOrdonnables){
            EntiersOrdonnables entier= (EntiersOrdonnables) o;
            return Integer.compare(this.tableau.get(i).entier,entier.entier);
        }else{
            throw new IllegalArgumentException("Object is not an instance of Ordonnable !");
        }
    }
    public void inserer(EntiersOrdonnables entier) {
        if(this.tableau.isEmpty()){
            this.tableau.add(entier);
        }else {
            int i = 0;
            while (i < this.tableau.size() && this.compareTo(entier,i) < 0) {
                i = i + 1;
            }
            this.tableau.add(i,entier);
        }
    }
    public void supprimer(Ordonnable entier){
        int i=0;
        while(i<this.tableau.size()){
            if(this.compareTo(entier,i) == 0){
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
            str=str+this.tableau.get(i).toString()+" ,";
        }
        str=str+".";
        return str;
    }
}
