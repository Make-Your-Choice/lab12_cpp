// PLab12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string>
#include <string.h>
#include <cstdlib>

using namespace std;

#define nmax 100
#define str_0 "unknown"

class payment
{
protected:
    int is_succeed;
public:
    payment(int a)
    {
        is_succeed = a;
    }
    virtual int is_accessible() = 0;
};

class payment_cash : public payment
{
public:
    payment_cash(int a) : payment(a)
    {
    }
    int is_accessible()
    {
        return is_succeed;
    }
};

class payment_card : public payment
{
public:
    payment_card(int a) : payment(a)
    {
    }
    int is_accessible()
    {
        return is_succeed;
    }
};

class special //бонусы
{
protected:
    int bonus_num; //число бонусов
    char* definition; //наименование бонусов
public:
    special() //конструктор без параметров
    {
        this->bonus_num = 5;
        definition = new char[10];
        strcpy(this->definition, "");
    }
    special(int a) //конструктор с параметром
    {
        this->bonus_num = a;
    }
    special(char* b, int c) //конструктор с параметрами
    {
        definition = new char[10];
        strcpy(definition, b);
        bonus_num = c;
    }
    special(const special& spec_offer) //конструктор копирования + мелкое копирование
    {
        this->definition = spec_offer.definition;
        this->bonus_num = spec_offer.bonus_num;
    }
    special& operator = (special& spec_offer) //перегрузка оператора присваивания + глубокое копирование
    {
        int k;
        if (definition)
        {
            delete definition; // очистка памяти
        }
        definition = NULL;
        this->bonus_num = spec_offer.bonus_num; // копирование обычного поля
        k = strlen(spec_offer.definition) + 1;
        definition = new char[k];  // выделение памяти для новой копии памяти для наименования
        strcpy(this->definition, spec_offer.definition);  // копирование в новую выделенную область
        return *this;
    }
    void output() //вывод общий
    {
        printf("\nNumber of bonuses: %d\nDefinition: %s\n", bonus_num, definition);
    }
    void output1() //вывод исла бонусов
    {
        printf("%d ", bonus_num);
    }
    void change_def(char* a) //изменение наименования
    {
        strcpy(this->definition, a);
    }
    void change_bonus_num(int a) //изменение числа бонусов
    {
        this->bonus_num = a;
    }
    virtual void expand_bonus_num()
    {
        puts("\nIncreasing number of bonuses");
        this->bonus_num += 2;
        puts("Number of bonuses increased on 2");
    }
    void reduce_bonus() //сокращение числа бонусов
    {
        puts("\nDecreasing number of bonuses");
        this->bonus_num -= 2;
        puts("Number of bonuses decreased on 2");
    }
    void reduce_bonus_on_num(int a)
    {
        puts("\nDecreasing number of bonuses");
        this->bonus_num -= a;
        printf("Number of bonuses decreased on %d\n", a);
    }
    void set_default() //установка значений по умолчанию
    {
        this->bonus_num = 5;
        definition = new char[10];
        strcpy(this->definition, str_0);
    }
    int get_bonus_num()
    {
        return this->bonus_num;
    }
    char* get_deinition()
    {
        return this->definition;
    }
    friend void operator << (ostream& o, special spec_offer)
    {
        cout << "\nNumber of bonuses : " << spec_offer.bonus_num << "\nDefinition: " << spec_offer.definition << "\n";
    }
    bool is_expanded_over_ten()
    {
        expand_bonus_num();
        if (bonus_num > 10)
            return true;
        else
            return false;
    }
};

class limited_special : public special
{
    int times_per_year;
public:
    limited_special(char* a, int b, int c) : special(a, b)
    {
        times_per_year = c;
    }
    void output()
    {
        printf("\nNumber of bonuses: %d\nDefinition: %s\nTimes per year: %d\n", bonus_num, definition, times_per_year);
    }
    void change_times_per_year(int a)
    {
        this->times_per_year = a;
    }
    void expand_bonus_num()
    {
        puts("\nIncreasing number of bonuses");
        this->bonus_num += 4;
        puts("Number of bonuses increased on 4");
    }
    void reduce_bonus_on_num(int a, int b)
    {
        puts("\nDecreasing number of bonuses and times per year");
        this->bonus_num -= a;
        this->times_per_year -= b;
        printf("Number of bonuses decreased on %d, times per year decreased on %d\n", a, b);
    }
    void set_default()
    {
        special::set_default();
        this->times_per_year = 2;
    }
    void operator =(special spec_offer)
    {
        this->bonus_num = spec_offer.get_bonus_num();
        this->definition = spec_offer.get_deinition();
        this->times_per_year = 4;
    }
    friend void operator << (ostream& o, limited_special lim_offer)
    {
        cout << "\nNumber of bonuses : " << lim_offer.bonus_num << "\nDefinition: " << lim_offer.definition << "\nTimes per year " << lim_offer.times_per_year << "\n";
    }
};

