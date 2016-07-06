var hueValues = [];
var saturationValues = [];
var brightnessValues = [];
var tileCountX = 50;
var tileCountY = 10;

function setup() {
  createCanvas(640, 640);
  colorMode(HSB, 360, 100, 100, 100);
  noStroke();
  
  for (var i = 0; i < tileCountX; i++) {
    hueValues.push(parseInt(random(360)));
    saturationValues.push(parseInt(random(100)));
    brightnessValues.push(parseInt(random(100)));
  }
}

function draw() {
  background(0, 0, 100);
  
  var counter = 0;
  var currentTileCountX = parseInt(map(mouseX, 0, width, 1, tileCountX));
  var currentTileCountY = parseInt(map(mouseY, 0, height, 1, tileCountY));
  var tileWidth = width / currentTileCountX;
  var tileHeight = height / currentTileCountY;
  
  for (var gridY = 0; gridY < tileCountY; gridY++) {
    for (var gridX = 0; gridX < tileCountX; gridX++) {
      var posX = tileWidth * gridX;
      var posY = tileHeight * gridY;
      var index = counter % currentTileCountX;
      
      fill(hueValues[index], saturationValues[index], brightnessValues[index]);
      rect(posX, posY, tileWidth, tileHeight);
      counter++;
    }
  }
}

function keyPressed() {
  if (key === '1') {
    for (var i = 0; i < tileCountX; i++) {
      hueValues[i] = parseInt(random(360));
      saturationValues[i] = parseInt(random(100));
      brightnessValues[i] = parseInt(random(100));
    }
  }
  
  if (key === '2') {
    for (var i = 0; i < tileCountX; i++) {
      hueValues[i] = parseInt(random(360));
      saturationValues[i] = parseInt(random(100));
      brightnessValues[i] = 100;
    }
  }
  
  if (key === '3') {
    for (var i = 0; i < tileCountX; i++) {
      hueValues[i] = parseInt(random(360));
      saturationValues[i] = 100;
      brightnessValues[i] = parseInt(random(100));
    }
  }
  
  if (key === '4') {
    for (var i = 0; i < tileCountX; i++) {
      hueValues[i] = 0;
      saturationValues[i] = 0;
      brightnessValues[i] = parseInt(random(100));
    }
  }
  
  if (key === '5') {
    for (var i = 0; i < tileCountX; i++) {
      hueValues[i] = 195;
      saturationValues[i] = 100;
      brightnessValues[i] = parseInt(random(100));
    }
  }
  
  if (key === '6') {
    for (var i = 0; i < tileCountX; i++) {
      hueValues[i] = 195;
      saturationValues[i] = parseInt(random(100));
      brightnessValues[i] = 100;
    }
  }
  
  if (key === '7') {
    for (var i = 0; i < tileCountX; i++) {
      hueValues[i] = parseInt(random(180));
      saturationValues[i] = 100;
      brightnessValues[i] = parseInt(random(100));
    }
  }
  
  if (key === '8') {
    for (var i = 0; i < tileCountX; i++) {
      hueValues[i] = parseInt(random(180, 360));
      saturationValues[i] = parseInt(random(80, 100));
      brightnessValues[i] = parseInt(random(50, 90));
    }
  }
  
  if (key === '9') {
    for (var i = 0; i < tileCountX; i++) {
      if (i % 2 === 0) {
        hueValues[i] = parseInt(random(360));
        saturationValues[i] = 100;
        brightnessValues[i] = parseInt(random(100));
      } else {
        hueValues[i] = 195;
        saturationValues[i] = parseInt(random(100));
        brightnessValues[i] = 100;
      }
    }
  }
}