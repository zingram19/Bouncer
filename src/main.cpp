/**
 * Bouncer
 *
 * 2D platformer by Zachary Ingram
 */
#include "main.h"
#include <unistd.h>

int main() {
    // get ur way to da levels folder
    chdir("Users/Shared/");
    // init game
    game g;
    if (g.isInit()) {
        // Game loop
        loop(&g);
    }
    return 0;
}