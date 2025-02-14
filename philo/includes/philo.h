/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:36:57 by hsamir            #+#    #+#             */
/*   Updated: 2025/02/12 23:11:42 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

# define ARG_ERR "Usage: ./philo <philos> <t_die> <t_eat> <t_sleep> [eat_c]\n"
# define SUCCESS 1
# define FAILURE 0

typedef struct s_critical_section
{
	pthread_mutex_t			*mutex;
	void					*data;
}							t_critical_section;

typedef struct s_sim_config
{
	int						err;
	int						philo_count;
	int						die_time_ms;
	int						eat_time_ms;
	int						sleep_time_ms;
	int						max_meals;
}							t_sim_config;

typedef struct s_simulation	t_simulation;

typedef struct s_philosopher
{
	unsigned int			id;
	pthread_t				thread;
	t_simulation			*sim;
	t_critical_section		eat_count;
	t_critical_section		last_meal_time;
}							t_philosopher;

typedef enum e_status
{
	IDLE,
	RUNNING,
	TERMINATED
}							t_status;

typedef struct s_simulation
{
	t_philosopher			**philos;
	pthread_mutex_t			*fork_mutexes;
	t_critical_section		status;
	pthread_t				monitor_thread;
	pthread_mutex_t			*write_lock;
	unsigned long			start_time;
	int						philo_count;
	int						die_time_ms;
	int						eat_time_ms;
	int						sleep_time_ms;
	int						think_time_ms;
	int						max_meals;
}							t_simulation;

t_sim_config				parse_arguments(int argc, char **argv);
int							is_within_uint_range(long number);
int							is_valid_unumber(char *str);
int							strtoui(const char *str, int *error);

int							init_cs(t_critical_section *cs, int size);
int							read_cs_data(t_critical_section *cs, void *data,
								int size);
int							write_cs_data(t_critical_section *cs, void *data,
								int size);

int							get_sim_state(t_simulation *sim);
void						set_sim_state(t_simulation *sim, int state);

void						abort_philos(t_philosopher **philos,
								int philo_count);
void						abort_forks(pthread_mutex_t *fork_mutexes,
								int fork_count);
void						abort_cs(t_critical_section *cs);
void						*abort_simulation(t_simulation *simulation);

t_simulation				*initialize_simulation(t_sim_config config);
t_philosopher				**initialize_philos(t_simulation *simulation);
int							start_simulation(t_simulation *simulation);
void						*philo_routine(void *arg);
void						*monitor_thread(void *arg);

void						increase_eat_count(t_philosopher *philo);
int							get_eat_count(t_philosopher *philo);
void						set_last_meal_time(t_philosopher *philo,
								unsigned long time);
unsigned long				get_last_meal_time(t_philosopher *philo);

pthread_mutex_t				*create_mutex(void);

void						sync_printf(char *message, t_philosopher *p);

unsigned long				current_time_ms(void);
unsigned long				current_time_us(void);
void						msleep(unsigned long time);

#endif