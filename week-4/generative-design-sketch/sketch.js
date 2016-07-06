var NORTH = 0;
var EAST = 1;
var SOUTH = 2;
var WEST = 3;

var direction = SOUTH;
var stepSize = 3;
var minLength = 10;
var angleCount = 7;
var pos;
var posCross;
var angle;

var canvas;

function setup() {
  canvas = createCanvas(600, 600);
  background(255);
  
  angle = getRandomAngle(direction);
  pos = createVector(random(width), 5);
  posCross = pos.copy();
}

function draw() {
  for (var i = 0; i < mouseX; i++) {
    // strokeWeight(1);
    // stroke(120);
    // point(pos.x, pos.y);
    
    pos.add(createVector(cos(radians(angle)) * stepSize, sin(radians(angle)) * stepSize));

    var reachedBorder = false;
    if (pos.y <= 0) {
      direction = SOUTH;
      reachedBorder = true;
    } else if (pos.x >= width) {
      direction = WEST;
      reachedBorder = true;
    } else if (pos.y >= height) {
      direction = NORTH;
      reachedBorder = true;
    } else if (pos.x <= 0) {
      direction = EAST;
      reachedBorder = true;
    }
    
    var pixelColor = getPixel(pos.x, pos.y);

    if (pixelColor[0] !== 255 || reachedBorder) {
      angle = getRandomAngle(direction);
      var distance = dist(pos.x, pos.y, posCross.x, posCross.y);
      if (distance >= minLength) {
        strokeWeight(distance / 50.0);
        stroke(0);
        line(pos.x, pos.y, posCross.x, posCross.y);
      }
      posCross = pos.copy();
    }
  }
}

function getRandomAngle(direction) {
  var a = (floor(random(-angleCount, angleCount)) + 0.5) * 90.0 / angleCount;
  if (direction === NORTH) { return a - 90; }
  if (direction === EAST) { return a; }
  if (direction === SOUTH) { return a + 90; }
  if (direction === WEST) { return a + 180; }
  return 0;
}

// adapted from https://github.com/processing/p5.js/pull/1488/files
// because that commit hasn't made it into a p5 release yet
function getPixel(x, y, w, h) {
  if (x === undefined && y === undefined &&
      w === undefined && h === undefined){
    x = 0;
    y = 0;
    w = width;
    h = height;
  } else if (w === undefined && h === undefined) {
    w = 1;
    h = 1;
  }

  // if the section does not overlap the canvas
  if(x + w < 0 || y + h < 0 || x > width || y > height){
    return [0, 0, 0, 255];
  }

  var pd = pixelDensity();

  // round down to get integer numbers
  x = Math.floor(x);
  y = Math.floor(y);

  var sx = x * pd;
  var sy = y * pd;
  if (w === 1 && h === 1){
    var imageData = canvas.drawingContext.getImageData(sx, sy, 1, 1).data;
    //imageData = [0,0,0,0];
    return [
      imageData[0],
      imageData[1],
      imageData[2],
      imageData[3]
    ];
  } else {
    //auto constrain the width and height to
    //dimensions of the source image
    var dw = Math.min(w, width);
    var dh = Math.min(h, height);
    var sw = dw * pd;
    var sh = dh * pd;

    var region = new p5.Image(dw, dh);
    region.canvas.getContext('2d').drawImage(canvas, sx, sy, sw, sh,
      0, 0, dw, dh);

    return region;
  }
}