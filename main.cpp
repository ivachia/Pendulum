#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

const double DEFAULT_GRAVITY = 9.81;

struct Pendulum {
    double length;
    double mass;
    double radius;
    double gravity;
    double maxVelocity;
    
    Pendulum(double l, double m, double r, double g) 
        : length(l), mass(m), radius(r), gravity(g), maxVelocity(0) {}
    
    void calculateMaxVelocity() {
        // Assuming simple pendulum with small-angle approximation
        maxVelocity = sqrt(2 * gravity * length);
    }
};

void getUserInput(double &length, double &mass, double &radius, double &gravity) {
    std::cout << "Enter length (m): ";
    std::cin >> length;
    std::cout << "Enter mass (kg): ";
    std::cin >> mass;
    std::cout << "Enter radius (optional, default 0.0): ";
    std::cin >> radius;
    if (std::cin.fail()) {
        radius = 0.0;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Enter gravity (optional, default 9.81 m/s^2): ";
    std::cin >> gravity;
    if (std::cin.fail()) {
        gravity = DEFAULT_GRAVITY;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    std::vector<Pendulum> pendulums;
    char choice;
    
    do {
        double length, mass, radius = 0.0, gravity = DEFAULT_GRAVITY;
        getUserInput(length, mass, radius, gravity);
        
        Pendulum pendulum(length, mass, radius, gravity);
        pendulum.calculateMaxVelocity();
        pendulums.push_back(pendulum);
        
        std::cout << "Add another pendulum? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    
    // Display results
    std::cout << "\nPendulum Data:\n";
    for (const auto &pendulum : pendulums) {
        std::cout << "Length: " << pendulum.length 
                  << ", Mass: " << pendulum.mass 
                  << ", Radius: " << pendulum.radius 
                  << ", Gravity: " << pendulum.gravity 
                  << ", Max Velocity: " << pendulum.maxVelocity << " m/s\n";
    }
    
    // Plotting using gnuplot
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "set title 'Pendulum Max Velocity vs Length'\n");
        fprintf(gnuplotPipe, "set xlabel 'Length (m)'\n");
        fprintf(gnuplotPipe, "set ylabel 'Max Velocity (m/s)'\n");
        fprintf(gnuplotPipe, "plot '-' with linespoints\n");
        
        for (const auto &pendulum : pendulums) {
            fprintf(gnuplotPipe, "%f %f\n", pendulum.length, pendulum.maxVelocity);
        }
        
        fprintf(gnuplotPipe, "e\n");
        fflush(gnuplotPipe);
        pclose(gnuplotPipe);
    } else {
        std::cerr << "Error opening gnuplot pipe.\n";
    }
    
    return 0;
}
