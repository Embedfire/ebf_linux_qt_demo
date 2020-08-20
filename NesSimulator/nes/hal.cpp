/*
This file present all abstraction needed to port LiteNES.
  (The current working implementation uses allegro library.)

To port this project, replace the following functions by your own:
1) nes_hal_init()
    Do essential initialization work, including starting a FPS HZ timer.

2) nes_set_bg_color(c)
    Set the back ground color to be the NES internal color code c.

3) nes_flush_buf(*buf)
    Flush the entire pixel buf's data to frame buffer.

4) nes_flip_display()
    Fill the screen with previously set background color, and
    display all contents in the frame buffer.

5) wait_for_frame()
    Implement it to make the following code is executed FPS times a second:
        while (1) {
            wait_for_frame();
            do_something();
        }

6) int nes_key_state(int b) 
    Query button b's state (1 to be pressed, otherwise 0).
    The correspondence of b and the buttons:
      0 - Power
      1 - A
      2 - B
      3 - SELECT
      4 - START
      5 - UP
      6 - DOWN
      7 - LEFT
      8 - RIGHT
*/
#include "gamewidget.h"
#include "hal.h"

extern NesGamePannel* s_gameWidgetPannel;

void nes_set_bg_color(int c)
{
    s_gameWidgetPannel->clearBackground(c);
}

/* Flush the pixel buffer */
void nes_flush_buf(PixelBuf *buf, int /*mod*/)
{
    for (int i = 0; i < buf->size; i++)
    {
        int x = buf->buf[i].x;
        int y = buf->buf[i].y;
        int c = buf->buf[i].c;

        s_gameWidgetPannel->addPoint(x,y,c);
    }
}

void nes_flip_display()
{
    s_gameWidgetPannel->display();
}

/* Query a button's state.
   Returns 1 if button #b is pressed. */
int nes_key_state(int b)
{
    //keys = SDL_GetKeyboardState(0);
     switch (b)
     {
         case 0: // On / Off
             return 1;
         case 1: // A
             return s_gameWidgetPannel->testFlag(C);
         case 2: // B
             return s_gameWidgetPannel->testFlag(D);
         case 3: // SELECT
             return s_gameWidgetPannel->testFlag(A);
         case 4: // START
             return s_gameWidgetPannel->testFlag(B);
         case 5: // UP
             return s_gameWidgetPannel->testFlag(UP);
         case 6: // DOWN
             return s_gameWidgetPannel->testFlag(DOWN);
         case 7: // LEFT
             return s_gameWidgetPannel->testFlag(LEFT);
         case 8: // RIGHT
             return s_gameWidgetPannel->testFlag(RIGHT);
         default:
             return 1;
     }
}

void fce_run()
{
    run_once();
}
