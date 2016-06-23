var ORIENTATIONS;

function setup() {
  createCanvas(512, 502);
  ORIENTATIONS = [0, HALF_PI];
}

function draw() {
  background(255);
  stroke(0);
  strokeWeight(2);
  
  var numLines = 800 * (width / 500);
  
  randomSeed(0);
  
  for (var i = 0; i < numLines; i++) {
    var origin = createVector(random(20, width-60), random(20, height-60));
    var length = random(10, 60);
    var orientation = ORIENTATIONS[floor(random(0, ORIENTATIONS.length))];
    var end = createVector(origin.x + length * cos(orientation), origin.y + length * sin(orientation))
    line(origin.x, origin.y, end.x, end.y);
  }
}

function windowResized() {
  resizeCanvas(windowWidth, windowHeight);
}