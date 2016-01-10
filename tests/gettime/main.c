#include <extc/gettime.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    char date[15];
    char time[15];
    char datetime[30];

    get_time_str(time);
    get_date_str(date);
    get_datetime_str(datetime);

    puts(time);
    puts(date);
    puts(datetime);

    return 0;
}