class book_store //основной класс
{
    special spec_offer[nmax]; //ассоциативный класс одномерный массив
    special spec_offer1[nmax][nmax]; //ассоциативный класс двумерный массив
    int n; //размерности массивов
    int m;
    std::string title = ""; //название
    std::string author = ""; //автор
    std::string genre = ""; //жанр
    int price; //цена
    int popularity; //популярность в условных единицах
public:
    int num_stock; //количество в магазине
    book_store(special spec_offer[nmax]); //конструктор параметром
    book_store(string str1, string str2, string str3, int a, int b, int c, int d, special spec_offer[nmax]); //конструктор с параметрами для одномерного массива
    book_store(string str1, string str2, string str3, int a, int b, int c, int d, int e, special spec_offer[nmax / 10][nmax / 10]); //конструктор с параметрами для двумерного массива
    book_store(string str1); //конструктор параметром
    void get();
    void output();
    void output1();
    void sell();
    void price_rise();
    void rearrange();
    void archivate();
    void genre_compare(book_store book);
    static int genre_len(book_store book); //статический метод - определение длины жанра
    int predictable_profit(int* a);
    int predictable_profit(int& a);
    friend int predictable_popularity(book_store book);
    int summarize(int a);
    static int space_left; //статическое поле - оставшееся место в магазине
    void reduce_bonus(); //метод для одномерного массива
    void reduce_bonus1(); //метод для двумерного массива
};

int book_store::space_left = 50;

book_store::book_store(special spec_offer[nmax]) //конструктор с параметром
{
    title = "";
    author = "";
    genre = "";
    n = 0;
    price = 0;
    num_stock = 0;
    popularity = 0;
    for (int i = 0; i < n; i++)
    {
        this->spec_offer[i] = spec_offer[i];
    }
    printf("\nEmpty book created\n");
};

book_store::book_store(string str) //конструктор с параметром для создания массива
{
    this->title = str;
    this->author = str_0;
    this->genre = str_0;
    this->price = 100;
    this->num_stock = 10;
    this->popularity = 15;
    this->n = 1;
    this->spec_offer[1].set_default();
}

book_store::book_store(string str1, string str2, string str3, int a, int b, int c, int d, special spec_offer[nmax]) //конструктор с параметрами для одномерного массива
{
    this->title = str1;
    this->author = str2;
    this->genre = str3;
    this->price = a;
    this->num_stock = b;
    this->popularity = c;
    this->n = d;
    for (int i = 0; i < n; i++)
    {
        this->spec_offer[i] = spec_offer[i];
    }
    printf("New book initialized (with parameters)\n");
}

book_store::book_store(string str1, string str2, string str3, int a, int b, int c, int d, int e, special spec_offer[nmax / 10][nmax / 10]) //конструктор с параметрами для двумерного массива
{
    this->title = str1;
    this->author = str2;
    this->genre = str3;
    this->price = a;
    this->num_stock = b;
    this->popularity = c;
    this->n = d;
    this->m = e;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            this->spec_offer1[i][j] = spec_offer[i][j];
        }
    }
    printf("New book initialized (with parameters)\n");
}

void book_store::get() //установка значений
{
    this->title;
    this->author;
    this->genre;
    this->price;
    this->num_stock;
    this->popularity;
    this->n;
    for (int i = 0; i < n; i++)
    {
        this->spec_offer[i];
    }
}

void book_store::output() //вывод
{
    std::cout << "\nTitle: " << title << "\nAuthor: " << author << "\nGenre: " << genre << "\nPrice: " << price << "\nNumber in stock: " << num_stock << "\nPopularity: " << popularity << '\n';
    //printf("Number of bonuses: ");
    for (int i = 0; i < n; i++)
    {
        spec_offer[i].output();
    }
    printf("\n");
}

void book_store::output1()
{
    std::cout << "\nTitle: " << title << "\nAuthor: " << author << "\nGenre: " << genre << "\nPrice: " << price << "\nNumber in stock: " << num_stock << "\nPopularity: " << popularity << '\n';
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            spec_offer1[i][j].output();
        }
    }
    printf("\n");
}

