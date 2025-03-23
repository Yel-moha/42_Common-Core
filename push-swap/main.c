#include "push_swap.h"

void free_all(t_stack *stack)
{
    if (stack->a)
    {
        free(stack->a);
        stack->a = NULL;
    }
    if (stack->b)
    {
        free(stack->b);
        stack->b = NULL;
    }
    if (stack->sorted)
    {
        free(stack->sorted);
        stack->sorted = NULL;
    }
}

int main(int argc, char **argv)
{
    t_stack stack;

    if (argc < 2)
        return (0);
    take_input(argc, argv, &stack);
   // if (stack.size_a <= 5)
        cycle_sort(&stack);  // ottimo per ≤ 5 elementi
  //  else
   //     radix_sort(&stack);  // efficiente per ≥ 6 elementi
    free_all(&stack);
    return (0);
}



// test 100 numeri
/* ./push_swap 132 76 297 610 197 261 715 763 90 931 637 343 855 864 666 267 395 211 657 933 994 888 800 
731 185 225 410 184 129 86 3 149 947 696 899 670 584 445 472 820 196 256 944 122 799 480 253 709 394 975 
714 753 678 644 276 531 821 405 889 742 868 504 590 273 912 870 535 153 999 856 43 908 499 845 155 295 552
 989 367 850 279 53 511 227 916 455 752 222 138 577 609 578 660 773 751 25 205 553 770 199

*/
