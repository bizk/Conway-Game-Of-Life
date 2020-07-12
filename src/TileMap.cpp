#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class TileMap : public sf::Drawable, public sf::Transformable {
    public:
        bool load(sf::Vector2u tileSize, std::vector<std::vector<int>> tiles, unsigned int width, unsigned int height) {
            // resize the vertex array to fit the level size
            m_vertices.setPrimitiveType(sf::Quads);
            m_vertices.resize(width * height * 4);

            // populate the vertex array, with one quad per tile
            for (unsigned int x = 0; x < width; ++x)
                for (unsigned int y = 0; y < height; ++y)
                {
                    // get a pointer to the current tile's quad
                    sf::Vertex* quad = &m_vertices[(x + y * width) * 4];

                    // define its 4 corners
                    quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
                    quad[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
                    quad[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
                    quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);

                    if (tiles[y][x] == 1) {
                        quad[0].color = sf::Color::Black;
                        quad[1].color = sf::Color::Black;
                        quad[2].color = sf::Color::Black;
                        quad[3].color = sf::Color::Black;
                    }
                }

            return true;
        }

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            // apply the transform
            states.transform *= getTransform();

            // draw the vertex array
            target.draw(m_vertices, states);
        }

    sf::VertexArray m_vertices;
};