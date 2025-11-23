//
// Created by dawid-gajownik on 23.11.2025.
//

#include "fdf.h"

int	offset_z(int multiplier, int map_height, t_map_prop **map_prop)
{
    return -(map_height/multiplier*(*map_prop)->bytes_pp
            + (map_height/multiplier)*(*map_prop)->line_size*(*map_prop)->bytes_pp);
}

int centering_offset_y(t_win_prop **win_prop, int height)
{
    int offset_y = ((*win_prop)->height - height * (*win_prop)->scale);
    return offset_y/2;
}

int centering_offset_x(t_win_prop **win_prop, int width)
{
    int offset_x = ((*win_prop)->width  - width  * (*win_prop)->scale);
    return offset_x/2;
}

int	perspective_offset_x(t_win_prop **win_prop, int out_x, int out_y, int height)
{

    int offset_x = sqrt(out_x*out_x)*(height-out_y*3)/(*win_prop)->height/2;
    if (out_x<0)
        return -offset_x;
    return offset_x;
}
int perspective_offset_y(t_map_prop **map_prop, int height)
{
    return -((height-(*map_prop)->height)/10);
}