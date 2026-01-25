
  // Updates the bird’s vertical position and applies gravity
void update_bird(int &y, int &speed) {
    y += speed;          // Move bird based on current speed
    speed += 1;          // Increase speed due to gravity
    if (y > HEIGHT) {    // Stop bird at bottom boundary
        y = HEIGHT;
        speed = 0;
    }
    if (y < 0) {         // Stop bird at top boundary
        y = 0;
        speed = 0;
    }
}

// Checks whether the bird collides with a pipe
bool check_collision(int bx, int by, int px, int py) {
    // Check horizontal overlap between bird and pipe
    if (bx + BIRD_WIDTH / 2 > px && bx - BIRD_WIDTH / 2 < px + PIPE_WIDTH) {
        // Check if bird hits upper or lower part of the pipe
        if (by - BIRD_HEIGHT / 2 < py ||
            by + BIRD_HEIGHT / 2 > py + PIPE_GAP) {
            return true; // Collision detected
        }
    }
    return false; // No collision
}


