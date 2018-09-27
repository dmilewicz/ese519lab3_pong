//
// Created by David Milewicz on 9/27/18.
//

#ifndef ESE519LAB3_PONG_DEMO_BALL_H
#define ESE519LAB3_PONG_DEMO_BALL_H


typedef struct p {
    int x,y;
} position;

typedef struct v {
    int deltax, deltay;
} velocity;

typedef struct b {
    position p;
    velocity v;

    int r;
} ball;


char buf[20];

void collide(ball *b) {
    if (b->p.x - b->r <= 1 || b->p.x + b->r >= 125) {
        sprintf(buf, "%d, %d", b->v.deltax, b->v.deltay);
        drawstring(buff, 0, 1, buf);
        b->v.deltax *= -1;
    }
    if (b->p.y - b->r <= 1 || b->p.y + b->r >= 62) {
//        sprintf(buf, "%d, %d", b->p.x, b->p.y);
//        drawstring(buff, 0, 1, buf);
        b->v.deltay *= -1;
    }
}

int update_pos(position *p, velocity *v) {
    p->x += v->deltax;
    p->y += v->deltay;
}



#endif //ESE519LAB3_PONG_DEMO_BALL_H
