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
    int h;
} paddle;


void vert_collide(ball *b);
void horiz_collide(ball *b);
void paddle_collide(ball *b, paddle *pad);
void ball_reset(position *p, velocity *v);


char buf[20];

// void collide(ball *b) {
//     if (b->p.x <= 2*b->r-1 || b->p.x + b->r >= 125) { //make 1 into 2
//         sprintf(buf, "%d, %d", b->v.deltax, b->v.deltay);
//         drawstring(buff, 0, 1, buf);
//         b->v.deltax *= -1;
//         //Trigger ball reset and update score
        
//     }
//     if (b->p.y - b->r <= 1 || b->p.y + b->r >= 62) {
// //        sprintf(buf, "%d, %d", b->p.x, b->p.y);
// //        drawstring(buff, 0, 1, buf);
//         b->v.deltay *= -1;
        
//     }
// }

void vert_collide(ball *b) { //Handles ball hitting side wall
    //if (b->p.x <= 2*b->r-1 || b->p.x + b->r >= 128) { 
      if (b->p.x + b->r <= 1 || b->p.x + b->r >= 128) { 
        sprintf(buf, "%d, %d", b->v.deltax, b->v.deltay);
        drawstring(buff, 0, 1, buf);
        
        ball_reset(&b->p, &b->v);
        
    }
}

void horiz_collide(ball *b) { //Handles ball hitting top or bottom walls
    if (b->p.y - b->r <= 1 || b->p.y + b->r >= 62) {
//        sprintf(buf, "%d, %d", b->p.x, b->p.y);
//        drawstring(buff, 0, 1, buf);
        b->v.deltay *= -1;    
    }
}

void paddle_collide(ball *b, paddle *pad) {
        if ((b->p.y >= pad->p.y) && (b->p.y <= pad->p.y + pad->h)) { //Ball is within y constraints of paddle
            if (abs(b->p.x - pad->p.x) <= b->r){
              b->v.deltax *= -1;
            } 
        }

}

void ball_reset(position *p, velocity *v){ //Moves ball back to middle & picks a random pathway for it
    p->x = LCDWIDTH / 2;
    p->y = LCDHEIGHT / 2;
    v->deltax = rand() % (5 + 1) + 0;
    v->deltay = rand() % (5 + 1) + 0;
    //rand() % (max_number + 1 - minimum_number) + minimum_number
}




int update_pos(position *p, velocity *v) {
    p->x += v->deltax;
    p->y += v->deltay;
}



#endif //ESE519LAB3_PONG_DEMO_BALL_H
