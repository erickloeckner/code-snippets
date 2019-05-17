void lineBresenham(int x0, int y0, int x1, int y1) {
    int dx, dy;
    int stepx, stepy;
    dx = x1 - x0;
    dy = y1 - y0;
    if (dy < 0) { dy = -dy; stepy = -1; } else { stepy = 1; }
    if (dx < 0) { dx = -dx; stepx = -1; } else { stepx = 1; }
    dy <<= 1; /* dy is now 2*dy */
    dx <<= 1; /* dx is now 2*dx */
    // if ((0 <= x0) && (x0 < RDim) && (0 <= y0) && (y0 < RDim))
        // theRaster[x0][y0] = 1;

    if (dx > dy) {
        int fraction = dy - (dx >> 1);
        while (x0 != x1) {
            x0 += stepx;
            // std::cout << "-x ";
            if (fraction >= 0) {
                y0 += stepy;
                // std::cout << "-y ";
                fraction -= dx;
            }
            fraction += dy;
            //if ((0 <= x0) && (x0 < RDim) && (0 <= y0) && (y0 < RDim))
            //  theRaster[x0][y0] = 1;
            // std::cout << x0 << " " << y0 << "\n";
            printf("%3d | %3d\n", x0, y0);
        }
    } else {
        int fraction = dx - (dy >> 1);
        while (y0 != y1) {
            if (fraction >= 0) {
                x0 += stepx;
                fraction -= dy;
            }
                
            y0 += stepy;
            fraction += dx;
            //if ((0 <= x0) && (x0 < RDim) && (0 <= y0) && (y0 < RDim))
            //  theRaster[x0][y0] = 1;
            // std::cout << x0 <<  " " << y0 << "\n";
            printf("%3d | %3d\n", x0, y0);
        }
    }
}
