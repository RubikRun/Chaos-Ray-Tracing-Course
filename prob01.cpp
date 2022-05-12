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

/// Output image resolution
static const Vec2i imageResolution = { 1920, 1080 };
/// Number of rectangles horizontally and vertically
static const Vec2i recCount = { 8, 6 };

static const int maxColorComponent = 255;

Color getRandomColor() {
    return {
        rand() % maxColorComponent,
        rand() % maxColorComponent,
        rand() % maxColorComponent
    };
}

float getNoise() {
    return float(rand()) / float(RAND_MAX);
}

void writeImage(const char *filepath, const Color *recColors) {
    std::ofstream ppmFileStream(filepath, std::ios::out | std::ios::binary);

    ppmFileStream << "P3\n";
    ppmFileStream << imageResolution.x << " " << imageResolution.y << "\n";
    ppmFileStream << maxColorComponent << "\n";

    const Vec2f recSize = {
        float(imageResolution.x) / float(recCount.x),
        float(imageResolution.y) / float(recCount.y)
    };

    for (int yPixIdx = 0; yPixIdx < imageResolution.y; ++yPixIdx) {
        for (int xPixIdx = 0; xPixIdx < imageResolution.x; ++xPixIdx) {
            const Vec2i recIdx = {
                int(float(xPixIdx) / recSize.x),
                int(float(yPixIdx) / recSize.y)
            };

            const float noise = getNoise();
            const Color color = recColors[recIdx.y * recCount.x + recIdx.x];
            const Color noisedColor = {
                int(float(color.r) * noise),
                int(float(color.g) * noise),
                int(float(color.b) * noise)
            };

            ppmFileStream << noisedColor.r << " " << noisedColor.g << " " << noisedColor.b << "\t";
        }
        ppmFileStream << "\n";
    }

    ppmFileStream.close();
}

int main() {
    srand(time(nullptr));

    Color recColors[recCount.x * recCount.y];
    for (int recInd = 0; recInd < recCount.x * recCount.y; recInd++) {
        recColors[recInd] = getRandomColor();
    }

    writeImage("output_image_01.ppm", recColors);

    return 0;
}
