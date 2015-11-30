#include "application.h"


int main (int argc, char **argv) {
    application_t app = {0}; 

    application_init (&app, &argc, &argv);
    
    load_resource (&app);

    application_run (&app);  

    return 0;
}
