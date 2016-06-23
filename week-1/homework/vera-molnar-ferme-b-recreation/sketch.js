var lines = [];

function setup() {
  createCanvas(windowWidth, windowHeight);
  
  var start = createVector(random(width), random(height));
  var length = random(20, 40);
  var angle = random(0, TWO_PI);
  var end = createVector(start.x + length * cos(angle), start.y + length * sin(angle));
  lines.push({ start: start, end: end });
  
  for (var i = 1; i < 100; i++) {
    var prevLine = lines[i-1];
    start = createVector(random(prevLine.start.x, prevLine.end.x), random(prevLine.start.y, prevLine.end.y));
    length = random(20, 40);
    angle = random(0, 2 * PI / 3);
    end = createVector(start.x + length * cos(angle), start.y + length * sin(angle));
    
    lines.push({ start: start, end: end });
  }
}

function draw() {
  background(236, 229, 226);
  fill(236, 229, 226);
  stroke(67, 12, 17);
  strokeWeight(4);

  lines.forEach(function (l) {
    line(l.start.x, l.start.y, l.end.x, l.end.y);
  });
}

function doLineSegmentsIntersect(line1Start, line1End, line2Start, line2End, intersection) {
  var diffLine1 = p5.Vector.sub(line1End, line1Start);
  var diffLine2 = p5.Vector.sub(line2End, line2Start);
  var compareLine1 = diffLine1.x * line1Start.y - diffLine1.y * line1Start.x;
  var compareLine2 = diffLine2.x * line2Start.y - diffLine2.y * line2Start.x;
  
  if (
    (
      ((diffLine1.x * line2Start.y - diffLine1.y * line2Start.x) < compareLine1) !==
      ((diffLine1.x * line2End.y - diffLine1.y * line2End.x) < compareLine1)
    )
    &&
    (
      ((diffLine2.x * line1Start.y - diffLine2.y * line1Start.x) < compareLine2) !==
      ((diffLine2.x * line1End.y - diffLine2.y * line1End.x) < compareLine2)
    )
  ) {
    var lDetDivInv = 1 / ((diffLine1.x * diffLine2.y) - (diffLine1.y * diffLine2.x));
		intersection.x =  -((diffLine1.x * compareLine2) - (compareLine1 * diffLine2.x)) * lDetDivInv;
		intersection.y =  -((diffLine1.y * compareLine2) - (compareLine1 * diffLine2.y)) * lDetDivInv;
    return true;
  }
  
  return false;
}