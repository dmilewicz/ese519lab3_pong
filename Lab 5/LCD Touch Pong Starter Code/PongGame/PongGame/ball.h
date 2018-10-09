//
// Created by David Milewicz on 9/27/18.
//
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef ESE519LAB3_PONG_DEMO_BALL_H
#define ESE519LAB3_PONG_DEMO_BALL_H

#define MAX_V     10
#define V_RANGE   MAX_V * 2

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define BOUND(min, max, x) MAX(MIN(x, max), min)

extern char score1;
extern char score2;


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
void point_alert();
void win_alert();
//void update_pos(position *p, velocity *v);
//void update_pos_paddle(paddle *pad);
//int pad_travel_to(padddle *pad, int y)


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

void timer1_init(){
    //TCNT1 = 6397;
    TCCR1A = 0x00;
    TIMSK1 |= (1 << TOIE1); //enable interrupts

}

void vert_collide(ball *b) { //Handles ball hitting side wall
    // if (b->p.x <= 2*b->r-1 || b->p.x + b->r >= 128) { 
    if (b->p.x - b->r < 0 || b->p.x + b->r >= LCDWIDTH) { 

        if (b->p.x < 64){
            score2 +=1;
        }
        else{
            score1 +=1;
        }

        if (score1 == ':' || score2 == ':'){
            win_alert();
        }

        point_alert();
        ball_reset(&b->p, &b->v);
        
    }
}

void horiz_collide(ball *b) { //Handles ball hitting top or bottom walls
    if (b->p.y - b->r < 0 || b->p.y + b->r >= LCDHEIGHT) {
        b->v.deltay *= -1;  
        point_alert();
    }
}

void paddle_collide(ball *b, paddle *pad) {
        if ((b->p.y >= pad->p.y) && (b->p.y <= pad->p.y + pad->h)) { //Ball is within y constraints of paddle
            if ((b->v.deltax > 0 && (abs(b->p.x - pad->p.x) <= b->r)) ||  // Right
                (b->v.deltax < 0 &&  abs(b->p.x - (pad->p.x + pad->l - 1)) <= b->r)) // Left
            {
                b->v.deltax *= -1;

                int y_center = pad->p.y + (pad->h / 2);
                b->v.deltay += BOUND(-3, 3, (b->p.y - y_center));
                point_alert();
            }
        }
}

void ball_reset(position *p, velocity *v){ //Moves ball back to middle & picks a random pathway for it
    p->x = LCDWIDTH / 2;
    p->y = LCDHEIGHT / 2;

    do {
        v->deltax = (rand() % 10) - 5;
    } while (abs(v->deltax) < 2);

    do {
        v->deltay = (rand() % 10) - 5;
    } while (abs(v->deltay) < 2);    
}

void point_alert(){
    //buzzer & backlight
    //PORTB |= 0x05; //Turn off blue and green backlights, leave red on
    //PORTB |= 0x00;
    TCCR2A |= (1 << COM2A0); //Activate buzzer

    TCCR1B = (1<<CS11);  // Timer mode with 1024 prescaler
    TCNT1L = 0;
    TCNT1H = 0;

}

void win_alert(){
    score1 = '0';
    score2 = '0';
    //buzzer & backlight
    PORTB |= 0x05; //Turn off blue and green backlights, leave red on
    //PORTB |= 0x00;
    TCCR2A |= (1 << COM2A0); //Activate buzzer

    _delay_ms(1000); //1 second delay
    PORTB &= ~0x05; //Turn blue and green back on
    TCCR2A &= !(1 << COM2A0); //Disconnect buzzer
}

int update_pos(position *p, velocity *v) {
    p->x += v->deltax;
    p->y += v->deltay;
}

int update_pos_paddle(paddle *pad) {
    pad->p.y = BOUND(0, LCDHEIGHT - pad->h, pad->p.y + pad->v.deltay);
}

/*
 *  Run before update_pos_paddle
 */
int pad_travel_to(paddle *pad, int y) {
    int y_center = y - (pad->h / 2);

    pad->v.deltay = BOUND(-MAX_V, MAX_V, y_center - pad->p.y);
}


#endif //ESE519LAB3_PONG_DEMO_BALL_H
