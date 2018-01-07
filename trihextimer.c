#include <msp430.h>
#include <inttypes.h>

#define CMD         0
#define DATA        1

volatile int A[] = { 0, 0, 0, 0, 0, 0, 9, 13, 6, 7, 12, 10 };
volatile int B[] = { 0, 0, 0, 0, 0, 0, 0, 7, 2, 11, 5, 1 };
volatile int E[] = { 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 3, 4 };
volatile int r[] = { 9, 13, 6, 2, 11, 5, 3, 4, 8 };
volatile int b[] = { 10, 12, 7, 1 };

int a[] = { 0, 0, 0, 0 };
int pt[] = { 0, 0 };
volatile int p1point = 2;
volatile int p2point = 5;
volatile int poin = 21;
unsigned int player = 1;
unsigned int p1flag = 0;
unsigned int p2flag = 0;
unsigned int debounce = 0;

volatile int anl = 0;
void leds(volatile int led, volatile int i)
{
//    segment_dis();
    if (led == 1)
    {
        if (i == 1)
        {
            P2OUT &= ~BIT1;
            P2OUT |= BIT3;
            B[5] = 1;
            E[3] = 1;
        }
        else
        {
            P2OUT |= BIT1;
            P2OUT &= ~BIT3;
            B[5] = 0;
            E[3] = 0;
        }
    }

    else if (led == 2)
    {
        if (i == 1)
        {
            P2OUT &= ~BIT0;
            P2OUT |= BIT3;
            B[2] = 1;
        }
        else
        {
            P2OUT &= ~BIT3;
            P2OUT |= BIT0;
            B[2] = 0;
        }
    }

    else if (led == 3)
    {
        if (i == 1)
        {

            P1OUT &= ~BIT5;
            P2OUT |= BIT3;
            E[4] = 1;
        }
        else
        {

            P2OUT &= ~BIT3;
            P1OUT |= BIT5;
            E[4] = 0;
        }
    }

    else if (led == 4)
    {
        if (i == 1)
        {
            P2OUT |= BIT3;
            P1OUT &= ~ BIT4;
            E[5] = 1;
        }
        else
        {
            P1OUT |= BIT4;
            P2OUT &= ~BIT3;
            E[5] = 0;
        }
    }

    else if (led == 5)
    {
        if (i == 1)
        {
            P1OUT &= ~BIT3;
            P2OUT |= BIT3;
            B[4] = 1;
        }
        else
        {
            P2OUT &= ~BIT3;
            P1OUT |= BIT3;
            B[4] = 0;
        }
    }

    else if (led == 6)
    {
        if (i == 1)
        {
            P1OUT &= ~BIT2;
            P2OUT |= BIT3;
            A[2] = 1;
        }
        else
        {
            P2OUT &= ~BIT3;
            P1OUT |= BIT2;
            A[2] = 0;
        }
    }

    else if (led == 7)
    {
        if (i == 1)
        {
            P1OUT &= ~BIT1;
            P2OUT |= BIT3;
            B[1] = 1;
            A[3] = 1;
        }
        else
        {
            P1OUT |= BIT1;
            P2OUT &= ~BIT3;
            B[1] = 0;
            A[3] = 0;
        }
    }

    else if (led == 8)
    {
        if (i == 1)
        {
            P2OUT |= BIT4;
            P2OUT &= ~ BIT1;
            E[0] = 1;
        }
        else
        {
            P2OUT &= ~BIT4;
            P2OUT |= BIT1;
            E[0] = 0;
        }
    }

    else if (led == 9)
    {
        if (i == 1)
        {
            P2OUT |= BIT4;
            P2OUT &= ~ BIT0;
            A[0] = 1;
        }
        else
        {
            P2OUT |= BIT0;
            P2OUT &= ~BIT4;
            A[0] = 0;
        }
    }

    else if (led == 10)
    {
        if (i == 1)
        {
            P2OUT |= BIT4;
            P1OUT &= ~BIT5;
            A[5] = 1;
            E[1] = 1;
        }
        else
        {
            P1OUT |= BIT5;
            P2OUT &= ~BIT4;
            A[5] = 0;
            E[1] = 0;
        }
    }

    else if (led == 11)
    {
        if (i == 1)
        {
            P2OUT |= BIT4;
            P1OUT &= ~BIT4;
            B[3] = 1;
        }
        else
        {
            P1OUT |= BIT4;
            P2OUT &= ~BIT4;
            B[3] = 0;
        }
    }

    else if (led == 12)
    {
        if (i == 1)
        {
            P2OUT |= BIT4;
            P1OUT &= ~BIT3;
            A[4] = 1;
            B[0] = 1;
            E[2] = 1;
        }
        else
        {
            P1OUT |= BIT3;
            P2OUT &= ~BIT4;
            A[4] = 0;
            B[0] = 0;
            E[2] = 0;
        }
    }

    else if (led == 13)
    {
        if (i == 1)
        {
            P2OUT |= BIT4;
            P1OUT &= ~BIT2;
            A[1] = 1;
        }
        else
        {
            P1OUT |= BIT2;
            P2OUT &= ~BIT4;
            A[1] = 0;
        }
    }
}
void set0()
{
    volatile int i;
    for (i = 0; i < 6; i++)
    {
        A[i] = 0;
        B[i] = 0;
        E[i] = 0;
    }
}
void buzzer(int i)
{
    if (i == 1)
    {
        P2DIR |= BIT6;
        P2OUT |= BIT6;
    }
    else
    {
        P2OUT &= ~BIT6;
    }
}
void Start(void)
{

    int i, j;
    for (i = 0; i < 9; i++)
    {
        leds(r[i], 1);
        buzzer(1);
        __delay_cycles(200000);
        leds(r[i], 0);
        buzzer(0);
        __delay_cycles(200000);
    }
    for (i = 0; i < 100; i++)
    {
        buzzer(1);
        for (j = 0; j < 4; j++)
        {
            leds(b[j], 1);
            __delay_cycles(500);
            leds(b[j], 0);
        }
        buzzer(0);
    }
}
void disable()                                            //disable all the leds
{
    P2OUT &= ~(BIT3 + BIT4 + BIT2);
    P1OUT |= (BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);
    P2OUT |= (BIT0 + BIT1 + BIT5 + BIT7);
}
//    END
void End(void)
{
    int i, j;
    for (j = 0; j < 3; j++)
    {
        leds(5, 1);
        buzzer(1);
        __delay_cycles(100000);
        leds(5, 0);
        leds(1, 1);
        buzzer(0);
        __delay_cycles(100000);
        leds(1, 0);
        leds(10, 1);
        leds(4, 1);
        buzzer(1);
        __delay_cycles(50000);
        buzzer(0);
        __delay_cycles(50000);
        buzzer(1);
        leds(10, 0);
        leds(4, 0);
        for (i = 0; i < 9; i++)
            leds(r[i], 1);
        __delay_cycles(100000);
        for (i = 0; i < 9; i++)
            leds(r[i], 0);
        buzzer(0);
    }
}
void ranled(void)
{
    int l;
    a[0] = rand() % 13;
    if (a[0] < 0)
    {
        a[0] = -(a[0] * 1);
    }

    a[1] = rand() % 13;
    if (a[1] < 0)
    {
        a[1] = -(a[1] * 1);
    }
    while (a[1] == a[0])
    {
        a[1] = rand() % 13;
    }
    a[2] = rand() % 13;
    if (a[2] < 0)
    {
        a[2] = -(a[2] * 1);
    }
    while (a[2] == a[0] || a[2] == a[1])
    {
        a[2] = rand() % 13;
    }
    a[3] = rand() % 13;
    if (a[3] < 0)
    {
        a[3] = -(a[3] * 1);
    }
    while (a[3] == a[0] || a[3] == a[1] || a[3] == a[2])
    {
        a[3] = rand() % 13;
    }
    for (l = 0; l < 4; l++)
    {
        leds(a[l] + 1, 1);
        __delay_cycles(1);
        disable();
    }
}
void display_p()
{
    P2OUT &= ~BIT7;
    P1OUT &= ~(BIT1 + BIT2 + BIT5);
    P2OUT &= ~(BIT0 + BIT1);
}

