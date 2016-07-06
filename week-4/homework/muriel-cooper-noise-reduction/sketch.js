var purple = '#5E3B65';
var black = '#202427';
var white = '#F3F1F2';
var points;
function setup() {
  createCanvas(windowWidth, windowHeight);
  points = [];
  t = 0;
}

function draw() {
  background(purple);
  stroke(255);
  
  translate(width / 2, height / 2);
  
  var a = -0.005;
  var b = 0.1;
  // var a = map(mouseX, 0, width, 1, 10);
  // var b = map(mouseY, 0, height, 1, 10);
  // var b = 0.3063489;
  
  stroke(white);
  noFill();
  beginShape();
  for (var i = 0; i < 1440; i++) {
    var angle = 0.1 * i;
    a -= millis() / 1000.0 * 0.0001;
    b -= millis() / 1000.0 * 0.000001;
    // equation for the logarithmic spiral
    var x = a * pow(Math.E, b * angle) * cos(angle);
    var y = a * pow(Math.E, b * angle) * sin(angle);
    // x = x + i * map(mouseX, 0, width, 0, 0.1);
    // equation for archimedes' spiral
    // var x = a + b * angle * cos(angle);
    // var y = a + b * angle * sin(angle);
    vertex(x, y);
  }
  endShape();
}

function windowResized() {
  resizeCanvas(windowWidth, windowHeight);
}