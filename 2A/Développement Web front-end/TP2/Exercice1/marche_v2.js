let total = 0;
let produits = ['asperges', 'carottes', 'oignons', 'cerises'];
let prix = [10, 5, 3, 20];
let panier = [0, 0, 0, 0];

document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("asperges").addEventListener("click", () => choisir(0));
    document.getElementById("carottes").addEventListener("click", () => choisir(1));
    document.getElementById("oignons").addEventListener("click", () => choisir(2));
    document.getElementById("cerises").addEventListener("click", () => choisir(3));
    document.getElementById("voir_panier").addEventListener("click", voir_panier);
    document.getElementById("payer").addEventListener("click", payer);
});

function choisir(numproduit) {
    const reponse = prompt("Quantité (en Kg) ?");
    if (reponse !== null) {
        panier[numproduit] += parseFloat(reponse);
        total += reponse * prix[numproduit];
    }
}

function voir_panier() {
    let string = "Votre panier :\n";
    for (let index in panier) {
        if (panier[index] !== 0) {
            string += `${produits[index]} (${panier[index]} Kg) : ${prix[index] * panier[index]} euros\n`;
        }
    }
    string += `Total = ${total} euros`;
    alert(string);
}

function payer() {
    if (total === 0) {
        alert("Votre panier est vide!");
    } else {
        voir_panier();
        const confirmation = confirm("Vous devez payer " + total + " euros. Ça sera tout ?");
        if (confirmation) {
            total = 0;
            panier = [0, 0, 0, 0];
        }
    }
}
