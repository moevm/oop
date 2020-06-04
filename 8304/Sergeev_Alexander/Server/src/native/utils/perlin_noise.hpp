#ifndef LOGIC_PERLIN_NOISE_HPP
#define LOGIC_PERLIN_NOISE_HPP

#include <cmath>

namespace utils {
    class perlin_noise {
    private:
        static double cos_lerp (double a, double b, double x) {
            double t = (1 - cosf((float)(x * 3.1415927))) * 0.5f;
            return a * (1 - t) + b * t;
        }

        static float cubic_lerp (float v0, float v1, float v2, float v3, float x) {
            float p = (v3 - v2) - (v0 - v1);
            float q = (v0 - v1) - p;
            float r = v2 - v0;
            float s = v1;

            //возможно 3,2 - степени
            return p * x * 3 + q * x * 2 + r * x + s;
        }


        static float lerp (float a, float b, float t) {
            return a + t * (b - a);
        }

        static float hermite_curve (float t) {
            return t * t * (3 - 2 * t);
        }

        static float quntic_curve (float t) {
            return t * t * t * (t * (t * 6 - 15) + 10);
        }

        static double get_noise (int x, int y) {
            int n = x + y * 57;
            n = (n << 13) ^ n;
            return 1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0;
        }

        static double smooth_noise (double x, double y) {
            int ix = (int)x, iy = (int)y;

            double corners = (get_noise(ix - 1, iy - 1) + get_noise(ix + 1, iy - 1) + get_noise(ix - 1, iy + 1) + get_noise(ix + 1, iy + 1)) / 16;
            double sides = (get_noise(ix - 1, iy) + get_noise(ix + 1, iy) + get_noise(ix, iy - 1) + get_noise(ix, iy + 1)) / 8;
            double center = get_noise(ix, iy) / 4;
            return corners + sides + center;
        }

        static double compile_noise (double x, double y) {
            int integer_x = (int)x;
            double fractional_x = x - integer_x;

            int integer_y = (int)y;
            double fractional_y = y - integer_y;

            double v1 = smooth_noise(integer_x, integer_y);
            double v2 = smooth_noise(integer_x + 1, integer_y);
            double v3 = smooth_noise(integer_x, integer_y + 1);
            double v4 = smooth_noise(integer_x + 1, integer_y + 1);

            double i1 = cos_lerp(v1, v2, fractional_x);
            double i2 = cos_lerp(v3, v4, fractional_x);

            return cos_lerp(i1, i2, fractional_y);
        }

    public:
        static double get_perlin_noise (double x, double y, double xOffset) {
            double total = 0;

            // это число может иметь и другие значения хоть cosf(sqrtf(2))*3.14f
            // главное чтобы было красиво и результат вас устраивал
            double persistence = 0.5f;

            // экспериментируйте с этими значениями, попробуйте ставить
            // например sqrtf(3.14f)*0.25f или что-то потяжелее для понимания J)
            double frequency = 0.1f;

            //амплитуда, в прямой зависимости от значения настойчивости
            double amplitude = 0.5;

            // рандомизация
            x += (xOffset);
            y += (xOffset);

            // octaves - переменная, которая обозначает число октав,
            // чем больше октав, тем лучше получается шум
            int octaves = 3;
            for (int i = 0; i < octaves; i++) {
                total += compile_noise(x * frequency, y * frequency) * amplitude;
                amplitude *= persistence;
                frequency *= 2;
            }

            total = std::abs(total);
            return total;
        }

        static double get_perlin_noise (float x, float y, double octaves, double frequency, double amplitude, double persistance, double lacunarity) {
            double total = 0;
            for (int i = 0; i < octaves; i++) {
                total += compile_noise(x * frequency, y * frequency) * amplitude;
                amplitude *= persistance;
                frequency *= lacunarity;
            }
            total = std::abs(total);
            if (total > 1) {
                return 1;
            }
            if (total < 0) {
                return 0;
            }
            return total;
        }
    };
}

#endif //LOGIC_PERLIN_NOISE_HPP