void Clockwise_A()
{
    int k;
    int temp = A[5];
    for (k = 5; k > 0; k--)
        A[k] = A[k - 1];
    A[0] = temp;
    B[0] = A[4];
    B[1] = A[3];
    E[2] = A[4];
    E[1] = A[5];
}

void Clockwise_B()
{
    int k;
    int temp = B[5];
    for (k = 5; k > 0; k--)
        B[k] = B[k - 1];
    B[0] = temp;
    A[4] = B[0];
    A[3] = B[1];
    E[2] = B[0];
    E[3] = B[5];
}

void Clockwise_D()
{
    int k;
    int temp = E[5];
    for (k = 5; k > 0; k--)
        E[k] = E[k - 1];
    E[0] = temp;
    A[4] = E[2];
    A[5] = E[1];
    B[0] = E[2];
    B[5] = E[3];
}

//    ANTICLOCKWISE
void Anticlockwise_A()
{
    int k;
    int temp = A[0];
    for (k = 0; k < 5; k++)
        A[k] = A[k + 1];
    A[5] = temp;
    B[0] = A[4];
    B[1] = A[3];
    E[2] = A[4];
    E[1] = A[5];

}

void Anticlockwise_B()
{
    int k;
    int temp = B[0];
    for (k = 0; k < 5; k++)
        B[k] = B[k + 1];
    B[5] = temp;
    A[4] = B[0];
    A[3] = B[1];
    E[2] = B[0];
    E[3] = B[5];

}

