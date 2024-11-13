// ===================================================================================

// ===================================================================================
// canvasImage : image sur un canvas
// nameImg : URL de l'image
// (posX,posY) : position du coin supérieur gauche de l'image dans le canvas
// ctx : contexte graphique
function canvasImage(imgURL,posX,posY,ctx)
{
    var img = new Image();

    // initialisation des propriétées de l'image
    img.src = imgURL;
    img.posX = posX;   
    img.posY = posY;
    img.ctx = ctx;

    return img;
}
// -----------------------------------------------------------------------------------
// Dessine l'image sur le canvas
// imge: graphics source
// (posX,posY) : position du coin supérieur gauche de l'image dans le canvas
function drawCanvasImage(image,posX,posY)
{   // attente du chargement de l'image et affichage si celui-ci est terminé
    image.addEventListener('load', imageLoaded, false);
    function imageLoaded(evt) {
        image.ctx.drawImage(img, posX, posY);	
    }
}
// ===================================================================================
// Constructeur for an animation object
// image: graphics source
// (x, y): position to draw the animation
// width, height: size of each tile
// nbXTiles : nombre de tiles horizontalement
// nbYTiles : nombre de tiles verticallement
// loop : animation en boucle (true) ou non (false)
function CanvasSprite(spriteImgURL, x, y, widthTile, heightTile, nbXTiles, nbYTiles,ctx)
{   
    this.image = canvasImage(spriteImgURL, x, y,ctx);
    this.widthTile = widthTile;
    this.heightTile = heightTile;
    this.nbXTiles = nbXTiles;
    this.nbYTiles = nbYTiles;
    this.animations = [];
    this.currentAnimation = null;
    this.currentTile = 0;
    this.loop = false;
    this.timeID = 0;  
}
// -----------------------------------------------------------------------------------
// Ajout d'une animation spécifique
// nameAnim : nom de l'animation
// tiles : tableau d'indices de tile
CanvasSprite.prototype.addAnimation = function(nameAnim, tiles)
{
    this.animations.push({ name: nameAnim, tiles: tiles}) 
}
// -----------------------------------------------------------------------------------
// Sélectionne une animation spécifique nameAnim
CanvasSprite.prototype.selectAnimation = function(nameAnim, loop)
{
    for (var i = 0; i < this.animations.length; i++) {
        if (this.animations[i].name === nameAnim) {
            this.currentAnimation = this.animations[i];
            console.log("Animation now selected: "+ nameAnim +".");
            this.loop = loop;
            this.currentTile=0;
            return;
        }
    }
    console.error("Animation with name '" + nameAnim + "' not found.");
}
// -----------------------------------------------------------------------------------
// Sélectionne la tile suivante et la dessine, si la tile existe (mode sans boucle)
// retourne false si la tile courrante est la dernière (mode sans boucle), true sinon
CanvasSprite.prototype.nextTile = function()
{
    if (this.currentAnimation.length > 0 && this.currentTile < this.currentAnimation.length - 1) {
        this.currentTile++;
        //this.drawTile(this.currentTile);
        return true; // Renvoie true car il y a une tile suivante
    } else {
        return false; // Renvoie false car la tile courante est la dernière
    }

}
// -----------------------------------------------------------------------------------
// Retourne la position de la tile dans le sprite selon x
CanvasSprite.prototype.tileX = function(tileIndex)
{
	return  (tileIndex % this.nbXTiles) * this.nbXTiles; 
}
// -----------------------------------------------------------------------------------
// Retourne la position de la tile dans le sprite selon y
CanvasSprite.prototype.tileY = function(tileIndex)
{
	return (tileIndex % this.nbYTiles) * this.heightTile;
}
// -----------------------------------------------------------------------------------
// Dessine une tile
CanvasSprite.prototype.drawTile = function(tileIndex) {
    var sourceX = this.tileX(this.currentAnimation.tiles[tileIndex]);
    var sourceY = this.tileY(this.currentAnimation.tiles[tileIndex]);

    this.image.ctx.clearRect(0, 0, this.widthTile, this.heightTile);

    this.image.ctx.drawImage(
        this.image,
        sourceX, sourceY, this.widthTile, this.heightTile,
        0, 0, this.widthTile, this.heightTile
    );
};
// ----------------------------------------------------------------------------------
// Dessine une tile
CanvasSprite.prototype.simpleAnim = function(tps) {
    
    var self = this;
    this.loop = true;
    this.image.ctx.clearRect(0, 0, this.widthTile, this.heightTile);
    for(var i=0;i<8;i++){
        self.drawTile(self.currentTile);
        self.nextTile();
        console.log(self.currentTile);
        console.log("test");
        }
    if (self.nextTile() === false) {
        self.currentTile = self.currentAnimation.tiles[0];
    }
    //this.timeID = setInterval(function() { }, tps);
}
// ----------------------------------------------------------------------------------
CanvasSprite.prototype.stopAnim = function()
{
	clearInterval(this.timeID);
    this.loop = false;
}
// ----------------------------------------------------------------------------------


function Start_StopAnim() {
    var courir = [0,1,2,3,4,5,6,7];
    var canva = document.getElementById("canvanim").getContext("2d");
    var chat = new CanvasSprite("./images/chat.png", 0, 0, 512, 256, 2, 4, canva);
    chat.addAnimation("courir", courir);
    chat.selectAnimation("courir", false);
    if(chat.loop) {
        console.log(document);
        chat.loop = false;
        chat.stopAnim();
    } else {
        console.log(chat.image.ctx);
        chat.loop = true;
        chat.simpleAnim(300);
    }
}