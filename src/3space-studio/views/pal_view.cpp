#include "pal_view.hpp"
#include "archives/bitmap.hpp"

pal_view::pal_view(std::basic_istream<std::byte>& image_stream)
{
  auto colours = darkstar::pal::get_pal_data(image_stream);
  rectangles.reserve(colours.size());

  float x = 0;
  float y = 0;
  auto size = colours.size() / 8;

  for (auto& colour : colours)
  {
    rectangles.emplace_back(sf::Vector2f(size, size));
    auto& rect = rectangles.back();

    rect.setPosition(x, y);
    rect.setFillColor(sf::Color(int(colour.red), int(colour.green), int(colour.blue)));

    y += size;

    if (y == colours.size())
    {
      y = 0;
      x += size;
    }
  }
}

void pal_view::render_ui(sf::RenderWindow* window, wxControl* parent, ImGuiContext* guiContext)
{
  window->clear();

  for (auto& rectangle : rectangles)
  {
    window->draw(rectangle);
  }
}

void pal_view::setup_gl(sf::RenderWindow* window, wxControl* parent, ImGuiContext* guiContext)
{
  auto [width, height] = parent->GetClientSize();

  auto image_width = rectangles.size() / 8 * rectangles.size();
  auto image_height = rectangles.size() / 8 * (rectangles.size() / 8);

  auto width_ratio = float(image_width) / width;
  auto height_ratio = float(image_height) / height;

  std::cout << width_ratio << '\n';
  std::cout << height_ratio << '\n';

  sf::FloatRect visibleArea(0, 0, image_width, image_height);
  sf::View view(visibleArea);
  view.setViewport(sf::FloatRect(0.5 - width_ratio / 16, 0.5 - height_ratio / 8, width_ratio, height_ratio));
  window->setView(view);
}