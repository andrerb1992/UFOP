
typedef double Real;
typedef short Inteiro;

typedef struct {
    Inteiro numerador;
    Inteiro denominador;
} Racional;


Real transforma(const Racional* r);

void soma(const Racional* r1, const Racional* r2, Racional* s);


void simplifica(const Racional* r, Racional* rs);


#endif	/* RACIONAL_H */

