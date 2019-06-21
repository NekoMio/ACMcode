#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <list>
#include <cstdlib>
int n, m, T, D_F, Z_D_to_M;
char C[2005];
// #define Log 1
namespace Pig
{
    bool Died[11];
    struct Pig_data
    {
        /*
        Id :
            1: 主猪
            2: 忠猪
            3: 反猪
        */
        std::list<char> Card;
        std::list<char>::iterator it, it2;
        int Identity, Strength;
        bool Equipped, Jump, Similar;
        void init(int Id, char *s)
        {
            Strength = 4, Similar = 0;
            Identity = Id;
            if (Id == 1) Jump = 1;
            for (int i = 1; i <= 4; i++)
                Card.push_back(s[i]);
        }
        void Print(int i = 0)
        {
            it2 = Card.end();
            if (it2 == Card.begin()) 
            {
                if(i != n)
                    printf("\n");
                return;
            }
            it2--;
            for (it = Card.begin(); it != it2; it++)
                printf("%c ", *it);
            printf("%c", *it2);
            if(i != n) printf ("\n");
        }
    }Pig[11];

}
namespace Card
{
    struct Card_Heap_data
    {
        char Card_Heap[2005];
        int h, t;
        void init(char *s, int Num)
        {
            t = Num;
            h = 0;
            for (int i = 1; i <= Num; i++)
                Card_Heap[i] = s[i];
        }
        char Get_Card()
        {
            if (h == t)
                return Card_Heap[h];
            else
                return Card_Heap[++h];
        }
    }Card;
}
namespace Main
{
void Read_init()
{
    #ifdef Log
        printf("===========================================\n Read Start\n=================================\n");
    #endif
    scanf("%d%d", &::n ,&::m);
    char s[5], ID[4];
    for (int i = 1; i <= n; i++)
    {
        scanf ("%s", ID);
        for (int j = 1; j <= 4; j++)
            std::cin >> s[j];
        if (ID[0] == 'M')
            Pig::Pig[i].init(1, s);
        else if (ID[0] == 'Z')
            Pig::Pig[i].init(2, s);
        else
            Pig::Pig[i].init(3, s), T++;
    }
#ifdef Log
    printf("===========================================\n Read Pig Succeed\n=================================\n");
#endif
    memset(Pig::Died, 0, sizeof(Pig::Died));
    for (int i = 1; i <= m; i++)
        std::cin >> C[i];
    #ifdef Log
        printf("===========================================\n Read Card Succeed\n=================================\n");
    #endif
    Card::Card.init(C, m);
#ifdef Log
    printf("===========================================\nCard Init Succeed\n=================================\n");
#endif
}
void Get_Card(int x, int t)
{
#ifdef Log
    printf("Pig %d Get %d Card\n", x, t);
#endif
    while (t--)
    {
        Pig::Pig[x].Card.push_back(Card::Card.Get_Card());
    }
}
int nxt[11];
int next(int x)
{
    if (nxt[x] != 0) return nxt[x];
    for (int i = x + 1; ; i++)
    {
        if (i == n + 1) i = 1;
        if (!Pig::Died[i]) 
            return nxt[x] = i;
    }
}
std::list<char>::iterator it, it2, searchit, eraseit;
bool Over(int &W)
{
    bool No_Fan = 1;
    int now = 0;
    if (Pig::Died[1]) return W = 1, 1;
    else now = 1;
    int Next_Pig = now;
    do
    {
        if (Pig::Pig[Next_Pig].Identity == 3) No_Fan = 0;
        Next_Pig = next(Next_Pig);
    }while (Next_Pig != now);
    if (No_Fan)
        return W = 0, 1;
    else
        return 0;
}
bool Judge(int x, char c, int K_Num, int &t)
{
    if (c == 'P') 
    {
        if (Pig::Pig[x].Strength != 4)
            return t = x, 1;
        else return 0;
    }
    else if (c == 'K')
    {
        if (K_Num && !Pig::Pig[x].Equipped) return 0;
        if (Pig::Pig[x].Identity == 1)
        {
            if (Pig::Pig[next(x)].Similar) return t = next(x), 1;
            if (Pig::Pig[next(x)].Identity == 3 && Pig::Pig[next(x)].Jump)
                return t = next(x), 1;
            else return 0;
        }
        else if (Pig::Pig[x].Identity == 2)
        {
            if (Pig::Pig[next(x)].Identity == 3 && Pig::Pig[next(x)].Jump)
                return t = next(x), 1;
            else return 0;
        }
        else if (Pig::Pig[x].Identity == 3)
        {
            if ((Pig::Pig[next(x)].Identity == 1 || Pig::Pig[next(x)].Identity == 2) && Pig::Pig[next(x)].Jump)
                return t = next(x), 1;
            else return 0;
        }
        else
        {
            printf ("ERROR No Identity\n");
        }
    } 
    else if (c == 'D') return 0;
    else if (c == 'F')
    {
        bool flag = 0;
        int Next_Pig = next(x);
        while (Next_Pig != x)
        {
            if (Pig::Pig[x].Identity == 1)
            {
                if (Pig::Pig[Next_Pig].Similar) return t = Next_Pig, 1;
                if (Pig::Pig[Next_Pig].Identity == 3 && Pig::Pig[Next_Pig].Jump)
                    return t = Next_Pig, 1;
                else goto Restart;
            }
            else if (Pig::Pig[x].Identity == 2)
            {
                if (Pig::Pig[Next_Pig].Identity == 3 && Pig::Pig[Next_Pig].Jump)
                    return t = Next_Pig, 1;
                else goto Restart;
            }
            else if (Pig::Pig[x].Identity == 3)
            {
                if (Pig::Pig[Next_Pig].Identity == 1)
                    return t = Next_Pig, 1;
                else if (Pig::Pig[Next_Pig].Identity == 2 && Pig::Pig[Next_Pig].Jump) 
                {
                    if (!flag) flag = 1, t = Next_Pig;
                    goto Restart;
                }
                else goto Restart;
            }
            else
            {
                printf ("ERROR No Identity\n");
            }
            Restart: Next_Pig = next(Next_Pig);
        }
        if (Pig::Pig[x].Identity == 3 && flag) return 1;
        else return 0;
    }
    else if (c == 'N' || c == 'W')
    {
        return t = -1, 1;
    }
    else if (c == 'J')
        return 0;
    else if (c == 'Z')
        return t = x, 1;
    else
    {
        printf ("ERROR in Card ID\n");
        exit(0);
        return 0;
    }
    return 0;
}
bool Have(char c, int t)// and erase
{
    #ifdef Log
        printf("It's %d to return He have ", t);
        Pig::Pig[t].Print();
    #endif
    for (searchit = Pig::Pig[t].Card.begin(); searchit != Pig::Pig[t].Card.end(); searchit++)
        if (*searchit == c)
        {
            #ifdef Log
                printf("Pig %d Used %c\n", t, c);
            #endif
            return Pig::Pig[t].Card.erase(searchit), 1;
        }
    return 0;
}
bool Need_Wuxie(int x)
{
    if (!Have('J', x)) return 0;
    Pig::Pig[x].Jump = 1;
    Pig::Pig[x].Similar = 0;
    return 1;
}
bool Wuxie(int x, bool op)
{
    int Next_Pig = x;
    do
    {
        if ((op == 0 && Pig::Pig[Next_Pig].Identity == 3) || (op == 1 && Pig::Pig[Next_Pig].Identity != 3))
        {
            if (!Need_Wuxie(Next_Pig)) goto again;
            if (!Wuxie(Next_Pig, op ^ 1)) return 1;
            return 0;
        }
        again: Next_Pig = next(Next_Pig);
    }while (Next_Pig != x);
    return 0;
}
bool Okforwuxie(int x, int t)
{
    if (!Pig::Pig[t].Jump) return 0;
    if (Pig::Pig[t].Identity == 3) return Wuxie(x, 0);
    else return Wuxie(x, 1);
}
void UseM(int x, char c, int t)
{
    if (c == 'K')
    {
        #ifdef Log
            printf("Pig %d use %c to %d\n", x, c, t);
        #endif
        if (Pig::Pig[t].Jump) Pig::Pig[x].Jump = 1;
        if (!Have('D', t))
        {
            #ifdef Log
                printf("Pig %d not have %c\n", t, 'D');
            #endif // Log
            Pig::Pig[t].Strength--;
            #ifdef Log
            printf("Pig %d HP = %d\n", t, Pig::Pig[t].Strength);
            #endif // Log
            if (Pig::Pig[t].Strength == 0)
            {
                if (!Have('P', t))
                {
                    #ifdef Log
                    printf("Pig %d Died\n", t);
                    #endif // Log
                    Pig::Died[t] = 1;
                    memset(nxt, 0, sizeof (nxt));
                    if (Pig::Died[1] == 1) return;
                    if (Pig::Pig[t].Identity == 2 && Pig::Pig[x].Identity == 1) 
                    {
                        Pig::Pig[x].Card.clear(), Pig::Pig[x].Equipped = 0;
                        Z_D_to_M = 1;
                    }
                    if (Pig::Pig[t].Identity == 3) 
                    {
                        D_F++;
                        if (D_F == T) return;
                        Get_Card(x, 3);
                    }
                }
                else
                    Pig::Pig[t].Strength = 1;
            }
        }
        return;
    }
    else if (c == 'P')
        return Pig::Pig[x].Strength++, void(0);
    else if (c == 'F')
    {
        #ifdef Log
            printf("Pig %d use %c to %d\n", x, c, t);
        #endif
        Pig::Pig[x].Jump = 1, Pig::Pig[x].Similar = 0;
        if (Pig::Pig[x].Identity == 1 && Pig::Pig[t].Identity == 2) 
        {
            Pig::Pig[t].Strength--;
            #ifdef Log
            printf("Pig %d HP = %d\n", t, Pig::Pig[t].Strength);
            #endif // Log
            if (Pig::Pig[t].Strength == 0)
            {
                if (!Have('P', t))
                {
                    #ifdef Log
                    printf("Pig %d Died\n", t);
                    #endif // Log
                    Pig::Died[t] = 1;
                    memset(nxt, 0, sizeof (nxt));
                    if (Pig::Died[1] == 1) return;
                    if (Pig::Pig[t].Identity == 2 && Pig::Pig[x].Identity == 1) 
                    {
                        Pig::Pig[x].Card.clear(), Pig::Pig[x].Equipped = 0;
                        Z_D_to_M = 1;
                    }
                    if (Pig::Pig[t].Identity == 3) 
                    {
                        D_F++;
                        if (D_F == T) return;
                        Get_Card(t, 3);
                    }
                }
                else
                    Pig::Pig[t].Strength = 1;
            }
            return;
        }
        if (Okforwuxie(x, t)) return void(0);
        while (1)
        {
            if (!Have('K', t)) 
            {
                Pig::Pig[t].Strength--;
                #ifdef Log
                printf("Pig %d HP = %d\n", t, Pig::Pig[t].Strength);
                #endif // Log
                if (Pig::Pig[t].Strength == 0)
                {
                    if (!Have('P', t))
                    {
                        #ifdef Log
                        printf("Pig %d Died\n", t);
                        #endif // Log
                        Pig::Died[t] = 1;
                        memset (nxt, 0, sizeof (nxt));
                        if (Pig::Died[1] == 1) return;
                        if (Pig::Pig[t].Identity == 2 && Pig::Pig[x].Identity == 1) 
                        {
                            Pig::Pig[x].Card.clear(), Pig::Pig[x].Equipped = 0;
                            Z_D_to_M = 1;
                        }
                        if (Pig::Pig[t].Identity == 3) 
                        {
                            D_F++;
                            if (D_F == T) return;
                            Get_Card(x, 3);
                        }
                    }
                    else
                        Pig::Pig[t].Strength = 1;
                }
                return;
            }
            if (!Have('K', x))
            {
                Pig::Pig[x].Strength--;
                #ifdef Log
                printf("Pig %d HP = %d\n", x, Pig::Pig[x].Strength);
                #endif // Log
                if (Pig::Pig[x].Strength == 0)
                {
                    if (!Have('P', x))
                    {
                        #ifdef Log
                        printf("Pig %d Died\n", x);
                        #endif // Log
                        Pig::Died[x] = 1;
                        memset (nxt, 0, sizeof (nxt));
                        if (Pig::Died[1] == 1) return;
                        if (Pig::Pig[x].Identity == 2 && Pig::Pig[t].Identity == 1) 
                        {
                            Pig::Pig[t].Card.clear(), Pig::Pig[t].Equipped = 0;
                            Z_D_to_M = 1;
                        }
                        if (Pig::Pig[x].Identity == 3) 
                        {
                            D_F++;
                            if (D_F == T) return;
                            Get_Card(t, 3);
                            return;
                        }
                    }
                    else
                        Pig::Pig[x].Strength = 1;
                }
                return;
            }
        }
    }
    else if (c == 'N')
    {
        #ifdef Log
        printf("Pig %d use %c to %d\n", x, c, t);
        #endif
        int Next_Pig = next(x);
        do
        {
            if (Okforwuxie(x, Next_Pig)) goto END1;
            if (!Have('K', Next_Pig))
            {
                Pig::Pig[Next_Pig].Strength--;
                #ifdef Log
                printf("Pig %d HP = %d\n", Next_Pig, Pig::Pig[Next_Pig].Strength);
                #endif // Log
                if (Pig::Pig[Next_Pig].Strength == 0)
                {
                    if (!Have('P', Next_Pig))
                    {
                        #ifdef Log
                        printf("Pig %d Died\n", Next_Pig);
                        #endif // Log
                        memset (nxt, 0, sizeof (nxt));
                        Pig::Died[Next_Pig] = 1;
                        if (Pig::Died[1] == 1) return;
                        if (Pig::Pig[Next_Pig].Identity == 2 && Pig::Pig[x].Identity == 1) 
                        {
                            Pig::Pig[x].Card.clear(), Pig::Pig[x].Equipped = 0;
                            Z_D_to_M = 1;
                        }
                        if (Pig::Pig[Next_Pig].Identity == 3) 
                        {
                            D_F++;
                            if (D_F == T) return;
                            Get_Card(x, 3);
                        }
                    }
                    else
                        Pig::Pig[Next_Pig].Strength = 1;
                }
                if (Pig::Pig[Next_Pig].Identity == 1 && Pig::Pig[x].Jump == 0) Pig::Pig[x].Similar = 1;
            }
            END1:Next_Pig = next(Next_Pig);
        }while (Next_Pig != x);
        return;
    }
    else if (c == 'W')
    {
        #ifdef Log
        printf("Pig %d use %c to %d\n", x, c, t);
        #endif
        int Next_Pig = next(x);
        do
        {
            if (Okforwuxie(x, Next_Pig)) goto END2;
            if (!Have('D', Next_Pig))
            {
                Pig::Pig[Next_Pig].Strength--;
                #ifdef Log
                printf("Pig %d HP = %d\n", Next_Pig, Pig::Pig[Next_Pig].Strength);
                #endif // Log
                if (Pig::Pig[Next_Pig].Strength == 0)
                {
                    if (!Have('P', Next_Pig))
                    {
                        #ifdef Log
                        printf("Pig %d Died\n", Next_Pig);
                        #endif // Log
                        Pig::Died[Next_Pig] = 1;
                        memset (nxt, 0, sizeof (nxt));
                        if (Pig::Died[1] == 1) return;
                        if (Pig::Pig[Next_Pig].Identity == 2 && Pig::Pig[x].Identity == 1) 
                        {
                            Pig::Pig[x].Card.clear(), Pig::Pig[x].Equipped = 0;
                            Z_D_to_M = 1;
                        }
                        if (Pig::Pig[Next_Pig].Identity == 3) 
                        {
                            D_F++;
                            if (D_F == T) return;
                            Get_Card(x, 3);
                        }
                    }
                    else
                        Pig::Pig[Next_Pig].Strength = 1;
                }
                if (Pig::Pig[Next_Pig].Identity == 1 && Pig::Pig[x].Jump == 0) Pig::Pig[x].Similar = 1;
            }
            END2:Next_Pig = next(Next_Pig);
        }while (Next_Pig != x);
        return;
    }
    else if (c == 'Z')
        return Pig::Pig[x].Equipped = 1, void(0);
}
void Use(int x, char c, int t)
{
    UseM(x, c, t);
    // printf("ERROR in Use at Identity, There is no Id in the Pig\n");
}
void Play(int x)
{
    it = Pig::Pig[x].Card.begin();
    int K_Num = 0;
    int Y = D_F;
    for (; it != Pig::Pig[x].Card.end(); it = it2)
    {
        int t = 0;
        if (Judge(x, *it, K_Num, t))
        {
            #ifdef Log
                printf("Pig %d Used %c to %d\n", x, *it, t);
            #endif
            Use(x, *it, t);
            if (Z_D_to_M) return;
            if (*it == 'K') K_Num++;
            Pig::Pig[x].Card.erase(it);
            it2 = Pig::Pig[x].Card.begin();
            if (Pig::Died[1] == 1 || Pig::Died[x] == 1 || D_F == T) return;
        }
        else
        {
            it2 = it;
            it2++;
        }
    }
}
void Run()
{
    int now = 1, W = 0;
    while (!Over(W))
    {
    #ifdef Log
        printf("It is %d Paly, It's Identity is %d ", now, Pig::Pig[now].Identity);
        if (Pig::Pig[now].Jump == 1)
            printf("He Jumped\n");
        else
            printf("He not Jumped\n");
    #endif // Log
        Get_Card(now, 2);
    #ifdef Log
        printf("He has ");
        Pig::Pig[now].Print();
    #endif
        Play(now);
        Z_D_to_M = 0;
        now = next(now);
    }
    if (W == 0)
    {
        printf ("MP\n");
        for (int i = 1; i <= n; i++)
        {
            if (Pig::Died[i])
                printf("DEAD\n");
            else
                Pig::Pig[i].Print(i);
        }
    }
    else
    {
        printf ("FP\n");
        for (int i = 1; i <= n; i++)
        {
            if (Pig::Died[i])
                printf("DEAD\n");
            else
                Pig::Pig[i].Print(i);
        }
    }
}
}
int main()
{
    freopen("kopk.in", "r", stdin);
    freopen("kopk.out", "w", stdout);
#ifdef Log
    printf("======================================\n Start\n======================================\n");
#endif
    Main::Read_init();
#ifdef Log
    printf("Read Success\n\n");
    printf("======================================\nGame Start\n\n");
#endif
    Main::Run();
}
