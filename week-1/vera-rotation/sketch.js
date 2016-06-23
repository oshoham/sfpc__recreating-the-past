function setup() {
  createCanvas(1000, 760);
  rectMode(CENTER);
}

function draw() {
  background(0);
  randomSeed(mouseX * 100)
  
  for (var i = 0; i < 20; i++) {
    for (var j = 0; j < 20; j++) {
      push();
      translate(50 + i * 30, 50 + j * 30);
      if (random(0, 1) < 0.5) {
        rotate(PI/4);
      }
      rect(0, 0, 20, 20);
      pop();
    }
  }
}