#ifndef JLOC2D
#define JLOC2D

#include "../lib/jthio.h"
#include "../lib/jlinear.h"

static const char *str_loc_title   = "\n%s=== Localização 2D por TDOA (4 mics) ===%s\n";
static const char *str_loc_solved  = "%sFonte localizada em (%.4f, %.4f) m | d0 = %.4f m%s\n";
static const char *str_loc_invalid = "\n%sAVISO: Localização inválida (matriz singular ou d0 < 0)%s\n";
static const char *str_loc_r_unit  = "%s(r1, r2, r3 em unidades) = (%.6f, %.6f, %.6f)%s\n";

#define MIC_SCALE_M   0.100   // 10 cm por unidade vetorial
#define SPEED_OF_SOUND 343.0  // m/s em 20°C

typedef struct {
    double x, y;      // metros
    double d_ref;     // distância até mic de referência (metros)
    bool valid;
} sndLoc2;

static const vec2 MIC_POS_UNIT[4] = {
    { 1.0,  0.0},   // m0
    { 0.0,  1.0},   // m1
    {-1.0,  0.0},   // m2
    { 0.0, -1.0}    // m3
};

void loc2d_build_tdoa_system(const vec2 mics[4], int ref_idx, const double r_unit[3], linSys3 *sys);
void loc2d_solve_tdoa(linSys3 *sys, sndLoc2 *loc);   // usa Gaussian + escala para metros

void jloc_simulator(void);

// retorna r a partir de Δt
double loc2d_r_from_delta_t(double delta_t_sec);

#endif