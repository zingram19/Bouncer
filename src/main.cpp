/**
 * Bouncer
 *
 * 2D platformer by Zachary Ingram
 */
#include "main.h"

int main() {
    // init game
    game g;
    if (g.isInit()) {
        // Game loop
        loop(&g);
    }
    return 0;
}