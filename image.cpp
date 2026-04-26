#include "image.h"

#include <fstream>
#include <ostream>
#include <stdexcept>

Image::Image()
    : width_(0), height_(0)
{
}

Image::Image(std::size_t width, std::size_t height, int value)
    : width_(width), height_(height), pixels_(width * height, value)
{
}

Image Image::load(const std::string& filename)
{
    std::ifstream input(filename);

    if (!input)
        throw std::runtime_error("Cannot open input file: " + filename);

    std::size_t width = 0;
    std::size_t height = 0;

    if (!(input >> width >> height))
        throw std::runtime_error("Cannot read image dimensions from: " + filename);

    if (width == 0 || height == 0)
        throw std::runtime_error("Image dimensions must be positive");

    Image image(width, height);

    for (std::size_t i = 0; i < image.size(); ++i) {
        if (!(input >> image.pixels_[i]))
            throw std::runtime_error("Not enough pixel values in: " + filename);

        if (image.pixels_[i] < 0 || image.pixels_[i] > 255)
            throw std::runtime_error("Pixel value outside range 0-255");
    }

    int extra_value = 0;

    if (input >> extra_value)
        throw std::runtime_error("Too many pixel values in: " + filename);

    return image;
}

void Image::save(const std::string& filename) const
{
    std::ofstream output(filename);

    if (!output)
        throw std::runtime_error("Cannot open output file: " + filename);

    write(output);
}

void Image::write(std::ostream& output) const
{
    output << width_ << " " << height_ << "\n";

    for (std::size_t y = 0; y < height_; ++y) {
        for (std::size_t x = 0; x < width_; ++x) {
            if (x > 0)
                output << " ";

            output << at(x, y);
        }

        output << "\n";
    }
}

std::size_t Image::width() const
{
    return width_;
}

std::size_t Image::height() const
{
    return height_;
}

std::size_t Image::size() const
{
    return pixels_.size();
}

int& Image::at(std::size_t x, std::size_t y)
{
    return pixels_.at(index(x, y));
}

int Image::at(std::size_t x, std::size_t y) const
{
    return pixels_.at(index(x, y));
}

const std::vector<int>& Image::pixels() const
{
    return pixels_;
}

std::size_t Image::index(std::size_t x, std::size_t y) const
{
    if (x >= width_ || y >= height_)
        throw std::out_of_range("Image coordinate outside bounds");

    return y * width_ + x;
}
