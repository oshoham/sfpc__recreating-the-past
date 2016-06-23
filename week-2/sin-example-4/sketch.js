var points;
var angles;

function setup() {
  createCanvas(640, 640);
  points = [];
  angles = [0, HALF_PI, PI, 3 * HALF_PI];
  ellipseMode(CENTER);
}

function draw() {
  background(51);
  stroke(255);
  // circle formula
  
  // x = xorig + radius * cos(angle)
  // y = yorig + radius * sin(angle)
  
  var elapsedSeconds = millis() / 1000;
  
  translate(width / 2, height / 2);
  
  var x = 250 * cos(elapsedSeconds * 3.1);
  var y = 250 * sin(elapsedSeconds * 2.7);
  
  // ellipse(x, y, 10, 10);
  
  points.push({ x: x, y: y });
  
  if (points.length > 200) {
    points.splice(0, 1);
  }
  
  noFill();
  
  for (var i = 0; i < angles.length; i++) {
    var angle = angles[i];
    push();
    rotate(angle);
    beginShape();
    for (var j = 0; j < points.length; j++) {
      vertex(points[j].x, points[j].y);
    }
    endShape();
    pop();
  }
}