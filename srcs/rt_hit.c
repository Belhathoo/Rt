/* ************************************************************************** */

#include <rt.h>

t_object rt_sl_plan(t_object *o, t_vec ax)
{
  t_object plan;

	plan.pos = o->pos;
	plan.rot = vec_pro_k(ax, -1);
  plan.col = o->col;
  plan.noi = o-> noi;
  plan.txt = o->txt;
  plan.mat = o->mat;
  return (plan);
}
int			rt_slicing(t_object *o, t_ray *r, t_hit *rec)
{
	t_vec     ax;
	t_vec     my;
  t_object  plan;
	double  t;
  t_vec p;
  ax = vec_unit(o->sl_vec);
  my = vec_unit(vec_sub(rec->p, vec_add(o->pos, o->sl_pnt)));
	if (vec_dot(my, ax) <= 0)
	{
    plan = rt_sl_plan(o, ax);
		t = rec->t1;
		p = vec_ray(r, rec->t);
		my = vec_unit(vec_sub(p, o->pos));
		if (vec_dot(my, ax) <= 0)
			return(0);
    rec->t = t;
    rec->p = p;
		return(rt_hit_plan(&plan, r, rec));
	}
	return (1);
}

int rt_hit(t_scene *scene, t_ray *r, t_hit *record)
{
  t_object  *obj;
  int      check_hit;

  check_hit = 0;
  record->closest = MAX;
  obj = scene->object;
  while (obj)
  {
    if (obj->hit(obj, r, record))
    {
      record->closest = record->t;
      record->curr_obj = obj;
      record->ray = r;
      check_hit = 1;
    }
    obj = obj->next;
  }
  return (check_hit);
}