void book_store::sell() //продажа
{
    puts("\nPutting book on sale");
    num_stock = num_stock - 1;
    popularity = popularity + 5;
    puts("Ony copy sold, popularity increased on 5");
}

void book_store::price_rise() //повышение цены
{
    puts("\nRising the price");
    price = price + 50;
    puts("Price risen on 50");
    return;
}

void book_store::rearrange() //перестановка
{
    puts("\nRearranging books");
    popularity = popularity + 10;
    puts("Books rearranged, popularity increased on 10");
}

void book_store::archivate() //отправка на склад
{
    puts("\nSending 4 books to the archive");
    num_stock = num_stock - 4;
    puts("4 books now stored in archive");
}

void book_store::genre_compare(book_store book) //сравнение жанров двух книг
{
    if (this->genre.compare(book.genre) == 0)
        printf("\nGenres are the same\n");
    else
        printf("\nGenres are different\n");
}

int book_store::summarize(int a) //сложение количества двух книг
{
    return this->num_stock + a;
}

int book_store::genre_len(book_store book) //вычисление длины строки 'жанр'
{
    return book.genre.length();
}

int book_store::predictable_profit(int* a) //подсчет ожидаемой прибыли по указателю
{
    *a = num_stock * price;
    return *a;
}

int book_store::predictable_profit(int& a) //подсчет ожидаемой прибыли по ссылке
{
    a = num_stock * price;
    return a;
}

int predictable_popularity(book_store book) //подсчет ожидаемой популярности от продажи (дружественная функция)
{
    return book.num_stock * 5 + book.popularity;
}

void book_store::reduce_bonus() //сокращение числа бонусов для одномерного массива
{
    for (int i = 0; i < n; i++)
    {
        this->spec_offer[i].reduce_bonus();
    }
}

void book_store::reduce_bonus1() //сокращение числа бонусов для двумерного массива
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            this->spec_offer1[i][j].reduce_bonus();
        }
    }
}

