var points = [];
var t = 0.0;

function setup() {
  createCanvas(windowWidth, windowHeight);
  randomSeed(10);
  
  var squareSize = 80;
  var padding = 100;
  
  for (var y = 0; y < 5; y++) {
    var isEvenRow = y % 2 === 0;
    for (var x = isEvenRow ? 0 : 4; isEvenRow ? x < 5 : x >= 0; isEvenRow ? x++ : x--) {
      var leftBound = padding + x * padding;
      var topBound = padding + y * padding;
      var rightBound = leftBound + squareSize;
      var bottomBound = topBound + squareSize;
      
      var possibleXCoordinates = [leftBound, leftBound + squareSize / 3, leftBound + squareSize * 2 / 3, rightBound];
      var possibleYCoordinates = [topBound, topBound + squareSize / 3, topBound + squareSize * 2 / 3, bottomBound];
      
      for (var i = 0; i < 16; i++) {
        var xCoordinate = possibleXCoordinates[floor(random(0, possibleXCoordinates.length))];
        var yCoordinate = possibleYCoordinates[floor(random(0, possibleYCoordinates.length))];
        points.push(createVector(xCoordinate, yCoordinate, random(0, 2)));
      }
    }
  }
}

function draw() {
  background(0);
  stroke(255);
  
  t += 0.005;
  
  var noisyPoints = points.map(function (p) { return p5.Vector.add(p, createVector(noise(t + p.z) * 100, 0)); })
  
  var start = noisyPoints[0];
  for (var i = 1; i < noisyPoints.length; i++) {
    var end = noisyPoints[i];
    line(start.x, start.y, end.x, end.y);
    start = end;
  }
}

function windowResized() {
  resizeCanvas(windowWidth, windowHeight);
}