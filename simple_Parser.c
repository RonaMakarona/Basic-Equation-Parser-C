#include <stdio.h>
#include <stdlib.h>
#include <string.h>

errno_t err;

enum type_Flag {
	NUM,
	OPR,
	UNDEFI
};

struct str_Obj {
	enum type_Flag type;
	char value[10];
};

int main(int agrc, char* argv[]) {
	
	char to_Parse_Str[100];
	struct str_Obj parse_Arr[100];
	parse_Arr[0].type = UNDEFI;
	int parse_Arr_Index = 0;

	int str_Index = 0;
	int num_Index = 0;
	struct str_Obj str_Object;

	printf("Enter the expression: \n");
	scanf_s("%100[^\n]", to_Parse_Str, sizeof(to_Parse_Str));

	while (to_Parse_Str[str_Index] != '\0')
	{
		switch (to_Parse_Str[str_Index])
		{
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':

			if (parse_Arr[parse_Arr_Index].type == NUM) {
				parse_Arr[parse_Arr_Index].value[num_Index] = to_Parse_Str[str_Index];
				num_Index++;
				str_Index++;
			}

			else {
				parse_Arr[parse_Arr_Index].type = NUM;
				parse_Arr[parse_Arr_Index].value[num_Index] = to_Parse_Str[str_Index];
				num_Index++;
				str_Index++;
			}

			break;

		case '+': case '-': case '/': case '*':
			parse_Arr[parse_Arr_Index].value[num_Index] = '\0';

			parse_Arr_Index++;
			num_Index = 0;
			parse_Arr[parse_Arr_Index].type = OPR;

			parse_Arr[parse_Arr_Index].value[0] = to_Parse_Str[str_Index];
			str_Index++;
			parse_Arr_Index++;
			break;

		case ' ':
			if (parse_Arr[parse_Arr_Index].type == NUM) {
				parse_Arr[parse_Arr_Index].value[num_Index] = '\0';
				str_Index++;
			}
			else
			{
				str_Index++;
				num_Index = 0;
			}

			break;

		default:
			break;
		}
	}
	parse_Arr[parse_Arr_Index].value[num_Index] = '\0';
	parse_Arr[parse_Arr_Index + 1].type = UNDEFI;
	printf("The solution is: %d \n",interpret_Parse(parse_Arr));
	return 0;
}

int interpret_Parse(struct str_Obj parsed_Arr[]) {

	int parsed_Arr_Index = 0;
	int value_Index = 0;
	char num[10];
	int a;
	int b;
	char operator = ' ';

	if (parsed_Arr[0].type != NUM) {
		printf("Syntax error! \n");
		return 0;
	}

	a = atoi(parsed_Arr[parsed_Arr_Index].value);
	parsed_Arr_Index++;

	while (parsed_Arr[parsed_Arr_Index].type != UNDEFI)
	{
		if (parsed_Arr[parsed_Arr_Index].type == OPR) {
			operator = parsed_Arr[parsed_Arr_Index].value[0];
			parsed_Arr_Index++;
			b = atoi(parsed_Arr[parsed_Arr_Index].value);
		}

		switch (operator)
		{
		case '+':
			a = add(a, b);
			break;
		case '-':
			a = sub(a, b);
			break;
		case '*':
			a = mul(a, b);
			break;
		case '/':
			a = divide(a, b);
			break;
		default:
			break;
		}

		parsed_Arr_Index++;
	}

	return a;
}
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
float divide(int a, int b) { return a / b; }

// to fix: add negative numbers (signed int)
// im muted
// maybe add mathematical order to opeartors (?)
// add int capacity (not more than given num)
// add negate (func if u put - it returns negative )
