#include <lo/lo.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define SAMPLE_RATE 500
#define SINE_FREQ 20.0
#define PI 3.14159265359

int main() {
    // Create OSC address (adjust host/port as needed)
    lo_address target = lo_address_new("localhost", "2228");
    
    if (target == NULL) {
        fprintf(stderr, "Error creating OSC address\n");
        return 1;
    }

    // Time variables
    double t = 0.0;
    const double dt = 1.0 / SAMPLE_RATE;

    printf("Starting OSC sender to localhost:2228\n");

    // Array of module IDs
    const long long module_ids[] = {
        1801729817500827LL,
        5245853359063299LL,
        2841899600611647LL,
        8854601895984255LL,
        4666552859119416LL,
        1472980066837876LL,
        333171591327196LL,
        5053687638998397LL,
        2870975173539524LL,
        5587902606238071LL,
        7187258617830562LL,
        5711119479847828LL,
        1945916579402223LL,
        4504024525600241LL,
        2161656104829363LL,
        5989089226418880LL,
        1894144147129545LL,
        13069561164302LL,
        7095315600387550LL,
        6767933738660314LL,
        2220582776555991LL,
        5980114935426132LL,
        1356357375813655LL,
        7218529386473080LL,
        2603258057162663LL,
        8530260904765889LL,
        1670645477511408LL,
        1081824471369046LL,
        4829921563915318LL,
        3045246876244971LL,
        512464826245387LL,
        2534868103224232LL,
        181228568503210LL,
        6711790293058318LL,
        640861961294629LL,
        1209706375026399LL,
        7376132278866080LL,
        4183796908856889LL,
        4767405664655808LL,
        3631474620643245LL,
        7167170257281516LL,
        2907157533121125LL,
        2325807461500063LL,
        5157247046457153LL,
        3269837859083636LL,
        831501910096530LL,
        559707736468119LL,
        6993632709364094LL,
        4797667611220816LL,
        6814900301115300LL,
        600206343829436LL,
        8400649305620711LL,
        4278385461881880LL,
        3910459693595886LL,
        179627325210214LL,
        7234358678050830LL,
        1601461407556938LL,
        8686155327960433LL,
        5282060974395176LL,
        1784030942839231LL,
        7332929414048946LL,
        5820163301572836LL,
    };
    int num_modules = sizeof(module_ids) / sizeof(module_ids[0]);

    int result;
    while (1) {
        // Calculate sine value
        const float value =( (float)sin(2.0 * PI * SINE_FREQ * t))/2.0f + 1/2.0f;
        
        for (uint16_t i = 0; i < num_modules; i++) {
            for (uint16_t param = 0; param < 3; param++) {
                int result = lo_send(target, "/param", "hif", module_ids[i], param, value);
                if (result == -1)
                    fprintf(stderr, "OSC error for module %lld: %s\n", module_ids[i], lo_address_errstr(target));
            }
        }
        // Sleep for dt seconds (convert to microseconds)
        usleep((useconds_t)(dt * 1000000));

        // Increment time
        t += dt;
    }

    lo_address_free(target);
    return 0;
}

