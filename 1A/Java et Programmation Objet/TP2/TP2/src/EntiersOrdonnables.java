class EntiersOrdonnables implements Ordonnable {
    int entier;
    public EntiersOrdonnables(String entier) {
        this.entier=Integer.parseInt(entier);
    }
    public String toString(){
        return String.valueOf(this.entier);
    }
    public boolean egal(Object o){
        if(o instanceof Ordonnable){
            EntiersOrdonnables entier= (EntiersOrdonnables) o;
            return this.entier == entier.entier;
        }else{
            return false;
        }
    }

    @Override
    public int compareTo(Object o, int i) {
        return 0;
    }

    public int compareTo(Object o){
        if(o instanceof Ordonnable){
            EntiersOrdonnables entier= (EntiersOrdonnables) o;
            return Integer.compare(this.entier,entier.entier);
        }else{
            throw new IllegalArgumentException("Object is not an instance of Ordonnable !");
        }
    }
}