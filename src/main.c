#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

void render(uint32_t image_width, uint32_t image_height);

int main(void) {
    uint32_t image_width, image_height;
    scanf("%" PRIu32 "%" PRIu32, &image_width, &image_height);

    printf("P3\n%" PRIu32 " %" PRIu32 "\n255\n", image_width, image_height);
    render(image_width, image_height);
    return 0;
}

void render(uint32_t image_width, uint32_t image_height) {
    for (uint32_t y = 0; y < image_height; ++y) {
        for (uint32_t x = 0; x < image_width; ++x) {
            double z_real = 0.0, z_imag = 0.0;
            double c_real = (2.0 * (double)x + 1.0) / (double)image_width - 1.5;
            double c_imag = (2.0 * (double)y + 1.0) / (double)image_height - 1.0;

            uint32_t num_iters = 0, max_iters = 2048;
            while (z_real * z_real + z_imag * z_imag <= 4 && num_iters < max_iters) {
                double z_real_new = z_real * z_real - z_imag * z_imag + c_real;
                double z_imag_new = 2 * z_real * z_imag + c_imag;
                z_real = z_real_new;
                z_imag = z_imag_new;
                ++num_iters;
            }

            if (num_iters == max_iters) {
                printf("0 0 0\n");
            }
            else {
                // [1, max_iters] -> [0.0, 1.0]
                double t = log((double)num_iters) / log((double)max_iters);
                double r = t;
                double g = t;
                double b = 0.5 - 0.5 * t;

                uint8_t ir = (uint8_t)(255.0 * r);
                uint8_t ig = (uint8_t)(255.0 * g);
                uint8_t ib = (uint8_t)(255.0 * b);
                
                printf("%" PRIu8 " %" PRIu8 " %" PRIu8 "\n", ir, ig, ib);
            }
        }
    }
}