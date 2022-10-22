#include "compensate.hpp"

/**
 * @brief
 * @param: shoot_speed distance height
 *
 */
void Compensate::solve_above(float v, float s, float h)
{
    compensate_angle = static_cast<float>(180 / 3.14 * atan2((pow(v, 2) + sqrt(pow(v, 4) - 9.8 * (2 * h * pow(v, 2) - 9.8 * pow(s, 2)))), (9.8 * s)));
}

void Compensate::solve_below(float v, float s, float h)
{
    compensate_angle = static_cast<float>(180 / 3.14 * atan2((-pow(v, 2) + sqrt(pow(v, 4) - pow(9.8 * s, 2) + 2 * 9.8 * h * pow(v, 2))), (9.8 * s)));
}

int Compensate::set(Point2f aim)
{
    if ((aim.y - image_center.y) > 0)
    {
        return 1;
    }

    if ((aim.y - image_center.y) < 0)
    {
        return 2;
    }

    else
    {
        return 0;
    }
}

void Compensate::run(Point2f aim, float v, float s, float h)
{
    if (set(aim) == 1)
    {
        solve_above(v, s, h);
        cout<<"compensate_angle + :"<<compensate_angle<<endl;
    }

    if (set(aim) == 2)
    {
        solve_below(v, s, h);
        cout<<"compensate_angle - :"<<compensate_angle<<endl;
    }
    
    else{
        cout<<"no need for compensation"<<endl;
    }
}

// pow(v,2)+sqrt(pow(v,4)-9.8*(2*h*pow(v,2)-9.8*pow(s,2)))

float solution(float a, float b, float c, float d)
{
	float x0, f, fd, h; 
	float x = 1.5;

	do
	{
		x0 = x; 

		f = a * x0 * x0 * x0 + b * x0 * x0 + c * x0 + d;

		fd = 3 * a * x0 * x0 + 2 * b * x0 + c;

		h = f / fd;

		x = x0 - h; 

	} while (fabs(x-x0) >= 1e-5);

	return x;
}

