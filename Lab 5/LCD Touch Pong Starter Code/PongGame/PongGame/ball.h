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

typedef struct pad {
    position p;
    velocity v;

    int l;
    int w;
} paddle;




char buf[20];

// void collide(ball *b) {
//     if (b->p.x - b->r <= 2 || b->p.x + b->r >= 125) { //make 1 into 2
//         sprintf(buf, "%d, %d", b->v.deltax, b->v.deltay);
//         drawstring(buff, 0, 1, buf);
//         b->v.deltax *= -1;
        
//     }
//     if (b->p.y - b->r <= 1 || b->p.y + b->r >= 62) {
// //        sprintf(buf, "%d, %d", b->p.x, b->p.y);
// //        drawstring(buff, 0, 1, buf);
//         b->v.deltay *= -1;
        
//     }
// }

void collide(ball *b) {
    if (b->p.x <= 2*b->r-1 || b->p.x + b->r >= 125) { //make 1 into 2
        sprintf(buf, "%d, %d", b->v.deltax, b->v.deltay);
        drawstring(buff, 0, 1, buf);
        b->v.deltax *= -1;
        //Trigger ball reset and update score
        
    }
    if (b->p.y - b->r <= 1 || b->p.y + b->r >= 62) {
//        sprintf(buf, "%d, %d", b->p.x, b->p.y);
//        drawstring(buff, 0, 1, buf);
        b->v.deltay *= -1;
        
    }
}

void paddle_collide(ball *b, paddle *pad) {
    if (b->v.deltax > 0){ //Ball is moving right
        if (b->p.y => pad->p.y) && (b->p.y <= pad->p.y + pad.l) //Ball is within y constraints of paddle

    }


    else{ //Ball is moving left
        if (b->p.y => pad->p.y) && (b->p.y <= pad->p.y + pad.l) //Ball is within y constraints of paddle

    }




}




int update_pos(position *p, velocity *v) {
    p->x += v->deltax;
    p->y += v->deltay;
}



#endif //ESE519LAB3_PONG_DEMO_BALL_H
