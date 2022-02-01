#include "testing.h"

t_token *make_token(t_type *type, char *text, t_token *last)
{
    t_token *new;

    new = ft_calloc(1, sizeof(t_token));
    if (!new)
    {
        printf("error in make_token");
        exit(666);
    }
    if (type)
        new->type = *type;
    if (text)
        new->type = strdup(text);
    if (last)
        new->prev = last;
    return (new);
}