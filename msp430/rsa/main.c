//https://proprogramming.org/program-to-implement-rsa-algorithm-in-c/


//#define DEBUG 1

#include <msp430.h>
#include <stdlib.h>
#include <math.h>

#ifdef DEBUG
#include <uart-debugger.h>   // to get the UART library go to https://github.com/amjadmajid/uart-debugger-repo
#endif


#define MSG "hello"
#define MSG_LEN 5

long int p,q,n,t,flag,e[50],d[50],temp[50],j,m[50],en[50],i;

char * msg = MSG;

int prime( long int);
void ce();
long int cd( long int);

void encrypt();
void decrypt();

int main()
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;
#ifdef DEBUG
    uart_init();
#endif

    // first prime number
    p =  941;
    flag=prime(p);
    if(flag==0)
    {
#ifdef DEBUG
     uart_sendText("Error 1\n\r", 9);
#endif
        while(1);
    }

    // second prime number
    q = 13;
    flag=prime(q);
    if(flag==0||p==q)
    {
#ifdef DEBUG
     uart_sendText("Error 2\n\r", 9);
#endif
        while(1);
    }

    // plain text message
    for(i=0; i < MSG_LEN  ;i++)
    {
        // hardware multiplier
        m[i]= *(msg+i);
#ifdef DEBUG
        uart_sendChar(*msg);
#endif
    }

#ifdef DEBUG
     uart_sendText("\n\r", 2);
#endif

    n = p * q ;
    t = (p-1) * (q-1);

    ce();
    encrypt();
    decrypt();

    __no_operation();

    while(1);

    return 0;
}

// check if the number is prime
int prime(long int pr)
{
    int i;
    j=sqrt(pr);
    for(i=2;i<=j;i++)
    {
        if(pr%i==0)
            return 0;
    }
    return 1;
}
void ce()
{
    int k;
    k=0;
    for(i=2;i<t;i++)
    {
        if(t%i==0)
            continue;

        flag=prime(i);

        if(flag==1&&i!=p&&i!=q)
        {
            e[k]=i; flag=cd(e[k]);
            if(flag>0)
            {
                d[k]=flag;
                k++;
            }
            if(k==49)
                break;
        }
    }
}

long int cd(long int x)
{
    long int k=1;
    while(1)
    {
        k=k+t;
        if(k%x==0)
            return(k/x);
    }
}
void encrypt()
{
    long int pt,ct,key=e[0],k,len;
    i=0;
    len=strlen(msg);
    while(i!=len)
    {
        pt=m[i];
        pt=pt-96;
        k=1;
        for(j=0;j<key;j++)
        {
            k=k*pt;
            k=k%n;
        }
        temp[i]=k;
        ct=k+96;
        en[i]=ct;
        i++;
    }
    en[i]=-1;

#ifdef DEBUG
    uart_sendText("THE_ENCRYPTED_MESSAGE_IS\n\r", 26);
     for(i=0;en[i]!=-1;i++){
         uart_sendChar(en[i]);
     }
     uart_sendText("\n\r", 2);
#endif

}
void decrypt()
{
    long int pt,ct,key=d[0],k;
      i=0;
      while(en[i]!=-1)
      {
          ct=temp[i];
          k=1;
          for(j=0;j<key;j++)
          {
              k=k*ct;
              k=k%n;
          }
          pt=k+96;
          m[i]=pt;
          i++;
      }
      m[i]=-1;

#ifdef DEBUG

    uart_sendText("THE_DECRYPTED_MESSAGE_IS\n\r", 26);
     for(i=0;i < MSG_LEN ;i++){
         uart_sendChar(m[i]);
     }
    uart_sendText("\n\r", 2);

#endif
}
