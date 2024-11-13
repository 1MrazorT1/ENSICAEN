let total = 0;

document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("asperges").addEventListener("click", () => choisir('asperges'));
    document.getElementById("carottes").addEventListener("click", () => choisir('carottes'));
    document.getElementById("oignons").addEventListener("click", () => choisir('oignons'));
    document.getElementById("cerises").addEventListener("click", () => choisir('cerises'));
    document.getElementById("payer").addEventListener("click", payer);
});

function choisir(produit) {
    total += prix(produit);
}

function prix(produit) {
    switch(produit) {
        case 'asperges': return 10;
        case 'carottes': return 5;
        case 'oignons': return 3;
        case 'cerises': return 20;
    }
}

function payer() {
    if (total === 0) {
        alert("Votre panier est vide!");
    } else {
        const confirmation = confirm("Vous devez payer " + total + " euros. Ça sera tout ?");
        if (confirmation) {
            total = 0;
        }
    }
}
