/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 17:42:37 by napark            #+#    #+#             */
/*   Updated: 2021/04/01 21:14:52 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void    parse(t_cube3d *s, char *argv)
{
    int fd;
    int check;
    char *line;

    if (check_path(argv))//.cub파일 유효성 검사
        ft_strexit("ERROR : Invalid file (.cub)");//아니면 exit처리
    if ((fd = open(argv, O_RDONLY)) == -1)//.cub파일 오픈
        ft_strexit("ERROR : we can't open .cub file");//열지 못하면 프로그램 exit
    while ((s_parse_check != 0xFF) && (check = get_next_line(fd, &line)) >= 0)
        check_parse_type(s, line);
}

static int     check_path(char *argv)
{
    int     len;

    if (ft_strlen(argv) < 4)
            ft_strexit("ERROR : unavailable .cub file");
            return(ERROR);
    if (argv[len - 1] == 'b' && argv[len - 2] == 'u' && argv[len - 3] == 'c' && argv[len - 4] == '.')
            return (SUCCESS);
    return (ERROR);
}

static void     check_parse_type(t_cube3d *s, char *line)
{
    char **split_count;
    int word_count;

    if (ft_strlen(line))
    {
        if (!(split_count = ft_split_count(line, ' ', &word_count)))//' '로 분리된 부분이 몇개인지 카운트
            ft_strexit("ERROR : (.cub) file is invalid!");
        start_parse(s, split_count, word_count);
        
    }
}

static  void    start_parse(t_cube3d *s, char **split_count, int word_count)
{
    if (!ft_strcmp(split_count[0], "R") && word_count == 3)
        store_information(s, split_count[1], split_count[2]);
}

static  int     ft_new_itoa(t_cube3d *s, char *value)
{
    int     len;
    int     n;

    n = 0;
    len = ft_strlen(value);
    while (len > 0 && ft_strchr("0123456789", value))
    {
        n *= 10;
        n += *value++ - '0';
        --len; 
    }
    if (len != 0)
        ft_strexit("ERROR : parsing error store_information");
    return (n);

}

void    store_information(t_cube3d *s, char **width, char **height)
{
    t_ivec  ti;

    if (!width || !height)
        ft_strexit("ERROR : No data in width and height");
    else if (ft_only_digit(width) || ft_only_digit(height))
        ti.data_width = ft_new_itoa(s, width);
        ti.data_height = ft_new_itoa(s, height);
    
    if (ti.data_height < s->timg.height)
        s->timg.height = ti.data_height;
    if (ti.data_width < s->timg.width)
        s->timg.width = ti.data_width;
}