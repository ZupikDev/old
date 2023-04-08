void test_addition()
{
    Matrice m1{ 2, 3 };
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(0, 2) = 3;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    m1(1, 2) = 6;

    Matrice m2{ 2, 3 };
    m2(0, 0) = 0;
    m2(0, 1) = 4;
    m2(0, 2) = 9;
    m2(1, 0) = 4;
    m2(1, 1) = -7;
    m2(1, 2) = 1;

    Matrice resultat{ 2, 3 };
    resultat(0, 0) = 1;
    resultat(0, 1) = 6;
    resultat(0, 2) = 12;
    resultat(1, 0) = 7;
    resultat(1, 1) = -3;
    resultat(1, 2) = 7;

    Matrice const addition{ m1 + m2 };

    assert(addition.nb_lignes() == resultat.nb_lignes() && "L'addition n'est pas correcte.");
    assert(addition.nb_colonnes() == resultat.nb_colonnes() && "L'addition n'est pas correcte.");
    for (int i{ 0 }; i < addition.nb_lignes(); ++i)
    {
        for (int j{ 0 }; j < addition.nb_colonnes(); ++j)
        {
            assert(resultat(i, j) == addition(i, j) && "L'addition n'est pas correcte.");
        }
    }
}

void test_multiplication_entier()
{
    Matrice m1{ 2, 3 };
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(0, 2) = 3;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    m1(1, 2) = 6;

    Matrice resultat{ 2, 3 };
    resultat(0, 0) = 2;
    resultat(0, 1) = 4;
    resultat(0, 2) = 6;
    resultat(1, 0) = 6;
    resultat(1, 1) = 8;
    resultat(1, 2) = 12;

    Matrice const multiplication{ m1 * 2 };

    assert(resultat.nb_lignes() == multiplication.nb_lignes() && "La multiplication par un entier n'est pas correcte.");
    assert(resultat.nb_colonnes() == multiplication.nb_colonnes() && "La multiplication par un entier n'est pas correcte.");
    for (int i{ 0 }; i < multiplication.nb_lignes(); ++i)
    {
        for (int j{ 0 }; j < multiplication.nb_colonnes(); ++j)
        {
            assert(resultat(i, j) == multiplication(i, j) && "La multiplication par un entier n'est pas correcte.");
        }
    }
}

void test_multiplication_matrice()
{
    Matrice m1{ 2, 3 };
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(0, 2) = 3;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    m1(1, 2) = 6;

    Matrice m2{ 3, 2 };
    m2(0, 0) = 0;
    m2(0, 1) = 4;
    m2(1, 0) = 4;
    m2(1, 1) = -7;
    m2(2, 0) = 9;
    m2(2, 1) = 1;

    Matrice resultat{ 2, 2 };
    resultat(0, 0) = 35;
    resultat(0, 1) = -7;
    resultat(1, 0) = 70;
    resultat(1, 1) = -10;

    Matrice const multiplication{ m1 * m2 };

    assert(resultat.nb_lignes() == multiplication.nb_lignes() && "La multiplication par une matrice n'est pas correcte.");
    assert(resultat.nb_colonnes() == multiplication.nb_colonnes() && "La multiplication par une matrice n'est pas correcte.");
    for (int i{ 0 }; i < multiplication.nb_lignes(); ++i)
    {
        for (int j{ 0 }; j < multiplication.nb_colonnes(); ++j)
        {
            assert(resultat(i, j) == multiplication(i, j) && "La multiplication par une matrice n'est pas correcte.");
        }
    }
}

void test_transposition()
{
    Matrice m1{ 2, 3 };
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(0, 2) = 3;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    m1(1, 2) = 6;

    Matrice resultat{ 3, 2 };
    resultat(0, 0) = 1;
    resultat(0, 1) = 3;
    resultat(1, 0) = 2;
    resultat(1, 1) = 4;
    resultat(2, 0) = 3;
    resultat(2, 1) = 6;

    Matrice const transposee{ m1.transpose() };

    assert(resultat.nb_lignes() == transposee.nb_lignes() && "La transposition n'est pas correcte.");
    assert(resultat.nb_colonnes() == transposee.nb_colonnes() && "La transposition n'est pas correcte.");
    for (int i{ 0 }; i < transposee.nb_lignes(); ++i)
    {
        for (int j{ 0 }; j < transposee.nb_colonnes(); ++j)
        {
            assert(resultat(i, j) == transposee(i, j) && "La transposition n'est pas correcte.");
        }
    }
}

void test_affichage()
{
    Matrice m1{ 2, 2 };
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 3;

    Matrice m2{ 2, 2 };
    m2(0, 0) = 0;
    m2(0, 1) = 4;
    m2(1, 0) = 4;
    m2(1, 1) = -7;

    std::cout << m1 << "\n";
    std::cout << m1 + m2 << "\n";
    std::cout << m1 + m2 + m2 << "\n";
}

int main()
{
    test_addition();
    test_multiplication_entier();
    test_multiplication_matrice();
    test_transposition();
    test_affichage();

    return 0;
}