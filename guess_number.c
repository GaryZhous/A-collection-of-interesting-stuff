#include<stdio.h>
#include<stdlib.h>
int getres(char s[],int length)
{
	int flag=0;
	for(int i=0;i<=length;i++)
	{
		if((int)s[i]>57 || (int)s[i]<48 && (int)s[i]!=0)
		{
			flag++;
		}
		if(s[i]=='-')
		{
			return -1;
		}
	}
	if(flag == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
extern void number_generator();
int m_strlen(char *p)
{
	int cnt=0;
	while(1)
	{
		cnt++;
		p++;
		if(*p=='\0')
		{
			break;
		}
	}
	return cnt;
}
int main()
{
	number_generator();
  int target = rand();
	int res;
	int res_target;
	int arr_length;
	char input[3];
	int limit_l=sizeof(input)/sizeof(input[0]);
	printf("please enter a number,if you want to exit,please enter 'q':\n");
  scanf("%s", input);
  if (input[0] == 'q')
   goto sussy;
	while(1)
	{
		int l=0;
		arr_length=m_strlen(input);
		if(arr_length>4)
		{
			printf("too long,limit 4!\n");
			continue;
		}
		res=getres(input,arr_length);
		switch(res)
		{
			case 1:
				res_target=atoi(input);	
				if(res_target<target && res_target>=0)
				{
					printf("try bigger!\n");
          scanf("%s",input);
					continue;

				}else if(res_target>target){
		
					printf("try smaller!\n");
          scanf("%s",input);
					continue;
				}
				else if(res_target == target)
				{
					printf("\n\ncongratulations,you guess successful!\n\n");
					break;
				}
				else
				{
					printf("unknowing error!\n");
          scanf("%s",input);
					continue;
				};
			case 0:
				printf("please enter a number!retry!\n");
        scanf("%s",input);
				continue;
			case -1:
				printf("can not be negtive number!\n");
        scanf("%s",input);
				continue;
			default:
				printf("error\n");
		}	
    break;
	}
sussy:
  printf("thx for guessing, have fun!\n");
  return 0;
}