int main()
{
    int x = 0, y, z, x2, n, m, k = 1, p, r; //переменные
    char* y2;
    y2 = new char[10];
    string x1, y1, z1;
    string s1, s2, s3; //массивы

    //работа с производным классом

    puts("\nWorking with a derivative class");
    int f1, f2;
    char* t;
    t = new char[10];
    strcpy(t, "ppp");
    limited_special lim_offer1(t, 8, 6);
    strcpy(t, "hhh");
    special sp_offer(t, 7);
    cout << lim_offer1;
    puts("\nOverload without basic method (reducing bonus num)");
    lim_offer1.reduce_bonus_on_num(2, 1);
    cout << lim_offer1;
    puts("\nOverload with basic method (setting default val)");
    lim_offer1.set_default();
    cout << lim_offer1;
    puts("\nOverload = (lim_offer1 = sp_offer)");
    puts("\nsp_offer");
    cout << sp_offer;
    lim_offer1 = sp_offer;
    puts("\nlim_offer1");
    cout << lim_offer1;
    puts("\nOverload of virtual function (increasing bonus_num for sp_offer and lim_offer1)");
    puts("\nVirtual function called by non-virtual");
    /*sp_offer.expand_bonus_num();
    puts("\nsp_offer");
    cout << sp_offer;
    lim_offer1.expand_bonus_num();
    puts("\nlim_offer1");
    cout << lim_offer1;*/
    f1 = sp_offer.is_expanded_over_ten();
    if (f1)
        puts("\nbonus num of sp_offer is over 10");
    else
        puts("\nbonus num of sp_offer is less than 10");
    f2 = lim_offer1.is_expanded_over_ten();
    if (f2)
        puts("\nbonus num of lim_offer1 is over 10");
    else
        puts("\nbonus num of lim_offer1 is less than 10");
    puts("\nVirtual function called by dynamic var after copying");
    strcpy(t, "rrr");
    limited_special* lim_offer2;
    lim_offer2 = new limited_special(t, 6, 4);
    special* sp_offer2;
    sp_offer2 = new special(t, 8);
    sp_offer2 = lim_offer2;
    puts("\nsp_offer2 = lim_offer2");
    cout << *sp_offer2;
    sp_offer2->expand_bonus_num();
    puts("\nsp_offer2");
    cout << *sp_offer2;

    //работа с абстрактным классом

    puts("\nWorking with an abtract class");
    int res1, res2;
    payment_cash cash1(1);
    payment_card card1(0);
    res1 = cash1.is_accessible();
    if(res1)
        puts("\ncash pay for cash1 is accessible");
    else
        puts("\ncas pay for cash1 is not accessible");
    res2 = card1.is_accessible();
    if (res2)
        puts("\ncard pay for card1 is accessible");
    else
        puts("\ncard pay for card1 is not accessible");

    //статический одномерный массив

    /*puts("\nWorking with a static one-sized massive\n");
    special spec_offer3[nmax / 10]; //вызов конструктора по умолчанию (без параметров) статический
    puts("Input number of specials\n");
    scanf_s("%d", &n);
    for (int i = 0; i < n; i++) //ввод одномерного массива
    {
        printf("\nInput number of bonuses for [%d] special: ", i+1);
        cin >> x2;
        spec_offer3[i].change_bonus_num(x2);
        printf("Input bonus definition for [%d] special: ", i+1);
        cin >> y2;
        spec_offer3[i].change_def(y2);
    }
    puts("\nInput information about 3 book\n");
    printf("Input title: ");
    cin >> s1;
    printf("Input author: ");
    cin >> s2;
    printf("Input genre: ");
    cin >> s3;
    r = 0;
    while (r == 0) //проверка корректности ввода цены
    {
        printf("Input price: ");
        r = 1;
        cin >> x1;
        try
        {
            if (!isdigit(x1[0])) //если цена - цифра
                throw 1;
            x = stoi(x1);
        }
        catch (int v)
        {
            cout << "Incorrect value\n"; //сообщение об ошибке
            r = 0;
        }
        if (r == 1)
        {
            continue;
        }
    }
    r = 0;
    while (r == 0) //проверка корректности ввода количества на складе
    {
        printf("Input number in stock: ");
        r = 1;
        cin >> y1;
        try
        {
            if (!isdigit(y1[0])) //если количество на складе - цифра
                throw 1;
            y = stoi(y1);
        }
        catch (int v)
        {
            cout << "Incorrect value\n"; //сообщение об ошибке
            r = 0;
        }
        if (r == 1)
        {
            continue;
        }
    }
    r = 0;
    while (r == 0) //проверка корректности ввода популярности
    {
        printf("Input popularity: ");
        r = 1;
        cin >> z1;
        try
        {
            if (!isdigit(z1[0])) //если популярность - цифра
                throw 1;
            z = stoi(z1);
        }
        catch (int v)
        {
            cout << "Incorrect value\n"; //сообщение об ошибке
            r = 0;
        }
        if (r == 1)
        {
            continue;
        }
    }
    book_store* book3 = new book_store(s1, s2, s3, x, y, z, n, spec_offer3); //вызов конструктора с параметрами динамический
    printf("\nYour book\n");
    book3->get();
    book3->output();
    book3->sell();
    printf("\nThird book\n");
    book3->get();
    book3->output();
    book3->price_rise();
    printf("\nThird book\n");
    book3->get();
    book3->output();
    book3->rearrange();
    printf("\nThird book\n");
    book3->get();
    book3->output();
    book3->archivate();
    printf("\nThird book\n");
    book3->get();
    book3->output();
    puts("Decreasing number for all the specials");
    book3->reduce_bonus();
    book3->get();
    book3->output();
    k = 1;
    p = 0;
    book3->predictable_profit(&k);
    printf("\nPredictable profit for the third book (using *): %d\n", k);
    p = predictable_popularity(*book3);
    printf("\nPredictable popularity for the first book (friend fuction): %d\n", p);*/

    //статический двумерный массив

    /*puts("\nWorking with a static two-sized massive\n");
    special spec_offer4[nmax / 10][nmax / 10]; //вызов конструктора по умолчанию (без параметров) статический
    puts("Input number of specials (n and m)\n");
    scanf_s("%d %d", &n, &m);
    for (int i = 0; i < n; i++) //ввод двумерного массива
    {
        for (int j = 0; j < m; j++)
        {
            printf("\nInput number of bonuses for [%d][%d] special: ", i + 1, j + 1);
            cin >> x2;
            spec_offer4[i][j].change_bonus_num(x2);
            printf("Input bonus definition for [%d][%d] special: ", i + 1, j + 1);
            cin >> y2;
            spec_offer4[i][j].change_def(y2);
        }
    }
    puts("\nInput information about 3 book\n");
    printf("Input title: ");
    cin >> s1;
    printf("Input author: ");
    cin >> s2;
    printf("Input genre: ");
    cin >> s3;
    r = 0;
    while (r == 0) //проверка корректности ввода цены
    {
        printf("Input price: ");
        r = 1;
        cin >> x1;
        try
        {
            if (!isdigit(x1[0])) //если цена - цифра
                throw 1;
            x = stoi(x1);
        }
        catch (int v)
        {
            cout << "Incorrect value\n"; //сообщение об ошибке
            r = 0;
        }
        if (r == 1)
        {
            continue;
        }
    }
    r = 0;
    while (r == 0) //проверка корректности ввода количества на складе
    {
        printf("Input number in stock: ");
        r = 1;
        cin >> y1;
        try
        {
            if (!isdigit(y1[0])) //если количество на складе - цифра
                throw 1;
            y = stoi(y1);
        }
        catch (int v)
        {
            cout << "Incorrect value\n"; //сообщение об ошибке
            r = 0;
        }
        if (r == 1)
        {
            continue;
        }
    }
    r = 0;
    while (r == 0) //проверка корректности ввода популярности
    {
        printf("Input popularity: ");
        r = 1;
        cin >> z1;
        try
        {
            if (!isdigit(z1[0])) //если популярность - цифра
                throw 1;
            z = stoi(z1);
        }
        catch (int v)
        {
            cout << "Incorrect value\n"; //сообщение об ошибке
            r = 0;
        }
        if (r == 1)
        {
            continue;
        }
    }
    book_store* book4 = new book_store(s1, s2, s3, x, y, z, n, m, spec_offer4); //вызов конструктора с параметрами динамический
    printf("\nYour book\n");
    book4->get();
    book4->output1();
    book4->sell();
    printf("\nThird book\n");
    book4->get();
    book4->output1();
    book4->price_rise();
    printf("\nThird book\n");
    book4->get();
    book4->output1();
    book4->rearrange();
    printf("\nThird book\n");
    book4->get();
    book4->output1();
    book4->archivate();
    printf("\nThird book\n");
    book4->get();
    book4->output1();
    puts("Decreasing number for all the specials");
    book4->reduce_bonus1();
    book4->get();
    book4->output1();
    k = 1;
    p = 0;
    book4->predictable_profit(&k);
    printf("\nPredictable profit for the third book (using *): %d\n", k);
    p = predictable_popularity(*book4);
    printf("\nPredictable popularity for the first book (friend fuction): %d\n", p);*/

    //массив с помощью конструктора с параметром

    /*printf("\nMassive using constructor with a single parameter\n");
    special spec_offer5[1];
    string title1 = "rrrr";
    string title2 = "ffff";
    book_store book5[2] = { title1,title2 };
    for (int i = 0; i < 2; i++)
    {
        book5[i].output();
    }*/

    //мелкое копирование

    /*printf("\nShallow copying\n");
    char* ptr1;
    ptr1 = new char[10];

    strcpy(ptr1, "iii");
    special spec_offer6(ptr1, 10); //вызов конструктора с параметрами статический
    special spec_offer7 = spec_offer6; //вызов конструктора копирования

    printf("\nspec_offer6\n");
    spec_offer6.output();
    printf("\nspec_offer7\n");
    spec_offer7.output();

    strcpy(ptr1, "jjj");
    spec_offer6.change_def(ptr1);
    spec_offer6.change_bonus_num(5);
    printf("\nspec_offer6\n");
    spec_offer6.output();
    printf("\nspec_offer7\n");
    spec_offer7.output();*/

    //глубокое копирование

    /*printf("\nDeep copying and overload\n");
    special* spec_offer_1;
    char* ptr;
    ptr = new char[10];
    strcpy(ptr, "ppp");
    spec_offer_1 = new special(ptr, 10);
    special* spec_offer_2;
    strcpy(ptr, "kkk");
    spec_offer_2 = new special(ptr, 15);
    printf("\nspec_offer_1\n");
    spec_offer_1->output();
    printf("\nspec_offer_2\n");
    spec_offer_2->output();
    *spec_offer_2 = *spec_offer_1;
    printf("\nspec_offer_1\n");
    spec_offer_1->output();
    printf("\nspec_offer_2\n");
    spec_offer_2->output();
    spec_offer_1->set_default();
    strcpy(ptr, "jjj");
    spec_offer_1->change_def(ptr);
    printf("\nspec_offer_1\n");
    spec_offer_1->output();
    printf("\nspec_offer_2\n");
    spec_offer_2->output();*/
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
