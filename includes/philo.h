#include <pthread.h>

#define ARGUMENT_ERROR "Usage: ./philo <philos> <t_die> <t_eat> <t_sleep> [eat_count]\n"

typedef struct s_critical_section
{
	pthread_mutex_t		*mutex;
	void				*data;
}						t_critical_section;
 
typedef struct s_sim_config
{
	int					err;
	int					philo_count;
	int					die_time_ms;
	int					eat_time_ms;
	int					sleep_time_ms;
	int					max_meals;
}						t_sim_config;

typedef struct			s_simulation t_simulation;

typedef struct s_philosopher
{
	unsigned int		id;
	pthread_t			*thread;
	t_simulation		*t_sim;
	t_critical_section	eat_count;
	t_critical_section	last_meal_time;
}						t_philosopher;

typedef enum e_status
{
	IDLE,
	RUNNING,
	TERMINATED
}						t_status;

typedef struct s_simulation
{
	t_philosopher		*philos;
	pthread_mutex_t		*fork_mutexes;
	t_status			status;
	unsigned int		philo_count;
	int					die_time_ms;
	int					eat_time_ms;
	int					sleep_time_ms;
	int					max_meals;
}						t_simulation;

t_sim_config    parse_arguments(int argc, char** argv);
int				is_within_uint_range(long number);
int				is_valid_unumber(char *str);
int				strtoui(const char *str, int *error);