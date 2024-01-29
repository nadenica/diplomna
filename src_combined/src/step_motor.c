

int color_to_steps[] = {0, 50, 100, 150};
static int current_color = 0;

int calculate_steps(int wanted_color)
{
  int res = wanted_color - current_color;
  current_color = wanted_color;
  return res<0 ? color_to_steps[res+4]:color_to_steps[res];
}