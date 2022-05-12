#include <fstream>
#include <cstdlib>
#include <ctime>

struct Vec2i {
    int x;
    int y;
};

struct Vec2f {
    float x;
    float y;
};

struct Color {
    int r;
    int g;
    int b;
};

struct Circle {
    Vec2f center;
    float radius;
    Color color;

    bool contains(const Vec2f &point) const {
        return (point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y) < radius * radius;
    }
};

/// Output image resolution
static const Vec2i imageResolution = { 1920, 1080 };
static const int maxColorComponent = 255;

static const int circlesCount = 150;
static const float radiusBase = 100.f;
static const float radiusVary = 60.f;

int getRandomInt(int a, int b) {
    return rand() % (b - a + 1) + a;
}

float getRandomFloat(float a, float b) {
    const float ratio = float(rand()) / float(RAND_MAX);
    return a + (b - a) * ratio;
}

Color getRandomColor() {
    return {
        getRandomInt(0, maxColorComponent),
        getRandomInt(0, maxColorComponent),
        getRandomInt(0, maxColorComponent)
    };
}

void generateCircles(Circle *circles) {
    for (int circIdx = 0; circIdx < circlesCount; circIdx++) {
        circles[circIdx].center.x = getRandomFloat(0.f, float(imageResolution.x));
        circles[circIdx].center.y = getRandomFloat(0.f, float(imageResolution.y));
        circles[circIdx].radius = radiusBase + getRandomFloat(-radiusVary, +radiusVary);
        circles[circIdx].color = getRandomColor();
    }
}

void writeImage(const char *filepath, const Circle *circles) {
    std::ofstream ppmFileStream(filepath, std::ios::out | std::ios::binary);

    ppmFileStream << "P3\n";
    ppmFileStream << imageResolution.x << " " << imageResolution.y << "\n";
    ppmFileStream << maxColorComponent << "\n";

    for (int rowIdx = 0; rowIdx < imageResolution.y; ++rowIdx) {
        for (int colIdx = 0; colIdx < imageResolution.x; ++colIdx) {
            const Vec2f point = { float(colIdx), float(rowIdx) };

            // Sum the color across all circles containing the current point
            Color colorSum = { 0, 0, 0 };
            int colorCount = 0;
            for (int circIdx = 0; circIdx < circlesCount; circIdx++) {
                if (circles[circIdx].contains(point)) {
                    colorSum.r += circles[circIdx].color.r;
                    colorSum.g += circles[circIdx].color.g;
                    colorSum.b += circles[circIdx].color.b;
                    colorCount++;
                }
            }
            // If no circles found, just write black pixel
            if (colorCount == 0) {
                ppmFileStream << "0 0 0\t";
                continue;
            }
            // Calculate the average color across the containing circles
            const Color colorAvg = {
                colorSum.r / colorCount,
                colorSum.g / colorCount,
                colorSum.b / colorCount
            };
            // Write average color pixel
            ppmFileStream << colorAvg.r << " " << colorAvg.g << " " << colorAvg.b << "\t";
        }
        ppmFileStream << "\n";
    }

    ppmFileStream.close();
}

int main() {
    srand(time(nullptr));

    Circle circles[circlesCount];
    generateCircles(circles);

    writeImage("output_image_02.ppm", circles);

    return 0;
}
