#include "jloc2.h"
#include <stdio.h>

void loc2d_build_tdoa_system(const vec2 mics[4], int ref_idx, const double r_unit[3], linSys3 *sys) {
    printf(str_loc_title, COR2, COR0);
    int row = 0;
    double xr = mics[ref_idx].i;
    double yr = mics[ref_idx].j;
    double qr = xr*xr + yr*yr;

    for (int i = 0; i < 4; ++i) {
        if (i == ref_idx) continue;
        double xi = mics[i].i;
        double yi = mics[i].j;
        double qi = xi*xi + yi*yi;
        double ri = r_unit[row];

        sys->A[row][0] = 2.0 * (xi - xr);
        sys->A[row][1] = 2.0 * (yi - yr);
        sys->A[row][2] = 2.0 * ri;
        sys->b[row]    = qi - qr - ri*ri;

        row++;
    }
    sys->solved = false;
    lin3_print("Sistema TDOA 3x3", sys);   // reuse your printer
}

void loc2d_solve_tdoa(linSys3 *sys, sndLoc2 *loc) {
    lin3_gaussian_solve(sys);               // numerical stable (your pivoting)
    if (!sys->solved) {
        printf(str_loc_invalid, COR3, COR0);
        loc->valid = false;
        return;
    }

    // lin3_cramer_solve(sys);  // cramer solve (manual), não usar

    loc->x = sys->x[0] * MIC_SCALE_M;
    loc->y = sys->x[1] * MIC_SCALE_M;
    loc->d_ref = sys->x[2] * MIC_SCALE_M;
    loc->valid = (loc->d_ref >= 0.0);
    if (loc->valid) {
        printf(str_loc_solved, COR2, loc->x, loc->y, loc->d_ref, COR0);
    } else {
        printf(str_loc_invalid, COR3, COR0);
    }
}

double loc2d_r_from_delta_t(double delta_t_sec) {
    return SPEED_OF_SOUND * delta_t_sec / MIC_SCALE_M;
}