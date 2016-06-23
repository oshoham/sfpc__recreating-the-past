var counter;

function setup() {
  createCanvas(windowWidth, windowHeight);
  counter = 0;
}

function draw() {
  background(51);
  var elapsedSeconds = millis() / 1000;
  
  // amplitude modulation
  // var signal = map(sin(elapsedSeconds * 0.5), -1, 1, 0, 1);
  // ellipse(map(signal * sin(elapsedSeconds * 3), -1, 1, 0, width), 100, 10, 10)
  
  // frequency modulation
  counter = counter + map(sin(elapsedSeconds * 10), -1, 1, 0.01, 0.05);
  ellipse(map(sin(counter), -1, 1, 0, width), 100, 10, 10);
}