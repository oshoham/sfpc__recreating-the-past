function setup() {
  createCanvas(1000, 740);
}

function draw() {
  background(0);
  stroke(255);
  
  randomSeed(mouseX * 10000);
  
  for (var i = 0; i < 30; i++) {
    for (var j = 0; j < 30; j++) {
      var randomAngle = random(0, TWO_PI);
      
      var origin = createVector(100 + 20 * i, 100 + j * 20);
      var direction = createVector(cos(randomAngle), sin(randomAngle));
      
      var amountRandom = 4;
      origin.add(createVector(random(-amountRandom, amountRandom), random(-amountRandom, amountRandom)));
      
      var a = p5.Vector.add(origin, p5.Vector.mult(direction, 10));
      var b = p5.Vector.sub(origin, p5.Vector.mult(direction, 10))
      
      if (noise(i/10.0, j/10.0) > map(100, 0, width, 0, 1)) {
        line(a.x, a.y, b.x, b.y);
      }
    }
  }
}