#include<iostream>
#include<string>
#include<ncurses.h> //console managment
#include<unistd.h> // sleep()
#include<vector>
using namespace std;

//Global
enum Direction {up, down, left, right, none};

class snake
{
    private:
        int size = 1;
        Direction direction = up;
    public:
        vector<pair<int, int>> body = {{0,0}};
        void move_up()
        {
            direction = Direction::up;
        }
        void move_down()
        {
            direction = Direction::down;
        }
        void move_left()
        {
            direction = Direction::left;
        }
        void move_right()
        {
            direction = Direction::right;
        }
        void move_none()
        {
            direction = Direction::none;
        }
        Direction whatis_direction()
        {
            return direction;
        }
        void set_body_value(int x, int y, int index)
        {
            body[index] = {x, y};
        }
        int get_size()
        {
            return size;
        }
        void add_size()
        {
            size++;
        }
};



void run(int h, int w, snake object)
{
    int start_y = h / 2;    //Start Position
    int start_x = w / 2;

    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE); // Special key


    

    while (true)
    {
        clear();
        { //Frame
            for (size_t i = 0; i < w; i++)
            {
                printw("#");
            }
            printw("\n");
            for (int i=1; i < (h-1); i++) {
                printw("#");
                // cout << setw(w - 1) << "#";
                mvprintw(i, w-1, "#");
                printw("\n");
            }
            for (size_t i = 0; i < w; i++)
            {
                printw("#");
            }

        }
        
        
        //update body
        if(object.whatis_direction() != Direction::none)    //fix hide body
        {
            object.set_body_value(start_x, start_y, 0);
        }

        // Update snake Position
        if(object.whatis_direction() == Direction::up)
        {
            start_y++;
        }
        else if(object.whatis_direction() == Direction::down)
        {
            start_y--;
        }
        else if(object.whatis_direction() == Direction::left)
        {
            start_x--;
        }
        else if(object.whatis_direction() == Direction::right)
        {
            start_x++;   
        }

        mvprintw(start_y, start_x, "@");    //Draw Snake head
        for (size_t i = 0; i < object.get_size(); i++)
        {
            mvprintw(object.body[i].second,object.body[i].first,"@");
        }
        
        
        
        { // Direction get and set Value
            int key = getch();
            if(key == 258) //UP
            {
                object.move_up();
            }
            else if(key == 259) //DOWN
            {
                object.move_down(); 
            }
            else if(key == 260) //LEFT
            {
                object.move_left();
            }
            else if(key == 261) //RIGHT
            {
                object.move_right();
            }
            else if(key == 27)
            {
                endwin();
                exit(1);
            }
            else
            {
                object.move_none();
            }
        }
        
        refresh();
    }


    endwin();
}

int main()
{
    snake player;

    run(15,25, player);
    return 0;
}