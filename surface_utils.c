//
// Created by dawid-gajownik on 23.11.2025.
//

#include "fdf.h"

unsigned char	*transformed_px_object(t_object *object, int width, int height, t_win_prop **win_prop)
{
    int half_x;
    int half_y;
    int out_x;
    int out_y;
    Vec2 p;

    object->grades = 0;
    half_x = (*win_prop)->width/2;
    half_y = (*win_prop)->height/2;
    out_x = (object->width*object->scale/4-(*win_prop)->width/2);
    out_y = -(object->height*object->scale/4-(*win_prop)->height/2);

    out_x = (int)round(out_x * cos(object->grades * M_PI / 200.0) - out_y * sin(object->grades * M_PI / 200.0)) + object->offset_x;
    out_y = (int)round(out_x * sin(object->grades * M_PI / 200.0) + out_y * cos(object->grades * M_PI / 200.0));

    p = map_to_sphere_2D(out_x, out_y,
                      width*1/4, height*1/4,
                      height/2*object->scale/4, height/2*1/4);
    out_x = p.x;
    out_y = p.y;

    if (out_x <= -half_x || out_x >= half_x || out_y <= -half_y || out_y >= half_y)
        return (NULL);
    return (object->img_data
            + ( ((*win_prop)->height/8 - (out_y*object->scale)) * object->line_size )
            + ( ((out_x) + (*win_prop)->width/8) * object->bytes_pp ));
}

unsigned char	*transformed_px(t_map_prop **map_prop, int width, int height, t_win_prop **win_prop)
{
    int half_x;
    int half_y;
    int out_x;
    int out_y;
    Vec2 p;

    out_x = ((*map_prop)->width*(*win_prop)->scale-(*win_prop)->width/2) + centering_offset_x(win_prop, width);
    out_y = -((*map_prop)->height*(*win_prop)->scale-(*win_prop)->height/2) - centering_offset_y(win_prop, height);
    half_x = (*win_prop)->width/2;
    half_y = (*win_prop)->height/2;
    if ((*win_prop)->s_down == 0) {
        out_x = (int)round(out_x * cos((*map_prop)->grades * M_PI / 200.0) - out_y * sin((*map_prop)->grades * M_PI / 200.0)) + (*win_prop)->offset_x;
        out_y = (int)round(out_x * sin((*map_prop)->grades * M_PI / 200.0) + out_y * cos((*map_prop)->grades * M_PI / 200.0)) - (*win_prop)->offset_y;
    }
    else {
        out_x = (int)round(out_x * cos(0) - out_y * sin(0))+ (*win_prop)->sphere_correction_x;
        out_y = (int)round(out_x * sin(0) + out_y * cos(0))+ height/2*(*win_prop)->scale;
    }
    if ((*win_prop)->a_down == 1 && (*win_prop)->s_down == 0) {
        out_x = out_x + perspective_offset_x(win_prop, out_x, out_y, height);
        out_y = out_y + perspective_offset_y(map_prop, height);
    }
    if ((*win_prop)->s_down == 1) {
        p = map_to_sphere_2D(out_x, out_y,
              width*(*win_prop)->scale, height*(*win_prop)->scale,
              height/2*(*win_prop)->scale, height/2*(*win_prop)->scale);
        out_x = p.x;
        out_y = p.y;
    }
    if ((*win_prop)->s_down == 1 && (*win_prop)->s_down == 1) {
        out_x = out_x + (*win_prop)->offset_x;
        out_y = out_y - (*win_prop)->offset_y;
    }
    if (out_x <= -half_x || out_x >= half_x-10 || out_y <= -half_y+10 || out_y >= half_y)
        return (NULL);
    return ((*map_prop)->img_data
            + ( ((*win_prop)->height/2 - (out_y)) * (*map_prop)->line_size )
            + ( ((out_x) + (*win_prop)->width/2) * (*map_prop)->bytes_pp ));
}

Vec2 map_to_sphere_2D(int px, int py, int width, int height,
                      int radiusX, int radiusY)
{
    float u = (float)px / (float)width;
    float v = (float)py / (float)height;

    float lambda = 2.0f * M_PI * (u - 0.5f);
    float phi    = M_PI * (v - 0.5f);

    float xf = cosf(phi) * sinf(lambda);
    float yf = sinf(phi);

    Vec2 out;
    out.x = (int)(xf * radiusX);
    out.y = (int)(yf * radiusY);

    return out;
}