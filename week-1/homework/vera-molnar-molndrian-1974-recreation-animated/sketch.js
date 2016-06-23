var ORIENTATIONS;
var lines;
var t = 0.0;

function setup() {
  createCanvas(windowWidth, windowHeight);
  ORIENTATIONS = [0, HALF_PI];
  lines = [];
  
  var numLines = 800 * (windowWidth / 500);
  
  randomSeed(0);
  
  for (var i = 0; i < numLines; i++) {
    var origin = createVector(random(20, width-40), random(20, height-40));
    var length = random(10, 60);
    var orientation = ORIENTATIONS[floor(random(0, ORIENTATIONS.length))];
    
    lines.push({
      origin: origin,
      length: length,
      orientation: orientation,
      noisePermutation: random(0, 2) // the range of noisePermutation affects how different the behavior of each line is
    })
  }
}

function draw() {
  background(255);
  stroke(0);
  strokeWeight(2);
  
  t += 0.008; // the amount we add to t affects how fast the Perlin noise changes
  
  lines.forEach(function(l) {
    var noisyLength = l.length * noise(t + l.noisePermutation) * 2
    var end = createVector(l.origin.x + noisyLength * cos(l.orientation), l.origin.y + noisyLength * sin(l.orientation))
    line(l.origin.x, l.origin.y, end.x, end.y);
  })
}

function windowResized() {
  resizeCanvas(windowWidth, windowHeight);
  setup();
}