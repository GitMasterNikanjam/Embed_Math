/**
 * @file test_embed_math.cpp
 * @brief Simple standalone test program for Embed_Math library.
 *
 * @details
 * This program demonstrates basic usage of functions from Embed_Math:
 *   - Angle wrapping (wrap_180, wrap_360).
 *   - Constrain values.
 *   - Safe math helpers (safe_sqrt, safe_asin).
 *   - Random number helpers.
 *
 * Build example:
 * @code{.sh}
 * mkdir -p ./bin && g++ -std=c++11 -Wall -Wextra -O2 test_embed_math.cpp ../Embed_Math.cpp -o ./bin/test_embed_math
 * ./test_embed_math
 * @endcode
 */

#include <iostream>
#include "../Embed_Math.h"

int main() {
    std::cout << "==== Embed_Math basic tests ====\n";

    // --- Angle wrapping ---
    std::cout << "wrap_360(-45) = " << wrap_360(-45.0f) << " deg\n";
    std::cout << "wrap_180(190) = " << wrap_180(190) << " deg\n";

    // --- Constrain ---
    float clamped = constrain_float(120.0f, 0.0f, 100.0f);
    std::cout << "constrain_float(120,0,100) = " << clamped << "\n";

    // --- Safe math ---
    std::cout << "safe_sqrt(9) = " << safe_sqrt(9.0f) << "\n";
    std::cout << "safe_sqrt(-4) = " << safe_sqrt(-4.0f) << "\n";
    std::cout << "safe_asin(0.5) = " << safe_asin(0.5f) << " rad\n";
    std::cout << "safe_asin(2) = " << safe_asin(2.0f) << " rad (clamped)\n";

    // --- Random numbers ---
    std::cout << "rand_float() = " << rand_float() << "\n";
    Vector3f v = rand_vec3f();
    std::cout << "rand_vec3f() = (" << v.x << ", " << v.y << ", " << v.z << ")\n";

    std::cout << "==== Done ====\n";
    return 0;
}
