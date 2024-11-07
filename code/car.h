#ifndef CAR_H
#define CAR_H


typedef enum {
    STOP,
    STREIGHT,
    LEFT,
    RIGHT,
    LEFT_CIRCLE,
    RIGHT_CIRCLE
} car_direction;

void Car_stop(void);
void Car_streight(void);
void Car_left(void);
void Car_right(void);
void Car_left_circle(void);
void Car_right_circle(void);
void kernel(void);
void Car_Init(void);
void Car_go(void);

#endif
