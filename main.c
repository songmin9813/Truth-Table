#include <stdio.h>
#include <Windows.h>
#include <math.h>
/*
20164043 한성민
본 프로그램은 입력받은 합성 명제에 따른 진리표를 출력하는 프로그램입니다.
*/
int andAri(int a, int b);//and연산입니다.
int orAri(int a, int b);//or연산입니다.
int notAri(int a);//not연산입니다.
int impAri(int a, int b);//imp연산입니다.
int opedTrans(int opedStack[], int p, int q, int r);//P,Q,R값을 정해진 참/거짓 값으로 바꾸어주는 함수입니다.
char trans(int a);//정수를 정해진 T/F값으로 바꿔주는 함수입니다.
void push(int stack[],int tmp);//스택의 push를 담당합니다.
int pop(int stack[]);//스택의 pop을 담당합니다.
int seek(int stack[]);//스택의 seek함수입니다.
int judge(int opedStack[], int op, int a, int b);//연산자와 피연산자를 기준으로 어떤 연산을 할지 판단하는 함수입니다.
void opPrint(int a);//진리표를 만들기 위해 필요한 연산자 출력함수입니다.
int main()
{
	char text[50] = {0 };//입력받을 텍스트
	int tmp[50] = { 0 };//스택 배열
	int exQ = 0, exR = 0, exP = 0, P, Q, R;
	int opStack[50] = { 0 };//연산자 스택 배열
	int opedStack[50] = { 0, };//피연산자 스택 배열
	int i,z=0,j=0,temp,sum=0,temp1,oped1,oped2;
	printf("진리표를 구하는 프로그램입니다!\n");
	printf("작성되는 진리표는 명제 P,Q,R로 최대 3개를 작성할 수 있습니다.\n");
	printf("논리 연산자는 and, or, not, imp로 총 4개로 된 영단어를 사용할 수 있습니다.\n\n\n");
	printf("연산의 우선순위는 기본적인 순서에 따라 not>and>or>imp 순으로 진행됩니다.\n");
	printf("합성 명제를 입력해주세요.(연산 사이에 띄어쓰기는 반드시 해주세요!!)\n");
	printf("-->");
	gets(text);
	for (i = 0; text[i] != '\0'; i++)
	{
		if (text[i] == 'a')//and는 편의상 3으로 관리합니다.
		{
			tmp[z] = 3;
			z++;
			i += 2;
		}
		else if (text[i] == 'o')//or은 편의상 4로 관리합니다.
		{
			tmp[z] = 4;
			z++;
			i += 1;
		}
		else if (text[i] == 'n')//not은 편의상 2로 관리합니다.
		{
			tmp[z] = 2;
			z++;
			i += 2;
		}
		else if (text[i] == 'i')//imp는 편의상 5로 관리합니다.
		{
			tmp[z] = 5;
			z++;
			i += 2;
		}
		else if (text[i] == 'p' || text[i] == 'P')//편의상 모든 문자는 아스키코드값으로 관리합니다.
		{
			exP = 1;
			tmp[z] = 80;
			z++;
		}
		else if (text[i] == 'q' || text[i] == 'Q')
		{
			exQ = 1;
			tmp[z] = 81;
			z++;
		}
		else if (text[i] == 'r' || text[i] == 'R')
		{
			exR = 1;
			tmp[z] = 82;
			z++;
		}
		else if (text[i] == ' ')
			continue;
		else
		{
			printf("무언가가 잘못된 입력! 프로그램을 종료합니다.\n");
			return 0;
		}
	}
	system("cls");
	printf("%s\n연산을 시작합니다.\n| ",text);
	if (exP == 1)
	{
		printf("P ");
	}
	if (exQ == 1)
	{
		printf("Q ");
	}
	if (exR == 1)
	{
		printf("R ");
	}
	printf("|");

	//여기부터는 표에 맞는 적절한 연산을 출력하는 과정입니다.
	for (i = 0; tmp[i] != 0; i++)
	{
		if (tmp[i] >= 2 && tmp[i] <= 5)//연산자를 입력받았을 경우
		{
			if (opStack[0] != 0)//스택에 이미 연산자가 있을 경우
			{
				if (seek(opStack) > tmp[i])//들어가려는 연산자의 우선순위가 높을 경우
					push(opStack, tmp[i]);
				else//스택의 연산자 우선순위가 높을 경우
				{
					while (tmp[i] >= seek(opStack) && seek(opStack))
						opPrint(pop(opStack));
					push(opStack, tmp[i]);
				}
			}
			else//연산자가 없을 경우
				push(opStack, tmp[i]);
		}
		else//피연산자를 입력받았을 경우
			continue;
	}
	while(seek(opStack)!=0)
		opPrint(pop(opStack));
	printf("\n");

	//여기부터는 실제 연산에 들어가는 작업입니다.
		for (z = 0; z < (int)pow(2, exP + exQ + exR); z++)//참은 7, 거짓은 6입니다.
		{
			temp = z;
			printf("| ");
			for (j = exP + exQ + exR - 1; j >= 0; j--)
				printf("%c ", trans(((temp >> j) & 1)+6));
			printf("|");
			for (i = 0; tmp[i] != 0; i++)
			{
				temp = z;
				if (exR == 1)//피연산자를 표에 맞는 T/F값으로 맞춰줍니다.
				{
					R = (temp & 1) + 6;
					temp = temp >> 1;
				}
				if (exQ == 1)
				{
					Q = (temp & 1) + 6;
					temp = temp >> 1;
				}
				if (exP == 1)
				{
					P = (temp & 1) + 6;
					temp = temp >> 1;
				}
				if (tmp[i] >= 2 && tmp[i] <= 5)//연산자를 입력받았을 경우
				{
					if (opStack[0] != 0)//스택에 이미 연산자가 있을 경우
					{//두 연산자의 우선순위를 비교합니다.
						if (seek(opStack) > tmp[i])//들어가려는 연산자의 우선순위가 높을 경우
							push(opStack, tmp[i]);
						else//스택의 우선순위가 높거나 같을 경우
						{//기본적으로 왼쪽 결합 법칙으로 적용합니다.
							while (tmp[i] >= seek(opStack) && seek(opStack))//연산자 스택에 temp1값을 넣을 수 있을 때까지 루프문이 돕니다.
							{
								oped1 = opedTrans(opedStack, P, Q, R);//피연산자를 표에 맞는 T/F값으로 변환시켜줍니다.
								oped2 = opedTrans(opedStack, P, Q, R);
								temp = judge(opedStack, pop(opStack), oped1, oped2);
								printf(" %c |", trans(temp));
								push(opedStack, temp);
							}
							push(opStack, tmp[i]);
						}
					}
					else//스택에 연산자가 없을 경우
						push(opStack, tmp[i]);
				}
				else//피연산자를 입력받았을 경우
					push(opedStack, tmp[i]);
			}
			while (opStack[0] != 0)
			{
				oped1 = opedTrans(opedStack, P, Q, R);//피연산자를 표에 맞는 T/F값으로 변환시켜줍니다.
				oped2 = opedTrans(opedStack, P, Q, R);
				temp = judge(opedStack, pop(opStack), oped1, oped2);
				printf(" %c |", trans(temp));
				push(opedStack, temp);
			}
			pop(opedStack);
			printf("\n");
		}
}
int seek(int stack[])//스택의 seek함수입니다.
{
	int i = 0;
	while (stack[i] != 0)
		i++;
	if (i == 0)
		return stack[0];
	else
		return stack[i - 1];
}
void push(int stack[], int tmp)//스택의 push를 담당합니다.
{
	int i = 0;
	while (stack[i] != 0)
		i++;
	stack[i] = tmp;
}
int pop(int stack[])//스택의 pop을 담당합니다.
{
	int i = 0, tmp;
	while (stack[i] != 0)
		i++;
	if (i == 0)
		return stack[i];
	tmp = stack[i - 1];
	stack[i - 1] = 0;
	return tmp;
}
int opedTrans(int opedStack[], int p, int q, int r)//P,Q,R값을 정해진 참/거짓 값으로 바꾸어주는 함수입니다.
{
	int tmp = pop(opedStack);
	if (tmp == 80)
		return p;
	else if (tmp == 81)
		return q;
	else if (tmp == 82)
		return r;
}
char trans(int a)//정수를 정해진 T/F값으로 바꿔주는 함수입니다.
{
	if (a == 7)
		return 'T';
	else
		return 'F';
}
int judge(int opedStack[], int op, int a, int b)//연산자와 피연산자를 기준으로 어떤 연산을 할지 판단하는 함수입니다.
{
	if (op == 2)//not은 단항 연산자입니다.
	{
		push(opedStack, b);
		return notAri(a);
	}
	else if (op == 3)
		return andAri(a, b);
	else if (op == 4)
		return orAri(a, b);
	else
		return impAri(a, b);
}
int impAri(int a, int b)//imp연산입니다.
{
	if (a == 6 && b == 7)
		return 6;
	else
		return 7;
}
int notAri(int a)//not연산입니다.
{
	if (a == 7)
		return 6;
	else
		return 7;
}
int orAri(int a, int b)//or연산입니다.
{
	if (a == 6 && b == 6)
		return 6;
	else
		return 7;
}
int andAri(int a, int b)//and연산입니다.
{
	if (a == 7 && b == 7)
		return 7;
	else
		return 6;
}
void opPrint(int a)//진리표를 만들기 위해 필요한 연산자 출력함수입니다.
{
	if (a == 2)
		printf("not|");
	else if (a == 3)
		printf("and|");
	else if (a == 4)
		printf(" or|");
	else
		printf("imp|");
}