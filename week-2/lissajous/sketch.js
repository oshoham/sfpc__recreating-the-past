var points;
var angles;
var colors;
var currentColorIndex;

function setup() {
  createCanvas(640, 640);
  points = [];
  angles = [0, HALF_PI, PI, 3 * HALF_PI];
  colors = ['#DD1E2F', '#EBB035', '#06A2CB',	'#218559', '#D0C6B1', '#192823'];
  currentColorIndex = 0;
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
  
  if (elapsedSeconds % 1 < 0.02) {
    currentColorIndex = (currentColorIndex + 1) % (colors.length - 1);
  }
  
  points.push({ x: x, y: y, c: currentColorIndex });
  
  if (points.length > 300) {
    points.splice(0, 1);
  }
  
  noFill();
  stroke(colors[points[0].c]);
  
  for (var i = 0; i < angles.length; i++) {
    var angle = angles[i];
    rotate(angle);
    beginShape();
    var prevColorIndex = currentColorIndex;
    for (var j = 0; j < points.length; j++) {
      if (points[j].c !== prevColorIndex) {
        stroke(colors[prevColorIndex]);
        endShape();
        beginShape();
      }
      vertex(points[j].x, points[j].y);
    }
    endShape();
    rotate(-angle);
  }
}