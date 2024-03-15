/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:39:52 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/15 15:18:22 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	time_frames(suseconds_t *last_fr_t, int *c_frame, int n_frames, int time)
{
	if(getms() - *last_fr_t > time)
	{
		*last_fr_t = getms();
		(*c_frame)++;
		if (*c_frame >= n_frames)
			*c_frame = 0;
	}
}

void	time_frames_p_atk(t_complete *s, int *c_frame, int n_frames, int time)
{
	if(getms() - s->unite_atk_last_f_t > time)
	{
		s->unite_atk_last_f_t = getms();
		(*c_frame)++;
		if (*c_frame >= n_frames)
		{
			*c_frame = 0;
			s->p_atk = false;
		}
	}
}

void	time_frames_exit(t_complete *s, int *c_frame, int n_frames, int time)
{
	if (getms() - s->e_last_f_t > time)
	{
		s->e_last_f_t = getms();
		(*c_frame)++;
		if(s->open_exit)
		{
			if ((*c_frame) >= 4)
				(*c_frame) = 3;
		}
		else
		{
			if ((*c_frame) >= 3)
				(*c_frame) = 0;
		}
	}
}

void	time_frames_en_atk(t_complete *s, int *c_frame, int n_frames, int time)
{
	if(getms() - s->en_atk_last_f_t > time)
	{
		s->en_atk_last_f_t = getms();
		(*c_frame)++;
		if (*c_frame >= n_frames)
		{
			*c_frame = 0;
			s->end_attack = false;
		}
	}
}

void	all_frames(t_complete *s)
{
	if(s->p_atk)
		time_frames_p_atk(s, &s->atk_u_curr_f, 4, 100);
	else
	{
		if(s->running)
			time_frames(&s->pr_last_f_t, &s->pr_curr_f, 5, 150);
		else
			time_frames(&s->p_last_f_t, &s->p_curr_f, 4, 170);
	}
	time_frames(&s->c_last_f_t, &s->c_curr_f, 3, 400);
	time_frames_exit(s, &s->e_curr_f, 4, 150);
	if(s->en_attack)
		time_frames_en_atk(s, &s->en_atk_curr_f, 3, 200);
	else
		time_frames(&s->en_last_f_t, &s->en_curr_f, 4, 400);
}
