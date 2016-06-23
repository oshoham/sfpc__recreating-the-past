function setup() {
  createCanvas(windowWidth, windowHeight);
  rectMode(CENTER);
}

function draw() {
  background(0);
  var elapsedSeconds = millis() / 1000; // p5.js only gives us elapsed milliseconds so we need to convert to seconds
  rect(map(sin(elapsedSeconds), -1, 1, 0, width), 100, 50, 50);
}