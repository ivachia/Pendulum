let length, mass, gravity, theta, velocity, time;
let angle, angularVelocity, angularAcceleration;
let isPaused = false;
let button;

function setup() {
  createCanvas(800, 600);
  
  // Input fields
  length = float(prompt("Enter the length of the pendulum (m):"));
  mass = float(prompt("Enter the mass of the pendulum (kg):"));
  gravity = float(prompt("Enter the gravity (m/s²):"));
  theta = float(prompt("Enter the initial angle (degrees):")) * (PI / 180);
  
  // Initialize variables
  angle = theta;
  angularVelocity = 0;
  angularAcceleration = 0;
  time = 0;
  
  // Create pause button
  button = createButton('Pause/Resume');
  button.position(10, 10);
  button.mousePressed(togglePause);
}

function draw() {
  background(220);
  
  if (!isPaused) {
    // Calculate angular acceleration
    angularAcceleration = (-1 * gravity / length) * sin(angle);
    
    // Update angular velocity and angle
    angularVelocity += angularAcceleration;
    angle += angularVelocity;
    
    // Update time
    time += deltaTime / 1000; // Convert milliseconds to seconds
  }
  
  // Calculate velocity
  velocity = angularVelocity * length; // Linear velocity
  
  // Draw pendulum
  let originX = width / 2;
  let originY = 100;
  let pendulumX = originX + length * sin(angle) * 100; // Scale for visualization
  let pendulumY = originY + length * cos(angle) * 100; // Scale for visualization
  
  stroke(0);
  line(originX, originY, pendulumX, pendulumY);
  fill(127);
  ellipse(pendulumX, pendulumY, mass * 10, mass * 10); // Scale mass for visualization
  
  // Display velocity and time
  fill(0);
  textSize(16);
  text(`Velocity: ${velocity.toFixed(2)} m/s`, 10, 50);
  text(`Time: ${time.toFixed(2)} s`, 10, 70);
}

function togglePause() {
  isPaused = !isPaused;
}
