#include <iostream>
#include <fstream>
#include <array>

const size_t ROWS = 6;
const size_t COLS = 6;
const double ALPHA = 0.01; // Thermal diffusivity
const double DX = 1.0;     // Spatial step size
const double DT = 0.01;    // Time step size

void apply_heat_equation(std::array<std::array<double, COLS>, ROWS>& matrix) {
    std::array<std::array<double, COLS>, ROWS> temp_matrix = matrix;

    // Apply the finite difference method to update the temperature distribution
    for (size_t i = 1; i < ROWS - 1; ++i) {
        for (size_t j = 1; j < COLS - 1; ++j) {
            double dT_dx2 = (matrix[i][j-1] - 2 * matrix[i][j] + matrix[i][j+1]) / (DX * DX);
            double dT_dy2 = (matrix[i-1][j] - 2 * matrix[i][j] + matrix[i+1][j]) / (DX * DX);
            temp_matrix[i][j] = matrix[i][j] + ALPHA * DT * (dT_dx2 + dT_dy2);
        }
    }

    // Update the original matrix with the values from the temporary matrix
    matrix = temp_matrix;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    std::array<std::array<double, COLS>, ROWS> matrix;

    // Read the initial temperature distribution from the text file
    for (size_t i = 0; i < ROWS; ++i) {
        for (size_t j = 0; j < COLS; ++j) {
            if (!(file >> matrix[i][j])) {
                std::cerr << "Error reading from file." << std::endl;
                return 1;
            }
        }
    }

    // Solve the heat equation for a certain number of time steps
    const size_t NUM_TIME_STEPS = 100000;
    for (size_t t = 0; t < NUM_TIME_STEPS; ++t) {
        apply_heat_equation(matrix);
    }

    // Print the updated temperature distribution
    std::cout << "Updated Temperature Distribution:" << std::endl;
    for (const auto& row : matrix) {
        for (double temp : row) {
            std::cout << temp << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
