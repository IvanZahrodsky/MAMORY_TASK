#ifndef _TASK_H_
#define _TASK_H_

#include <iostream>
#include <memory.h>
#include <malloc.h>
#include <stdio.h>

using namespace std;
typedef unsigned char UC;
typedef unsigned int UI;

#define COUNT_CAR 22
#define MAX_COLOR 0x00FFFFFF
#define MAX_DATE 2012
#define MAX_KM 0x000FFFFF
enum car_brand
{
  BMW,
  AUDI,
  MERCEDES,
  TOYOTA,
  MITSUBISHI,
  CHEVROLET,
  ASTON_MARTIN,
  OPEL,
  FORD,
  FIAT,
  PORSCHE,
  VOLKSWAGEN,
  ALFA_ROMEO,
  FERRARI,
  MASERATI,
  LAMBORGHINI,
  DAEWOO,
  HONDA,
  LEXUS,
  MAZDA,
  NISSAN,
  SUBARU
};
const char *CBRAND[] = {
                      "BMW",
                      "AUDI",
                      "MERCEDES",
                      "TOYOTA",
                      "MITSUBISHI",
                      "CHEVROLET",
                      "ASTON_MARTIN",
                      "OPEL",
                      "FORD",
                      "FIAT",
                      "PORSCHE",
                      "VOLKSWAGEN",
                      "ALFA_ROMEO",
                      "FERRARI",
                      "MASERATI",
                      "LAMBORGHINI",
                      "DAEWOO",
                      "HONDA",
                      "LEXUS",
                      "MAZDA",
                      "NISSAN",
                      "SUBARU"
                };


struct RGB
{
    UC R;
    UC G;
    UC B;
};


struct S
{
  UC sname[16];
  car_brand brand;
  RGB color;
  UI date : 12;
  UI km : 20;

};

struct my_list
{
    S data;
    my_list *next;
};


void add1( my_list *&ptr , S dat , UI &count )
{
    my_list *temp;
    temp = (my_list * ) malloc ( sizeof(my_list));
    if ( temp == NULL )
    {
        cout << "Error in adding element! Memory out!\n";
        return;
    }
    if ( ptr ==  NULL )
    {
        temp -> next = NULL;
        temp -> data = dat;
        ptr = temp;
        ++count;
        cout << "\nElement added!\n";
        return;
    }
    temp -> next = ptr;
    temp -> data = dat;
    ptr = temp;
    ++count;
	cout << "\nElement added!\n";
}

void add2( my_list *&ptr , S dat, UI& count )
{
	my_list *temp;
    temp = (my_list * ) malloc ( (count+1) * sizeof(my_list));
	if ( temp == NULL )
	{
		cout << "Error in adding element! Memory out!\n";
        return;
	}
	memcpy ( temp , &dat, sizeof(S));
	memcpy ( temp + 1 , ptr , count * sizeof(my_list) );
	if ( count > 1 )
	{
		temp[0].next = &temp[1];
	}
	else
	{
		temp[0].next = NULL;
	}
	++count;
	cout << "\nElement added!\n";

}

void PrintList ( my_list *ptr , UI count )
{
    if ( count == 0 )
    {
        cout << "List is empty\n";
		return;
    }
    cout << "\nLIST:\n\n";
    UI temp;
    while ( ptr != NULL )
    {
        temp = 0;
        memcpy(&temp,&ptr -> data.color,3);
        cout << dec << ptr -> data.sname << "\t" << CBRAND[ ptr -> data.brand] << "\t" << temp <<"\t" << ptr -> data.date << "\t" << ptr->data.km ;
        cout << "  Next adress  -  " << hex << "0x" << (int) ptr -> next << endl;
        ptr = ptr -> next;
    }
}