void Anticlockwise_D()
{
    int k;
    int temp = E[0];
    for (k = 0; k < 5; k++)
        E[k] = E[k + 1];
    E[5] = temp;
    A[4] = E[2];
    A[5] = E[1];
    B[0] = E[2];
    B[5] = E[3];

}
void segment_print(int n)
{
    if (n == 0)
    {
        P1OUT &= ~(BIT1 + BIT2 + BIT3 + BIT4 + BIT5);
        P2OUT &= ~(BIT0);
        __delay_cycles(600);
    }
    else if (n == 1)
    {
        P1OUT &= ~(BIT2 + BIT3);
        __delay_cycles(200);
    }
    else if (n == 2)
    {
        P1OUT &= ~(BIT1 + BIT2 + BIT4 + BIT5);
        P2OUT &= ~(BIT1);
        __delay_cycles(600);
    }
    else if (n == 3)
    {
        P1OUT &= ~(BIT1 + BIT2 + BIT3 + BIT4);
        P2OUT &= ~(BIT1);
        __delay_cycles(600);
    }
    else if (n == 4)
    {
        P1OUT &= ~(BIT2 + BIT3);
        P2OUT &= ~(BIT0 + BIT1);
        __delay_cycles(600);
    }
    else if (n == 5)
    {
        P1OUT &= ~(BIT1 + BIT3 + BIT4);
        P2OUT &= ~(BIT0 + BIT1);
        __delay_cycles(600);
    }
    else if (n == 6)
    {
        P1OUT &= ~(BIT1 + BIT3 + BIT4 + BIT5);
        P2OUT &= ~(BIT0 + BIT1);
        __delay_cycles(600);
    }
    else if (n == 7)
    {
        P1OUT &= ~(BIT1 + BIT2 + BIT3);
        __delay_cycles(600);
    }
    else if (n == 8)
    {
        P1OUT &= ~(BIT1 + BIT2 + BIT3 + BIT4 + BIT5);
        P2OUT &= ~(BIT0 + BIT1);
        __delay_cycles(600);
    }
    else if (n == 9)
    {
        P1OUT &= ~(BIT1 + BIT2 + BIT3);
        P2OUT &= ~(BIT0 + BIT1);
        __delay_cycles(600);
    }
    disable();
}
void points(int p)               //function to display the points on the segment
{
    int i;
    pt[0] = p / 10;
    pt[1] = p % 10;
    for (i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            P1OUT &= ~ BIT6;
        }
        else
            P2OUT &= ~ BIT5;

        switch (pt[i])
        {
        case 0:
            segment_print(0);
            break;
        case 1:
            segment_print(1);
            break;
        case 2:
            segment_print(2);
            break;
        case 3:
            segment_print(3);
            break;
        case 4:
            segment_print(4);
            break;
        case 5:
            segment_print(5);
            break;
        case 6:
            segment_print(6);
            break;
        case 7:
            segment_print(7);
            break;
        case 8:
            segment_print(8);
            break;
        case 9:
            segment_print(9);
            break;
        }
    }
}
void compare(void)
{
    while (1)
    {
        if (p1point > p2point)
        {
            P2OUT &= ~BIT7;
            P2OUT &= ~BIT1;
            __delay_cycles(300);
            disable();
            P1OUT &= ~BIT7;
            P1OUT &= ~(BIT1 + BIT2 + BIT5);
            P2OUT &= ~(BIT0 + BIT1);
            __delay_cycles(300);
            disable();
            P1OUT &= ~BIT6;
            P1OUT &= ~(BIT2 + BIT3);
            __delay_cycles(300);
            disable();
            P2OUT &= ~BIT5;
            P2OUT &= ~BIT1;
            __delay_cycles(300);
            disable();
            //P1 WINS
        }

        if (p1point < p2point)
        {
            P2OUT &= ~BIT7;
            P2OUT &= ~BIT1;
            __delay_cycles(300);
            disable();
            __delay_cycles(50);
            P1OUT &= ~BIT7;
            P1OUT &= ~(BIT1 + BIT2 + BIT5);
            P2OUT &= ~(BIT0 + BIT1);
            __delay_cycles(300);
            disable();
            __delay_cycles(50);
            P1OUT &= ~BIT6;
            P1OUT &= ~(BIT1 + BIT2 + BIT4 + BIT5);
            P2OUT &= ~(BIT1);
            __delay_cycles(300);
            disable();
            __delay_cycles(50);
            P2OUT &= ~BIT5;
            P2OUT &= ~BIT1;
            __delay_cycles(300);
            disable();
            __delay_cycles(50);
        }

        if (p1point == p2point)
        {
            P2OUT &= ~BIT7;
            P1OUT &= ~(BIT1 + BIT2 + BIT5);
            P2OUT &= ~(BIT0 + BIT1);
            __delay_cycles(300);
            disable();
            __delay_cycles(50);
            P1OUT &= ~BIT7;
            P1OUT &= ~(BIT2 + BIT3);
            __delay_cycles(150);
            disable();
            __delay_cycles(50);
            P1OUT &= ~BIT6;
            P1OUT &= ~(BIT1 + BIT2 + BIT5);
            P2OUT &= ~(BIT0 + BIT1);
            __delay_cycles(300);
            disable();
            __delay_cycles(50);
            P2OUT &= ~BIT5;
            P1OUT &= ~(BIT1 + BIT2 + BIT4 + BIT5);
            P2OUT &= ~(BIT1);
            __delay_cycles(300);
            disable();
            __delay_cycles(50);
        }
    }
}
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    P1DIR |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);
    P2DIR |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);
    P2OUT |= BIT2;
    P2SEL &= ~(BIT6 + BIT7);
    P2SEL2 &= ~(BIT6 + BIT7);
    Start();
    P2OUT &= ~BIT6;
    set0();
    ranled();
    disable();
    poin = 20;
    ADC10CTL0 &= ~ENC;
    ADC10CTL0 |= SREF_0 + ADC10ON;
    ADC10CTL0 |= ADC10IE;
    ADC10CTL1 |= INCH_0 + ADC10SSEL_3 + ADC10DIV_7;
    __bis_SR_register(GIE);
    ADC10AE0 |= BIT0;
    TA0CTL |= TASSEL_2;             //SMCLK
    TA0CTL |= MC_1;                 //UP MODE
    TA0CCR0 = 18000;                //VALUE
    TA0CTL |= TACLR;
    TA0CCTL0 |= CCIE;               //ENABLES INTERRUPT
    while (1)
    {
        if (player % 2 == 1)
        {
            if (p1flag != 1 && p1flag != 2)
            {
                if (A[3] == 1 && A[4] == 1 && A[5] == 1 && B[5] == 1)
                    p1flag = 1;
                else if (poin == 0)
                    p1flag = 2;
                if (!(ADC10CTL1 & ADC10BUSY))
                    ADC10CTL0 |= ENC + ADC10SC;
                anl = ADC10MEM;
            }
            else
            {
                p1point = poin;
                set0();
                ranled();
                disable();
                poin = 20;
                player += 1;
            }
        }
        else
        {
            if (p2flag != 1 && p2flag != 2)
            {
                if (A[3] == 1 && A[4] == 1 && A[5] == 1 && B[5] == 1)
                    p2flag = 1;
                else if (poin == 0)
                    p2flag = 2;
                if (!(ADC10CTL1 & ADC10BUSY))
                    ADC10CTL0 |= ENC + ADC10SC;
                anl = ADC10MEM;
            }
            else
            {
                p2point = poin;
                TA0CTL |= TACLR;
                TA0CCTL0 &= ~CCIE;
                End();
                compare();
            }
        }
    }
}
#pragma vector = TIMER0_A0_VECTOR
__interrupt
void TA0CCR0_ISR(void)
{
    display_p();
    __delay_cycles(600);
    disable();
    P1OUT &= ~(BIT7);                                       //segment2-on
    if (player % 2 == 0)
    {
        segment_print(2);
    }
    else
    {
        segment_print(1);
    }
    P1OUT |= BIT6;
    P2OUT |= BIT5 + BIT7 + BIT2;
    disable();
    points(poin);
    disable();
    volatile int i, j, k;
    for (i = 0, j = 6; i < 6; i++, j++)
    {
        leds(A[j], A[i]);
        __delay_cycles(600);
        disable();
        leds(B[j], B[i]);
        __delay_cycles(600);
        disable();
        leds(E[j], E[i]);
        __delay_cycles(600);
        disable();
    }

}
#pragma vector = ADC10_VECTOR
__interrupt
void adcds(void)
{
    if (anl > 1000)
    {
        debounce++;
    }
    if (debounce > 10)
    {
        if (anl >= 0 && anl <= 10)                     //SW 1 PRESSED (0)
        {
            Anticlockwise_D();
            poin -= 1;
            debounce = 0;
        }
        else if (anl >= 150 && anl <= 200)             //SW 2 PRESSED (175)
        {
            Anticlockwise_A();
            poin -= 1;
            debounce = 0;
        }
        else if (anl >= 300 && anl <= 400)            //SW 3 PRESSED (350)
        {
            Clockwise_B();
            poin -= 1;
            debounce = 0;
        }
        else if (anl >= 720 && anl <= 800)             //SW 4 PRESSED (767)
        {
            Anticlockwise_B();
            poin -= 1;
            debounce = 0;
        }
        else if (anl >= 820 && anl <= 890)             //SW 5 PRESSED (856)
        {
            Clockwise_A();
            poin -= 1;
            debounce = 0;
        }
        else if (anl >= 900 && anl <= 980)             //SW 6 PRESSED (937)
        {
            Clockwise_D();
            poin -= 1;
            debounce = 0;
        }
        else
        {
            debounce++;
        }
    }
}

