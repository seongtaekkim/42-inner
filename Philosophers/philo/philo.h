
#ifndef PHILO_H
 #define PHILO_H

#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
# include <stdio.h>

/*
****
8***
***
     -lpthread(필수)
     int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
int pthread_attr_getdetachstate(pthread_attr_t *attr, int *detachstate);

*ps : detach를 사용한다면 3번 방법을 추천한다. 이유는 pthread_detach함수가 불리기 전에 새로 생성 된 thread가 끝날 수도 있기 때문.

*/
typedef enum s_status
{
    TAKEN,
    EATING,
    SLEEP,
    THINK,
    DIE,
    COMPLETED
}   t_status;

typedef enum s_philo_endcode
{
    PROCEEDING,
    DEATH_OF_PHILO,
    FINISH_OF_EAT
}   t_philo_endcode;

typedef struct s_option
{
    int             number_of_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             number_of_eat;
    long long       start_time;
    pthread_mutex_t *fork;
    pthread_mutex_t pmutex;
    pthread_mutex_t main_mutex;
    pthread_t       monitor;
    t_philo_endcode endcode;
}   t_option;

typedef struct s_info
{
    pthread_t   philo;
    int         id;
    int         rfork;
    int         lfork;
    t_status    status;
    long long   philo_time;
    t_option    *option;
}   t_info;

typedef enum s_bool
{
    false,
    true
}   t_bool;

char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);

int     check_time(double s_time, int sleep_time);
t_bool  cur_time(long long *begin);
t_bool	wait_time(long long start, long long time);

t_bool    sync_print(t_info *info, char *msg);
t_bool     _atoi(const char *str, int *output);


t_bool take_fork(t_info *info);
t_bool  eat_philo();
t_bool  put_fork(t_info *info);
t_bool  sleep_philo();
t_bool  think_philo();
int exit_process(t_info *info);

#endif