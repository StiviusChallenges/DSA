#include "vector.h"

int main()
{

    vector* vec = vector_create(10);
    print_vector(vec);
    printf("\n");
    push_back(vec,11);
    set_element(vec,0,5);
    print_vector(vec);
    vector_erase(vec,1);
    print_vector(vec);
    int n = vector_find(vec,11);
    print_vector(vec);
    printf("%d\n",n);
    vector_clear(vec);
    vector_delete(vec);
    return 0;
}
