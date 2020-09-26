#include <stdio.h>
#include <Windows.h>
#include <math.h>
/*
20164043 �Ѽ���
�� ���α׷��� �Է¹��� �ռ� ������ ���� ����ǥ�� ����ϴ� ���α׷��Դϴ�.
*/
int andAri(int a, int b);//and�����Դϴ�.
int orAri(int a, int b);//or�����Դϴ�.
int notAri(int a);//not�����Դϴ�.
int impAri(int a, int b);//imp�����Դϴ�.
int opedTrans(int opedStack[], int p, int q, int r);//P,Q,R���� ������ ��/���� ������ �ٲپ��ִ� �Լ��Դϴ�.
char trans(int a);//������ ������ T/F������ �ٲ��ִ� �Լ��Դϴ�.
void push(int stack[],int tmp);//������ push�� ����մϴ�.
int pop(int stack[]);//������ pop�� ����մϴ�.
int seek(int stack[]);//������ seek�Լ��Դϴ�.
int judge(int opedStack[], int op, int a, int b);//�����ڿ� �ǿ����ڸ� �������� � ������ ���� �Ǵ��ϴ� �Լ��Դϴ�.
void opPrint(int a);//����ǥ�� ����� ���� �ʿ��� ������ ����Լ��Դϴ�.
int main()
{
	char text[50] = {0 };//�Է¹��� �ؽ�Ʈ
	int tmp[50] = { 0 };//���� �迭
	int exQ = 0, exR = 0, exP = 0, P, Q, R;
	int opStack[50] = { 0 };//������ ���� �迭
	int opedStack[50] = { 0, };//�ǿ����� ���� �迭
	int i,z=0,j=0,temp,sum=0,temp1,oped1,oped2;
	printf("����ǥ�� ���ϴ� ���α׷��Դϴ�!\n");
	printf("�ۼ��Ǵ� ����ǥ�� ���� P,Q,R�� �ִ� 3���� �ۼ��� �� �ֽ��ϴ�.\n");
	printf("�� �����ڴ� and, or, not, imp�� �� 4���� �� ���ܾ ����� �� �ֽ��ϴ�.\n\n\n");
	printf("������ �켱������ �⺻���� ������ ���� not>and>or>imp ������ ����˴ϴ�.\n");
	printf("�ռ� ������ �Է����ּ���.(���� ���̿� ����� �ݵ�� ���ּ���!!)\n");
	printf("-->");
	gets(text);
	for (i = 0; text[i] != '\0'; i++)
	{
		if (text[i] == 'a')//and�� ���ǻ� 3���� �����մϴ�.
		{
			tmp[z] = 3;
			z++;
			i += 2;
		}
		else if (text[i] == 'o')//or�� ���ǻ� 4�� �����մϴ�.
		{
			tmp[z] = 4;
			z++;
			i += 1;
		}
		else if (text[i] == 'n')//not�� ���ǻ� 2�� �����մϴ�.
		{
			tmp[z] = 2;
			z++;
			i += 2;
		}
		else if (text[i] == 'i')//imp�� ���ǻ� 5�� �����մϴ�.
		{
			tmp[z] = 5;
			z++;
			i += 2;
		}
		else if (text[i] == 'p' || text[i] == 'P')//���ǻ� ��� ���ڴ� �ƽ�Ű�ڵ尪���� �����մϴ�.
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
			printf("���𰡰� �߸��� �Է�! ���α׷��� �����մϴ�.\n");
			return 0;
		}
	}
	system("cls");
	printf("%s\n������ �����մϴ�.\n| ",text);
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

	//������ʹ� ǥ�� �´� ������ ������ ����ϴ� �����Դϴ�.
	for (i = 0; tmp[i] != 0; i++)
	{
		if (tmp[i] >= 2 && tmp[i] <= 5)//�����ڸ� �Է¹޾��� ���
		{
			if (opStack[0] != 0)//���ÿ� �̹� �����ڰ� ���� ���
			{
				if (seek(opStack) > tmp[i])//������ �������� �켱������ ���� ���
					push(opStack, tmp[i]);
				else//������ ������ �켱������ ���� ���
				{
					while (tmp[i] >= seek(opStack) && seek(opStack))
						opPrint(pop(opStack));
					push(opStack, tmp[i]);
				}
			}
			else//�����ڰ� ���� ���
				push(opStack, tmp[i]);
		}
		else//�ǿ����ڸ� �Է¹޾��� ���
			continue;
	}
	while(seek(opStack)!=0)
		opPrint(pop(opStack));
	printf("\n");

	//������ʹ� ���� ���꿡 ���� �۾��Դϴ�.
		for (z = 0; z < (int)pow(2, exP + exQ + exR); z++)//���� 7, ������ 6�Դϴ�.
		{
			temp = z;
			printf("| ");
			for (j = exP + exQ + exR - 1; j >= 0; j--)
				printf("%c ", trans(((temp >> j) & 1)+6));
			printf("|");
			for (i = 0; tmp[i] != 0; i++)
			{
				temp = z;
				if (exR == 1)//�ǿ����ڸ� ǥ�� �´� T/F������ �����ݴϴ�.
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
				if (tmp[i] >= 2 && tmp[i] <= 5)//�����ڸ� �Է¹޾��� ���
				{
					if (opStack[0] != 0)//���ÿ� �̹� �����ڰ� ���� ���
					{//�� �������� �켱������ ���մϴ�.
						if (seek(opStack) > tmp[i])//������ �������� �켱������ ���� ���
							push(opStack, tmp[i]);
						else//������ �켱������ ���ų� ���� ���
						{//�⺻������ ���� ���� ��Ģ���� �����մϴ�.
							while (tmp[i] >= seek(opStack) && seek(opStack))//������ ���ÿ� temp1���� ���� �� ���� ������ �������� ���ϴ�.
							{
								oped1 = opedTrans(opedStack, P, Q, R);//�ǿ����ڸ� ǥ�� �´� T/F������ ��ȯ�����ݴϴ�.
								oped2 = opedTrans(opedStack, P, Q, R);
								temp = judge(opedStack, pop(opStack), oped1, oped2);
								printf(" %c |", trans(temp));
								push(opedStack, temp);
							}
							push(opStack, tmp[i]);
						}
					}
					else//���ÿ� �����ڰ� ���� ���
						push(opStack, tmp[i]);
				}
				else//�ǿ����ڸ� �Է¹޾��� ���
					push(opedStack, tmp[i]);
			}
			while (opStack[0] != 0)
			{
				oped1 = opedTrans(opedStack, P, Q, R);//�ǿ����ڸ� ǥ�� �´� T/F������ ��ȯ�����ݴϴ�.
				oped2 = opedTrans(opedStack, P, Q, R);
				temp = judge(opedStack, pop(opStack), oped1, oped2);
				printf(" %c |", trans(temp));
				push(opedStack, temp);
			}
			pop(opedStack);
			printf("\n");
		}
}
int seek(int stack[])//������ seek�Լ��Դϴ�.
{
	int i = 0;
	while (stack[i] != 0)
		i++;
	if (i == 0)
		return stack[0];
	else
		return stack[i - 1];
}
void push(int stack[], int tmp)//������ push�� ����մϴ�.
{
	int i = 0;
	while (stack[i] != 0)
		i++;
	stack[i] = tmp;
}
int pop(int stack[])//������ pop�� ����մϴ�.
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
int opedTrans(int opedStack[], int p, int q, int r)//P,Q,R���� ������ ��/���� ������ �ٲپ��ִ� �Լ��Դϴ�.
{
	int tmp = pop(opedStack);
	if (tmp == 80)
		return p;
	else if (tmp == 81)
		return q;
	else if (tmp == 82)
		return r;
}
char trans(int a)//������ ������ T/F������ �ٲ��ִ� �Լ��Դϴ�.
{
	if (a == 7)
		return 'T';
	else
		return 'F';
}
int judge(int opedStack[], int op, int a, int b)//�����ڿ� �ǿ����ڸ� �������� � ������ ���� �Ǵ��ϴ� �Լ��Դϴ�.
{
	if (op == 2)//not�� ���� �������Դϴ�.
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
int impAri(int a, int b)//imp�����Դϴ�.
{
	if (a == 6 && b == 7)
		return 6;
	else
		return 7;
}
int notAri(int a)//not�����Դϴ�.
{
	if (a == 7)
		return 6;
	else
		return 7;
}
int orAri(int a, int b)//or�����Դϴ�.
{
	if (a == 6 && b == 6)
		return 6;
	else
		return 7;
}
int andAri(int a, int b)//and�����Դϴ�.
{
	if (a == 7 && b == 7)
		return 7;
	else
		return 6;
}
void opPrint(int a)//����ǥ�� ����� ���� �ʿ��� ������ ����Լ��Դϴ�.
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