void Delete1( my_list *& ptr )
{
    if(!ptr)
	{
		cout << "\nList is empty!\n";
        return;
	}
    my_list *temp;
    while( ptr )
    {
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
	cout << "\nList is deleted!\n";
}

void Delete2( my_list *& ptr )
{
    if(!ptr)
	{
		cout << "\nList is empty!\n";
        return;
	}
    delete[] ptr;
	cout << "\nList is deleted!\n";
}

void Delete ( my_list *&ptr , bool& flag)
{
	!flag ? Delete1(ptr) : Delete2(ptr);
	flag = false;
}
my_list* Konvert( my_list*& ptr , UI count , bool& flag)
{
	if ( !flag )
	{
		return ptr;
	}
    my_list *temp;
	my_list *oldptr = ptr;
    temp = (my_list *) malloc ( count * sizeof(my_list) );
    if ( temp == NULL )
    {
        cout << "Error in Konvert! Memory out";
        return ptr;
    }
    UI i = 0;
    while ( oldptr != NULL)
    {
		memcpy ( temp + i , oldptr, sizeof(my_list));
        if ( i < count - 1 )
            temp [ i ] .next = & temp[ i+1 ];
        ++i;
        oldptr = oldptr -> next;
    }
    temp [ count - 1 ] .next = NULL;
	Delete1 ( ptr );
	flag = true;
	 cout << "\nConvertation is OK!\n";
    return temp;
}

my_list* DeKonvert( my_list*& ptr , UI count , bool flag)
{
	if ( flag )
	{
		return ptr;
	}
    my_list *temp = NULL, *temp1;
	my_list *temp2 = NULL;
    for ( UI i = 0; i < count ; i++ )
	{
			temp1 = (my_list * ) malloc ( sizeof(my_list));
			if ( temp1 == NULL )
			{
				cout << "Error in DeKonvert! Memory out!\n";
				Delete1 ( temp );
				return ptr;
			}
			if ( temp ==  NULL )
			{
				memcpy ( temp1, ptr + i,sizeof(my_list));
				temp1 -> next = NULL;
				temp = temp2 = temp1;
				continue;
			}
			memcpy ( temp1, ptr + i,sizeof(my_list));
			temp2 -> next = temp1;
			temp2 = temp1;
	}
	cout << "\nDeConvertation is OK!\n";
    return temp;
}

void Add ( my_list *&ptr , bool flag , UI &count )
{
    S tmp;
    UI temp;
    cout << "\nEnter data:\n\n";
    cout << "Surname :  ";
    cin >> tmp.sname;
    fflush(stdin);
    if(cin.fail())
    {
        cout << "\nEror in entering! Data not recorded!\n";
        cin.clear();
        return;
    }
    cout << "Chose brand of car :  ";
    cin >> temp;
    fflush(stdin);
    if(cin.fail() || ( temp > COUNT_CAR - 1  ) )
    {
        cout << "\nEror in entering! Data not recorded!\n";
        cin.clear();
        return;
    }
    memcpy (&tmp.brand,&temp,4);
    cout << "Color ( Number (RGB) ) :  ";
    cin >> temp;
    fflush(stdin);
    if(cin.fail() || ( temp > MAX_COLOR ) )
    {
        cout << "\nEror in entering! Data not recorded!\n";
        cin.clear();
        return;
    }
    memcpy (&tmp.color,&temp,3);
    cout << "Date :  ";
    cin >> temp;
    fflush(stdin);
    if(cin.fail() || ( temp > MAX_DATE ))
    {
        cout << "\nEror in entering! Data not recorded!\n";
        return;
    }
    tmp.date = temp;
    cout << "KM :  ";
    cin >> temp;
    fflush(stdin);
    if(cin.fail() || ( temp > MAX_KM ))
    {
        cout << "\nEror in entering! Data not recorded!\n";
        return;
    }
    tmp.km = temp;
    !flag ? add1 ( ptr,tmp,count ) : add2 ( ptr,tmp,count );
}
inline void Help ( void )
{
	cout << " \nPlease choose an action:\n\
			1 - Add element\n\
			2 - Delete list\n\
			3 - Convert\n\
			4 - DeConvert\n\
			5 - Check the convert status\n\
			6 - Print list\n\
			7 - Print list brand of car\n\
			8 - PrintHelp\n\
			9 - Exit\n";
}

inline void PrintBrandCar ()
{
	cout << "\nNumber:\t\tBrand\n";
	for ( UC i = 0 ; i < COUNT_CAR ; i++ )
	{
		cout << i << "\t\t" << CBRAND [i] << endl;
	}
}
inline void Check ( bool flag )
{
	if ( flag )
	{
		cout << "\nList is compressed\n";
	}
	else
	{
		cout << "\nList is NOT compressed\n";
	}
}
int Run ( void )
{
	UC choice;
	bool pack = false;
    UI count = 0;
    my_list  *nd = NULL;
	Help();
	while ( true )
	{
		cout << " \nPlease choose an action:\n";
		cin >> choice;
		fflush (stdin);
		if ( cin.fail() || ( choice > '8' ) || choice == '0' )
		{
			cout << "\nError!\n";
			continue;
		}
		switch ( choice )
		{
			case '1':
				Add ( nd, pack, count );
				continue;
			case '2':
				Delete ( nd, pack );
				continue;
			case '3':
				nd = Konvert ( nd , count , pack );
				continue;
			case '4':
				nd = DeKonvert ( nd, count , pack );
				continue;
			case '5':
				Check(pack);
				continue;
			case '6':
				PrintList ( nd, count );
				continue;
			case '7':
				PrintBrandCar();
				continue;
			case '8':
				Help();
				continue;
			case '9':
				Delete ( nd, pack );
				return 0;
		}
	}
	return 0;
}
#endif // _TASK_H_
