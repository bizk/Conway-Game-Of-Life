// Conway-Game-Of-Life.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <set>
#include "TileMap.cpp"

using namespace std;
class MapCanvas;

class MapCanvas {
private:
    int width, height;
    vector<vector<int>> matrix;
    set<int> cells;
public:
    MapCanvas(unsigned int width, unsigned int height) {
        this->width = width;
        this->height = height;
        this->matrix.resize(this->height);
        for (int i = 0; i < this->height; ++i) {
            this->matrix[i].resize(this->width);
        }
    }

    //Prints canvas
    void display_canvas() {
        cout << '\n';
        for (const auto& y : matrix) {
            for (const auto& x : y) {
                if (x == 1) cout << "#";
                else cout << "_";
                cout << " ";
            }
            cout << '\n';
        }

    }

    int getPositionValue(int x, int y) {
        return this->matrix[y][x];
    }

    void setPositionAlive(int x, int y) {
        if (this->matrix[y][x] == 0) {
            this->matrix[y][x] = 1;
        }
        else this->matrix[y][x] = 0;
    }

    int getWidth() {
        return this->width;
    }

    int getHeight() {
        return this->height;
    }

    int checkNeighbours(int x, int y) {
        int auxY = y - 1, auxX, aliveNeighbours = 0;

        if (auxY < 0) auxY = y;

        for (; auxY <= y + 1; auxY += 1) {
            if (auxY >= this->height) break;

            if (x - 1 < 0) auxX = x;
            else auxX = x - 1;

            for (; auxX <= x + 1; auxX += 1) {
                if (auxX >= this->width || (auxX == x && auxY == y)) continue;
                else if (this->matrix[auxY][auxX] == 1) {
                    aliveNeighbours += 1;
                };
            }
        }
        return aliveNeighbours;
    }

    void nextGeneration() {
        vector<vector <int>> nextMatrix;
        nextMatrix.resize(this->height);

        for (int i = 0; i < this->height; ++i) {
            nextMatrix[i].resize(this->width);
        }

        for (int y = 0; y < this->height; ++y) {
            for (int x = 0; x < this->width; ++x) {
                int cellNeighbours = this->checkNeighbours(x, y);
                //If the cell is dead but has exactly 3 neigbhours it becomes alive
                if (this->matrix[y][x] == 0 && cellNeighbours == 3) nextMatrix[y][x] = 1;
                //If the cell is alive and has 2 or 3 neighbours it stays alive
                else if (this->matrix[y][x] == 1 && (cellNeighbours == 2 || cellNeighbours == 3)) nextMatrix[y][x] = 1;
                //Else it remains dead;
            }
        }
        this->matrix = nextMatrix;
    }

    vector<vector <int>> getMap() {
        return this->matrix;
    }
};

int main(int argc, char** argv) {
    int columnsRow = 10;
    MapCanvas canvas = MapCanvas(columnsRow, columnsRow);
    MapCanvas* canvasPointer = &canvas;

    int generations = 10;
    
    canvas.setPositionAlive(2, 1);
    canvas.setPositionAlive(2, 2);
    canvas.setPositionAlive(2, 3);
    canvas.setPositionAlive(3, 2);

    /*
    for (int i = 0; i < generations; ++i) {
        canvas.nextGeneration();
        canvas.display_canvas();
    }

    cout << "### Finished ###";
    */
    int windowSize = 800;
    float squareSize = (windowSize / columnsRow)*1.0f;
    
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "life game");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear(sf::Color::Black); //Window color

        sf::RectangleShape rectangle(sf::Vector2f(squareSize, squareSize));
        rectangle.setOutlineThickness(2.f);
        rectangle.setOutlineColor(sf::Color(250, 150, 100));

        TileMap map;
        vector<vector<int>> canvasMap = canvas.getMap();
        if (!map.load(sf::Vector2u(32,32), canvasMap, 10,10))

        window.clear();
        window.draw(map);
        window.display();

        canvas.nextGeneration();
        sf::sleep(sf::Time(sf::milliseconds(500.f)));
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
