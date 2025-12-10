
typedef struct  s_point
  {
    int           x;
    int           y;
  }               t_point;


void  flood_fill(char **tab, t_point size, t_point begin)
{
    char original;

    // Controlla limiti
    if (begin.x < 0 || begin.y < 0 || begin.x >= size.x || begin.y >= size.y)
        return;

    original = tab[begin.y][begin.x];

    // Se è già F, non fare nulla
    if (original == 'F')
        return;

    // Funzione ricorsiva interna
    void fill(int x, int y)
    {
        if (x < 0 || y < 0 || x >= size.x || y >= size.y)
            return;
        if (tab[y][x] != original)
            return;
        tab[y][x] = 'F';
        fill(x + 1, y);
        fill(x - 1, y);
        fill(x, y + 1);
        fill(x, y - 1);
    }

    fill(begin.x, begin.y);
}