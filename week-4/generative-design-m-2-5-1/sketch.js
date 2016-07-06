var pointCount = 1000;
var freqX = 4;
var freqY = 7;
var phi = 15;
var lissajousPoints = [];

var modFreqX = 3;
var modFreqY = 2;

var lineWeight = 1;
var lineColor;
var lineAlpha = 50;

var connectionRadius = 100;
var connectionRamp = 6;

function setup() {
  createCanvas(displayWidth, displayHeight);
  calculateLissajousPoints();
  lineColor = color(0);
  drawLissajous();
}

function draw() {
  
}

function drawLissajous() {
  background(255);
  strokeWeight(lineWeight);
  strokeCap(ROUND);
  noFill();
  
  push();
  translate(width / 2, height / 2);
  
  for (var i = 0; i < pointCount; i++) {
    for (var j = 0; j < i; j++) {
      var p1 = lissajousPoints[i];
      var p2 = lissajousPoints[j];
      
      var d = p5.Vector.dist(p1, p2);
      var a = pow(1 / (d / connectionRadius + 1), 6);
      
      if (d < connectionRadius) {
        stroke(lineColor, a * lineAlpha);
        line(p1.x, p1.y, p2.x, p2.y);
      }
    }
  }
  
  pop();
}

function calculateLissajousPoints() {
  lissajousPoints = [];
  
  for (var i = 0; i <= pointCount; i++) {
    var angle = map(i, 0, pointCount, 0, TWO_PI);
    var x = sin(angle * freqX + radians(phi)) * cos(angle * modFreqX);
    var y = sin(angle * freqY) * cos(angle * modFreqY);
    
    x = x * (width / 2 - 30);
    y = y * (height / 2 - 30);
    
    lissajousPoints[i] = createVector(x, y);
  }
}

function keyPressed() {
  switch(key) {
    case '1':
      freqX--;
      break;
    case '2':
      freqX++;
      break;
    case '3':
      freqY--;
      break;
    case '4':
      freqY++;
      break;
    case '7':
      modFreqX--;
      break;
    case '8':
      modFreqX++;
      break;
    case '9':
      modFreqY--;
      break;
    case '0':
      modFreqY++;
      break;
  }
  freqX = max(freqX, 1);
  freqY = max(freqY, 1);
  modFreqX = max(modFreqX, 1);
  modFreqY = max(modFreqY, 1);
  
  switch(keyCode) {
    case LEFT_ARROW:
      phi -= 15;
      break;
    case RIGHT_ARROW:
      phi += 15;
      break;
  }
  
  calculateLissajousPoints();
  drawLissajous();
}