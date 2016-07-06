var pointCount = 600;
var freqX = 1;
var freqY = 4;
var freqZ = 2;
var phiX = 0.0;
var phiY = 0.0;
var lissajousPoints;

var offsetX = 0;
var offsetY = 0;
var clickX = 0;
var clickY = 0;
var zoom = -1000;
var rotationX = 0.0;
var rotationY = 0.0;
var targetRotationX = 0.0;
var targetRotationY = 0.0;
var clickRotationX;
var clickRotationY;

function setup() {
  createCanvas(displayWidth, displayHeight, WEBGL);
  lissajousPoints = calculateLissajousPoints();
}

function draw() {
  background(255);
  ambientLight(128, 128, 128);
  directionalLight(128, 128, 128, 0, 0, -1);
  
  // set view
  translate(0, 0, zoom);
  if (mouseIsPressed && mouseButton === RIGHT) {
    offsetX = mouseX - clickX;
    offsetY = mouseY - clickY;
    targetRotationX = constrain(clickRotationX + offsetY / parseFloat(width) * TWO_PI, -HALF_PI, HALF_PI);
    targetRotationY = clickRotationY + offsetX / parseFloat(height) * TWO_PI;
  }
  rotationX += (targetRotationX - rotationX) * 0.25;
  rotationY += (targetRotationY - rotationY) * 0.25;
  rotateX(-rotationX);
  rotateY(-rotationY);
  
  // draw triangles
  noStroke();
  beginShape(TRIANGLE_FAN);
  for (var i = 0; i < pointCount - 2; i++) {
    if (i % 3 === 0) {
      // gradient for every triangle to lissajou path
      ambientMaterial(50);
      vertex(0, 0, 0);
      ambientMaterial(200);
      vertex(lissajousPoints[i].x, lissajousPoints[i].y, lissajousPoints[i].z);
      vertex(lissajousPoints[i+2].x, lissajousPoints[i+2].y, lissajousPoints[i+2].z);
    }
  }
  endShape();
  
  // draw lissajous path
  stroke(0);
  strokeWeight(1);
  noFill();
  beginShape();
  for (var i = 0; i <= pointCount; i++) {
    vertex(lissajousPoints[i].x, lissajousPoints[i].y, lissajousPoints[i].z);
  }
  endShape();
}

function mousePressed() {
  clickX = mouseX;
  clickY = mouseY;
  clickRotationX = rotationX;
  clickRotationY = rotationY;
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
    case '5':
      freqZ--;
      break;
    case '6':
      freqZ++;
      break;
  }
  freqX = max(freqX, 1);
  freqY = max(freqY, 1);
  freqZ = max(freqZ, 1);
  
  switch(keyCode) {
    case LEFT_ARROW:
      phiX -= 15;
      break;
    case RIGHT_ARROW:
      phiX += 15;
      break;
    case DOWN_ARROW:
      phiY -= 15;
      break;
    case UP_ARROW:
      phiY += 15;
      break;
  }
  
  lissajousPoints = calculateLissajousPoints();
}

function calculateLissajousPoints() {
  var points = [];
  var f = width / 2.0;
  
  for (var i = 0; i <= pointCount; i++) {
    var angle = map(i, 0, pointCount, 0, TWO_PI);
    var x = sin(angle * freqX + radians(phiX)) * sin(angle * 2) * f;
    var y = sin(angle * freqY + radians(phiY)) * f;
    var z = sin(angle * freqZ) * f;
    points[i] = createVector(x, y, z);
  }
  
  return points;
}