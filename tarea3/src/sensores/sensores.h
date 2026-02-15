#ifndef SENSORES_H
#define SENSORES_H

// enum para identificar los sensores
enum sensores_id {
    pos_id = 0xA0,
    gest_id = 0xB0
};

typedef void (*print_sensor)();

#endif