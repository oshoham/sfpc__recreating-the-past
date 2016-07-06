var tileCount = 20;
var circleAlpha = 180;
var circleColor;
var noisePermutations;

var t = 0.0;

function setup() {
  createCanvas(600, 600);
  circleColor = color(0);
  
  randomSeed(0);
  
  noisePermutations = [];
  for (var i = 0; i < tileCount; i++) {
    noisePermutations[i] = [];
    for (var j = 0; j < tileCount; j++) {
      noisePermutations[i][j] = { x: random(0, 2), y: random(0, 2) };
    }
  }
}

function draw() {
  translate(width / tileCount / 2, height / tileCount / 2);
  background(255);
  noFill();
  
  stroke(circleColor, circleAlpha);
  strokeWeight(mouseY/60);
  
  t += 0.008;
  
  for (var gridY = 0; gridY < tileCount; gridY++) {
    for (var gridX = 0; gridX < tileCount; gridX++) {
      var posX = width / tileCount * gridX;
      var posY = height / tileCount * gridY;
      
      var shiftX = noise(t + noisePermutations[gridY][gridX].x) * 25;
      var shiftY = noise(t + noisePermutations[gridY][gridX].y) * 25;
      
      ellipse(posX + shiftX, posY + shiftY, mouseY/15, mouseY/15);
    }
  }
}