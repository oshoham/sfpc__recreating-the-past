function setup() {
  createCanvas(windowWidth, windowHeight);
  rectMode(CENTER);
}

function draw() {
  background(0);
  var elapsedSeconds = millis() / 1000;
  for (var i = 0; i < 100; i++) {
    ellipse(map(sin(elapsedSeconds * (1 + i / 50.0)), -1, 1, 0, width), i * 8, 5, 5);
  }
}