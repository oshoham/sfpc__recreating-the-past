var lines = [];

function setup() {
  createCanvas(640, 360);
}

function draw() {
  background(0);
  for (var iterations = 0; iterations < 100; iterations++) {
    // make a new line at a random point facing a random direction
    var angle = random(0, TWO_PI);
    var x = random(0, width);
    var y = random(0, height);
    
    var newLine = {
      start: createVector(x, y),
      end: createVector(x + 20 * cos(angle), y + 20 * sin(angle))
    };
    
    // check whether the new line intersects with any existing lines
    var doesIntersect = false;
    for (var i = 0; i < lines.length; i++) {
      if (doLineSegmentsIntersect(newLine.start, newLine.end, lines[i].start, lines[i].end)) {
        doesIntersect = true;
        break;
      }
    }
    
    if (!doesIntersect) {
      lines.push(newLine);
    }
  }
  
  // draw the lines
  stroke(255);
  lines.forEach(function (l) {
    line(l.start.x, l.start.y, l.end.x, l.end.y);
  });
}

// adapted from https://github.com/openframeworks/openFrameworks/blob/master/libs/openFrameworks/math/ofMath.cpp#L264
function doLineSegmentsIntersect(line1Start, line1End, line2Start, line2End) {
  var diffLine1 = p5.Vector.sub(line1End, line1Start);
  var diffLine2 = p5.Vector.sub(line2End, line2Start);
  var compareLine1 = diffLine1.x * line1Start.y - diffLine1.y * line1Start.x;
  var compareLine2 = diffLine2.x * line2Start.y - diffLine2.y * line2Start.x;
  
  return (
    (
      ((diffLine1.x * line2Start.y - diffLine1.y * line2Start.x) < compareLine1) !==
      ((diffLine1.x * line2End.y - diffLine1.y * line2End.x) < compareLine1)
    )
    &&
    (
      ((diffLine2.x * line1Start.y - diffLine2.y * line1Start.x) < compareLine2) !==
      ((diffLine2.x * line1End.y - diffLine2.y * line1End.x) < compareLine2)
    )
  );
}